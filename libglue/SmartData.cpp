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

#ifdef __ARCH_AVR
	#include "Arduino.h"
#else
	#include <stdio.h>
#endif

#include "SmartData.h"

const int _sz_type_desc=1;
const int _sz_head=4; // size in bytes to encode the value of the size of the content of a message
const int _sz_sub_head=2; // size in bytes to encode the value of the size of the content of a submessage
const int _last_idx=-1;
const int _sz_sub_head_complete=_sz_sub_head+_sz_type_desc;
	/** Constructor
	*
	**/
	SmartMessage::SmartMessage()
	{
		content=(byte*)malloc(_sz_head);
		#ifdef __ARCH_AVR
		// sizeof(long)==_sz_head==4
		long2Bytes(content,0);
		#else
		// sizeof(int)==_sz_head==4
		int2Bytes(content,0);
		#endif

		identifier=random();
	};

	/** Destructor
	*
	**/	
	SmartMessage::~SmartMessage()
	{
		free(content);
		content=0;
	};

	/** size
	* Returns the size in bytes of the complete message (+4 bytes header)
	**/
	int_32 SmartMessage::size(){
		int_32 size=0;
		#ifdef __ARCH_AVR
		bytes2Long(content,&size);
		#else
		bytes2Int(content,&size);
		#endif
		return size+_sz_head;
	};

	/** count
	* Returns the nuber of submessages contained in the SmartMessage instacne
	**/	
	int SmartMessage::count(){
		#ifdef __ARCH_AVR
		return (int)getElmIndex(_last_idx);
		#else
		return getElmIndex(_last_idx);
		#endif

	};

	/** isEmpty
	* returns true if message do not contain any submessages
	**/	
	bool SmartMessage::isEmpty(){
		return (content==(byte*)0)||size()==_sz_head;
	};

	/** Empty
	* Remove all potential submessages
	**/	
	void SmartMessage::Empty(){
		//frees actual content
		free(content);
		content=0;
	};

	/** setContent
	*	Set the content of the message without trying to free previous buffer value
	**/	
	void SmartMessage::setContent(byte* msg){
		//set new content
		content=msg;	
	};

	/** fromArray
	*	regenerate message from a byte array
	*   Serialization function
	**/
	void SmartMessage::fromArray(byte* msg){
		Empty();
		int ln;
		bytes2Int(msg,&ln);
		content=(byte*)malloc(ln+_sz_head);
		memcpy(content,msg,ln+_sz_head);	
	};

	/** toArray
	*	returns a byte array representing the message content (without header)
	*   (De)Serialization function
	**/
	byte* SmartMessage::toArray(){
		byte* result=(byte*)malloc(size());
		memcpy(result,content,size());
		return result;
	};

	/** getArray
	*	returns a byte array representing the message content (including header)
	**/
	byte* SmartMessage::getArray(){
		return content;
	};

	// x86/64 only members
	#ifdef __ARCH_X86
	char* SmartMessage::toString()
	{
		static char infos[1024];

		sprintf(infos,"SmartMessage description:\nNb sub:%d\nSize:%d",count(),size());

		return infos;
	};
	#endif

	/** getBytes
	*	returns content of a byte array type submessage at _index_
	**/
	byte* SmartMessage::getBytes(int index,short* plength)
	{
		int_32 riidx=getElmIndex(index);
		byte* value;
		if(riidx>0)
		{
			bytes2Short(&content[riidx-_sz_sub_head_complete],plength);
			//ln-4+1
			value=(byte*)malloc(*plength);
			
			for(int t=0;t<*plength;t++)
			{
				value[t]=content[riidx+t];
			}
		}
		return value;

	};

	/** addBytes
	* Add data to a message
	**/
	void SmartMessage::addBytes(byte* value, short plength)
	{
		// position at the end of msg
		int_32 size=this->size();

		
		// increase size
		// n=4(ssize) + 1(tpe), ln(data)
		content=(byte*)realloc(content,size+_sz_sub_head_complete+plength);

		// write subsize + ? TODO : remove desc size (4)
		short2Bytes(&content[size],plength);
		// write type flag
		content[size+_sz_sub_head]=(byte)BDTBytes;
		// write value
		for(int t=0;t<plength;t++)
		{
			content[size+_sz_sub_head_complete+t]=value[t];
		}
		// update msg size flag
		// size+4+ln==size+_sz_sub_head_complete+ln-4
		setSize((size-_sz_head)+_sz_sub_head_complete+plength);
	};

	/** getString
	*	returns content of a string type submessage at _index_
	* 	add a 0 terminating the buffer
	**/
	char* SmartMessage::getString(int index){
		int_32 riidx=getElmIndex(index);
		char* value;
		short ln;
		if(riidx>0)
		{
			bytes2Short(&content[riidx-_sz_sub_head_complete],&ln);
			//ln-4+1
			value=(char*)malloc(ln+1);
			
			for(int t=0;t<ln;t++)
			{
				value[t]=content[riidx+t];
			}
			value[ln]=0;
		}
		return value;
	};

	/** addString
	* Add data to a message
	**/	
	void SmartMessage::addString(char* pstr){
		int_32 size=this->size();
		int ln=strlen(pstr);
		
		// increase size
		// 12=4*ssize, 4*tpe, ln*data
		content=(byte*)realloc(content,size+_sz_sub_head_complete+ln);
		
		// write subsize
		int2Bytes(&content[size],ln);
		// write type flag
		content[size+_sz_sub_head]=(byte)BDTString;
		// write value
		for(int t=0;t<ln;t++)
		{
			content[size+_sz_sub_head_complete+t]=pstr[t];
		}
		// update msg size flag
		setSize((size-_sz_head)+_sz_sub_head_complete+ln);
	};

	/** getShort
	*	returns content of a short type submessage at _index_
	**/	
	short SmartMessage::getShort(int index){
		short value;
		int_32 riidx=getElmIndex(index);
		bytes2Short(&content[riidx],&value);
		return value;
	};

	/** addShort
	* Add data to a message
	**/	
	void SmartMessage::addShort(short value){
	
		int_32 size=this->size();
		
		// increase size
		content=(byte*)realloc(content,size+_sz_sub_head_complete+sizeof(short));
		
		// write subsize
		short2Bytes(&content[size],(short)sizeof(short));
		// write type flag
		content[size+_sz_sub_head]=(byte)BDTShort;
		// write value
		short2Bytes(&content[size+_sz_sub_head_complete],value);
		// update msg size flag
		setSize((size-_sz_head)+_sz_sub_head_complete+sizeof(short));
		
	};


	/** getInt
	*	returns content of an int type submessage at _index_
	**/	
	int SmartMessage::getInt(int index){
		int value;
		int_32 riidx=getElmIndex(index);
		bytes2Int(&content[riidx],&value);
		return value;
	};

	/** addInt
	* Add data to a message
	**/	
	void SmartMessage::addInt(int value){
	
		int_32 size=this->size();
		
		// increase size
		// 12=4*ssize, 4*tpe, 4*data
		content=(byte*)realloc(content,size+_sz_sub_head_complete+sizeof(int));
		
		// write subsize
		short2Bytes(&content[size],(short)sizeof(int));
		// write type flag
		content[size+_sz_sub_head]=(byte)BDTInt;
		// write value
		int2Bytes(&content[size+_sz_sub_head_complete],value);
		// update msg size flag
		setSize((size-_sz_head)+_sz_sub_head_complete+sizeof(int));
		
	};


	/** getLong
	*	returns content of a long type submessage at _index_
	**/
	long SmartMessage::getLong(int index){
		long value;
		int_32 riidx=getElmIndex(index);
		bytes2Long(&content[riidx],&value);
		return value;
	};

	/** addLong
	* Add data to a message
	**/	
	void SmartMessage::addLong(long value){
	
		int_32 size=this->size();
		
		// increase size
		// 16=4*ssize, 4*tpe, 8*data
		content=(byte*)realloc(content,size+_sz_sub_head_complete+sizeof(long));
		
		// write subsize
		int2Bytes(&content[size],sizeof(long));
		// write type flag
		content[size+_sz_sub_head]=(byte)BDTLong;
		// write value
		long2Bytes(&content[size+_sz_sub_head_complete],value);
		// update msg size flag
		setSize((size-_sz_head)+_sz_sub_head_complete+sizeof(long));
		
	};

	/** getFloat
	*	returns content of a double type submessage at _index_
	**/
	float SmartMessage::getFloat(int index){
		float value;
		int_32 riidx=getElmIndex(index);
		bytes2Float(&content[riidx],&value);
		return value;
	};

	/** addFloat
	* Add data to a message
	**/	
	void SmartMessage::addFloat(float value){
	
		int_32 size=this->size();
		
		// increase size
		// 16=4*ssize, 4*tpe, 8*data
		content=(byte*)realloc(content,size+_sz_sub_head_complete+sizeof(float));
		
		// write subsize
		int2Bytes(&content[size],sizeof(float));
		// write type flag
		content[size+_sz_sub_head]=(byte)BDTFloat;
		// write value
		float2Bytes(&content[size+_sz_sub_head_complete],value);
		// update msg size flag
		setSize((size-_sz_head)+_sz_sub_head_complete+sizeof(float));
		
	};

	/** getDouble
	*	returns content of a double type submessage at _index_
	**/
	double SmartMessage::getDouble(int index){
		double value;
		int_32 riidx=getElmIndex(index);
		bytes2Double(&content[riidx],&value);
		return value;
	};

	/** addDouble
	* Add data to a message
	**/	
	void SmartMessage::addDouble(double value){
	
		int_32 size=this->size();
		
		// increase size
		// 16=4*ssize, 4*tpe, 8*data
		content=(byte*)realloc(content,size+_sz_sub_head_complete+sizeof(double));
		
		// write subsize
		int2Bytes(&content[size],sizeof(double));
		// write type flag
		content[size+_sz_sub_head]=(byte)BDTDouble;
		// write value
		double2Bytes(&content[size+_sz_sub_head_complete],value);
		// update msg size flag
		setSize((size-_sz_head)+_sz_sub_head_complete+sizeof(double));
		
	};

	/** Bool
	*	x86 : 1 byte
	*	AVR : 1 byte
	**/
	bool SmartMessage::getBool(int index){
		return (bool)getByte(index);
	};

	void SmartMessage::addBool(bool value){
		addByte((byte)value);
	};

	/** Byte
	*	x86 : 1 byte
	*	AVR : 1 byte
	**/
	byte SmartMessage::getByte(int index){
		byte value;
		int_32 riidx=getElmIndex(index);
		value=content[riidx];
		return content[riidx];
	};

	void SmartMessage::addByte(byte value){

		int_32 size=this->size();
		int szbyte=sizeof(byte);
		// increase size
		// 12=4*ssize, 4*tpe, 4*data
		content=(byte*)realloc(content,size+_sz_sub_head_complete+szbyte);
		
		// write subsize
		content[size]=szbyte;
		// write type flag
		content[size+_sz_sub_head]=(byte)BDTByte;
		// write value
		content[size+_sz_sub_head_complete]=value;
		// update msg size flag
		setSize((size-_sz_head)+_sz_sub_head_complete+szbyte);
	};

	/** Returns the start position of the data held at _index_
	*
	* index = -1 to get elms count (total nb of indice)
	**/
	int_32 SmartMessage::getElmIndex(int index){
		int t=0;
		int_32 r=0;
		int_32 size=this->size();
		short subsize=1;
		
		
		for(r=_sz_head;r<size;r+=subsize)
		{
			
			if(t==index)
			{
				return r+_sz_sub_head_complete;	
			}
			//jump sub size (int)
			bytes2Short(&content[r],&subsize);
			//sz lbl itself
			subsize+=_sz_sub_head_complete;
			t++;
			
		}
		if(index==-1)
		{
			return t;
		}
		return -1;
	};

	void SmartMessage::setSize(int_32 sz)
	{
		#ifdef __ARCH_AVR
		// sizeof(long)==_sz_head==4
		long2Bytes(content,sz);
		#else
		// sizeof(int)==_sz_head==4
		int2Bytes(content,sz);
		#endif
		
	};

	/** Attach a virtual byte array of size to the message
	*
	**/
	void SmartMessage::attach(int plength)
	{
		// position at the end of msg
		int_32 size=this->size();

		
		// increase size
		// n=4(ssize) + 1(tpe), ln(data)
		content=(byte*)realloc(content,size+_sz_sub_head_complete);

		// write subsize + ? TODO : remove desc size (4)
		short2Bytes(&content[size],plength);
		// write type flag
		content[size+_sz_sub_head]=(byte)BDTBytes;
		// write value
		// no, virtual ...
		// update msg size flag
		// size+4+ln==size+_sz_sub_head_complete+ln-4
		setSize((size-_sz_head)+_sz_sub_head_complete+plength);
	};

	/** short2Bytes
	* 	convert from a int to a buffer of bytes
	**/
	bool SmartMessage::short2Bytes(byte* buf, short value)
	{
		memcpy(buf,&value,sizeof(short));	
		return true;
	};

	/** bytes2Short
	* 	convert from byte array to int value
	**/
	bool SmartMessage::bytes2Short(byte* buf, short* value)
	{
		memcpy(value,buf,sizeof(short));
		return true;
	};

	/** int2Bytes
	* 	convert from a int to a buffer of bytes
	**/
	bool SmartMessage::int2Bytes(byte* buf, int value)
	{
		memcpy(buf,&value,sizeof(int));	
		return true;
	};

	/** bytes2Int
	* 	convert from byte array to int value
	**/
	bool SmartMessage::bytes2Int(byte* buf, int* value)
	{

		memcpy(value,buf,sizeof(int));
		return true;
	};

	/** long2Bytes
	* 	convert from a long to a buffer of bytes
	**/
	bool SmartMessage::long2Bytes(byte* buf, long value){
		

		memcpy(buf,&value,sizeof(long));


		return true;
	};

	/** bytes2Long
	* 	convert from byte array to long value
	**/
	bool SmartMessage::bytes2Long(byte* buf, long* value){
		
		memcpy(value,buf,sizeof(long));

		return true;
	};

	/** float2Bytes
	* 	convert from a float to a buffer of bytes
	**/
	bool SmartMessage::float2Bytes(byte* buf, float value){
		
		memcpy(buf,&value,sizeof(float));

		return true;
	};

	/** bytes2Float
	* 	convert from byte array to float value
	**/
	bool SmartMessage::bytes2Float(byte* buf, float* value){
		
		memcpy(value,buf,sizeof(float));

		return true;
	};

	/** double2Bytes
	* 	convert from a double to a buffer of bytes
	**/
	bool SmartMessage::double2Bytes(byte* buf, double value){
		
		memcpy(buf,&value,sizeof(double));

		return true;
	};

	/** bytes2Double
	* 	convert from byte array to double value
	**/
	bool SmartMessage::bytes2Double(byte* buf, double* value){
		
		memcpy(value,buf,sizeof(double));

		return true;
	};