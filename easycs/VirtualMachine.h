#ifndef VIRTULAMACHINE
#define VIRTULAMACHINE


#include "InternalCode.h"
#include "Stack.h"

class ParserShared;
class Parser;
class VMEasycs;

/*
==================================

	Easycs Virtual Machine

==================================
*/

//запись активации
struct activationrecord_s{	
	int				numFmv;     // кол-во формальных
	int				numVars;	// кол-во локальных и формальных переменных
	arg_t			*localVars;	// массив локальных переменных
	arg_t			retVal;		// сохраненное значение
	codesegment_t	*addrCall;	// адрес возврата
	codesegment_t	*addr;		// адрес вызываемой подпрограммы
};


class VirtualMachine
{
public:
	VirtualMachine(){
		topFrame = 0;
		topArg   = 0;
		internalCode = new InternalCode;
	};
	virtual ~VirtualMachine(){
		delete[] funcs;
		delete internalCode;
	};

protected:
	friend Parser;
	friend ParserShared;
	friend VMEasycs;

	// указатель на внутреннее предсдавление кода
	InternalCode	*internalCode;

	int					topFrame, 
						topArg;
	arg_t*				argStack[1024];		// runtime стек аргументов
	activationrecord_s	frameStack[1024];	// runtime стек записей активации

	// массив экземпл€ров функций. ¬ызов функции 
	// добавл€ет в стек фреймов экземпл€р вызываемой ф-ии
	int	numFuncs;
	activationrecord_s *funcs;


	static const cfptr MxPLUS			[6][6];
	static const cfptr MxMINUS			[6][6];
	static const cfptr MxSTAR			[6][6];
	static const cfptr MxSLASH		    [6][6];
	static const cfptr MxPERCENT		[6][6];
	static const cfptr MxASSIGN			[6][6];
	static const cfptr MxASSIGNASSIGN	[6][6];
	static const cfptr MxXOR			[6][6];
	static const cfptr MxOR				[6][6];
	static const cfptr MxOROR			[6][6];
	static const cfptr MxAND			[6][6];
	static const cfptr MxANDAND			[6][6];
	static const cfptr MxMORE			[6][6];
	static const cfptr MxMOREASSIGN		[6][6];
	static const cfptr MxLESS			[6][6];
	static const cfptr MxLESSASSIGN		[6][6];
	static const cfptr MxEXCLAMASSIGN	[6][6];

	static const cfptr ArUNARYMINUS		[6];
	static const cfptr ArUNARYEXCLAM	[6];
	static const cfptr ArJMPF			[6];
	static const cfptr ArJMPT			[6];
	static const cfptr ArPUSH			[6];

	void PLUS_error							(arg_t*, arg_t*, arg_t*);
	void PLUS_INT_INT						(arg_t*, arg_t*, arg_t*);
	void PLUS_INT_FLOAT						(arg_t*, arg_t*, arg_t*);
	void PLUS_INT_STRING					(arg_t*, arg_t*, arg_t*);
	void PLUS_INT_BOOL						(arg_t*, arg_t*, arg_t*);
	void PLUS_FLOAT_INT						(arg_t*, arg_t*, arg_t*);
	void PLUS_FLOAT_FLOAT					(arg_t*, arg_t*, arg_t*);
	void PLUS_FLOAT_STRING					(arg_t*, arg_t*, arg_t*);
	void PLUS_FLOAT_BOOL					(arg_t*, arg_t*, arg_t*);
	void PLUS_STRING_INT					(arg_t*, arg_t*, arg_t*);
	void PLUS_STRING_FLOAT					(arg_t*, arg_t*, arg_t*);
	void PLUS_STRING_STRING					(arg_t*, arg_t*, arg_t*);
	void PLUS_STRING_BOOL					(arg_t*, arg_t*, arg_t*);
	void PLUS_BOOL_INT						(arg_t*, arg_t*, arg_t*);
	void PLUS_BOOL_FLOAT					(arg_t*, arg_t*, arg_t*);
	void PLUS_BOOL_STRING					(arg_t*, arg_t*, arg_t*);
	void PLUS_BOOL_BOOL						(arg_t*, arg_t*, arg_t*);
	void PLUS_LOCAL_VAR_arg					(arg_t*, arg_t*, arg_t*);
	void PLUS_LOCAL_VAR_LOCAL_VAR			(arg_t*, arg_t*, arg_t*);
	void PLUS_arg_LOCAL_VAR					(arg_t*, arg_t*, arg_t*);

