#include "VirtualMachine.h"

#include <string.h>


const cfptr VirtualMachine::MxPLUS			[6][6] = 
{
	&PLUS_error, &PLUS_error,          &PLUS_error,         &PLUS_error,           &PLUS_error,          &PLUS_error, 
	&PLUS_error, &PLUS_INT_INT,        &PLUS_INT_FLOAT,     &PLUS_INT_BOOL,        &PLUS_INT_STRING,     &PLUS_arg_LOCAL_VAR, 
	&PLUS_error, &PLUS_FLOAT_INT,      &PLUS_FLOAT_FLOAT,   &PLUS_FLOAT_BOOL,      &PLUS_FLOAT_STRING,   &PLUS_arg_LOCAL_VAR, 
	&PLUS_error, &PLUS_BOOL_INT,       &PLUS_BOOL_FLOAT,    &PLUS_BOOL_BOOL,       &PLUS_BOOL_STRING,    &PLUS_arg_LOCAL_VAR, 
	&PLUS_error, &PLUS_STRING_INT,     &PLUS_STRING_FLOAT,  &PLUS_STRING_BOOL,     &PLUS_STRING_STRING,  &PLUS_arg_LOCAL_VAR, 
	&PLUS_error, &PLUS_LOCAL_VAR_arg,  &PLUS_LOCAL_VAR_arg, &PLUS_LOCAL_VAR_arg,   &PLUS_LOCAL_VAR_arg,  &PLUS_LOCAL_VAR_LOCAL_VAR 
};

const cfptr VirtualMachine::MxMINUS			[6][6] =
{
	&MINUS_error, &MINUS_error,          &MINUS_error,       	&MINUS_error,       	 &MINUS_error,     &MINUS_error, 
	&MINUS_error, &MINUS_INT_INT,        &MINUS_INT_FLOAT,      &MINUS_INT_BOOL,       &MINUS_error,   &MINUS_arg_LOCAL_VAR, 
	&MINUS_error, &MINUS_FLOAT_INT,      &MINUS_FLOAT_FLOAT,    &MINUS_FLOAT_BOOL,     &MINUS_error,   &MINUS_arg_LOCAL_VAR, 
	&MINUS_error, &MINUS_BOOL_INT,       &MINUS_BOOL_FLOAT,     &MINUS_BOOL_BOOL,      &MINUS_error,   &MINUS_arg_LOCAL_VAR, 
	&MINUS_error, &MINUS_error,     	 &MINUS_error,     	    &MINUS_error,     	   &MINUS_error,&MINUS_error, 
	&MINUS_error, &MINUS_LOCAL_VAR_arg,  &MINUS_LOCAL_VAR_arg,  &MINUS_LOCAL_VAR_arg,  &MINUS_error,   &MINUS_LOCAL_VAR_LOCAL_VAR 
};


const cfptr VirtualMachine::MxSTAR			[6][6] =
{
	&STAR_error, &STAR_error,          &STAR_error,       	 &STAR_error,         &STAR_error,  &STAR_error, 
	&STAR_error, &STAR_INT_INT,        &STAR_INT_FLOAT,      &STAR_INT_BOOL,      &STAR_error,   &STAR_arg_LOCAL_VAR, 
	&STAR_error, &STAR_FLOAT_INT,      &STAR_FLOAT_FLOAT,    &STAR_FLOAT_BOOL,    &STAR_error,   &STAR_arg_LOCAL_VAR, 
	&STAR_error, &STAR_BOOL_INT,       &STAR_BOOL_FLOAT,     &STAR_BOOL_BOOL,     &STAR_error,   &STAR_arg_LOCAL_VAR, 
	&STAR_error, &STAR_error,     	   &STAR_error,			 &STAR_error,     	&STAR_error,    &STAR_error, 
	&STAR_error, &STAR_LOCAL_VAR_arg,  &STAR_LOCAL_VAR_arg,  &STAR_LOCAL_VAR_arg, &STAR_error,   &STAR_LOCAL_VAR_LOCAL_VAR 
};

const cfptr VirtualMachine::MxSLASH		    [6][6] =
{
	&SLASH_error, &SLASH_error,          &SLASH_error,         &SLASH_error,         &SLASH_error,   &SLASH_error, 
	&SLASH_error, &SLASH_INT_INT,        &SLASH_INT_FLOAT,     &SLASH_INT_BOOL,      &SLASH_error,   &SLASH_arg_LOCAL_VAR, 
	&SLASH_error, &SLASH_FLOAT_INT,      &SLASH_FLOAT_FLOAT,   &SLASH_FLOAT_BOOL,    &SLASH_error,   &SLASH_arg_LOCAL_VAR, 
	&SLASH_error, &SLASH_BOOL_INT,       &SLASH_BOOL_FLOAT,    &SLASH_BOOL_BOOL,     &SLASH_error,   &SLASH_arg_LOCAL_VAR, 
	&SLASH_error, &SLASH_error,     	 &SLASH_error,         &SLASH_error,     	&SLASH_error,     &SLASH_error, 
	&SLASH_error, &SLASH_LOCAL_VAR_arg,  &SLASH_LOCAL_VAR_arg, &SLASH_LOCAL_VAR_arg, &SLASH_error,   &SLASH_LOCAL_VAR_LOCAL_VAR 
};

const cfptr VirtualMachine::MxPERCENT		[6][6] = 
{
	&PERCENT_error, &PERCENT_error,          &PERCENT_error, &PERCENT_error,         &PERCENT_error,    &PERCENT_error, 
	&PERCENT_error, &PERCENT_INT_INT,        &PERCENT_error, &PERCENT_INT_BOOL,      &PERCENT_error,   &PERCENT_error, 
	&PERCENT_error, &PERCENT_error,      	 &PERCENT_error, &PERCENT_error,      	 &PERCENT_error,    &PERCENT_error, 
	&PERCENT_error, &PERCENT_BOOL_INT,       &PERCENT_error, &PERCENT_BOOL_BOOL,     &PERCENT_error,   &PERCENT_arg_LOCAL_VAR, 
	&PERCENT_error, &PERCENT_error,     	 &PERCENT_error, &PERCENT_error,     	 &PERCENT_error,    &PERCENT_error, 
	&PERCENT_error, &PERCENT_LOCAL_VAR_arg,  &PERCENT_error, &PERCENT_LOCAL_VAR_arg, &PERCENT_error,   &PERCENT_LOCAL_VAR_LOCAL_VAR 
};

const cfptr VirtualMachine::MxASSIGN		[6][6] =
{
	&ASSIGN_error, &ASSIGN_error,          &ASSIGN_error,         &ASSIGN_error,         &ASSIGN_error,         &ASSIGN_error, 
	&ASSIGN_error, &ASSIGN_INT_INT,        &ASSIGN_INT_FLOAT,     &ASSIGN_INT_BOOL,      &ASSIGN_error,		      &ASSIGN_arg_LOCAL_VAR, 
	&ASSIGN_error, &ASSIGN_FLOAT_INT,      &ASSIGN_FLOAT_FLOAT,   &ASSIGN_FLOAT_BOOL,    &ASSIGN_error,		    &ASSIGN_arg_LOCAL_VAR, 
	&ASSIGN_error, &ASSIGN_BOOL_INT,       &ASSIGN_BOOL_FLOAT,    &ASSIGN_BOOL_BOOL,     &ASSIGN_error,	        &ASSIGN_arg_LOCAL_VAR, 
	&ASSIGN_error, &ASSIGN_STRING_INT,     &ASSIGN_STRING_FLOAT,  &ASSIGN_STRING_BOOL,   &ASSIGN_STRING_STRING, &ASSIGN_arg_LOCAL_VAR, 
	&ASSIGN_error, &ASSIGN_LOCAL_VAR_arg,  &ASSIGN_LOCAL_VAR_arg, &ASSIGN_LOCAL_VAR_arg, &ASSIGN_LOCAL_VAR_arg,  &ASSIGN_LOCAL_VAR_LOCAL_VAR 
};

const cfptr VirtualMachine::MxASSIGNASSIGN	[6][6] =
{
	&ASSIGNASSIGN_error, &ASSIGNASSIGN_error,          &ASSIGNASSIGN_error,         &ASSIGNASSIGN_error,          &ASSIGNASSIGN_error,          &ASSIGNASSIGN_error, 
	&ASSIGNASSIGN_error, &ASSIGNASSIGN_INT_INT,        &ASSIGNASSIGN_INT_FLOAT,     &ASSIGNASSIGN_INT_BOOL,       &ASSIGNASSIGN_error,           &ASSIGNASSIGN_arg_LOCAL_VAR, 
	&ASSIGNASSIGN_error, &ASSIGNASSIGN_FLOAT_INT,      &ASSIGNASSIGN_FLOAT_FLOAT,   &ASSIGNASSIGN_FLOAT_BOOL,     &ASSIGNASSIGN_error,           &ASSIGNASSIGN_arg_LOCAL_VAR, 
	&ASSIGNASSIGN_error, &ASSIGNASSIGN_BOOL_INT,       &ASSIGNASSIGN_BOOL_FLOAT,    &ASSIGNASSIGN_BOOL_BOOL,      &ASSIGNASSIGN_error,           &ASSIGNASSIGN_arg_LOCAL_VAR, 
	&ASSIGNASSIGN_error, &ASSIGNASSIGN_error,     	   &ASSIGNASSIGN_error,     	&ASSIGNASSIGN_error,     	 &ASSIGNASSIGN_STRING_STRING,     &ASSIGNASSIGN_arg_LOCAL_VAR, 
	&ASSIGNASSIGN_error, &ASSIGNASSIGN_LOCAL_VAR_arg,  &ASSIGNASSIGN_LOCAL_VAR_arg, &ASSIGNASSIGN_LOCAL_VAR_arg,  &ASSIGNASSIGN_LOCAL_VAR_arg,   &ASSIGNASSIGN_LOCAL_VAR_LOCAL_VAR 
};

const cfptr VirtualMachine::MxXOR			[6][6] =
{
	&XOR_error, &XOR_error,          &XOR_error, &XOR_error,         &XOR_error,    &XOR_error, 
	&XOR_error, &XOR_INT_INT,        &XOR_error, &XOR_INT_BOOL,      &XOR_error,   &XOR_arg_LOCAL_VAR, 
	&XOR_error, &XOR_error,      	 &XOR_error, &XOR_error,      	 &XOR_error,    &XOR_error, 
	&XOR_error, &XOR_BOOL_INT,       &XOR_error, &XOR_BOOL_BOOL,     &XOR_error,   &XOR_arg_LOCAL_VAR, 
	&XOR_error, &XOR_error,     	 &XOR_error, &XOR_error,     	 &XOR_error,    &XOR_error, 
	&XOR_error, &XOR_LOCAL_VAR_arg,  &XOR_error, &XOR_LOCAL_VAR_arg, &XOR_error,   &XOR_LOCAL_VAR_LOCAL_VAR 
};

const cfptr VirtualMachine::MxOR			[6][6] =
{
	&OR_error, &OR_error,          &OR_error, &OR_error,          &OR_error, &OR_error, 
	&OR_error, &OR_INT_INT,        &OR_error, &OR_INT_BOOL,       &OR_error, &OR_arg_LOCAL_VAR, 
	&OR_error, &OR_error,      	   &OR_error, &OR_error,      	 &OR_error,  &OR_error, 
	&OR_error, &OR_BOOL_INT,       &OR_error, &OR_BOOL_BOOL,      &OR_error, &OR_arg_LOCAL_VAR, 
	&OR_error, &OR_error,     	   &OR_error, &OR_error,     	 &OR_error,  &OR_error, 
	&OR_error, &OR_LOCAL_VAR_arg,  &OR_error, &OR_LOCAL_VAR_arg,  &OR_error, &OR_LOCAL_VAR_LOCAL_VAR 
};

