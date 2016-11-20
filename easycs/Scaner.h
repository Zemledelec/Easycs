#ifndef __EASYCS_SCANER_H__
#define __EASYCS_SCANER_H__

#include "LArray.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

//	расрознает: 
//				одинарные разделители: (все)
//				двойные разделители: == += -= *= /= &= ^= |= %= != >= <= ++ -- || &&
//				цепочки символов: [a]+...
//				числовые константы:  [n].[n][e|E][+|-][n] | [n]
//				строка: "..."
//				ключевые слова
//				ремарки: /*...*/  //...
//

const static char* keywords[]= 
{
	"int",
	"float",
	"if",
	"return",
	"while",
	"do",
	"break",
	"continue",
	"void",
	"false",
	"true",
	"bool",
	"else",
	"string",
	"for",
	"exit",
	"switch",
	"case",
	NULL
};



enum TOKENCLASS
{
	TC_SEPARATOR=0,
	TC_CONSTANT_INT,
	TC_CONSTANT_FLOAT,
	TC_VARIABLE,
	TC_STRING,
	TC_KEYWORD
};

// позиция токена в текстовом файле
struct fPosition_s{
	int Line;	// строка
	int Char;	// символ
	int Column; // столбец
};


//лексема(token)
struct token_s{
	TOKENCLASS	tokClass;
	union{
		int		cInt;
		float	cFloat;
		char	*str;
	};

	fPosition_s fPos;

	token_s();
	~token_s();

	void Set( const TOKENCLASS tc, const int   v );
	void Set( const TOKENCLASS tc, const float v );
	void Set( const TOKENCLASS tc, const char *s );
};


inline token_s::token_s(){
	str = NULL;
	fPos.Line = fPos.Char = fPos.Column = 1;
}

inline token_s::~token_s(){
	if( str )
		if( !( ( tokClass==TC_CONSTANT_INT ) || ( tokClass==TC_CONSTANT_FLOAT ) ) )
			delete[] str;
}

inline void token_s::Set( const TOKENCLASS tc, const int   v ){
	if( str )
		if( !( ( tokClass==TC_CONSTANT_INT ) || ( tokClass==TC_CONSTANT_FLOAT ) ) )
			delete[] str;
	tokClass = tc;
	cInt = v;
}

inline void token_s::Set( const TOKENCLASS tc, const float v ){
	if( str )
		if( !( ( tokClass==TC_CONSTANT_INT ) || ( tokClass==TC_CONSTANT_FLOAT ) ) )
			delete[] str;
	tokClass = tc;
	cFloat = v;
}

inline void token_s::Set( const TOKENCLASS tc, const char *s )
{
	if( tc == TC_SEPARATOR || 
		tc == TC_VARIABLE  || 
		tc == TC_KEYWORD   ||
		tc == TC_STRING )
	{
		
		if( str )
			if( !( ( tokClass==TC_CONSTANT_INT ) || ( tokClass==TC_CONSTANT_FLOAT ) ) )
				delete[] str;
		tokClass = tc;
		str = new char[ strlen( s ) + 1 ];
		memset( str, 0x0000, strlen( s ) + 1 );
		strcpy_s( str, strlen( s ) + 1, s );
	}
}


static void printtoken( token_s& t ){
	switch( t.tokClass )
	{
	case TC_SEPARATOR:      printf( "TC_SEPARATOR       _%s_\n", t.str ); break;
	case TC_CONSTANT_FLOAT: printf( "TC_CONSTANT_FLOAT  _%f_\n", t.cFloat );break;
	case TC_CONSTANT_INT:   printf( "TC_CONSTANT_INT    _%d_\n", t.cInt ); break;
	case TC_VARIABLE:       printf( "TC_VARIABLE        _%s_\n", t.str ); break;
	case TC_KEYWORD:        printf( "TC_KEYWORD         _%s_\n", t.str ); break;
	case TC_STRING:         printf( "TC_STRING          _%s_\n", t.str );break;
	}
}




class Scaner
{
	FILE *fp;
	int scanChar[256];
	static int scanTable[27][40];

	void	Init();
	int		Str2Int		( const char *str );
	float	Str2Float	( const char *str );
	int		HStr2Int	( const char *str );
	bool	IsKeyword	( const char *str );

public:
	Scaner(){
		Init();
	};
	~Scaner(){};
	void Assign( FILE* f );

	// возвращает лексему из фаилового потока.
	// В случае удачной обработки лексемы возвращает 0
	// иначе возвращает код ошибки обрабатываемой лексемы
	// (пропускает "пустые" разделители и ремарки)
	int Read( token_s& t );
};


inline void Scaner::Assign( FILE* f ){
	fp = f;
}





#endif