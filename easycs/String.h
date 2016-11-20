
#include <string.h>
#include <ios>


#define BASESTRINGSIZE 32


class String
{
public:
					String();
					String( const char c );
					String( const char * val );
					String( const String& str );
					~String();

					operator const char *() const;
					operator const char *();
 
	char&			operator [] ( int index );
	char			operator [] ( int index )const;

	String&			operator = ( const char val );
	String&			operator = ( const char* val );
	String&			operator = ( const String& str );

	String&			operator += ( const char val );
	String&			operator += ( const char* val );
	String&			operator += ( const String& str );

	friend String	operator + ( const String& a, const String& b );
	friend String	operator + ( const String& a, const char* b );
	friend String	operator + ( const char* a, const String& b );
	friend String	operator + ( const char a, const String& b );
	friend String	operator + ( const String& a, const char b );

	friend bool		operator == ( const String& a, const String& b );
	friend bool		operator == ( const String& a, const char* b );
	friend bool		operator == ( const char* a, const String& b );

	friend bool		operator != ( const String& a, const String& b );
	friend bool		operator != ( const String& a, const char* b );
	friend bool		operator != ( const char* a, const String& b );

	static String   ToString( const int a );
	static String	ToString( const float a, const int  numOfDec );

	void			Append( const char val );
	void			Append( const char* val );
	void			Append( const String& str );

	bool			Cmp( const char* val )const;
	static bool		Cmp( const char* val1, const char* val2 );

	void			ReAllocate( const int size, const bool keep = false );
	bool			IsEmpty()const;
	int				Length()const;
	int				Size()const;
	char*			c_str()const;
	void			Clear();
	void			Free();

private:
	char*	data;
	char	baseBuffer[ BASESTRINGSIZE ];
	int		length;
	int		allocated;
	void	Init();

};



inline void String::Init(){
	length = 0;
	allocated = BASESTRINGSIZE;
	data = baseBuffer;
	data[0] = '\0';
	memset( baseBuffer, 0, sizeof( baseBuffer ) );
}

inline void String::Free(){
	if( data && data != baseBuffer ){
		delete[] data;
		data = baseBuffer;
	} 
}

inline void String::Clear(){
	if( data && data != baseBuffer ){
		memset( data, 0x0000, allocated );
		//strcpy_s( data, allocated, "" );
	} 
}

inline String::String(){
	Init();
}


inline String::String( const char c ){
	Init();
	ReAllocate( 2 );
	data[0] = c;
	data[1] = '\0';
	length = 1;
}


inline String::String( const char* val ){
	Init();
	if( val ){
		int l = strlen( val );
		ReAllocate( l + 1 );
		strcpy_s( data, l + 1, val );
		length = l;
	}
}

inline String::String( const String& str ){
	Init();
	int l = str.length;
	ReAllocate( l + 1 );
	strcpy_s( data, l + 1, str.data );
	length = l;
}

inline String::~String(){
	Free();
}

inline String::operator const char *() const{
	return data;
}

inline String::operator const char *(){
	return data;
}

inline char& String::operator [] ( int index ){
	return data[ index ];
}


inline char String::operator [] ( int index )const{
	return data[ index ];
}

inline String& String::operator = ( const String& str ){
	int l = str.Length();
	ReAllocate( l + 1 );
	strcpy_s( data, l + 1, str.data );
	data[l] = '\0';
	length = l;
	return *this;
}

inline String& String::operator += ( const char val ){
	Append( val );
	return *this;
}

inline String& String::operator += ( const char* val ){
	Append( val );
	return *this;
}

inline String& String::operator += ( const String& str ){
	Append( str );
	return *this;
}

inline String operator + ( const String& a, const String& b ){
	String result( a );
	result.Append( b );
	return result;
}

inline String operator + ( const String& a, const char* b ){
	String result( a );
	result.Append( b );
	return result;
}

inline String operator + ( const char* a, const String& b ){
	String result( a );
	result.Append( b );
	return result;

}

inline String operator + ( const char a, const String& b ){
	String result( a );
	result.Append( b );
	return result;
}

inline String operator + ( const String& a, const char b ){
	String result( a );
	result.Append( b );
	return result;
}

inline bool operator == ( const String& a, const String& b ){
	return( !String::Cmp( a.data, b.data ) );
}

inline bool operator == ( const String& a, const char* b ){
	return( !String::Cmp( a.data, b ) );
}

inline bool operator == ( const char* a, const String& b ){
	return( !String::Cmp( a, b.data ) );
}

inline bool operator != ( const String& a, const String& b ){
	return( String::Cmp( a.data, b.data ) );
}

inline bool operator != ( const String& a, const char* b ){
	return( String::Cmp( a.data, b ) );
}

inline bool operator != ( const char* a, const String& b ){
	return( String::Cmp( a, b.data ) );
}

inline bool String::Cmp( const char *s )const{
	return Cmp( data, s );
} 

inline bool String::IsEmpty()const{
	return length>0?false:true;
}

inline int	String::Length()const{
	return length;
}

inline int	String::Size()const{
	return allocated;
}

inline char* String::c_str()const{
	return data;
}

