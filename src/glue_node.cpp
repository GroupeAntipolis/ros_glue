/*
 * Copyright (C) 2015, Marco Carta-Gullung, GroupeAntipolis.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *   * Redistributions of source code must retain the above copyright notice,
 *     this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *   * Neither the names of Stanford University or Willow Garage, Inc. nor the names of its
 *     contributors may be used to endorse or promote products derived from
 *     this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

/** /mainpage
 * This program is used to explore the environnement in a smart way.
 *
 */
//#define DEBUG
 // for shutdown
#include <signal.h> 

// %Tag(FULLTEXT)%
#include "ros/ros.h"
#include "std_msgs/Float32.h"
#include <cstdio>
#include <deque>
#include "math.h"
/// include glue lib

#include "SmartData.h"
#include "random_gen.h"
#include "graph_manager.h"
#include "math_nodes.h"
#include "logical_nodes.h"
/*#include "/home/carta/prog/Projects/LIBRARIES/CPP/SmartDataCPP/SmartData.h"
#include "/home/carta/prog/Projects/LIBRARIES/CPP/rng/random_gen.h"
#include "/home/carta/prog/Projects/LIBRARIES/CPP/glue/graph_manager.h"*/

#include "glue_node/glue_create.h"
#include "glue_node/glue_open.h"
#include "glue_node/glue_query.h"
#include "glue_node/glue_training.h"

using namespace std;

// conf
const int standby_time = 5;
const char* node_name="glue_node";


// glue graph
graph_manager* gm=0;
string graphName;
std::vector<double> graph_out_data;
std::vector<double> graph_in_data;

// Signal-safe flag for whether shutdown is requested
sig_atomic_t volatile g_request_shutdown = 0;



// Replacement SIGINT handler
void mySigIntHandler(int sig)
{
  g_request_shutdown = 1;
}

// replace win32 sleep
void msleep(int millis){usleep(millis*1000);};


void activate_training()
{
	if(gm!=0)
	if(!gm->is_training()&&gm->get_training_count()>0)
	{
		ROS_INFO_NAMED(node_name,"Activate training mode.");
		gm->start_training();
	}
}

void deactivate_training()
{
	if(gm->is_training())
	{
		ROS_INFO_NAMED(node_name,"Deactivate training mode.");
		gm->stop_training();
	}
}


/** this let create a new glue_graph
*
**/
bool srv_create(glue_node::glue_create::Request  &req,
         glue_node::glue_create::Response &res)
{

	if(gm==0)
	{
		ROS_INFO_NAMED(node_name,"Create graph with %d in, %d out %d nodes ...",req.in_count,req.out_count,req.in_count*req.out_count);
		gm=new graph_manager(req.in_count,req.out_count,(req.in_count+req.out_count)*2,req.in_count*req.out_count);
		res.success=gm!=0;
		if(gm==0)
		{
			ROS_ERROR_NAMED(node_name,"Can't create GLUE graph !");
		}
		else
		{
			graph_in_data.resize(sizeof(double)*req.in_count);
			graph_out_data.resize(sizeof(double)*req.out_count);
			graphName=req.name;
		}
	}
	else
	{
		ROS_ERROR_NAMED(node_name,"Graph already exists !");
		res.success=false;
	}

  return res.success;
}

/** this let query the current glue_graph
*
**/
bool srv_query(glue_node::glue_query::Request  &req,
         glue_node::glue_query::Response &res)
{
	if(gm!=0)
	{
		deactivate_training();
		#ifdef DEBUG
		ROS_INFO_NAMED(node_name,"Query graph nodes ...");
		#endif
		gm->activate(req.query.data(),graph_out_data.data());
		res.answer=graph_out_data;
		return true;
	}
	else
	{
		ROS_ERROR_NAMED(node_name,"Graph don't exists in node !");
		return false;
	}

}

