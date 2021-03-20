#include<stdio.h>
void main(int argc, char **argv)
{	
	printf("argc is %d\n", argc);
	printf("Program %s is runnincg\n", argv[0]);
	for(int i=1 ; i<argc; i++)
	{
		printf("argv[%d] = %s\n", i, argv[i]);
	}

}
