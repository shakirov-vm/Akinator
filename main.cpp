#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_STR_SIZE 100

#ifndef TREE_H_
#define TREE_H_
#include "Tree.h"
#endif

int main()
{
	class Tree Akinator;

	printf("Do you want play? (Yes(Y)/ No(N))\n");
	
	char* answer = (char*)calloc(MAX_STR_SIZE, sizeof(char)); //// ??????????

	while (1)
	{
		scanf("%s", answer);
		if (!strcmp(answer, "yes") || !strcmp(answer, "Yes") || !strcmp(answer, "y") || !strcmp(answer, "Y")) {
			Akinator.Game();
			continue;
		}
		if (!strcmp(answer, "no") || !strcmp(answer, "No") || !strcmp(answer, "n") || !strcmp(answer, "N"))
			break;
		printf("Invalid command. Enter \"Yes\"(\"Y\") or \"No\"(\"N\")\n");
	}
	printf("Exit from game\n");
	free(answer);
	return 0;
}