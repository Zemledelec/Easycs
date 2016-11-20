#include "ParserShared.h"
#include <ios>			// _msize



ARGCLASS ParserShared::STR2ARGCLASS( const char* type )
{
	if( !strcmp( type, "int"	) ) return ARGC_INT;
	if( !strcmp( type, "float"	) ) return ARGC_FLOAT;
	if( !strcmp( type, "bool"	) ) return ARGC_BOOL;
	if( !strcmp( type, "string" ) ) return ARGC_STRING;
	if( !strcmp( type, "void"   ) ) return ARGC_VOID;
	return ARGC_VOID;
}


bool ParserShared::TOKENSTR( const token_s& t, const int count, const TOKENCLASS tc,  ... )
{
	if( t.tokClass != tc )
		return false;

	// считаем кол-во переданных параметров
	va_list argptr;
	/*va_start( argptr, tc );
	char *ps;

	int count=0;
	while( ps = va_arg( argptr, char* ) )
	{
		count++;
	}*/
	// просматриваем переданные параметры
	va_start( argptr, tc );	
	for( int i=0; i<count; i++ )
	{
		if( !strcmp( t.str, va_arg( argptr, char* ) ) ){
			va_end( argptr );
			return true;
		}
	}

	va_end( argptr );
	return false;
//	return ( count == 1 ? true : false );
}

bool  ParserShared::STRSTRSTR( const char* s,  const int count, ... ){
	// считаем кол-во переданных параметров
	va_list argptr;
	/*va_start( argptr, tc );
	char *ps;

	int count=0;
	while( ps = va_arg( argptr, char* ) )
	{
		count++;
	}*/
	// просматриваем переданные параметры
	va_start( argptr, count );	
	for( int i=0; i<count; i++ )
	{
		if( !strcmp( s, va_arg( argptr, char* ) ) ){
			va_end( argptr );
			return true;
		}
	}

	va_end( argptr );
	return false;
//	return ( count == 1 ? true : false );
}




arg_t ParserShared::TOKEN2ARG( const token_s& t ){
	switch( t.tokClass )
	{
	case TC_CONSTANT_INT:	return arg_t( ARGC_INT,		t.cInt		);
	case TC_CONSTANT_FLOAT:	return arg_t( ARGC_FLOAT,	t.cFloat	);
	case TC_STRING:			return arg_t( ARGC_STRING,	t.str		);
	default:				return arg_t( ARGC_INT, 0 );
	}
}



//cfptr ParserShared::TOKEN2OP( const token_s& t )
//{	
//	return STR2OP( t.str );
//}

enum{
	PLUS=0,
	MINUS,
	STAR,
	SLASH,
	PERCENT,
	AND,
	OR,
	XOR,
	ASSIGN,
	ASSIGNASSIGN,
	OROR,
	ANDAND,
	MORE,    
	MOREASSIGN,
	LESS,
	LESSASSIGN,
	EXCLAMASSIGN,
};

enum{
	UNARYPLUS=0,
	UNARYMINUS,
	UNARYEXCLAM
};

enum{
	T_INT=0,
	T_FLOAT,
	T_STRING,
	T_BOOL
};



static const int narrowBaseTypeTable[4][4] = 
{
	//                 T_INT    T_FLOAT    T_STRING    T_BOOL
	/*T_INT    */                   0,                 5, NOCOMPATIBLE_TYPES, -2,
	/*T_FLOAT  */                  -5,                 0, NOCOMPATIBLE_TYPES, -10,     
	/*T_STRING */   NOCOMPATIBLE_TYPES, NOCOMPATIBLE_TYPES,                 0, NOCOMPATIBLE_TYPES,       
	/*T_BOOL   */                   2,                10, NOCOMPATIBLE_TYPES, 0
};

int ParserShared::GetNarrowBaseType( const arg_t& arg1, const arg_t& arg2 ){
	return narrowBaseTypeTable[ ArgT( arg1.argClass ) ][ ArgT( arg2.argClass ) ];
}



