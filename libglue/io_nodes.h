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

#ifndef __IONODES_H__
#define __IONODES_H__
#include "node.h"


// *********************************** NODE INPUT ************************************* //

class node_input:node
{
public:
	node_input();
	node* create();
	//void store();

	/// node_input have member to set its value
	/// and let it forward it in direction of
	void input_value(g_nbr pvalue);

	/// forward value
	void activate();

	/// mutation function
	void mute(mutation* mut);
	static void delete_mute(mutation* pmutation);
	static void reverse_mute(mutation* pmutation);


	/// static stock of objects
	static std::deque<node*> node_stock;
	static bool stored;/// static bool always set to false at start	
	bool is_stored();
	std::deque<node*>* get_stock();

	/// XIXO ability of node type
	/// static : shared by node type
	const static node_io_mode io_mode=fido;

	bool fromArray(byte* parray);

};

// *********************************** NODE OUTPUT ************************************* ///

class node_output:node
{
public:
	node_output();
	node* create();
	///void store();

	/// node_output have member to set its value
	/// and let it forward it in direction of
	void input_value(g_nbr pvalue);

	/// forward value
	void activate();

	/// mutation function
	void mute(mutation* mut);
	static void delete_mute(mutation* pmutation);
	static void reverse_mute(mutation* pmutation);


	/// static stock of objects
	static std::deque<node*> node_stock;
	static bool stored;/// static bool always set to false at start
	bool is_stored();
	std::deque<node*>* get_stock();

	/// XIXO ability of node type
	/// static : shared by node type
	const static node_io_mode io_mode=fifo;

	bool fromArray(byte* parray);
};

#endif