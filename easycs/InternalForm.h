#ifndef __EASYCS_INTERNAL_FORM__
#define __EASYCS_INTERNAL_FORM__

/*
====================================
	������ ��������� ����������
====================================
*/
enum ARGCLASS{
	ARGC_POINTER=0,		// ����� ���������� � ����(codesegment_t*)
	ARGC_VOID,			// ��� ��������� void
	ARGC_VALUE_INT,		// ��� ��������� int
	ARGC_VALUE_FLOAT,	// ��� ��������� float
	ARGC_VALUE_STRING,  // ��������� ��� ���������
	ARGC_VALUE_BOOL,	// ��� ��������� bool
	ARGC_GLOBAL_VAR,	// ���������� ����������(����� ��������� � ����: arg_t*)
	ARGC_LOCAL_VAR		// ��������� ����������(����� ��������� � ������ ���������: arg_t[0..n], 
						// n - ���-�� ��������� ���������� � ������� ������ � �����������  )
};


/*
===========================================
	��������� ����������� �������������
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

// ������������ ���(��������)
struct instruction_t{
	void (*fptr)( arg_t*, arg_t*, arg_t* );
	arg_t arg1, arg2, res;
};


// ������ �������� (�������� ������������ ����)
struct codesegment_t{
	codesegment_t *next, *prev;
	instruction_t instr;
};



/*
========================================================

	Class InternalForm 
	���������� ������������� ���������.
	������������ ��� �������������� ����������.

========================================================
*/

class InternalCode
{
public:
	InternalCode();
	~InternalCode();

	// ���������� ����� ���������� � ����������
	// ..

	// ����������� �� ����
	void StepNext();
	void StepPrev();
	void MoveTo( codesegment_t *p );
	codesegment_t *Current()const;
	codesegment_t *Begin()const;
	codesegment_t *End()const;

	int NumCodeSeg()const;
	
private:

	int numCodeSeg;				// ���-�� ����������(������ ������� ��������)
	codesegment_t *codeSeg;		// ������������ ����(���������� ������� ��������)
	codesegment_t *codeCurr;	// ��������� �� ������� ����������
	codesegment_t *codeBegin;	// ����� ������ ����
	codesegment_t *codeEnd;		// ����� ����� ����
};


// �����������
InternalCode::InternalCode(){
		codeSeg = new codesegment_t;
		codeCurr = codeBegin = codeEnd = codeSeg;
		codeSeg->prev = codeSeg->next = NULL;		
		numCodeSeg = 0;
}

// ����������
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