const cfptr VirtualMachine::MxOROR			[6][6] = 
{
	&OROR_error, &OROR_error,          &OROR_error,         &OROR_error,       	  &OROR_error,  &OROR_error, 
	&OROR_error, &OROR_INT_INT,        &OROR_INT_FLOAT,     &OROR_INT_BOOL,       &OROR_error,  &OROR_arg_LOCAL_VAR, 
	&OROR_error, &OROR_FLOAT_INT,      &OROR_FLOAT_FLOAT,   &OROR_FLOAT_BOOL,     &OROR_error,  &OROR_arg_LOCAL_VAR, 
	&OROR_error, &OROR_BOOL_INT,       &OROR_BOOL_FLOAT,    &OROR_BOOL_BOOL,      &OROR_error,  &OROR_arg_LOCAL_VAR, 
	&OROR_error, &OROR_error,     	   &OROR_error,     	&OROR_error,     	  &OROR_error,  &OROR_error, 
	&OROR_error, &OROR_LOCAL_VAR_arg,  &OROR_LOCAL_VAR_arg, &OROR_LOCAL_VAR_arg,  &OROR_error,  &OROR_LOCAL_VAR_LOCAL_VAR 
};

const cfptr VirtualMachine::MxAND			[6][6] =
{
	&AND_error, &AND_error,          &AND_error, &AND_error,          &AND_error, &AND_error, 
	&AND_error, &AND_INT_INT,        &AND_error, &AND_INT_BOOL,       &AND_error, &AND_arg_LOCAL_VAR, 
	&AND_error, &AND_error,			 &AND_error, &AND_error,      	  &AND_error, &AND_error, 
	&AND_error, &AND_BOOL_INT,       &AND_error, &AND_BOOL_BOOL,      &AND_error, &AND_arg_LOCAL_VAR, 
	&AND_error, &AND_error,     	 &AND_error, &AND_error,     	  &AND_error, &AND_error, 
	&AND_error, &AND_LOCAL_VAR_arg,  &AND_error, &AND_LOCAL_VAR_arg,  &AND_error, &AND_LOCAL_VAR_LOCAL_VAR 
};

const cfptr VirtualMachine::MxANDAND		[6][6] =
{
	&ANDAND_error, &ANDAND_error,          &ANDAND_error,          &ANDAND_error,         &ANDAND_error,  &ANDAND_error, 
	&ANDAND_error, &ANDAND_INT_INT,        &ANDAND_INT_FLOAT,      &ANDAND_INT_BOOL,      &ANDAND_error,  &ANDAND_arg_LOCAL_VAR, 
	&ANDAND_error, &ANDAND_FLOAT_INT,      &ANDAND_FLOAT_FLOAT,    &ANDAND_FLOAT_BOOL,    &ANDAND_error,  &ANDAND_arg_LOCAL_VAR, 
	&ANDAND_error, &ANDAND_BOOL_INT,       &ANDAND_BOOL_FLOAT,     &ANDAND_BOOL_BOOL,     &ANDAND_error,  &ANDAND_arg_LOCAL_VAR, 
	&ANDAND_error, &ANDAND_error,     	   &ANDAND_error,     	   &ANDAND_error,     	 &ANDAND_error,   &ANDAND_error, 
	&ANDAND_error, &ANDAND_LOCAL_VAR_arg,  &ANDAND_LOCAL_VAR_arg,  &ANDAND_LOCAL_VAR_arg, &ANDAND_error,  &ANDAND_LOCAL_VAR_LOCAL_VAR 
};

const cfptr VirtualMachine::MxMORE			[6][6] =
{
	&MORE_error, &MORE_error,          &MORE_error,         &MORE_error,       	  &MORE_error, &MORE_error, 
	&MORE_error, &MORE_INT_INT,        &MORE_INT_FLOAT,     &MORE_INT_BOOL,       &MORE_error, &MORE_arg_LOCAL_VAR, 
	&MORE_error, &MORE_FLOAT_INT,      &MORE_FLOAT_FLOAT,   &MORE_FLOAT_BOOL,     &MORE_error, &MORE_arg_LOCAL_VAR, 
	&MORE_error, &MORE_BOOL_INT,       &MORE_BOOL_FLOAT,    &MORE_BOOL_BOOL,      &MORE_error, &MORE_arg_LOCAL_VAR, 
	&MORE_error, &MORE_error,     	   &MORE_error,     	&MORE_error,     	  &MORE_error, &MORE_error, 
	&MORE_error, &MORE_LOCAL_VAR_arg,  &MORE_LOCAL_VAR_arg, &MORE_LOCAL_VAR_arg,  &MORE_error, &MORE_LOCAL_VAR_LOCAL_VAR 
};

const cfptr VirtualMachine::MxMOREASSIGN	[6][6] =
{
	&MOREASSIGN_error, &MOREASSIGN_error,          &MOREASSIGN_error,       	&MOREASSIGN_error,          &MOREASSIGN_error,  &MOREASSIGN_error, 
	&MOREASSIGN_error, &MOREASSIGN_INT_INT,        &MOREASSIGN_INT_FLOAT,       &MOREASSIGN_INT_BOOL,       &MOREASSIGN_error,  &MOREASSIGN_arg_LOCAL_VAR, 
	&MOREASSIGN_error, &MOREASSIGN_FLOAT_INT,      &MOREASSIGN_FLOAT_FLOAT,     &MOREASSIGN_FLOAT_BOOL,     &MOREASSIGN_error,  &MOREASSIGN_arg_LOCAL_VAR, 
	&MOREASSIGN_error, &MOREASSIGN_BOOL_INT,       &MOREASSIGN_BOOL_FLOAT,      &MOREASSIGN_BOOL_BOOL,      &MOREASSIGN_error,  &MOREASSIGN_arg_LOCAL_VAR, 
	&MOREASSIGN_error, &MOREASSIGN_error,     	   &MOREASSIGN_error,     		&MOREASSIGN_error,     	    &MOREASSIGN_error,  &MOREASSIGN_error, 
	&MOREASSIGN_error, &MOREASSIGN_LOCAL_VAR_arg,  &MOREASSIGN_LOCAL_VAR_arg,  	&MOREASSIGN_LOCAL_VAR_arg,  &MOREASSIGN_error,  &MOREASSIGN_LOCAL_VAR_LOCAL_VAR 
};

const cfptr VirtualMachine::MxLESS			[6][6] = 
{
	&LESS_error, &LESS_error,		    &LESS_error,		  &LESS_error,		    &LESS_error,   &LESS_error, 
	&LESS_error, &LESS_INT_INT,			&LESS_INT_FLOAT,	  &LESS_INT_BOOL,		&LESS_error,   &LESS_arg_LOCAL_VAR, 
	&LESS_error, &LESS_FLOAT_INT,	    &LESS_FLOAT_FLOAT,	  &LESS_FLOAT_BOOL,	    &LESS_error,   &LESS_arg_LOCAL_VAR, 
	&LESS_error, &LESS_BOOL_INT,	    &LESS_BOOL_FLOAT,	  &LESS_BOOL_BOOL,	    &LESS_error,   &LESS_arg_LOCAL_VAR, 
	&LESS_error, &LESS_error,		    &LESS_error,		  &LESS_error,		    &LESS_error,   &LESS_error, 
	&LESS_error, &LESS_LOCAL_VAR_arg,   &LESS_LOCAL_VAR_arg,  &LESS_LOCAL_VAR_arg,  &LESS_error,  &LESS_LOCAL_VAR_LOCAL_VAR 
};

const cfptr VirtualMachine::MxLESSASSIGN	[6][6] =
{
	&LESSASSIGN_error, &LESSASSIGN_error,		   &LESSASSIGN_error,		  &LESSASSIGN_error,		  &LESSASSIGN_error, &LESSASSIGN_error, 
	&LESSASSIGN_error, &LESSASSIGN_INT_INT,		   &LESSASSIGN_INT_FLOAT,	  &LESSASSIGN_INT_BOOL,		  &LESSASSIGN_error,  &LESSASSIGN_arg_LOCAL_VAR, 
	&LESSASSIGN_error, &LESSASSIGN_FLOAT_INT,	   &LESSASSIGN_FLOAT_FLOAT,	  &LESSASSIGN_FLOAT_BOOL,	  &LESSASSIGN_error,  &LESSASSIGN_arg_LOCAL_VAR, 
	&LESSASSIGN_error, &LESSASSIGN_BOOL_INT,	   &LESSASSIGN_BOOL_FLOAT,	  &LESSASSIGN_BOOL_BOOL,	  &LESSASSIGN_error,  &LESSASSIGN_arg_LOCAL_VAR, 
	&LESSASSIGN_error, &LESSASSIGN_error,		   &LESSASSIGN_error,		  &LESSASSIGN_error,		  &LESSASSIGN_error, &LESSASSIGN_error, 
	&LESSASSIGN_error, &LESSASSIGN_LOCAL_VAR_arg,  &LESSASSIGN_LOCAL_VAR_arg, &LESSASSIGN_LOCAL_VAR_arg,  &LESSASSIGN_error, &LESSASSIGN_LOCAL_VAR_LOCAL_VAR 
};

const cfptr VirtualMachine::MxEXCLAMASSIGN	[6][6] = 
{
	&EXCLAMASSIGN_error, &EXCLAMASSIGN_error,		    &EXCLAMASSIGN_error,		  &EXCLAMASSIGN_error,		    &EXCLAMASSIGN_error,		      &EXCLAMASSIGN_error, 
	&EXCLAMASSIGN_error, &EXCLAMASSIGN_INT_INT,			&EXCLAMASSIGN_INT_FLOAT,	  &EXCLAMASSIGN_INT_BOOL,	    &EXCLAMASSIGN_error,		  &EXCLAMASSIGN_arg_LOCAL_VAR, 
	&EXCLAMASSIGN_error, &EXCLAMASSIGN_FLOAT_INT,	    &EXCLAMASSIGN_FLOAT_FLOAT,	  &EXCLAMASSIGN_FLOAT_BOOL,	    &EXCLAMASSIGN_error,		  &EXCLAMASSIGN_arg_LOCAL_VAR, 
	&EXCLAMASSIGN_error, &EXCLAMASSIGN_BOOL_INT,		&EXCLAMASSIGN_BOOL_FLOAT,	  &EXCLAMASSIGN_BOOL_BOOL,	    &EXCLAMASSIGN_error,		  &EXCLAMASSIGN_arg_LOCAL_VAR, 
	&EXCLAMASSIGN_error, &EXCLAMASSIGN_error,		    &EXCLAMASSIGN_error,		  &EXCLAMASSIGN_error,		    &EXCLAMASSIGN_STRING_STRING,  &EXCLAMASSIGN_arg_LOCAL_VAR, 
	&EXCLAMASSIGN_error, &EXCLAMASSIGN_LOCAL_VAR_arg,   &EXCLAMASSIGN_LOCAL_VAR_arg,  &EXCLAMASSIGN_LOCAL_VAR_arg,  &EXCLAMASSIGN_LOCAL_VAR_arg,   &EXCLAMASSIGN_LOCAL_VAR_LOCAL_VAR 
};

const cfptr VirtualMachine::ArUNARYMINUS	[6] = 
{
	&UNARYMINUS_error, &UNARYMINUS_INT, &UNARYMINUS_FLOAT, &UNARYMINUS_BOOL, &UNARYMINUS_error,   &UNARYMINUS_LOCAL_VAR
};

const cfptr VirtualMachine::ArUNARYEXCLAM	[6] = 
{
	&UNARYEXCLAM_error, &UNARYEXCLAM_INT, &UNARYEXCLAM_FLOAT, &UNARYEXCLAM_BOOL, &UNARYEXCLAM_error,  &UNARYEXCLAM_LOCAL_VAR
};

const cfptr VirtualMachine::ArJMPF			[6] = 
{
	&JMPF_VOID, &JMPF_INT, &JMPF_FLOAT, &JMPF_BOOL, &JMPF_STRING,   &JMPF_LOCAL_VAR
};

const cfptr VirtualMachine::ArJMPT			[6] = 
{
	&JMPT_VOID, &JMPT_INT, &JMPT_FLOAT, &JMPT_BOOL, &JMPT_STRING,  &JMPT_LOCAL_VAR
};

const cfptr VirtualMachine::ArPUSH			[6] = 
{
	&PUSH_arg, &PUSH_arg, &PUSH_arg, &PUSH_arg, &PUSH_arg,  &PUSH_LOCAL_VAR
};


