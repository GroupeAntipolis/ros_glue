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
#ifndef __NODEFACT_H__
#define __NODEFACT_H__
#include "node.h"

/// first definition of node_factory
class node_factory;

/// Pointer to a register a set of typ nodes in a node type library
typedef void(*registrator)(node_factory* pfactory); 

class node_factory
{
	
public:
	node_factory();
	~node_factory();
	void store_node(node* pnode,bool pregister=false);
	int get_type_count();
	node* create_node(int ptypeid);
	node* create_node(char * ptypeid);

	static void add_registrator(registrator pregistrator);

private:
	int node_type_number;
	std::deque<node*> factory;
	static std::deque<registrator> registrators;
	/// iterator for pointing in graph.nodes list
	std::deque<node*>::iterator fact_iterator;
};

#endif