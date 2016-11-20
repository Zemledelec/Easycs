#ifndef __EASYCS_PARSERSHARED_H__
#define __EASYCS_PARSERSHARED_H__

#include <stdarg.h>
#include "Scaner.h"
#include "VirtualMachine.h"


#define NOCOMPATIBLE_TYPES 555
#define UNAMBIGUOUS_TYPES -5554


class ParserShared
{
public:
	static const int utMx[3][4];
	static const int btMx[17][4][4];

	// ���������� true ���� ��������� ������������� ������
	// ��������� ���� �� � ����� �������� �������
	// TOKENSTR( tt, TC_KEYWORD, "int", "float" );
	static bool  TOKENSTR( const token_s& t,  const int count, const TOKENCLASS tc, ... );
	static bool  STRSTRSTR( const char* s, const int count, ... );

	// ���������� �������� ����������� ��������� ���������������� ������.
	static arg_t TOKEN2ARG( const token_s& t );
//	static cfptr TOKEN2OP( const token_s& t );
//	static cfptr STR2OP( const char* str );

	// ���������� ��� �� ��� ��������
	static ARGCLASS STR2ARGCLASS( const char* );
	static int opInd( const char* opStr );
	static int ArgT( ARGCLASS t );
	static int GetNarrowBaseType( const arg_t& arg1, const arg_t& arg2 );
};

#endif