/*
====================================
	Функции виртуальной машины
====================================
*/


#define OPERATOR_LOCAL_VAR_LOCAL_VAR(OPMx) 	\
	if( ARGC_REFERENCE == frameStack[topFrame].localVars[ arg1->addrLocal ].argClass ){\
		if( ARGC_REFERENCE == frameStack[topFrame].localVars[ arg2->addrLocal ].argClass ){\
			(this->*(OPMx[ frameStack[topFrame].localVars[ arg1->addrLocal ].addrReference->argClass ][ frameStack[topFrame].localVars[ arg2->addrLocal ].addrReference->argClass ]))( frameStack[topFrame].localVars[ arg1->addrLocal ].addrReference, frameStack[topFrame].localVars[ arg2->addrLocal ].addrReference, res );\
			return;\
		}\
		(this->*(OPMx[ frameStack[topFrame].localVars[ arg1->addrLocal ].addrReference->argClass ][ frameStack[topFrame].localVars[ arg2->addrLocal ].argClass ]))( frameStack[topFrame].localVars[ arg1->addrLocal ].addrReference, &frameStack[topFrame].localVars[ arg2->addrLocal ], res );\
		return;\
	}\
	if( ARGC_REFERENCE == frameStack[topFrame].localVars[ arg2->addrLocal ].argClass ){\
		(this->*(OPMx[ frameStack[topFrame].localVars[ arg1->addrLocal ].argClass ][ frameStack[topFrame].localVars[ arg2->addrLocal ].addrReference->argClass ]))(&frameStack[topFrame].localVars[ arg1->addrLocal ], frameStack[topFrame].localVars[ arg2->addrLocal ].addrReference, res );\
		return;\
	}\
	(this->*(OPMx[ frameStack[topFrame].localVars[ arg1->addrLocal ].argClass ][ frameStack[topFrame].localVars[ arg2->addrLocal ].argClass ]))(&frameStack[topFrame].localVars[ arg1->addrLocal ], &frameStack[topFrame].localVars[ arg2->addrLocal ], res );



#define OPERATOR_arg_LOCAL_VAR(OPMx)	\
	if( ARGC_REFERENCE == frameStack[topFrame].localVars[ arg2->addrLocal ].argClass )\
		(this->*(OPMx[ arg1->argClass ][ frameStack[topFrame].localVars[ arg2->addrLocal ].addrReference->argClass ]))(arg1, frameStack[topFrame].localVars[ arg2->addrLocal ].addrReference, res );\
	else\
		(this->*(OPMx[ arg1->argClass ][ frameStack[topFrame].localVars[ arg2->addrLocal ].argClass ]))(arg1, &frameStack[topFrame].localVars[ arg2->addrLocal ], res );


#define OPERATOR_LOCAL_VAR_arg(OPMx)	\
	if( ARGC_REFERENCE == frameStack[topFrame].localVars[ arg1->addrLocal ].argClass )\
		(this->*(OPMx[ frameStack[topFrame].localVars[ arg1->addrLocal ].addrReference->argClass ][ arg2->argClass ]))(frameStack[topFrame].localVars[ arg1->addrLocal ].addrReference, arg2, res );\
	else\
		(this->*(OPMx[ frameStack[topFrame].localVars[ arg1->addrLocal ].argClass ][ arg2->argClass ]))(&frameStack[topFrame].localVars[ arg1->addrLocal ], arg2, res );


//===========
//	+
//===========
void VirtualMachine::PLUS_error							( arg_t* arg1, arg_t* arg2, arg_t* res ){
	// error
}
void VirtualMachine::PLUS_INT_INT						( arg_t* arg1, arg_t* arg2, arg_t* res ){
	res->valInt	  = arg1->valInt + arg2->valInt;
}
void VirtualMachine::PLUS_INT_FLOAT						( arg_t* arg1, arg_t* arg2, arg_t* res ){
	res->valFloat = arg1->valInt + arg2->valFloat;
}
void VirtualMachine::PLUS_INT_STRING					( arg_t* arg1, arg_t* arg2, arg_t* res ){
}
void VirtualMachine::PLUS_INT_BOOL						( arg_t* arg1, arg_t* arg2, arg_t* res ){
	res->valInt = arg1->valInt + arg2->valBool;
}
void VirtualMachine::PLUS_FLOAT_INT						( arg_t* arg1, arg_t* arg2, arg_t* res ){
	res->valFloat = arg1->valFloat + arg2->valInt;
}
void VirtualMachine::PLUS_FLOAT_FLOAT					( arg_t* arg1, arg_t* arg2, arg_t* res ){
	res->valFloat = arg1->valFloat + arg2->valFloat;
}
void VirtualMachine::PLUS_FLOAT_STRING					( arg_t* arg1, arg_t* arg2, arg_t* res ){
}
void VirtualMachine::PLUS_FLOAT_BOOL					( arg_t* arg1, arg_t* arg2, arg_t* res ){
	res->valFloat = arg1->valFloat + arg2->valBool;
}
void VirtualMachine::PLUS_STRING_INT					( arg_t* arg1, arg_t* arg2, arg_t* res ){
}
void VirtualMachine::PLUS_STRING_FLOAT					( arg_t* arg1, arg_t* arg2, arg_t* res ){
}
void VirtualMachine::PLUS_STRING_STRING					( arg_t* arg1, arg_t* arg2, arg_t* res ){
	if( res->valStr )
		delete[] res->valStr;

	size_t len = strlen( arg1->valStr ) + strlen( arg2->valStr ) + 1;
	res->valStr = new char[ len ];
	res->valStr[0] = '\0';
	strcpy_s( res->valStr, len, arg1->valStr );
	strcat_s( res->valStr, len, arg2->valStr );
}
void VirtualMachine::PLUS_STRING_BOOL					( arg_t* arg1, arg_t* arg2, arg_t* res ){
}
void VirtualMachine::PLUS_BOOL_INT						( arg_t* arg1, arg_t* arg2, arg_t* res ){
	res->valInt   = arg1->valBool + arg2->valInt;
}
void VirtualMachine::PLUS_BOOL_FLOAT					( arg_t* arg1, arg_t* arg2, arg_t* res ){
	res->valFloat = arg1->valBool + arg2->valFloat;
}
void VirtualMachine::PLUS_BOOL_STRING					( arg_t* arg1, arg_t* arg2, arg_t* res ){
}
void VirtualMachine::PLUS_BOOL_BOOL						( arg_t* arg1, arg_t* arg2, arg_t* res ){
	res->valInt   = arg1->valBool + arg2->valBool;
}
void VirtualMachine::PLUS_arg_LOCAL_VAR					( arg_t* arg1, arg_t* arg2, arg_t* res ){
	OPERATOR_arg_LOCAL_VAR(MxPLUS);
}
void VirtualMachine::PLUS_LOCAL_VAR_arg					( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	OPERATOR_LOCAL_VAR_arg(MxPLUS);
	if( ARGC_REFERENCE == frameStack[topFrame].localVars[ arg1->addrLocal ].argClass )
		(this->*(MxPLUS[ frameStack[topFrame].localVars[ arg1->addrLocal ].addrReference->argClass ][ arg2->argClass ]))(frameStack[topFrame].localVars[ arg1->addrLocal ].addrReference, arg2, res );
	else
		(this->*(MxPLUS[ frameStack[topFrame].localVars[ arg1->addrLocal ].argClass ][ arg2->argClass ]))(&frameStack[topFrame].localVars[ arg1->addrLocal ], arg2, res );
}
void VirtualMachine::PLUS_LOCAL_VAR_LOCAL_VAR			( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	OPERATOR_LOCAL_VAR_LOCAL_VAR(MxPLUS);
	if( ARGC_REFERENCE == frameStack[topFrame].localVars[ arg1->addrLocal ].argClass ){
		if( ARGC_REFERENCE == frameStack[topFrame].localVars[ arg2->addrLocal ].argClass ){
			(this->*(MxPLUS[ frameStack[topFrame].localVars[ arg1->addrLocal ].addrReference->argClass ][ frameStack[topFrame].localVars[ arg2->addrLocal ].addrReference->argClass ]))( frameStack[topFrame].localVars[ arg1->addrLocal ].addrReference, frameStack[topFrame].localVars[ arg2->addrLocal ].addrReference, res );
			return;
		}
		(this->*(MxPLUS[ frameStack[topFrame].localVars[ arg1->addrLocal ].addrReference->argClass ][ frameStack[topFrame].localVars[ arg2->addrLocal ].argClass ]))( frameStack[topFrame].localVars[ arg1->addrLocal ].addrReference, &frameStack[topFrame].localVars[ arg2->addrLocal ], res );
		return;
	}
	if( ARGC_REFERENCE == frameStack[topFrame].localVars[ arg2->addrLocal ].argClass ){
		(this->*(MxPLUS[ frameStack[topFrame].localVars[ arg1->addrLocal ].argClass ][ frameStack[topFrame].localVars[ arg2->addrLocal ].addrReference->argClass ]))(&frameStack[topFrame].localVars[ arg1->addrLocal ], frameStack[topFrame].localVars[ arg2->addrLocal ].addrReference, res );
		return;
	}

	(this->*(MxPLUS[ frameStack[topFrame].localVars[ arg1->addrLocal ].argClass ]
	[ frameStack[topFrame].localVars[ arg2->addrLocal ].argClass ]))
		(&frameStack[topFrame].localVars[ arg1->addrLocal ], &frameStack[topFrame].localVars[ arg2->addrLocal ], res );
}



//===========
//	-
//===========
void VirtualMachine::MINUS_error						( arg_t* arg1, arg_t* arg2, arg_t* res ){
	//error
}
void VirtualMachine::MINUS_INT_INT						( arg_t* arg1, arg_t* arg2, arg_t* res ){
	res->valInt   = arg1->valInt - arg2->valInt;
}
void VirtualMachine::MINUS_INT_FLOAT					( arg_t* arg1, arg_t* arg2, arg_t* res ){
	res->valFloat = arg1->valInt - arg2->valFloat;
}
void VirtualMachine::MINUS_INT_BOOL						( arg_t* arg1, arg_t* arg2, arg_t* res ){
	res->valInt   = arg1->valInt - arg2->valBool;
}
void VirtualMachine::MINUS_FLOAT_INT					( arg_t* arg1, arg_t* arg2, arg_t* res ){
	res->valFloat = arg1->valFloat - arg2->valInt;
}
void VirtualMachine::MINUS_FLOAT_FLOAT					( arg_t* arg1, arg_t* arg2, arg_t* res ){
	res->valFloat = arg1->valFloat - arg2->valFloat;
}
void VirtualMachine::MINUS_FLOAT_BOOL					( arg_t* arg1, arg_t* arg2, arg_t* res ){
	res->valFloat = arg1->valFloat - arg2->valBool;
}
void VirtualMachine::MINUS_BOOL_INT						( arg_t* arg1, arg_t* arg2, arg_t* res ){
	res->valInt   = arg1->valBool - arg2->valInt;
}
void VirtualMachine::MINUS_BOOL_FLOAT					( arg_t* arg1, arg_t* arg2, arg_t* res ){
	res->valFloat = arg1->valBool - arg2->valFloat;
}
void VirtualMachine::MINUS_BOOL_BOOL					( arg_t* arg1, arg_t* arg2, arg_t* res ){
	res->valInt   = arg1->valBool - arg2->valBool;
}
void VirtualMachine::MINUS_arg_LOCAL_VAR					( arg_t* arg1, arg_t* arg2, arg_t* res ){
	//(this->*(MxMINUS[ arg1->argClass ][ frameStack[topFrame].localVars[ arg2->addrLocal ].argClass ]))(arg1, &frameStack[topFrame].localVars[ arg2->addrLocal ], res );
	OPERATOR_arg_LOCAL_VAR(MxMINUS);
}
void VirtualMachine::MINUS_LOCAL_VAR_arg					( arg_t* arg1, arg_t* arg2, arg_t* res ){
	//(this->*(MxMINUS[ frameStack[topFrame].localVars[ arg1->addrLocal ].argClass ][ arg2->argClass ]))(&frameStack[topFrame].localVars[ arg1->addrLocal ], arg2, res );
	OPERATOR_LOCAL_VAR_arg(MxMINUS);
}
void VirtualMachine::MINUS_LOCAL_VAR_LOCAL_VAR			( arg_t* arg1, arg_t* arg2, arg_t* res ){
	//(this->*(MxMINUS[ frameStack[topFrame].localVars[ arg1->addrLocal ].argClass ][ frameStack[topFrame].localVars[ arg2->addrLocal ].argClass ]))(&frameStack[topFrame].localVars[ arg1->addrLocal ], &frameStack[topFrame].localVars[ arg2->addrLocal ], res );
	OPERATOR_LOCAL_VAR_LOCAL_VAR(MxMINUS);
}


