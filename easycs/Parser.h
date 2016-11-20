#ifndef __EASYCS_PARSER_H__
#define __EASYCS_PARSER_H__

//BoMbAstiC gAmes

#include "Hash.h"
#include "ParserShared.h"
#include "String.h"




/*
================================

	Class Parser

================================
*/

class Parser
{
public:
	Parser();
	~Parser();

	void AssignVM( const VirtualMachine* pvm );
	void Compile( const char* fileName );

private:

	/*
	===============================
		Результат парсера
	===============================
	*/
	friend VMEasycs;
	VirtualMachine *vm;


	/*
	=============================
		Механизм транслятора
	=============================
	*/
	char* currFileName;
	char* logFileName;
	int numErrors, numWarnings;
	void LogText( char *lpszText, ... );

	Scaner	scaner;
	FILE	*currFile;
	token_s *currTok;

	// промежуточное хранилище кол-ва 
	// локальных переменных финкций 
	LArray<int> tempFuncsNumVars;

	// стек arg_t для перевода в ОПЗ
	Stack<arg_t> argStack;

	Hash<int>	htOverloadFuncs;   // хеш-таблица кол-ва 
								   // одноименных перегруженных ф-й
	Hash<int>	htFuncs;		   // хеш-таблица для функций(хранит адрес в массиве экземпляров функций)
	Hash<arg_t> htVars;			   // хеш-таблица для переменных	


	int				numBlock;	// номер блока( 0 1{ 2{} 3{ 4{} } } )
	int				blockDeep;  // глубина блока
	LArray<int>		deepStack;	// стек вложенности блока
	int				numVars;	// кол-во обьявлений локальных перемнных в текущей функции
	bool			inFunc;		// флаг того, что идет трансляция тела функции
	int				loopDeep;	// глубина вложенности циклов

	bool InFunc()const;			// флаг того, что идет трансляция функции
	bool InClass()const;		// флаг того, что идет трансляция класса

	// Область видимости
	// унифицированное имя функции : [ область видимости ]::@[ имя функции ]#[ номер перегрузки ]
	// унифицированное имя глобальной переменной : [ область видимости ]::[ имя глобальной переменной ]
	// унифицированное имя локальной переменной : [ унифицированное имя функции ]::[ имя локальной переменной ]#[ номер блока ]
	LArray<String>	namespaceStack; 
	int				namespaceDeep;
	String			MangleNamespace( const int deep );
	String			MangleVarName( const String& name,  const int nmspDeep, const int blockNum );


	void InitFunction( const char* uName, const char* type, const int numOvf );
	bool InitGlobalVariable( arg_t&, const char*, const char* );
	bool InitLocalVariable( arg_t&, const char*, const char*, int );
	bool MatchVariable( arg_t& a, const char* varName );
	bool MatchFunction( int& funcInd, const char* nameStr, const int numParams, const arg_t* params );
	void VariableDeclaration( const String& nameStr, const char* type );
	int  CorrelateFuncParameters( int& errParam, const int indFunc, const int numParams, const arg_t* params );
	int  GetTypeNarrow( const arg_t& arg1, const arg_t& arg2 );

	
	bool			IsLValue( const arg_t& arg );
	arg_t			GetTypeArg( const arg_t& a );				// Возвращает аргумент - результат, по аргументу трехадресного кода.	
	bool			IsType( arg_t& atype, const char* name );	// Возвращает факт объявления переменной с именем name
	bool			IsBaseType( const arg_t& arg );				// является ли аргумент базвого типа (int float bool string void)
	arg_t			StrTypeToArg( const String& stype );
	void			NewInstruction( const char* opStr, const arg_t& arg1, const arg_t& arg2 );
    codesegment_t*	MakeNewInstruction( const cfptr op, const arg_t* addrArg1, const arg_t* addrArg2, const arg_t* addrRes );
	void			StringToArgclass( arg_t& res, const String& stype );
	String			ArgclassToString( const arg_t& arg );
	
