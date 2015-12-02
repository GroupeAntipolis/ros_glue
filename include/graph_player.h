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

#ifndef __GRAPHPLAY_H__
#define __GRAPHPLAY_H__

#include "graph.h"
#include "glue_types.h"

//////////////////////////////////////
/// the graph player job is to activate
/// the graph. The graph represents an
/// operation that the player can compute.
/// The computation need input values
/// and it's result are output values.

/** \brief The graph_player allows to activate a Glue graph
*
*	
*/
extern "C" class graph_player
{

public:

	graph_player(graph* pgraph);

	void activate(g_nbr* vi,g_nbr* vo);
	
private:

	graph* _graph;

};
#endif