
#include "Parser.h"
//#include <ios>			// _msize

#define MAXDIGITS  16	// кол-во цифр в числе


void Parser::LogText( char *lpszText, ... ){

    va_list argList;
    FILE *pFile;

    va_start(argList, lpszText);

    if ((pFile = fopen( logFileName, "a+")) == NULL)
	    return;

    vfprintf(pFile, lpszText, argList);

    fclose(pFile);
    va_end(argList);
}


arg_t Parser::GetTypeArg( const arg_t& a )
{
	switch( a.argClass )
	{
	case ARGC_POINTER:		return GetTypeArg( *a.addrInstruction->instr.res );
	case ARGC_GLOBAL_VAR:   return GetTypeArg( *a.addrGlobal );
	case ARGC_LOCAL_VAR:	return GetTypeArg( vm->funcs[ vm->numFuncs ].localVars[ a.addrLocal ] );
	case ARGC_REFERENCE:	return GetTypeArg( *a.addrReference );
	}
	return a;
}


// конструктор
Parser::Parser(){
	vm = 0x0000;
}


// деструктор
Parser::~Parser(){
	delete currTok;
}



void Parser::Compile( const char* fileName )
{
	currFileName = const_cast<char*>(fileName);
	if( fopen_s( &currFile, fileName, "rt" ) ){
		return;
	}
	scaner.Assign( currFile );

	if( !vm )
		vm = new VirtualMachine;

	StartParse();
}

void Parser::AssignVM( const VirtualMachine* pvm ){
	vm = const_cast<VirtualMachine*>(pvm);
}



void Parser::StartParse()
{
	// PASS1
	currTok = new token_s;
	inFunc = false;
	namespaceDeep	= 0;
	vm->numFuncs	= 0;
	numBlock		= 0;
	blockDeep		= 0;
	loopDeep		= 0;


	argStack.SetSize( 128, false );

	numErrors = numWarnings = 0;

	LogText( "Compiling...\n" );
	tempFuncsNumVars.SetSize( 256, false );
	while( !feof( currFile ) )
	{
		scaner.Read( *currTok );
		PASS1_expr();
	}

	if( numErrors > 0 ){
		LogText( "%s - %d error(s), %d warning(s)\n", currFileName, numErrors, numWarnings );
		return;
	}

	vm->funcs = new activationrecord_s[ vm->numFuncs ];
	for( int i=0; i<vm->numFuncs; i++ ){
		int nvars = tempFuncsNumVars[i];
		vm->funcs[i].numVars = nvars;
		if( nvars )
			vm->funcs[i].localVars = new arg_t[ nvars ];
	}
	tempFuncsNumVars.Clear();


	// PASS2
	namespaceDeep	= 0;
	vm->numFuncs	= 0;
	numBlock		= 0;
	blockDeep		= 0;
	loopDeep		= 0;
	deepStack[ 0 ]  = 0;

	vm->internalCode->NewInstruction( &VirtualMachine::NOP, 0x0000, 0x0000 );
	namespaceStack.SetSize( 100, false );

	fseek( currFile, 0, SEEK_SET );
	while( !feof( currFile ) )
	{
		scaner.Read( *currTok );
		PASS2_expr();
	}

	MakeNewInstruction( &VirtualMachine::NOP, 0x0000, 0x0000, 0x0000 );

	fclose( currFile );
	LogText("Compile complete.\n");
}


/*
=====================================
	PASS1
=====================================
*/
void Parser::PASS1_variable_function_decl()
{
	scaner.Read( *currTok );

	int len = strlen( currTok->str ) + 1;
	char* funName = new char[ len ];
	strcpy_s( funName, len, currTok->str );

	if( currTok->tokClass != TC_VARIABLE )
	{
		LogText( "%s(%d) : error: syntax error '%s' : variable expected.\n", currFileName, currTok->fPos.Line, currTok->str ); 
		numErrors++;
		delete[] funName;
		return;
	}
	scaner.Read( *currTok );

	// объявление переменной
	if( ParserShared::TOKENSTR( *currTok, 3, TC_SEPARATOR, "=", ",", ";" ) )
	{
		// локальная
		if( inFunc ){
			numVars++;
		}
		// глобальная
//		else{
//			numGlobDecls++;
//		}

		// инициализация переменной
		if( ParserShared::TOKENSTR( *currTok, 1, TC_SEPARATOR, "=" ) )
		{
			scaner.Read( *currTok );
			PASS1_arith_expr();
		}
		
		while( ParserShared::TOKENSTR( *currTok, 1, TC_SEPARATOR, "," ) )
		{
			scaner.Read( *currTok );

			if( currTok->tokClass == TC_VARIABLE )
			{
				// локальная
				if( inFunc ){
					numVars++;
				}
				// глобальная
//				else{
//					numGlobDecls++;
//				}
				scaner.Read( *currTok );

				// инициализация переменной
				if( ParserShared::TOKENSTR( *currTok, 1, TC_SEPARATOR, "=" ) )
				{
					scaner.Read( *currTok );
					PASS1_arith_expr();
				}
			}
			else{
				LogText( "%s(%d) : error: syntax error : variable expected.\n", currFileName, currTok->fPos.Line ); 
				numErrors++;
			}
		}
		if( !ParserShared::TOKENSTR( *currTok, 1, TC_SEPARATOR, ";" ) ){
			LogText( "%s(%d) : error: syntax error : '%s'\n", currFileName, currTok->fPos.Line, currTok->str ); 
			numErrors++;
		}
	}
	// объявление функции
	else if( ParserShared::TOKENSTR( *currTok, 1, TC_SEPARATOR, "(" ) && !inFunc )
	{
		inFunc  = true;
		numVars = 0;
		numBlock  = 0;
		vm->numFuncs++;

		scaner.Read( *currTok );

		if( ParserShared::TOKENSTR( *currTok, 5, TC_KEYWORD, "void", "int", "float", "string", "bool" ) )
		{
			scaner.Read( *currTok );

			if( ParserShared::TOKENSTR( *currTok, 1, TC_SEPARATOR, "&" ) )
				scaner.Read( *currTok );

			if( currTok->tokClass == TC_VARIABLE )
			{
				numVars++;
				scaner.Read( *currTok );

				while( ParserShared::TOKENSTR( *currTok, 1, TC_SEPARATOR, "," ) )
				{
					scaner.Read( *currTok );

					if( ParserShared::TOKENSTR( *currTok, 5, TC_KEYWORD, "void", "int", "float", "bool", "string" ) )
					{
						scaner.Read( *currTok );

						if( ParserShared::TOKENSTR( *currTok, 1, TC_SEPARATOR, "&" ) )
							scaner.Read( *currTok );

						if( currTok->tokClass == TC_VARIABLE )
						{
							numVars++;
							scaner.Read( *currTok );
						}
						else{
							LogText( "%s(%d) : error: syntax error : '%s'\n", currFileName, currTok->fPos.Line, currTok->str ); 
							numErrors++;
						}

					}
					else{
						LogText( "%s(%d) : error: syntax error : '%s'\n", currFileName, currTok->fPos.Line, currTok->str ); 
						numErrors++;
					}
				}
			}
			else{
				LogText( "%s(%d) : error: syntax error : '%s'\n", currFileName, currTok->fPos.Line, currTok->str ); 
				numErrors++;
			}
		}

		if( !ParserShared::TOKENSTR( *currTok, 1, TC_SEPARATOR, ")" ) ){
			LogText( "%s(%d) : error: syntax error : ')' expected\n", currFileName, currTok->fPos.Line ); 
			numErrors++;
		}

		scaner.Read( *currTok );

		if( ParserShared::TOKENSTR( *currTok, 1, TC_SEPARATOR, "{" ) )
		{
			PASS1_expr_seq();
		}
		else{
		}

		inFunc = false;
		tempFuncsNumVars[ vm->numFuncs - 1 ] = numVars;
	}
	else{
		LogText( "%s(%d) : error: '%s' local function definitions are illegal.\n", currFileName, currTok->fPos.Line, funName ); 
		while( !ParserShared::TOKENSTR( *currTok, 2, TC_SEPARATOR, ")", ";" ) )scaner.Read( *currTok );
		numErrors++;
	}
	delete[] funName;
}


void Parser::PASS1_expr_seq()
{
	if( ParserShared::TOKENSTR( *currTok, 1, TC_SEPARATOR, "{" ) )
	{
		numBlock++;
		blockDeep++;
		deepStack[ blockDeep ] = numBlock;

		scaner.Read( *currTok );

		PASS1_expr();

		while( ParserShared::TOKENSTR( *currTok, 1, TC_SEPARATOR, ";" ) )
		{		
			scaner.Read( *currTok );
			PASS1_expr();
		}

		if( !ParserShared::TOKENSTR( *currTok, 1, TC_SEPARATOR, "}" ) ){
			LogText( "%s(%d) : error: syntax error : '}' expected\n", currFileName, currTok->fPos.Line ); 
			numErrors++;
		}

		currTok->Set( TC_SEPARATOR, ";" );
		blockDeep--;
	}
}


void Parser::PASS1_return()
{
	scaner.Read( *currTok );
	PASS1_arith_sequence();
}



