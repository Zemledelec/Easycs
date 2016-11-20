#include "Scaner.h"


#define		SCANDIGIT			0
#define		SCANLETTER			1
#define		SCANSEPARATOR		2
#define		SCANPLUS			3
#define		SCANMINUS			4
#define		SCANPOINT			5
#define		SCANE				6
#define		SCANSLASH		    7
#define		SCANSTAR			8
#define		SCANINVCOMMAS		9
#define		SCANNEWLINE		   10
#define		SCAN0			   11
#define		SCANX			   12
#define		SCANA			   13
#define		SCANB			   14
#define		SCANC			   15
#define		SCAND			   16
#define		SCANF			   17
#define		SCANWHITE		   18
#define     SCANASSIGN		   19	
#define     SCANAND			   20	
#define     SCANOR			   21	
#define     SCANXOR			   22	
#define     SCANEXCLAM		   23	
#define     SCANMORE		   24	
#define     SCANLESS		   25	
#define     SCANPERCENT		   26	


void Scaner::Init()
{
	for( int i=0; i<=255; i++ )
		scanChar[i] = SCANSEPARATOR;

	// letters
	scanChar['_'] = SCANLETTER;
	scanChar['a'] = SCANA;
	scanChar['b'] = SCANB;
	scanChar['c'] = SCANC;
	scanChar['d'] = SCAND;
	scanChar['e'] = SCANE;
	scanChar['f'] = SCANF;
	scanChar['g'] = SCANLETTER;
	scanChar['h'] = SCANLETTER;
	scanChar['i'] = SCANLETTER;
	scanChar['j'] = SCANLETTER;
	scanChar['k'] = SCANLETTER;
	scanChar['l'] = SCANLETTER;
	scanChar['m'] = SCANLETTER;
	scanChar['n'] = SCANLETTER;
	scanChar['o'] = SCANLETTER;
	scanChar['p'] = SCANLETTER;
	scanChar['q'] = SCANLETTER;
	scanChar['r'] = SCANLETTER;
	scanChar['s'] = SCANLETTER;
	scanChar['t'] = SCANLETTER;
	scanChar['u'] = SCANLETTER;
	scanChar['v'] = SCANLETTER;
	scanChar['w'] = SCANLETTER;
	scanChar['x'] = SCANX;
	scanChar['y'] = SCANLETTER;
	scanChar['z'] = SCANLETTER;
	scanChar['A'] = SCANA;
	scanChar['B'] = SCANB;
	scanChar['C'] = SCANC;
	scanChar['D'] = SCAND;
	scanChar['E'] = SCANE;
	scanChar['F'] = SCANF;
	scanChar['G'] = SCANLETTER;
	scanChar['H'] = SCANLETTER;
	scanChar['I'] = SCANLETTER;
	scanChar['J'] = SCANLETTER;
	scanChar['K'] = SCANLETTER;
	scanChar['L'] = SCANLETTER;
	scanChar['M'] = SCANLETTER;
	scanChar['N'] = SCANLETTER;
	scanChar['O'] = SCANLETTER;
	scanChar['P'] = SCANLETTER;
	scanChar['Q'] = SCANLETTER;
	scanChar['R'] = SCANLETTER;
	scanChar['S'] = SCANLETTER;
	scanChar['T'] = SCANLETTER;
	scanChar['U'] = SCANLETTER;
	scanChar['V'] = SCANLETTER;
	scanChar['W'] = SCANLETTER;
	scanChar['X'] = SCANX;
	scanChar['Y'] = SCANLETTER;
	scanChar['Z'] = SCANLETTER;

	// digits
	scanChar['0'] = SCAN0;
	scanChar['1'] = SCANDIGIT;
	scanChar['2'] = SCANDIGIT;
	scanChar['3'] = SCANDIGIT;
	scanChar['4'] = SCANDIGIT;
	scanChar['5'] = SCANDIGIT;
	scanChar['6'] = SCANDIGIT;
	scanChar['7'] = SCANDIGIT;
	scanChar['8'] = SCANDIGIT;
	scanChar['9'] = SCANDIGIT;

	// separators
	scanChar[';'] = SCANSEPARATOR;
	scanChar['!'] = SCANEXCLAM;
	scanChar['@'] = SCANSEPARATOR;
	scanChar['#'] = SCANSEPARATOR;
	scanChar['$'] = SCANSEPARATOR;
	scanChar['%'] = SCANPERCENT;
	scanChar['^'] = SCANXOR;
	scanChar['&'] = SCANAND;
	scanChar['*'] = SCANSTAR;
	scanChar['('] = SCANSEPARATOR;
	scanChar[')'] = SCANSEPARATOR;
	scanChar['-'] = SCANMINUS;
	scanChar['+'] = SCANPLUS;
	scanChar['='] = SCANASSIGN;
	scanChar['|'] = SCANOR;
	scanChar[','] = SCANSEPARATOR;
	scanChar['.'] = SCANPOINT;
	scanChar['/'] = SCANSLASH;
	scanChar['<'] = SCANLESS;
	scanChar['>'] = SCANMORE;
	scanChar['['] = SCANSEPARATOR;
	scanChar[']'] = SCANSEPARATOR;
	scanChar['{'] = SCANSEPARATOR;
	scanChar['}'] = SCANSEPARATOR;
	scanChar[':'] = SCANSEPARATOR;
	scanChar['"'] = SCANINVCOMMAS;
	scanChar[EOF] = SCANSEPARATOR;

	// separators(white)
	scanChar[' '] = SCANWHITE;
	scanChar['\t'] = SCANWHITE;//Tab
	scanChar['\n'] = SCANNEWLINE;//'\n'
} 