//==========
//   *
//==========
void VirtualMachine::STAR_error							( arg_t* arg1, arg_t* arg2, arg_t* res ){
	// error
}
void VirtualMachine::STAR_INT_INT						( arg_t* arg1, arg_t* arg2, arg_t* res ){
	res->valInt   = arg1->valInt * arg2->valInt;
}
void VirtualMachine::STAR_INT_FLOAT						( arg_t* arg1, arg_t* arg2, arg_t* res ){
	res->valFloat = arg1->valInt * arg2->valFloat;
}
void VirtualMachine::STAR_INT_BOOL						( arg_t* arg1, arg_t* arg2, arg_t* res ){
	res->valInt   = arg1->valInt * arg2->valBool;
}
void VirtualMachine::STAR_FLOAT_INT						( arg_t* arg1, arg_t* arg2, arg_t* res ){
	res->valFloat = arg1->valFloat * arg2->valInt;
}
void VirtualMachine::STAR_FLOAT_FLOAT					( arg_t* arg1, arg_t* arg2, arg_t* res ){
	res->valFloat = arg1->valFloat * arg2->valFloat;
}
void VirtualMachine::STAR_FLOAT_BOOL					( arg_t* arg1, arg_t* arg2, arg_t* res ){
	res->valFloat = arg1->valFloat * arg2->valBool;
}
void VirtualMachine::STAR_BOOL_INT						( arg_t* arg1, arg_t* arg2, arg_t* res ){
	res->valInt   = arg1->valBool * arg2->valInt;
}
void VirtualMachine::STAR_BOOL_FLOAT					( arg_t* arg1, arg_t* arg2, arg_t* res ){
	res->valFloat   = arg1->valBool * arg2->valFloat;
}
void VirtualMachine::STAR_BOOL_BOOL						( arg_t* arg1, arg_t* arg2, arg_t* res ){
	res->valInt   = arg1->valBool * arg2->valBool;
}
void VirtualMachine::STAR_arg_LOCAL_VAR					( arg_t* arg1, arg_t* arg2, arg_t* res ){
	//(this->*(MxSTAR[ arg1->argClass ][ frameStack[topFrame].localVars[ arg2->addrLocal ].argClass ]))(arg1, &frameStack[topFrame].localVars[ arg2->addrLocal ], res );
	OPERATOR_arg_LOCAL_VAR(MxSTAR);
}
void VirtualMachine::STAR_LOCAL_VAR_arg					( arg_t* arg1, arg_t* arg2, arg_t* res ){
	//(this->*(MxSTAR[ frameStack[topFrame].localVars[ arg1->addrLocal ].argClass ][ arg2->argClass ]))(&frameStack[topFrame].localVars[ arg1->addrLocal ], arg2, res );
	OPERATOR_LOCAL_VAR_arg(MxSTAR);
}
void VirtualMachine::STAR_LOCAL_VAR_LOCAL_VAR			( arg_t* arg1, arg_t* arg2, arg_t* res ){
	//(this->*(MxSTAR[ frameStack[topFrame].localVars[ arg1->addrLocal ].argClass ][ frameStack[topFrame].localVars[ arg2->addrLocal ].argClass ]))(&frameStack[topFrame].localVars[ arg1->addrLocal ], &frameStack[topFrame].localVars[ arg2->addrLocal ], res );
	OPERATOR_LOCAL_VAR_LOCAL_VAR(MxSTAR);
}



//===========
//	/
//===========
void VirtualMachine::SLASH_error						( arg_t* arg1, arg_t* arg2, arg_t* res ){
	// error
}
void VirtualMachine::SLASH_INT_INT						( arg_t* arg1, arg_t* arg2, arg_t* res ){
	res->valInt = arg1->valInt / arg2->valInt;
}
void VirtualMachine::SLASH_INT_FLOAT					( arg_t* arg1, arg_t* arg2, arg_t* res ){
	res->valFloat = arg1->valInt / arg2->valFloat;
}
void VirtualMachine::SLASH_INT_BOOL						( arg_t* arg1, arg_t* arg2, arg_t* res ){
	res->valInt   = arg1->valInt / arg2->valBool;
}
void VirtualMachine::SLASH_FLOAT_INT					( arg_t* arg1, arg_t* arg2, arg_t* res ){
	res->valFloat = arg1->valFloat / arg2->valInt;
}
void VirtualMachine::SLASH_FLOAT_FLOAT					( arg_t* arg1, arg_t* arg2, arg_t* res ){
	res->valFloat = arg1->valFloat / arg2->valFloat;
}
void VirtualMachine::SLASH_FLOAT_BOOL					( arg_t* arg1, arg_t* arg2, arg_t* res ){
	res->valFloat = arg1->valFloat / arg2->valBool;
}
void VirtualMachine::SLASH_BOOL_INT						( arg_t* arg1, arg_t* arg2, arg_t* res ){
	res->valInt   = arg1->valBool / arg2->valInt;
}
void VirtualMachine::SLASH_BOOL_FLOAT					( arg_t* arg1, arg_t* arg2, arg_t* res ){
	res->valFloat   = arg1->valBool / arg2->valFloat;
}
void VirtualMachine::SLASH_BOOL_BOOL					( arg_t* arg1, arg_t* arg2, arg_t* res ){
	res->valBool   = arg1->valBool / arg2->valBool;
}
void VirtualMachine::SLASH_arg_LOCAL_VAR					( arg_t* arg1, arg_t* arg2, arg_t* res ){
	//(this->*(MxSLASH[ arg1->argClass ][ frameStack[topFrame].localVars[ arg2->addrLocal ].argClass ]))(arg1, &frameStack[topFrame].localVars[ arg2->addrLocal ], res );
	OPERATOR_arg_LOCAL_VAR(MxSLASH);
}
void VirtualMachine::SLASH_LOCAL_VAR_arg					( arg_t* arg1, arg_t* arg2, arg_t* res ){
	//(this->*(MxSLASH[ frameStack[topFrame].localVars[ arg1->addrLocal ].argClass ][ arg2->argClass ]))(&frameStack[topFrame].localVars[ arg1->addrLocal ], arg2, res );
	OPERATOR_LOCAL_VAR_arg(MxSLASH);
}
void VirtualMachine::SLASH_LOCAL_VAR_LOCAL_VAR			( arg_t* arg1, arg_t* arg2, arg_t* res ){
	//(this->*(MxSLASH[ frameStack[topFrame].localVars[ arg1->addrLocal ].argClass ][ frameStack[topFrame].localVars[ arg2->addrLocal ].argClass ]))(&frameStack[topFrame].localVars[ arg1->addrLocal ], &frameStack[topFrame].localVars[ arg2->addrLocal ], res );
	OPERATOR_LOCAL_VAR_LOCAL_VAR(MxSLASH);
}




//===========
//	%
//===========
void VirtualMachine::PERCENT_error						( arg_t* arg1, arg_t* arg2, arg_t* res ){
	// error
}
void VirtualMachine::PERCENT_INT_INT					( arg_t* arg1, arg_t* arg2, arg_t* res ){
	res->valInt = arg1->valInt % arg2->valInt;
}
void VirtualMachine::PERCENT_INT_BOOL					( arg_t* arg1, arg_t* arg2, arg_t* res ){
	res->valInt   = arg1->valInt % arg2->valBool;
}
void VirtualMachine::PERCENT_BOOL_INT					( arg_t* arg1, arg_t* arg2, arg_t* res ){
	res->valInt   = arg1->valBool % arg2->valInt;
}
void VirtualMachine::PERCENT_BOOL_BOOL					( arg_t* arg1, arg_t* arg2, arg_t* res ){
	res->valBool  = arg1->valBool % arg2->valBool;
}
void VirtualMachine::PERCENT_arg_LOCAL_VAR					( arg_t* arg1, arg_t* arg2, arg_t* res ){
	//(this->*(MxPERCENT[ arg1->argClass ][ frameStack[topFrame].localVars[ arg2->addrLocal ].argClass ]))(arg1, &frameStack[topFrame].localVars[ arg2->addrLocal ], res );
	OPERATOR_arg_LOCAL_VAR(MxPERCENT);
}
void VirtualMachine::PERCENT_LOCAL_VAR_arg					( arg_t* arg1, arg_t* arg2, arg_t* res ){
	//(this->*(MxPERCENT[ frameStack[topFrame].localVars[ arg1->addrLocal ].argClass ][ arg2->argClass ]))(&frameStack[topFrame].localVars[ arg1->addrLocal ], arg2, res );
	OPERATOR_LOCAL_VAR_arg(MxPERCENT);
}
void VirtualMachine::PERCENT_LOCAL_VAR_LOCAL_VAR			( arg_t* arg1, arg_t* arg2, arg_t* res ){
	//(this->*(MxPERCENT[ frameStack[topFrame].localVars[ arg1->addrLocal ].argClass ][ frameStack[topFrame].localVars[ arg2->addrLocal ].argClass ]))(&frameStack[topFrame].localVars[ arg1->addrLocal ], &frameStack[topFrame].localVars[ arg2->addrLocal ], res );
	OPERATOR_LOCAL_VAR_LOCAL_VAR(MxPERCENT);
}



//===========
//	=
//===========
void VirtualMachine::ASSIGN_INT_INT						( arg_t* arg1, arg_t* arg2, arg_t* res ){
	arg1->valInt = res->valInt = arg2->valInt;
}
void VirtualMachine::ASSIGN_INT_FLOAT					( arg_t* arg1, arg_t* arg2, arg_t* res ){
	arg1->valInt = res->valInt = arg2->valFloat;
}
void VirtualMachine::ASSIGN_INT_BOOL					( arg_t* arg1, arg_t* arg2, arg_t* res ){
	arg1->valInt = res->valInt = arg2->valBool;
}
void VirtualMachine::ASSIGN_FLOAT_INT					( arg_t* arg1, arg_t* arg2, arg_t* res ){
	arg1->valFloat = res->valFloat = arg2->valInt;
}
void VirtualMachine::ASSIGN_FLOAT_FLOAT					( arg_t* arg1, arg_t* arg2, arg_t* res ){
	arg1->valFloat = res->valFloat = arg2->valFloat;
}
void VirtualMachine::ASSIGN_FLOAT_BOOL					( arg_t* arg1, arg_t* arg2, arg_t* res ){
	arg1->valFloat = res->valFloat = arg2->valBool;
}
void VirtualMachine::ASSIGN_STRING_STRING				( arg_t* arg1, arg_t* arg2, arg_t* res ){
	if( arg1->valStr != arg2->valStr )
	{
		if( arg1->valStr )
			delete[] arg1->valStr;

		int len = strlen( arg2->valStr ) + 1;
		arg1->valStr = new char[ len ];
		strcpy_s( arg1->valStr, len, arg2->valStr );
	}
	res->valStr = arg1->valStr;
}
void VirtualMachine::ASSIGN_STRING_INT					( arg_t* arg1, arg_t* arg2, arg_t* res ){

}
void VirtualMachine::ASSIGN_STRING_FLOAT				( arg_t* arg1, arg_t* arg2, arg_t* res ){

}
void VirtualMachine::ASSIGN_STRING_BOOL					( arg_t* arg1, arg_t* arg2, arg_t* res ){

}
void VirtualMachine::ASSIGN_BOOL_INT					( arg_t* arg1, arg_t* arg2, arg_t* res ){
	arg1->valBool = res->valBool = arg2->valInt;
}
void VirtualMachine::ASSIGN_BOOL_FLOAT					( arg_t* arg1, arg_t* arg2, arg_t* res ){
	arg1->valBool = res->valBool = arg2->valFloat;
}
void VirtualMachine::ASSIGN_BOOL_BOOL					( arg_t* arg1, arg_t* arg2, arg_t* res ){
	arg1->valBool = res->valBool = arg2->valBool;
}
void VirtualMachine::ASSIGN_arg_LOCAL_VAR					( arg_t* arg1, arg_t* arg2, arg_t* res ){
	//(this->*(MxASSIGN[ arg1->argClass ][ frameStack[topFrame].localVars[ arg2->addrLocal ].argClass ]))(arg1, &frameStack[topFrame].localVars[ arg2->addrLocal ], res );
	OPERATOR_arg_LOCAL_VAR(MxASSIGN);
}
void VirtualMachine::ASSIGN_LOCAL_VAR_arg					( arg_t* arg1, arg_t* arg2, arg_t* res ){
	//(this->*(MxASSIGN[ frameStack[topFrame].localVars[ arg1->addrLocal ].argClass ][ arg2->argClass ]))(&frameStack[topFrame].localVars[ arg1->addrLocal ], arg2, res );
//	OPERATOR_LOCAL_VAR_arg(MxASSIGN);
	if( ARGC_REFERENCE == frameStack[topFrame].localVars[ arg1->addrLocal ].argClass )
		(this->*(MxASSIGN[ frameStack[topFrame].localVars[ arg1->addrLocal ].addrReference->argClass ][ arg2->argClass ]))(frameStack[topFrame].localVars[ arg1->addrLocal ].addrReference, arg2, frameStack[topFrame].localVars[ arg1->addrLocal ].addrReference );
	else
		(this->*(MxASSIGN[ frameStack[topFrame].localVars[ arg1->addrLocal ].argClass ][ arg2->argClass ]))(&frameStack[topFrame].localVars[ arg1->addrLocal ], arg2, &frameStack[topFrame].localVars[ arg1->addrLocal ] );
}
void VirtualMachine::ASSIGN_LOCAL_VAR_LOCAL_VAR			( arg_t* arg1, arg_t* arg2, arg_t* res ){
	OPERATOR_LOCAL_VAR_LOCAL_VAR(MxASSIGN);
}
void VirtualMachine::ASSIGN_error						( arg_t* arg1, arg_t* arg2, arg_t* res ){
	// error
}