void Parser::PASS1_expr()
{
	if( ParserShared::TOKENSTR( *currTok, 5, TC_KEYWORD, "int", "float", "void", "string", "bool" ) )
	{
		PASS1_variable_function_decl();
	}
	else if( ParserShared::TOKENSTR( *currTok, 1, TC_SEPARATOR, "{" ) )
	{
		PASS1_expr_seq();
	}
	else if( ParserShared::TOKENSTR( *currTok, 1, TC_KEYWORD, "if" ) )
	{
		PASS1_if_expr();
	}
	else if( ParserShared::TOKENSTR( *currTok, 1, TC_KEYWORD, "while" ) )
	{
		PASS1_while_expr();
	}
	else if( ParserShared::TOKENSTR( *currTok, 1, TC_KEYWORD, "do" ) )
	{
		PASS1_do_while_expr();
	}
	else if( ParserShared::TOKENSTR( *currTok, 1, TC_KEYWORD, "for" ) )
	{
		PASS1_for_expr();
	}
	else if( ParserShared::TOKENSTR( *currTok, 1, TC_KEYWORD, "return" ) )
	{
		PASS1_return();
	}
	else if( ParserShared::TOKENSTR( *currTok, 2, TC_KEYWORD, "break", "continue" ) )
	{
		scaner.Read( *currTok );
	}
	else
	{
		PASS1_arith_sequence();
	}
}


void Parser::PASS1_if_expr()
{
	if( ParserShared::TOKENSTR( *currTok, 1, TC_KEYWORD, "if" ) )
	{
		scaner.Read( *currTok );

		if( !ParserShared::TOKENSTR( *currTok, 1, TC_SEPARATOR, "(" ) ){
			LogText( "%s(%d) : error: syntax error : '(' expected\n", currFileName, currTok->fPos.Line ); 
			numErrors++;
		}

		scaner.Read( *currTok );

		PASS1_term_initialization();

		if( !ParserShared::TOKENSTR( *currTok, 1, TC_SEPARATOR, ")" ) ){
			LogText( "%s(%d) : error: syntax error : ')' expected\n", currFileName, currTok->fPos.Line ); 
			numErrors++;
		}

		scaner.Read( *currTok );

		PASS1_expr();

		long pos = ftell( currFile );
		scaner.Read( *currTok );

		if( ParserShared::TOKENSTR( *currTok, 1, TC_KEYWORD, "else" ) )
		{
				scaner.Read( *currTok );
				PASS1_expr();
		}
		else{
			fseek( currFile, pos, SEEK_SET );
			currTok->Set( TC_SEPARATOR, ";" );
		}
	}
}


void Parser::PASS1_while_expr()
{
	if( ParserShared::TOKENSTR( *currTok, 1, TC_KEYWORD, "while" ) )
	{
		scaner.Read( *currTok );

		if( !ParserShared::TOKENSTR( *currTok, 1, TC_SEPARATOR, "(" ) ){
			LogText( "%s(%d) : error: syntax error : '(' expected\n", currFileName, currTok->fPos.Line ); 
			numErrors++;
			return;
		}

		scaner.Read( *currTok );

		PASS1_term_initialization();

		if( !ParserShared::TOKENSTR( *currTok, 1, TC_SEPARATOR, ")" ) ){
			LogText( "%s(%d) : error: syntax error : ')' expected\n", currFileName, currTok->fPos.Line ); 
			numErrors++;
			return;
		}

		scaner.Read( *currTok );

	    PASS1_expr();
	}				
}


void Parser::PASS1_do_while_expr()
{
	if( ParserShared::TOKENSTR( *currTok, 1, TC_KEYWORD, "do" ) )
	{
		scaner.Read( *currTok );

		PASS1_expr_seq();

		scaner.Read( *currTok );

		if( !ParserShared::TOKENSTR( *currTok, 1, TC_KEYWORD, "while" ) ){
			LogText( "%s(%d) : error: syntax error : 'while' expected\n", currFileName, currTok->fPos.Line ); 
			numErrors++;
			return;
		}
		scaner.Read( *currTok );
		if( !ParserShared::TOKENSTR( *currTok, 1, TC_SEPARATOR, "(" ) ){
			LogText( "%s(%d) : error: syntax error : '(' expected\n", currFileName, currTok->fPos.Line ); 
			numErrors++;
			return;
		}

		scaner.Read( *currTok );

		PASS1_arith_expr();

		if( !ParserShared::TOKENSTR( *currTok, 1, TC_SEPARATOR, ")" ) ){
			LogText( "%s(%d) : error: syntax error : ')' expected\n", currFileName, currTok->fPos.Line ); 
			numErrors++;
			return;
		}

		scaner.Read( *currTok );

		if( !ParserShared::TOKENSTR( *currTok, 1, TC_SEPARATOR, ";" ) ){
			LogText( "%s(%d) : error: syntax error : missing ';' before '%s'\n", currFileName, currTok->fPos.Line, currTok->str ); 
			numErrors++;
		}
	}
}


void Parser::PASS1_term_initialization()
{
	if( ParserShared::TOKENSTR( *currTok, 5, TC_KEYWORD, "int", "float", "void", "bool", "string" ) )
	{
		scaner.Read( *currTok );
		if( currTok->tokClass != TC_VARIABLE ){
			// error: empty term declaration
			numErrors++;
		}
		else
		{
			numVars++;
			scaner.Read( *currTok );

			if( !ParserShared::TOKENSTR( *currTok, 1, TC_SEPARATOR, "=" ) ){
				// error: empty term declaration	
				numErrors++;
			}
			else{
				scaner.Read( *currTok );
				PASS1_arith_expr();
			}
		}
	}
	else
	{
		PASS1_arith_expr();
	}
}




void Parser::PASS1_for_initialization()
{
	if( ParserShared::TOKENSTR( *currTok, 5, TC_KEYWORD, "int", "float", "void", "bool", "string" ) )
	{
		scaner.Read( *currTok );
		if( currTok->tokClass != TC_VARIABLE ){
			// error: empty declaration
		}
		else
		{
			numVars++;
			scaner.Read( *currTok );

			if( ParserShared::TOKENSTR( *currTok, 1, TC_SEPARATOR, "=" ) ){
				scaner.Read( *currTok );
				PASS1_arith_expr();
			}

			while( ParserShared::TOKENSTR( *currTok, 1, TC_SEPARATOR, "," ) )
			{
				scaner.Read( *currTok );
				if( currTok->tokClass != TC_VARIABLE ){
					// syntax error 'currTok'
				}
				else
				{
					numVars++;
					scaner.Read( *currTok );

					if( ParserShared::TOKENSTR( *currTok, 1, TC_SEPARATOR, "=" ) ){
						scaner.Read( *currTok );
						PASS1_arith_expr();
					}
				}
			}
		}
	}
	else
	{
		PASS1_arith_sequence();
	}
}



void Parser::PASS1_for_expr()
{
	if( ParserShared::TOKENSTR( *currTok, 1, TC_KEYWORD, "for" ) )
	{
		scaner.Read( *currTok );

		if( !ParserShared::TOKENSTR( *currTok, 1, TC_SEPARATOR, "(" ) ){
			LogText( "%s(%d) : error: syntax error : '(' expected\n", currFileName, currTok->fPos.Line ); 
			numErrors++;
			return;
		}

		scaner.Read( *currTok );

		PASS1_for_initialization();

		if( !ParserShared::TOKENSTR( *currTok, 1, TC_SEPARATOR, ";" ) ){
			LogText( "%s(%d) : error: syntax error : ';' expected\n", currFileName, currTok->fPos.Line ); 
			numErrors++;
			return;
		}

		scaner.Read( *currTok );

		PASS1_arith_sequence();

		if( !ParserShared::TOKENSTR( *currTok, 1, TC_SEPARATOR, ";" ) ){
			LogText( "%s(%d) : error: syntax error : ';' expected\n", currFileName, currTok->fPos.Line ); 
			numErrors++;
			return;
		}

		scaner.Read( *currTok );

		PASS1_arith_sequence();

		if( !ParserShared::TOKENSTR( *currTok, 1, TC_SEPARATOR, ")" ) ){
			LogText( "%s(%d) : error: syntax error : ')' expected\n", currFileName, currTok->fPos.Line ); 
			numErrors++;
			return;
		}

		scaner.Read( *currTok );

		PASS1_expr();
	}
}



void Parser::PASS1_arith_sequence()
{
	PASS1_arith_expr();

	while( ParserShared::TOKENSTR( *currTok, 1, TC_SEPARATOR, "," ) )
	{
		scaner.Read( *currTok );
		PASS1_arith_expr();
	}
}


void Parser::PASS1_arith_expr()
{
	PASS1_opp1();

	while( ParserShared::TOKENSTR( *currTok, 9, TC_SEPARATOR, "=", "+=", "-=", "*=", "/=", "&=", "|=", "^=", "%=" ) )
	{
		scaner.Read( *currTok );
		PASS1_opp1();
	}
}


void Parser::PASS1_opp1()
{
	PASS1_opp2();

	while( ParserShared::TOKENSTR( *currTok, 6, TC_SEPARATOR, "==", "<=", ">=", "!=", "<", ">" ) )
	{
		scaner.Read( *currTok );
		PASS1_opp2();
	}
}


void Parser::PASS1_opp2()
{
	PASS1_opp3();

	while( ParserShared::TOKENSTR( *currTok, 5, TC_SEPARATOR, "+", "-", "|", "||", "^" ) )
	{
		scaner.Read( *currTok );
		PASS1_opp3();
	}
}


void Parser::PASS1_opp3()
{
	PASS1_unary();

	while( ParserShared::TOKENSTR( *currTok, 5, TC_SEPARATOR, "*", "/", "&", "&&", "%" ) )
	{
		scaner.Read( *currTok );
		PASS1_unary();
	}
}


void Parser::PASS1_unary()
{
	if( ParserShared::TOKENSTR(*currTok, 3, TC_SEPARATOR, "+", "-", "!" ) )
	{
		scaner.Read( *currTok );
	}

	PASS1_double_prefix();
}


void Parser::PASS1_double_prefix()
{
	if( ParserShared::TOKENSTR( *currTok, 2, TC_SEPARATOR, "++", "--" ) )
	{
		scaner.Read( *currTok );
	}

	PASS1_double_suffix();	
}