	void MINUS_error						(arg_t*, arg_t*, arg_t*);
	void MINUS_INT_INT						(arg_t*, arg_t*, arg_t*);
	void MINUS_INT_FLOAT					(arg_t*, arg_t*, arg_t*);
	void MINUS_INT_BOOL						(arg_t*, arg_t*, arg_t*);
	void MINUS_FLOAT_INT					(arg_t*, arg_t*, arg_t*);
	void MINUS_FLOAT_FLOAT					(arg_t*, arg_t*, arg_t*);
	void MINUS_FLOAT_BOOL					(arg_t*, arg_t*, arg_t*);
	void MINUS_BOOL_INT						(arg_t*, arg_t*, arg_t*);
	void MINUS_BOOL_FLOAT					(arg_t*, arg_t*, arg_t*);
	void MINUS_BOOL_BOOL					(arg_t*, arg_t*, arg_t*);
	void MINUS_LOCAL_VAR_arg				(arg_t*, arg_t*, arg_t*);
	void MINUS_LOCAL_VAR_LOCAL_VAR			(arg_t*, arg_t*, arg_t*);
	void MINUS_arg_LOCAL_VAR				(arg_t*, arg_t*, arg_t*);

	void STAR_error							(arg_t*, arg_t*, arg_t*);
	void STAR_INT_INT						(arg_t*, arg_t*, arg_t*);
	void STAR_INT_FLOAT						(arg_t*, arg_t*, arg_t*);
	void STAR_INT_BOOL						(arg_t*, arg_t*, arg_t*);
	void STAR_FLOAT_INT						(arg_t*, arg_t*, arg_t*);
	void STAR_FLOAT_FLOAT					(arg_t*, arg_t*, arg_t*);
	void STAR_FLOAT_BOOL					(arg_t*, arg_t*, arg_t*);
	void STAR_BOOL_INT						(arg_t*, arg_t*, arg_t*);
	void STAR_BOOL_FLOAT					(arg_t*, arg_t*, arg_t*);
	void STAR_BOOL_BOOL						(arg_t*, arg_t*, arg_t*);
	void STAR_LOCAL_VAR_arg					(arg_t*, arg_t*, arg_t*);
	void STAR_LOCAL_VAR_LOCAL_VAR			(arg_t*, arg_t*, arg_t*);
	void STAR_arg_LOCAL_VAR					(arg_t*, arg_t*, arg_t*);

	void SLASH_error						(arg_t*, arg_t*, arg_t*);
	void SLASH_INT_INT						(arg_t*, arg_t*, arg_t*);
	void SLASH_INT_FLOAT					(arg_t*, arg_t*, arg_t*);
	void SLASH_INT_BOOL						(arg_t*, arg_t*, arg_t*);
	void SLASH_FLOAT_INT					(arg_t*, arg_t*, arg_t*);
	void SLASH_FLOAT_FLOAT					(arg_t*, arg_t*, arg_t*);
	void SLASH_FLOAT_BOOL					(arg_t*, arg_t*, arg_t*);
	void SLASH_BOOL_INT						(arg_t*, arg_t*, arg_t*);
	void SLASH_BOOL_FLOAT					(arg_t*, arg_t*, arg_t*);
	void SLASH_BOOL_BOOL					(arg_t*, arg_t*, arg_t*);
	void SLASH_LOCAL_VAR_arg				(arg_t*, arg_t*, arg_t*);
	void SLASH_LOCAL_VAR_LOCAL_VAR			(arg_t*, arg_t*, arg_t*);
	void SLASH_arg_LOCAL_VAR				(arg_t*, arg_t*, arg_t*);

	void PERCENT_error						(arg_t*, arg_t*, arg_t*);
	void PERCENT_INT_INT					(arg_t*, arg_t*, arg_t*);
	void PERCENT_INT_BOOL					(arg_t*, arg_t*, arg_t*);
	void PERCENT_BOOL_INT					(arg_t*, arg_t*, arg_t*);
	void PERCENT_BOOL_BOOL					(arg_t*, arg_t*, arg_t*);
	void PERCENT_LOCAL_VAR_arg				(arg_t*, arg_t*, arg_t*);
	void PERCENT_LOCAL_VAR_LOCAL_VAR		(arg_t*, arg_t*, arg_t*);
	void PERCENT_arg_LOCAL_VAR				(arg_t*, arg_t*, arg_t*);