int Scaner::scanTable[27][40] =
{
	/*______________________0____1____2____3____4____5____6____7____8____9____10____11____12____13____14____15____16____17____18____19____20____21____22____23____24____25____26____27____28____29_____30____31____32____33____34____35____36____37____38____39
	/*  SCANDIGIT     |*/	1,   1,   3,   3,   6,   6,   6,   7,   8,   0,   10,   11,   11,    1,   15,   15,    0,	 0,	   0,    0,    0,   0,     0,    0,    0,   0,     0,    0,    0,    0,     0,   0,    0,    0,    0,    0,    0,    0,     0,    0,
	/*  SCANLETTER    |*/	8, 255,   0, 255, 255, 255, 255,   7,   8,   0,   10,   11,   11,  255,  255,  255,    0,	 0,	   0,    0,    0,   0,     0,    0,    0,   0,     0,    0,    0,    0,     0,   0,    0,    0,    0,    0,    0,    0,     0,    0,
	/*  SCANSEPARATOR |*/   0,   0,   0,   0, 255, 255,   0,   7,   0,   0,   10,   11,   11,    0,  255,    0,    0,	 0,	   0,    0,    0,   0,     0,    0,    0,   0,     0,    0,    0,    0,     0,   0,    0,    0,    0,    0,    0,    0,     0,    0,
	/*  SCANPLUS	  |*/  17,   0, 255,   0,   5, 255,   0,   7,   0,   0,   10,   11,   11,    0,  255,    0,    0,   18,	   0,    0,    0,   0,     0,    0,    0,   0,     0,    0,    0,    0,     0,   0,    0,    0,    0,    0,    0,    0,     0,    0,
	/*  SCANMINUS     |*/  19,   0, 255,   0,   5, 255,   0,   7,   0,   0,   10,   11,   11,    0,  255,    0,    0, 	 0,	   0,   20,    0,   0,     0,    0,    0,   0,     0,    0,    0,    0,     0,   0,    0,    0,    0,    0,    0,    0,     0,    0,
	/*  SCANPOINT     |*/	2,   3,   0, 255, 255, 255, 255,   7,   0,   0,   10,   11,   11,    3,  255,  255,    0,	 0,	   0,    0,    0,   0,     0,    0,    0,   0,     0,    0,    0,    0,     0,   0,    0,    0,    0,    0,    0,    0,     0,    0,
	/*  SCANE         |*/	8,   4,   0,   4, 255, 255, 255,   7,   8,   0,   10,   11,   11,  255,   15,   15,    0,	 0,	   0,    0,    0,   0,     0,    0,    0,   0,     0,    0,    0,    0,     0,   0,    0,    0,    0,    0,    0,    0,     0,    0, 
	/*  SCANSLASH     |*/	9,   0,   0,   0, 255, 255,   0,   7,   0,  10,   10,   11,    0,    0,  255,    0,    0,	 0,	   0,    0,    0,   0,     0,    0,    0,   0,     0,    0,    0,    0,     0,   0,    0,    0,    0,    0,    0,    0,     0,    0,
	/*  SCANSTAR      |*/  21,   0,   0,   0, 255, 255,   0,   7,   0,  11,   10,   12,   12,    0,  255,    0,    0,	 0,	   0,    0,    0,   0,     0,    0,    0,   0,     0,    0,    0,    0,     0,   0,    0,    0,    0,    0,    0,    0,     0,    0,
	/*  SCANINVCOMMAS |*/   7,   0,   0,   0, 255, 255,   0,   0,   0,   0,   10,   11,   11,  255,  255,  255,    0,	 0,	   0,    0,    0,   0,     0,    0,    0,   0,     0,    0,    0,    0,     0,   0,    0,    0,    0,    0,    0,    0,     0,    0,
	/*  SCANNEWLINE   |*/  16,   0,   0,   0, 255, 255,   0, 255,   0,   0,    0,   11,   11,    0,  255,    0,   16,	 0,	   0,    0,    0,   0,     0,    0,    0,   0,     0,    0,    0,    0,     0,   0,    0,    0,    0,    0,    0,    0,     0,    0, 
	/*	SCAN0		  |*/  13,	 1,	  3,   3,   6,   6,   6,   7,   8,   0,   10,   11,   11,    1,   15,   15,    0,	 0,	   0,    0,    0,   0,     0,    0,    0,   0,     0,    0,    0,    0,     0,   0,    0,    0,    0,    0,    0,    0,     0,    0,
	/*	SCANX		  |*/   8, 255,   0, 255, 255, 255, 255,   7,   8,   0,   10,   11,   11,   14,  255,  255,    0,	 0,	   0,    0,    0,   0,     0,    0,    0,   0,     0,    0,    0,    0,     0,   0,    0,    0,    0,    0,    0,    0,     0,    0,
	/*	SCANA		  |*/   8, 255,   0, 255, 255, 255, 255,   7,   8,   0,   10,   11,   11,  255,   15,   15,    0,	 0,	   0,    0,    0,   0,     0,    0,    0,   0,     0,    0,    0,    0,     0,   0,    0,    0,    0,    0,    0,    0,     0,    0,
	/*	SCANB		  |*/   8, 255,   0, 255, 255, 255, 255,   7,   8,   0,   10,   11,   11,  255,   15,   15,    0,	 0,	   0,    0,    0,   0,     0,    0,    0,   0,     0,    0,    0,    0,     0,   0,    0,    0,    0,    0,    0,    0,     0,    0,
	/*	SCANC		  |*/   8, 255,   0, 255, 255, 255, 255,   7,   8,   0,   10,   11,   11,  255,   15,   15,    0,	 0,	   0,    0,    0,   0,     0,    0,    0,   0,     0,    0,    0,    0,     0,   0,    0,    0,    0,    0,    0,    0,     0,    0,
	/*	SCAND		  |*/   8, 255,   0, 255, 255, 255, 255,   7,   8,   0,   10,   11,   11,  255,   15,   15,    0,	 0,	   0,    0,    0,   0,     0,    0,    0,   0,     0,    0,    0,    0,     0,   0,    0,    0,    0,    0,    0,    0,     0,    0,
	/*	SCANF		  |*/   8, 255,   0, 255, 255, 255, 255,   7,   8,   0,   10,   11,   11,  255,   15,   15,    0,	 0,	   0,    0,    0,   0,     0,    0,    0,   0,     0,    0,    0,    0,     0,   0,    0,    0,    0,    0,    0,    0,     0,    0,
	/*	SCANWHITE     |*/  16,   0,   0,   0, 255, 255,   0,   7,   0,   0,   10,   11,   11,    0,  255,    0,   16,    0,    0,    0,    0,   0,     0,    0,    0,   0,     0,    0,    0,    0,     0,   0,    0,    0,    0,    0,    0,    0,     0,    0,
	/*  SCANASSIGN    |*/  28,   0,   0,   0, 255, 255,   0,   7,   0,  23,   10,   11,   11,    0,  255,    0,    0,   18,	   0,   20,    0,  22,     0,    0,   25,   0,    27,    0,   29,    0,    31,   0,   33,    0,   35,    0,   37,    0,    39,    0,
	/*  SCANAND       |*/  24,   0,   0,   0, 255, 255,   0,   7,   0,   0,   10,   12,   12,    0,  255,    0,    0,	 0,	   0,    0,    0,   0,     0,    0,   25,   0,     0,    0,    0,    0,     0,   0,    0,    0,    0,    0,    0,    0,     0,    0,
	/*  SCANOR        |*/  26,   0,   0,   0, 255, 255,   0,   7,   0,   0,   10,   12,   12,    0,  255,    0,    0,	 0,	   0,    0,    0,   0,     0,    0,    0,   0,    27,    0,    0,    0,     0,   0,    0,    0,    0,    0,    0,    0,     0,    0,
	/*  SCANXOR       |*/  30,   0,   0,   0, 255, 255,   0,   7,   0,   0,   10,   12,   12,    0,  255,    0,    0,	 0,	   0,    0,    0,   0,     0,    0,    0,   0,     0,    0,    0,    0,     0,   0,    0,    0,    0,    0,    0,    0,     0,    0,
	/*  SCANEXCLAM    |*/  32,   0,   0,   0, 255, 255,   0,   7,   0,   0,   10,   12,   12,    0,  255,    0,    0,	 0,	   0,    0,    0,   0,     0,    0,    0,   0,     0,    0,    0,    0,     0,   0,    0,    0,    0,    0,    0,    0,     0,    0,
	/*  SCANMORE      |*/  34,   0,   0,   0, 255, 255,   0,   7,   0,   0,   10,   12,   12,    0,  255,    0,    0,	 0,	   0,    0,    0,   0,     0,    0,    0,   0,     0,    0,    0,    0,     0,   0,    0,    0,    0,    0,    0,    0,     0,    0,
	/*  SCANLESS      |*/  36,   0,   0,   0, 255, 255,   0,   7,   0,   0,   10,   12,   12,    0,  255,    0,    0,	 0,	   0,    0,    0,   0,     0,    0,    0,   0,     0,    0,    0,    0,     0,   0,    0,    0,    0,    0,    0,    0,     0,    0,     
	/*  SCANPERCENT   |*/  38,   0,   0,   0, 255, 255,   0,   7,   0,   0,   10,   12,   12,    0,  255,    0,    0,	 0,	   0,    0,    0,   0,     0,    0,    0,   0,     0,    0,    0,    0,     0,   0,    0,    0,    0,    0,    0,    0,     0,    0    
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
};