void Parser::PASS1_double_suffix()
{
	PASS1_factor();

	if( ParserShared::TOKENSTR( *currTok, 2, TC_SEPARATOR, "++", "--" ) )
	{
		scaner.Read( *currTok );
	}
}

void Parser::PASS1_factor()
{
	if( ParserShared::TOKENSTR( *currTok, 1, TC_SEPARATOR, "(" ) ){
		scaner.Read( *currTok );
		PASS1_arith_sequence();
		if( !ParserShared::TOKENSTR( *currTok, 1, TC_SEPARATOR, ")" ) ){
			LogText( "%s(%d) : error: syntax error : ')' expected\n", currFileName, currTok->fPos.Line ); 
			numErrors++;
		}
		scaner.Read( *currTok );
		return;
	}

	if( currTok->tokClass == TC_CONSTANT_INT    || 
		currTok->tokClass == TC_CONSTANT_FLOAT  || 
		currTok->tokClass == TC_STRING )
	{
		scaner.Read( *currTok );
		return;
	}

	if( currTok->tokClass == TC_VARIABLE ){
		scaner.Read( *currTok );
		// функция
		if( ParserShared::TOKENSTR( *currTok, 1, TC_SEPARATOR, "(" ) )
		{
			if( inFunc ){
				numVars++;
			}

			scaner.Read( *currTok );
			if( !ParserShared::TOKENSTR( *currTok, 1, TC_SEPARATOR, ")" ) ){
				PASS1_arith_expr();
				while( ParserShared::TOKENSTR( *currTok, 1, TC_SEPARATOR, "," ) ){
					scaner.Read( *currTok );
					PASS1_arith_expr();
				}
				if( !ParserShared::TOKENSTR( *currTok, 1, TC_SEPARATOR, ")" ) ){
					LogText( "%s(%d) : error: syntax error : ')' expected\n", currFileName, currTok->fPos.Line ); 
					numErrors++;
				}
			}
			scaner.Read( *currTok );
		}
		// переменная
		else{
		}
		return;
	}
}



/*
=====================================
	PASS2
=====================================
*/

cfptr Parser::GetOpCode( const char* opStr, const arg_t& arg1 )
{
	if( !strcmp( opStr, "u!"   ) ) return VirtualMachine::ArUNARYEXCLAM		[ arg1.argClass ];
	if( !strcmp( opStr, "u-"   ) ) return VirtualMachine::ArUNARYMINUS		[ arg1.argClass ];
//	if( !strcmp( opStr, "jmpf" ) ) return VirtualMachine::ArJMPF			[ arg1.argClass ];
//	if( !strcmp( opStr, "jmpt" ) ) return VirtualMachine::ArJMPT			[ arg1.argClass ];
//	if( !strcmp( opStr, "push" ) ) return VirtualMachine::ArPUSH			[ arg1.argClass ];

	return 0x0000;
}

cfptr Parser::GetOpCode( const char* opStr, const arg_t& arg1, const arg_t& arg2 )
{
	if( !strcmp( opStr, "+"  ) ) return VirtualMachine::MxPLUS			[ arg1.argClass ][ arg2.argClass ];
	if( !strcmp( opStr, "="  ) ) return VirtualMachine::MxASSIGN		[ arg1.argClass ][ arg2.argClass ];
	if( !strcmp( opStr, "-"  ) ) return VirtualMachine::MxMINUS			[ arg1.argClass ][ arg2.argClass ];
	if( !strcmp( opStr, "*"  ) ) return VirtualMachine::MxSTAR			[ arg1.argClass ][ arg2.argClass ];
	if( !strcmp( opStr, "/"  ) ) return VirtualMachine::MxSLASH			[ arg1.argClass ][ arg2.argClass ];
	if( !strcmp( opStr, "%"  ) ) return VirtualMachine::MxPERCENT		[ arg1.argClass ][ arg2.argClass ];
	if( !strcmp( opStr, "^"  ) ) return VirtualMachine::MxXOR			[ arg1.argClass ][ arg2.argClass ];
	if( !strcmp( opStr, "&"  ) ) return VirtualMachine::MxAND			[ arg1.argClass ][ arg2.argClass ];
	if( !strcmp( opStr, "==" ) ) return VirtualMachine::MxASSIGNASSIGN	[ arg1.argClass ][ arg2.argClass ];
	if( !strcmp( opStr, "|"  ) ) return VirtualMachine::MxOR			[ arg1.argClass ][ arg2.argClass ];
	if( !strcmp( opStr, "||" ) ) return VirtualMachine::MxOROR			[ arg1.argClass ][ arg2.argClass ];
	if( !strcmp( opStr, "&&" ) ) return VirtualMachine::MxANDAND		[ arg1.argClass ][ arg2.argClass ];
	if( !strcmp( opStr, ">"  ) ) return VirtualMachine::MxMORE			[ arg1.argClass ][ arg2.argClass ];
	if( !strcmp( opStr, ">=" ) ) return VirtualMachine::MxMOREASSIGN	[ arg1.argClass ][ arg2.argClass ];
	if( !strcmp( opStr, "<"  ) ) return VirtualMachine::MxLESS			[ arg1.argClass ][ arg2.argClass ];
	if( !strcmp( opStr, "<=" ) ) return VirtualMachine::MxLESSASSIGN	[ arg1.argClass ][ arg2.argClass ];
	if( !strcmp( opStr, "!=" ) ) return VirtualMachine::MxEXCLAMASSIGN	[ arg1.argClass ][ arg2.argClass ];

	return 0x0000;
}


bool Parser::GetOperatorCompatibility( arg_t& res, const char* opStr, 
												   const arg_t& arg1, 
												   const arg_t& arg2 )
{
	int resType;
	if( opStr[0] != 'u' ){
		// для бинарных операторов
		resType = ParserShared::btMx[ ParserShared::opInd( opStr ) ]
									[ ParserShared::ArgT( arg1.argClass ) ]
									[ ParserShared::ArgT( arg2.argClass ) ];
	}
	else{
		// для унарных операторов
		resType = ParserShared::utMx[ ParserShared::opInd( opStr ) ]
									[ ParserShared::ArgT( arg1.argClass ) ];
	}

	res.argClass = static_cast<ARGCLASS>( resType );

	if( ARGC_ERROR == resType ){
		return false;
	}

	return true;
}


bool Parser::IsBaseType( const arg_t& arg )
{
	if( arg.argClass == ARGC_INT	 ||  
	    arg.argClass == ARGC_FLOAT	 ||
        arg.argClass == ARGC_BOOL	 ||
        arg.argClass == ARGC_STRING  ||
		arg.argClass == ARGC_VOID )
	{
		return true;
	}
	return false;
}



void Parser::NewInstruction( const char* opStr, const arg_t& arg1, const arg_t& arg2 )
{
	arg_t res;

 	if( GetOperatorCompatibility( res, opStr, GetTypeArg( arg1 ), GetTypeArg( arg2 ) ) )
	{
		cfptr op;
		if( IsBaseType( arg1 ) && IsBaseType( arg2 ) )
		{
			if( opStr[0] != 'u' )
				op = GetOpCode( opStr, arg1, arg2 );
			else
				op = GetOpCode( opStr, arg1 );

			(vm->*(op))( const_cast<arg_t*>(&arg1), const_cast<arg_t*>(&arg2), &res );
		}
		else
		{
			arg_t *new_arg1 = 0x0000,
				  *new_arg2 = 0x0000;
				  //*new_res  = 0x0000;

			new_arg1 = vm->internalCode->NewArg( arg1 );
			if( opStr[0] != 'u' ){
				new_arg2 = vm->internalCode->NewArg( arg2 );
				op = GetOpCode( opStr, *new_arg1, *new_arg2 );
			}
			else
				op = GetOpCode( opStr, *new_arg1 );

			//new_res				= new arg_t( res );
			//res.addrInstruction = vm->internalCode->NewInstruction( op, new_arg1, new_arg2 );
			//vm->internalCode->codeCurr->instr.res = new_res;
			res.addrInstruction = MakeNewInstruction( op, new_arg1, new_arg2, new arg_t( res ) );
			res.argClass		= ARGC_POINTER;
		}

		argStack.Push( res );
	}
	else
	{
		LogText("error: cant covert type 'TEMPORARY' to 'TEMPORARY'\n" );
		// error... несовместимость типов или типа(для унарного) оператора
		numErrors++;
	}
}


codesegment_t* Parser::MakeNewInstruction( const cfptr op, const arg_t* addrArg1, const arg_t* addrArg2, const arg_t* addrRes ){
	codesegment_t* res;
	if( 0x0000 == vm->internalCode->codeCurr->instr.opf ){
		res = vm->internalCode->codeCurr;
		vm->internalCode->SetInstruction( res, op, const_cast<arg_t*>(addrArg1), const_cast<arg_t*>(addrArg2) );
	}else
		res = vm->internalCode->NewInstruction( op, const_cast<arg_t*>(addrArg1), const_cast<arg_t*>(addrArg2) );
	res->instr.res = const_cast<arg_t*>(addrRes);
	return res;
}


bool Parser::IsType( arg_t& atype, const char* name )
{
	if( ParserShared::STRSTRSTR( name, 5, "int", "float", "void", "string", "bool" ) ){
		atype.argClass = ParserShared::STR2ARGCLASS( name );
		return true;
	}

	//
	// ... проверка для ARGC_USER переменной
	//

	return false;
}



