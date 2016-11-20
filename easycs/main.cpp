#include <conio.h>
#include "VMEasycs.h"
#include <windows.h>





void main( int argc, char* argv[] )
{
	VMEasycs v;
	v.LogFile( "easycs.log" );
	v.Load( "test.ec" );

	DWORD t1;
	DWORD t0=GetTickCount();

	v.Execute();

	t1 = GetTickCount()-t0;
	printf("%d\n", t1);

	_getch();
	return;
}