	void ASSIGN_INT_INT						(arg_t*, arg_t*, arg_t*);
	void ASSIGN_INT_FLOAT					(arg_t*, arg_t*, arg_t*);
	void ASSIGN_INT_BOOL					(arg_t*, arg_t*, arg_t*);
	void ASSIGN_FLOAT_INT					(arg_t*, arg_t*, arg_t*);
	void ASSIGN_FLOAT_FLOAT					(arg_t*, arg_t*, arg_t*);
	void ASSIGN_FLOAT_BOOL					(arg_t*, arg_t*, arg_t*);
	void ASSIGN_STRING_STRING				(arg_t*, arg_t*, arg_t*);
	void ASSIGN_STRING_INT					(arg_t*, arg_t*, arg_t*);
	void ASSIGN_STRING_FLOAT				(arg_t*, arg_t*, arg_t*);
	void ASSIGN_STRING_BOOL					(arg_t*, arg_t*, arg_t*);
	void ASSIGN_BOOL_INT					(arg_t*, arg_t*, arg_t*);
	void ASSIGN_BOOL_FLOAT					(arg_t*, arg_t*, arg_t*);
	void ASSIGN_BOOL_BOOL					(arg_t*, arg_t*, arg_t*);
	void ASSIGN_arg_LOCAL_VAR				(arg_t*, arg_t*, arg_t*);
	void ASSIGN_LOCAL_VAR_arg				(arg_t*, arg_t*, arg_t*);
	void ASSIGN_LOCAL_VAR_LOCAL_VAR			(arg_t*, arg_t*, arg_t*);
	void ASSIGN_error						(arg_t*, arg_t*, arg_t*);


	void ASSIGNASSIGN_error					(arg_t*, arg_t*, arg_t*);
	void ASSIGNASSIGN_INT_INT				(arg_t*, arg_t*, arg_t*);
	void ASSIGNASSIGN_INT_FLOAT				(arg_t*, arg_t*, arg_t*);
	void ASSIGNASSIGN_INT_BOOL				(arg_t*, arg_t*, arg_t*);
	void ASSIGNASSIGN_FLOAT_INT				(arg_t*, arg_t*, arg_t*);
	void ASSIGNASSIGN_FLOAT_FLOAT			(arg_t*, arg_t*, arg_t*);
	void ASSIGNASSIGN_FLOAT_BOOL			(arg_t*, arg_t*, arg_t*);
	void ASSIGNASSIGN_STRING_STRING			(arg_t*, arg_t*, arg_t*);
	void ASSIGNASSIGN_BOOL_INT				(arg_t*, arg_t*, arg_t*);
	void ASSIGNASSIGN_BOOL_FLOAT			(arg_t*, arg_t*, arg_t*);
	void ASSIGNASSIGN_BOOL_BOOL				(arg_t*, arg_t*, arg_t*);
	void ASSIGNASSIGN_LOCAL_VAR_arg			(arg_t*, arg_t*, arg_t*);
	void ASSIGNASSIGN_LOCAL_VAR_LOCAL_VAR	(arg_t*, arg_t*, arg_t*);
	void ASSIGNASSIGN_arg_LOCAL_VAR			(arg_t*, arg_t*, arg_t*);

	void XOR_error							(arg_t*, arg_t*, arg_t*);
	void XOR_INT_INT						(arg_t*, arg_t*, arg_t*);
	void XOR_INT_BOOL						(arg_t*, arg_t*, arg_t*);
	void XOR_BOOL_INT						(arg_t*, arg_t*, arg_t*);
	void XOR_BOOL_BOOL						(arg_t*, arg_t*, arg_t*);
	void XOR_LOCAL_VAR_arg					(arg_t*, arg_t*, arg_t*);
	void XOR_LOCAL_VAR_LOCAL_VAR			(arg_t*, arg_t*, arg_t*);
	void XOR_arg_LOCAL_VAR					(arg_t*, arg_t*, arg_t*);