//===========
//	==
//===========
void VirtualMachine::ASSIGNASSIGN_error					( arg_t* arg1, arg_t* arg2, arg_t* res ){
	// error
}
void VirtualMachine::ASSIGNASSIGN_INT_INT				( arg_t* arg1, arg_t* arg2, arg_t* res ){
	res->valBool  = arg1->valInt == arg2->valInt;
}
void VirtualMachine::ASSIGNASSIGN_INT_FLOAT				( arg_t* arg1, arg_t* arg2, arg_t* res ){
	res->valBool  = arg1->valInt == arg2->valFloat;
}
void VirtualMachine::ASSIGNASSIGN_INT_BOOL				( arg_t* arg1, arg_t* arg2, arg_t* res ){
	res->valBool  = arg1->valInt == arg2->valBool;
}
void VirtualMachine::ASSIGNASSIGN_FLOAT_INT				( arg_t* arg1, arg_t* arg2, arg_t* res ){
	res->valBool  = arg1->valFloat == arg2->valInt;
}
void VirtualMachine::ASSIGNASSIGN_FLOAT_FLOAT			( arg_t* arg1, arg_t* arg2, arg_t* res ){
	res->valBool  = arg1->valFloat == arg2->valFloat;
}
void VirtualMachine::ASSIGNASSIGN_FLOAT_BOOL			( arg_t* arg1, arg_t* arg2, arg_t* res ){
	res->valBool  = arg1->valFloat == arg2->valBool;
}
void VirtualMachine::ASSIGNASSIGN_STRING_STRING			( arg_t* arg1, arg_t* arg2, arg_t* res ){
	if( arg1->valStr != arg2->valStr ){
		if( arg1->valStr ){
			if( arg2->valStr ){
				res->valBool  = !strcmp( arg1->valStr, arg2->valStr );
				return;
			}
		}
	}
	else{
		res->valBool = true;	
		return;
	}
	res->valBool = false;
}
void VirtualMachine::ASSIGNASSIGN_BOOL_INT				( arg_t* arg1, arg_t* arg2, arg_t* res ){
	res->valBool  = arg1->valBool == arg2->valInt;
}
void VirtualMachine::ASSIGNASSIGN_BOOL_FLOAT			( arg_t* arg1, arg_t* arg2, arg_t* res ){
	res->valBool  = arg1->valBool == arg2->valFloat;
}
void VirtualMachine::ASSIGNASSIGN_BOOL_BOOL				( arg_t* arg1, arg_t* arg2, arg_t* res ){
	res->valBool  = arg1->valBool == arg2->valBool;
}
void VirtualMachine::ASSIGNASSIGN_arg_LOCAL_VAR					( arg_t* arg1, arg_t* arg2, arg_t* res ){
	//(this->*(MxASSIGNASSIGN[ arg1->argClass ][ frameStack[topFrame].localVars[ arg2->addrLocal ].argClass ]))(arg1, &frameStack[topFrame].localVars[ arg2->addrLocal ], res );
	OPERATOR_arg_LOCAL_VAR(MxASSIGNASSIGN);
}
void VirtualMachine::ASSIGNASSIGN_LOCAL_VAR_arg					( arg_t* arg1, arg_t* arg2, arg_t* res ){
	//(this->*(MxASSIGNASSIGN[ frameStack[topFrame].localVars[ arg1->addrLocal ].argClass ][ arg2->argClass ]))(&frameStack[topFrame].localVars[ arg1->addrLocal ], arg2, res );
	OPERATOR_LOCAL_VAR_arg(MxASSIGNASSIGN);
}
void VirtualMachine::ASSIGNASSIGN_LOCAL_VAR_LOCAL_VAR			( arg_t* arg1, arg_t* arg2, arg_t* res ){
	//(this->*(MxASSIGNASSIGN[ frameStack[topFrame].localVars[ arg1->addrLocal ].argClass ][ frameStack[topFrame].localVars[ arg2->addrLocal ].argClass ]))(&frameStack[topFrame].localVars[ arg1->addrLocal ], &frameStack[topFrame].localVars[ arg2->addrLocal ], res );
	OPERATOR_LOCAL_VAR_LOCAL_VAR(MxASSIGNASSIGN);
}



//===========
//	^
//===========
void VirtualMachine::XOR_error							( arg_t* arg1, arg_t* arg2, arg_t* res ){
	// error
}
void VirtualMachine::XOR_INT_INT						( arg_t* arg1, arg_t* arg2, arg_t* res ){
	res->valInt   = arg1->valInt ^ arg2->valInt;
}
void VirtualMachine::XOR_INT_BOOL						( arg_t* arg1, arg_t* arg2, arg_t* res ){
	res->valInt   = arg1->valInt ^ arg2->valBool;
}
void VirtualMachine::XOR_BOOL_INT						( arg_t* arg1, arg_t* arg2, arg_t* res ){
	res->valInt   = arg1->valBool ^ arg2->valInt;
}
void VirtualMachine::XOR_BOOL_BOOL						( arg_t* arg1, arg_t* arg2, arg_t* res ){
	res->valBool = arg1->valBool ^ arg2->valBool;
}
void VirtualMachine::XOR_arg_LOCAL_VAR					( arg_t* arg1, arg_t* arg2, arg_t* res ){
	//(this->*(MxXOR[ arg1->argClass ][ frameStack[topFrame].localVars[ arg2->addrLocal ].argClass ]))(arg1, &frameStack[topFrame].localVars[ arg2->addrLocal ], res );
	OPERATOR_arg_LOCAL_VAR(MxXOR);
}
void VirtualMachine::XOR_LOCAL_VAR_arg					( arg_t* arg1, arg_t* arg2, arg_t* res ){
	//(this->*(MxXOR[ frameStack[topFrame].localVars[ arg1->addrLocal ].argClass ][ arg2->argClass ]))(&frameStack[topFrame].localVars[ arg1->addrLocal ], arg2, res );
	OPERATOR_LOCAL_VAR_arg(MxXOR);
}
void VirtualMachine::XOR_LOCAL_VAR_LOCAL_VAR			( arg_t* arg1, arg_t* arg2, arg_t* res ){
	//(this->*(MxXOR[ frameStack[topFrame].localVars[ arg1->addrLocal ].argClass ][ frameStack[topFrame].localVars[ arg2->addrLocal ].argClass ]))(&frameStack[topFrame].localVars[ arg1->addrLocal ], &frameStack[topFrame].localVars[ arg2->addrLocal ], res );
	OPERATOR_LOCAL_VAR_LOCAL_VAR(MxXOR);
}




//===========
//	|
//===========
void VirtualMachine::OR_error							( arg_t* arg1, arg_t* arg2, arg_t* res ){
}
void VirtualMachine::OR_INT_INT							( arg_t* arg1, arg_t* arg2, arg_t* res ){
	res->valInt   = arg1->valInt + arg2->valInt;
}
void VirtualMachine::OR_INT_BOOL						( arg_t* arg1, arg_t* arg2, arg_t* res ){
	res->valInt   = arg1->valInt ^ arg2->valInt;
}
void VirtualMachine::OR_BOOL_INT						( arg_t* arg1, arg_t* arg2, arg_t* res ){
	res->valInt   = arg1->valBool | arg2->valInt;
}
void VirtualMachine::OR_BOOL_BOOL						( arg_t* arg1, arg_t* arg2, arg_t* res ){
	res->valBool  = arg1->valBool | arg2->valBool;
}
void VirtualMachine::OR_arg_LOCAL_VAR					( arg_t* arg1, arg_t* arg2, arg_t* res ){
	//(this->*(MxOR[ arg1->argClass ][ frameStack[topFrame].localVars[ arg2->addrLocal ].argClass ]))(arg1, &frameStack[topFrame].localVars[ arg2->addrLocal ], res );
	OPERATOR_arg_LOCAL_VAR(MxOR);
}
void VirtualMachine::OR_LOCAL_VAR_arg					( arg_t* arg1, arg_t* arg2, arg_t* res ){
	//(this->*(MxOR[ frameStack[topFrame].localVars[ arg1->addrLocal ].argClass ][ arg2->argClass ]))(&frameStack[topFrame].localVars[ arg1->addrLocal ], arg2, res );
	OPERATOR_LOCAL_VAR_arg(MxOR);
}
void VirtualMachine::OR_LOCAL_VAR_LOCAL_VAR			( arg_t* arg1, arg_t* arg2, arg_t* res ){
	//(this->*(MxOR[ frameStack[topFrame].localVars[ arg1->addrLocal ].argClass ][ frameStack[topFrame].localVars[ arg2->addrLocal ].argClass ]))(&frameStack[topFrame].localVars[ arg1->addrLocal ], &frameStack[topFrame].localVars[ arg2->addrLocal ], res );
	OPERATOR_LOCAL_VAR_LOCAL_VAR(MxOR);
}



