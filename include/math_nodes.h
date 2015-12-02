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

#ifndef __NODEMATH_H__
#define __NODEMATH_H__
#include "node.h"
#include "node_factory.h"


	//void factory_callback(node_factory* pfactory);
	void math_lib_registration();




// *********************************** NODE BINARY ************************************* //

class node_binary: public node
{
public:

	/// constructor
	node_binary();

	/// mutation function
	void mute(mutation* mut);
	static void delete_mute(mutation* pmutation);
	static void reverse_mute(mutation* pmutation);

	void activate();

	/// XIXO ability of node type
	/// static : shared by node type
	const static node_io_mode io_mode=dido;
protected:
	int srv_it;

};

// *********************************** NODE UNARY ************************************* //

class node_unary: public node
{
public:

	/// constructor
	node_unary();

	/// mutation function
	void mute(mutation* mut);
	static void delete_mute(mutation* pmutation);
	static void reverse_mute(mutation* pmutation);

	void activate();

	/// XIXO ability of node type
	/// static : shared by node type
	const static node_io_mode io_mode=fido;

};

// *********************************** NODE PLUS ************************************* //

class node_plus:node_binary
{
public:

	/// static factory 
	/// This let descendants deal with node_factory
	node* create();
	/// static stock of objects

	void input_value(g_nbr pvalue);

	/// Serialization
	byte* toArray();
	bool fromArray(byte* parray);
};

// *********************************** NODE MINUS ************************************* //

class node_minus:node_binary
{
public:

	/// static factory 
	/// This let descendants deal with node_factory
	node* create();

	void input_value(g_nbr pvalue);

	/// Serialization
	byte* toArray();
	bool fromArray(byte* parray);
};

// *********************************** NODE MULTIPLY ************************************* //

class node_multiply:node_binary
{
public:

	/// static factory 
	/// This let descendants deal with node_factory
	node* create();

	void input_value(g_nbr pvalue);

	/// Serialization
	byte* toArray();
	bool fromArray(byte* parray);
};

// *********************************** NODE DIVIDE ************************************* //

class node_divide:node_binary
{
public:

	/// static factory 
	/// This let descendants deal with node_factory
	node* create();

	void input_value(g_nbr pvalue);

	/// Serialization
	byte* toArray();
	bool fromArray(byte* parray);
};

// *********************************** NODE CONST ************************************* //

class node_const:node
{
public:
	node_const();
	node* create();

	/// node_input have member to set its value
	/// and let it forward it in direction of
	void input_value(g_nbr pvalue);

	/// forward value
	void activate();

	/// mutation function
	void mute(mutation* mut);
	static void delete_mute(mutation* pmutation);
	static void reverse_mute(mutation* pmutation);

	/// XIXO ability of node type
	/// static : shared by node type
	const static node_io_mode io_mode=fido;
	/// Serialization
	byte* toArray(int* size);
	bool fromArray(byte* parray);
	int sens;
	int pas;

};

// *********************************** NODE SIN ************************************* //

class node_sin:node_unary
{
public:

	/// static factory 
	/// This let descendants deal with node_factory
	node* create();

	void input_value(g_nbr pvalue);

	/// Serialization
	byte* toArray();
	bool fromArray(byte* parray);
};

// *********************************** NODE COS ************************************* //

class node_cos:node_unary
{
public:

	/// static factory 
	/// This let descendants deal with node_factory
	node* create();

	void input_value(g_nbr pvalue);

	/// Serialization
	byte* toArray();
	bool fromArray(byte* parray);
};

#endif