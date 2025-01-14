#include <stdlib.h>

int var;
int var2;

void baz(void);

void
foo(int *data)
{
	baz();
	return;
}

int
bar(void)
{
	foo(NULL);
	foo(&var);
	foo(&var2);

	return 0;
}