	void OR_error							(arg_t*, arg_t*, arg_t*);
	void OR_INT_INT							(arg_t*, arg_t*, arg_t*);
	void OR_INT_BOOL						(arg_t*, arg_t*, arg_t*);
	void OR_BOOL_INT						(arg_t*, arg_t*, arg_t*);
	void OR_BOOL_BOOL						(arg_t*, arg_t*, arg_t*);
	void OR_LOCAL_VAR_arg					(arg_t*, arg_t*, arg_t*);
	void OR_LOCAL_VAR_LOCAL_VAR				(arg_t*, arg_t*, arg_t*);
	void OR_arg_LOCAL_VAR					(arg_t*, arg_t*, arg_t*);

	void OROR_error							(arg_t*, arg_t*, arg_t*);
	void OROR_INT_INT						(arg_t*, arg_t*, arg_t*);
	void OROR_INT_FLOAT						(arg_t*, arg_t*, arg_t*);
	void OROR_INT_BOOL						(arg_t*, arg_t*, arg_t*);
	void OROR_FLOAT_INT						(arg_t*, arg_t*, arg_t*);
	void OROR_FLOAT_FLOAT					(arg_t*, arg_t*, arg_t*);
	void OROR_FLOAT_BOOL					(arg_t*, arg_t*, arg_t*);
	void OROR_BOOL_INT						(arg_t*, arg_t*, arg_t*);
	void OROR_BOOL_FLOAT					(arg_t*, arg_t*, arg_t*);
	void OROR_BOOL_BOOL						(arg_t*, arg_t*, arg_t*);
	void OROR_LOCAL_VAR_arg					(arg_t*, arg_t*, arg_t*);
	void OROR_LOCAL_VAR_LOCAL_VAR			(arg_t*, arg_t*, arg_t*);
	void OROR_arg_LOCAL_VAR					(arg_t*, arg_t*, arg_t*);

	void AND_error							(arg_t*, arg_t*, arg_t*);
	void AND_INT_INT						(arg_t*, arg_t*, arg_t*);
	void AND_INT_BOOL						(arg_t*, arg_t*, arg_t*);
	void AND_BOOL_INT						(arg_t*, arg_t*, arg_t*);
	void AND_BOOL_BOOL						(arg_t*, arg_t*, arg_t*);
	void AND_LOCAL_VAR_arg					(arg_t*, arg_t*, arg_t*);
	void AND_LOCAL_VAR_LOCAL_VAR			(arg_t*, arg_t*, arg_t*);
	void AND_arg_LOCAL_VAR					(arg_t*, arg_t*, arg_t*);

	void ANDAND_error						(arg_t*, arg_t*, arg_t*);
	void ANDAND_INT_INT						(arg_t*, arg_t*, arg_t*);
	void ANDAND_INT_FLOAT					(arg_t*, arg_t*, arg_t*);
	void ANDAND_INT_BOOL					(arg_t*, arg_t*, arg_t*);
	void ANDAND_FLOAT_INT					(arg_t*, arg_t*, arg_t*);
	void ANDAND_FLOAT_FLOAT					(arg_t*, arg_t*, arg_t*);
	void ANDAND_FLOAT_BOOL					(arg_t*, arg_t*, arg_t*);
	void ANDAND_BOOL_INT					(arg_t*, arg_t*, arg_t*);
	void ANDAND_BOOL_BOOL					(arg_t*, arg_t*, arg_t*);
	void ANDAND_BOOL_FLOAT					(arg_t*, arg_t*, arg_t*);
	void ANDAND_LOCAL_VAR_arg				(arg_t*, arg_t*, arg_t*);
	void ANDAND_LOCAL_VAR_LOCAL_VAR			(arg_t*, arg_t*, arg_t*);
	void ANDAND_arg_LOCAL_VAR				(arg_t*, arg_t*, arg_t*);

	void MORE_error							(arg_t*, arg_t*, arg_t*);
	void MORE_INT_INT						(arg_t*, arg_t*, arg_t*);
	void MORE_INT_FLOAT						(arg_t*, arg_t*, arg_t*);
	void MORE_INT_BOOL						(arg_t*, arg_t*, arg_t*);
	void MORE_FLOAT_INT						(arg_t*, arg_t*, arg_t*);
	void MORE_FLOAT_FLOAT					(arg_t*, arg_t*, arg_t*);
	void MORE_FLOAT_BOOL					(arg_t*, arg_t*, arg_t*);
	void MORE_BOOL_INT						(arg_t*, arg_t*, arg_t*);
	void MORE_BOOL_FLOAT					(arg_t*, arg_t*, arg_t*);
	void MORE_BOOL_BOOL						(arg_t*, arg_t*, arg_t*);
	void MORE_LOCAL_VAR_arg					(arg_t*, arg_t*, arg_t*);
	void MORE_LOCAL_VAR_LOCAL_VAR			(arg_t*, arg_t*, arg_t*);
	void MORE_arg_LOCAL_VAR					(arg_t*, arg_t*, arg_t*);

