#include "VMEasycs.h"
//#include <string.h>
//
//
//static fptr MxPLUS			[8][8] = 
//{
//	PLUS_POINTER_POINTER,    PLUS_error, PLUS_POINTER_arg,    PLUS_POINTER_arg,    PLUS_POINTER_arg,    PLUS_POINTER_arg,     PLUS_POINTER_GLOBAL_VAR,    PLUS_POINTER_LOCAL_VAR, 
//	PLUS_error,              PLUS_error, PLUS_error,          PLUS_error,          PLUS_error,          PLUS_error,           PLUS_error,                 PLUS_error, 
//	PLUS_arg_POINTER,        PLUS_error, PLUS_INT_INT,        PLUS_INT_FLOAT,      PLUS_INT_STRING,     PLUS_INT_BOOL,        PLUS_arg_GLOBAL_VAR,        PLUS_arg_LOCAL_VAR, 
//	PLUS_arg_POINTER,		 PLUS_error, PLUS_FLOAT_INT,      PLUS_FLOAT_FLOAT,    PLUS_FLOAT_STRING,   PLUS_FLOAT_BOOL,      PLUS_arg_GLOBAL_VAR,        PLUS_arg_LOCAL_VAR, 
//	PLUS_arg_POINTER,        PLUS_error, PLUS_STRING_INT,     PLUS_STRING_FLOAT,   PLUS_STRING_STRING,  PLUS_STRING_BOOL,     PLUS_arg_GLOBAL_VAR,        PLUS_arg_LOCAL_VAR, 
//	PLUS_arg_POINTER,        PLUS_error, PLUS_BOOL_INT,       PLUS_BOOL_FLOAT,     PLUS_BOOL_STRING,    PLUS_BOOL_BOOL,       PLUS_arg_GLOBAL_VAR,        PLUS_arg_LOCAL_VAR, 
//	PLUS_GLOBAL_VAR_POINTER, PLUS_error, PLUS_GLOBAL_VAR_arg, PLUS_GLOBAL_VAR_arg, PLUS_GLOBAL_VAR_arg, PLUS_GLOBAL_VAR_arg,  PLUS_GLOBAL_VAR_GLOBAL_VAR, PLUS_GLOBAL_VAR_LOCAL_VAR, 
//	PLUS_LOCAL_VAR_POINTER,  PLUS_error, PLUS_LOCAL_VAR_arg,  PLUS_LOCAL_VAR_arg,  PLUS_LOCAL_VAR_arg,  PLUS_LOCAL_VAR_arg,   PLUS_LOCAL_VAR_GLOBAL_VAR,  PLUS_LOCAL_VAR_LOCAL_VAR 
//};
//
//static fptr MxMINUS			[8][8] =
//{
//	MINUS_POINTER_POINTER,    MINUS_error, MINUS_POINTER_arg,    MINUS_POINTER_arg,      MINUS_error, MINUS_POINTER_arg,     MINUS_POINTER_GLOBAL_VAR,    MINUS_POINTER_LOCAL_VAR, 
//	MINUS_error,       		  MINUS_error, MINUS_error,          MINUS_error,       	 MINUS_error, MINUS_error,       	 MINUS_error,       		  MINUS_error, 
//	MINUS_arg_POINTER,        MINUS_error, MINUS_INT_INT,        MINUS_INT_FLOAT,        MINUS_error, MINUS_INT_BOOL,        MINUS_arg_GLOBAL_VAR,        MINUS_arg_LOCAL_VAR, 
//	MINUS_arg_POINTER,        MINUS_error, MINUS_FLOAT_INT,      MINUS_FLOAT_FLOAT,      MINUS_error, MINUS_FLOAT_BOOL,      MINUS_arg_GLOBAL_VAR,		  MINUS_arg_LOCAL_VAR, 
//	MINUS_error,			  MINUS_error, MINUS_error,     	 MINUS_error,     	     MINUS_error, MINUS_error,     		 MINUS_error,		   		  MINUS_error, 
//	MINUS_arg_POINTER,        MINUS_error, MINUS_BOOL_INT,       MINUS_BOOL_FLOAT,       MINUS_error, MINUS_BOOL_BOOL,       MINUS_arg_GLOBAL_VAR,        MINUS_arg_LOCAL_VAR, 
//	MINUS_GLOBAL_VAR_POINTER, MINUS_error, MINUS_GLOBAL_VAR_arg, MINUS_GLOBAL_VAR_arg,   MINUS_error, MINUS_GLOBAL_VAR_arg,  MINUS_GLOBAL_VAR_GLOBAL_VAR, MINUS_GLOBAL_VAR_LOCAL_VAR, 
//	MINUS_LOCAL_VAR_POINTER,  MINUS_error, MINUS_LOCAL_VAR_arg,  MINUS_LOCAL_VAR_arg,    MINUS_error, MINUS_LOCAL_VAR_arg,   MINUS_LOCAL_VAR_GLOBAL_VAR,  MINUS_LOCAL_VAR_LOCAL_VAR 
//};
//
//
//static fptr MxSTAR			[8][8] =
//{
//	STAR_POINTER_POINTER,    STAR_error, STAR_POINTER_arg,	  STAR_POINTER_arg,    	STAR_error, STAR_POINTER_arg,    STAR_POINTER_GLOBAL_VAR,    STAR_POINTER_LOCAL_VAR, 
//	STAR_error,       	     STAR_error, STAR_error,       	  STAR_error,       	STAR_error, STAR_error,       	 STAR_error,       		     STAR_error, 
//	STAR_arg_POINTER,        STAR_error, STAR_INT_INT,        STAR_INT_FLOAT,       STAR_error, STAR_INT_BOOL,       STAR_arg_GLOBAL_VAR,        STAR_arg_LOCAL_VAR, 
//	STAR_arg_POINTER,        STAR_error, STAR_FLOAT_INT,      STAR_FLOAT_FLOAT,     STAR_error, STAR_FLOAT_BOOL,     STAR_arg_GLOBAL_VAR,        STAR_arg_LOCAL_VAR, 
//	STAR_error,     		 STAR_error, STAR_error,     	  STAR_error,			STAR_error, STAR_error,     	 STAR_error,     			 STAR_error, 
//	STAR_arg_POINTER,        STAR_error, STAR_BOOL_INT,       STAR_BOOL_FLOAT,      STAR_error, STAR_BOOL_BOOL,      STAR_arg_GLOBAL_VAR,        STAR_arg_LOCAL_VAR, 
//	STAR_GLOBAL_VAR_POINTER, STAR_error, STAR_GLOBAL_VAR_arg, STAR_GLOBAL_VAR_arg,  STAR_error, STAR_GLOBAL_VAR_arg, STAR_GLOBAL_VAR_GLOBAL_VAR, STAR_GLOBAL_VAR_LOCAL_VAR, 
//	STAR_LOCAL_VAR_POINTER,  STAR_error, STAR_LOCAL_VAR_arg,  STAR_LOCAL_VAR_arg,   STAR_error, STAR_LOCAL_VAR_arg,  STAR_LOCAL_VAR_GLOBAL_VAR,  STAR_LOCAL_VAR_LOCAL_VAR 
//};
//
//static fptr MxSLASH		    [8][8] =
//{
//	SLASH_POINTER_POINTER,    SLASH_error, SLASH_POINTER_arg,    SLASH_POINTER_arg,    SLASH_error, SLASH_POINTER_arg,    SLASH_POINTER_GLOBAL_VAR,    SLASH_POINTER_LOCAL_VAR, 
//	SLASH_error,       		  SLASH_error, SLASH_error,          SLASH_error,          SLASH_error, SLASH_error,          SLASH_arg_GLOBAL_VAR,        SLASH_error, 
//	SLASH_arg_POINTER,        SLASH_error, SLASH_INT_INT,        SLASH_INT_FLOAT,      SLASH_error, SLASH_INT_BOOL,       SLASH_arg_GLOBAL_VAR,        SLASH_arg_LOCAL_VAR, 
//	SLASH_arg_POINTER,        SLASH_error, SLASH_FLOAT_INT,      SLASH_FLOAT_FLOAT,    SLASH_error, SLASH_FLOAT_BOOL,     SLASH_arg_GLOBAL_VAR,        SLASH_arg_LOCAL_VAR, 
//	SLASH_error,     		  SLASH_error, SLASH_error,     	 SLASH_error,          SLASH_error, SLASH_error,     	  SLASH_error,     			   SLASH_error, 
//	SLASH_arg_POINTER,        SLASH_error, SLASH_BOOL_INT,       SLASH_BOOL_FLOAT,     SLASH_error, SLASH_BOOL_BOOL,      SLASH_arg_GLOBAL_VAR,        SLASH_arg_LOCAL_VAR, 
//	SLASH_GLOBAL_VAR_POINTER, SLASH_error, SLASH_GLOBAL_VAR_arg, SLASH_GLOBAL_VAR_arg, SLASH_error, SLASH_GLOBAL_VAR_arg, SLASH_GLOBAL_VAR_GLOBAL_VAR, SLASH_GLOBAL_VAR_LOCAL_VAR, 
//	SLASH_LOCAL_VAR_POINTER,  SLASH_error, SLASH_LOCAL_VAR_arg,  SLASH_LOCAL_VAR_arg,  SLASH_error, SLASH_LOCAL_VAR_arg,  SLASH_LOCAL_VAR_GLOBAL_VAR,  SLASH_LOCAL_VAR_LOCAL_VAR 
//};
//
//static fptr MxPERCENT		[8][8] = 
//{
//	PERCENT_POINTER_POINTER,    PERCENT_error, PERCENT_POINTER_arg,    PERCENT_error, PERCENT_error, PERCENT_POINTER_arg,    PERCENT_POINTER_GLOBAL_VAR,    PERCENT_POINTER_LOCAL_VAR, 
//	PERCENT_error,       		PERCENT_error, PERCENT_error,          PERCENT_error, PERCENT_error, PERCENT_error,       	 PERCENT_error,       		    PERCENT_error, 
//	PERCENT_arg_POINTER,        PERCENT_error, PERCENT_INT_INT,        PERCENT_error, PERCENT_error, PERCENT_INT_BOOL,       PERCENT_arg_GLOBAL_VAR,        PERCENT_error, 
//	PERCENT_error,      		PERCENT_error, PERCENT_error,      	   PERCENT_error, PERCENT_error, PERCENT_error,      	 PERCENT_error,      			PERCENT_error, 
//	PERCENT_error,     		    PERCENT_error, PERCENT_error,     	   PERCENT_error, PERCENT_error, PERCENT_error,     	 PERCENT_error,     			PERCENT_error, 
//	PERCENT_arg_POINTER,        PERCENT_error, PERCENT_BOOL_INT,       PERCENT_error, PERCENT_error, PERCENT_BOOL_BOOL,      PERCENT_arg_GLOBAL_VAR,        PERCENT_arg_LOCAL_VAR, 
//	PERCENT_GLOBAL_VAR_POINTER, PERCENT_error, PERCENT_GLOBAL_VAR_arg, PERCENT_error, PERCENT_error, PERCENT_GLOBAL_VAR_arg, PERCENT_GLOBAL_VAR_GLOBAL_VAR, PERCENT_GLOBAL_VAR_LOCAL_VAR, 
//	PERCENT_LOCAL_VAR_POINTER,  PERCENT_error, PERCENT_LOCAL_VAR_arg,  PERCENT_error, PERCENT_error, PERCENT_LOCAL_VAR_arg,  PERCENT_LOCAL_VAR_GLOBAL_VAR,  PERCENT_LOCAL_VAR_LOCAL_VAR 
//};
//
//static fptr MxASSIGN			[8][8] =
//{
//	ASSIGN_error,			   ASSIGN_error, ASSIGN_error,		    ASSIGN_error,		   ASSIGN_error,		  ASSIGN_error,    		 ASSIGN_error,    			   ASSIGN_error, 
//	ASSIGN_error,	       	   ASSIGN_error, ASSIGN_error,          ASSIGN_error,          ASSIGN_error,          ASSIGN_error,       	 ASSIGN_error,       		   ASSIGN_error, 
//	ASSIGN_error,		       ASSIGN_error, ASSIGN_INT_INT,        ASSIGN_INT_FLOAT,      ASSIGN_error,		  ASSIGN_INT_BOOL,       ASSIGN_error,        		   ASSIGN_error, 
//	ASSIGN_error,		       ASSIGN_error, ASSIGN_FLOAT_INT,      ASSIGN_FLOAT_FLOAT,    ASSIGN_error,		  ASSIGN_FLOAT_BOOL,     ASSIGN_error,      		   ASSIGN_error, 
//	ASSIGN_error,		       ASSIGN_error, ASSIGN_STRING_INT,     ASSIGN_STRING_FLOAT,   ASSIGN_STRING_STRING,  ASSIGN_STRING_BOOL,    ASSIGN_error,     			   ASSIGN_error, 
//	ASSIGN_error,		       ASSIGN_error, ASSIGN_BOOL_INT,       ASSIGN_BOOL_FLOAT,     ASSIGN_error,	      ASSIGN_BOOL_BOOL,      ASSIGN_error,       		   ASSIGN_error, 
//	ASSIGN_GLOBAL_VAR_POINTER, ASSIGN_error, ASSIGN_GLOBAL_VAR_arg, ASSIGN_GLOBAL_VAR_arg, ASSIGN_GLOBAL_VAR_arg, ASSIGN_GLOBAL_VAR_arg, ASSIGN_GLOBAL_VAR_GLOBAL_VAR, ASSIGN_GLOBAL_VAR_LOCAL_VAR, 
//	ASSIGN_LOCAL_VAR_POINTER,  ASSIGN_error, ASSIGN_LOCAL_VAR_arg,  ASSIGN_LOCAL_VAR_arg,  ASSIGN_LOCAL_VAR_arg,  ASSIGN_LOCAL_VAR_arg,  ASSIGN_LOCAL_VAR_GLOBAL_VAR,  ASSIGN_LOCAL_VAR_LOCAL_VAR 
//};
//
//static fptr MxASSIGNASSIGN	[8][8] =
//{
//	ASSIGNASSIGN_POINTER_POINTER,    ASSIGNASSIGN_error, ASSIGNASSIGN_POINTER_arg,    ASSIGNASSIGN_POINTER_arg,    ASSIGNASSIGN_POINTER_arg,    ASSIGNASSIGN_POINTER_arg,    ASSIGNASSIGN_POINTER_GLOBAL_VAR,    ASSIGNASSIGN_POINTER_LOCAL_VAR, 
//	ASSIGNASSIGN_error,       	     ASSIGNASSIGN_error, ASSIGNASSIGN_error,       	  ASSIGNASSIGN_error,          ASSIGNASSIGN_error,       	ASSIGNASSIGN_error,          ASSIGNASSIGN_error,       	         ASSIGNASSIGN_error, 
//	ASSIGNASSIGN_arg_POINTER,        ASSIGNASSIGN_error, ASSIGNASSIGN_INT_INT,        ASSIGNASSIGN_INT_FLOAT,      ASSIGNASSIGN_error,          ASSIGNASSIGN_INT_BOOL,       ASSIGNASSIGN_arg_GLOBAL_VAR,        ASSIGNASSIGN_arg_LOCAL_VAR, 
//	ASSIGNASSIGN_arg_POINTER,        ASSIGNASSIGN_error, ASSIGNASSIGN_FLOAT_INT,      ASSIGNASSIGN_FLOAT_FLOAT,    ASSIGNASSIGN_error,       	ASSIGNASSIGN_FLOAT_BOOL,     ASSIGNASSIGN_arg_GLOBAL_VAR,        ASSIGNASSIGN_arg_LOCAL_VAR, 
//	ASSIGNASSIGN_arg_POINTER,        ASSIGNASSIGN_error, ASSIGNASSIGN_error,     	  ASSIGNASSIGN_error,     	   ASSIGNASSIGN_STRING_STRING,  ASSIGNASSIGN_error,     	 ASSIGNASSIGN_arg_GLOBAL_VAR,        ASSIGNASSIGN_arg_LOCAL_VAR, 
//	ASSIGNASSIGN_arg_POINTER,        ASSIGNASSIGN_error, ASSIGNASSIGN_BOOL_INT,       ASSIGNASSIGN_BOOL_FLOAT,     ASSIGNASSIGN_error,       	ASSIGNASSIGN_BOOL_BOOL,      ASSIGNASSIGN_arg_GLOBAL_VAR,        ASSIGNASSIGN_arg_LOCAL_VAR, 
//	ASSIGNASSIGN_GLOBAL_VAR_POINTER, ASSIGNASSIGN_error, ASSIGNASSIGN_GLOBAL_VAR_arg, ASSIGNASSIGN_GLOBAL_VAR_arg, ASSIGNASSIGN_GLOBAL_VAR_arg, ASSIGNASSIGN_GLOBAL_VAR_arg, ASSIGNASSIGN_GLOBAL_VAR_GLOBAL_VAR, ASSIGNASSIGN_GLOBAL_VAR_LOCAL_VAR, 
//	ASSIGNASSIGN_LOCAL_VAR_POINTER,  ASSIGNASSIGN_error, ASSIGNASSIGN_LOCAL_VAR_arg,  ASSIGNASSIGN_LOCAL_VAR_arg,  ASSIGNASSIGN_LOCAL_VAR_arg,  ASSIGNASSIGN_LOCAL_VAR_arg,  ASSIGNASSIGN_LOCAL_VAR_GLOBAL_VAR,  ASSIGNASSIGN_LOCAL_VAR_LOCAL_VAR 
//};
//
//static fptr MxXOR			[8][8] =
//{
//	XOR_POINTER_POINTER,    XOR_error, XOR_POINTER_arg,    XOR_error, XOR_error, XOR_POINTER_arg,    XOR_POINTER_GLOBAL_VAR,    XOR_POINTER_LOCAL_VAR, 
//	XOR_error,       		XOR_error, XOR_error,          XOR_error, XOR_error, XOR_error,       	 XOR_error,       		    XOR_error, 
//	XOR_arg_POINTER,        XOR_error, XOR_INT_INT,        XOR_error, XOR_error, XOR_INT_BOOL,       XOR_arg_GLOBAL_VAR,        XOR_arg_LOCAL_VAR, 
//	XOR_error,      		XOR_error, XOR_error,      	   XOR_error, XOR_error, XOR_error,      	 XOR_error,      			XOR_error, 
//	XOR_error,     		    XOR_error, XOR_error,     	   XOR_error, XOR_error, XOR_error,     	 XOR_error,     		    XOR_error, 
//	XOR_arg_POINTER,        XOR_error, XOR_BOOL_INT,       XOR_error, XOR_error, XOR_BOOL_BOOL,      XOR_arg_GLOBAL_VAR,        XOR_arg_LOCAL_VAR, 
//	XOR_GLOBAL_VAR_POINTER, XOR_error, XOR_GLOBAL_VAR_arg, XOR_error, XOR_error, XOR_GLOBAL_VAR_arg, XOR_GLOBAL_VAR_GLOBAL_VAR, XOR_GLOBAL_VAR_LOCAL_VAR, 
//	XOR_LOCAL_VAR_POINTER,  XOR_error, XOR_LOCAL_VAR_arg,  XOR_error, XOR_error, XOR_LOCAL_VAR_arg,  XOR_LOCAL_VAR_GLOBAL_VAR,  XOR_LOCAL_VAR_LOCAL_VAR 
//};
//
//static fptr MxOR				[8][8] =
//{
//	OR_POINTER_POINTER,    OR_error, OR_POINTER_arg,    OR_error, OR_error, OR_POINTER_arg,    OR_POINTER_GLOBAL_VAR,    OR_POINTER_LOCAL_VAR, 
//	OR_error,       	   OR_error, OR_error,       	OR_error, OR_error, OR_error,          OR_error,       		     OR_error, 
//	OR_arg_POINTER,        OR_error, OR_INT_INT,        OR_error, OR_error, OR_INT_BOOL,       OR_arg_GLOBAL_VAR,        OR_arg_LOCAL_VAR, 
//	OR_error,      		   OR_error, OR_error,      	OR_error, OR_error, OR_error,      	   OR_error,      			 OR_error, 
//	OR_error,     		   OR_error, OR_error,     	    OR_error, OR_error, OR_error,     	   OR_error,     			 OR_error, 
//	OR_arg_POINTER,        OR_error, OR_BOOL_INT,       OR_error, OR_error, OR_BOOL_BOOL,      OR_arg_GLOBAL_VAR,        OR_arg_LOCAL_VAR, 
//	OR_GLOBAL_VAR_POINTER, OR_error, OR_GLOBAL_VAR_arg, OR_error, OR_error, OR_GLOBAL_VAR_arg, OR_GLOBAL_VAR_GLOBAL_VAR, OR_GLOBAL_VAR_LOCAL_VAR, 
//	OR_LOCAL_VAR_POINTER,  OR_error, OR_LOCAL_VAR_arg,  OR_error, OR_error, OR_LOCAL_VAR_arg,  OR_LOCAL_VAR_GLOBAL_VAR,  OR_LOCAL_VAR_LOCAL_VAR 
//};
//
//static fptr MxOROR			[8][8] = 
//{
//	OROR_POINTER_POINTER,    OROR_error, OROR_POINTER_arg,    OROR_POINTER_arg,    OROR_error, OROR_POINTER_arg,    OROR_POINTER_GLOBAL_VAR,    OROR_POINTER_LOCAL_VAR, 
//	OROR_error,       	     OROR_error, OROR_error,       	  OROR_error,          OROR_error, OROR_error,       	OROR_error,       		    OROR_error, 
//	OROR_arg_POINTER,        OROR_error, OROR_INT_INT,        OROR_INT_FLOAT,      OROR_error, OROR_INT_BOOL,       OROR_arg_GLOBAL_VAR,        OROR_arg_LOCAL_VAR, 
//	OROR_arg_POINTER,        OROR_error, OROR_FLOAT_INT,      OROR_FLOAT_FLOAT,    OROR_error, OROR_FLOAT_BOOL,     OROR_arg_GLOBAL_VAR,        OROR_arg_LOCAL_VAR, 
//	OROR_error,     		 OROR_error, OROR_error,     	  OROR_error,     	   OROR_error, OROR_error,     		OROR_error,     			OROR_error, 
//	OROR_arg_POINTER,        OROR_error, OROR_BOOL_INT,       OROR_BOOL_FLOAT,     OROR_error, OROR_BOOL_BOOL,      OROR_arg_GLOBAL_VAR,        OROR_arg_LOCAL_VAR, 
//	OROR_GLOBAL_VAR_POINTER, OROR_error, OROR_GLOBAL_VAR_arg, OROR_GLOBAL_VAR_arg, OROR_error, OROR_GLOBAL_VAR_arg, OROR_GLOBAL_VAR_GLOBAL_VAR, OROR_GLOBAL_VAR_LOCAL_VAR, 
//	OROR_LOCAL_VAR_POINTER,  OROR_error, OROR_LOCAL_VAR_arg,  OROR_LOCAL_VAR_arg,  OROR_error, OROR_LOCAL_VAR_arg,  OROR_LOCAL_VAR_GLOBAL_VAR,  OROR_LOCAL_VAR_LOCAL_VAR 
//};
//
//static fptr MxAND			[8][8] =
//{
//	AND_POINTER_POINTER,    AND_error, AND_POINTER_arg,    AND_error, AND_error, AND_POINTER_arg,    AND_POINTER_GLOBAL_VAR,    AND_POINTER_LOCAL_VAR, 
//	AND_error,       		AND_error, AND_error,          AND_error, AND_error, AND_error,       	 AND_error,       		    AND_error, 
//	AND_arg_POINTER,        AND_error, AND_INT_INT,        AND_error, AND_error, AND_INT_BOOL,       AND_arg_GLOBAL_VAR,        AND_arg_LOCAL_VAR, 
//	AND_error,      		AND_error, AND_error,		   AND_error, AND_error, AND_error,      	 AND_error,      			AND_error, 
//	AND_error,     		    AND_error, AND_error,     	   AND_error, AND_error, AND_error,     	 AND_error,     			AND_error, 
//	AND_arg_POINTER,        AND_error, AND_BOOL_INT,       AND_error, AND_error, AND_BOOL_BOOL,      AND_arg_GLOBAL_VAR,        AND_arg_LOCAL_VAR, 
//	AND_GLOBAL_VAR_POINTER, AND_error, AND_GLOBAL_VAR_arg, AND_error, AND_error, AND_GLOBAL_VAR_arg, AND_GLOBAL_VAR_GLOBAL_VAR, AND_GLOBAL_VAR_LOCAL_VAR, 
//	AND_LOCAL_VAR_POINTER,  AND_error, AND_LOCAL_VAR_arg,  AND_error, AND_error, AND_LOCAL_VAR_arg,  AND_LOCAL_VAR_GLOBAL_VAR,  AND_LOCAL_VAR_LOCAL_VAR 
//};
//
//static fptr MxANDAND			[8][8] =
//{
//	ANDAND_POINTER_POINTER,    ANDAND_error, ANDAND_POINTER_arg,    ANDAND_POINTER_arg,    ANDAND_error, ANDAND_POINTER_arg,    ANDAND_POINTER_GLOBAL_VAR,    ANDAND_POINTER_LOCAL_VAR, 
//	ANDAND_error,       	   ANDAND_error, ANDAND_error,       	ANDAND_error,          ANDAND_error, ANDAND_error,       	ANDAND_error,       		  ANDAND_error, 
//	ANDAND_arg_POINTER,        ANDAND_error, ANDAND_INT_INT,        ANDAND_INT_FLOAT,      ANDAND_error, ANDAND_INT_BOOL,       ANDAND_arg_GLOBAL_VAR,        ANDAND_arg_LOCAL_VAR, 
//	ANDAND_arg_POINTER,        ANDAND_error, ANDAND_FLOAT_INT,      ANDAND_FLOAT_FLOAT,    ANDAND_error, ANDAND_FLOAT_BOOL,     ANDAND_arg_GLOBAL_VAR,        ANDAND_arg_LOCAL_VAR, 
//	ANDAND_error,     		   ANDAND_error, ANDAND_error,     	    ANDAND_error,     	   ANDAND_error, ANDAND_error,     		ANDAND_error,     			  ANDAND_error, 
//	ANDAND_arg_POINTER,        ANDAND_error, ANDAND_BOOL_INT,       ANDAND_BOOL_FLOAT,     ANDAND_error, ANDAND_BOOL_BOOL,      ANDAND_arg_GLOBAL_VAR,        ANDAND_arg_LOCAL_VAR, 
//	ANDAND_GLOBAL_VAR_POINTER, ANDAND_error, ANDAND_GLOBAL_VAR_arg, ANDAND_GLOBAL_VAR_arg, ANDAND_error, ANDAND_GLOBAL_VAR_arg, ANDAND_GLOBAL_VAR_GLOBAL_VAR, ANDAND_GLOBAL_VAR_LOCAL_VAR, 
//	ANDAND_LOCAL_VAR_POINTER,  ANDAND_error, ANDAND_LOCAL_VAR_arg,  ANDAND_LOCAL_VAR_arg,  ANDAND_error, ANDAND_LOCAL_VAR_arg,  ANDAND_LOCAL_VAR_GLOBAL_VAR,  ANDAND_LOCAL_VAR_LOCAL_VAR 
//};
//
//static fptr MxMORE			[8][8] =
//{
//	MORE_POINTER_POINTER,    MORE_error, MORE_POINTER_arg,    MORE_POINTER_arg,    MORE_error, MORE_POINTER_arg,    MORE_POINTER_GLOBAL_VAR,    MORE_POINTER_LOCAL_VAR, 
//	MORE_error,       	     MORE_error, MORE_error,       	  MORE_error,          MORE_error, MORE_error,       	MORE_error,       		    MORE_error, 
//	MORE_arg_POINTER,        MORE_error, MORE_INT_INT,        MORE_INT_FLOAT,      MORE_error, MORE_INT_BOOL,       MORE_arg_GLOBAL_VAR,        MORE_arg_LOCAL_VAR, 
//	MORE_arg_POINTER,        MORE_error, MORE_FLOAT_INT,      MORE_FLOAT_FLOAT,    MORE_error, MORE_FLOAT_BOOL,     MORE_arg_GLOBAL_VAR,        MORE_arg_LOCAL_VAR, 
//	MORE_error,     		 MORE_error, MORE_error,     	  MORE_error,     	   MORE_error, MORE_error,     		MORE_error,     			MORE_error, 
//	MORE_arg_POINTER,        MORE_error, MORE_BOOL_INT,       MORE_BOOL_FLOAT,     MORE_error, MORE_BOOL_BOOL,      MORE_arg_GLOBAL_VAR,        MORE_arg_LOCAL_VAR, 
//	MORE_GLOBAL_VAR_POINTER, MORE_error, MORE_GLOBAL_VAR_arg, MORE_GLOBAL_VAR_arg, MORE_error, MORE_GLOBAL_VAR_arg, MORE_GLOBAL_VAR_GLOBAL_VAR, MORE_GLOBAL_VAR_LOCAL_VAR, 
//	MORE_LOCAL_VAR_POINTER,  MORE_error, MORE_LOCAL_VAR_arg,  MORE_LOCAL_VAR_arg,  MORE_error, MORE_LOCAL_VAR_arg,  MORE_LOCAL_VAR_GLOBAL_VAR,  MORE_LOCAL_VAR_LOCAL_VAR 
//};
//
//static fptr MxMOREASSIGN		[8][8] =
//{
//	MOREASSIGN_POINTER_POINTER,	   MOREASSIGN_error, MOREASSIGN_POINTER_arg,    MOREASSIGN_POINTER_arg,    	MOREASSIGN_error, MOREASSIGN_POINTER_arg,    MOREASSIGN_POINTER_GLOBAL_VAR,    MOREASSIGN_POINTER_LOCAL_VAR, 
//	MOREASSIGN_error,			   MOREASSIGN_error, MOREASSIGN_error,       	MOREASSIGN_error,       	MOREASSIGN_error, MOREASSIGN_error,       	 MOREASSIGN_error,       		   MOREASSIGN_error, 
//	MOREASSIGN_arg_POINTER,		   MOREASSIGN_error, MOREASSIGN_INT_INT,        MOREASSIGN_INT_FLOAT,       MOREASSIGN_error, MOREASSIGN_INT_BOOL,       MOREASSIGN_arg_GLOBAL_VAR,        MOREASSIGN_arg_LOCAL_VAR, 
//	MOREASSIGN_arg_POINTER,		   MOREASSIGN_error, MOREASSIGN_FLOAT_INT,      MOREASSIGN_FLOAT_FLOAT,     MOREASSIGN_error, MOREASSIGN_FLOAT_BOOL,     MOREASSIGN_arg_GLOBAL_VAR,        MOREASSIGN_arg_LOCAL_VAR, 
//	MOREASSIGN_error,			   MOREASSIGN_error, MOREASSIGN_error,     	    MOREASSIGN_error,     		MOREASSIGN_error, MOREASSIGN_error,     	 MOREASSIGN_error,     		       MOREASSIGN_error, 
//	MOREASSIGN_arg_POINTER,		   MOREASSIGN_error, MOREASSIGN_BOOL_INT,       MOREASSIGN_BOOL_FLOAT,      MOREASSIGN_error, MOREASSIGN_BOOL_BOOL,      MOREASSIGN_arg_GLOBAL_VAR,        MOREASSIGN_arg_LOCAL_VAR, 
//	MOREASSIGN_GLOBAL_VAR_POINTER, MOREASSIGN_error, MOREASSIGN_GLOBAL_VAR_arg, MOREASSIGN_GLOBAL_VAR_arg, 	MOREASSIGN_error, MOREASSIGN_GLOBAL_VAR_arg, MOREASSIGN_GLOBAL_VAR_GLOBAL_VAR, MOREASSIGN_GLOBAL_VAR_LOCAL_VAR, 
//	MOREASSIGN_LOCAL_VAR_POINTER,  MOREASSIGN_error, MOREASSIGN_LOCAL_VAR_arg,  MOREASSIGN_LOCAL_VAR_arg,  	MOREASSIGN_error, MOREASSIGN_LOCAL_VAR_arg,  MOREASSIGN_LOCAL_VAR_GLOBAL_VAR,  MOREASSIGN_LOCAL_VAR_LOCAL_VAR 
//};
//
//static fptr MxLESS			[8][8] = 
//{
//	LESS_POINTER_POINTER,	 LESS_error, LESS_POINTER_arg,	  LESS_POINTER_arg,	   LESS_error, LESS_POINTER_arg,	LESS_POINTER_GLOBAL_VAR,	LESS_POINTER_LOCAL_VAR, 
//	LESS_error,			     LESS_error, LESS_error,		  LESS_error,		   LESS_error, LESS_error,			LESS_error,				    LESS_error, 
//	LESS_arg_POINTER,		 LESS_error, LESS_INT_INT,		  LESS_INT_FLOAT,	   LESS_error, LESS_INT_BOOL,		LESS_arg_GLOBAL_VAR,		LESS_arg_LOCAL_VAR, 
//	LESS_arg_POINTER,		 LESS_error, LESS_FLOAT_INT,	  LESS_FLOAT_FLOAT,	   LESS_error, LESS_FLOAT_BOOL,		LESS_arg_GLOBAL_VAR,		LESS_arg_LOCAL_VAR, 
//	LESS_error,			     LESS_error, LESS_error,		  LESS_error,		   LESS_error, LESS_error,			LESS_error,				    LESS_error, 
//	LESS_arg_POINTER,		 LESS_error, LESS_BOOL_INT,	      LESS_BOOL_FLOAT,	   LESS_error, LESS_BOOL_BOOL,		LESS_arg_GLOBAL_VAR,		LESS_arg_LOCAL_VAR, 
//	LESS_GLOBAL_VAR_POINTER, LESS_error, LESS_GLOBAL_VAR_arg, LESS_GLOBAL_VAR_arg, LESS_error, LESS_GLOBAL_VAR_arg, LESS_GLOBAL_VAR_GLOBAL_VAR, LESS_GLOBAL_VAR_LOCAL_VAR, 
//	LESS_LOCAL_VAR_POINTER,  LESS_error, LESS_LOCAL_VAR_arg,  LESS_LOCAL_VAR_arg,  LESS_error, LESS_LOCAL_VAR_arg,	LESS_LOCAL_VAR_GLOBAL_VAR,  LESS_LOCAL_VAR_LOCAL_VAR 
//};
//
//static fptr MxLESSASSIGN		[8][8] =
//{
//	LESSASSIGN_POINTER_POINTER,	   LESSASSIGN_error, LESSASSIGN_POINTER_arg,	LESSASSIGN_POINTER_arg,	   LESSASSIGN_error, LESSASSIGN_POINTER_arg,	LESSASSIGN_POINTER_GLOBAL_VAR,	  LESSASSIGN_POINTER_LOCAL_VAR, 
//	LESSASSIGN_error,		  	   LESSASSIGN_error, LESSASSIGN_error,		    LESSASSIGN_error,		   LESSASSIGN_error, LESSASSIGN_error,			LESSASSIGN_error,				  LESSASSIGN_error, 
//	LESSASSIGN_arg_POINTER,		   LESSASSIGN_error, LESSASSIGN_INT_INT,		LESSASSIGN_INT_FLOAT,	   LESSASSIGN_error, LESSASSIGN_INT_BOOL,		LESSASSIGN_arg_GLOBAL_VAR,		  LESSASSIGN_arg_LOCAL_VAR, 
//	LESSASSIGN_arg_POINTER,		   LESSASSIGN_error, LESSASSIGN_FLOAT_INT,	    LESSASSIGN_FLOAT_FLOAT,	   LESSASSIGN_error, LESSASSIGN_FLOAT_BOOL,		LESSASSIGN_arg_GLOBAL_VAR,		  LESSASSIGN_arg_LOCAL_VAR, 
//	LESSASSIGN_error,			   LESSASSIGN_error, LESSASSIGN_error,		    LESSASSIGN_error,		   LESSASSIGN_error, LESSASSIGN_error,			LESSASSIGN_error,				  LESSASSIGN_error, 
//	LESSASSIGN_arg_POINTER,		   LESSASSIGN_error, LESSASSIGN_BOOL_INT,		LESSASSIGN_BOOL_FLOAT,	   LESSASSIGN_error, LESSASSIGN_BOOL_BOOL,		LESSASSIGN_arg_GLOBAL_VAR,		  LESSASSIGN_arg_LOCAL_VAR, 
//	LESSASSIGN_GLOBAL_VAR_POINTER, LESSASSIGN_error, LESSASSIGN_GLOBAL_VAR_arg, LESSASSIGN_GLOBAL_VAR_arg, LESSASSIGN_error, LESSASSIGN_GLOBAL_VAR_arg, LESSASSIGN_GLOBAL_VAR_GLOBAL_VAR, LESSASSIGN_GLOBAL_VAR_LOCAL_VAR, 
//	LESSASSIGN_LOCAL_VAR_POINTER,  LESSASSIGN_error, LESSASSIGN_LOCAL_VAR_arg,  LESSASSIGN_LOCAL_VAR_arg,  LESSASSIGN_error, LESSASSIGN_LOCAL_VAR_arg,	LESSASSIGN_LOCAL_VAR_GLOBAL_VAR,  LESSASSIGN_LOCAL_VAR_LOCAL_VAR 
//};
//
//static fptr MxEXCLAMASSIGN	[8][8] = 
//{
//	EXCLAMASSIGN_POINTER_POINTER,	 EXCLAMASSIGN_error, EXCLAMASSIGN_POINTER_arg,	  EXCLAMASSIGN_POINTER_arg,	   EXCLAMASSIGN_POINTER_arg,	EXCLAMASSIGN_POINTER_arg,	 EXCLAMASSIGN_POINTER_GLOBAL_VAR,	   EXCLAMASSIGN_POINTER_LOCAL_VAR, 
//	EXCLAMASSIGN_error,			     EXCLAMASSIGN_error, EXCLAMASSIGN_error,		  EXCLAMASSIGN_error,		   EXCLAMASSIGN_error,		    EXCLAMASSIGN_error,			 EXCLAMASSIGN_error,				   EXCLAMASSIGN_error, 
//	EXCLAMASSIGN_arg_POINTER,		 EXCLAMASSIGN_error, EXCLAMASSIGN_INT_INT,		  EXCLAMASSIGN_INT_FLOAT,	   EXCLAMASSIGN_error,		    EXCLAMASSIGN_INT_BOOL,		 EXCLAMASSIGN_arg_GLOBAL_VAR,		   EXCLAMASSIGN_arg_LOCAL_VAR, 
//	EXCLAMASSIGN_arg_POINTER,		 EXCLAMASSIGN_error, EXCLAMASSIGN_FLOAT_INT,	  EXCLAMASSIGN_FLOAT_FLOAT,	   EXCLAMASSIGN_error,		    EXCLAMASSIGN_FLOAT_BOOL,	 EXCLAMASSIGN_arg_GLOBAL_VAR,		   EXCLAMASSIGN_arg_LOCAL_VAR, 
//	EXCLAMASSIGN_error,		         EXCLAMASSIGN_error, EXCLAMASSIGN_error,		  EXCLAMASSIGN_error,		   EXCLAMASSIGN_STRING_STRING,  EXCLAMASSIGN_error,			 EXCLAMASSIGN_arg_GLOBAL_VAR,		   EXCLAMASSIGN_arg_LOCAL_VAR, 
//	EXCLAMASSIGN_arg_POINTER,		 EXCLAMASSIGN_error, EXCLAMASSIGN_BOOL_INT,		  EXCLAMASSIGN_BOOL_FLOAT,	   EXCLAMASSIGN_error,		    EXCLAMASSIGN_BOOL_BOOL,		 EXCLAMASSIGN_arg_GLOBAL_VAR,		   EXCLAMASSIGN_arg_LOCAL_VAR, 
//	EXCLAMASSIGN_GLOBAL_VAR_POINTER, EXCLAMASSIGN_error, EXCLAMASSIGN_GLOBAL_VAR_arg, EXCLAMASSIGN_GLOBAL_VAR_arg, EXCLAMASSIGN_GLOBAL_VAR_arg, EXCLAMASSIGN_GLOBAL_VAR_arg, EXCLAMASSIGN_GLOBAL_VAR_GLOBAL_VAR,   EXCLAMASSIGN_GLOBAL_VAR_LOCAL_VAR, 
//	EXCLAMASSIGN_LOCAL_VAR_POINTER,  EXCLAMASSIGN_error, EXCLAMASSIGN_LOCAL_VAR_arg,  EXCLAMASSIGN_LOCAL_VAR_arg,  EXCLAMASSIGN_LOCAL_VAR_arg,  EXCLAMASSIGN_LOCAL_VAR_arg,	 EXCLAMASSIGN_LOCAL_VAR_GLOBAL_VAR,    EXCLAMASSIGN_LOCAL_VAR_LOCAL_VAR 
//};
//
//
///*
//====================================
//	Функции виртуальной машины
//====================================
//*/
//
////===========
////	+
////===========
//static static void PLUS								( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	MxPLUS[ arg1->argClass ][ arg2->argClass ]( arg1, arg2, res );
//}
//static void PLUS_POINTER_POINTER				( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	MxPLUS[ arg1->addrInstruction->instr.res.argClass ]
//		  [ arg2->addrInstruction->instr.res.argClass ]( &arg1->addrInstruction->instr.res, 
//														 &arg2->addrInstruction->instr.res, res );
//}
//static void PLUS_POINTER_arg					( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	MxPLUS[ arg1->addrInstruction->instr.res.argClass ]
//		  [ arg2->argClass ]( &arg1->addrInstruction->instr.res, arg2, res );
//}
//static void PLUS_POINTER_GLOBAL_VAR			( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	MxPLUS[ arg1->addrInstruction->instr.res.argClass ]
//	      [ arg2->addrGlobal->argClass ]( &arg1->addrInstruction->instr.res, arg2->addrGlobal, res );
//}
//static void PLUS_POINTER_LOCAL_VAR				( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	MxPLUS[ arg1->addrInstruction->instr.res.argClass ]
//		  [ ::VMArr[ ::curVM ]->frameStack.Keep().localVars[ arg2->addrLocal ].argClass ]
//		  ( &arg1->addrInstruction->instr.res, &::VMArr[ ::curVM ]->frameStack.Keep().localVars[ arg2->addrLocal ], res );
//}
//static void PLUS_error							( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	// error
//}
//static void PLUS_arg_POINTER					( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	MxPLUS[ arg1->argClass ][ arg2->addrInstruction->instr.res.argClass ]
//		  ( arg1, &arg2->addrInstruction->instr.res, res );
//}
//static void PLUS_INT_INT						( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	res->argClass = ARGC_INT;
//	res->valInt	  = arg1->valInt + arg2->valInt;
//}
//static void PLUS_INT_FLOAT						( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	res->argClass = ARGC_FLOAT;
//	res->valFloat = static_cast<float>(arg1->valInt) + arg2->valFloat;
//
//}
//static void PLUS_INT_STRING					( arg_t* arg1, arg_t* arg2, arg_t* res ){
//}
//static void PLUS_INT_BOOL						( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	res->argClass = ARGC_INT;
//	res->valInt   = arg1->valInt + static_cast<int>(arg2->valBool);
//}
//static void PLUS_arg_GLOBAL_VAR					( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	MxPLUS[ arg1->argClass ]
//		  [ arg2->addrGlobal->argClass ]( arg1, arg2->addrGlobal, res );
//}
//static void PLUS_arg_LOCAL_VAR					( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	MxPLUS[ arg1->argClass ]
//		  [ ::VMArr[ ::curVM ]->frameStack.Keep().localVars[ arg2->addrLocal ].argClass ]
//		  ( arg1, &::VMArr[ ::curVM ]->frameStack.Keep().localVars[ arg2->addrLocal ], res );
//}
//static void PLUS_FLOAT_INT						( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	res->argClass = ARGC_FLOAT;
//	res->valFloat = arg1->valFloat + static_cast<float>(arg2->valInt);
//}
//static void PLUS_FLOAT_FLOAT					( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	res->argClass = ARGC_FLOAT;
//	res->valFloat = arg1->valFloat + arg2->valFloat;
//}
//static void PLUS_FLOAT_STRING					( arg_t* arg1, arg_t* arg2, arg_t* res ){
//}
//static void PLUS_FLOAT_BOOL					( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	res->argClass = ARGC_FLOAT;
//	res->valFloat = arg1->valFloat + static_cast<float>(arg2->valBool);
//}
//static void PLUS_STRING_INT					( arg_t* arg1, arg_t* arg2, arg_t* res ){
//}
//static void PLUS_STRING_FLOAT					( arg_t* arg1, arg_t* arg2, arg_t* res ){
//}
//static void PLUS_STRING_STRING					( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	if( res->valStr && res->argClass == ARGC_STRING )
//		delete[] res->valStr;
//	else
//		res->argClass = ARGC_STRING;
//
//	size_t len = strlen( arg1->valStr ) + strlen( arg2->valStr ) + 1;
//	res->valStr = new char[ len ];
//	memset( res->valStr, 0x0000, len );
//	strcpy( res->valStr, arg1->valStr );
//	strcat( res->valStr, arg2->valStr );
//}
//static void PLUS_STRING_BOOL					( arg_t* arg1, arg_t* arg2, arg_t* res ){
//}
//static void PLUS_BOOL_INT						( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	res->argClass = ARGC_INT;
//	res->valInt   = static_cast<int>(arg1->valBool) + arg2->valInt;
//}
//static void PLUS_BOOL_FLOAT					( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	res->argClass = ARGC_FLOAT;
//	res->valFloat = static_cast<float>(arg1->valBool) + arg2->valFloat;
//}
//static void PLUS_BOOL_STRING					( arg_t* arg1, arg_t* arg2, arg_t* res ){
//}
//static void PLUS_BOOL_BOOL						( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	res->argClass = ARGC_INT;
//	res->valInt   = static_cast<int>(arg1->valBool) + static_cast<int>(arg2->valBool);
//}
//static void PLUS_GLOBAL_VAR_POINTER			( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	MxPLUS[ arg1->addrGlobal->argClass ]
//		  [ arg2->addrInstruction->instr.res.argClass ]( arg1->addrGlobal, &arg2->addrInstruction->instr.res, res );
//}
//static void PLUS_GLOBAL_VAR_arg				( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	MxPLUS[ arg1->addrGlobal->argClass ]
//		  [ arg2->argClass ]( arg1->addrGlobal, arg2, res );
//}
//static void PLUS_GLOBAL_VAR_GLOBAL_VAR			( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	MxPLUS[ arg1->addrGlobal->argClass ]	
//		  [ arg2->addrGlobal->argClass ]( arg1->addrGlobal,
//										  arg2->addrGlobal, res );
//}
//static void PLUS_GLOBAL_VAR_LOCAL_VAR			( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	MxPLUS[ arg1->addrGlobal->argClass ]
//		  [ ::VMArr[ ::curVM ]->frameStack.Keep().localVars[ arg2->addrLocal ].argClass ]
//		  ( arg1->addrGlobal, &::VMArr[ ::curVM ]->frameStack.Keep().localVars[ arg2->addrLocal ], res );
//}
//static void PLUS_LOCAL_VAR_POINTER				( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	MxPLUS[ ::VMArr[ ::curVM ]->frameStack.Keep().localVars[ arg2->addrLocal ].argClass ]
//		  [ arg2->addrInstruction->instr.res.argClass ]( &::VMArr[ ::curVM ]->frameStack.Keep().localVars[ arg2->addrLocal ], 
//														 &arg2->addrInstruction->instr.res, res );
//}
//static void PLUS_LOCAL_VAR_arg					( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	MxPLUS[ ::VMArr[ ::curVM ]->frameStack.Keep().localVars[ arg2->addrLocal ].argClass ]
//		  [ arg2->argClass ]( &::VMArr[ ::curVM ]->frameStack.Keep().localVars[ arg2->addrLocal ], arg2, res );
//}
//static void PLUS_LOCAL_VAR_GLOBAL_VAR			( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	MxPLUS[ ::VMArr[ ::curVM ]->frameStack.Keep().localVars[ arg2->addrLocal ].argClass ]
//		  [ arg2->addrGlobal->argClass ]( &::VMArr[ ::curVM ]->frameStack.Keep().localVars[ arg2->addrLocal ], 
//										  arg2->addrGlobal, res );
//}
//static void PLUS_LOCAL_VAR_LOCAL_VAR			( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	MxPLUS[ ::VMArr[ ::curVM ]->frameStack.Keep().localVars[ arg1->addrLocal ].argClass ]
//		  [ ::VMArr[ ::curVM ]->frameStack.Keep().localVars[ arg2->addrLocal ].argClass ]
//		  ( &::VMArr[ ::curVM ]->frameStack.Keep().localVars[ arg1->addrLocal ],
//		    &::VMArr[ ::curVM ]->frameStack.Keep().localVars[ arg2->addrLocal ], res );
//}
//
//
////===========
////	+=
////===========
//static void PLUSASSIGN							( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	PLUS( arg1, arg2, res );
//	ASSIGN( arg1, res, res );
//}
//
//
////===========
////	-
////===========
//static void MINUS								( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	MxMINUS[ arg1->argClass ][ arg2->argClass ]( arg1, arg2, res );
//}
//static void MINUS_POINTER_POINTER				( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	MxMINUS[ arg1->addrInstruction->instr.res.argClass ]
//		   [ arg2->addrInstruction->instr.res.argClass ]( &arg1->addrInstruction->instr.res,
//														  &arg1->addrInstruction->instr.res,
//														  res );
//}
//static void MINUS_POINTER_GLOBAL_VAR			( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	MxMINUS[ arg1->addrInstruction->instr.res.argClass ]
//		   [ arg2->addrGlobal->argClass ]( &arg1->addrInstruction->instr.res, arg2->addrGlobal, res );
//}
//static void MINUS_POINTER_LOCAL_VAR			( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	MxMINUS[ arg1->addrInstruction->instr.res.argClass ]
//		   [ ::VMArr[ ::curVM ]->frameStack.Keep().localVars[ arg2->addrLocal ].argClass ]( &arg1->addrInstruction->instr.res, &::VMArr[ ::curVM ]->frameStack.Keep().localVars[ arg2->addrLocal ], res );
//}
//static void MINUS_POINTER_arg ( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	MxMINUS[ arg1->addrInstruction->instr.res.argClass ]
//		   [ arg2->argClass ]( &arg1->addrInstruction->instr.res, arg2, res );
//}
//static void MINUS_error						( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	//error
//}
//static void MINUS_arg_POINTER					( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	MxMINUS[ arg1->argClass ]
//		   [ arg2->addrInstruction->instr.res.argClass ]( arg1, &arg2->addrInstruction->instr.res, res );
//}
//static void MINUS_INT_INT						( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	res->argClass = ARGC_INT;
//	res->valInt   = arg1->valInt + arg2->valInt;
//}
//static void MINUS_INT_FLOAT					( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	res->argClass = ARGC_FLOAT;
//	res->valFloat = static_cast<float>(arg1->valInt) - arg2->valFloat;
//}
//static void MINUS_INT_BOOL						( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	res->argClass = ARGC_INT;
//	res->valInt   = arg1->valInt - static_cast<int>(arg2->valBool);
//}
//static void MINUS_arg_GLOBAL_VAR				( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	MxMINUS[ arg1->argClass ][ arg2->addrGlobal->argClass ]( arg1, arg2->addrGlobal, res );
//}
//static void MINUS_arg_LOCAL_VAR				( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	MxMINUS[ arg1->argClass ][ arg2->addrGlobal->argClass ]( arg1, arg2->addrGlobal, res );
//}
//static void MINUS_FLOAT_INT					( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	res->argClass = ARGC_FLOAT;
//	res->valFloat = arg1->valFloat - static_cast<float>(arg2->valInt);
//}
//static void MINUS_FLOAT_FLOAT					( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	res->argClass = ARGC_FLOAT;
//	res->valFloat = arg1->valFloat - arg2->valFloat;
//}
//static void MINUS_FLOAT_BOOL					( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	res->argClass = ARGC_FLOAT;
//	res->valFloat = arg1->valFloat - static_cast<float>(arg2->valBool);
//}
//static void MINUS_BOOL_INT						( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	res->argClass = ARGC_INT;
//	res->valInt   = static_cast<int>(arg1->valBool) - arg2->valInt;
//}
//static void MINUS_BOOL_FLOAT					( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	res->argClass = ARGC_FLOAT;
//	res->valFloat = static_cast<float>(arg1->valBool) - arg2->valFloat;
//}
//static void MINUS_BOOL_BOOL					( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	res->argClass = ARGC_INT;
//	res->valInt   = static_cast<int>(arg1->valBool) - static_cast<int>(arg2->valBool);
//}
//static void MINUS_GLOBAL_VAR_POINTER			( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	MxMINUS[ arg1->addrGlobal->argClass ]
//		   [ arg2->addrInstruction->instr.res.argClass ]( arg1->addrGlobal, &arg2->addrInstruction->instr.res, res );
//}
//static void MINUS_GLOBAL_VAR_arg				( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	MxMINUS[ arg1->addrGlobal->argClass ][ arg2->argClass ]( arg1->addrGlobal, arg2, res );
//}
//static void MINUS_GLOBAL_VAR_GLOBAL_VAR		( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	MxMINUS[ arg1->addrGlobal->argClass ]
//		   [ arg2->addrGlobal->argClass ]( arg1->addrGlobal, arg2->addrGlobal, res );
//}
//static void MINUS_GLOBAL_VAR_LOCAL_VAR			( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	MxMINUS[ arg1->addrGlobal->argClass ][ ::VMArr[ ::curVM ]->frameStack.Keep().localVars[arg2->addrLocal].argClass ]
//	( arg1->addrGlobal, &::VMArr[ ::curVM ]->frameStack.Keep().localVars[arg2->addrLocal], res );
//}
//static void MINUS_LOCAL_VAR_POINTER			( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	MxMINUS[ ::VMArr[ ::curVM ]->frameStack.Keep().localVars[ arg1->addrLocal ].argClass ]
//		   [ arg2->addrInstruction->instr.res.argClass ]
//		   ( &::VMArr[ ::curVM ]->frameStack.Keep().localVars[ arg1->addrLocal ],
//		     &arg2->addrInstruction->instr.res, res );
//}
//static void MINUS_LOCAL_VAR_arg				( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	MxMINUS[ ::VMArr[ ::curVM ]->frameStack.Keep().localVars[ arg1->addrLocal ].argClass ]
//		   [ arg2->argClass ]
//		   ( &::VMArr[ ::curVM ]->frameStack.Keep().localVars[ arg1->addrLocal ], arg2, res );
//}
//static void MINUS_LOCAL_VAR_GLOBAL_VAR			( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	MxMINUS[ ::VMArr[ ::curVM ]->frameStack.Keep().localVars[ arg1->addrLocal ].argClass ]
//		   [ arg2->addrGlobal->argClass ]
//		   ( &::VMArr[ ::curVM ]->frameStack.Keep().localVars[ arg1->addrLocal ], arg2->addrGlobal, res );
//}
//static void MINUS_LOCAL_VAR_LOCAL_VAR			( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	MxMINUS[ ::VMArr[ ::curVM ]->frameStack.Keep().localVars[ arg1->addrLocal ].argClass ]
//		   [ ::VMArr[ ::curVM ]->frameStack.Keep().localVars[ arg2->addrLocal ].argClass ]
//		   ( &::VMArr[ ::curVM ]->frameStack.Keep().localVars[ arg1->addrLocal ],
//		 	 &::VMArr[ ::curVM ]->frameStack.Keep().localVars[ arg2->addrLocal ], res );
//}
//
//
////===========
////	-=
////===========
//static void MINUSASSIGN						( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	MINUS( arg1, arg2, res );
//	ASSIGN( arg1, res, res );
//}
//
//
////===========
////	*
////===========
//static void STAR								( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	MxSTAR[ arg1->argClass ][ arg2->argClass ]( arg1, arg2, res );
//}
//static void STAR_POINTER_POINTER				( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	MxSTAR[ arg1->addrInstruction->instr.res.argClass ]
//	      [ arg2->addrInstruction->instr.res.argClass ]( &arg1->addrInstruction->instr.res,
//														 &arg2->addrInstruction->instr.res,
//														 res );
//}
//static void STAR_POINTER_GLOBAL_VAR			( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	MxSTAR[ arg1->addrInstruction->instr.res.argClass ]
//		  [ arg2->addrGlobal->argClass ]( &arg1->addrInstruction->instr.res, arg2->addrGlobal, res );
//}
//static void STAR_POINTER_LOCAL_VAR				( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	MxSTAR[ arg1->addrInstruction->instr.res.argClass ]
//		  [ ::VMArr[ ::curVM ]->frameStack.Keep().localVars[ arg2->addrLocal ].argClass ]
//		  ( &arg1->addrInstruction->instr.res, &::VMArr[ ::curVM ]->frameStack.Keep().localVars[ arg2->addrLocal ], res );
//}
//
//static void STAR_POINTER_arg ( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	MxSTAR[ arg1->addrInstruction->instr.res.argClass ]
//		  [ arg2->argClass ]( &arg1->addrInstruction->instr.res, arg2, res );
//}
//
//static void STAR_error							( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	// error
//}
//
//static void STAR_arg_POINTER					( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	MxSTAR[ arg1->argClass ]
//		  [ arg2->addrInstruction->instr.res.argClass ]( arg1, &arg2->addrInstruction->instr.res, res );
//}
//static void STAR_INT_INT						( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	res->argClass = ARGC_INT;
//	res->valInt   = arg1->valInt * arg2->valInt;
//}
//static void STAR_INT_FLOAT						( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	res->argClass = ARGC_FLOAT;
//	res->valFloat = static_cast<float>(arg1->valInt) * arg2->valFloat;
//}
//static void STAR_INT_BOOL						( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	res->argClass = ARGC_INT;
//	res->valInt   = arg1->valInt * static_cast<int>(arg2->valBool);
//}
//static void STAR_arg_GLOBAL_VAR				( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	MxSTAR[ arg1->argClass ][ arg2->addrGlobal->argClass ]( arg1, arg2->addrGlobal, res );
//}
//static void STAR_arg_LOCAL_VAR					( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	MxSTAR[ arg1->argClass ]
//		  [ ::VMArr[ ::curVM ]->frameStack.Keep().localVars[ arg2->addrLocal ].argClass ]
//		  ( arg1, &::VMArr[ ::curVM ]->frameStack.Keep().localVars[ arg2->addrLocal ], res );
//}
//static void STAR_FLOAT_INT						( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	res->argClass = ARGC_FLOAT;
//	res->valFloat = arg1->valFloat * static_cast<float>(arg2->valInt);
//}
//static void STAR_FLOAT_FLOAT					( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	res->argClass = ARGC_FLOAT;
//	res->valFloat = arg1->valFloat * arg2->valFloat;
//}
//static void STAR_FLOAT_BOOL					( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	res->argClass = ARGC_FLOAT;
//	res->valFloat = arg1->valFloat * static_cast<float>(arg2->valBool);
//}
//static void STAR_BOOL_INT						( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	res->argClass = ARGC_INT;
//	res->valInt   = static_cast<int>(arg1->valBool) * arg2->valInt;
//}
//static void STAR_BOOL_FLOAT					( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	res->argClass = ARGC_FLOAT;
//	res->valFloat   = static_cast<float>(arg1->valBool) * arg2->valFloat;
//}
//static void STAR_BOOL_BOOL						( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	res->argClass = ARGC_INT;
//	res->valInt   = static_cast<int>(arg1->valBool) * static_cast<int>(arg2->valBool);
//}
//static void STAR_GLOBAL_VAR_POINTER			( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	MxSTAR[ arg1->addrGlobal->argClass ]
//	[ arg2->addrInstruction->instr.res.argClass ]( arg1->addrGlobal ,
//												   &arg2->addrInstruction->instr.res, res );
//}
//static void STAR_GLOBAL_VAR_arg				( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	MxSTAR[ arg1->addrGlobal->argClass ][ arg2->argClass ]( arg1->addrGlobal, arg2, res );
//}
//static void STAR_GLOBAL_VAR_GLOBAL_VAR			( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	MxSTAR[ arg1->addrGlobal->argClass ]
//		  [ arg2->addrGlobal->argClass ]( arg1->addrGlobal, arg2->addrGlobal, res );
//}
//static void STAR_GLOBAL_VAR_LOCAL_VAR			( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	MxSTAR[ arg1->addrGlobal->argClass ]
//		  [ ::VMArr[ ::curVM ]->frameStack.Keep().localVars[ arg2->addrLocal ].argClass ]
//		  ( arg1->addrGlobal, &::VMArr[ ::curVM ]->frameStack.Keep().localVars[ arg2->addrLocal ], res );
//}
//
//static void STAR_LOCAL_VAR_POINTER				( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	MxSTAR[ ::VMArr[ ::curVM ]->frameStack.Keep().localVars[ arg1->addrLocal ].argClass ]
//		  [ arg2->addrInstruction->instr.res.argClass ]
//		  ( &::VMArr[ ::curVM ]->frameStack.Keep().localVars[ arg1->addrLocal ], &arg2->addrInstruction->instr.res, res );
//}
//static void STAR_LOCAL_VAR_arg					( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	MxSTAR[ ::VMArr[ ::curVM ]->frameStack.Keep().localVars[ arg1->addrLocal ].argClass ]
//		  [ arg2->argClass ]
//		  ( &::VMArr[ ::curVM ]->frameStack.Keep().localVars[ arg1->addrLocal ], arg2, res );
//}
//static void STAR_LOCAL_VAR_GLOBAL_VAR			( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	MxSTAR[ ::VMArr[ ::curVM ]->frameStack.Keep().localVars[ arg1->addrLocal ].argClass ]
//		  [ arg2->addrGlobal->argClass ]
//		  ( &::VMArr[ ::curVM ]->frameStack.Keep().localVars[ arg1->addrLocal ], arg2->addrGlobal, res );
//}
// static void STAR_LOCAL_VAR_LOCAL_VAR			( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	MxSTAR[ ::VMArr[ ::curVM ]->frameStack.Keep().localVars[ arg1->addrLocal ].argClass ]
//		  [ ::VMArr[ ::curVM ]->frameStack.Keep().localVars[ arg2->addrLocal ].argClass ]
//		  ( &::VMArr[ ::curVM ]->frameStack.Keep().localVars[ arg1->addrLocal ],
//			&::VMArr[ ::curVM ]->frameStack.Keep().localVars[ arg2->addrLocal ], res );
//}
//
////===========
////	*=
////===========
//static void STARASSIGN							( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	STAR( arg1, arg2, res );
//	ASSIGN( arg1, res, res );
//}
//
////===========
////	/
////===========
//static void SLASH								( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	MxSLASH[ arg1->argClass ][ arg2->argClass ]( arg1, arg2, res );
//}
//
//static void SLASH_POINTER_POINTER				( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	MxSLASH[ arg1->addrInstruction->instr.res.argClass ]
//	       [ arg2->addrInstruction->instr.res.argClass ]( &arg1->addrInstruction->instr.res,
//														  &arg2->addrInstruction->instr.res,
//														  res );
//}
//static void SLASH_POINTER_GLOBAL_VAR			( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	MxSLASH[ arg1->addrInstruction->instr.res.argClass ]
//		   [ arg2->addrGlobal->argClass ]( &arg1->addrInstruction->instr.res, arg2->addrGlobal, res );
//}
//static void SLASH_POINTER_LOCAL_VAR			( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	MxSLASH[ arg1->addrInstruction->instr.res.argClass ]
//		   [ ::VMArr[ ::curVM ]->frameStack.Keep().localVars[ arg2->addrLocal ].argClass ]
//		   ( &arg1->addrInstruction->instr.res, 
//		     &::VMArr[ ::curVM ]->frameStack.Keep().localVars[ arg2->addrLocal ], res );
//}
//static void SLASH_POINTER_arg ( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	MxSLASH[ arg1->addrInstruction->instr.res.argClass ]
//		   [ arg2->argClass ]( &arg1->addrInstruction->instr.res, arg2, res );
//}
//static void SLASH_error						( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	// error
//}
//static void SLASH_arg_POINTER					( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	MxSLASH[ arg1->argClass ]
//		   [ arg2->addrInstruction->instr.res.argClass ]( arg1, &arg2->addrInstruction->instr.res, res );
//}
//static void SLASH_INT_INT						( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	res->argClass = ARGC_INT;
//	res->valInt = arg1->valInt / arg2->valInt;
//}
//static void SLASH_INT_FLOAT					( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	res->argClass = ARGC_FLOAT;
//	res->valFloat = static_cast<float>(arg1->valInt) / arg2->valFloat;
//}
//static void SLASH_INT_BOOL						( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	res->argClass = ARGC_INT;
//	res->valInt   = arg1->valInt / static_cast<int>(arg2->valBool);
//}
//static void SLASH_arg_GLOBAL_VAR				( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	MxSLASH[ arg1->argClass ][ arg2->addrGlobal->argClass ]( arg1, arg2->addrGlobal, res );
//}
//static void SLASH_arg_LOCAL_VAR				( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	MxSLASH[ arg1->argClass ][ ::VMArr[ ::curVM ]->frameStack.Keep().localVars[ arg2->addrLocal ].argClass ]
//		   ( arg1, &::VMArr[ ::curVM ]->frameStack.Keep().localVars[ arg2->addrLocal ], res );	
//}
//static void SLASH_FLOAT_INT					( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	res->argClass = ARGC_FLOAT;
//	res->valFloat = arg1->valFloat / static_cast<float>(arg2->valInt);
//}
//static void SLASH_FLOAT_FLOAT					( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	res->argClass = ARGC_FLOAT;
//	res->valFloat = arg1->valFloat / arg2->valFloat;
//}
//static void SLASH_FLOAT_BOOL					( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	res->argClass = ARGC_FLOAT;
//	res->valFloat = arg1->valFloat / static_cast<float>(arg2->valBool);
//}
//static void SLASH_BOOL_INT						( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	res->argClass = ARGC_INT;
//	res->valInt   = static_cast<int>(static_cast<int>(arg1->valBool) / arg2->valInt);
//}
//static void SLASH_BOOL_FLOAT					( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	res->argClass = ARGC_FLOAT;
//	res->valFloat   = static_cast<float>(arg1->valBool) / arg2->valFloat;
//}
//static void SLASH_BOOL_BOOL					( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	res->argClass = ARGC_BOOL;
//	res->valBool   = static_cast<bool>( static_cast<float>(arg1->valBool) / static_cast<float>(arg2->valBool) );
//}
//static void SLASH_GLOBAL_VAR_POINTER			( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	MxSLASH[ arg1->addrGlobal->argClass ]
//		   [ arg2->addrInstruction->instr.res.argClass ]( arg1->addrGlobal, 
//														  &arg2->addrInstruction->instr.res, res );
//}
//static void SLASH_GLOBAL_VAR_arg				( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	MxSLASH[ arg1->addrGlobal->argClass ][ arg2->argClass ]( arg1->addrGlobal, arg2, res );
//}
//static void SLASH_GLOBAL_VAR_GLOBAL_VAR		( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	MxSLASH[ arg1->addrGlobal->argClass ][ arg2->addrGlobal->argClass ]( arg1->addrGlobal,
//																		 arg2->addrGlobal, res );
//}
//static void SLASH_GLOBAL_VAR_LOCAL_VAR			( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	MxSLASH[ arg1->addrGlobal->argClass ][ arg2->addrGlobal->argClass ]( arg1->addrGlobal,
//																		 arg2->addrGlobal, res );
//}
//static void SLASH_LOCAL_VAR_POINTER			( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	MxSLASH[ ::VMArr[ ::curVM ]->frameStack.Keep().localVars[ arg1->addrLocal ].argClass ]
//		   [ arg2->addrInstruction->instr.res.argClass ]
//		   ( &::VMArr[ ::curVM ]->frameStack.Keep().localVars[ arg1->addrLocal ],
//		     &arg2->addrInstruction->instr.res, res );									
//}
//static void SLASH_LOCAL_VAR_arg				( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	MxSLASH[ ::VMArr[ ::curVM ]->frameStack.Keep().localVars[ arg1->addrLocal ].argClass ]
//		   [ arg2->argClass ]
//		   ( &::VMArr[ ::curVM ]->frameStack.Keep().localVars[ arg1->addrLocal ], arg2, res );
//}
//static void SLASH_LOCAL_VAR_GLOBAL_VAR			( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	MxSLASH[ ::VMArr[ ::curVM ]->frameStack.Keep().localVars[ arg1->addrLocal ].argClass ]
//		   [ arg2->addrGlobal->argClass ]
//		   ( &::VMArr[ ::curVM ]->frameStack.Keep().localVars[ arg1->addrLocal ], arg2->addrGlobal, res );
//}
//static void SLASH_LOCAL_VAR_LOCAL_VAR			( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	MxSLASH[ ::VMArr[ ::curVM ]->frameStack.Keep().localVars[ arg1->addrLocal ].argClass ]
//		   [ ::VMArr[ ::curVM ]->frameStack.Keep().localVars[ arg2->addrLocal ].argClass ]
//		   ( &::VMArr[ ::curVM ]->frameStack.Keep().localVars[ arg1->addrLocal ],
//			 &::VMArr[ ::curVM ]->frameStack.Keep().localVars[ arg2->addrLocal ], res );
//}
//
//
////===========
////	/=
////===========
//static void SLASHASSIGN						( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	SLASH( arg1, arg2, res );
//	ASSIGN( arg1, res, res );
//}
//
////===========
////	%
////===========
//static void PERCENT							( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	MxPERCENT[ arg1->argClass ][ arg2->argClass ]( arg1, arg2, res );
//}
//
//static void PERCENT_POINTER_POINTER			( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	MxPERCENT[ arg1->addrInstruction->instr.res.argClass ]
//	         [ arg2->addrInstruction->instr.res.argClass ]( &arg1->addrInstruction->instr.res,
//														    &arg2->addrInstruction->instr.res,
//														    res );
//}
//static void PERCENT_POINTER_GLOBAL_VAR			( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	MxPERCENT[ arg1->addrInstruction->instr.res.argClass ]
//			 [ arg2->addrGlobal->argClass ]
//			 ( &arg1->addrInstruction->instr.res, arg2->addrGlobal, res );
//}
//static void PERCENT_POINTER_LOCAL_VAR			( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	MxPERCENT[ arg1->addrInstruction->instr.res.argClass ]
//			 [ ::VMArr[ ::curVM ]->frameStack.Keep().localVars[ arg2->addrLocal ].argClass ]
//			 ( &arg1->addrInstruction->instr.res, 
//			   &::VMArr[ ::curVM ]->frameStack.Keep().localVars[ arg2->addrLocal ], res );
//}
//static void PERCENT_POINTER_arg				( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	MxPERCENT[ arg1->addrInstruction->instr.res.argClass ]
//		     [ arg2->argClass ]( &arg1->addrInstruction->instr.res, arg2, res );
//}
//static void PERCENT_error						( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	// error
//}
//static void PERCENT_arg_POINTER				( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	MxPERCENT[ arg1->argClass ]
//		     [ arg2->addrInstruction->instr.res.argClass ]( arg1, &arg2->addrInstruction->instr.res, res );
//}
//static void PERCENT_INT_INT					( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	res->argClass = ARGC_INT;
//	res->valInt = arg1->valInt % arg2->valInt;
//}
//static void PERCENT_INT_BOOL					( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	res->argClass = ARGC_INT;
//	res->valInt   = arg1->valInt % static_cast<int>(arg2->valBool);
//}
//static void PERCENT_arg_GLOBAL_VAR				( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	MxPERCENT[ arg1->argClass ][ arg2->addrGlobal->argClass ]( arg1, arg2->addrGlobal, res );
//}
//static void PERCENT_arg_LOCAL_VAR				( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	MxPERCENT[ arg1->argClass ]
//			 [ ::VMArr[ ::curVM ]->frameStack.Keep().localVars[ arg2->addrLocal ].argClass ]
//			 ( arg1, &::VMArr[ ::curVM ]->frameStack.Keep().localVars[ arg2->addrLocal ], res );
//}
//static void PERCENT_BOOL_INT					( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	res->argClass = ARGC_INT;
//	res->valInt   = static_cast<int>(arg1->valBool) % arg2->valInt;
//}
//static void PERCENT_BOOL_BOOL					( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	res->argClass = ARGC_BOOL;
//	res->valBool  = static_cast<int>(arg1->valBool) % static_cast<int>(arg2->valBool);
//}
//static void PERCENT_GLOBAL_VAR_POINTER			( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	MxPERCENT[ arg1->addrGlobal->argClass ]
//			 [ arg2->addrInstruction->instr.res.argClass ]( arg1->addrGlobal, 
//															&arg2->addrInstruction->instr.res, res );
//}
//static void PERCENT_GLOBAL_VAR_arg				( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	MxPERCENT[ arg1->addrGlobal->argClass ][ arg2->argClass ]( arg1->addrGlobal, arg2, res );
//}
//static void PERCENT_GLOBAL_VAR_GLOBAL_VAR		( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	MxPERCENT[ arg1->addrGlobal->argClass ]
//			 [ arg2->addrGlobal->argClass ]( arg1->addrGlobal, arg2->addrGlobal, res );
//}
//static void PERCENT_GLOBAL_VAR_LOCAL_VAR		( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	MxPERCENT[ arg1->addrGlobal->argClass ]
//			 [ ::VMArr[ ::curVM ]->frameStack.Keep().localVars[ arg2->addrLocal ].argClass ]
//			 ( arg1->addrGlobal, &::VMArr[ ::curVM ]->frameStack.Keep().localVars[ arg2->addrLocal ], res );
//}
//
//static void PERCENT_LOCAL_VAR_POINTER			( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	MxPERCENT[ ::VMArr[ ::curVM ]->frameStack.Keep().localVars[ arg1->addrLocal ].argClass ]
//			 [ arg2->addrInstruction->instr.res.argClass ]
//			 ( &::VMArr[ ::curVM ]->frameStack.Keep().localVars[ arg1->addrLocal ], 
//			   &arg2->addrInstruction->instr.res, res );
//}
//static void PERCENT_LOCAL_VAR_arg				( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	MxPERCENT[ ::VMArr[ ::curVM ]->frameStack.Keep().localVars[ arg1->addrLocal ].argClass ]
//			 [ arg2->argClass ]
//			 ( &::VMArr[ ::curVM ]->frameStack.Keep().localVars[ arg1->addrLocal ], arg2, res );
//}
//static void PERCENT_LOCAL_VAR_GLOBAL_VAR		( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	MxPERCENT[ ::VMArr[ ::curVM ]->frameStack.Keep().localVars[ arg1->addrLocal ].argClass ]
//			 [ arg2->addrGlobal->argClass ]
//			 ( &::VMArr[ ::curVM ]->frameStack.Keep().localVars[ arg1->addrLocal ], arg2->addrGlobal, res );
//}
//static void PERCENT_LOCAL_VAR_LOCAL_VAR			( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	MxPERCENT[ ::VMArr[ ::curVM ]->frameStack.Keep().localVars[ arg1->addrLocal ].argClass ]
//			 [ ::VMArr[ ::curVM ]->frameStack.Keep().localVars[ arg2->addrLocal ].argClass ]
//			 ( &::VMArr[ ::curVM ]->frameStack.Keep().localVars[ arg1->addrLocal ], 
//			   &::VMArr[ ::curVM ]->frameStack.Keep().localVars[ arg2->addrLocal ], res );
//}
//
//
////===========
////	%=
////===========
//static void PERCENTASSIGN						( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	PERCENT( arg1, arg2, res );
//	ASSIGN( arg1, res, res );
//}
//
////===========
////	=
////===========
//static void ASSIGN								( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	MxASSIGN[ arg1->argClass ][ arg2->argClass ]( arg1, arg2, res );
//}
//static void ASSIGN_INT_INT						( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	res->argClass = ARGC_INT;
//	arg1->valInt = res->valInt = arg2->valInt;
//}
//static void ASSIGN_INT_FLOAT					( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	res->argClass = ARGC_INT;
//	arg1->valInt = res->valInt = static_cast<int>(arg2->valFloat);
//}
//static void ASSIGN_INT_BOOL					( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	res->argClass = ARGC_INT;
//	arg1->valInt = res->valInt = arg2->valBool;
//}
//static void ASSIGN_FLOAT_INT					( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	res->argClass = ARGC_FLOAT;
//	arg1->valFloat = res->valFloat = static_cast<float>(arg2->valInt);
//}
//static void ASSIGN_FLOAT_FLOAT					( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	res->argClass = ARGC_FLOAT;
//	arg1->valFloat = res->valFloat = arg2->valFloat;
//}
//static void ASSIGN_FLOAT_BOOL					( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	res->argClass = ARGC_FLOAT;
//	arg1->valFloat = res->valFloat = static_cast<float>(arg2->valBool);
//}
//static void ASSIGN_STRING_STRING				( arg_t* arg1, arg_t* arg2, arg_t* res ){
//
//}
//static void ASSIGN_STRING_INT					( arg_t* arg1, arg_t* arg2, arg_t* res ){
//
//}
//static void ASSIGN_STRING_FLOAT				( arg_t* arg1, arg_t* arg2, arg_t* res ){
//
//}
//static void ASSIGN_STRING_BOOL					( arg_t* arg1, arg_t* arg2, arg_t* res ){
//
//}
//
//static void ASSIGN_BOOL_INT					( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	res->argClass = ARGC_BOOL;
//	arg1->valBool = res->valBool = static_cast<bool>(arg2->valInt);
//}
//static void ASSIGN_BOOL_FLOAT					( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	res->argClass = ARGC_BOOL;
//	arg1->valBool = res->valBool = static_cast<bool>(arg2->valFloat);
//}
//static void ASSIGN_BOOL_BOOL					( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	res->argClass = ARGC_BOOL;
//	arg1->valBool = res->valBool = arg2->valBool;
//}
//static void ASSIGN_GLOBAL_VAR_POINTER			( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	MxASSIGN[ arg1->addrGlobal->argClass ]
//			[ arg2->addrInstruction->instr.res.argClass ]( arg1->addrGlobal, 
//														   &arg2->addrInstruction->instr.res, res );
//}
//static void ASSIGN_GLOBAL_VAR_arg				( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	MxASSIGN[ arg1->addrGlobal->argClass ][ arg2->argClass ]( arg1->addrGlobal, arg2, res );
//}
//static void ASSIGN_GLOBAL_VAR_GLOBAL_VAR		( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	MxASSIGN[ arg1->addrGlobal->argClass ]
//			[ arg2->addrGlobal->argClass ]( arg1->addrGlobal, arg2->addrGlobal, res );
//}
//static void ASSIGN_GLOBAL_VAR_LOCAL_VAR		( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	MxASSIGN[ arg1->addrGlobal->argClass ]
//			[ ::VMArr[ ::curVM ]->frameStack.Keep().localVars[ arg2->addrLocal ].argClass ]
//			( arg1->addrGlobal, &::VMArr[ ::curVM ]->frameStack.Keep().localVars[ arg2->addrLocal ], res );
//}
//static void ASSIGN_LOCAL_VAR_POINTER			( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	MxASSIGN[ ::VMArr[ ::curVM ]->frameStack.Keep().localVars[ arg1->addrLocal ].argClass ]
//			[ arg2->addrInstruction->instr.res.argClass ]
//			( &::VMArr[ ::curVM ]->frameStack.Keep().localVars[ arg1->addrLocal ],
//			  &arg2->addrInstruction->instr.res, res );
//}
//static void ASSIGN_LOCAL_VAR_arg				( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	MxASSIGN[ ::VMArr[ ::curVM ]->frameStack.Keep().localVars[ arg1->addrLocal ].argClass ]
//			[ arg2->argClass ]
//			( &::VMArr[ ::curVM ]->frameStack.Keep().localVars[ arg1->addrLocal ], arg2, res );
//}
//static void ASSIGN_LOCAL_VAR_GLOBAL_VAR		( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	MxASSIGN[ ::VMArr[ ::curVM ]->frameStack.Keep().localVars[ arg1->addrLocal ].argClass ]
//			[ arg2->addrGlobal->argClass ]
//			( &::VMArr[ ::curVM ]->frameStack.Keep().localVars[ arg1->addrLocal ], arg2->addrGlobal, res );
//}
//static void ASSIGN_LOCAL_VAR_LOCAL_VAR			( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	MxASSIGN[ ::VMArr[ ::curVM ]->frameStack.Keep().localVars[ arg1->addrLocal ].argClass ]
//			[ ::VMArr[ ::curVM ]->frameStack.Keep().localVars[ arg2->addrLocal ].argClass ]
//			( &::VMArr[ ::curVM ]->frameStack.Keep().localVars[ arg1->addrLocal ],
//			  &::VMArr[ ::curVM ]->frameStack.Keep().localVars[ arg2->addrLocal ], res );
//}
//static void ASSIGN_error						( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	// error
//}
//
//
////===========
////	==
////===========
//static void ASSIGNASSIGN						( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	MxASSIGNASSIGN[ arg1->argClass ][ arg2->argClass ]( arg1, arg2, res );
//}
//
//static void ASSIGNASSIGN_POINTER_POINTER		( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	MxPERCENT[ arg1->addrInstruction->instr.res.argClass ]
//	         [ arg2->addrInstruction->instr.res.argClass ]( &arg1->addrInstruction->instr.res,
//														    &arg2->addrInstruction->instr.res,
//														    res );
//}
//static void ASSIGNASSIGN_POINTER_GLOBAL_VAR	( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	MxASSIGNASSIGN[ arg1->addrInstruction->instr.res.argClass ]
//				  [ arg2->addrGlobal->argClass ]( &arg1->addrInstruction->instr.res,
//												  arg2->addrGlobal, res );
//}
//static void ASSIGNASSIGN_POINTER_LOCAL_VAR		( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	MxASSIGNASSIGN[ arg1->addrInstruction->instr.res.argClass ]
//				  [ ::VMArr[ ::curVM ]->frameStack.Keep().localVars[ arg2->addrLocal ].argClass ]
//				  ( &arg1->addrInstruction->instr.res,
//				    &::VMArr[ ::curVM ]->frameStack.Keep().localVars[ arg2->addrLocal ], res );
//}
//static void ASSIGNASSIGN_POINTER_arg ( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	MxASSIGNASSIGN[ arg1->addrInstruction->instr.res.argClass ]
//		          [ arg2->argClass ]( &arg1->addrInstruction->instr.res, arg2, res );
//}
//static void ASSIGNASSIGN_error					( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	// error
//}
//static void ASSIGNASSIGN_arg_POINTER			( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	MxASSIGNASSIGN[ arg1->argClass ]
//				  [ arg2->addrInstruction->instr.res.argClass ]( arg1, &arg2->addrInstruction->instr.res, res );
//}
//static void ASSIGNASSIGN_INT_INT				( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	res->argClass = ARGC_BOOL;
//	res->valBool  = arg1->valInt == arg2->valInt;
//}
//static void ASSIGNASSIGN_INT_FLOAT				( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	res->argClass = ARGC_BOOL;
//	res->valBool  = static_cast<float>(arg1->valInt) == arg2->valFloat;
//}
//static void ASSIGNASSIGN_INT_BOOL				( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	res->argClass = ARGC_BOOL;
//	res->valBool  = static_cast<bool>( arg1->valInt == static_cast<int>(arg2->valBool) );
//}
//static void ASSIGNASSIGN_arg_GLOBAL_VAR		( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	MxASSIGNASSIGN[ arg1->argClass ]
//				  [ arg2->addrGlobal->argClass ]( arg1, arg2->addrGlobal, res );
//}
//static void ASSIGNASSIGN_arg_LOCAL_VAR			( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	MxASSIGNASSIGN[ arg1->argClass ]
//				  [ ::VMArr[ ::curVM ]->frameStack.Keep().localVars[ arg2->addrLocal ].argClass ]
//				  ( arg1, &::VMArr[ ::curVM ]->frameStack.Keep().localVars[ arg2->addrLocal ], res );
//}
//static void ASSIGNASSIGN_FLOAT_INT				( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	res->argClass = ARGC_BOOL;
//	res->valBool  = arg1->valFloat == static_cast<float>(arg2->valInt);
//}
//static void ASSIGNASSIGN_FLOAT_FLOAT			( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	res->argClass = ARGC_BOOL;
//	res->valBool  = arg1->valFloat == arg2->valFloat;
//}
//static void ASSIGNASSIGN_FLOAT_BOOL			( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	res->argClass = ARGC_BOOL;
//	res->valBool  = static_cast<bool>( arg1->valFloat == static_cast<float>(arg2->valBool) );
//}
//static void ASSIGNASSIGN_STRING_STRING			( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	res->argClass = ARGC_BOOL;
//	res->valBool  = !strcmp( arg1->valStr, arg2->valStr );
//}
//static void ASSIGNASSIGN_BOOL_INT				( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	res->argClass = ARGC_BOOL;
//	res->valBool  = static_cast<bool>( static_cast<int>(arg1->valBool) == arg2->valInt );
//}
//static void ASSIGNASSIGN_BOOL_FLOAT			( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	res->argClass = ARGC_BOOL;
//	res->valBool  = static_cast<float>( arg1->valBool ) == arg2->valFloat;
//}
//static void ASSIGNASSIGN_BOOL_BOOL				( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	res->argClass = ARGC_BOOL;
//	res->valBool  = arg1->valBool == arg2->valBool;
//}
//static void ASSIGNASSIGN_GLOBAL_VAR_POINTER	( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	MxASSIGNASSIGN[ arg1->addrGlobal->argClass ]
//			      [ arg2->addrInstruction->instr.res.argClass ]( arg1->addrGlobal, 
//																 &arg2->addrInstruction->instr.res, res );
//}
//static void ASSIGNASSIGN_GLOBAL_VAR_arg		( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	MxASSIGNASSIGN[ arg1->addrGlobal->argClass ]
//			      [ arg2->argClass ]( arg1->addrGlobal, arg2, res );
//}
//static void ASSIGNASSIGN_GLOBAL_VAR_GLOBAL_VAR	( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	MxASSIGNASSIGN[ arg1->addrGlobal->argClass ]
//			      [ arg2->addrGlobal->argClass ]( arg1->addrGlobal, arg2->addrGlobal, res );
//}
//static void ASSIGNASSIGN_GLOBAL_VAR_LOCAL_VAR	( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	MxASSIGNASSIGN[ arg1->addrGlobal->argClass ]
//			      [ ::VMArr[ ::curVM ]->frameStack.Keep().localVars[ arg2->addrLocal ].argClass ]
//				  ( arg1->addrGlobal, &::VMArr[ ::curVM ]->frameStack.Keep().localVars[ arg2->addrLocal ], res );
//}
//static void ASSIGNASSIGN_LOCAL_VAR_POINTER		( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	MxASSIGNASSIGN[ ::VMArr[ ::curVM ]->frameStack.Keep().localVars[ arg1->addrLocal ].argClass ]
//			      [ arg2->addrInstruction->instr.res.argClass ]
//				  ( &::VMArr[ ::curVM ]->frameStack.Keep().localVars[ arg1->addrLocal ], 
//					&arg2->addrInstruction->instr.res, res );
//}
//static void ASSIGNASSIGN_LOCAL_VAR_arg			( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	MxASSIGNASSIGN[ ::VMArr[ ::curVM ]->frameStack.Keep().localVars[ arg1->addrLocal ].argClass ]
//			      [ arg2->argClass ]( &::VMArr[ ::curVM ]->frameStack.Keep().localVars[ arg1->addrLocal ], arg2, res );
//}
//static void ASSIGNASSIGN_LOCAL_VAR_GLOBAL_VAR	( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	MxASSIGNASSIGN[ ::VMArr[ ::curVM ]->frameStack.Keep().localVars[ arg1->addrLocal ].argClass ]
//			      [ arg2->addrGlobal->argClass ]
//				  ( &::VMArr[ ::curVM ]->frameStack.Keep().localVars[ arg1->addrLocal ], arg2->addrGlobal, res );
//}
//static void ASSIGNASSIGN_LOCAL_VAR_LOCAL_VAR	( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	MxASSIGNASSIGN[ ::VMArr[ ::curVM ]->frameStack.Keep().localVars[ arg1->addrLocal ].argClass ]
//			      [ ::VMArr[ ::curVM ]->frameStack.Keep().localVars[ arg2->addrLocal ].argClass ]
//				  ( &::VMArr[ ::curVM ]->frameStack.Keep().localVars[ arg1->addrLocal ],
//					&::VMArr[ ::curVM ]->frameStack.Keep().localVars[ arg1->addrLocal ], res );
//}
//
//
//
////===========
////	^
////===========
//static void XOR								( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	MxXOR[ arg1->argClass ][ arg2->argClass ]( arg1, arg2, res );
//}
//
//static void XOR_POINTER_POINTER				( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	MxXOR[ arg1->addrInstruction->instr.res.argClass ]
//		 [ arg2->addrInstruction->instr.res.argClass ]( &arg1->addrInstruction->instr.res,
//														&arg2->addrInstruction->instr.res, res );
//}
//static void XOR_POINTER_GLOBAL_VAR				( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	MxXOR[ arg1->addrInstruction->instr.res.argClass ]
//		 [ arg2->addrGlobal->argClass ]( &arg1->addrInstruction->instr.res, arg2->addrGlobal, res );
//}
//static void XOR_POINTER_LOCAL_VAR				( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	MxXOR[ arg1->addrInstruction->instr.res.argClass ]
//		 [ ::VMArr[ ::curVM ]->frameStack.Keep().localVars[ arg2->addrLocal ].argClass ]
//		 ( &arg1->addrInstruction->instr.res, &::VMArr[ ::curVM ]->frameStack.Keep().localVars[ arg2->addrLocal ], res );
//}
//static void XOR_POINTER_arg					( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	MxXOR[ arg1->addrInstruction->instr.res.argClass ]
//		 [ arg2->argClass ]( &arg1->addrInstruction->instr.res, arg2, res );
//}
//static void XOR_error							( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	// error
//}
//static void XOR_arg_POINTER					( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	MxXOR[ arg1->argClass ]
//	     [ arg2->addrInstruction->instr.res.argClass ]( arg1, &arg2->addrInstruction->instr.res, res );
//}
//static void XOR_INT_INT						( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	res->argClass = ARGC_INT;
//	res->valInt   = arg1->valInt ^ arg2->valInt;
//}
//static void XOR_INT_BOOL						( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	res->argClass = ARGC_INT;
//	res->valInt   = arg1->valInt ^ static_cast<int>(arg2->valBool);
//}
//static void XOR_arg_GLOBAL_VAR					( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	MxXOR[ arg1->argClass ][ arg2->addrGlobal->argClass ]( arg1, arg2->addrGlobal, res );
//}
//static void XOR_arg_LOCAL_VAR					( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	MxXOR[ arg1->argClass ]
//	     [ ::VMArr[ ::curVM ]->frameStack.Keep().localVars[ arg2->addrLocal ].argClass ]
//		 ( arg1, &::VMArr[ ::curVM ]->frameStack.Keep().localVars[ arg2->addrLocal ], res );
//}
//static void XOR_BOOL_INT						( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	res->argClass = ARGC_INT;
//	res->valInt   = static_cast<int>(arg1->valBool) ^ arg2->valInt;
//}
//static void XOR_BOOL_BOOL						( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	res->argClass = ARGC_BOOL;
//	res->valBool = arg1->valBool ^ arg2->valBool;
//}
//static void XOR_GLOBAL_VAR_POINTER				( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	MxXOR[ arg1->addrGlobal->argClass ]
//	     [ arg2->addrInstruction->instr.res.argClass ]( arg1->addrGlobal, 
//														&arg2->addrInstruction->instr.res, res );
//}
//static void XOR_GLOBAL_VAR_arg					( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	MxXOR[ arg1->addrGlobal->argClass ][ arg2->argClass ]( arg1->addrGlobal, arg2, res );
//}
//static void XOR_GLOBAL_VAR_GLOBAL_VAR			( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	MxXOR[ arg1->addrGlobal->argClass ]
//		 [ arg2->addrGlobal->argClass ]( arg1->addrGlobal, arg2->addrGlobal, res );
//}
//static void XOR_GLOBAL_VAR_LOCAL_VAR			( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	MxXOR[ arg1->addrGlobal->argClass ]
//		 [ ::VMArr[ ::curVM ]->frameStack.Keep().localVars[ arg2->addrLocal ].argClass ]
//		 ( arg1->addrGlobal, &::VMArr[ ::curVM ]->frameStack.Keep().localVars[ arg2->addrLocal ], res );
//}
//
//static void XOR_LOCAL_VAR_POINTER				( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	MxXOR[ ::VMArr[ ::curVM ]->frameStack.Keep().localVars[ arg1->addrLocal ].argClass ]
//		 [ arg2->addrInstruction->instr.res.argClass ]
//		 ( &::VMArr[ ::curVM ]->frameStack.Keep().localVars[ arg1->addrLocal ],
//		   &arg2->addrInstruction->instr.res, res );
//}
//static void XOR_LOCAL_VAR_arg					( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	MxXOR[ ::VMArr[ ::curVM ]->frameStack.Keep().localVars[ arg1->addrLocal ].argClass ]
//		 [ arg2->argClass ]( &::VMArr[ ::curVM ]->frameStack.Keep().localVars[ arg1->addrLocal ], arg2, res );
//}
//static void XOR_LOCAL_VAR_GLOBAL_VAR			( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	MxXOR[ ::VMArr[ ::curVM ]->frameStack.Keep().localVars[ arg1->addrLocal ].argClass ]
//		 [ arg2->addrGlobal->argClass ]( &::VMArr[ ::curVM ]->frameStack.Keep().localVars[ arg1->addrLocal ],
//										  arg2->addrGlobal, res );
//}
//static void XOR_LOCAL_VAR_LOCAL_VAR			( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	MxXOR[ ::VMArr[ ::curVM ]->frameStack.Keep().localVars[ arg1->addrLocal ].argClass ]
//		 [ ::VMArr[ ::curVM ]->frameStack.Keep().localVars[ arg2->addrLocal ].argClass ]
//		 ( &::VMArr[ ::curVM ]->frameStack.Keep().localVars[ arg1->addrLocal ],
//		   &::VMArr[ ::curVM ]->frameStack.Keep().localVars[ arg2->addrLocal ], res );
//}
//
////===========
////	^=
////===========
//static void XORASSIGN							( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	XOR( arg1, arg2, res );
//	ASSIGN( arg1, res, res );
//}
//
////===========
////	|
////===========
//static void OR									( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	MxOR[ arg1->argClass ][ arg2->argClass ]( arg1, arg2, res );
//}
//
//static void OR_POINTER_POINTER					( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	MxOR[ arg1->addrInstruction->instr.res.argClass ]
//	    [ arg2->addrInstruction->instr.res.argClass ]( &arg1->addrInstruction->instr.res,
//													   &arg2->addrInstruction->instr.res, res );
//}
//static void OR_POINTER_GLOBAL_VAR				( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	MxOR[ arg1->addrInstruction->instr.res.argClass ]
//		[ arg2->addrGlobal->argClass ]( &arg1->addrInstruction->instr.res, arg2->addrGlobal, res );
//}
//static void OR_POINTER_LOCAL_VAR				( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	MxOR[ arg1->addrInstruction->instr.res.argClass ]
//		[ ::VMArr[ ::curVM ]->frameStack.Keep().localVars[ arg2->addrLocal ].argClass ]
//		( &arg1->addrInstruction->instr.res, &::VMArr[ ::curVM ]->frameStack.Keep().localVars[ arg2->addrLocal ], res );
//}
//static void OR_POINTER_arg						( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	MxOR[ arg1->addrInstruction->instr.res.argClass ]
//	    [ arg2->argClass ]( &arg1->addrInstruction->instr.res, arg2, res );
//}
//static void OR_error							( arg_t* arg1, arg_t* arg2, arg_t* res ){
//}
//static void OR_INT_POINTER						( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	MxOR[ arg1->argClass ]
//	    [ arg2->addrInstruction->instr.res.argClass ]( arg1, &arg2->addrInstruction->instr.res, res );
//}
//static void OR_INT_INT							( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	res->argClass = ARGC_INT;
//	res->valInt   = arg1->valInt + arg2->valInt;
//}
//static void OR_INT_BOOL						( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	res->argClass = ARGC_INT;
//	res->valInt   = arg1->valInt ^ arg2->valInt;
//}
//static void OR_arg_GLOBAL_VAR					( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	MxOR[ arg1->argClass ][ arg2->addrGlobal->argClass ]( arg1, arg2->addrGlobal, res );
//}
//static void OR_arg_POINTER						( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	 MxOR[ arg1->argClass ][ arg2->addrInstruction->instr.res.argClass ]
//	 ( arg1, &arg2->addrInstruction->instr.res, res );
//}
//static void OR_arg_LOCAL_VAR					( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	MxOR[ arg1->argClass ][ ::VMArr[ ::curVM ]->frameStack.Keep().localVars[ arg2->addrLocal ].argClass ]
//		( arg1, &::VMArr[ ::curVM ]->frameStack.Keep().localVars[ arg2->addrLocal ], res );
//}
//static void OR_BOOL_INT						( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	res->argClass = ARGC_INT;
//	res->valInt   = static_cast<int>(arg1->valBool) | arg2->valInt;
//}
//static void OR_BOOL_BOOL						( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	res->argClass = ARGC_BOOL;
//	res->valBool  = arg1->valBool | arg2->valBool;
//}
//static void OR_GLOBAL_VAR_POINTER				( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	MxOR[ arg1->addrGlobal->argClass ]
//		[ arg2->addrInstruction->instr.res.argClass ]( arg1->addrGlobal, 
//													   &arg2->addrInstruction->instr.res, res );
//}
//static void OR_GLOBAL_VAR_arg					( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	MxOR[ arg1->addrGlobal->argClass ][ arg2->argClass ]( arg1->addrGlobal, arg2, res );
//}
//static void OR_GLOBAL_VAR_GLOBAL_VAR			( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	MxOR[ arg1->addrGlobal->argClass ]
//	    [ arg2->addrGlobal->argClass ]( arg1->addrGlobal, arg2->addrGlobal, res );
//}
//static void OR_GLOBAL_VAR_LOCAL_VAR			( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	MxOR[ arg1->addrGlobal->argClass ]
//	    [ ::VMArr[ ::curVM ]->frameStack.Keep().localVars[ arg2->addrLocal ].argClass ]
//		( arg1->addrGlobal, &::VMArr[ ::curVM ]->frameStack.Keep().localVars[ arg2->addrLocal ], res );
//}
//static void OR_LOCAL_VAR_POINTER				( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	MxOR[ ::VMArr[ ::curVM ]->frameStack.Keep().localVars[ arg1->addrLocal ].argClass ]
//	    [ arg2->addrInstruction->instr.res.argClass ]
//		( &::VMArr[ ::curVM ]->frameStack.Keep().localVars[ arg1->addrLocal ],
//		  &arg2->addrInstruction->instr.res, res );
//}
//static void OR_LOCAL_VAR_arg					( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	MxOR[ ::VMArr[ ::curVM ]->frameStack.Keep().localVars[ arg1->addrLocal ].argClass ]
//	    [ arg2->argClass ]( &::VMArr[ ::curVM ]->frameStack.Keep().localVars[ arg1->addrLocal ], arg2, res );
//}
//static void OR_LOCAL_VAR_GLOBAL_VAR			( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	MxOR[ ::VMArr[ ::curVM ]->frameStack.Keep().localVars[ arg1->addrLocal ].argClass ]
//	    [ arg2->addrGlobal->argClass ]( &::VMArr[ ::curVM ]->frameStack.Keep().localVars[ arg1->addrLocal ],
//										arg2->addrGlobal, res );
//}
//static void OR_LOCAL_VAR_LOCAL_VAR				( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	MxOR[ ::VMArr[ ::curVM ]->frameStack.Keep().localVars[ arg1->addrLocal ].argClass ]
//		[ ::VMArr[ ::curVM ]->frameStack.Keep().localVars[ arg2->addrLocal ].argClass ]
//		( &::VMArr[ ::curVM ]->frameStack.Keep().localVars[ arg1->addrLocal ],
//		  &::VMArr[ ::curVM ]->frameStack.Keep().localVars[ arg2->addrLocal ], res );
//}
//
////===========
////  |=
////===========
//static void ORASSIGN							( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	OR( arg1, arg2, res );
//	ASSIGN( arg1, res, res );
//}
//
////===========
////	||
////===========
//static void OROR								( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	MxOROR[ arg1->argClass ][ arg2->argClass ]( arg1, arg2, res );
//}
//
//static void OROR_POINTER_POINTER				( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	MxOROR[ arg1->addrInstruction->instr.res.argClass ]
//	      [ arg2->addrInstruction->instr.res.argClass ]( &arg1->addrInstruction->instr.res,
//														 &arg2->addrInstruction->instr.res, res );
//}
//static void OROR_POINTER_GLOBAL_VAR			( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	MxOROR[ arg1->addrInstruction->instr.res.argClass ]
//		  [ arg2->addrGlobal->argClass ]( &arg1->addrInstruction->instr.res, arg2->addrGlobal, res );
//}
//static void OROR_POINTER_LOCAL_VAR				( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	MxOROR[ arg1->addrInstruction->instr.res.argClass ]
//		  [ ::VMArr[ ::curVM ]->frameStack.Keep().localVars[ arg2->addrLocal ].argClass ]
//		  ( &arg1->addrInstruction->instr.res, &::VMArr[ ::curVM ]->frameStack.Keep().localVars[ arg2->addrLocal ], res );
//}
//static void OROR_POINTER_arg					( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	MxOROR[ arg1->addrInstruction->instr.res.argClass ]
//		  [ arg2->argClass ]
//		  ( &arg1->addrInstruction->instr.res, arg2, res );
//}
//
//static void OROR_error							( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	// error
//}
//static void OROR_INT_INT						( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	res->argClass = ARGC_BOOL;
//	res->valBool  = arg1->valInt || arg2->valInt;
//}
//static void OROR_INT_FLOAT						( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	res->argClass = ARGC_BOOL;
//	res->valBool  = arg1->valInt || arg2->valFloat;
//}
//static void OROR_INT_BOOL						( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	res->argClass = ARGC_BOOL;
//	res->valBool  = arg1->valInt || arg2->valBool;
//}
//static void OROR_arg_POINTER					( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	MxOROR[ arg1->argClass ]
//		  [ arg2->addrInstruction->instr.res.argClass ]
//		  ( arg1, &arg2->addrInstruction->instr.res, res );
//}
//static void OROR_arg_GLOBAL_VAR				( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	MxOROR[ arg1->argClass ][ arg2->addrGlobal->argClass ]( arg1, arg2->addrGlobal, res );
//}
//static void OROR_arg_LOCAL_VAR					( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	MxOROR[ arg1->argClass ]
//		  [ ::VMArr[ ::curVM ]->frameStack.Keep().localVars[ arg2->addrLocal ].argClass ]
//		  ( arg1, &::VMArr[ ::curVM ]->frameStack.Keep().localVars[ arg2->addrLocal ], res );
//}
//static void OROR_FLOAT_INT						( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	res->argClass = ARGC_BOOL;
//	res->valBool  = arg1->valFloat || arg2->valInt;
//}
//static void OROR_FLOAT_FLOAT					( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	res->argClass = ARGC_BOOL;
//	res->valBool  = arg1->valFloat || arg2->valFloat;
//}
//static void OROR_FLOAT_BOOL					( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	res->argClass = ARGC_BOOL;
//	res->valBool  = arg1->valFloat || arg2->valBool;
//}
//static void OROR_BOOL_INT						( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	res->argClass = ARGC_BOOL;
//	res->valBool  = arg1->valBool || arg2->valInt;
//}
//static void OROR_BOOL_FLOAT					( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	res->argClass = ARGC_BOOL;
//	res->valBool  = arg1->valBool || arg2->valFloat;
//}
//static void OROR_BOOL_BOOL						( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	res->argClass = ARGC_BOOL;
//	res->valBool  = arg1->valBool || arg2->valBool;
//}
//static void OROR_GLOBAL_VAR_POINTER				( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	MxOROR[ arg1->addrGlobal->argClass ]
//		  [ arg2->addrInstruction->instr.res.argClass ]( arg1->addrGlobal, &arg2->addrInstruction->instr.res, res );
//}
//static void OROR_GLOBAL_VAR_arg					( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	MxOROR[ arg1->addrGlobal->argClass ][ arg2->argClass ]( arg1->addrGlobal, arg2, res );
//}
//static void OROR_GLOBAL_VAR_GLOBAL_VAR			( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	MxOROR[ arg1->addrGlobal->argClass ]
//		  [ arg2->addrGlobal->argClass ]( arg1->addrGlobal, arg2->addrGlobal, res );
//}
//static void OROR_GLOBAL_VAR_LOCAL_VAR			( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	MxOROR[ arg1->addrGlobal->argClass ]
//		  [ ::VMArr[ ::curVM ]->frameStack.Keep().localVars[ arg2->addrLocal ].argClass ]
//		  ( arg1->addrGlobal, &::VMArr[ ::curVM ]->frameStack.Keep().localVars[ arg2->addrLocal ], res );
//}
//static void OROR_LOCAL_VAR_POINTER				( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	MxOROR[ ::VMArr[ ::curVM ]->frameStack.Keep().localVars[ arg1->addrLocal ].argClass ]
//		  [ arg2->addrInstruction->instr.res.argClass ]
//		  ( &::VMArr[ ::curVM ]->frameStack.Keep().localVars[ arg1->addrLocal ], &arg2->addrInstruction->instr.res, res );
//}
//static void OROR_LOCAL_VAR_arg					( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	MxOROR[ ::VMArr[ ::curVM ]->frameStack.Keep().localVars[ arg1->addrLocal ].argClass ]
//		  [ arg2->argClass ]( &::VMArr[ ::curVM ]->frameStack.Keep().localVars[ arg1->addrLocal ], arg2, res );
//}
//static void OROR_LOCAL_VAR_GLOBAL_VAR			( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	MxOROR[ ::VMArr[ ::curVM ]->frameStack.Keep().localVars[ arg1->addrLocal ].argClass ]
//		  [ arg2->addrGlobal->argClass ]
//		  ( &::VMArr[ ::curVM ]->frameStack.Keep().localVars[ arg1->addrLocal ], arg2->addrGlobal, res );
//}
//static void OROR_LOCAL_VAR_LOCAL_VAR			( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	MxOROR[ ::VMArr[ ::curVM ]->frameStack.Keep().localVars[ arg1->addrLocal ].argClass ]
//		  [ ::VMArr[ ::curVM ]->frameStack.Keep().localVars[ arg2->addrLocal ].argClass ]
//		  ( &::VMArr[ ::curVM ]->frameStack.Keep().localVars[ arg1->addrLocal ],
//			&::VMArr[ ::curVM ]->frameStack.Keep().localVars[ arg2->addrLocal ], res );
//}
//
//
////===========
////	&
////===========
//static void AND								( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	MxAND[ arg1->argClass ][ arg2->argClass ]( arg1, arg2, res );
//}
//static void AND_POINTER_POINTER				( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	MxAND[ arg1->addrInstruction->instr.res.argClass ]
//		 [ arg2->addrInstruction->instr.res.argClass ]( &arg1->addrInstruction->instr.res,
//													    &arg2->addrInstruction->instr.res, res );
//}
//static void AND_POINTER_GLOBAL_VAR				( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	MxAND[ arg1->addrInstruction->instr.res.argClass ]
//		 [ arg2->addrGlobal->argClass ]( &arg1->addrInstruction->instr.res, arg2->addrGlobal, res );
//}
//static void AND_POINTER_LOCAL_VAR				( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	MxAND[ arg1->addrInstruction->instr.res.argClass ]
//		 [ ::VMArr[ ::curVM ]->frameStack.Keep().localVars[ arg2->addrLocal ].argClass ]
//		 ( &::VMArr[ ::curVM ]->frameStack.Keep().localVars[ arg2->addrLocal ], arg2->addrGlobal, res );
//}
//static void AND_POINTER_arg					( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	MxAND[ arg1->addrInstruction->instr.res.argClass ]
//		 [ arg2->argClass ]
//		 ( &arg1->addrInstruction->instr.res, arg2, res );
//}
//static void AND_error							( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	// error
//}
//static void AND_arg_POINTER					( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	MxAND[ arg1->argClass ]
//		 [ arg2->addrInstruction->instr.res.argClass ]( arg1, &arg2->addrInstruction->instr.res, res );
//}
//static void AND_INT_INT						( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	res->argClass = ARGC_INT;
//	res->valInt   = arg1->valInt & arg2->valInt;
//}
//static void AND_INT_BOOL						( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	res->argClass = ARGC_INT;
//	res->valInt   = arg1->valInt & static_cast<int>(arg2->valBool);
//}
//static void AND_arg_GLOBAL_VAR					( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	MxAND[ arg1->argClass ][ arg2->addrGlobal->argClass ](  arg1, arg2->addrGlobal, res );
//}
//static void AND_arg_LOCAL_VAR					( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	MxAND[ arg1->argClass ]
//		 [ ::VMArr[ ::curVM ]->frameStack.Keep().localVars[ arg2->addrLocal ].argClass ]
//		 (  arg1, &::VMArr[ ::curVM ]->frameStack.Keep().localVars[ arg2->addrLocal ], res );
//}
//static void AND_BOOL_INT						( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	res->argClass = ARGC_INT;
//	res->valInt   = static_cast<int>(arg1->valBool) & arg2->valInt;
//}
//static void AND_BOOL_BOOL						( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	res->argClass = ARGC_BOOL;
//	res->valBool  = arg1->valBool & arg2->valBool;
//}
//static void AND_GLOBAL_VAR_POINTER				( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	MxAND[ arg1->addrGlobal->argClass ]
//		 [ arg2->addrInstruction->instr.res.argClass ]( arg1->addrGlobal, 
//														&arg2->addrInstruction->instr.res, res );		 
//}
//static void AND_GLOBAL_VAR_arg					( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	MxAND[ arg1->addrGlobal->argClass ][ arg2->argClass ]( arg1->addrGlobal, arg2, res );		 
//}
//static void AND_GLOBAL_VAR_GLOBAL_VAR			( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	MxAND[ arg1->addrGlobal->argClass ]
//		 [ arg2->addrGlobal->argClass ]( arg1->addrGlobal, arg2->addrGlobal, res );		 
//}
//static void AND_GLOBAL_VAR_LOCAL_VAR			( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	MxAND[ arg1->addrGlobal->argClass ]
//		 [ ::VMArr[ ::curVM ]->frameStack.Keep().localVars[ arg2->addrLocal ].argClass ]
//		 ( arg1->addrGlobal, &::VMArr[ ::curVM ]->frameStack.Keep().localVars[ arg2->addrLocal ], res );		 
//}
//static void AND_LOCAL_VAR_POINTER				( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	MxAND[ ::VMArr[ ::curVM ]->frameStack.Keep().localVars[ arg1->addrLocal ].argClass ]
//		 [ arg2->addrInstruction->instr.res.argClass ]
//		 ( &::VMArr[ ::curVM ]->frameStack.Keep().localVars[ arg1->addrLocal ], &arg2->addrInstruction->instr.res, res );		 
//}
//static void AND_LOCAL_VAR_arg					( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	MxAND[ ::VMArr[ ::curVM ]->frameStack.Keep().localVars[ arg1->addrLocal ].argClass ]
//		 [ arg2->argClass ]
//		 ( &::VMArr[ ::curVM ]->frameStack.Keep().localVars[ arg1->addrLocal ], arg2, res );		 
//}
//static void AND_LOCAL_VAR_GLOBAL_VAR			( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	MxAND[ ::VMArr[ ::curVM ]->frameStack.Keep().localVars[ arg1->addrLocal ].argClass ]
//		 [ arg2->addrGlobal->argClass ]
//		 ( &::VMArr[ ::curVM ]->frameStack.Keep().localVars[ arg1->addrLocal ], arg2->addrGlobal, res );		 
//}
//static void AND_LOCAL_VAR_LOCAL_VAR			( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	MxAND[ ::VMArr[ ::curVM ]->frameStack.Keep().localVars[ arg1->addrLocal ].argClass ]
//		 [ ::VMArr[ ::curVM ]->frameStack.Keep().localVars[ arg2->addrLocal ].argClass ]
//		 ( &::VMArr[ ::curVM ]->frameStack.Keep().localVars[ arg1->addrLocal ], 
//		   &::VMArr[ ::curVM ]->frameStack.Keep().localVars[ arg2->addrLocal ], res );		 
//}
//
////===========
////  &=
////===========
//static void ANDASSIGN							( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	AND( arg1, arg2, res );
//	ASSIGN( arg1, res, res );
//}
//
//
////===========
////	&&
////===========
//static void ANDAND								( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	MxANDAND[ arg1->argClass ][ arg2->argClass ]( arg1, arg2, res );
//}
//
//static void ANDAND_POINTER_POINTER				( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	MxANDAND[ arg1->addrInstruction->instr.res.argClass ]
//		    [ arg2->addrInstruction->instr.res.argClass ]( &arg1->addrInstruction->instr.res,
//														   &arg2->addrInstruction->instr.res, res );
//}
//static void ANDAND_POINTER_GLOBAL_VAR			( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	MxANDAND[ arg1->addrInstruction->instr.res.argClass ]
//			[ arg2->addrGlobal->argClass ]( &arg1->addrInstruction->instr.res, arg2->addrGlobal, res );
//}
//static void ANDAND_POINTER_LOCAL_VAR			( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	MxANDAND[ arg1->addrInstruction->instr.res.argClass ]
//			[ ::VMArr[ ::curVM ]->frameStack.Keep().localVars[ arg2->addrLocal ].argClass ]
//			( &arg1->addrInstruction->instr.res, &::VMArr[ ::curVM ]->frameStack.Keep().localVars[ arg2->addrLocal ], res );
//}
//static void ANDAND_POINTER_arg					( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	MxANDAND[ arg1->addrInstruction->instr.res.argClass ]
//			[ arg2->argClass ]
//			( &arg1->addrInstruction->instr.res, arg2, res );
//}
//static void ANDAND_error						( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	// error
//}
//static void ANDAND_arg_POINTER					( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	MxANDAND[ arg1->argClass ]
//			[ arg2->addrInstruction->instr.res.argClass ]( arg1, &arg2->addrInstruction->instr.res, res );
//}
//static void ANDAND_INT_INT						( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	res->argClass = ARGC_BOOL;
//	res->valBool  = arg1->valInt && arg2->valInt;
//}
//static void ANDAND_INT_FLOAT					( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	res->argClass = ARGC_BOOL;
//	res->valBool  = arg1->valInt && arg2->valFloat;
//}
//static void ANDAND_INT_BOOL					( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	res->argClass = ARGC_BOOL;
//	res->valBool  = arg1->valInt && arg2->valBool;
//}
//static void ANDAND_arg_GLOBAL_VAR				( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	MxANDAND[ arg1->argClass ][ arg2->addrGlobal->argClass ]( arg1, arg2->addrGlobal, res );
//}
//static void ANDAND_arg_LOCAL_VAR				( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	MxANDAND[ arg1->argClass ]
//			[ ::VMArr[ ::curVM ]->frameStack.Keep().localVars[ arg2->addrLocal ].argClass ]
//			( arg1, &::VMArr[ ::curVM ]->frameStack.Keep().localVars[ arg2->addrLocal ], res );
//}
//static void ANDAND_FLOAT_INT					( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	res->argClass = ARGC_BOOL;
//	res->valBool  = arg1->valFloat && arg2->valInt;
//}
//static void ANDAND_FLOAT_FLOAT					( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	res->argClass = ARGC_BOOL;
//	res->valBool  = arg1->valFloat && arg2->valFloat;
//}
//static void ANDAND_FLOAT_BOOL					( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	res->argClass = ARGC_BOOL;
//	res->valBool  = arg1->valFloat && arg2->valBool;
//}
//static void ANDAND_BOOL_INT					( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	res->argClass = ARGC_BOOL;
//	res->valBool  = arg1->valBool && arg2->valInt;
//}
//static void ANDAND_BOOL_BOOL					( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	res->argClass = ARGC_BOOL;
//	res->valBool  = arg1->valBool && arg2->valBool;
//}
//static void ANDAND_BOOL_FLOAT					( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	res->argClass = ARGC_BOOL;
//	res->valBool  = arg1->valBool && arg2->valFloat;
//}
//static void ANDAND_GLOBAL_VAR_POINTER			( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	MxANDAND[ arg1->addrGlobal->argClass ]
//			[ arg2->addrInstruction->instr.res.argClass ]( arg1->addrGlobal, &arg2->addrInstruction->instr.res, res );
//}
//static void ANDAND_GLOBAL_VAR_arg				( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	MxANDAND[ arg1->addrGlobal->argClass ][ arg2->argClass ]( arg1->addrGlobal, arg2, res );
//}
//static void ANDAND_GLOBAL_VAR_GLOBAL_VAR		( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	MxANDAND[ arg1->addrGlobal->argClass ]
//			[ arg2->addrGlobal->argClass ]( arg1->addrGlobal, arg2->addrGlobal, res );
//}
//static void ANDAND_GLOBAL_VAR_LOCAL_VAR		( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	MxANDAND[ arg1->addrGlobal->argClass ]
//			[ ::VMArr[ ::curVM ]->frameStack.Keep().localVars[ arg2->addrLocal ].argClass ]
//			( arg1->addrGlobal, &::VMArr[ ::curVM ]->frameStack.Keep().localVars[ arg2->addrLocal ], res );
//}
//static void ANDAND_LOCAL_VAR_POINTER			( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	MxANDAND[ ::VMArr[ ::curVM ]->frameStack.Keep().localVars[ arg1->addrLocal ].argClass ]
//			[ arg2->addrInstruction->instr.res.argClass ]
//			( &::VMArr[ ::curVM ]->frameStack.Keep().localVars[ arg1->addrLocal ], &arg2->addrInstruction->instr.res, res );
//}
//static void ANDAND_LOCAL_VAR_arg				( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	MxANDAND[ ::VMArr[ ::curVM ]->frameStack.Keep().localVars[ arg1->addrLocal ].argClass ]
//			[ arg2->argClass ]( &::VMArr[ ::curVM ]->frameStack.Keep().localVars[ arg1->addrLocal ], arg2, res );
//}
//static void ANDAND_LOCAL_VAR_GLOBAL_VAR		( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	MxANDAND[ ::VMArr[ ::curVM ]->frameStack.Keep().localVars[ arg1->addrLocal ].argClass ]
//			[ arg2->addrGlobal->argClass ]
//			( &::VMArr[ ::curVM ]->frameStack.Keep().localVars[ arg1->addrLocal ], arg2->addrGlobal, res );
//}
//static void ANDAND_LOCAL_VAR_LOCAL_VAR			( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	MxANDAND[ ::VMArr[ ::curVM ]->frameStack.Keep().localVars[ arg1->addrLocal ].argClass ]
//			[ ::VMArr[ ::curVM ]->frameStack.Keep().localVars[ arg2->addrLocal ].argClass ]
//			( &::VMArr[ ::curVM ]->frameStack.Keep().localVars[ arg1->addrLocal ],
//			  &::VMArr[ ::curVM ]->frameStack.Keep().localVars[ arg2->addrLocal ], res );
//}
//
//
////===========
////	>
////===========
//static void MORE								( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	MxMORE[ arg1->argClass ][ arg2->argClass ]( arg1, arg2, res );
//}
//
//static void MORE_POINTER_POINTER				( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	MxMORE[ arg1->addrInstruction->instr.res.argClass ]
//		  [ arg2->addrInstruction->instr.res.argClass ]( &arg1->addrInstruction->instr.res,
//														 &arg2->addrInstruction->instr.res, res );
//}
//static void MORE_POINTER_GLOBAL_VAR			( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	MxMORE[ arg1->addrInstruction->instr.res.argClass ]
//		  [ arg2->addrGlobal->argClass ]( &arg1->addrInstruction->instr.res, arg2->addrGlobal, res );
//}
//static void MORE_POINTER_LOCAL_VAR				( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	MxMORE[ arg1->addrInstruction->instr.res.argClass ]
//		  [ arg2->addrGlobal->argClass ]( &arg1->addrInstruction->instr.res, arg2->addrGlobal, res );
//}
//static void MORE_POINTER_arg					( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	MxMORE[ arg1->addrInstruction->instr.res.argClass ] 
//	      [ arg2->argClass ]
//		  ( &arg1->addrInstruction->instr.res, arg2, res );
//}
//static void MORE_error							( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	// error
//}
//static void MORE_arg_POINTER					( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	MxMORE[ arg1->argClass ]
//		  [ arg2->addrInstruction->instr.res.argClass ]( arg1, &arg2->addrInstruction->instr.res, res );
//}
//static void MORE_INT_INT						( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	res->argClass = ARGC_BOOL;
//	res->valBool  = arg1->valInt > arg2->valInt;
//}
//static void MORE_INT_FLOAT						( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	res->argClass = ARGC_BOOL;
//	res->valBool  = arg1->valInt > arg2->valFloat;
//}
//static void MORE_INT_BOOL						( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	res->argClass = ARGC_BOOL;
//	res->valBool  = static_cast<bool>( arg1->valInt > static_cast<int>(arg2->valBool) );
//}
//static void MORE_arg_GLOBAL_VAR				( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	MxMORE[ arg1->argClass ][ arg2->addrGlobal->argClass ]( arg1, arg2->addrGlobal, res );
//}
//static void MORE_arg_LOCAL_VAR					( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	MxMORE[ arg1->argClass ]
//		  [ ::VMArr[ ::curVM ]->frameStack.Keep().localVars[ arg2->addrLocal ].argClass ]
//		  ( arg1, &::VMArr[ ::curVM ]->frameStack.Keep().localVars[ arg2->addrLocal ], res );
//}
//static void MORE_FLOAT_INT						( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	res->argClass = ARGC_BOOL;
//	res->valBool  = arg1->valFloat > arg2->valInt;
//}
//static void MORE_FLOAT_FLOAT					( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	res->argClass = ARGC_BOOL;
//	res->valBool  = arg1->valFloat > arg2->valFloat;
//}
//static void MORE_FLOAT_BOOL					( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	res->argClass = ARGC_BOOL;
//	res->valBool  = static_cast<bool>( arg1->valInt > static_cast<int>(arg2->valBool) );
//}
//static void MORE_BOOL_INT						( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	res->argClass = ARGC_BOOL;
//	res->valBool  = static_cast<bool>( static_cast<int>(arg1->valBool) > arg2->valInt );
//}
//static void MORE_BOOL_FLOAT					( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	res->argClass = ARGC_BOOL;
//	res->valBool  = static_cast<bool>( static_cast<float>(arg1->valBool) > arg2->valFloat );
//}
//static void MORE_BOOL_BOOL						( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	res->argClass = ARGC_BOOL;
//	res->valBool  = arg1->valBool > arg2->valBool;
//}
//static void MORE_GLOBAL_VAR_POINTER			( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	MxMORE[ arg1->addrGlobal->argClass ]
//		  [ arg2->addrInstruction->instr.res.argClass ]
//		  ( arg1->addrGlobal, &arg2->addrInstruction->instr.res, res );
//}
//static void MORE_GLOBAL_VAR_arg				( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	MxMORE[ arg1->addrGlobal->argClass ][ arg2->argClass ]( arg1->addrGlobal, arg2, res );
//}
//static void MORE_GLOBAL_VAR_GLOBAL_VAR			( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	MxMORE[ arg1->addrGlobal->argClass ][ arg2->addrGlobal->argClass ]( arg1->addrGlobal, arg2->addrGlobal, res );
//}
//static void MORE_GLOBAL_VAR_LOCAL_VAR			( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	MxMORE[ arg1->addrGlobal->argClass ]
//		  [ ::VMArr[ ::curVM ]->frameStack.Keep().localVars[ arg2->addrLocal ].argClass ]
//		  ( arg1->addrGlobal, &::VMArr[ ::curVM ]->frameStack.Keep().localVars[ arg2->addrLocal ], res );
//}
//static void MORE_LOCAL_VAR_POINTER				( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	MxMORE[ ::VMArr[ ::curVM ]->frameStack.Keep().localVars[ arg1->addrLocal ].argClass ]
//		  [ arg2->addrInstruction->instr.res.argClass ]
//		  ( &::VMArr[ ::curVM ]->frameStack.Keep().localVars[ arg1->addrLocal ], &arg2->addrInstruction->instr.res, res );
//}
//static void MORE_LOCAL_VAR_arg					( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	MxMORE[ ::VMArr[ ::curVM ]->frameStack.Keep().localVars[ arg1->addrLocal ].argClass ]
//		  [ arg2->argClass ]( &::VMArr[ ::curVM ]->frameStack.Keep().localVars[ arg1->addrLocal ], arg2, res );
//}
//static void MORE_LOCAL_VAR_GLOBAL_VAR			( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	MxMORE[ ::VMArr[ ::curVM ]->frameStack.Keep().localVars[ arg1->addrLocal ].argClass ]
//		  [ arg2->addrGlobal->argClass ]
//		  ( &::VMArr[ ::curVM ]->frameStack.Keep().localVars[ arg1->addrLocal ], arg2->addrGlobal, res );
//}
//static void MORE_LOCAL_VAR_LOCAL_VAR			( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	MxMORE[ ::VMArr[ ::curVM ]->frameStack.Keep().localVars[ arg1->addrLocal ].argClass ]
//		  [ ::VMArr[ ::curVM ]->frameStack.Keep().localVars[ arg2->addrLocal ].argClass ]
//		  ( &::VMArr[ ::curVM ]->frameStack.Keep().localVars[ arg1->addrLocal ],
//			&::VMArr[ ::curVM ]->frameStack.Keep().localVars[ arg2->addrLocal ], res );
//}
//
//
////===========
////	>=
////===========
//static void MOREASSIGN							( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	MxMOREASSIGN[ arg1->argClass ][ arg2->argClass ]( arg1, arg2, res );
//}
//
//static void MOREASSIGN_POINTER_POINTER			( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	MxMOREASSIGN[ arg1->addrInstruction->instr.res.argClass ]
//				[ arg2->addrInstruction->instr.res.argClass ]( &arg1->addrInstruction->instr.res,
//															   &arg2->addrInstruction->instr.res,
//															   res );
//}
//static void MOREASSIGN_POINTER_GLOBAL_VAR		( arg_t* arg1, arg_t* arg2, arg_t* res ){
//}
//static void MOREASSIGN_POINTER_LOCAL_VAR		( arg_t* arg1, arg_t* arg2, arg_t* res ){
//}
//static void MOREASSIGN_POINTER_arg				( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	MxMOREASSIGN[ arg1->addrInstruction->instr.res.argClass ]
//				[ arg2->argClass ]( &arg1->addrInstruction->instr.res, arg2, res );
//}
//static void MOREASSIGN_error					( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	// error
//}
//static void MOREASSIGN_arg_POINTER				( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	MxMOREASSIGN[ arg1->argClass ]
//				[ arg2->addrInstruction->instr.res.argClass ]( arg1, &arg2->addrInstruction->instr.res, res );
//}
//static void MOREASSIGN_INT_INT					( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	res->argClass = ARGC_BOOL;
//	res->valBool  = arg1->valInt >= arg2->valInt;
//}
//static void MOREASSIGN_INT_FLOAT				( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	res->argClass = ARGC_BOOL;
//	res->valBool  = arg1->valInt >= arg2->valFloat;
//}
//static void MOREASSIGN_INT_BOOL				( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	res->argClass = ARGC_BOOL;
//	res->valBool  = static_cast<bool>( arg1->valInt >= static_cast<int>(arg2->valBool) );
//}
//static void MOREASSIGN_arg_GLOBAL_VAR			( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	MxMOREASSIGN[ arg1->argClass ][ arg2->addrGlobal->argClass ]( arg1, arg2->addrGlobal, res );
//}
//static void MOREASSIGN_arg_LOCAL_VAR			( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	MxMOREASSIGN[ arg1->argClass ]
//				[ ::VMArr[ ::curVM ]->frameStack.Keep().localVars[ arg2->addrLocal ].argClass ]
//				( arg1, &::VMArr[ ::curVM ]->frameStack.Keep().localVars[ arg2->addrLocal ], res );
//}
//static void MOREASSIGN_FLOAT_INT				( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	res->argClass = ARGC_BOOL;
//	res->valBool  = arg1->valFloat >= arg2->valInt;
//}
//static void MOREASSIGN_FLOAT_FLOAT				( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	res->argClass = ARGC_BOOL;
//	res->valBool  = arg1->valFloat >= arg2->valFloat;
//}
//static void MOREASSIGN_FLOAT_BOOL				( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	res->argClass = ARGC_BOOL;
//	res->valBool  = arg1->valFloat >= static_cast<float>(arg2->valBool);
//}
//static void MOREASSIGN_BOOL_INT				( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	res->argClass = ARGC_BOOL;
//	res->valBool  = static_cast<int>(arg1->valBool) >= arg2->valInt;
//}
//static void MOREASSIGN_BOOL_FLOAT				( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	res->argClass = ARGC_BOOL;
//	res->valBool  = static_cast<float>(arg1->valBool) >= arg2->valFloat;
//}
//static void MOREASSIGN_BOOL_BOOL				( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	res->argClass = ARGC_BOOL;
//	res->valBool  = arg1->valBool >= arg2->valBool;
//}
//static void MOREASSIGN_GLOBAL_VAR_POINTER		( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	MxMOREASSIGN[ arg1->addrGlobal->argClass ]
//				[ arg2->addrInstruction->instr.res.argClass ]
//				( arg1->addrGlobal, &arg2->addrInstruction->instr.res, res );
//}
//static void MOREASSIGN_GLOBAL_VAR_arg			( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	MxMOREASSIGN[ arg1->addrGlobal->argClass ]
//				[ arg2->argClass ]( arg1->addrGlobal, &arg2->addrInstruction->instr.res, res );
//}
//static void MOREASSIGN_GLOBAL_VAR_GLOBAL_VAR	( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	MxMOREASSIGN[ arg1->addrGlobal->argClass ]
//				[ arg2->addrGlobal->argClass ]( arg1->addrGlobal, arg2->addrGlobal, res );
//}
//static void MOREASSIGN_GLOBAL_VAR_LOCAL_VAR	( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	MxMOREASSIGN[ arg1->addrGlobal->argClass ]
//				[ ::VMArr[ ::curVM ]->frameStack.Keep().localVars[ arg2->addrLocal ].argClass ]
//				( arg1->addrGlobal, &::VMArr[ ::curVM ]->frameStack.Keep().localVars[ arg2->addrLocal ], res );
//}
//static void MOREASSIGN_LOCAL_VAR_POINTER		( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	MxMOREASSIGN[ ::VMArr[ ::curVM ]->frameStack.Keep().localVars[ arg1->addrLocal ].argClass ]
//				[ arg2->addrInstruction->instr.res.argClass ]
//				( &::VMArr[ ::curVM ]->frameStack.Keep().localVars[ arg1->addrLocal ],
//				  &arg2->addrInstruction->instr.res, res );
//}
//static void MOREASSIGN_LOCAL_VAR_arg			( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	MxMOREASSIGN[ ::VMArr[ ::curVM ]->frameStack.Keep().localVars[ arg1->addrLocal ].argClass ]
//				[ arg2->argClass ]( &::VMArr[ ::curVM ]->frameStack.Keep().localVars[ arg1->addrLocal ], arg2, res );
//}
//static void MOREASSIGN_LOCAL_VAR_GLOBAL_VAR	( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	MxMOREASSIGN[ ::VMArr[ ::curVM ]->frameStack.Keep().localVars[ arg1->addrLocal ].argClass ]
//				[ arg2->addrGlobal->argClass ]
//				( &::VMArr[ ::curVM ]->frameStack.Keep().localVars[ arg1->addrLocal ], arg2->addrGlobal, res );
//}
//static void MOREASSIGN_LOCAL_VAR_LOCAL_VAR		( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	MxMOREASSIGN[ ::VMArr[ ::curVM ]->frameStack.Keep().localVars[ arg1->addrLocal ].argClass ]
//				[ ::VMArr[ ::curVM ]->frameStack.Keep().localVars[ arg2->addrLocal ].argClass ]
//				( &::VMArr[ ::curVM ]->frameStack.Keep().localVars[ arg1->addrLocal ],
//				  &::VMArr[ ::curVM ]->frameStack.Keep().localVars[ arg2->addrLocal ], res );
//}
//
//
////===========
////	<
////===========
//static void LESS								( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	MxLESS[ arg1->argClass ][ arg2->argClass ]( arg1, arg2, res );
//}
//
//static void LESS_POINTER_POINTER				( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	MxLESS[ arg1->addrInstruction->instr.res.argClass ]
//		  [ arg2->addrInstruction->instr.res.argClass ]( &arg1->addrInstruction->instr.res,
//														 &arg2->addrInstruction->instr.res,
//														 res );
//}
//static void LESS_POINTER_GLOBAL_VAR			( arg_t* arg1, arg_t* arg2, arg_t* res ){
//}
//static void LESS_POINTER_LOCAL_VAR				( arg_t* arg1, arg_t* arg2, arg_t* res ){
//}
//static void LESS_POINTER_arg					( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	MxLESS[ arg1->addrInstruction->instr.res.argClass ]
//		  [ arg2->argClass ]( &arg1->addrInstruction->instr.res, arg2, res );
//}
//static void LESS_arg_POINTER					( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	MxLESS[ arg1->argClass ]
//		  [ arg2->addrInstruction->instr.res.argClass ]( arg1, &arg2->addrInstruction->instr.res, res );
//}
//static void LESS_error							( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	// error
//}
//static void LESS_INT_INT						( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	res->argClass = ARGC_BOOL;
//	res->valBool  = arg1->valInt < arg2->valInt;
//}
//static void LESS_INT_FLOAT						( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	res->argClass = ARGC_BOOL;
//	res->valBool  = arg1->valInt < arg2->valFloat;
//}
//static void LESS_INT_BOOL						( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	res->argClass = ARGC_BOOL;
//	res->valBool  = static_cast<bool>( arg1->valInt < static_cast<int>(arg2->valBool) );
//}
//static void LESS_arg_GLOBAL_VAR				( arg_t* arg1, arg_t* arg2, arg_t* res ){
//}
//static void LESS_arg_LOCAL_VAR					( arg_t* arg1, arg_t* arg2, arg_t* res ){
//}
//static void LESS_FLOAT_INT						( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	res->argClass = ARGC_BOOL;
//	res->valBool  = static_cast<bool>( arg1->valFloat < static_cast<float>(arg2->valBool) );
//}
//static void LESS_FLOAT_FLOAT					( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	res->argClass = ARGC_BOOL;
//	res->valBool  = arg1->valFloat < arg2->valFloat;
//}
//static void LESS_FLOAT_BOOL					( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	res->argClass = ARGC_BOOL;
//	res->valBool  = arg1->valFloat < static_cast<float>(arg2->valBool);
//}
//static void LESS_BOOL_INT						( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	res->argClass = ARGC_BOOL;
//	res->valBool  = static_cast<int>(arg1->valBool) < arg2->valInt;
//}
//static void LESS_BOOL_FLOAT					( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	res->argClass = ARGC_BOOL;
//	res->valBool  = static_cast<float>(arg1->valBool) < arg2->valFloat;
//}
//static void LESS_BOOL_BOOL						( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	res->argClass = ARGC_BOOL;
//	res->valBool  = arg1->valBool < arg2->valBool;
//}
//static void LESS_GLOBAL_VAR_POINTER			( arg_t* arg1, arg_t* arg2, arg_t* res ){
//}
//static void LESS_GLOBAL_VAR_arg				( arg_t* arg1, arg_t* arg2, arg_t* res ){
//}
//static void LESS_GLOBAL_VAR_GLOBAL_VAR			( arg_t* arg1, arg_t* arg2, arg_t* res ){
//}
//static void LESS_GLOBAL_VAR_LOCAL_VAR			( arg_t* arg1, arg_t* arg2, arg_t* res ){
//}
//static void LESS_LOCAL_VAR_POINTER				( arg_t* arg1, arg_t* arg2, arg_t* res ){
//}
//static void LESS_LOCAL_VAR_arg					( arg_t* arg1, arg_t* arg2, arg_t* res ){
//}
//static void LESS_LOCAL_VAR_GLOBAL_VAR			( arg_t* arg1, arg_t* arg2, arg_t* res ){
//}
//static void LESS_LOCAL_VAR_LOCAL_VAR			( arg_t* arg1, arg_t* arg2, arg_t* res ){
//}
//
//
////===========
////	<=
////===========
//static void LESSASSIGN							( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	MxLESSASSIGN[ arg1->argClass ][ arg2->argClass ]( arg1, arg2, res );
//}
//static void LESSASSIGN_POINTER_POINTER			( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	MxLESSASSIGN[ arg1->addrInstruction->instr.res.argClass ]
//			    [ arg2->addrInstruction->instr.res.argClass ]( &arg1->addrInstruction->instr.res,
//															   &arg2->addrInstruction->instr.res, res );
//}
//static void LESSASSIGN_POINTER_GLOBAL_VAR		( arg_t* arg1, arg_t* arg2, arg_t* res ){
//}
//static void LESSASSIGN_POINTER_LOCAL_VAR		( arg_t* arg1, arg_t* arg2, arg_t* res ){
//}
//static void LESSASSIGN_POINTER_arg				( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	MxLESSASSIGN[ arg1->addrInstruction->instr.res.argClass ]
//				[ arg2->argClass ]( &arg1->addrInstruction->instr.res, arg2, res );
//}
//
//static void LESSASSIGN_error					( arg_t* arg1, arg_t* arg2, arg_t* res ){
//}
//static void LESSASSIGN_INT_INT					( arg_t* arg1, arg_t* arg2, arg_t* res ){
//}
//static void LESSASSIGN_INT_FLOAT				( arg_t* arg1, arg_t* arg2, arg_t* res ){
//}
//static void LESSASSIGN_INT_BOOL				( arg_t* arg1, arg_t* arg2, arg_t* res ){
//}
//static void LESSASSIGN_arg_GLOBAL_VAR			( arg_t* arg1, arg_t* arg2, arg_t* res ){
//}
//static void LESSASSIGN_arg_LOCAL_VAR			( arg_t* arg1, arg_t* arg2, arg_t* res ){
//}
//static void LESSASSIGN_arg_POINTER				( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	MxLESSASSIGN[ arg1->argClass ]
//			    [ arg2->addrInstruction->instr.res.argClass ]( arg1, &arg2->addrInstruction->instr.res, res );
//}
//static void LESSASSIGN_FLOAT_INT				( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	res->argClass = ARGC_BOOL;
//	res->valBool  = arg1->valFloat <= static_cast<float>(arg2->valInt);
//}
//static void LESSASSIGN_FLOAT_FLOAT				( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	res->argClass = ARGC_BOOL;
//	res->valBool = arg1->valFloat <= arg2->valFloat;
//}
//static void LESSASSIGN_FLOAT_BOOL				( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	res->argClass = ARGC_BOOL;
//	res->valBool = arg1->valFloat <= static_cast<float>(arg2->valBool);
//}
//static void LESSASSIGN_BOOL_INT				( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	res->argClass = ARGC_BOOL;
//	res->valBool  = static_cast<int>(arg1->valBool) <= arg2->valInt;
//}
//static void LESSASSIGN_BOOL_FLOAT				( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	res->argClass = ARGC_BOOL;
//	res->valBool  = static_cast<float>(arg1->valBool) <= arg2->valInt;
//}
//static void LESSASSIGN_BOOL_BOOL				( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	res->argClass = ARGC_BOOL;
//	res->valBool  = arg1->valBool <= arg2->valBool;
//}
//static void LESSASSIGN_GLOBAL_VAR_POINTER		( arg_t* arg1, arg_t* arg2, arg_t* res ){
//}
//static void LESSASSIGN_GLOBAL_VAR_arg			( arg_t* arg1, arg_t* arg2, arg_t* res ){
//}
//static void LESSASSIGN_GLOBAL_VAR_GLOBAL_VAR	( arg_t* arg1, arg_t* arg2, arg_t* res ){
//}
//static void LESSASSIGN_GLOBAL_VAR_LOCAL_VAR	( arg_t* arg1, arg_t* arg2, arg_t* res ){
//}
//static void LESSASSIGN_LOCAL_VAR_POINTER		( arg_t* arg1, arg_t* arg2, arg_t* res ){
//}
//static void LESSASSIGN_LOCAL_VAR_arg			( arg_t* arg1, arg_t* arg2, arg_t* res ){
//}
//static void LESSASSIGN_LOCAL_VAR_GLOBAL_VAR	( arg_t* arg1, arg_t* arg2, arg_t* res ){
//}
//static void LESSASSIGN_LOCAL_VAR_LOCAL_VAR		( arg_t* arg1, arg_t* arg2, arg_t* res ){
//}
//
//
////===========
////	!=
////===========
//static void EXCLAMASSIGN						( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	MxEXCLAMASSIGN[ arg1->argClass ][ arg2->argClass ]( arg1, arg2, res );
//}
//static void EXCLAMASSIGN_POINTER_POINTER		( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	MxEXCLAMASSIGN[ arg1->addrInstruction->instr.res.argClass ]
//				  [ arg2->addrInstruction->instr.res.argClass ]( &arg1->addrInstruction->instr.res,
//																 &arg2->addrInstruction->instr.res, res );
//}
//static void EXCLAMASSIGN_POINTER_GLOBAL_VAR	( arg_t* arg1, arg_t* arg2, arg_t* res ){
//}
//static void EXCLAMASSIGN_POINTER_LOCAL_VAR		( arg_t* arg1, arg_t* arg2, arg_t* res ){
//}
//static void EXCLAMASSIGN_POINTER_arg			( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	MxEXCLAMASSIGN[ arg1->addrInstruction->instr.res.argClass ]
//				  [ arg2->argClass ]( &arg1->addrInstruction->instr.res, arg2, res );
//}
//static void EXCLAMASSIGN_error					( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	// error
//}
//static void EXCLAMASSIGN_arg_POINTER			( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	MxEXCLAMASSIGN[ arg1->argClass ]
//				  [ arg2->addrInstruction->instr.res.argClass ]( arg1, &arg2->addrInstruction->instr.res, res );
//}
//static void EXCLAMASSIGN_INT_INT				( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	res->argClass = ARGC_BOOL;
//	res->valBool  = arg1->valInt != arg2->valInt;
//}
//static void EXCLAMASSIGN_INT_FLOAT				( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	res->argClass = ARGC_BOOL;
//	res->valBool  = arg1->valInt != arg2->valFloat;
//}
//static void EXCLAMASSIGN_INT_BOOL				( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	res->argClass = ARGC_BOOL;
//	res->valBool  = arg1->valInt != static_cast<int>(arg2->valBool);
//}
//static void EXCLAMASSIGN_arg_GLOBAL_VAR		( arg_t* arg1, arg_t* arg2, arg_t* res ){
//}
//static void EXCLAMASSIGN_arg_LOCAL_VAR			( arg_t* arg1, arg_t* arg2, arg_t* res ){
//}
//static void EXCLAMASSIGN_FLOAT_INT				( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	res->argClass = ARGC_BOOL;
//	res->valBool  = arg1->valFloat != arg2->valInt;
//}
//static void EXCLAMASSIGN_FLOAT_FLOAT			( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	res->argClass = ARGC_BOOL;
//	res->valBool  = arg1->valFloat != arg2->valFloat;
//}
//static void EXCLAMASSIGN_FLOAT_BOOL			( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	res->argClass = ARGC_BOOL;
//	res->valBool  = arg1->valFloat != static_cast<float>(arg2->valBool);
//}
//static void EXCLAMASSIGN_STRING_STRING			( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	res->argClass = ARGC_BOOL;
//	res->valBool  = !strcmp( arg1->valStr, arg2->valStr );
//}
//static void EXCLAMASSIGN_BOOL_INT				( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	res->argClass = ARGC_BOOL;
//	res->valBool  = static_cast<int>(arg1->valBool) != arg2->valInt;
//}
//static void EXCLAMASSIGN_BOOL_FLOAT			( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	res->argClass = ARGC_BOOL;
//	res->valBool  = static_cast<float>(arg1->valBool) != arg2->valFloat;
//}
//static void EXCLAMASSIGN_BOOL_BOOL				( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	res->argClass = ARGC_BOOL;
//	res->valBool  = arg1->valBool != arg2->valBool;
//}
//static void EXCLAMASSIGN_GLOBAL_VAR_POINTER	( arg_t* arg1, arg_t* arg2, arg_t* res ){
//}
//static void EXCLAMASSIGN_GLOBAL_VAR_arg		( arg_t* arg1, arg_t* arg2, arg_t* res ){
//}
//static void EXCLAMASSIGN_GLOBAL_VAR_GLOBAL_VAR	( arg_t* arg1, arg_t* arg2, arg_t* res ){
//}
//static void EXCLAMASSIGN_GLOBAL_VAR_LOCAL_VAR	( arg_t* arg1, arg_t* arg2, arg_t* res ){
//}
//static void EXCLAMASSIGN_LOCAL_VAR_POINTER		( arg_t* arg1, arg_t* arg2, arg_t* res ){
//}
// static void EXCLAMASSIGN_LOCAL_VAR_arg		( arg_t* arg1, arg_t* arg2, arg_t* res ){
//}
//static void EXCLAMASSIGN_LOCAL_VAR_GLOBAL_VAR	( arg_t* arg1, arg_t* arg2, arg_t* res ){
//}
//static void EXCLAMASSIGN_LOCAL_VAR_LOCAL_VAR	( arg_t* arg1, arg_t* arg2, arg_t* res ){
//}
//
//
//static void NEGATE								( arg_t* arg1, arg_t* arg2, arg_t* res ){
//}
//static void JMP								( arg_t* arg1, arg_t* arg2, arg_t* res ){
//	::VMArr[ ::curVM ]->internalCode->MoveTo( arg1->addrInstruction );
//}
//static void JMPF								( arg_t* arg1, arg_t* arg2, arg_t* res ){
//}
//static void JMPT								( arg_t* arg1, arg_t* arg2, arg_t* res ){
//}
//static void CALL								( arg_t* arg1, arg_t* arg2, arg_t* res ){
//}
//static void RET								( arg_t* arg1, arg_t* arg2, arg_t* res ){
//}
//static void PUSH								( arg_t* arg1, arg_t* arg2, arg_t* res ){
//}
//static void POP								( arg_t* arg1, arg_t* arg2, arg_t* res ){
//}
//static void GDEND								( arg_t* arg1, arg_t* arg2, arg_t* res ){
//}
//static void NOP								( arg_t* arg1, arg_t* arg2, arg_t* res ){
//}