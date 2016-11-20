#ifndef _LOGTEXT_H
#define _LOGTEXT_H

#include <stdarg.h>
#include <stdio.h>

#define LOGFILENAME	"easycs.log"


bool LogText( char *lpszText, ...)
{
	va_list argList;
	FILE *pFile;

	va_start(argList, lpszText);

    if ((pFile = fopen( LOGFILENAME, "a+")) == NULL)
		return(false);

    vfprintf(pFile, lpszText, argList);
    putc('\n', pFile);

    fclose(pFile);
    va_end(argList);

	return(true);
}


#endif