const int ParserShared::utMx[3][4] = 
{				/*T_INT*/    /*T_FLOAT*/  /*T_STRING*/ /*T_BOOL*/ 
/*UNARYPLUS*/	{ ARGC_INT,	 ARGC_FLOAT, ARGC_ERROR, ARGC_INT  },
/*UNARYMINUS*/	{ ARGC_INT,	 ARGC_FLOAT, ARGC_ERROR, ARGC_INT  },
/*UNARYEXCLAM*/	{ ARGC_BOOL,  ARGC_BOOL,  ARGC_BOOL, ARGC_BOOL }
};

const int ParserShared::btMx[17][4][4] = 
{				 /*T_INT*/      /*T_FLOAT*/  /*T_STRING*/     /*T_BOOL*/ 
/*PLUS*/		{
	/*T_INT		*/ ARGC_INT,       ARGC_FLOAT,	    ARGC_ERROR, ARGC_INT, 
	/*T_FLOAT	*/ ARGC_FLOAT,     ARGC_FLOAT,	    ARGC_ERROR, ARGC_FLOAT,
	/*T_STRING	*/ ARGC_ERROR,     ARGC_ERROR,	   ARGC_STRING, ARGC_ERROR,
	/*T_BOOL	*/ ARGC_INT,	   ARGC_FLOAT,	    ARGC_ERROR, ARGC_INT
},
/*MINUS*/		{  
	/*T_INT		*/ ARGC_INT,     ARGC_FLOAT,   ARGC_ERROR, ARGC_INT,
	/*T_FLOAT	*/ ARGC_FLOAT,   ARGC_FLOAT,   ARGC_ERROR, ARGC_FLOAT,
	/*T_STRING	*/ ARGC_ERROR,	 ARGC_ERROR,   ARGC_ERROR, ARGC_ERROR,
	/*T_BOOL	*/ ARGC_INT,	 ARGC_FLOAT,   ARGC_ERROR, ARGC_INT
},
/*STAR*/		{
	/*T_INT		*/ ARGC_INT,	 ARGC_FLOAT,   ARGC_ERROR, ARGC_INT,
	/*T_FLOAT	*/ ARGC_FLOAT,	 ARGC_FLOAT,   ARGC_ERROR, ARGC_FLOAT,
	/*T_STRING	*/ ARGC_ERROR,	 ARGC_ERROR,   ARGC_ERROR, ARGC_ERROR,
	/*T_BOOL	*/ ARGC_INT,	 ARGC_FLOAT,   ARGC_ERROR, ARGC_INT
},
/*SLASH*/		{
	/*T_INT		*/ ARGC_FLOAT,   ARGC_FLOAT,	ARGC_ERROR, ARGC_FLOAT,
	/*T_FLOAT	*/ ARGC_FLOAT,   ARGC_FLOAT,	ARGC_ERROR, ARGC_FLOAT,
	/*T_STRING	*/ ARGC_ERROR,	 ARGC_ERROR,    ARGC_ERROR, ARGC_ERROR,
	/*T_BOOL	*/ ARGC_FLOAT,	 ARGC_FLOAT,    ARGC_ERROR, ARGC_FLOAT
},
/*PERCENT*/		{
	/*T_INT		*/ ARGC_INT,	 ARGC_ERROR,  ARGC_ERROR, ARGC_INT,
	/*T_FLOAT	*/ ARGC_ERROR,	 ARGC_ERROR,  ARGC_ERROR, ARGC_ERROR,
	/*T_STRING	*/ ARGC_ERROR,	 ARGC_ERROR,  ARGC_ERROR, ARGC_ERROR,	
	/*T_BOOL	*/ ARGC_INT,	 ARGC_ERROR,  ARGC_ERROR, ARGC_INT
},
/*AND*/			{
	/*T_INT		*/ ARGC_INT,	ARGC_ERROR,	  ARGC_ERROR, ARGC_INT,
	/*T_FLOAT	*/ ARGC_ERROR,	ARGC_ERROR,	  ARGC_ERROR, ARGC_ERROR,
	/*T_STRING	*/ ARGC_ERROR,	ARGC_ERROR,	  ARGC_ERROR, ARGC_ERROR,
	/*T_BOOL	*/ ARGC_INT,	ARGC_ERROR,	  ARGC_ERROR, ARGC_BOOL
},
/*OR*/			{
	/*T_INT		*/ ARGC_INT,	ARGC_ERROR,	ARGC_ERROR, ARGC_INT,
	/*T_FLOAT	*/ ARGC_ERROR,	ARGC_ERROR,	ARGC_ERROR, ARGC_ERROR,
	/*T_STRING	*/ ARGC_ERROR,	ARGC_ERROR,	ARGC_ERROR, ARGC_ERROR,
	/*T_BOOL	*/ ARGC_INT,	ARGC_ERROR,	ARGC_ERROR, ARGC_BOOL
},
/*XOR*/			{
	/*T_INT		*/ ARGC_INT,	ARGC_ERROR,	ARGC_ERROR,  ARGC_INT,
	/*T_FLOAT	*/ ARGC_ERROR,	ARGC_ERROR,	ARGC_ERROR,  ARGC_ERROR,
	/*T_STRING	*/ ARGC_ERROR,	ARGC_ERROR,	ARGC_ERROR,  ARGC_ERROR,
	/*T_BOOL	*/ ARGC_INT,	ARGC_ERROR,	ARGC_ERROR,  ARGC_BOOL
},
/*ASSIGN*/		{
	/*T_INT		*/ ARGC_INT,	  ARGC_INT,	   ARGC_ERROR,  ARGC_INT,
	/*T_FLOAT	*/ ARGC_FLOAT,	ARGC_FLOAT,	   ARGC_ERROR,  ARGC_FLOAT,
	/*T_STRING	*/ ARGC_ERROR,	ARGC_ERROR,   ARGC_STRING,	ARGC_ERROR, 		
	/*T_BOOL	*/ ARGC_BOOL,	 ARGC_BOOL,	    ARGC_BOOL,	ARGC_BOOL
},
/*ASSIGNASSIGN*/{
	/*T_INT		*/ ARGC_BOOL,    ARGC_BOOL,	   ARGC_BOOL, ARGC_BOOL,
	/*T_FLOAT	*/ ARGC_BOOL,	 ARGC_BOOL,	   ARGC_BOOL, ARGC_BOOL,
	/*T_STRING	*/ ARGC_BOOL,	 ARGC_BOOL,	   ARGC_BOOL, ARGC_BOOL,
	/*T_BOOL	*/ ARGC_BOOL,    ARGC_BOOL,    ARGC_BOOL, ARGC_BOOL
},
/*OROR*/		{
	/*T_INT		*/ ARGC_BOOL,	 ARGC_BOOL,    ARGC_BOOL, ARGC_BOOL,
	/*T_FLOAT	*/ ARGC_BOOL,	 ARGC_BOOL,    ARGC_BOOL, ARGC_BOOL,
	/*T_STRING	*/ ARGC_BOOL,	 ARGC_BOOL,    ARGC_BOOL, ARGC_BOOL,
	/*T_BOOL	*/ ARGC_BOOL,	 ARGC_BOOL,    ARGC_BOOL, ARGC_BOOL,
},
/*ANDAND*/		{
	/*T_INT		*/ ARGC_BOOL,	 ARGC_BOOL,    ARGC_BOOL, ARGC_BOOL,
	/*T_FLOAT	*/ ARGC_BOOL,	 ARGC_BOOL,    ARGC_BOOL, ARGC_BOOL,
	/*T_STRING	*/ ARGC_BOOL,	 ARGC_BOOL,    ARGC_BOOL, ARGC_BOOL,
	/*T_BOOL	*/ ARGC_BOOL,	 ARGC_BOOL,    ARGC_BOOL, ARGC_BOOL,
},
/*MORE*/		{
	/*T_INT		*/ ARGC_BOOL,	ARGC_BOOL,   ARGC_ERROR, ARGC_BOOL,
	/*T_FLOAT	*/ ARGC_BOOL,	ARGC_BOOL,   ARGC_ERROR, ARGC_BOOL,
	/*T_STRING	*/ ARGC_ERROR,	ARGC_ERROR,  ARGC_ERROR, ARGC_ERROR,
	/*T_BOOL	*/ ARGC_BOOL,	ARGC_BOOL,   ARGC_ERROR, ARGC_BOOL
},
/*MOREASSIGN*/	{
	/*T_INT		*/ ARGC_BOOL,	  ARGC_BOOL,  ARGC_ERROR, ARGC_BOOL,
	/*T_FLOAT	*/ ARGC_BOOL,	  ARGC_BOOL,  ARGC_ERROR, ARGC_BOOL,
	/*T_STRING	*/ ARGC_ERROR,	 ARGC_ERROR,  ARGC_ERROR, ARGC_ERROR,
	/*T_BOOL	*/ ARGC_BOOL,	  ARGC_BOOL,  ARGC_ERROR, ARGC_BOOL
},
/*LESS*/		{
	/*T_INT		*/ ARGC_BOOL,	  ARGC_BOOL,  ARGC_ERROR, ARGC_BOOL,
	/*T_FLOAT	*/ ARGC_BOOL,	  ARGC_BOOL,  ARGC_ERROR, ARGC_BOOL,
	/*T_STRING	*/ ARGC_ERROR,	 ARGC_ERROR,  ARGC_ERROR, ARGC_ERROR,
	/*T_BOOL	*/ ARGC_BOOL,	  ARGC_BOOL,  ARGC_ERROR, ARGC_BOOL
},
/*LESSASSIGN*/	{
	/*T_INT		*/ ARGC_BOOL,	  ARGC_BOOL,  ARGC_ERROR, ARGC_BOOL,
	/*T_FLOAT	*/ ARGC_BOOL,	  ARGC_BOOL,  ARGC_ERROR, ARGC_BOOL,
	/*T_STRING	*/ ARGC_ERROR,	 ARGC_ERROR,  ARGC_ERROR, ARGC_ERROR,
	/*T_BOOL	*/ ARGC_BOOL,	  ARGC_BOOL,  ARGC_ERROR, ARGC_BOOL
},
/*EXCLAMASSIGN*/{
	/*T_INT		*/ ARGC_BOOL,    ARGC_BOOL,	   ARGC_BOOL, ARGC_BOOL,
	/*T_FLOAT	*/ ARGC_BOOL,	 ARGC_BOOL,	   ARGC_BOOL, ARGC_BOOL,
	/*T_STRING	*/ ARGC_BOOL,	 ARGC_BOOL,	   ARGC_BOOL, ARGC_BOOL,
	/*T_BOOL	*/ ARGC_BOOL,    ARGC_BOOL,    ARGC_BOOL, ARGC_BOOL
}
};

