#include <stdlib.h>

int var;
int var2;

void
foo(int *data)
{
	*data = 4;
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
