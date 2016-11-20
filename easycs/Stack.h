#ifndef __EASICS_STACK_H__
#define __EASYCS_STACK_H__


/*
=================================

	Class Stack

=================================
*/


template<class T>
class Stack
{
	T *data;
	int size;
	mutable int top;
	int count;

public:
	Stack();
	Stack( const int s );
	~Stack();

	void SetSize( const int s, bool keep = true );
	bool Empty()const;
	void Push(const T& object );
	T Pop()const;
	T Keep()const;
	int Count()const;
};


template<class T>
inline Stack<T>::Stack(){
	size = 0;
	top = 0;
}


template<class T>
inline Stack<T>::Stack( const int s ){
	SetSize( s, false );
	top = 0;
}


template<class T>
inline Stack<T>::~Stack(){
	if( size )
		delete[] data;
}


template<class T>
void Stack<T>::SetSize( const int s, bool keep = true )
{
	if( size == 0 ){
		data = new T[ 256 ];
		size = s;
		return;
	}

	if( s==0 )
	{
		if( size > 0 )
		{
			delete[] data;
			size = 0;
			return;
		}
	}

	if( !keep )
	{
		if( size > 0 )
		{
			delete[] data;
		}
		if( s > 0 )
		{
			size = s;
			data = new T[ s + 1 ];
			top = 0;
		}
	}
	else
	{
		T *temp = new T[ s + 1 ];
		int ss = size<s?size:s;
		for( int i = 1; i <= ss ; i++ ){
			temp[i] = data[i];
		}
		T *toDie = data;
		data = temp;
		delete[] toDie;
		size = s;
		if( top>size )
			top = size;
	}
}



template<class T>
inline void Stack<T>::Push( const T& object )
{
	if( top >= size )this->SetSize( size + 256, true );
	data[ ++top ] = object;
}


template<class T>
inline T Stack<T>::Pop()const
{
	if( top )
		return data[ top-- ];
	return data[0];
}


template<class T>
inline T Stack<T>::Keep()const
{
	if( top )
		return data[ top ];
	return data[0];
}



template<class T>
inline bool Stack<T>::Empty()const{
	return top==0;
}


template<class T>
inline int Stack<T>::Count()const{
	return top;
}


#endif