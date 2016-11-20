#include "String.h"



void String::ReAllocate( const int size, const bool keep )
{
	allocated = size;
	char* newbuffer = new char[ allocated + 1 ];
	memset( newbuffer, 0, allocated + 1 );

	if ( keep && data ) {
		data[ length ] = '\0';
		strcpy_s( newbuffer, allocated + 1, data );
	}

	if( data && data != baseBuffer ){
		delete[] data;
	}

	data = newbuffer; 
}


bool String::Cmp( const char *s1, const char *s2 )
{
	int c1, c2, d;
	do{
		c1 = *s1++;
		c2 = *s2++;

		d = c1 - c2;
		if( d )
			return true;
	}while( c1 );
	return false;
} 


String& String::operator = ( const char* val )
{
	if ( !val ){
		ReAllocate( 1 );
		data[ 0 ] = '\0';
		length = 0;
		return *this;
	}

	if( val == data )
		return *this;

	if( val >= data && val <= data + length ){
		int diff = val - data;

		int i;
		for( i = 0; val[ i ]; i++ )
			data[ i ] = val[ i ];
		
		data[ i ] = '\0';
		length -= diff;
		return *this;
	}

	int l = strlen( val );
	ReAllocate( l + 1 );
	strcpy_s( data, l + 1, val );
	length = l;
	data[ length ] = '\0';
	return *this;
}


void String::Append( const char val ){
	ReAllocate( length + 2, true );
	data[ length ] = val;
	length++;
	data[ length ] = '\0';
}


void String::Append( const char* val ){
	if( val ){
		int l = strlen( val );
		int newlength = length + l;
		ReAllocate( newlength + 1, true );
		for( int i = 0; i < l; i++ ) {
			data[ length + i ] = val[ i ];
		}
		length = newlength;
		data[ length ] = '\0';
	}
}


void String::Append( const String& str ){
	int newlength = str.length + length;
	ReAllocate( newlength + 1, true );
	for( int i = 0; i < str.length; i++ ) {
		data[ length + i ] = str.data[i];
	}
	length = newlength;
	data[ length ] = '\0';
}

String String::ToString( const int a ){
	String result;
	_itoa_s( a, result.baseBuffer, BASESTRINGSIZE, 10 );
	result.length = strlen( result.baseBuffer );
	return result;
}


String String::ToString( const float a, const int  numOfDec ){
	String result;
	int d,s;
	_fcvt_s( result.baseBuffer, BASESTRINGSIZE, a, numOfDec, &d, &s );
	return result;
}
