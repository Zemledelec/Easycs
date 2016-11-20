#include "VMEasycs.h"


VMEasycs::VMEasycs(){
}

VMEasycs::~VMEasycs(){
}

void VMEasycs::LogFile( const char* fileName ){
	if ( fopen(fileName, "w")==NULL ){
		return;
	}
	parser.logFileName = const_cast<char*>(fileName);
}

void VMEasycs::Assign( const VirtualMachine* vm ){
	parser.AssignVM( vm );
}

void VMEasycs::Load( const char *fileName )
{
	parser.Compile( fileName );
	parser.PrintVM();
	pvm = parser.vm;
}

void VMEasycs::Execute()
{
	pvm->internalCode->MoveTo( pvm->internalCode->codeBegin );
	while( pvm->internalCode->codeCurr )
	{
		( pvm->*( pvm->internalCode->codeCurr->instr.opf ) )(
			pvm->internalCode->codeCurr->instr.arg1,
			pvm->internalCode->codeCurr->instr.arg2,
			pvm->internalCode->codeCurr->instr.res );

		pvm->internalCode->codeCurr = pvm->internalCode->codeCurr->next;
	}
	parser.LogText("-----------------------\n");
	parser.PrintVM();
}

