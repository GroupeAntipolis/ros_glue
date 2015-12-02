//
//
//  	G.L.U.E. by M.C.G. 2015 
//
//  	Glue stands for 
// 	Genetically Led Universal Evaluator.
//
// 		Add some glue in your code... 
//
//

#ifndef __GRAPHTRAIN_H__
#define __GRAPHTRAIN_H__

#include "graph.h"
#include "graph_coach.h"
#include "graph_evaluators.h"
#include "glue_types.h"
#include <pthread.h>
//////////////////////////////////////
/// the graph trainer works with more
/// graph coaches (NO! TODO: changes this) comformly to the population
/// size and the number of desired processes
/// In a biprocessor configuration programmer
/// should consider using at least 2 processes
/// in order to use the entire power of the machine.
/// A unique process in a multiprocessor configuration
/// can be a way to share power between glue and other
/// computer stuff (programs)

class graph_trainer
{

public:

	/// trainer constructor
	graph_trainer(graph_coach* pgraph_coach);
	graph_trainer(graph_coach* pgraph_coach, graph_evaluator* pgraph_evaluator);
	graph_trainer(graph_coach* pgraph_coach, graph_evaluator* pgraph_evaluator,double score);
	~graph_trainer();

	/// this memeber starts the thread
	void start_training();

	/// this stops the thread
	void stop_training();

	/// we ste that to true to
	/// indicate that we want
	/// the thread stops.
	bool wait_stop;

	/// the thread indicates
	/// whenever it starts or
	/// stops by setting started
	/// to true or false
	bool started;

	/// the shared graph coach
	graph_coach* Graph_coach;

	graph* Graph;

	graph_evaluator* Graph_evaluator;

	double score;
	int thread_index;

	graph_trainer* clone();

private:

	/// thread that will host a graph for training
	pthread_t graph_thread;

};
#endif