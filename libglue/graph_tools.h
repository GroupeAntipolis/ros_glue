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
#ifndef __GRAPHTOOLS_H__
#define __GRAPHTOOLS_H__

#include "graph.h"

bool test_graph(graph* pgraph);
bool test_node(node* tnode,graph* grph);
int get_node_index(node* pnode,graph* grph);

/// tell if clientnode is client of servernode
bool isClientOf(node* servernode,node* clientnode, graph* grph);

/// tell if servernode is server of clientnode
bool isServerOf(node* clientnode,node* servernode, graph* grph);

#endif