	void MOREASSIGN_error					(arg_t*, arg_t*, arg_t*);
	void MOREASSIGN_INT_INT					(arg_t*, arg_t*, arg_t*);
	void MOREASSIGN_INT_FLOAT				(arg_t*, arg_t*, arg_t*);
	void MOREASSIGN_INT_BOOL				(arg_t*, arg_t*, arg_t*);
	void MOREASSIGN_FLOAT_INT				(arg_t*, arg_t*, arg_t*);
	void MOREASSIGN_FLOAT_FLOAT				(arg_t*, arg_t*, arg_t*);
	void MOREASSIGN_FLOAT_BOOL				(arg_t*, arg_t*, arg_t*);
	void MOREASSIGN_BOOL_INT				(arg_t*, arg_t*, arg_t*);
	void MOREASSIGN_BOOL_FLOAT				(arg_t*, arg_t*, arg_t*);
	void MOREASSIGN_BOOL_BOOL				(arg_t*, arg_t*, arg_t*);
	void MOREASSIGN_LOCAL_VAR_arg			(arg_t*, arg_t*, arg_t*);
	void MOREASSIGN_LOCAL_VAR_LOCAL_VAR		(arg_t*, arg_t*, arg_t*);
	void MOREASSIGN_arg_LOCAL_VAR			(arg_t*, arg_t*, arg_t*);

	void LESS_error							(arg_t*, arg_t*, arg_t*);
	void LESS_INT_INT						(arg_t*, arg_t*, arg_t*);
	void LESS_INT_FLOAT						(arg_t*, arg_t*, arg_t*);
	void LESS_INT_BOOL						(arg_t*, arg_t*, arg_t*);
	void LESS_FLOAT_INT						(arg_t*, arg_t*, arg_t*);
	void LESS_FLOAT_FLOAT					(arg_t*, arg_t*, arg_t*);
	void LESS_FLOAT_BOOL					(arg_t*, arg_t*, arg_t*);
	void LESS_BOOL_INT						(arg_t*, arg_t*, arg_t*);
	void LESS_BOOL_FLOAT					(arg_t*, arg_t*, arg_t*);
	void LESS_BOOL_BOOL						(arg_t*, arg_t*, arg_t*);
	void LESS_LOCAL_VAR_arg					(arg_t*, arg_t*, arg_t*);
	void LESS_LOCAL_VAR_LOCAL_VAR			(arg_t*, arg_t*, arg_t*);
	void LESS_arg_LOCAL_VAR					(arg_t*, arg_t*, arg_t*);

	void LESSASSIGN_error					(arg_t*, arg_t*, arg_t*);
	void LESSASSIGN_INT_INT					(arg_t*, arg_t*, arg_t*);
	void LESSASSIGN_INT_FLOAT				(arg_t*, arg_t*, arg_t*);
	void LESSASSIGN_INT_BOOL				(arg_t*, arg_t*, arg_t*);
	void LESSASSIGN_FLOAT_INT				(arg_t*, arg_t*, arg_t*);
	void LESSASSIGN_FLOAT_FLOAT				(arg_t*, arg_t*, arg_t*);
	void LESSASSIGN_FLOAT_BOOL				(arg_t*, arg_t*, arg_t*);
	void LESSASSIGN_BOOL_INT				(arg_t*, arg_t*, arg_t*);
	void LESSASSIGN_BOOL_FLOAT				(arg_t*, arg_t*, arg_t*);
	void LESSASSIGN_BOOL_BOOL				(arg_t*, arg_t*, arg_t*);
	void LESSASSIGN_LOCAL_VAR_arg			(arg_t*, arg_t*, arg_t*);
	void LESSASSIGN_LOCAL_VAR_LOCAL_VAR		(arg_t*, arg_t*, arg_t*);
	void LESSASSIGN_arg_LOCAL_VAR			(arg_t*, arg_t*, arg_t*);

