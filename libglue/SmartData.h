//
//
//  	C++ SmartData library
//
//	Standard datatypes byte-level storage & manuputation.
//
//	Custom ibrary managing blob object and typed multipart messaging.
//		[Marco Carta-Gullung . 2015]
//
//


// Choose architecture to build
#ifdef __AVR
	#define __ARCH_AVR
#endif
#ifdef __x86_64__
	#define __ARCH_X86
#endif
//	#define __ARCH_ARM

#ifndef SmartData_h
#define SmartData_h

/** This conditional definition allow implicit msg conversion
* e.g. An x86 float will be seen as an avr double and so on
*
**/
#ifdef __ARCH_AVR
	#include "Arduino.h"
	typedef long int_32;
	enum BDType{
	    BDTBool,
		BDTByte,
	    BDTInt, 		// x86 short
	    BDTLong,		// 86 int (int32)
	    BDTBigLong,
	    BDTDouble,
	    BDTBigDouble,
	    BDTString,

	    BDTBools, 
	    BDTBytes,
	    BDTInts, 
	    BDTLongs, 
	    BDTBigLongs,
	    BDTDoubles,
	    BDTBigDoubles,

	    BDTImage,

	    // short of avr are not std desc
	    BDTShort, // (avr int)
	    BDTFloat
	};
#endif
#ifdef __ARCH_X86
	#include <stdlib.h>
	#include <string.h>
	#include <string>
	using std::string;
	//using namespace std;
	typedef unsigned char byte;
	typedef int int_32;
	enum BDType{
	    BDTBool,
		BDTByte,
	    BDTShort, 
	    BDTInt, 
	    BDTLong,
	    BDTFloat,
	    BDTDouble,
	    BDTString,

	    BDTBools, 
	    BDTBytes,
	    BDTShorts, 
	    BDTInts, 
	    BDTLongs,
	    BDTFloats,
	    BDTDoubles,

	    BDTImage
	};



#endif


class SmartMessage
{
	public:
		SmartMessage();
		~SmartMessage();


		static bool short2Bytes(byte* buf, short value);
		static bool bytes2Short(byte* buf, short* value);
		static bool int2Bytes(byte* buf, int value);
		static bool bytes2Int(byte* buf, int* value);
		static bool long2Bytes(byte* buf, long value);
		static bool bytes2Long(byte* buf, long* value);
		static bool float2Bytes(byte* buf, float value);
		static bool bytes2Float(byte* buf, float* value);
		static bool double2Bytes(byte* buf, double value);
		static bool bytes2Double(byte* buf, double* value);


		void setContent(byte* msg);
		void Empty();
		bool isEmpty();
		byte* toArray();
		byte* getArray();
		void fromArray(byte* msg);

		// x86/64 only members
		#ifdef __ARCH_X86
		char* toString();
		#endif

		/** Short
		*	x86 : 2 bytes
		*	AVR : 2 bytes
		**/
		short getShort(int index);
		void addShort(short value);

		/** Int
		*	x86 : 4 bytes
		*	AVR : 2 bytes
		**/
		int getInt(int index);
		void addInt(int value);

		/** Long
		*	x86 : 8 bytes
		*	AVR : 4 bytes
		**/
		long getLong(int index);
		void addLong(long value);

		/** Float
		*	x86 : 4 bytes
		*	AVR : 2 bytes
		**/
		float getFloat(int index);
		void addFloat(float value);

		/** Double
		*	x86 : 8 bytes
		*	AVR : 4 bytes
		**/
		double getDouble(int index);
		void addDouble(double value);

		/** Bool
		*	x86 : 1 byte
		*	AVR : 1 byte
		**/
		bool getBool(int index);
		void addBool(bool value);

		/** Byte
		*	x86 : 1 byte
		*	AVR : 1 byte
		**/
		byte getByte(int index);
		void addByte(byte value);

		/** String
		*	Arch. indipendent
		**/
		char* getString(int index);
		void addString(char* pstr);

		/** Type generique
		*	x86 : n byte(s)
		*	AVR : n byte(s)
		**/
		/*template <typename data_t>
		data_t getData(int index,BDType tpe);
		template <typename data_t>
		void addData(data_t value,BDType tpe);*/

		/** Bytes
		*	Arch. indipendent
		**/
		byte* getBytes(int index,short* plength);
		void addBytes(byte* value, short plength);

		void attach(int plength);

		int_32 size();
		int count();
		int_32 identifier;
	private:
		byte* content; /// the size - header (4bytes) then, the data...
		int_32 getElmIndex(int index);
		void setSize(int_32 sz);
};

#endif


