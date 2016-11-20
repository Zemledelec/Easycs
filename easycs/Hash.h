#ifndef __HASH_H__
#define __HASH_H__

#include <string.h>


/*
=========================================

	Chains method hash table class 

=========================================
*/

#define	DEFAULTHASHSIZE	256


template<class T>
class Hash
{
	typedef struct hashnode{
		T			data;
		char		*string;
		hashnode	*next;
	} *phashnode;

	int			size;
	hashnode	**table;
	int			count;

	void	InitTable();
	// Линейное рехэширование(поиск эл-та в списке)
	hashnode*	Search( const char *str, const int hi )const;
	int			HashIndex( const char *str )const;

public:		
		Hash();
		~Hash();

		void	Set( const char* key, const T& v );
		bool	Get( const char* key, T **v = 0x0000 )const;
		bool	Remove( const char* key );
		void	Clear();
		int		Count()const;
};


template<class T>
Hash<T>::Hash()
{
	count = 0;
	size = DEFAULTHASHSIZE;
	InitTable();
}

template<class T>
Hash<T>::~Hash()
{
	count = 0;
	Clear();
}


template<class T>
inline void Hash<T>::InitTable(){
	if(size)
	{
		table = new phashnode[ size ];
		for( int i = 0; i < size; i++ )
			table[i] = 0x0000;
	}
}




template<class T>
void Hash<T>::Clear()
{
	for( int i=0; i<size; i++ )
	{
		hashnode *toDie;
		hashnode *n=table[i];
		while(n)
		{
			toDie = n;
			n = n->next;
			delete toDie;
		}
	}
	delete[] table;
}


template<class T>
inline int Hash<T>::HashIndex( const char *str )const
{
	int hi = 0;
	char *pp = const_cast<char*>(str);

	while( *pp ){
		hi <<= 1;
		hi ^= *pp++;
	}
	if( hi<0 ) hi = - hi;
	hi %= size;
	return hi;
}



template <class T>
inline typename Hash<T>::hashnode* Hash<T>::Search( const char* str, const int hi )const{
	for( hashnode *n=table[hi]; n; n = n->next )
		if( strcmp( str, n->string )==0 )
			return n;
	return NULL;
}


template<class T>
void Hash<T>::Set( const char* str, const T& v )
{
	int hi = HashIndex( str );
	hashnode *nn;
	if( !(nn=Search( str, hi )) )
	{
		nn = new hashnode;
		nn->string = new char[ strlen( str ) + 1 ];
		strcpy_s( nn->string, strlen( str ) + 1, str );
		nn->next = table[hi];
		table[hi] = nn;
		count++;
	}
	nn->data = v;
}


template<class T>
bool Hash<T>::Get( const char* str, T **v = 0x0000 )const
{
	int hi = HashIndex( str );
	hashnode *nn;
	if( !(nn=Search( str, hi )) )
	{
		v = NULL;
		return false;
	}
	else{
		if( v != 0x0000 )
			*v = &nn->data;
	}

	return true;
}



template<class T>
bool Hash<T>::Remove( const char* key )
{
	hashnode *prev	= table[hi];
	hashnode *first = table[hi];
	int hi = HashIndex( key );
	for( hashnode *n = table[hi]; n; prev = n, n = n->next )
	{
		if( !strcmp( key, n->string ) )
		{
			prev->next = n->next;
			if( n == first )
				table[hi] = first->next;
			delete[] n->string;
			delete n;
			count--;
			return true;
		}
	}

	return false;
}


template<class T>
inline int Hash<T>::Count()const{
	return count;
}




#endif