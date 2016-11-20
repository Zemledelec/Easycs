#include "InternalCode.h"


arg_t::arg_t( const arg_t& a )
{
	argClass = a.argClass;
	valStr = 0x0000;

	switch( a.argClass )
	{
		case ARGC_POINTER:	
			addrInstruction = a.addrInstruction;	
			break;
		case ARGC_VOID:
			break;
		case ARGC_INT:			
			valInt = a.valInt;					
			break;
		case ARGC_FLOAT:		
			valFloat = a.valFloat;				
			break;
		case ARGC_STRING:
			if( a.valStr ){
				int len = strlen( a.valStr ) + 1;
				valStr = new char[ len ];
				valStr[ len - 1 ] = '\0';
				strcpy_s( valStr, len, a.valStr );
			}else
				valStr = 0x0000;
			break;
		case ARGC_BOOL:			
			valBool = a.valBool;					
			break;
		case ARGC_LOCAL_VAR:	
			addrLocal = a.addrLocal;
			break;
		case ARGC_GLOBAL_VAR:
			addrGlobal = a.addrGlobal;
			break;
		case ARGC_REFERENCE:
			addrReference = a.addrReference;
			break;
	}
}

arg_t& arg_t::operator = ( const arg_t& a )
{
	if( this == &a ) return *this;
	if( this->argClass == ARGC_STRING && valStr ){
		delete[] this->valStr;
		valStr = 0x0000;
	}
	this->argClass = a.argClass;
	switch( a.argClass )
	{
		case ARGC_POINTER:
			addrInstruction = a.addrInstruction;
			break;
		case ARGC_VOID:
			break;
		case ARGC_INT:
			valInt = a.valInt;
			break;
		case ARGC_FLOAT:
			valFloat = a.valFloat;
			break;
		case ARGC_STRING:
			if( a.valStr ){
				int len = strlen( a.valStr ) + 1;
				valStr = new char[ len ];
				valStr[ len - 1 ] = '\0';
				strcpy_s( valStr, len, a.valStr );
			}else
				valStr = 0x0000;
			break;
		case ARGC_BOOL:
			valBool = a.valBool;
			break;
		case ARGC_LOCAL_VAR:
			addrLocal = a.addrLocal;
			break;
		case ARGC_GLOBAL_VAR:
			addrGlobal = a.addrGlobal;
			break;
		case ARGC_REFERENCE:
			addrReference = a.addrReference;
			break;
	}
	return *this;
};



// конструктор
InternalCode::InternalCode(){
	codeCurr = codeEnd = codeBegin = 0x0000;
	numCodeSeg = 0;
}

// деструктор
InternalCode::~InternalCode()
{
	codesegment_t *curr = codeBegin;
	while( !curr ){
		codesegment_t* toDie = curr;
		curr = curr->next;
		delete toDie;
	}
}

codesegment_t* InternalCode::New(){
	codesegment_t* newcode	= new codesegment_t;
	newcode->instr.opf  = 0x0000;
	newcode->instr.arg1 = 0x0000;
	newcode->instr.arg2 = 0x0000;
	newcode->instr.res  = 0x0000;
	if( numCodeSeg > 0 ){
		newcode->next = codeCurr->next;
		newcode->prev = codeCurr;
		if( codeCurr->next == 0x0000 )
			codeEnd = newcode;
		else
			codeCurr->next->prev = newcode;
		codeCurr->next = newcode;
		codeCurr = newcode;
	}
	else{
		newcode->next = newcode->prev  = 0x0000;
		codeCurr = codeBegin = codeEnd = newcode;
	}
	numCodeSeg++;
	return newcode;
}


codesegment_t* InternalCode::NewInstruction( const cfptr op, arg_t* arg1, arg_t* arg2 ){
	SetInstruction( New(), op, arg1, arg2 );
	return codeEnd;
}


void InternalCode::SetInstruction( codesegment_t* addr, const cfptr op, arg_t* arg1, arg_t* arg2 ){
	addr->instr.opf  = op;
	addr->instr.arg1 = arg1;
	addr->instr.arg2 = arg2;
}

arg_t* InternalCode::NewArg( const arg_t& arg )
{
	if( ARGC_POINTER == arg.argClass ) 
		return arg.addrInstruction->instr.res;
	if( ARGC_GLOBAL_VAR == arg.argClass ) 
		return arg.addrGlobal;
	return new arg_t( arg );
}
