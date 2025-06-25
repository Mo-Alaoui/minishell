#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{

	char *s = malloc(3);
	s = strcpy(s, "hi");

	printf("%s\n", s);
	free(s);
	s = NULL;
	if (s)
	    free(s);
}
