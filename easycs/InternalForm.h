#ifndef __EASYCS_INTERNAL_FORM__
#define __EASYCS_INTERNAL_FORM__

/*
====================================
	классы аргумента инструкции
====================================
*/
enum ARGCLASS{
	ARGC_POINTER=0,		// адрес инструкции в коде(codesegment_t*)
	ARGC_VOID,			// тип аргумента void
	ARGC_VALUE_INT,		// тип аргумента int
	ARGC_VALUE_FLOAT,	// тип аргумента float
	ARGC_VALUE_STRING,  // строковый тип аргумента
	ARGC_VALUE_BOOL,	// тип аргумента bool
	ARGC_GLOBAL_VAR,	// глобальная переменная(адрес аргумента в куче: arg_t*)
	ARGC_LOCAL_VAR		// локальная переменная(адрес аргумента в записи активации: arg_t[0..n], 
						// n - кол-во локальных переменных в функции вместе с формальными  )
};


/*
===========================================
	Структуры внутреннего представления
===========================================
*/
struct codesegment_t;

struct arg_t{
	ARGCLASS				argclass;
	union{
		codesegment_t		*addr_instruction;
		void				void_val;
		int					int_val;
		float				float_val;
		char				*str_val;
		bool				bool_val;
		arg_t				*addr_global_var;
		int					addr_local_var;
	};
};

// трехадресный код(четверка)
struct instruction_t{
	void (*fptr)( arg_t*, arg_t*, arg_t* );
	arg_t arg1, arg2, res;
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

	// добавление новой инструкции и аргументов
	// ..

	// перемещение по коду
	void StepNext();
	void StepPrev();
	void MoveTo( codesegment_t *p );
	codesegment_t *Current()const;
	codesegment_t *Begin()const;
	codesegment_t *End()const;

	int NumCodeSeg()const;
	
private:

	int numCodeSeg;				// кол-во инструкций(размер таблицы четверок)
	codesegment_t *codeSeg;		// пространство кода(собственно таблица четверок)
	codesegment_t *codeCurr;	// указатель на текущую инструкцию
	codesegment_t *codeBegin;	// адрес начала кода
	codesegment_t *codeEnd;		// адрес конца кода
};


// конструктор
InternalCode::InternalCode(){
		codeSeg = new codesegment_t;
		codeCurr = codeBegin = codeEnd = codeSeg;
		codeSeg->prev = codeSeg->next = NULL;		
		numCodeSeg = 0;
}

// деструктор
InternalCode::~InternalCode()
{
	codesegment_t *curr = Begin();
	while( !curr ){
		curr = curr->next;
		delete curr->prev;
	}
}


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