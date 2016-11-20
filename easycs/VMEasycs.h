#ifndef __EASYCS_VMEASYCS__
#define __EASYCS_VMEASYCS__


#include "Parser.h"



/*
==============================================

   Easycs virtual maschine cover

==============================================
*/


class VMEasycs
{
public:
	VMEasycs();
	~VMEasycs();

	void LogFile( const char* fileName );
	void Assign( const VirtualMachine* vm );
	void Load( const char* fileName );
	void Execute();

private:
	Parser parser;
	//��������� �� ���������� ������.
	//��� ����� �������� ������� � �� �������.
	VirtualMachine *pvm;
};



#endif