//===========
//	||
//===========
void VirtualMachine::OROR_error							( arg_t* arg1, arg_t* arg2, arg_t* res ){
	// error
}
void VirtualMachine::OROR_INT_INT						( arg_t* arg1, arg_t* arg2, arg_t* res ){
	res->valBool  = arg1->valInt || arg2->valInt;
}
void VirtualMachine::OROR_INT_FLOAT						( arg_t* arg1, arg_t* arg2, arg_t* res ){
	res->valBool  = arg1->valInt || arg2->valFloat;
}
void VirtualMachine::OROR_INT_BOOL						( arg_t* arg1, arg_t* arg2, arg_t* res ){
	res->valBool  = arg1->valInt || arg2->valBool;
}
void VirtualMachine::OROR_FLOAT_INT						( arg_t* arg1, arg_t* arg2, arg_t* res ){
	res->valBool  = arg1->valFloat || arg2->valInt;
}
void VirtualMachine::OROR_FLOAT_FLOAT					( arg_t* arg1, arg_t* arg2, arg_t* res ){
	res->valBool  = arg1->valFloat || arg2->valFloat;
}
void VirtualMachine::OROR_FLOAT_BOOL					( arg_t* arg1, arg_t* arg2, arg_t* res ){
	res->valBool  = arg1->valFloat || arg2->valBool;
}
void VirtualMachine::OROR_BOOL_INT						( arg_t* arg1, arg_t* arg2, arg_t* res ){
	res->valBool  = arg1->valBool || arg2->valInt;
}
void VirtualMachine::OROR_BOOL_FLOAT					( arg_t* arg1, arg_t* arg2, arg_t* res ){
	res->valBool  = arg1->valBool || arg2->valFloat;
}
void VirtualMachine::OROR_BOOL_BOOL						( arg_t* arg1, arg_t* arg2, arg_t* res ){
	res->valBool  = arg1->valBool || arg2->valBool;
}
void VirtualMachine::OROR_arg_LOCAL_VAR					( arg_t* arg1, arg_t* arg2, arg_t* res ){
	//(this->*(MxOROR[ arg1->argClass ][ frameStack[topFrame].localVars[ arg2->addrLocal ].argClass ]))(arg1, &frameStack[topFrame].localVars[ arg2->addrLocal ], res );
	OPERATOR_arg_LOCAL_VAR(MxOROR);
}
void VirtualMachine::OROR_LOCAL_VAR_arg					( arg_t* arg1, arg_t* arg2, arg_t* res ){
	//(this->*(MxOROR[ frameStack[topFrame].localVars[ arg1->addrLocal ].argClass ][ arg2->argClass ]))(&frameStack[topFrame].localVars[ arg1->addrLocal ], arg2, res );
	OPERATOR_LOCAL_VAR_arg(MxOROR);
}
void VirtualMachine::OROR_LOCAL_VAR_LOCAL_VAR			( arg_t* arg1, arg_t* arg2, arg_t* res ){
	//(this->*(MxOROR[ frameStack[topFrame].localVars[ arg1->addrLocal ].argClass ][ frameStack[topFrame].localVars[ arg2->addrLocal ].argClass ]))(&frameStack[topFrame].localVars[ arg1->addrLocal ], &frameStack[topFrame].localVars[ arg2->addrLocal ], res );
	OPERATOR_LOCAL_VAR_LOCAL_VAR(MxOROR);
}



//===========
//	&
//===========
void VirtualMachine::AND_error							( arg_t* arg1, arg_t* arg2, arg_t* res ){
	// error
}
void VirtualMachine::AND_INT_INT						( arg_t* arg1, arg_t* arg2, arg_t* res ){
	res->valInt   = arg1->valInt & arg2->valInt;
}
void VirtualMachine::AND_INT_BOOL						( arg_t* arg1, arg_t* arg2, arg_t* res ){
	res->valInt   = arg1->valInt & arg2->valBool;
}
void VirtualMachine::AND_BOOL_INT						( arg_t* arg1, arg_t* arg2, arg_t* res ){
	res->valInt   = arg1->valBool & arg2->valInt;
}
void VirtualMachine::AND_BOOL_BOOL						( arg_t* arg1, arg_t* arg2, arg_t* res ){
	res->valBool  = arg1->valBool & arg2->valBool;
}
void VirtualMachine::AND_arg_LOCAL_VAR					( arg_t* arg1, arg_t* arg2, arg_t* res ){
	//(this->*(MxAND[ arg1->argClass ][ frameStack[topFrame].localVars[ arg2->addrLocal ].argClass ]))(arg1, &frameStack[topFrame].localVars[ arg2->addrLocal ], res );
	OPERATOR_arg_LOCAL_VAR(MxAND);
}
void VirtualMachine::AND_LOCAL_VAR_arg					( arg_t* arg1, arg_t* arg2, arg_t* res ){
	//(this->*(MxAND[ frameStack[topFrame].localVars[ arg1->addrLocal ].argClass ][ arg2->argClass ]))(&frameStack[topFrame].localVars[ arg1->addrLocal ], arg2, res );
	OPERATOR_LOCAL_VAR_arg(MxAND);
}
void VirtualMachine::AND_LOCAL_VAR_LOCAL_VAR			( arg_t* arg1, arg_t* arg2, arg_t* res ){
	//(this->*(MxAND[ frameStack[topFrame].localVars[ arg1->addrLocal ].argClass ][ frameStack[topFrame].localVars[ arg2->addrLocal ].argClass ]))(&frameStack[topFrame].localVars[ arg1->addrLocal ], &frameStack[topFrame].localVars[ arg2->addrLocal ], res );
	OPERATOR_LOCAL_VAR_LOCAL_VAR(MxAND);
}


//===========
//	&&
//===========
void VirtualMachine::ANDAND_error						( arg_t* arg1, arg_t* arg2, arg_t* res ){
	// error
}
void VirtualMachine::ANDAND_INT_INT						( arg_t* arg1, arg_t* arg2, arg_t* res ){
	res->valBool  = arg1->valInt && arg2->valInt;
}
void VirtualMachine::ANDAND_INT_FLOAT					( arg_t* arg1, arg_t* arg2, arg_t* res ){
	res->valBool  = arg1->valInt && arg2->valFloat;
}
void VirtualMachine::ANDAND_INT_BOOL					( arg_t* arg1, arg_t* arg2, arg_t* res ){
	res->valBool  = arg1->valInt && arg2->valBool;
}
void VirtualMachine::ANDAND_FLOAT_INT					( arg_t* arg1, arg_t* arg2, arg_t* res ){
	res->valBool  = arg1->valFloat && arg2->valInt;
}
void VirtualMachine::ANDAND_FLOAT_FLOAT					( arg_t* arg1, arg_t* arg2, arg_t* res ){
	res->valBool  = arg1->valFloat && arg2->valFloat;
}
void VirtualMachine::ANDAND_FLOAT_BOOL					( arg_t* arg1, arg_t* arg2, arg_t* res ){
	res->valBool  = arg1->valFloat && arg2->valBool;
}
void VirtualMachine::ANDAND_BOOL_INT					( arg_t* arg1, arg_t* arg2, arg_t* res ){
	res->valBool  = arg1->valBool && arg2->valInt;
}
void VirtualMachine::ANDAND_BOOL_BOOL					( arg_t* arg1, arg_t* arg2, arg_t* res ){
	res->valBool  = arg1->valBool && arg2->valBool;
}
void VirtualMachine::ANDAND_BOOL_FLOAT					( arg_t* arg1, arg_t* arg2, arg_t* res ){
	res->valBool  = arg1->valBool && arg2->valFloat;
}
void VirtualMachine::ANDAND_arg_LOCAL_VAR					( arg_t* arg1, arg_t* arg2, arg_t* res ){
	//(this->*(MxANDAND[ arg1->argClass ][ frameStack[topFrame].localVars[ arg2->addrLocal ].argClass ]))(arg1, &frameStack[topFrame].localVars[ arg2->addrLocal ], res );
	OPERATOR_arg_LOCAL_VAR(MxANDAND);
}
void VirtualMachine::ANDAND_LOCAL_VAR_arg					( arg_t* arg1, arg_t* arg2, arg_t* res ){
	//(this->*(MxANDAND[ frameStack[topFrame].localVars[ arg1->addrLocal ].argClass ][ arg2->argClass ]))(&frameStack[topFrame].localVars[ arg1->addrLocal ], arg2, res );
	OPERATOR_LOCAL_VAR_arg(MxANDAND);
}
void VirtualMachine::ANDAND_LOCAL_VAR_LOCAL_VAR			( arg_t* arg1, arg_t* arg2, arg_t* res ){
	//(this->*(MxANDAND[ frameStack[topFrame].localVars[ arg1->addrLocal ].argClass ][ frameStack[topFrame].localVars[ arg2->addrLocal ].argClass ]))(&frameStack[topFrame].localVars[ arg1->addrLocal ], &frameStack[topFrame].localVars[ arg2->addrLocal ], res );
	OPERATOR_LOCAL_VAR_LOCAL_VAR(MxANDAND);
}


//===========
//	>
//===========
void VirtualMachine::MORE_error							( arg_t* arg1, arg_t* arg2, arg_t* res ){
	// error
}
void VirtualMachine::MORE_INT_INT						( arg_t* arg1, arg_t* arg2, arg_t* res ){
	res->valBool  = arg1->valInt > arg2->valInt;
}
void VirtualMachine::MORE_INT_FLOAT						( arg_t* arg1, arg_t* arg2, arg_t* res ){
	res->valBool  = arg1->valInt > arg2->valFloat;
}
void VirtualMachine::MORE_INT_BOOL						( arg_t* arg1, arg_t* arg2, arg_t* res ){
	res->valBool  = arg1->valInt > arg2->valBool;
}
void VirtualMachine::MORE_FLOAT_INT						( arg_t* arg1, arg_t* arg2, arg_t* res ){
	res->valBool  = arg1->valFloat > arg2->valInt;
}
void VirtualMachine::MORE_FLOAT_FLOAT					( arg_t* arg1, arg_t* arg2, arg_t* res ){
	res->valBool  = arg1->valFloat > arg2->valFloat;
}
void VirtualMachine::MORE_FLOAT_BOOL					( arg_t* arg1, arg_t* arg2, arg_t* res ){
	res->valBool  = arg1->valInt > arg2->valBool;
}
void VirtualMachine::MORE_BOOL_INT						( arg_t* arg1, arg_t* arg2, arg_t* res ){
	res->valBool  = arg1->valBool > arg2->valInt;
}
void VirtualMachine::MORE_BOOL_FLOAT					( arg_t* arg1, arg_t* arg2, arg_t* res ){
	res->valBool  = arg1->valBool > arg2->valFloat;
}
void VirtualMachine::MORE_BOOL_BOOL						( arg_t* arg1, arg_t* arg2, arg_t* res ){
	res->valBool  = arg1->valBool > arg2->valBool;
}
void VirtualMachine::MORE_arg_LOCAL_VAR					( arg_t* arg1, arg_t* arg2, arg_t* res ){
	//(this->*(MxMORE[ arg1->argClass ][ frameStack[topFrame].localVars[ arg2->addrLocal ].argClass ]))(arg1, &frameStack[topFrame].localVars[ arg2->addrLocal ], res );
	OPERATOR_arg_LOCAL_VAR(MxMORE);
}
void VirtualMachine::MORE_LOCAL_VAR_arg					( arg_t* arg1, arg_t* arg2, arg_t* res ){
	//(this->*(MxMORE[ frameStack[topFrame].localVars[ arg1->addrLocal ].argClass ][ arg2->argClass ]))(&frameStack[topFrame].localVars[ arg1->addrLocal ], arg2, res );
	OPERATOR_LOCAL_VAR_arg(MxMORE);
}
void VirtualMachine::MORE_LOCAL_VAR_LOCAL_VAR			( arg_t* arg1, arg_t* arg2, arg_t* res ){
	//(this->*(MxMORE[ frameStack[topFrame].localVars[ arg1->addrLocal ].argClass ][ frameStack[topFrame].localVars[ arg2->addrLocal ].argClass ]))(&frameStack[topFrame].localVars[ arg1->addrLocal ], &frameStack[topFrame].localVars[ arg2->addrLocal ], res );
	OPERATOR_LOCAL_VAR_LOCAL_VAR(MxMORE);
}



