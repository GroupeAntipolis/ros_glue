//
//
///  	G.L.U.E. by M.C.G. 2015 
//
///  	Glue stands for 
/// 	Genetically Led Universal Evaluator.
//
/// 		Add some glue in your code... 
//
//

#ifndef __GRAPHGEO_H__
#define __GRAPHGEO_H__

#include <deque>
#include "global.h"
using namespace std;

typedef deque<int> io_suite;
typedef deque<io_suite*> configuration;
typedef deque<configuration*> multiconf;

/** \brief The graph_geometer can compute input output configuration used in sampling
*
*	
*/
class graph_geometer
{
	
public:

	graph_geometer();
	~graph_geometer();

	/// retrieves thes dividers of number even a big one.
	io_suite* calc_dividers(int tiw);

	/// this wrapper extends get_power_couples addin the ability to filter the result deque
	///fixing possible output number in an interval
	configuration* get_power_couples_ex(int value,int out_width=-1,int min_out_width=1);

	/// this function retrieves the different couples of number defining extremities of
	/// a graph able to process the number of values defined in "value" parameter
	configuration* get_power_couples(configuration* cconf, int value,int out_width=-1,int min_out_width=1);

	/// calculate how many layers is needed by a
	/// particular configuration
	int calc_layer_count(int width, int a, int b);

	/// calculate how many times in total the graph
	/// will be used by this conf
	int calc_graph_count(int width, int a, int b);

	/// return the feasible complete configurations for problem defined by
	/// this io suite and requested outputs number
	configuration* search_correct_configs(io_suite* dimensions, int output_width);

	/// search for arbitrary suite in a conf
	bool suite_exists(configuration* conf, io_suite* suite);
	
	/// let delete a configuration
	void delete_conf(configuration* conf);
	void delete_multi_conf(multiconf* mconf);

private:

	/// given a value and one of its possible divisors, retieve the possible coupled value for
	/// then be able to define a compatible divisor graph
	io_suite* calc_possible_output_width(int tiw, int giw,int out_width=-1,int min_out_width=1);

	/// here we combine all the per dimension configurations together
	/// then we test all generated complete configuration
	configuration* search_configs(configuration* mainc,multiconf* dims);

	/// detect if the per dimension configuration
	/// is compatibe with main partitioning
	bool is_good_conf(io_suite* conf);

	/// combine the suites of two configurations together.
	/// dest suites nb = c1 suites nb * c2 suites nb
	configuration* combine(configuration* c1,configuration* c2);

	int lastnb;
	int lastsquare;
};

#endif