bool Parser::InitGlobalVariable( arg_t& resArg, const char* name, const char* type )
{
	arg_t *globalVar;
//	String nameStr = "::" + String( name );
	//String mangledVarName( MangleVarName( name, deepStack[ blockDeep ] ) );

	if( htVars.Get( name, &globalVar ) ){
		if( globalVar->addrGlobal->argClass == ParserShared::STR2ARGCLASS( type ) )
			LogText( "%s(%d) : error: '%s %s' : redifinition\n", currFileName, currTok->fPos.Line, type, name ); 
		else
			LogText( "%s(%d) : error: '%s' : redifinition; different basic types\n", currFileName, currTok->fPos.Line, name ); 
		numErrors++;
		return false;
	}
	globalVar = new arg_t;
	globalVar->argClass = ParserShared::STR2ARGCLASS( type );
	arg_t globalVarArg( ARGC_GLOBAL_VAR, globalVar );
	htVars.Set( name, globalVarArg );
	resArg = globalVarArg;
	return true;
}


bool Parser::InitLocalVariable( arg_t& resArg, const char* name, const char* type, const int addr )
{
	//String mangledVarName( MangleVarName( name, deepStack[ blockDeep ] ) );
	
	// проверяем на одноименность существующих
	arg_t *localVar;
	if( htVars.Get( name, &localVar ) ){
		if( vm->funcs[ vm->numFuncs ].localVars[ localVar->addrLocal ].argClass == ParserShared::STR2ARGCLASS( type ) )
			LogText( "%s(%d) : error: '%s %s' : redifinition\n", currFileName, currTok->fPos.Line, type, name ); 
		else
			LogText( "%s(%d) : error: '%s' : redifinition; different basic types\n", currFileName, currTok->fPos.Line, name ); 
		numErrors++;
		return false;
	}


	resArg = arg_t( ARGC_LOCAL_VAR, addr );
	htVars.Set( name,  resArg );

	String stype( type );
	if( '&' == stype[ stype.Length() - 1 ] ){
		stype[ stype.Length() - 1 ] = '\0';
		vm->funcs[ vm->numFuncs ].localVars[ addr ].argClass		= ARGC_REFERENCE;
		vm->funcs[ vm->numFuncs ].localVars[ addr ].addrReference	= new arg_t( StrTypeToArg( stype ) );
	}
	else
		vm->funcs[ vm->numFuncs ].localVars[ addr ] = StrTypeToArg( stype );

	return true;
}


arg_t Parser::StrTypeToArg( const String& stype )
{
	arg_t res;

	if		( stype == "int"	) res.argClass = ARGC_INT;
	else if	( stype == "float"	) res.argClass = ARGC_FLOAT;
	else if	( stype == "bool"	) res.argClass = ARGC_BOOL;
	else if	( stype == "string" ) res.argClass = ARGC_STRING;
	else if	( stype == "void"	) res.argClass = ARGC_VOID;

	//
	// ... для пользовательского типа
	//

	return res;

}


bool Parser::InFunc()const{
	return namespaceStack[ namespaceDeep==0?0:namespaceDeep-1 ].c_str()[0] == '@'?true:false;
}

bool Parser::InClass()const{
	return namespaceStack[ namespaceDeep==0?0:namespaceDeep-1 ].c_str()[0] == '$'?true:false;
}


String Parser::MangleNamespace( const int deep )
{
	String result;
	for( int i=0; i<deep; i++ )
		result += "::" + namespaceStack[i];
	return result;
}


void Parser::InitFunction( const char* uName, const char* type, const int numOvf )
{
	htOverloadFuncs.Set( uName, numOvf + 1 );
	String temp = String( uName ) + "#";
	temp += String::ToString( numOvf );
	htFuncs.Set( temp.c_str(),  vm->numFuncs );
}



String Parser::MangleVarName( const String& name,  const int nmspDeep, const int blockNum )
{	
	String result( MangleNamespace( nmspDeep ) );
	result += "::" + name + "#" + String::ToString( blockNum );
	return result;
}


void Parser::VariableDeclaration( const String& nameStr, const char* type )
{
	arg_t declArg;

	String mangledName( MangleVarName( nameStr, namespaceDeep, deepStack[ blockDeep ] ) );

	//локальная
	if( InFunc() ){
		numVars++;
		InitLocalVariable( declArg, mangledName.c_str(), type, numVars - 1 );
	}
	// глобальная
	else{
		InitGlobalVariable( declArg, mangledName.c_str(), type );
	}

	// инициализация переменной
	if( ParserShared::TOKENSTR( *currTok, 1, TC_SEPARATOR, "=" ) )
	{
		scaner.Read( *currTok );
		PASS2_arith_expr();

		NewInstruction( "=", declArg, argStack.Pop() );
	}
}



void Parser::PASS2_variable_function_decl()
{
	// запоминаем н азвание типа
	String typeStr( currTok->str );

	scaner.Read( *currTok );

	// запоминаем название переменной(или функции)
	String nameStr( currTok->str );

	if( currTok->tokClass != TC_VARIABLE ){
		// error
		return;
	}

	scaner.Read( *currTok );

	// объявление переменной
	if( ParserShared::TOKENSTR( *currTok, 3, TC_SEPARATOR, "=", ",", ";" ) )
	{
		VariableDeclaration( nameStr, typeStr.c_str() );
		
		while( ParserShared::TOKENSTR( *currTok, 1, TC_SEPARATOR, "," ) )
		{
			scaner.Read( *currTok );

			if( currTok->tokClass == TC_VARIABLE )
			{
				nameStr = currTok->str;
				scaner.Read( *currTok );
				VariableDeclaration( nameStr, typeStr.c_str() ); 
			}
			else{
				// error: variable expected
			}
		}
	}

	// объявление функции
	else if( ParserShared::TOKENSTR( *currTok, 1, TC_SEPARATOR, "(" ) && !inFunc )
	{
		numVars = 0;

		scaner.Read( *currTok );
		
		//временное хранилище формальных параметров
		struct varinfo_s{
			String name, type;
		};
		LArray<varinfo_s*> lvArray;

		//считывание формальных параметров
		if( ParserShared::TOKENSTR( *currTok, 5, TC_KEYWORD, "void", "int", "float", "string", "bool" ) )
		{
			lvArray[ numVars ] = new varinfo_s;
			lvArray[ numVars ]->type = currTok->str;

			scaner.Read( *currTok );

			if( ParserShared::TOKENSTR( *currTok, 1, TC_SEPARATOR, "&" ) ){
				lvArray[ numVars ]->type += '&';
				scaner.Read( *currTok );
			}

			if( currTok->tokClass == TC_VARIABLE )
			{
				lvArray[ numVars ]->name = currTok->str;
				numVars++;

				scaner.Read( *currTok );

				while( ParserShared::TOKENSTR( *currTok, 1, TC_SEPARATOR, "," ) )
				{
					scaner.Read( *currTok );

					if( ParserShared::TOKENSTR( *currTok, 5, TC_KEYWORD, "void", "int", "float", "bool", "string" ) )
					{
						lvArray[ numVars ] = new varinfo_s;
						lvArray[ numVars ]->type = currTok->str;

						scaner.Read( *currTok );

						if( ParserShared::TOKENSTR( *currTok, 1, TC_SEPARATOR, "&" ) ){
							lvArray[ numVars ]->type += '&';
							scaner.Read( *currTok );
						}

						if( currTok->tokClass == TC_VARIABLE )
						{
							lvArray[ numVars ]->name = currTok->str;
							numVars++;

							scaner.Read( *currTok );
						}
					}
				}
			}
		}

		if( !ParserShared::TOKENSTR( *currTok, 1, TC_SEPARATOR, ")" ) ){
			LogText( "%s(%d) : error: syntax error : missing ')' before '%s'\n", currFileName, currTok->fPos.Line, currTok->str ); 
			numErrors++;
		}


		// Формирование имени функции с учетом области видимости
		String uName( MangleNamespace( namespaceDeep ) );
		String uNameTemp = uName + "::" + nameStr;
		uName += "::@" + nameStr;

		// проверяем на существование одноименной переменной в этой области видимости
		// может быть только в случае, совпадения имен функции и перемнной в одной 
		// области видимости(не беря в расчет нулевой символ).
		// ... здесь ошибка!!! формируется имя ::::@func#0 вместо ::@func#0
		if( htVars.Get( MangleVarName( uNameTemp, namespaceDeep, deepStack[ blockDeep ] ).c_str() ) ){
			LogText( "%s(%d) : error: '%s' : redefinition; previous definition was 'data variable'", currFileName, currTok->fPos.Line, currTok->str, nameStr.c_str() ); 
			numErrors++;
		}

		// после считывания формальных параметров,
		// проверяем на сущесвтование одноименной функции в области видимости
		// если существуют одноименные функции проверяем на однозначность
		int  *numOvf = 0x0000;
		int  cnum	 = 0;
		bool match	 = false; // флаг совпадения
		if( htOverloadFuncs.Get( uName.c_str(), &numOvf ) )
		{
			String tempuName( uName );

			for( int i=0; i<*numOvf && !match; i++ )
			{
				// добавляем к имени функции номер перегруженности(#i), находим по 
				// этому имени описание функции и проверяем на соответствие типов
				uName += '#' + String::ToString( cnum );
				int *indFun;
				htFuncs.Get( uName.c_str(), &indFun );

				if( vm->funcs[ *indFun ].numFmv == numVars ){
					bool matchParams = true;
					for( int i=0; i<vm->funcs[ *indFun ].numFmv; i++ )
					{
						arg_t argParam;
						if( ARGC_REFERENCE == vm->funcs[ *indFun ].localVars[ i ].argClass )
							argParam.argClass = vm->funcs[ *indFun ].localVars[ i ].addrReference->argClass;
						else
							argParam.argClass = vm->funcs[ *indFun ].localVars[ i ].argClass;

						arg_t argParamFirst;
						StringToArgclass( argParamFirst, lvArray[ i ]->type );

						if( argParam.argClass != argParamFirst.argClass ){
							matchParams = false;
							break;
						}
					}
					if( matchParams )match = true;
				}
				cnum = i+1;
				uName = tempuName;
			}
		}


		if( match ){
			String tempParams;
			for( int i=0; i<numVars; tempParams+=',', i++ )
				tempParams += lvArray[ i ]->type;
			// !!!выводить информацию о перегруженной функции для параметров по ссылке корректно!!!
			tempParams.c_str()[ tempParams.Length()-1 ] = '\0';
			LogText( "error: function '%s %s(%s)' already has a body\n", typeStr.c_str(), nameStr.c_str(), tempParams.c_str() );
			numErrors++;
		}

		// инициализация новой функции!
		// добавляем в стек области видимости пеобразованное название функции
		namespaceStack[ namespaceDeep ] = '@' + nameStr + '#' + String::ToString( cnum );
		InitFunction( uName.c_str(), typeStr.c_str(), numOvf==0x0000?0:*numOvf ); 
		vm->funcs[ vm->numFuncs ].numFmv			= numVars;
		vm->funcs[ vm->numFuncs ].addr				= vm->internalCode->Current();
		vm->funcs[ vm->numFuncs ].retVal.argClass	= ParserShared::STR2ARGCLASS( typeStr );

		namespaceDeep++;

		// заключаем сегмент кода функции в "объезд" джампом
		codesegment_t* jmpAddr = MakeNewInstruction( &VirtualMachine::JMP, 0x0000, 0x0000, 0x0000 );

		// инициализация формальных параметров
		numBlock++;
		blockDeep++;
		deepStack[ blockDeep ] = numBlock;

		if( numVars > 0 ){
			MakeNewInstruction( &VirtualMachine::POP, new arg_t( ARGC_INT, vm->numFuncs ), 0x0000, 0x0000 );
			arg_t ttt;
			for( int i=0; i<numVars; i++ ){
				String mangledName( MangleVarName( lvArray[i]->name, namespaceDeep, deepStack[ blockDeep ] ) );
				InitLocalVariable( ttt, mangledName, lvArray[i]->type.c_str(), i );
				delete lvArray[i];		
			}
		}
		vm->funcs[ vm->numFuncs ].addr = vm->internalCode->codeCurr;

		scaner.Read( *currTok );

		if( ParserShared::TOKENSTR( *currTok, 1, TC_SEPARATOR, "{" ) )
		{
			numBlock--;
			blockDeep--;

			PASS2_expr_seq();

			MakeNewInstruction( &VirtualMachine::RET, new arg_t( vm->funcs[ vm->numFuncs ].retVal ), 0x0000, 0x0000 );
			
			jmpAddr->instr.arg1 = new arg_t( ARGC_POINTER, vm->internalCode->New() );
			vm->funcs[ vm->numFuncs ].addr = jmpAddr;
			vm->numFuncs++;
			namespaceStack[ --namespaceDeep ].Clear();
		}
		else{
		}
	}
	else
	{
		// error
	}
}


