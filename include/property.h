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

#ifndef Property_Header
#define Property_Header

// 	USAGE
//++++++++++
//	HEADER:
//============================================
//	class Dumb
//	{
//		public:
//		Dumb();
//		// Parent public property
//		Dumb* get_parent();
//		void set_parent(Dumb* pparent); 
//		Property<Dumb*, Dumb> Parent;
//		private:
//
//		Dumb* _parent;
//	};
//
//	SOURCE:
//============================================
//	Dumb::Dumb()
//	{
//		// setting up parent property
//		Parent.Set_Class( this );
//        Parent.Set_Get( &Dumb::get_parent );
//        Parent.Set_Set( &Dumb::set_parent );
//        _parent=NULL;
//	};
//
//	Dumb* Dumb::get_parent()
//	{
//		return _parent;
//	};
//
//	void Dumb::set_parent(Dumb* pparent)
//	{
//		_parent=pparent;
//	}; 




template<typename Type, typename ClassHolder>
class Property
{
    private:

    Type (ClassHolder::*Get)();
    void (ClassHolder::*Set)(Type Val);
    ClassHolder * Class;

    public:

    Property() : Get(NULL), Set(NULL), Class(NULL) {}
    Property(ClassHolder * ClassA, Type (ClassHolder::*GetA)(), void (ClassHolder::*SetA)(Type Val)) :  Class(ClassA), Get(GetA), Set(SetA) {}

    void Set_Property_Control(ClassHolder * ClassA, Type (ClassHolder::*GetA)(), void (ClassHolder::*SetA)(Type Val))
    {
        Class = ClassA;
        Get = GetA;
        Set = SetA;
    }

    void Set_Get(Type (ClassHolder::*GetA)())
    {
        Get = GetA;
    }

    void Set_Set(void (ClassHolder::*SetA)(Type Val))
    {
        Set = SetA;
    }

    void Set_Class(ClassHolder * Holder)
    {
        Class = Holder;
    }

    // set
    Type operator = (const Type& In)
    {
        if ( Set ) (Class->*Set)(In);
        return In;
    }

    // set
    Type operator = (Property& In)
    {
        if ( Set ) (Class->*Set)(In);
        return In;
    }

    // get
    operator Type()
    {
        return Get ? (Class->*Get)() : 0;
    }

};

#endif