//===========
//	>=
//===========
void VirtualMachine::MOREASSIGN_error					( arg_t* arg1, arg_t* arg2, arg_t* res ){
	// error
}
void VirtualMachine::MOREASSIGN_INT_INT					( arg_t* arg1, arg_t* arg2, arg_t* res ){
	res->valBool  = arg1->valInt >= arg2->valInt;
}
void VirtualMachine::MOREASSIGN_INT_FLOAT				( arg_t* arg1, arg_t* arg2, arg_t* res ){
	res->valBool  = arg1->valInt >= arg2->valFloat;
}
void VirtualMachine::MOREASSIGN_INT_BOOL				( arg_t* arg1, arg_t* arg2, arg_t* res ){
	res->valBool  = arg1->valInt >= arg2->valBool;
}
void VirtualMachine::MOREASSIGN_FLOAT_INT				( arg_t* arg1, arg_t* arg2, arg_t* res ){
	res->valBool  = arg1->valFloat >= arg2->valInt;
}
void VirtualMachine::MOREASSIGN_FLOAT_FLOAT				( arg_t* arg1, arg_t* arg2, arg_t* res ){
	res->valBool  = arg1->valFloat >= arg2->valFloat;
}
void VirtualMachine::MOREASSIGN_FLOAT_BOOL				( arg_t* arg1, arg_t* arg2, arg_t* res ){
	res->valBool  = arg1->valFloat >= arg2->valBool;
}
void VirtualMachine::MOREASSIGN_BOOL_INT				( arg_t* arg1, arg_t* arg2, arg_t* res ){
	res->valBool  = arg1->valBool >= arg2->valInt;
}
void VirtualMachine::MOREASSIGN_BOOL_FLOAT				( arg_t* arg1, arg_t* arg2, arg_t* res ){
	res->valBool  = arg1->valBool >= arg2->valFloat;
}
void VirtualMachine::MOREASSIGN_BOOL_BOOL				( arg_t* arg1, arg_t* arg2, arg_t* res ){
	res->valBool  = arg1->valBool >= arg2->valBool;
}
void VirtualMachine::MOREASSIGN_arg_LOCAL_VAR					( arg_t* arg1, arg_t* arg2, arg_t* res ){
	//(this->*(MxMOREASSIGN[ arg1->argClass ][ frameStack[topFrame].localVars[ arg2->addrLocal ].argClass ]))(arg1, &frameStack[topFrame].localVars[ arg2->addrLocal ], res );
	OPERATOR_arg_LOCAL_VAR(MxMOREASSIGN);
}
void VirtualMachine::MOREASSIGN_LOCAL_VAR_arg					( arg_t* arg1, arg_t* arg2, arg_t* res ){
	//(this->*(MxMOREASSIGN[ frameStack[topFrame].localVars[ arg1->addrLocal ].argClass ][ arg2->argClass ]))(&frameStack[topFrame].localVars[ arg1->addrLocal ], arg2, res );
	OPERATOR_LOCAL_VAR_arg(MxMOREASSIGN);
}
void VirtualMachine::MOREASSIGN_LOCAL_VAR_LOCAL_VAR			( arg_t* arg1, arg_t* arg2, arg_t* res ){
	//(this->*(MxMOREASSIGN[ frameStack[topFrame].localVars[ arg1->addrLocal ].argClass ][ frameStack[topFrame].localVars[ arg2->addrLocal ].argClass ]))(&frameStack[topFrame].localVars[ arg1->addrLocal ], &frameStack[topFrame].localVars[ arg2->addrLocal ], res );
	OPERATOR_LOCAL_VAR_LOCAL_VAR(MxMOREASSIGN);
}


//===========
//	<
//===========
void VirtualMachine::LESS_error							( arg_t* arg1, arg_t* arg2, arg_t* res ){
	// error
}
void VirtualMachine::LESS_INT_INT						( arg_t* arg1, arg_t* arg2, arg_t* res ){
	res->valBool  = arg1->valInt < arg2->valInt;
}
void VirtualMachine::LESS_INT_FLOAT						( arg_t* arg1, arg_t* arg2, arg_t* res ){
	res->valBool  = arg1->valInt < arg2->valFloat;
}
void VirtualMachine::LESS_INT_BOOL						( arg_t* arg1, arg_t* arg2, arg_t* res ){
	res->valBool  = arg1->valInt < arg2->valBool;
}
void VirtualMachine::LESS_FLOAT_INT						( arg_t* arg1, arg_t* arg2, arg_t* res ){
	res->valBool  = arg1->valFloat < arg2->valBool;
}
void VirtualMachine::LESS_FLOAT_FLOAT					( arg_t* arg1, arg_t* arg2, arg_t* res ){
	res->valBool  = arg1->valFloat < arg2->valFloat;
}
void VirtualMachine::LESS_FLOAT_BOOL					( arg_t* arg1, arg_t* arg2, arg_t* res ){
	res->valBool  = arg1->valFloat < arg2->valBool;
}
void VirtualMachine::LESS_BOOL_INT						( arg_t* arg1, arg_t* arg2, arg_t* res ){
	res->valBool  = arg1->valBool < arg2->valInt;
}
void VirtualMachine::LESS_BOOL_FLOAT					( arg_t* arg1, arg_t* arg2, arg_t* res ){
	res->valBool  = arg1->valBool < arg2->valFloat;
}
void VirtualMachine::LESS_BOOL_BOOL						( arg_t* arg1, arg_t* arg2, arg_t* res ){
	res->valBool  = arg1->valBool < arg2->valBool;
}
void VirtualMachine::LESS_arg_LOCAL_VAR					( arg_t* arg1, arg_t* arg2, arg_t* res ){
	//(this->*(MxLESS[ arg1->argClass ][ frameStack[topFrame].localVars[ arg2->addrLocal ].argClass ]))(arg1, &frameStack[topFrame].localVars[ arg2->addrLocal ], res );
	OPERATOR_arg_LOCAL_VAR(MxLESS);
}
void VirtualMachine::LESS_LOCAL_VAR_arg					( arg_t* arg1, arg_t* arg2, arg_t* res ){
	//(this->*(MxLESS[ frameStack[topFrame].localVars[ arg1->addrLocal ].argClass ][ arg2->argClass ]))(&frameStack[topFrame].localVars[ arg1->addrLocal ], arg2, res );
	OPERATOR_LOCAL_VAR_arg(MxLESS);
}
void VirtualMachine::LESS_LOCAL_VAR_LOCAL_VAR			( arg_t* arg1, arg_t* arg2, arg_t* res ){
	//(this->*(MxLESS[ frameStack[topFrame].localVars[ arg1->addrLocal ].argClass ][ frameStack[topFrame].localVars[ arg2->addrLocal ].argClass ]))(&frameStack[topFrame].localVars[ arg1->addrLocal ], &frameStack[topFrame].localVars[ arg2->addrLocal ], res );
	OPERATOR_LOCAL_VAR_LOCAL_VAR(MxLESS);
}


//===========
//	<=
//===========
void VirtualMachine::LESSASSIGN_error					( arg_t* arg1, arg_t* arg2, arg_t* res ){
}
void VirtualMachine::LESSASSIGN_INT_INT					( arg_t* arg1, arg_t* arg2, arg_t* res ){
	res->valBool  = arg1->valInt <= arg2->valInt;
}
void VirtualMachine::LESSASSIGN_INT_FLOAT				( arg_t* arg1, arg_t* arg2, arg_t* res ){
	res->valBool  = arg1->valInt <= arg2->valFloat;
}
void VirtualMachine::LESSASSIGN_INT_BOOL				( arg_t* arg1, arg_t* arg2, arg_t* res ){
	res->valBool  = arg1->valInt <= arg2->valBool;
}
void VirtualMachine::LESSASSIGN_FLOAT_INT				( arg_t* arg1, arg_t* arg2, arg_t* res ){
	res->valBool  = arg1->valFloat <= arg2->valInt;
}
void VirtualMachine::LESSASSIGN_FLOAT_FLOAT				( arg_t* arg1, arg_t* arg2, arg_t* res ){
	res->valBool = arg1->valFloat <= arg2->valFloat;
}
void VirtualMachine::LESSASSIGN_FLOAT_BOOL				( arg_t* arg1, arg_t* arg2, arg_t* res ){
	res->valBool = arg1->valFloat <= arg2->valBool;
}
void VirtualMachine::LESSASSIGN_BOOL_INT				( arg_t* arg1, arg_t* arg2, arg_t* res ){
	res->valBool  = arg1->valBool <= arg2->valInt;
}
void VirtualMachine::LESSASSIGN_BOOL_FLOAT				( arg_t* arg1, arg_t* arg2, arg_t* res ){
	res->valBool  = arg1->valBool <= arg2->valInt;
}
void VirtualMachine::LESSASSIGN_BOOL_BOOL				( arg_t* arg1, arg_t* arg2, arg_t* res ){
	res->valBool  = arg1->valBool <= arg2->valBool;
}
void VirtualMachine::LESSASSIGN_arg_LOCAL_VAR					( arg_t* arg1, arg_t* arg2, arg_t* res ){
	//(this->*(MxLESSASSIGN[ arg1->argClass ][ frameStack[topFrame].localVars[ arg2->addrLocal ].argClass ]))(arg1, &frameStack[topFrame].localVars[ arg2->addrLocal ], res );
	OPERATOR_arg_LOCAL_VAR(MxLESSASSIGN);
}
void VirtualMachine::LESSASSIGN_LOCAL_VAR_arg					( arg_t* arg1, arg_t* arg2, arg_t* res ){
	//(this->*(MxLESSASSIGN[ frameStack[topFrame].localVars[ arg1->addrLocal ].argClass ][ arg2->argClass ]))(&frameStack[topFrame].localVars[ arg1->addrLocal ], arg2, res );
	OPERATOR_LOCAL_VAR_arg(MxLESSASSIGN);
}
void VirtualMachine::LESSASSIGN_LOCAL_VAR_LOCAL_VAR			( arg_t* arg1, arg_t* arg2, arg_t* res ){
	//(this->*(MxLESSASSIGN[ frameStack[topFrame].localVars[ arg1->addrLocal ].argClass ][ frameStack[topFrame].localVars[ arg2->addrLocal ].argClass ]))(&frameStack[topFrame].localVars[ arg1->addrLocal ], &frameStack[topFrame].localVars[ arg2->addrLocal ], res );
	OPERATOR_LOCAL_VAR_LOCAL_VAR(MxLESSASSIGN);
}




//===========
//	!=
//===========
void VirtualMachine::EXCLAMASSIGN_error					( arg_t* arg1, arg_t* arg2, arg_t* res ){
	// error
}
void VirtualMachine::EXCLAMASSIGN_INT_INT				( arg_t* arg1, arg_t* arg2, arg_t* res ){
	res->valBool  = arg1->valInt != arg2->valInt;
}
void VirtualMachine::EXCLAMASSIGN_INT_FLOAT				( arg_t* arg1, arg_t* arg2, arg_t* res ){
	res->valBool  = arg1->valInt != arg2->valFloat;
}
void VirtualMachine::EXCLAMASSIGN_INT_BOOL				( arg_t* arg1, arg_t* arg2, arg_t* res ){
	res->valBool  = arg1->valInt != arg2->valBool;
}
void VirtualMachine::EXCLAMASSIGN_FLOAT_INT				( arg_t* arg1, arg_t* arg2, arg_t* res ){
	res->valBool  = arg1->valFloat != arg2->valInt;
}
void VirtualMachine::EXCLAMASSIGN_FLOAT_FLOAT			( arg_t* arg1, arg_t* arg2, arg_t* res ){
	res->valBool  = arg1->valFloat != arg2->valFloat;
}
void VirtualMachine::EXCLAMASSIGN_FLOAT_BOOL			( arg_t* arg1, arg_t* arg2, arg_t* res ){
	res->valBool  = arg1->valFloat != arg2->valBool;
}
void VirtualMachine::EXCLAMASSIGN_STRING_STRING			( arg_t* arg1, arg_t* arg2, arg_t* res ){
	if( arg1->valStr != arg2->valStr ){
		if( arg1->valStr ){
			if( arg2->valStr ){
				res->valBool  = strcmp( arg1->valStr, arg2->valStr );
				return;
			}
		}
	}
	res->valBool = true;
}
void VirtualMachine::EXCLAMASSIGN_BOOL_INT				( arg_t* arg1, arg_t* arg2, arg_t* res ){
	res->valBool  = arg1->valBool != arg2->valInt;
}
void VirtualMachine::EXCLAMASSIGN_BOOL_FLOAT			( arg_t* arg1, arg_t* arg2, arg_t* res ){
	res->valBool  = arg1->valBool != arg2->valFloat;
}
void VirtualMachine::EXCLAMASSIGN_BOOL_BOOL				( arg_t* arg1, arg_t* arg2, arg_t* res ){
	res->valBool  = arg1->valBool != arg2->valBool;
}
void VirtualMachine::EXCLAMASSIGN_arg_LOCAL_VAR					( arg_t* arg1, arg_t* arg2, arg_t* res ){
	//(this->*(MxEXCLAMASSIGN[ arg1->argClass ][ frameStack[topFrame].localVars[ arg2->addrLocal ].argClass ]))(arg1, &frameStack[topFrame].localVars[ arg2->addrLocal ], res );
	OPERATOR_arg_LOCAL_VAR(MxEXCLAMASSIGN);
}
void VirtualMachine::EXCLAMASSIGN_LOCAL_VAR_arg					( arg_t* arg1, arg_t* arg2, arg_t* res ){
	//(this->*(MxEXCLAMASSIGN[ frameStack[topFrame].localVars[ arg1->addrLocal ].argClass ][ arg2->argClass ]))(&frameStack[topFrame].localVars[ arg1->addrLocal ], arg2, res );
	OPERATOR_LOCAL_VAR_arg(MxEXCLAMASSIGN);
}
void VirtualMachine::EXCLAMASSIGN_LOCAL_VAR_LOCAL_VAR			( arg_t* arg1, arg_t* arg2, arg_t* res ){
	//(this->*(MxEXCLAMASSIGN[ frameStack[topFrame].localVars[ arg1->addrLocal ].argClass ][ frameStack[topFrame].localVars[ arg2->addrLocal ].argClass ]))(&frameStack[topFrame].localVars[ arg1->addrLocal ], &frameStack[topFrame].localVars[ arg2->addrLocal ], res );
	OPERATOR_LOCAL_VAR_LOCAL_VAR(MxEXCLAMASSIGN);
}



