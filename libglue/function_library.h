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
	Functions library header file.
**/

#ifndef __FUNCTIONLIB_H__
#define __FUNCTIONLIB_H__

#include "function.h"
#include "glue_types.h"



	class function_library
	{
		public:
		list<op> functions;
		void addFunction(op pfunction);
	}




	// standard operators
	void op_plus(g_nbr* vi,g_nbr* vo);
	void op_minus(g_nbr* values);
	void op_divid(g_nbr* values);
	void op_multip(g_nbr* values);




#endif