bool Scaner::IsKeyword( const char* str ){
	for( int i=0; keywords[i]; i++ ){		
		if( !strcmp( keywords[i], str ) )
			return true;
	}
	return false;
}

int Scaner::Str2Int( const char *str ){
	int n=0;
	int d=1;
	int l = static_cast<int>( strlen( str ) );
	while( l>0 ){			
		l--;
		n += d * ( str[ l ] - 48 );
		d *= 10;
	}
	return n;
}


float Scaner::Str2Float( const char *str )
{
	
	int	len = static_cast<int>( strlen( str ) );

	if( strcspn("e", str)!=len ||
		strcspn("E", str)!=len )
	{	
		// float
		float	n=0.0f;
		int		d=1;
		int		s=0;
		while( len>0 ){					
			len--;
			if( str[ len ]=='e' ||
				str[ len ]=='E' ||
				str[ len ]=='+'  )
			{
				if( s==0 )
					s = static_cast<int>(n);
				d = 1;
				n = 0.0f;
			}
			else if( str[ len ]=='-' ){
					s = static_cast<int>(-n);
					d = 1;
					n = 0.0f;
				}
				else if( str[ len ]=='.' ){
					n/= d;
					d = 1;
				}
				else
				{
					n += static_cast<float>( d * ( str[ len ] - 48 ) );
					d *= 10;
				}
		}					
		return ( n * pow( 10.0f, s ) );
	}
	else
	{
		// fix(float)
		float n=0.0f;
		int d=1;
		while( len>0 ){			
			len--;
			if( str[ len ]=='.' ){
				n/= d;
				d = 1;
			}
			else{
				n += d * ( str[ len ] - 48 );
				d *= 10;
			}
		}				
		return n;
	}
}


