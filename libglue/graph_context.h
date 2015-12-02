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

#ifndef __GRAPHCONTEXT_H__
#define __GRAPHCONTEXT_H__

#include "node_factory.h"

/////////////////////////////////////////
// The graph context is a singleton used
// to store and serve transversal


static class graph_context
{

public:
 	static graph_context();
	
private:

	// we include the factory in order to
	// reference nodes. 
	node_factory* factory;

};
#endif