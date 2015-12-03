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

 // for shutdown
#include <signal.h> 

// %Tag(FULLTEXT)%
#include "ros/ros.h"
#include "std_msgs/Float32.h"
#include <cstdio>
#include <deque>
#include "math.h"
#include "glue_node/glue_create.h"
#include "glue_node/glue_open.h"
#include "glue_node/glue_query.h"
#include "glue_node/glue_training.h"
#include "random_gen.h"

using namespace std;

const char* node_name="glue_client";

// our random generator
random_gen rnd;

ros::ServiceClient create_request;
ros::ServiceClient query_request;
ros::Publisher glue_train;

// Signal-safe flag for whether shutdown is requested
sig_atomic_t volatile g_request_shutdown = 0;

// Replacement SIGINT handler
void mySigIntHandler(int sig)
{
  g_request_shutdown = 1;
}

// replace win32 sleep
void msleep(int millis){usleep(millis*1000);};


void build_training()
{
	double* inputs;
	double* output;
	glue_node::glue_training* train=new glue_node::glue_training();
	train->training_query.resize(4);
	train->training_answer.resize(1);


	inputs=train->training_query.data();
	output=train->training_answer.data();

	cout << "we build 100 trainings .." << endl;
	// we build 10 trainings
	for(int t=0;t<100;t++)
	{
		inputs[0]=rnd.next_double();
		inputs[1]=rnd.next_double();
		inputs[2]=rnd.next_double();
		inputs[3]=rnd.next_double();
		output[0]=inputs[2]*inputs[3]*cos(inputs[1]/inputs[0]);
		//output[0]=inputs[0]*cos(inputs[1]/inputs[0]);
		//output[0]=inputs[0]*inputs[1];

		cout << t << " " << inputs[0] << "*" << inputs[1] << "+" << inputs[0] << "=" << output[0] << endl;

		glue_train.publish(*train);

		/// we let the time go ..
		msleep(100);
	}

	delete train;

}

void query_glue()
{
	double* inputs;
	double* output;
	glue_node::glue_query query;
	query.request.query.reserve(4);

	inputs=query.request.query.data();
	output=query.response.answer.data();

	cout << "we query 10 times .." << endl;
	for(int t=0;t<10;t++)
	{
		inputs[0]=rnd.next_double();
		inputs[1]=rnd.next_double();
		inputs[2]=rnd.next_double();
		inputs[3]=rnd.next_double();
		output[0]=inputs[2]*inputs[3]*cos(inputs[1]/inputs[0]);
		//output[0]=inputs[0]*cos(inputs[1]/inputs[0]);
		//output[0]=inputs[0]*inputs[1];

		cout << t << "." << inputs[0] << "*" << inputs[1] << "+" << inputs[0] << "=" << output[0] << endl;
		cout << t << "." << inputs[0] << "*" << inputs[1] << "+" << inputs[0] << "=" << inputs[0] * inputs[1] + inputs[0] << endl;
		/// we let the time go ..
		msleep(500);

	}

}

bool register_service()
{
	glue_node::glue_create srv;
	srv.request.name = "test_glue_node";
	srv.request.in_count = 4;
	srv.request.out_count = 1;
	if (!create_request.call(srv))
	{
		ROS_ERROR("Failed to create glue graph !");
		msleep(3000);
		return register_service();
	}
	return true;
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

	create_request = n.serviceClient<glue_node::glue_create>("glue_create");
	query_request = n.serviceClient<glue_node::glue_query>("glue_query");
	glue_train = n.advertise<glue_node::glue_training>( "glue_tranining",10);/**/
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
	msleep(3000);
	register_service();
	build_training();
	/**
	* ros::spin() will enter a loop, pumping callbacks.  With this version, all
	* callbacks will be called from within this thread (the main one).  ros::spin()
	* will exit when Ctrl-C is pressed, or the node is shutdown by the master.
	*/
	ros::Rate r(100);
	// Do our own spin loop
	while (!g_request_shutdown)
	{
		// Do non-callback stuff
		ros::spinOnce();                  // Handle ROS events
	  	r.sleep();
	}

	ros::shutdown();

	return 0;
}
// %EndTag(FULLTEXT)%