#include <memory.h>

/*
====================================

   class LArray - dynamyc array

====================================
*/


template<class T>
class LArray
{
	T		*data;
	int		size;

public:
				LArray();
				LArray( const int s );
				LArray( const LArray& l );
				~LArray();

	const T&	operator [] ( const int i )const;
	T&			operator [] ( const int i );
	LArray&		operator =  ( const LArray& l );
	T*			Data()const;
	void		Clear();


	void SetSize( const int s, bool keep = true );
	int Size()const;
};


template<class T>
LArray<T>::LArray(){
	size = 0;
}


template<class T>
LArray<T>::LArray( const int s ){
	size = s;
	data = new T[ s + 1 ];
	memset( data, 0x0000, sizeof( T ) * ( s + 1 ) );
}


template<class T>
LArray<T>::LArray( const  LArray& l ){
	size = l.Size();
	data = new T[ size + 1 ];
	memset( data, 0x0000, sizeof( T ) * (s+1) );
	for( int i = 0; i < size; i++ ){
		data[i] = l[i];
	}
}


template<class T>
LArray<T>::~LArray(){
	if( size > 0 )
		delete[] data;
}

template<class T>
void LArray<T>::Clear(){
	delete[] data;
	size = 0;
}

template<class T>
inline int LArray<T>::Size()const{
	return size;
}


template<class T>
inline T& LArray<T>::operator [] ( const int i ){
	if( i >= size )this->SetSize( size + 256, true );
	return data[i];
}


template<class T>
inline const T& LArray<T>::operator [] ( const int i )const{
	
	if( i >= size ) return data[ size + 1 ];
	return data[i];
}

template<class T>
inline LArray<T>& LArray<T>::operator = ( const LArray& l ){
	SetSize( l.Size(), false );
	for( int i = 0; i < size ; i++ ){
		data[i] = l[i];
	}
	return *this;
}


template<class T>
inline T* LArray<T>::Data()const{
	return data;
}


template<class T>
void LArray<T>::SetSize( const int s, bool keep = true )
{
	if( s == 0 ){
		delete[] data;
		size = s;
	}
	else
	{
		if( s > 0 )
		{
			if( size==0 ){
				data = new T[ s + 1 ];
				//memset( data, 0x0000, sizeof( T ) * ( s + 1 ) );
			}
			else
			{
				if( keep )
				{
					T *temp = new T[ s + 1 ];
					memset( temp, 0x0000, sizeof( T ) * (s+1) );
					int ss = size<s?size:s;
					for( int i = 0; i < ss ; i++ ){
						temp[i] = data[i];
					}
					T *toDie = data;
					data = temp;
					delete[] toDie;
				}
				else
				{
					delete[] data;
					data = new T[ s+1 ];
					memset( data, 0x0000, sizeof( T ) * ( s + 1 ) );
				}
			}

			size = s;
		}
	}

}


