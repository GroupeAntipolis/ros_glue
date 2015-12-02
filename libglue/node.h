//
//
//  	G.L.U.E. by M.C.G. 2015 
//
//  	Glue stands for 
// 	Genetically Led Universal Evaluator.
//
// 		Add some glue in your code... 
//

/**
	Node Class header file.
	Node class is the base element of a Glue Graph.
**/

#ifndef __NODE_H__
#define __NODE_H__

#include <deque>
#include "glue_types.h"
#include "random_gen.h"
#include "mutation_stack.h"
#include "global.h"

	/// Fixed or dynamical input or output
	/// A FIFO node have a fixed number of possible connexions (input and output)
	/// A FIDO one have a dynamical number of possible clients.
	/// A DIFO have a dynamical number of possible servers.
	/// For now, there is no DIDO nodes in glue, but nothing theoretically
	/// exluded :)
	/// XIXO ability of the node type depends on its primary operation nature.

	enum node_io_mode
	{
		fifo, 	/// fixed width of both in and out:
			  	/// graphnode or array manipulator node.
		fido, 	/// fixed width of in, variable with out: 
				/// Constant, unary op
		difo,	/// unused for now.
		dido 	/// Binary op
	};

	/// The node is the base architecture element of a glue
	/// structure.
	/// a node class can be seen as a structure able do do some
	/// basic computation.

	class node
	{
	public:

		/// base constructor for nodes
		node();
		~node();
		/// node id (graph scope)
		int node_id;

		/// these decribes how many connexions, a particular node type
		/// can handle.
		int maxcli,maxsrv,mincli,minsrv;

		/// a node holds a g_nbr value (see glue_types.h)
		g_nbr value;

		/// our random generator
		static random_gen* rnd;

		/// our pure virtual mutation
		/// function
		virtual void mute(mutation* mut)=0;
		static void reverse_mute(mutation* pmutation);
		static void delete_mute(mutation* pmutation);


		/// compute values from servers
		/// store result in clients!
		/// pure virtual : abstract class
		virtual void activate()=0;

		/// node_output have member to set its value
		/// pure virtual : abstract class
		virtual void input_value(g_nbr pvalue)=0;

		/// static factory 
		/// This let descendants deal with node_factory
		/// pure virtual : abstract class
		virtual node* create()=0;
		virtual void store();

		/// static stock of objects
		/// static : shared by node type
		std::deque<node*>* node_stock;


		/// list of nodes connected to this node
		/// Servers provide input and clients are set from
		/// output values after an activation (graph_player)
		std::deque<node*> clients;
		std::deque<node*> servers;

		/// iterator for pointing in graph.nodes list
		std::deque<node*>::iterator cli_iterator;
		std::deque<node*>::iterator srv_iterator;

		/// XIXO ability of node type
		/// static : shared by node type
		const static node_io_mode io_mode=fifo;

		/// Serialization
		/// virtual : extendable by subclass
		virtual byte* toArray(int* size);
		/// pure virtual : abstract class
		virtual bool fromArray(byte* parray)=0;

	};

#endif