	bool			GetOperatorCompatibility( arg_t& res, const char* opStr, const arg_t& arg1, const arg_t& arg2 );
	cfptr			GetOpCode( const char* opStr, const arg_t& arg1, const arg_t& arg2 );
	cfptr			GetOpCode( const char* opStr, const arg_t& arg1 );

	void SetBreakContinue( const codesegment_t* loopBegin,  const codesegment_t* loopEnd, 
						   const codesegment_t* pBreak,     const codesegment_t* pContinue );

	// точка входа транслятора
	void StartParse();

	//=================================
	// рекурсивный СА
	//=================================

	// Первый проход определяет: кол-во функций, 
	// кол-во локальных переменных
	void PASS1_variable_function_decl();	// D: [ int | float | bool | void ] TC_VARIABLE [ = E { , TC_VARIABLE [ = E ] } | ( [???] ) { B1 } ] 
	void PASS1_return();

	void PASS1_expr_seq();					// block: { B1 }
	void PASS1_expr();						// S: block | D | A | _if_expr

	void PASS1_term_initialization();
	void PASS1_if_expr();					// if_expr: if ( A ) S [ else S ]
	void PASS1_while_expr();				// while_expr: while ( A ) S
	void PASS1_do_while_expr();				// do_while_expr: do S while ( A )
	void PASS1_for_initialization();
	void PASS1_for_expr();					// for( A , A , A ) expr

	void PASS1_arith_sequence();			// A {, A }
	void PASS1_arith_expr();				// A { [ = | *= | /= | ^= | |= | &= | %= | += | -= ] E }
	void PASS1_opp1();						// E: E1 { [ == | <= | >= | != | < | > ] E1 }
	void PASS1_opp2();						// E1: T { [ + | - | | | || | ^ ] T }
	void PASS1_opp3();						// T: U { [ * | / | & | && ] U }
	void PASS1_unary();						// U: [ + | - | ! ] F | F
	void PASS1_double_prefix();				// A ++
	void PASS1_double_suffix();				// ++ A
	void PASS1_factor();					// F: ( A ) | TC_CONSTANT_INT | TC_CONSTANT_FLOAT | [ [ ++ | -- ] TC_VARIABLE ] | TC_VARIABLE [ ++ | -- ]


	// Второй проход строит ВМ(четверки)
	void PASS2_variable_function_decl();	// D: [ int | float | bool | void ] TC_VARIABLE [ = E { , TC_VARIABLE [ = E ] } | ( [???] ) { B1 } ] 
	void PASS2_return();

	void PASS2_expr_seq();					// block: { B1 }
	void PASS2_expr();						// S: block | D | A | _if_expr

	void PASS2_break_continue();
	void PASS2_term_initialization();
	void PASS2_if_expr();					// if_expr: if ( A ) S [ else S ]
	void PASS2_while_expr();				// while_expr: while ( A ) S
	void PASS2_do_while_expr();				// do_while_expr: do S while ( A )
	void PASS2_for_initialization();
	void PASS2_for_expr();					// for( A , A , A ) expr

	void PASS2_arith_sequence();			// A { , A }
	void PASS2_arith_expr();				// A { [ = | *= | /= | ^= | |= | &= | %= | += | -= ] E }
	void PASS2_opp1();						// E: E1 { [ == | <= | >= | != | < | > ] E1 }
	void PASS2_opp2();						// E1: T { [ + | - | | | || | ^ ] T }
	void PASS2_opp3();						// T: U { [ * | / | & | && ] U }
	void PASS2_unary();						// U: [ + | - | ! ] F | F
	void PASS2_double_prefix();				// A ++
	void PASS2_double_suffix();				// ++ A
	void PASS2_factor();					// F: ( A ) | TC_CONSTANT_INT | TC_CONSTANT_FLOAT | [ [ ++ | -- ] TC_VARIABLE ] | TC_VARIABLE [ ++ | -- ]



	///////////////////////////////////////
	///////////////////////////////////////
	void PrintVM();
	void PrintArg( const arg_t*);
	void PrintArgClass( const arg_t*);
	void PrintOp( const cfptr );

};





#endif