int Scaner::HStr2Int( const char *str ){
	int n=0;
	int d=1;
	int len = static_cast<int>( strlen(str) );
	while( len>2 ){			
		len--;
		if( scanChar[ str[len] ] == SCANDIGIT ||
			scanChar[ str[len] ] == SCAN0 )
			n += d * ( str[ len ] - 48 );
		else if( str[len] == 'A' ||
				 str[len] == 'B' ||
				 str[len] == 'C' ||
				 str[len] == 'D' ||
				 str[len] == 'E' ||
				 str[len] == 'F' )
				 n += d * ( str[len] - 55 );
		else if( str[len] == 'a' ||
				 str[len] == 'b' ||
				 str[len] == 'c' ||
				 str[len] == 'd' ||
				 str[len] == 'e' ||
				 str[len] == 'f' )
				 n += d * ( str[len] - 87 );
		d *= 16;
	}
	return n;
}



int Scaner::Read( token_s& t )
{
	LArray<char> buffer(512);
	int  top  = 0;

	int prescond = 0;// текущее состояние(present condition)
	int prevcond = 0;// предыдущее состояние(previous condition)

	bool ft = false;

	// считывает лексему(read token)
	do{
		char ch;
		fread( &ch, 1, 1, fp );

		// вычисление позиции
		t.fPos.Char += 1;
		if( ch=='\n' ){
			t.fPos.Line += 1;
			t.fPos.Char  = t.fPos.Column = 1;
		}
		if( ch=='\t' )
			t.fPos.Column += 4;
		else
			t.fPos.Column += 1;

		// переход состояния в автомате ЛА(сканера)
		prescond = scanTable[ scanChar[ch] ][ prevcond ];


		// убираем кавычки из строки
		buffer[ ch=='"'?top:top++ ] = ch;

		// возврат в начальное состояние автомата
		if( prescond==0 )
		{			
			// убираем кавычки из строки
			if( ch!='"' )
				buffer[ top==1?1:top-1 ]=0;
			else
				buffer[top]=0;

			ft=true;

			// separator
			if( prevcond==0  || prevcond==2  || prevcond==9  || prevcond==17 || prevcond==18 || prevcond==19 ||
				prevcond==20 || prevcond==21 || prevcond==22 || prevcond==23 || prevcond==24 || prevcond==25 ||
				prevcond==26 || prevcond==27 || prevcond==28 || prevcond==29 || prevcond==30 || prevcond==31 ||
				prevcond==32 || prevcond==33 || prevcond==34 || prevcond==35 || prevcond==36 || prevcond==37 ||
				prevcond==38 || prevcond==39 )
			{
				t.Set( TC_SEPARATOR, buffer.Data() );
			}
			// int
			else if( prevcond==1 || prevcond==13 ){
				t.Set( TC_CONSTANT_INT, Str2Int( buffer.Data() ) );
			}
			// float
			else if( prevcond==3 || prevcond==6 ){
				t.Set( TC_CONSTANT_FLOAT, Str2Float( buffer.Data() ) );
			}
			// string
			else if( prevcond==7 ){
				t.Set( TC_STRING, buffer.Data() );
			}
			// variable|keyword
			else if( prevcond==8 ){
				if( IsKeyword( buffer.Data() ) )
					t.Set( TC_KEYWORD, buffer.Data() );
				else
					t.Set( TC_VARIABLE, buffer.Data() );
			}
			// hex int
			else if( prevcond==15 ){
				t.Set( TC_CONSTANT_INT, HStr2Int( buffer.Data() ) );
			}	
			// white
			else if( prevcond==10 || prevcond==12 || prevcond==16 ){
				top=0;
				ft=false;
			}

			if( prevcond!=0 && prevcond!=7 && prevcond!=10 && prevcond!=12 )
				fseek( fp, ftell( fp )-1, SEEK_SET );
		}

		prevcond = prescond;

	}while( !ft && !feof(fp) && prescond!=255 );
	
	if( feof(fp) ){ t.Set( TC_SEPARATOR, "eof" ); }

	return prescond;
}