	void EXCLAMASSIGN_error					(arg_t*, arg_t*, arg_t*);
	void EXCLAMASSIGN_INT_INT				(arg_t*, arg_t*, arg_t*);
	void EXCLAMASSIGN_INT_FLOAT				(arg_t*, arg_t*, arg_t*);
	void EXCLAMASSIGN_INT_BOOL				(arg_t*, arg_t*, arg_t*);
	void EXCLAMASSIGN_FLOAT_INT				(arg_t*, arg_t*, arg_t*);
	void EXCLAMASSIGN_FLOAT_FLOAT			(arg_t*, arg_t*, arg_t*);
	void EXCLAMASSIGN_FLOAT_BOOL			(arg_t*, arg_t*, arg_t*);
	void EXCLAMASSIGN_STRING_STRING			(arg_t*, arg_t*, arg_t*);
	void EXCLAMASSIGN_BOOL_INT				(arg_t*, arg_t*, arg_t*);
	void EXCLAMASSIGN_BOOL_FLOAT			(arg_t*, arg_t*, arg_t*);
	void EXCLAMASSIGN_BOOL_BOOL				(arg_t*, arg_t*, arg_t*);
	void EXCLAMASSIGN_LOCAL_VAR_arg			(arg_t*, arg_t*, arg_t*);
	void EXCLAMASSIGN_LOCAL_VAR_LOCAL_VAR	(arg_t*, arg_t*, arg_t*);
	void EXCLAMASSIGN_arg_LOCAL_VAR			(arg_t*, arg_t*, arg_t*);

	void UNARYPLUS_error					(arg_t*, arg_t*, arg_t*);
	void UNARYPLUS_INT						(arg_t*, arg_t*, arg_t*);
	void UNARYPLUS_FLOAT					(arg_t*, arg_t*, arg_t*);
	void UNARYPLUS_BOOL						(arg_t*, arg_t*, arg_t*);
	void UNARYPLUS_LOCAL_VAR				(arg_t*, arg_t*, arg_t*);

	void UNARYMINUS_error					(arg_t*, arg_t*, arg_t*);
	void UNARYMINUS_INT						(arg_t*, arg_t*, arg_t*);
	void UNARYMINUS_FLOAT					(arg_t*, arg_t*, arg_t*);
	void UNARYMINUS_BOOL					(arg_t*, arg_t*, arg_t*);
	void UNARYMINUS_LOCAL_VAR				(arg_t*, arg_t*, arg_t*);

	void UNARYEXCLAM_error					(arg_t*, arg_t*, arg_t*);
	void UNARYEXCLAM_INT					(arg_t*, arg_t*, arg_t*);
	void UNARYEXCLAM_FLOAT					(arg_t*, arg_t*, arg_t*);
	void UNARYEXCLAM_BOOL					(arg_t*, arg_t*, arg_t*);
	void UNARYEXCLAM_LOCAL_VAR				(arg_t*, arg_t*, arg_t*);

	void JMP								(arg_t*, arg_t*, arg_t*);

	void JMPF_VOID							(arg_t*, arg_t*, arg_t*);
	void JMPF_INT							(arg_t*, arg_t*, arg_t*);
	void JMPF_FLOAT							(arg_t*, arg_t*, arg_t*);
	void JMPF_BOOL							(arg_t*, arg_t*, arg_t*);
	void JMPF_STRING						(arg_t*, arg_t*, arg_t*);
	void JMPF_LOCAL_VAR						(arg_t*, arg_t*, arg_t*);

	void JMPT_VOID							(arg_t*, arg_t*, arg_t*);
	void JMPT_INT							(arg_t*, arg_t*, arg_t*);
	void JMPT_FLOAT							(arg_t*, arg_t*, arg_t*);
	void JMPT_BOOL							(arg_t*, arg_t*, arg_t*);
	void JMPT_STRING						(arg_t*, arg_t*, arg_t*);
	void JMPT_LOCAL_VAR						(arg_t*, arg_t*, arg_t*);

	void CALL								(arg_t*, arg_t*, arg_t*);
	void RET								(arg_t*, arg_t*, arg_t*);
	void PUSH_arg							(arg_t*, arg_t*, arg_t*);
	void PUSH_LOCAL_VAR						(arg_t*, arg_t*, arg_t*);
	void POP								(arg_t*, arg_t*, arg_t*);
	void NOP								(arg_t*, arg_t*, arg_t*);
	void BREAK								(arg_t*, arg_t*, arg_t*);
	void CONTINUE							(arg_t*, arg_t*, arg_t*);
};


#endif