void Parser::StringToArgclass( arg_t& res, const String& stype )
{
	String temp( stype );
	if( '&' == temp[ temp.Length() - 1 ] ){
		temp[ temp.Length() - 1 ] = '\0';
	}

	// базовые типы
	if		( "void"	== temp ){ res.argClass = ARGC_VOID;	return; }
	else if	( "int"		== temp ){ res.argClass = ARGC_INT;		return; }
	else if	( "float"	== temp ){ res.argClass = ARGC_FLOAT;	return; }
	else if	( "bool"	== temp ){ res.argClass = ARGC_BOOL;	return; }
	else if	( "string"	== temp ){ res.argClass = ARGC_STRING;	return; }

	//
	// для пользовательских типов
	//
	//
}



void Parser::PASS2_expr_seq()
{
	if( ParserShared::TOKENSTR( *currTok, 1, TC_SEPARATOR, "{" ) )
	{
		numBlock++;
		blockDeep++;
		deepStack[ blockDeep ] = numBlock;

		scaner.Read( *currTok );

		PASS2_expr();

		while( ParserShared::TOKENSTR( *currTok, 1, TC_SEPARATOR, ";" ) )
		{		
			scaner.Read( *currTok );
			PASS2_expr();
		}

		if( !ParserShared::TOKENSTR( *currTok, 1, TC_SEPARATOR, "}" ) ){
			// error "\nblock ERROR: expected } \n
		}
		currTok->Set( TC_SEPARATOR, ";" );
		blockDeep--;
	}
}


void Parser::PASS2_return()
{
	if( InFunc() )
	{
		scaner.Read( *currTok );
		if( ParserShared::TOKENSTR( *currTok, 1, TC_SEPARATOR, ";" ) )
		{
			if( ARGC_VOID != vm->funcs[ vm->numFuncs ].retVal.argClass ){
				LogText( "error: '%s' : function must return a value\n", "TEMPORARY" );		
				numErrors++;
			}
		}
		else
		{
			PASS2_arith_sequence();

			arg_t ret_arg( argStack.Pop() );

			if( ARGC_VOID == vm->funcs[ vm->numFuncs ].retVal.argClass ){
				LogText( "error: '%s' : 'void' function returning a value\n", "TEMPORARY" );
				numErrors++;
			}

			if( 555 == ParserShared::GetNarrowBaseType( GetTypeArg( ret_arg ), vm->funcs[ vm->numFuncs ].retVal ) ){
				LogText( "error: 'return' : cannot convert from '%s' to '%s'\n", "TEMPORARY", "TEMPORARY" );
				numErrors++;
			}

			MakeNewInstruction( &VirtualMachine::RET,  vm->internalCode->NewArg( ret_arg ), 0x0000, 0x0000 );
		}
	}
	else
	{
		LogText( "%s(%d) : error: syntax error : 'return'\n", currFileName, currTok->fPos.Line ); 
		numErrors++;
	}
}



void Parser::PASS2_expr()
{
	if( ParserShared::TOKENSTR( *currTok, 5, TC_KEYWORD, "int", "float", "void", "string", "bool" ) )
	{
		PASS2_variable_function_decl();
	}
	else if( ParserShared::TOKENSTR( *currTok, 1, TC_KEYWORD, "if" ) )
	{
		PASS2_if_expr();
	}
	else if( ParserShared::TOKENSTR( *currTok, 1, TC_KEYWORD, "while" ) )
	{
		PASS2_while_expr();
	}
	else if( ParserShared::TOKENSTR( *currTok, 1, TC_KEYWORD, "do" ) )
	{
		PASS2_do_while_expr();
	}
	else if( ParserShared::TOKENSTR( *currTok, 1, TC_KEYWORD, "for" ) )
	{
		PASS2_for_expr();
	}
	else if( ParserShared::TOKENSTR( *currTok, 1, TC_KEYWORD, "return" ) )
	{
		PASS2_return();
	}
	else if( ParserShared::TOKENSTR( *currTok, 1, TC_SEPARATOR, "{" ) )
	{
		PASS2_expr_seq();
	}
	else if( ParserShared::TOKENSTR( *currTok, 2, TC_KEYWORD, "break", "continue" ) )
	{
		PASS2_break_continue();
	}
	else
	{
		PASS2_arith_sequence();
		argStack.Pop();
	}
}


void Parser::PASS2_term_initialization()
{
	if( ParserShared::TOKENSTR( *currTok, 5, TC_KEYWORD, "int", "float", "void", "bool", "string" ) )
	{
		String typeStr = currTok->str;

		scaner.Read( *currTok );
		String nameStr = currTok->str;
		scaner.Read( *currTok );

		VariableDeclaration( nameStr.c_str(), typeStr.c_str() );
	}
	else
	{
		PASS2_arith_expr();
	}
}

void Parser::PASS2_break_continue()
{
	cfptr op;
	if( !loopDeep ){
	    LogText( "error: illegal %s", currTok->str );
	    numErrors++;
	}
	else if( !strcmp( currTok->str, "break" ) )
		op = &VirtualMachine::BREAK;
	else // "continue"
		op = &VirtualMachine::CONTINUE;

	MakeNewInstruction( op, 0x0000, 0x0000, 0x0000 );

	scaner.Read( *currTok );
	if( !ParserShared::TOKENSTR( *currTok, 1, TC_SEPARATOR, ";" ) ){
		LogText( "error: syntax error : missing ';' before '%s'", currTok->str );
		numErrors++;
	}
}


void Parser::SetBreakContinue( const codesegment_t* loopBegin,  
							   const codesegment_t* loopEnd,
							   const codesegment_t* pBreak,
							   const codesegment_t* pContinue )
{
	codesegment_t* p = const_cast<codesegment_t*>(loopBegin);
	while( p!=loopEnd ){
		if(      p->instr.opf == &VirtualMachine::BREAK )
			vm->internalCode->SetInstruction( p, &VirtualMachine::JMP, new arg_t( ARGC_POINTER, const_cast<codesegment_t*>(pBreak ) ), 0x0000 );
		else if( p->instr.opf == &VirtualMachine::CONTINUE )
			vm->internalCode->SetInstruction( p, &VirtualMachine::JMP, new arg_t( ARGC_POINTER, const_cast<codesegment_t*>(pContinue) ), 0x0000 );		
		p = p->next;
	}
}


