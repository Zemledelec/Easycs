int main( int f )
{

    int num = 1000000;
    int res = 0;

    for( int i=0; i<num; i+=1 )
    {
        res+=1;
    }
    return 0;
}


int main2() 
{
  int num = 16;
  int res = 0;

  for(int a = 0; a < num; a+=1){
    for(int b = 0; b < num; b+=1){
      for(int c = 0; c < num; c+=1){
        for(int d = 0; d < num; d+=1){
          for(int e = 0; e < num; e+=1){
            for(int f = 0; f < num; f+=1){
              res+=1;
            }
          }
        }
      }
    }
  }

}

int main() 
{
    int num = 1000000;
    int res;
    for(int i = 0; i < num; i+=1)
    {
        res = 12 + (133 - 571) * 2 + i * 5;
    }
return 123;
}

int main3(){
    int repeat = 10;
    int num = 100000;

    for(int j = 0; j < repeat; j+=1)
    {
        for(int i = 0; i < num; i+=1)
        {
          float f = 3.14 * i / num;
//          f = (f + 1)/6;
//          f = 2*f - 1;
        }
    }
    return 0;
}



int fib( int n)
{
  if(n < 2) return 1;
  return fib(n - 2) + fib(n - 1);
}

int tt = main3();