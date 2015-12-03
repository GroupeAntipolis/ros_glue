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

/// This class evolve a graph conforminig to prdefined set of input and output values.
/// the set is filled by the add training function

#ifndef __GRAPHCOACH_H__
#define __GRAPHCOACH_H__

#include "graph.h"
#include "mutation_stack.h"
#include "glue_types.h"
#include "random_gen.h"
#include "graph_evaluators.h"
#include <pthread.h>
enum mutation_count_mode
{
	mut_cnt_auto, 	/// the coach will choose automatically the right
					/// mutation count for a train moment
	mut_cnt_max, 	/// random mutation count in interval 
					/// [min_mut,..,max_mut]
	mut_cnt_fix		/// mutation count per moment fixed by max_mut
};

/** \brief The graph coach class is used to manage training
*
*	
*/
extern "C" class graph_coach
{
public:
	/// our constructor
	graph_coach(graph_evaluator* pgraph_evaluator);
	~graph_coach();

	/// simple method to get the number
	/// of registered sets of traiining values
	void add_training(g_nbr* vi,g_nbr* vo);

	/// Adds a set of input training values
	/// and an output one.
	int get_training_count();

	graph_evaluator* Graph_evaluator;


	/// random number generator
	random_gen* Rnd;

	/// how much mutation between evaluations
	int max_mut;
	int min_mut;
	mutation_count_mode mut_mode;

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

	double score;

	/// configuration

	/// how much processor we have?
	int process_count;

	/// how much graph individuals we want
	/// to train simultaneously
	int population_size;

private:

	/// thread that will host trainers for training
	pthread_t graph_thread;

};

#endif