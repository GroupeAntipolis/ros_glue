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

/// the graph manager is a simple (class)
/// interface for a simpler usage of glue
/// object modules.

#ifndef __GRAPHMAN_H__
#define __GRAPHMAN_H__

#include "graph.h"
#include "graph_coach.h"

/** \brief The graph_manager is an helper (interface) for external programs using Glue
*
*	
*/
class graph_manager
{

	public:
	/// constructor for the graph_manager object
	graph_manager(int pin,int pout,int min_nodes,int max_nodes);
	~graph_manager();
	/// edge to coach training sets adding method
	void add_training(g_nbr* vi,g_nbr* vo);
	
	void activate(g_nbr* vi,g_nbr* vo);

	/// idem for get the training count already
	/// held by the coach
	int get_training_count();

	bool is_training();

	void start_training();

	/// this stops the thread
	void stop_training();

	bool test_serialization();
	bool test_geometer();

	bool test_glue();

	double getScore();

	private:

	/// for correctly doing his work this class need
	/// private access to glue ressources

	/// ... a graph on wich work is done ...
	graph* _graph;

	/// ... a training coach ...
	graph_coach* _graph_coach;

	graph_player* _graph_player;

};

#endif