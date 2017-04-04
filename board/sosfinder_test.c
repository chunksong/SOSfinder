#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[])
{
	if(argc < 2) {
		printf("no input file\n");
	}

	printf("%d\n", (int)strlen(argv[1]));

	return 0;
}
