# Easycs
Long time ago I made my own computer language(C grammar) interpreter, for making things I like the most.
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