void Parser::PASS2_if_expr()
{
	if( ParserShared::TOKENSTR( *currTok, 1, TC_KEYWORD, "if" ) )
	{
		scaner.Read( *currTok );

		if( !ParserShared::TOKENSTR( *currTok, 1, TC_SEPARATOR, "(" ) ){
			// error '(' expected
			return;
		}

		scaner.Read( *currTok );

		numBlock++;
		blockDeep++;
		deepStack[ blockDeep ] = numBlock;

		// вместо:
		//PASS2_term_initialization();		
		// эта переменная должна быть видна в блоке else
		bool	if_init_block = false;
		String	nameStr;
		arg_t	declArg;

		if( ParserShared::TOKENSTR( *currTok, 5, TC_KEYWORD, "int", "float", "void", "bool", "string" ) )
		{
			if_init_block = true;
			String typeStr = currTok->str;

			scaner.Read( *currTok );
			nameStr = currTok->str;

			scaner.Read( *currTok );

			String mangledVarName = MangleVarName( nameStr, namespaceDeep, deepStack[ blockDeep ] );

			//локальная
			if( InFunc() ){
				numVars++;				
				InitLocalVariable( declArg, mangledVarName.c_str(), typeStr.c_str(), numVars - 1 );
			}
			// глобальная
			else{
				InitGlobalVariable( declArg, mangledVarName.c_str(), typeStr.c_str() );
			}

			// инициализация переменной
			if( ParserShared::TOKENSTR( *currTok, 1, TC_SEPARATOR, "=" ) )
			{
				scaner.Read( *currTok );
				PASS2_arith_expr();

				NewInstruction( "=", declArg, argStack.Pop() );

			}
		}
		else
		{
			PASS2_arith_expr();
		}

		if( !ParserShared::TOKENSTR( *currTok, 1, TC_SEPARATOR, ")" ) ){
			// error ')' expected
			return;
		}
		arg_t *ifArg = vm->internalCode->NewArg( argStack.Pop() );

		codesegment_t*  jmpfAddr = MakeNewInstruction( &VirtualMachine::NOP, 0x0000, 0x0000, 0x0000 );
		scaner.Read( *currTok );

		bool block = false;
		if( ParserShared::TOKENSTR( *currTok, 1, TC_SEPARATOR, "{" ) ){
			numBlock--;
			blockDeep--;
			block = true;
		}

		PASS2_expr();

		if( !block )
			blockDeep--;

		long pos = ftell( currFile );
		scaner.Read( *currTok );

		if( ParserShared::TOKENSTR( *currTok, 1, TC_KEYWORD, "else" ) )
		{
			numBlock++;
			blockDeep++;
			deepStack[ blockDeep ] = numBlock;

			if( if_init_block )
				htVars.Set( MangleVarName( nameStr, namespaceDeep, deepStack[ blockDeep ] ), declArg );

			codesegment_t*  jmpAddr = MakeNewInstruction( &VirtualMachine::NOP, 0x0000, 0x0000, 0x0000 );
			scaner.Read( *currTok );

			bool block = false;
			if( ParserShared::TOKENSTR( *currTok, 1, TC_SEPARATOR, "{" ) ){
				numBlock--;
				blockDeep--;
				block = true;
			}
			
			PASS2_expr();

			if( !block )
				blockDeep--;

			codesegment_t *endif = vm->internalCode->New();
			vm->internalCode->SetInstruction( jmpfAddr, vm->ArJMPF[ ifArg->argClass ], ifArg, new arg_t( ARGC_POINTER, jmpAddr->next ) );
			vm->internalCode->SetInstruction( jmpAddr, &VirtualMachine::JMP, new arg_t( ARGC_POINTER, endif ), 0x0000 );
		}
		else{
			codesegment_t *endif = vm->internalCode->New();
			vm->internalCode->SetInstruction( jmpfAddr, vm->ArJMPF[ ifArg->argClass ], ifArg, new arg_t( ARGC_POINTER, endif ) );
			fseek( currFile, pos, SEEK_SET );
			currTok->Set( TC_SEPARATOR, ";" );
		}
	}
}


void Parser::PASS2_while_expr()
{
	if( ParserShared::TOKENSTR( *currTok, 1, TC_KEYWORD, "while" ) )
	{
		scaner.Read( *currTok );

		numBlock++;
		blockDeep++;
		deepStack[ blockDeep ] = numBlock;

		if( !ParserShared::TOKENSTR( *currTok, 1, TC_SEPARATOR, "(" ) ){
			// error '(' expected
			return;
		}
		scaner.Read( *currTok );
		codesegment_t *whileAddr = vm->internalCode->New();

		PASS2_term_initialization();
		arg_t *whileArg = vm->internalCode->NewArg( argStack.Pop() );

		codesegment_t *jmpfAddr = MakeNewInstruction( &VirtualMachine::NOP, 0x0000, 0x0000, 0x0000 );
		
		if( !ParserShared::TOKENSTR( *currTok, 1, TC_SEPARATOR, ")" ) ){
			// error ')' expected
			return;
		}

		scaner.Read( *currTok );

		bool block = false;
		if( ParserShared::TOKENSTR( *currTok, 1, TC_SEPARATOR, "{" ) ){
			numBlock--;
			blockDeep--;
			block = true;
		}

		if( !ParserShared::TOKENSTR( *currTok, 1, TC_SEPARATOR, ";" ) ){
			loopDeep++;
			PASS2_expr();
			loopDeep--;
		}

		if( !block )
			blockDeep--;


		MakeNewInstruction( &VirtualMachine::JMP, new arg_t( ARGC_POINTER, whileAddr ), 0x0000, 0x0000 );
		codesegment_t *endwhile = vm->internalCode->New();
		vm->internalCode->SetInstruction( jmpfAddr, vm->ArJMPF[ whileArg->argClass ], whileArg, new arg_t( ARGC_POINTER, endwhile ) );

		SetBreakContinue( jmpfAddr, endwhile, endwhile, whileAddr );
	}				
}


void Parser::PASS2_do_while_expr()
{
	if( ParserShared::TOKENSTR( *currTok, 1, TC_KEYWORD, "do" ) )
	{
		codesegment_t *doAddr = vm->internalCode->New();
		scaner.Read( *currTok );

		loopDeep++;
		PASS2_expr_seq();
		loopDeep--;

		scaner.Read( *currTok );
		if( !ParserShared::TOKENSTR( *currTok, 1, TC_KEYWORD, "while" ) ){
			// error
			return;
		}
		scaner.Read( *currTok );
		if( !ParserShared::TOKENSTR( *currTok, 1, TC_SEPARATOR, "(" ) ){
			// error
			return;
		}
		scaner.Read( *currTok );

		codesegment_t* addrterm = vm->internalCode->codeCurr;

		int doblock = deepStack[ blockDeep ];
		blockDeep++;
		deepStack[ blockDeep ] = doblock;

		PASS2_arith_expr();

		if( !ParserShared::TOKENSTR( *currTok, 1, TC_SEPARATOR, ")" ) ){
			// error
			return;
		}

		blockDeep--;

		arg_t *jmptArg = vm->internalCode->NewArg( argStack.Pop() );
		codesegment_t* enddo = MakeNewInstruction( vm->ArJMPT[ jmptArg->argClass ], jmptArg, new arg_t( ARGC_POINTER, doAddr ), 0x0000 );
		vm->internalCode->New();
		scaner.Read( *currTok );

		SetBreakContinue( doAddr, enddo, enddo->next, addrterm );
	}
}





void Parser::PASS2_for_initialization()
{
	if( ParserShared::TOKENSTR( *currTok, 5, TC_KEYWORD, "int", "float", "void", "bool", "string" ) )
	{
		String typeStr = currTok->str;

		scaner.Read( *currTok );
		if( currTok->tokClass != TC_VARIABLE ){
			// error: empty declaration
		}
		else
		{
			String nameStr = currTok->str;
			scaner.Read( *currTok );
			VariableDeclaration( nameStr.c_str(), typeStr.c_str() );
			
			while( ParserShared::TOKENSTR( *currTok, 1, TC_SEPARATOR, "," ) )
			{
				scaner.Read( *currTok );

				if( currTok->tokClass == TC_VARIABLE )
				{
					nameStr = currTok->str;
					scaner.Read( *currTok );
					VariableDeclaration( nameStr.c_str(), typeStr.c_str() ); 
				}
			}
		}
	}
	else
	{
		PASS2_arith_sequence();
	}
}

