# Easycs
C like language interpreter, for making things...fast and easy!
It's comparatively fast interpreter, and completely primitive against other languages such as Python, LUA, and even Angel Script. Nevertheless...
Now, I want just to save it here as a good memory.

Unfortunately, remains only basics things such as local and global variables, block variables, 
and native simple types, arrays and recursive function calls. It handles grammar and lexical erros, But it was able to work with 
3D engine named Caloris:) which was lost in time like...you know what in rain.

```easycs.exe <filename>```

```
int fib( int n)
{
  if(n < 2) return 1;
  return fib(n - 2) + fib(n - 1);
}

int tt = main3();

int fib(term, val=1, prev=0) {        
    if(term == 0) return prev;        
    if(term == 1) return val;        
    return fib (term - 1, val + prev, val);    
};
```

### Requirements

1. Strict typing.
2. Basic types: int, float, bool, string, void.
3. Dynamic array as a basic type. Type of stored elements.
4. Creation of user-defined types in OOP. Classes.
5. Block visibility.
6. Automatic variables.
7. Declaration of local and global variables.
8. Parameters of basic types, except arrays, are passed to functions by value. User-defined types are passed by reference.
9. Usage of built-in global functions in the code.
10. Access to the VM's control stack from the program's code. This means obtaining and modifying the VM's state, calling methods, and modifying script variables.
11. Control flow statements: if-else, while, do-while, for. break, continue.
12. Single-line comments are indicated by '//', multiline comments are indicated by '/' (open) and '/' (close).
13. Preprocessor facilities, include and define directives.


### Translation mechanism

1. Preprocessor processing.
Input: Program written in the easycs language as a text file.
Output: Program written in the esycs language with macro substitutions performed. This is a temporary file divided into lines, taking into account the macro substitutions of the C language rules. Each line starts with a comment indicating the name of the source file and the line number.

2. Syntax-directed translation.
Input: Program written in the easycs language.
Output: Internal representation of the program for the easycs VM.
This phase consists of two passes. The first pass checks for syntax and lexical errors. The second pass checks for semantic errors (type checking) and constructs the internal representation for the VM.


Внутренее представление ВМ включает в себя набор механизмов для выполнения кода.

Основа кода - это список трехадресных инструкций представленных четверками(инструкциями):

описание инструкции:

op - адрес метода обработки данной инструкции;
arg1, arg2 - аргументы
res - аргумент-результат выполнения оператора над аргументами.


Работа ВМ заключается в последовательном выполнении операций op инструкции списка четверок.

Работу ВМ easycs обеспечивают механизмы:

Список четверок(инструкций), стек записей активаций(фреймов), стек передачи параметров,
массив прототипов глобальных функций.


### Реализация


```typedef void (VirtualMachine::*cfptr)( arg_t*, arg_t*, arg_t* );```

```
struct instruction_t{
    cfptr opf;
    arg_t arg1, arg2, res;
};
```

```
struct arg_t{
    ARGCLASS argClass;
    union{
        codesegment_t    *addrInstruction;
        void      	 *pVoid;
        int        	 valInt;
        float        	 valFloat;
        char        	 *valStr;
        bool        	 valBool;
        arg_t        	 *addrGlobal;
        int        	 addrLocal;
    };
};
```

```
enum ARGCLASS{
    ARGC_POINTER=0,     // адрес инструкции в коде(codesegment_t*)
    ARGC_VOID,    	// тип аргумента void
    ARGC_INT,    	// тип аргумента int
    ARGC_FLOAT,    	// тип аргумента float
    ARGC_STRING,    	// строковый тип аргумента
    ARGC_BOOL,    	// тип аргумента bool
    ARGC_GLOBAL_VAR,	// глобальная переменная(адрес аргумента в куче: arg_t*)
    ARGC_LOCAL_VAR    	// локальная переменная(адрес аргумента в записи активации: arg_t[0..n],
            		// n - кол-во локальных переменных в функции вместе с формальными  )
};
```

```
struct codesegment_t{
    codesegment_t *next, *prev;
    instruction_t instr;
};
```

```
struct activationrecord_s{   
    int        		numVars;    	// кол-во локальных и формальных переменных
    arg_t        	*localVars;     // массив локальных переменных
    arg_t        	retVar;         // возвращаемое значение
    codesegment_t    	*addrCall;    	// сохраненное состояние счетчика комманд(адрес возврата)
};
```

### Virtual Machine and Syntax Analyzer

```
class InternalCode
{
public:
    InternalCode();
    ~InternalCode();

    codesegment_t* New();
    codesegment_t* NewMext();

    // перемещение по коду
    void StepNext();
    void StepPrev();
    void MoveTo( codesegment_t *p );
    codesegment_t *Current()const;
    codesegment_t *Begin()const;
    codesegment_t *End()const;
    int NumCodeSeg()const;
   
private:

    int numCodeSeg;            // кол-во инструкций(размер таблицы четверок)
    codesegment_t *codeCurr;    // указатель на текущую инструкцию
    codesegment_t *codeBegin;    // адрес начала кода
    codesegment_t *codeEnd;        // адрес конца кода
};
```

```
class VirtualMachine{
public:
    VirtualMachine();
    virtual ~VirtualMachine();

protected:
    friend Parser;
    friend VMEasycs;

    InternalCode    *internalCode;
    Stack frameStack;    // runtime стек записей активации
    Stack argStack;            // runtime стек аргументов для передачи по значению

    // функции-операторы виртуальной машины
    void PLUS     ( arg_t* arg1, arg_t* arg2, arg_t* res );
    void MINUS     ( arg_t* arg1, arg_t* arg2, arg_t* res );
    //...

    void CALL     ( arg_t* arg1, arg_t* arg2, arg_t* res );
    void RET     ( arg_t* arg1, arg_t* arg2, arg_t* res );
    void PUSH     ( arg_t* arg1, arg_t* arg2, arg_t* res );
    void POP     ( arg_t* arg1, arg_t* arg2, arg_t* res );
    //...
}
```