void VirtualMachine::UNARYPLUS_error						( arg_t* arg1, arg_t* arg2, arg_t* res ){
}
void VirtualMachine::UNARYPLUS_INT							( arg_t* arg1, arg_t* arg2, arg_t* res ){
}
void VirtualMachine::UNARYPLUS_FLOAT						( arg_t* arg1, arg_t* arg2, arg_t* res ){
}
void VirtualMachine::UNARYPLUS_BOOL							( arg_t* arg1, arg_t* arg2, arg_t* res ){
}
void VirtualMachine::UNARYPLUS_LOCAL_VAR					( arg_t* arg1, arg_t* arg2, arg_t* res ){
}





void VirtualMachine::UNARYMINUS_error						( arg_t* arg1, arg_t* arg2, arg_t* res ){
	// error
}
void VirtualMachine::UNARYMINUS_INT							( arg_t* arg1, arg_t* arg2, arg_t* res ){
	res->valInt   = -arg1->valInt;
}
void VirtualMachine::UNARYMINUS_FLOAT						( arg_t* arg1, arg_t* arg2, arg_t* res ){
	res->valFloat   = -arg1->valFloat;
}
void VirtualMachine::UNARYMINUS_BOOL						( arg_t* arg1, arg_t* arg2, arg_t* res ){
	res->valInt   = -arg1->valBool;
}
void VirtualMachine::UNARYMINUS_LOCAL_VAR					( arg_t* arg1, arg_t* arg2, arg_t* res ){
	if( ARGC_REFERENCE == frameStack[topFrame].localVars[ arg1->addrLocal ].argClass )
		(this->*(ArUNARYMINUS[ frameStack[topFrame].localVars[ arg1->addrLocal ].addrReference->argClass ]))( frameStack[topFrame].localVars[ arg1->addrLocal ].addrReference, arg2, res );
	else
		(this->*(ArUNARYMINUS[ frameStack[topFrame].localVars[ arg1->addrLocal ].argClass ]))(&frameStack[topFrame].localVars[ arg1->addrLocal ], arg2, res );
}



void VirtualMachine::UNARYEXCLAM_error						( arg_t* arg1, arg_t* arg2, arg_t* res ){
	// error
}
void VirtualMachine::UNARYEXCLAM_INT							( arg_t* arg1, arg_t* arg2, arg_t* res ){
	res->valBool = !arg1->valInt;
}
void VirtualMachine::UNARYEXCLAM_FLOAT						( arg_t* arg1, arg_t* arg2, arg_t* res ){
	res->valBool = !arg1->valFloat;
}
void VirtualMachine::UNARYEXCLAM_BOOL						( arg_t* arg1, arg_t* arg2, arg_t* res ){
	res->valBool = !arg1->valBool;
}
void VirtualMachine::UNARYEXCLAM_LOCAL_VAR					( arg_t* arg1, arg_t* arg2, arg_t* res ){
	if( ARGC_REFERENCE == frameStack[topFrame].localVars[ arg1->addrLocal ].argClass )
		(this->*(ArUNARYEXCLAM[ frameStack[topFrame].localVars[ arg1->addrLocal ].addrReference->argClass ]))( frameStack[topFrame].localVars[ arg1->addrLocal ].addrReference, arg2, res );
	else
		(this->*(ArUNARYEXCLAM[ frameStack[topFrame].localVars[ arg1->addrLocal ].argClass ]))(&frameStack[topFrame].localVars[ arg1->addrLocal ], arg2, res );
}


void VirtualMachine::JMPF_VOID							( arg_t* arg1, arg_t* arg2, arg_t* res ){
}
void VirtualMachine::JMPF_INT							( arg_t* arg1, arg_t* arg2, arg_t* res ){
	if( !arg1->valInt )
		internalCode->codeCurr = arg2->addrInstruction->prev;
}
void VirtualMachine::JMPF_FLOAT							( arg_t* arg1, arg_t* arg2, arg_t* res ){
	if( !arg1->valFloat )
		internalCode->codeCurr = arg2->addrInstruction->prev;
}
void VirtualMachine::JMPF_STRING						( arg_t* arg1, arg_t* arg2, arg_t* res ){
	if( arg1->valStr )
		if( !strlen( arg1->valStr ) )
			internalCode->codeCurr = arg2->addrInstruction->prev;
}
void VirtualMachine::JMPF_BOOL							( arg_t* arg1, arg_t* arg2, arg_t* res ){
	if( !arg1->valBool )
		internalCode->codeCurr = arg2->addrInstruction->prev;
}
void VirtualMachine::JMPF_LOCAL_VAR						( arg_t* arg1, arg_t* arg2, arg_t* res ){
	if( ARGC_REFERENCE == frameStack[topFrame].localVars[ arg1->addrLocal ].argClass )
		(this->*(ArJMPF[ frameStack[topFrame].localVars[ arg1->addrLocal ].addrReference->argClass ]))( frameStack[topFrame].localVars[ arg1->addrLocal ].addrReference, arg2, res );	
	else
		(this->*(ArJMPF[ frameStack[topFrame].localVars[ arg1->addrLocal ].argClass ]))(&frameStack[topFrame].localVars[ arg1->addrLocal ], arg2, res );
}



void VirtualMachine::JMPT_VOID							( arg_t* arg1, arg_t* arg2, arg_t* res ){
}
void VirtualMachine::JMPT_INT							( arg_t* arg1, arg_t* arg2, arg_t* res ){
	if( arg1->valInt )
		internalCode->codeCurr = arg2->addrInstruction;
}
void VirtualMachine::JMPT_FLOAT							( arg_t* arg1, arg_t* arg2, arg_t* res ){
	if( arg1->valFloat )
		internalCode->codeCurr = arg2->addrInstruction;
}
void VirtualMachine::JMPT_STRING						( arg_t* arg1, arg_t* arg2, arg_t* res ){
	if( arg1->valStr )
		if( strlen( arg1->valStr ) )
			internalCode->codeCurr = arg2->addrInstruction->prev;
}
void VirtualMachine::JMPT_BOOL							( arg_t* arg1, arg_t* arg2, arg_t* res ){
	if( arg1->valBool )
		internalCode->codeCurr = arg2->addrInstruction->prev;
}
void VirtualMachine::JMPT_LOCAL_VAR						( arg_t* arg1, arg_t* arg2, arg_t* res ){
	if( ARGC_REFERENCE == frameStack[topFrame].localVars[ arg1->addrLocal ].argClass )
		(this->*(ArJMPT[ frameStack[topFrame].localVars[ arg1->addrLocal ].addrReference->argClass ]))( frameStack[topFrame].localVars[ arg1->addrLocal ].addrReference, arg2, res );	
	else
		(this->*(ArJMPT[ frameStack[topFrame].localVars[ arg1->addrLocal ].argClass ]))(&frameStack[topFrame].localVars[ arg1->addrLocal ], arg2, res );
}

void VirtualMachine::CALL								( arg_t* arg1, arg_t* arg2, arg_t* res )
{
	// создаем новую запись активации вызываемой подпрограммы
	topFrame++;

	frameStack[ topFrame ].retVal.argClass	= funcs[ arg1->valInt ].retVal.argClass;
	frameStack[ topFrame ].numFmv			= funcs[ arg1->valInt ].numFmv;
	frameStack[ topFrame ].numVars			= funcs[ arg1->valInt ].numVars;
	frameStack[ topFrame ].localVars		= new arg_t[ frameStack[ topFrame ].numVars ];

	for( int i=0; i<frameStack[ topFrame ].numVars; i++ )
		frameStack[ topFrame ].localVars[i].argClass = funcs[ arg1->valInt ].localVars[i].argClass;

	// сохраняем адрес возврата
	frameStack[ topFrame ].addrCall	= internalCode->codeCurr;	

	internalCode->codeCurr = funcs[ arg1->valInt ].addr;
}


void VirtualMachine::RET								( arg_t* arg1, arg_t* arg2, arg_t* res )
{
	internalCode->codeCurr = frameStack[ topFrame ].addrCall;
	topFrame--;

	if( ARGC_LOCAL_VAR == arg1->argClass )
		(this->*(MxASSIGN[ internalCode->codeCurr->instr.res->argClass ][ frameStack[ topFrame + 1 ].localVars[ arg1->addrLocal ].argClass ]))
		( internalCode->codeCurr->instr.res, 
		  &frameStack[ topFrame + 1 ].localVars[ arg1->addrLocal ], 
		  internalCode->codeCurr->instr.res );
	else 
		(this->*(MxASSIGN[ internalCode->codeCurr->instr.res->argClass ][ arg1->argClass ]))
		( internalCode->codeCurr->instr.res, 
		  arg1, 
		  internalCode->codeCurr->instr.res );

	delete[] frameStack[ topFrame + 1 ].localVars;
}

void VirtualMachine::PUSH_arg							( arg_t* arg1, arg_t* arg2, arg_t* res ){
	argStack[ topArg ] = arg1;
	topArg++;
}
void VirtualMachine::PUSH_LOCAL_VAR						( arg_t* arg1, arg_t* arg2, arg_t* res )
{
	if( ARGC_REFERENCE == frameStack[topFrame].localVars[ arg1->addrLocal ].argClass )
		argStack[ topArg ] = frameStack[topFrame].localVars[ arg1->addrLocal ].addrReference;
	else
		argStack[ topArg ] = &frameStack[topFrame].localVars[ arg1->addrLocal ];
	topArg++;
}


void VirtualMachine::POP								( arg_t* arg1, arg_t* arg2, arg_t* res )
{
	for( int i=0; i<frameStack[ topFrame ].numFmv; i++ )
	{
		topArg--;

		if( ARGC_REFERENCE == frameStack[ topFrame ].localVars[i].argClass )
			frameStack[ topFrame ].localVars[i].addrReference = argStack[ topArg ];
		else
			(this->*(MxASSIGN[ frameStack[ topFrame ].localVars[i].argClass ][ argStack[ topArg ]->argClass ]))
			( &frameStack[ topFrame ].localVars[i], 
			  argStack[ topArg ], 
			  &frameStack[ topFrame ].localVars[i] );
	} 
}


void VirtualMachine::NOP								( arg_t* arg1, arg_t* arg2, arg_t* res ){
	// empty
}
void VirtualMachine::BREAK								( arg_t* arg1, arg_t* arg2, arg_t* res ){
	// empty
}
void VirtualMachine::CONTINUE							( arg_t* arg1, arg_t* arg2, arg_t* res ){
	// empty
}
void VirtualMachine::JMP								( arg_t* arg1, arg_t* arg2, arg_t* res ){
	internalCode->codeCurr = arg1->addrInstruction->prev;
}