void Parser::PASS2_for_expr()
{
	if( ParserShared::TOKENSTR( *currTok, 1, TC_KEYWORD, "for" ) )
	{
		scaner.Read( *currTok );

		numBlock++;
		blockDeep++;
		deepStack[ blockDeep ] = numBlock;

		if( !ParserShared::TOKENSTR( *currTok, 1, TC_SEPARATOR, "(" ) ){
			// error '(' expected
			return;
		}
		scaner.Read( *currTok );

		PASS2_for_initialization();

		if( !ParserShared::TOKENSTR( *currTok, 1, TC_SEPARATOR, ";" ) ){
			// error ';' expected
			return;
		}
		codesegment_t *a2Addr = vm->internalCode->Current();
		scaner.Read( *currTok );

		codesegment_t *jmpfAddr = a2Addr;	
		arg_t		  *jmpfArg;
		bool forever = true;

		if( !ParserShared::TOKENSTR( *currTok, 1, TC_SEPARATOR, ";" ) )
		{
			forever = false;
			PASS2_arith_sequence();

			jmpfAddr = MakeNewInstruction( &VirtualMachine::NOP, 0x0000, 0x0000, 0x0000 );
			jmpfArg	 = vm->internalCode->NewArg( argStack.Pop() );


			if( !ParserShared::TOKENSTR( *currTok, 1, TC_SEPARATOR, ";" ) ){
				// error ';' expected
				return;
			}
		}

		scaner.Read( *currTok );

		PASS2_arith_sequence();
		codesegment_t* incAddr = jmpfAddr->next;
		codesegment_t *jmpAddr = MakeNewInstruction( &VirtualMachine::JMP, 0x0000, 0x0000, 0x0000 );

		if( !ParserShared::TOKENSTR( *currTok, 1, TC_SEPARATOR, ")" ) ){
			// error ')' expected
			return;
		}

		scaner.Read( *currTok );

		bool block = false;
		if( ParserShared::TOKENSTR( *currTok, 1, TC_SEPARATOR, "{" ) ){
			numBlock--;
			blockDeep--;
			block = true;
		}

		if( !ParserShared::TOKENSTR( *currTok, 1, TC_SEPARATOR, ";" ) ){
			loopDeep++;
			PASS2_expr();
			loopDeep--;
		}

		if( !block )
			blockDeep--;

		if( jmpAddr->next ){
			jmpAddr->next->prev = jmpfAddr;
			vm->internalCode->codeCurr->next = jmpfAddr->next;

			if( !vm->internalCode->codeCurr->instr.opf )
				vm->internalCode->codeCurr->instr.opf = &VirtualMachine::NOP;

			jmpfAddr->next->prev = vm->internalCode->codeCurr;
			jmpfAddr->next = jmpAddr->next;
			jmpAddr->next = 0x0000;
			vm->internalCode->MoveTo( jmpAddr );
		}

		codesegment_t *exprBeginAddr = jmpAddr;

		codesegment_t *endforAddr = vm->internalCode->New();
		if( !forever )
			vm->internalCode->SetInstruction( jmpfAddr, vm->ArJMPF[ jmpfArg->argClass ], jmpfArg, new arg_t( ARGC_POINTER, endforAddr ) );
		 vm->internalCode->SetInstruction( jmpAddr, &VirtualMachine::JMP, new arg_t( ARGC_POINTER, a2Addr->next ), 0x0000 );

		 SetBreakContinue( jmpfAddr->next, endforAddr, endforAddr, incAddr );
	}
}


void Parser::PASS2_arith_sequence()
{
	PASS2_arith_expr();

	int ns = 0;
	while( ParserShared::TOKENSTR( *currTok, 1, TC_SEPARATOR, "," ) )
	{
		scaner.Read( *currTok );
		PASS2_arith_expr();
		ns++;
	}

	arg_t top( argStack.Pop() );
	for( int i=0; i<ns; i++ ){
		argStack.Pop();
	}
	argStack.Push( top );
}


void Parser::PASS2_arith_expr()
{
	PASS2_opp1();

	int ina=0;
	LArray<String> op;
	while( ParserShared::TOKENSTR( *currTok, 9, TC_SEPARATOR, "=", "+=", "-=", "*=", "/=", "&=", "|=", "^=", "%=" ) )
	{
		op[ ina++ ] = currTok->str ;
		scaner.Read( *currTok );
		PASS2_opp1();
	}

	for( int i=0; i<ina; i++ ){
		arg_t arg2( argStack.Pop() );
		arg_t arg1( argStack.Pop() );

		if( arg1.argClass != ARGC_LOCAL_VAR && 
			arg1.argClass != ARGC_GLOBAL_VAR )
		{
			LogText( "error: '%s' : left operand must be l-value\n", op[i].c_str() );
			numErrors++;
		}

		if( ParserShared::STRSTRSTR( op[i].c_str(), 8, "+=","-=","*=","/=","&=","|=","^=","%=" ) ){
			op[i].c_str()[ op[i].Length()-1 ] = '\0';
			NewInstruction( op[i], arg1, arg2 );
			arg2 = argStack.Pop();
		}
		NewInstruction( "=", arg1, arg2 );
		argStack.Pop();
		argStack.Push( arg1 );
	}
}


void Parser::PASS2_opp1()
{
	PASS2_opp2();

	while( ParserShared::TOKENSTR( *currTok, 6, TC_SEPARATOR, "==", "<=", ">=", "!=", "<", ">" ) )
	{
		String op = currTok->str;
		scaner.Read( *currTok );
		PASS2_opp2();
		NewInstruction( op, argStack.Pop(), argStack.Pop() );
	}
}



void Parser::PASS2_opp2()
{
	PASS2_opp3();

	while( ParserShared::TOKENSTR( *currTok, 5, TC_SEPARATOR, "+", "-", "|", "||", "^" ) )
	{
		String op = currTok->str;
		scaner.Read( *currTok );
		PASS2_opp3();
		NewInstruction( op, argStack.Pop(), argStack.Pop() );
	}
}



void Parser::PASS2_opp3()
{
	PASS2_unary();

	while( ParserShared::TOKENSTR( *currTok, 5, TC_SEPARATOR, "*", "/", "&", "&&", "%" ) )
	{
		String op = currTok->str;
		scaner.Read( *currTok );
		PASS2_unary();
		NewInstruction( op, argStack.Pop(), argStack.Pop() );
	}
}



void Parser::PASS2_unary()
{
	String op;
	if( ParserShared::TOKENSTR(*currTok, 3, TC_SEPARATOR, "+", "-", "!" ) ){
		op = "u" + String( currTok->str );
		scaner.Read( *currTok );
	}

	PASS2_double_prefix();

	if( !op.IsEmpty() ){
		if( op != "u+" )
			NewInstruction( op, argStack.Pop(), arg_t() );
	}
}


void Parser::PASS2_double_prefix()
{
	bool flag = false;
	String opStr;
	if( ParserShared::TOKENSTR( *currTok, 2, TC_SEPARATOR, "++", "--" ) )
	{
		flag = true;
		opStr = currTok->str;
		scaner.Read( *currTok );
	}

	PASS2_double_suffix();	

	if( flag )
	{
		arg_t lvalArg = argStack.Pop();

		NewInstruction( String( opStr[0] ).c_str(), lvalArg, arg_t( ARGC_INT, 1 ) );

		if( lvalArg.argClass != ARGC_LOCAL_VAR && 
			lvalArg.argClass != ARGC_GLOBAL_VAR )
		{
			LogText( "error: '%s' needs l-value\n", opStr.c_str() );
			numErrors++;
		}

		NewInstruction( "=", lvalArg, argStack.Pop() );

		argStack.Pop();
		argStack.Push( lvalArg );
	}
}

void Parser::PASS2_double_suffix()
{
	PASS2_factor();

	if( ParserShared::TOKENSTR( *currTok, 2, TC_SEPARATOR, "++", "--" ) )
	{
		String opStr( currTok->str );

		arg_t lvalArg			= argStack.Pop();

		if( lvalArg.argClass != ARGC_LOCAL_VAR && 
			lvalArg.argClass != ARGC_GLOBAL_VAR )
		{
			LogText( "error: '%s' needs l-value\n", opStr.c_str() );
			numErrors++;
		}

		arg_t tempArg( ARGC_GLOBAL_VAR, new arg_t( GetTypeArg( lvalArg ) ) );

		NewInstruction( "=", tempArg, lvalArg );
		arg_t temp1 = argStack.Pop();

		NewInstruction( String( opStr[0] ).c_str(), temp1, arg_t( ARGC_INT, 1 ) );
		NewInstruction( "=", lvalArg, argStack.Pop() );
		argStack.Pop();
		argStack.Push( temp1 );

		scaner.Read( *currTok );
	}
}



void Parser::PASS2_factor()
{
	if( ParserShared::TOKENSTR( *currTok, 1, TC_SEPARATOR, "(" ) ){
		scaner.Read( *currTok );
		PASS2_arith_sequence();
		if( !ParserShared::TOKENSTR( *currTok, 1, TC_SEPARATOR, ")" ) ){
			// error: ')' expected;
		}
		scaner.Read( *currTok );
		return;
	}

	if( currTok->tokClass == TC_CONSTANT_INT    || 
		currTok->tokClass == TC_CONSTANT_FLOAT  || 
		currTok->tokClass == TC_STRING )
	{
		argStack.Push( ParserShared::TOKEN2ARG( *currTok ) );
		scaner.Read( *currTok );
		return;
	}

	if( currTok->tokClass == TC_VARIABLE )
	{
		String nameStr( currTok->str );

		scaner.Read( *currTok );

		// функция
		if( ParserShared::TOKENSTR( *currTok, 1, TC_SEPARATOR, "(" ) )
		{
			int numParams = 0;
			scaner.Read( *currTok );
			LArray<arg_t> params;

			if( !ParserShared::TOKENSTR( *currTok, 1, TC_SEPARATOR, ")" ) )
			{
				PASS2_arith_expr();
				params[ numParams++ ] = argStack.Pop();

				while( ParserShared::TOKENSTR( *currTok, 1, TC_SEPARATOR, "," ) )
				{
					scaner.Read( *currTok );
					PASS2_arith_expr();
					params[ numParams++ ] = argStack.Pop();
				}

				if( !ParserShared::TOKENSTR( *currTok, 1, TC_SEPARATOR, ")" ) ){
					// error
				}
			}

			scaner.Read( *currTok );

			int funcInd;
			if( MatchFunction( funcInd, nameStr.c_str(), numParams, params.Data() ) )
			{
				for( int i = numParams - 1; i >= 0; i-- ){
					arg_t *pusharg = vm->internalCode->NewArg( params[i] );
					MakeNewInstruction( vm->ArPUSH[ pusharg->argClass ], pusharg, 0x0000, 0x0000 );
				}
				// рекурсивный вызов функции предполагает хранение результата вызова в стеке.
				// Значит для каждого вызова ф-ии создаем переменную 
				// хранящую результат выполнения.

				arg_t *resArg;
				if( InFunc() ){
					resArg = new arg_t( ARGC_LOCAL_VAR, numVars );
					vm->funcs[ vm->numFuncs ].localVars[ numVars ] = vm->funcs[ funcInd ].retVal;
					numVars++;
				}
				else{
					resArg = new arg_t( vm->funcs[ funcInd ].retVal );
				}	

				codesegment_t* addrInstr = MakeNewInstruction( &VirtualMachine::CALL, new arg_t( ARGC_INT, funcInd ), 0x0000, resArg );
				argStack.Push( arg_t( ARGC_POINTER, addrInstr ) );
			}
		}
		// переменная
		else
		{		
			arg_t varArg;
			if( MatchVariable( varArg, nameStr.c_str() ) ){
				argStack.Push( varArg );
			}
		}
		return;
	}
}



