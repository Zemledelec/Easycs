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
		��������� �������
	===============================
	*/
	friend VMEasycs;
	VirtualMachine *vm;


	/*
	=============================
		�������� �����������
	=============================
	*/
	char* currFileName;
	char* logFileName;
	int numErrors, numWarnings;
	void LogText( char *lpszText, ... );

	Scaner	scaner;
	FILE	*currFile;
	token_s *currTok;

	// ������������� ��������� ���-�� 
	// ��������� ���������� ������� 
	LArray<int> tempFuncsNumVars;

	// ���� arg_t ��� �������� � ���
	Stack<arg_t> argStack;

	Hash<int>	htOverloadFuncs;   // ���-������� ���-�� 
								   // ����������� ������������� �-�
	Hash<int>	htFuncs;		   // ���-������� ��� �������(������ ����� � ������� ����������� �������)
	Hash<arg_t> htVars;			   // ���-������� ��� ����������	


	int				numBlock;	// ����� �����( 0 1{ 2{} 3{ 4{} } } )
	int				blockDeep;  // ������� �����
	LArray<int>		deepStack;	// ���� ����������� �����
	int				numVars;	// ���-�� ���������� ��������� ��������� � ������� �������
	bool			inFunc;		// ���� ����, ��� ���� ���������� ���� �������
	int				loopDeep;	// ������� ����������� ������

	bool InFunc()const;			// ���� ����, ��� ���� ���������� �������
	bool InClass()const;		// ���� ����, ��� ���� ���������� ������

	// ������� ���������
	// ��������������� ��� ������� : [ ������� ��������� ]::@[ ��� ������� ]#[ ����� ���������� ]
	// ��������������� ��� ���������� ���������� : [ ������� ��������� ]::[ ��� ���������� ���������� ]
	// ��������������� ��� ��������� ���������� : [ ��������������� ��� ������� ]::[ ��� ��������� ���������� ]#[ ����� ����� ]
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
	arg_t			GetTypeArg( const arg_t& a );				// ���������� �������� - ���������, �� ��������� ������������� ����.	
	bool			IsType( arg_t& atype, const char* name );	// ���������� ���� ���������� ���������� � ������ name
	bool			IsBaseType( const arg_t& arg );				// �������� �� �������� ������� ���� (int float bool string void)
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

	// ����� ����� �����������
	void StartParse();

	//=================================
	// ����������� ��
	//=================================

	// ������ ������ ����������: ���-�� �������, 
	// ���-�� ��������� ����������
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


	// ������ ������ ������ ��(��������)
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




