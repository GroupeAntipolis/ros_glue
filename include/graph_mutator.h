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

#ifndef __GRAPHMUT_H__
#define __GRAPHMUT_H__

#include "graph.h"
#include "mutation_stack.h"
#include "random_gen.h"
#include "node_factory.h"

enum meta_mutation_id
{
	m_connectServer,
	m_disconnectServer,
	m_addNode,
	m_delNode,
	m_mute
};

/*enum mutation_id
{
	connectServer,
	disconnectServer,
	connectClient,
	disconnecClient,
	addNode,
	delNode,
	mute
};*/

/** \brief The graph_mutator implements the rules for self modifying graph
*
*	
*/
extern "C" class graph_mutator
{

public:

	/// Constructor
	graph_mutator(graph* pgraph,bool can_init=true);
	~graph_mutator();
	/// mutation operation
	/// It includes metaoperations
	void mute(int times);
	/// accept previously made mutations
	/// reserse mutations can be saved
	void accept(bool saveflag);
	/// reject previously made mutations
	/// mutations can be saved
	void reject(bool saveflag);

	static random_gen* rnd;

	void prog_add_client(int nodeid,int clientid,int clientindex);
	void prog_add_server(int nodeid, int serverid, int serverindex);

	long n_metamutations;
	long get_n_mutations();

	#ifdef dbg_mutation_loops
		long last_n_metamutations;
	#endif

private:
	#ifdef dbg_mutation_loops
	bool check_mutation_nb();
	#endif
	/// pointer to current graph
	graph* _graph;
	/// current mutation manager
	mutation_manager* mutman;
	/// dynamicla list of mutables
	std::deque<node*>mutables;

	/// initialize graph
	void initialize_graph();

	int nb_nodes;
	int min_nodes;
	int max_nodes;

	/// meta operations
	/// ***************
	/// the metaoperation'job is to transform the graph
	/// in an open but controlled mode. 
	/// After a metaoperation, the graph will be as consistent
	/// as it was before.

	void meta_add_node(int nodeid);
	void meta_del_node(int nodeid);
	void meta_add_client(int nodeid);
	int meta_del_client(int nodeid,bool checknodes=true);
	void meta_add_server(int nodeid);
	int meta_del_server(int nodeid,bool checknodes=true);
	void meta_mute(int nodeid);
	void meta_check_node(int nodeid);


	/// final operations
	/// ****************
	/// The final operations make the job & nothing else
	/// there dont care about graph consistency (that's
	/// the job of metaoperations).
	/// static cause dont need context to act
	/// graph is provided in mutation_struct argument

	static void add_node(mutation* pmutation);
	static void del_node(mutation* pmutation);
	static void add_client(mutation* pmutation);
	static void del_client(mutation* pmutation);
	static void add_server(mutation* pmutation);
	static void del_server(mutation* pmutation);
	static void mute(mutation* pmutation);

	static void delete_add_node(mutation* pmutation);
	static void delete_del_node(mutation* pmutation);
	static void delete_add_client(mutation* pmutation);
	static void delete_del_client(mutation* pmutation);
	static void delete_add_server(mutation* pmutation);
	static void delete_del_server(mutation* pmutation);
	static void delete_mute(mutation* pmutation);



};



#endif