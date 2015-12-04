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

#ifndef __FUNCTION_H__
#define __FUNCTION_H__

#include "glue_types.h"

//typedef g_nbr(*binary_operator_pointer)(g_nbr,g_nbr);

typedef g_nbr*(*op)(g_nbr* values);


class operation
{
	public:
	operation();
	void execute();
	void setParm(g_nbr parm);
	protected:

	g_nbr* params;

};


class binary_operation:operation
{
	binary_operation();
};

#endif