/** this let train the current glue_graph
*
**/
void sub_train(const glue_node::glue_training  &msg)
{
	if(gm!=0)
	{
		deactivate_training();
		#ifdef DEBUG
		ROS_INFO_NAMED(node_name,"Add training to %s graph. test in adr %ld; test vector %ld.",graphName.c_str(),(long)msg.training_query.data(),msg.training_query.size());
		#endif
		gm->add_training((double*)msg.training_query.data(),(double*)msg.training_answer.data());

	}

}



int main(int argc, char **argv)
{
	/**
	* The ros::init() function needs to see argc and argv so that it can perform
	* any ROS arguments and name remapping that were provided at the command line.
	* For programmatic remappings you can use a different version of init() which takes
	* remappings directly, but for most command-line programs, passing argc and argv is
	* the easiest way to do it.  The third argument to init() is the name of the node.
	*
	* You must call one of the versions of ros::init() before using any other
	* part of the ROS system.
	*/
	//ros::init(argc, argv, node_name);
	// Override SIGINT handler
	ros::init(argc, argv, node_name, ros::init_options::NoSigintHandler);
	signal(SIGINT, mySigIntHandler);

	/// initialize glue
	ROS_INFO("Initialize glue");
	math_lib_registration();
	logic_lib_registration();
	gm=0;
	/**
	* NodeHandle is the main access point to communications with the ROS system.
	* The first NodeHandle constructed will fully initialize this node, and the last
	* NodeHandle destructed will close down the node.
	*/
	ros::NodeHandle n;


	/** this line inform ros that we will subscribe on /move_base/result which says if and whe the goal position and orientation is reached.
	*
	*/
	//ros::Subscriber pc_battery_sub = n.subscribe("laptop_battery", 10, battery_msg_callback);  

	ros::ServiceServer create_service = n.advertiseService("glue_create", srv_create);
	ros::ServiceServer query_service = n.advertiseService("glue_query", srv_query);
	ros::Subscriber subtrain = n.subscribe( "glue_tranining",10, sub_train);

	/**
	* The advertise() function is how you tell ROS that you want to
	* publish on a given topic name. This invokes a call to the ROS
	* master node, which keeps a registry of who is publishing and who
	* is subscribing. After this advertise() call is made, the master
	* node will notify anyone who is trying to subscribe to this topic name,
	* and they will in turn negotiate a peer-to-peer connection with this
	* node.  advertise() returns a Publisher object which allows you to
	* publish messages on that topic through a call to publish().  Once
	* all copies of the returned Publisher object are destroyed, the topic
	* will be automatically unadvertised.
	*
	* The second parameter to advertise() is the size of the message queue
	* used for publishing messages.  If messages are published more quickly
	* than we can send them, the number here specifies how many messages to
	* buffer up before throwing some away.
	*/

    

	// %Tag(PUBLISHER)%
	/** Here we declare a publisher that propose a new position for the robot. Goal position.
	*/
	//lead_battery_pub = n.advertise< smart_battery_msgs::SmartBatteryStatus>("lead_battery_charge", 10);

	// %EndTag(PUBLISHER)%  



	/*espeak_line_msg.data="Penguins will rule the world ! Yeah !";
	speak_line_pub.publish(espeak_line_msg);*/
	/**
	* ros::spin() will enter a loop, pumping callbacks.  With this version, all
	* callbacks will be called from within this thread (the main one).  ros::spin()
	* will exit when Ctrl-C is pressed, or the node is shutdown by the master.
	*/
	ros::Rate r(100);
	int counter=0;
	// Do our own spin loop
	while (!g_request_shutdown)
	{
		// Do non-callback stuff
		counter++;
		ros::spinOnce();                  // Handle ROS events
	  	r.sleep();

	  	if(counter==standby_time*100)
	  	{
	  		activate_training();
	  		counter=0;
	  	}
	}



	ros::shutdown();


	return 0;
}
// %EndTag(FULLTEXT)%