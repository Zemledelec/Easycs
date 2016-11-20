#ifndef __EASYCS_INTERNAL_FORM__
#define __EASYCS_INTERNAL_FORM__

#include <string.h>

/*
====================================
	классы аргумента инструкции
====================================
*/
enum ARGCLASS{
	ARGC_VOID=0,		// тип аргумента void
	ARGC_INT,			// тип аргумента int
	ARGC_FLOAT,			// тип аргумента float
	ARGC_BOOL,			// тип аргумента bool
	ARGC_STRING,		// строковый тип аргумента
	ARGC_LOCAL_VAR,		// локальная переменная(адрес аргумента в записи активации: arg_t[0..n], 
						// n - кол-во локальных переменных в функции вместе с формальными  )
	ARGC_REFERENCE,		// ссылка (для передачи значения по ссылке)
	ARGC_GLOBAL_VAR,	// глобальная переменная(адрес аргумента в куче: arg_t*)
	ARGC_POINTER,		// адрес инструкции в коде(codesegment_t*)
	ARGC_ERROR
};


/*
===========================================
	Структуры внутреннего представления
===========================================
*/
struct codesegment_t;

struct arg_t{
	ARGCLASS				argClass;
	union{
		void				*pVoid;
		int					valInt;
		float				valFloat;
		bool				valBool;
		int					addrLocal;
		arg_t				*addrReference;
		codesegment_t		*addrInstruction;
		arg_t				*addrGlobal;

	};
	char *valStr;

	arg_t();
	arg_t( const arg_t& );
	arg_t( ARGCLASS, codesegment_t*	);
	arg_t( ARGCLASS, int			);
	arg_t( ARGCLASS, float			);
	arg_t( ARGCLASS, void*			);
	arg_t( ARGCLASS, const char*	);
	arg_t( ARGCLASS, bool			);
	arg_t( ARGCLASS, arg_t*			);

	~arg_t();
	arg_t& operator = ( const arg_t& );
};



inline arg_t::arg_t(){
	argClass = ARGC_INT;
	valInt = 0;
	valStr = 0x0000;
}




inline arg_t::arg_t( ARGCLASS a, codesegment_t* v ){
	argClass = a;
	addrInstruction = v;
	valStr = 0x0000;
}


inline arg_t::arg_t( ARGCLASS a, int v ){
	argClass = a;
	if( a == ARGC_INT ){
		valInt = v;
	}
	else if( a == ARGC_LOCAL_VAR ){
		addrLocal = v;
	}
	valStr = 0x0000;
}

inline arg_t::arg_t( ARGCLASS a, float v ){
	argClass = a;
	valFloat = v;
	valStr = 0x0000;
}

inline arg_t::arg_t( ARGCLASS a, void* v ){
	argClass = a;
	pVoid = v;
	valStr = 0x0000;
}

inline arg_t::arg_t( ARGCLASS a, bool v	){
	argClass = a;
	valBool = v;
	valStr = 0x0000;
}

inline arg_t::arg_t( ARGCLASS a, arg_t* v ){
	argClass = a;
	if( ARGC_GLOBAL_VAR == a )
		addrGlobal = v;
	else if( ARGC_REFERENCE == a )
		addrReference = v;
	valStr = 0x0000;
}

inline arg_t::arg_t( ARGCLASS a, const char* s ){
	argClass = a;
	int len = strlen( s ) + 1;
	valStr = new char[ len ];
	strcpy_s( valStr, len, s );
}


inline arg_t::~arg_t(){
	if( argClass == ARGC_STRING && valStr ){
		delete[] valStr;
		valStr = 0x0000;
	}
	valInt = 0;
}



class VirtualMachine;
typedef void (VirtualMachine::*cfptr)(arg_t*, arg_t*, arg_t*);
//typedef void (*fptr)( arg_t*, arg_t*, arg_t* );

// трехадресный код(четверка)
struct instruction_t{
	cfptr opf;
	arg_t *arg1, *arg2, *res;
};


// список четверок (адресное пространство кода)
struct codesegment_t{
	codesegment_t *next, *prev;
	instruction_t instr;
};




/*
========================================================

	Class InternalForm 
	Внутреннее представление программы.
	Трехадресный код представленный четверками.

========================================================
*/

class InternalCode
{
public:
	InternalCode();
	~InternalCode();

	codesegment_t* New();

	codesegment_t*	NewInstruction( const cfptr op, arg_t* arg1, arg_t* arg2 );
	void			SetInstruction( codesegment_t* addr, const cfptr op, 
														 arg_t* arg1, 
														 arg_t* arg2 );
	arg_t*			NewArg( const arg_t& arg );

	// перемещение по коду
	void StepNext();
	void StepPrev();
	void MoveTo( codesegment_t *p );
	codesegment_t *Current()const;
	codesegment_t *Begin()const;
	codesegment_t *End()const;
	int NumCodeSeg()const;
	
	int numCodeSeg;				// кол-во инструкций(размер таблицы четверок)
	codesegment_t *codeCurr;	// указатель на текущую инструкцию
	codesegment_t *codeBegin;	// адрес начала кода
	codesegment_t *codeEnd;		// адрес конца кода
private:

};


inline void InternalCode::StepNext(){ 
	codeCurr = codeCurr->next; 
}

inline void InternalCode::StepPrev(){
	codeCurr = codeCurr->prev;
}

inline void InternalCode::MoveTo( codesegment_t *p ){
	codeCurr = p;
}

inline codesegment_t* InternalCode::Current()const{
	return codeCurr;
}

inline codesegment_t* InternalCode::Begin()const{
	return codeBegin;
}

inline codesegment_t* InternalCode::End()const{
	return codeEnd;
}

inline int InternalCode::NumCodeSeg()const{
	return numCodeSeg;
}



#endif