```
class Parser
{
public:
    Parser();
    ~Parser();

    void AssignVM( const VirtualMachine* pvm );
    void Compile( const char* fileName );

private:
    // результат парсера
    friend VMEasycs;
    VirtualMachine *vm;


    //...

    // Грамматика рекурсивного спуска
    // набор функций PASS1
    // набор функций PASS2

};
```

```
class VMEasycs
{
public:
    VMEasycs();
    ~VMEasycs();

    void Assign( const VirtualMachine* vm );
    void Load( const char* fileName );
    void Execute();

private:
    Parser parser;
    VirtualMachine *pvm;     //указатель на виртуальую машину.

};
```

### Function Overloading and Scope Visibility

Транслятор отслеживает область видимости с помощью стека области видимости namespaceStack. Это 
массив строк соответствующих названиям областей. Когда нужно узнать имя по области видимости 
из стека области видимости собирается строка вида:
```[ название области видимости1 ]::[ название области видимости2 ]::{ ... }```


1. Имя функции транслятор предбразует к виду ```[ область видимости ]::@[ имя функции ]```.
2. Выполняется поиск на точное соответствие типов уже существующих одноименных функций:
	а) Из хеш таблицы перегруженных функций возврашаем кол-во уже перегруженных функций.
	б) Вычисляем название функции путем подставления в конец названия функции числа взятого
	   из хеш таблицы перегруженных функций, и уменьшаем это число на единицу для следующей итерации.
	в) Из хеш таблицы функций, по преобразованному названию функции определяем кол-во формальных параметров,
           и проверяем на точное соответствие типы формальных параметров уже существующей 
 	   ф-ии и проверяемой(транслирующейся в данный момент). Если кол-во не совпадает то ф-я перегружена, если
	   хотя-бы один из типов сравниваемых параметров не совпадает, то ф-я перегружена. Выходим из цикла.
        г) Если предыдущий цикл закончился с положительным результатом, переходим в пункт б),
           иначе выдаем сообщение об ошибке, что ф-я уже существует.
3. Если однозначных соответствий не найдено, По имени функции в хеш таблице пергруженных функций 
   увеличиваем счетчик одноименных перегруженных функций.


При трансляции вызова функции выполнется алгоритм на наибольшее соответствие формальных и 
фактических параметров.
По первоначальному названию функции строится множество ф-й добавлением каждому имени номера 
из области значений взятых из таблицы перегруженных функций.
Для каждой полученной функции возвращаем типы формальных параметров, сравниваем с соответствующей 
парой, типы формального и фактического параметров, вычисляем коэфициент соответствия путем 
сложения чисел лежащих на пересечении таблицы коэфициентов сужения этих типов.
Выбор остается за той функцией, для которой коэфициент минимален, но не меньше нуля!


Имя локальной переменной, а в том числе и имя формальной переменной ф-и, строится так:
```[ область видимости ]::@[ имя функции с номером перегрузки ]::[ имя переменной ]#[ номер блока ]```

Первый символ в названии функции '@' - признак трансляции функции.
Первый символ в названии функции '$' - признак трансляции класса.



Пример:
```
class CBoo
{
	int t;
	void fun()
        1{
        	int a;
		2{
			int p;
		}

		3{
			int b;
			4{
				class CFoo
				{
					int k;
					void fun( int ){};
					void fun( float ){};
				};
			}
		}
	};
};
```
```
CBoo  --> $CBoo#0
t     --> $CBoo#0::t
fun() --> $CBoo#0::@fun#0
a     --> $CBoo#0::@fun#0::a#1
p     --> $CBoo#0::@fun#0::p#2
b     --> $CBoo#0::@fun#0::b#3
CFoo  --> $CBoo#0::@fun#0::$CFoo#4
k     --> $CBoo#0::@fun#0::$CFoo#4::k#5
fun[2]--> $CBoo#0::@fun#0::$CFoo#4::@fun#0
fun[3]--> $CBoo#0::@fun#0::$CFoo#4::@fun#1
```

Пример:

```
01: void fun()
02: 1{
03:	 int a;
04:	 2{
05:		int a;
06:	 }
07:	
08:	 int a;
09:
10:	 3{
11:		 int a;
12:		 4{	
13:		 	int a;
14:		 }
15		 a;
16: 	 }
17: }
```
```
01: fun() --> @fun#0
03: a     --> @fun#0::a#1
05: a     --> @fun#0::a#2
08: a     --> @fun#0::a#1   // error: redefenition
11: a     --> @fun#0::a#3
13: a     --> @fun#0::a#4
15: a     --> @fun#0::a#3
```

Контроль соответствия типов происходит во время компиляции и во время исполнения.

Контроль соответствия типов во время компиляции осуществляется в момент добавления
инструкции в ВМ для бинарных и унарных операторов сложения сравнения присвоения и т.д.
Результат - тип - результат выполнения инструкции записывается в соответствующую интсрукцию
трехадресного кода. В случае несоответствия сообщает о ошибке.


Добавление критической функции глобальной области видимости.

1) Добавление вызова ф-ии через стандартный вызов иструкции для ВМ
2) Добавление информации о имени и типах для парсера данной ф-ии.



