int fib( float& z, int& n )
{
	fib( z,n );
}


float fib( int n )
{
    if( n < 2 ) return 1;
    return fib( n - 2 ) + fib( n - 1 );
}

int fib( int z, int n )
{
	fib( 12.45,17 );
}


float k = 5;
k = fib(12, k);