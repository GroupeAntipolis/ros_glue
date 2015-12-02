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

#ifndef __MUTSTACK_H__
#define __MUTSTACK_H__

#include <iostream>
#include <deque>
using namespace std;

/// forward declaration of mutation
/// for first use in mutator function pointer
class mutation;

/// Pointer to a restore function in a class
typedef void(*mutator)(mutation* pmutation);

/// mutation (reversible) representation
class mutation
{
	public:

	/// constructor
	mutation(void* pdata,int pidentifier,mutator pinjector,mutator pmdeleter);

	/// data all public
	void* data;
	int identifier;
	mutator injector;
	mutator mdeleter;

};

class mutation_manager
{
	public:

	mutation_manager();
	~mutation_manager();

	void add_mutation(void* pdata,int pidentifier,mutator pinjector,mutator pmdeleter);
	void add_mutation(void* pdata,mutator pinjector,mutator pmdeleter);
	void add_mutation(mutation* pmutation);
	void accept();
	void reject();
	/// count of mutations
	long n_mutations;
	private:
	std::deque<mutation*> _lm;

	/// iterator fo pointing in graph.nodes list
	std::deque<mutation*>::iterator mutation_iterator;
};


#endif