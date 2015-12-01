# Glue ROS node #

## Glue ##

Glue stands for Genetically Led Universal Evaluator and is a machine learning algorithm similar to genetic programming (GP), except that it does not use a concept of population. Clearly, Glue optimizes a single candidate solution to the problem addressed in contrast to the use of C GP. This excluded any crossover operator (evolutionary operators), but a reverse mutation operator is introduced. To solve the problem, optimizes Glue (transforms) a graph whose nodes are operators.

(See more on <a href="http://marco.carta.fr/marco/homepage/spip.php?rubrique26&page=rubrique">this page</a>.)

>1. Genetically Led Universal Evaluator

## Glue node ##

This package is dedicated to machine learning tasks with reals. ros_glue is a service type node for <a href="wiki.ros.org">ROS</a>.
Feel free to ask any <i>numerical</i> question to your glue graph.

### Topics: ###

	serviceClient<glue_node::glue_create>("glue_create");
	serviceClient<glue_node::glue_query>("glue_query");
	advertise<glue_node::glue_training>( "glue_tranining");
	
### Messages or requests: ###

#### glue_create (srv) ####
+ string name
+ int32 in_count
+ int32 out_count

+ bool success

#### glue_training (msg) ####
+ float64[] training_query
+ float64[] training_answer

#### glue_query (srv) ####
+ float64[] query

+ float64[] answer



### Usage: ###

These are the 3 step in which pass in order to use glue:

 1. Create
 2. Train
 3. Query
 
 Launch file:
 
		$ roslaunch ros_glue glue_minimal.launch 
		
#### Help: ####

See glue_client.cpp for a (near) complete example.
	
	
 Enjoy ... & feedback on <a href="github.com/GroupeAntipolis/ros_glue">github.com/GroupeAntipolis/ros_glue</a>


<center><b>2015 M. Carta-Gullung pour GroupeAntipolis</b></center>