bool Parser::MatchFunction( int& funcInd, const char* nameStr, const int numParams, const arg_t* params )
{
	// Доступ только из области функции, для области глобальных 
	// объявлений[0], и области текущего класса[namespaceDeep-1]				
	String mangledFuncName = MangleNamespace( namespaceDeep?namespaceDeep-1:0 ) + "::@" + nameStr;

	int *numOverloadedFuncs;
	if( !htOverloadFuncs.Get( mangledFuncName.c_str(), &numOverloadedFuncs ) ){
		LogText( "error: '%s': identifier not found\n", nameStr );
		numErrors++;
		return false;
	}


	int *indFunc;
	int errParam;

	// существует одна функция
	if		( 1 == *numOverloadedFuncs )
	{
		htFuncs.Get( mangledFuncName + "#0", &indFunc );

		if( numParams == vm->funcs[ *indFunc ].numFmv )
		{
			if( NOCOMPATIBLE_TYPES == CorrelateFuncParameters( errParam, *indFunc, numParams, params ) )
			{
				LogText( "error: '%s' : cannot convert parameter %d from '%s' to '%s'\n", 
					nameStr, 
					errParam,
					ArgclassToString( params[ errParam-1 ] ).c_str(), 
					ArgclassToString( vm->funcs[ *indFunc ].localVars[ errParam-1 ] ).c_str() );
				numErrors++;
				return false;
			}
			else{
				funcInd = *indFunc;
				return true;
			}
		}
		else
		{
			LogText( "error: '%s' : function does not take %d arguments\n", nameStr, numParams );
			numErrors++;
			return false;
		}
	}

	// несколько перегруженных
	else if	( 1 <  *numOverloadedFuncs )
	{
		bool errNOFTA = true;
		bool errNOCAT = true;

		int numAmbiguous = 0;
		int max_nwp = -2147483648;

		for( int i=0; i<*numOverloadedFuncs; i++ )
		{
			String tempStr( mangledFuncName + '#' + String::ToString(i) );
			htFuncs.Get( tempStr.c_str(), &indFunc );

			if( numParams == vm->funcs[ *indFunc ].numFmv )
			{
				errNOFTA = false;
				int	nwp = CorrelateFuncParameters( errParam, *indFunc, numParams, params );

				if( nwp != NOCOMPATIBLE_TYPES )
				{
					errNOCAT = false;					

					if( UNAMBIGUOUS_TYPES == nwp	){
						funcInd = i;
						return true;
					}
					else if( nwp > max_nwp ){
						max_nwp = nwp;
						funcInd = i;
						numAmbiguous = 1;
					}
					else if( nwp == max_nwp ){
						++numAmbiguous;
					}
				}
			}
		}

		if( errNOFTA ){
			LogText( "error: '%s' : no overloaded function takes %d arguments\n", nameStr, numParams );
			numErrors++;
			return false;
		}

		if( errNOCAT ){
			LogText( "error: '%s' none of the %d overloads could convert all the argument types\n", nameStr, *numOverloadedFuncs );
			numErrors++;
			return false;
		}

		if( numAmbiguous > 1 ){
			LogText("error: '%s': %d overloads have similar conversions\n", nameStr, numAmbiguous );
			numErrors++;
			return false;
		}

		return true;
	}
}


int Parser::GetTypeNarrow( const arg_t& arg1, const arg_t& arg2 )
{
	if( IsBaseType( arg1 ) && IsBaseType( arg1 ) )
		return ParserShared::GetNarrowBaseType( arg1, arg2 );

	return NOCOMPATIBLE_TYPES;
}


bool Parser::IsLValue( const arg_t& arg ){
	if( ARGC_LOCAL_VAR  == arg.argClass ||
		ARGC_GLOBAL_VAR == arg.argClass )
	{
		return true;
	}

	return false;
}


// возващает коэфициент сужения/расширения
int Parser::CorrelateFuncParameters( int& errParam, const int indFunc, const int numParams, const arg_t* params )
{
	bool unambiguous = true;
	int res = 0;
	errParam = -1;

	for( int j=0; j<numParams; j++ )
	{
		int nar = GetTypeNarrow( GetTypeArg( params[ j ] ),  
								 GetTypeArg( vm->funcs[ indFunc ].localVars[ j ] ) );

		bool islvalue = false;
		if( IsLValue( params[j] ) )
			islvalue = true;

		bool isRefParam = false;
		if( ARGC_REFERENCE == vm->funcs[ indFunc ].localVars[ j ].argClass )
			isRefParam = true;

		bool noErrRef = true;
		if( isRefParam ){
			if( !islvalue )
				noErrRef = false;
			else if( nar )
				noErrRef = false;
		}
												
		if( nar != NOCOMPATIBLE_TYPES && noErrRef )
		{
			if( nar != 0 ){
				unambiguous = false;
				res += nar;
			}
		}
		else
		{
			errParam = j+1;
			return NOCOMPATIBLE_TYPES;
		}
	}

	if( unambiguous ) return UNAMBIGUOUS_TYPES;

	return res;
}


String Parser::ArgclassToString( const arg_t& arg )
{
	arg_t typeArg = GetTypeArg( arg );

	String res;

	switch( typeArg.argClass )
	{
	case ARGC_VOID:		res = "void";	break;
	case ARGC_INT:		res = "int";	break;
	case ARGC_FLOAT:	res = "float";	break;
	case ARGC_BOOL:		res = "bool";	break;
	case ARGC_STRING:	res = "string"; break;
	}

	if( ARGC_REFERENCE == arg.argClass )
		res += " &";

	//
	// для ARGC_USERCLASS
	//

	return res;
}



bool Parser::MatchVariable( arg_t& a, const char* varName )
{
	arg_t *varArg;
	// поиск переменной в локальной области
	for( int i = blockDeep; i >= 0; i-- )
		if( htVars.Get( MangleVarName( String( varName ), namespaceDeep, deepStack[i] ), &varArg ) ){
			a = *varArg;
			return true;
		}

	// поиск в глобальной области
	for( int i = blockDeep; i >= 0; i-- )
		if( htVars.Get( MangleVarName( String( varName ), 0, deepStack[i] ), &varArg ) ){
			a = *varArg;
			return true;
		}
	// поиск переменной в глобальной области

	// поиск в области класса
	//...

	// поиск в глобальной области
	//String globVarName = String("::") + varName;
	//if( htVars.Get( globVarName.c_str(), &varArg ) ){
	//	a = *varArg;
	//	return true;
	//}

	LogText( "%s(%d) : error: '%s' : undeclared identifier\n", currFileName, currTok->fPos.Line, varName ); 
	numErrors++;
	return false;
}



//////////////////////////////////////////////////////
void Parser::PrintArg( const arg_t* arg ){
	if( arg )
	if( arg->argClass == ARGC_POINTER				) LogText("0x%x", arg->addrInstruction );
	else if( arg->argClass == ARGC_INT				) LogText("%di", arg->valInt );
	else if( arg->argClass == ARGC_FLOAT			) LogText("%ff", arg->valFloat );
	else if( arg->argClass == ARGC_STRING			) LogText("'%ss'", arg->valStr );
	else if( arg->argClass == ARGC_LOCAL_VAR		) LogText("[%d]", arg->addrLocal );
	else if( arg->argClass == ARGC_GLOBAL_VAR		) LogText("[0x%x]", arg->addrGlobal );
}

void Parser::PrintArgClass( const arg_t* arg ){
	if( arg )
	if( arg->argClass == ARGC_POINTER				) LogText("ARGC_POINTER" );
	else if( arg->argClass == ARGC_VOID				) LogText("ARGC_VOID" );
	else if( arg->argClass == ARGC_INT				) LogText("ARGC_INT" );
	else if( arg->argClass == ARGC_FLOAT			) LogText("ARGC_FLOAT" );
	else if( arg->argClass == ARGC_BOOL				) LogText("ARGC_BOOL" );
	else if( arg->argClass == ARGC_STRING			) LogText("ARGC_STRING" );
	else if( arg->argClass == ARGC_LOCAL_VAR		) LogText("ARGC_LOCAL_VAR" );
	else if( arg->argClass == ARGC_GLOBAL_VAR		) LogText("ARGC_GLOBAL_VAR");
}

void Parser::PrintOp( const cfptr op )
{
	if		(  op == &VirtualMachine::NOP			)	LogText("'nop'");
	else if	(  op == &VirtualMachine::JMP			)	LogText("'jmp'");
	else if	(  op == &VirtualMachine::CALL			)	LogText("'call'");
	else if	(  op == &VirtualMachine::RET			)	LogText("'ret'");
	else if	(  op == &VirtualMachine::POP			)	LogText("'pop'");
	else 
		LogText("0x%x", op);
}



void Parser::PrintVM()
{
	codesegment_t* pp = vm->internalCode->Begin();
	while( pp->next ){
		LogText("0x%x : ", pp );
		PrintOp( pp->instr.opf );
		LogText(" arg1(");
		PrintArg( pp->instr.arg1 );
		LogText(") arg2(");
		PrintArg( pp->instr.arg2 );
		LogText(") res(");
		PrintArg( pp->instr.res );
		LogText(")\n");
		pp = pp->next;
	}

}