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

#ifndef __NODELOGIC_H__
#define __NODELOGIC_H__
#include "math_nodes.h"

	void logic_lib_registration();

// *********************************** NODE LOGIC ************************************* //

class node_logic:public node
{
public:
	node_logic();

	/// forward value
	void activate();
	
	/// mutation function
	void mute(mutation* mut);
	static void delete_mute(mutation* pmutation);
	static void reverse_mute(mutation* pmutation);

	/// XIXO ability of node type
	/// static : shared by node type
	const static node_io_mode io_mode=fido;
	
	int not_true;
	
protected:
	int srv_it;
};
	
// *********************************** NODE SUP (>) ************************************* //

class node_sup:node_logic
{
public:
	node* create();

	/// node_input have member to set its value
	/// and let it forward it in direction of
	void input_value(g_nbr pvalue);

	/// Serialization
	byte* toArray(int* size);
	bool fromArray(byte* parray);

};

#endif