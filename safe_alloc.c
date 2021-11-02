#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct
{
	int ** allocate;
	int i;
} safe_alloc;

void safe_alloc_init( safe_alloc *a ) {
	a->i = 0;
	a->allocate = malloc( sizeof(int) );
}

void * safe_alloc_new( safe_alloc *a, int size ) {
	void *ret = malloc( size );
	a->allocate = realloc(a->allocate, sizeof(int) * (a->i + 1) );
	a->allocate[a->i++] = ret;
	return ret;
}

void * safe_alloc_get( safe_alloc *a ) {
	return a->allocate[a->i-1];
}

void safe_free( safe_alloc *a) {
	for( int i = 0; i < a->i; i++ ) {
		free(a->allocate[i]);
	}
	free(a->allocate);
}

safe_alloc allocate;

int main(int argc, char const *argv[])
{
	safe_alloc_init( &allocate );
	char *t = safe_alloc_new( &allocate, 10 );
	*t++ = 't';
	*t++ = 'e';
	*t++ = 's';
	*t++ = 't';

	printf("%s\n", safe_alloc_get( &allocate ) );

	char *t1 = safe_alloc_new( &allocate, 10 );
	strcpy( t1, "test2");
	printf("%s\n", t1);

	//this free up all allocation
	safe_free( &allocate );

	return 0;
}