int ParserShared::opInd( const char* opStr )
{
	if( !strcmp( opStr, "+"	 ) ) return PLUS;
	if( !strcmp( opStr, "-"	 ) ) return MINUS;
	if( !strcmp( opStr, "*"	 ) ) return STAR;	
	if( !strcmp( opStr, "/"	 ) ) return SLASH;	
	if( !strcmp( opStr, "%"	 ) ) return PERCENT;
	if( !strcmp( opStr, "="	 ) ) return ASSIGN;    
	if( !strcmp( opStr, "==" ) ) return ASSIGNASSIGN;
	if( !strcmp( opStr, "^"	 ) ) return XOR;       
	if( !strcmp( opStr, "|"	 ) ) return OR;        
	if( !strcmp( opStr, "||" ) ) return OROR;      
	if( !strcmp( opStr, "&"  ) ) return AND;       
	if( !strcmp( opStr, "&&" ) ) return ANDAND;    
	if( !strcmp( opStr, ">"	 ) ) return MORE;      
	if( !strcmp( opStr, ">=" ) ) return MOREASSIGN;
	if( !strcmp( opStr, "<"	 ) ) return LESS;      
	if( !strcmp( opStr, "<=" ) ) return LESSASSIGN;
	if( !strcmp( opStr, "!=" ) ) return EXCLAMASSIGN;
	if( !strcmp( opStr, "!"	 ) ) return UNARYEXCLAM;
	if( !strcmp( opStr, "u+" ) ) return UNARYPLUS;
	if( !strcmp( opStr, "u-" ) ) return UNARYMINUS;
	return -1;
}


int ParserShared::ArgT( ARGCLASS t )
{
	switch(t)
	{
		case ARGC_INT:		return T_INT;
		case ARGC_FLOAT:	return T_FLOAT;
		case ARGC_STRING:	return T_STRING;
		case ARGC_BOOL:		return T_BOOL;
	}
	return -1;
}
