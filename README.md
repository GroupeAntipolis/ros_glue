# Glue ROS node #

## Glue ##

Glue stands for Genetically Led Universal Evaluator and is a machine learning algorithm similar to genetic programming (GP), except that it does not use a concept of population. Clearly, Glue optimizes a single candidate solution to the given problem in contrast to GP. This excluded any crossover operator (evolutionary operators), but a reverse mutation operator is introduced. To solve a problem,  Glue optimizes (transforms) a graph whose nodes are operators.

(See more on <a href="http://marco.carta.fr/marco/homepage/spip.php?rubrique26&page=rubrique">this page</a>.)

>1. Genetically Led Universal Evaluator

## Glue node ##

This package is dedicated to machine learning tasks with reals. ros_glue is a service type node for <a href="wiki.ros.org">ROS</a>.
Feel free to ask any <i>numerical</i> (cohérent) question to your glue graph. 

#### Disclaimers: ####

The code proposed is NOT complete (but usable). Feel free to insult in an elegant manner ... ;)

Glue is not a continuous solver so far, but, soon, dynamic variables nodes (see <a href="http://marco.carta.fr/marco/homepage/spip.php?rubrique26&page=rubrique">this page</a>) will alow that.

Feel free to ask for a 32bit version (or something else, but the moon, at <a href="github.com/GroupeAntipolis/ros_glue">github.com/GroupeAntipolis/ros_glue</a>

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


<center><b>2015 M. Carta-Gullung pour <a href="github.com/GroupeAntipolis">github.com/GroupeAntipolis</a></b></center>

