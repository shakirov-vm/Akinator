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

	printf("You need load base. Enter name\n");
	char* answer = (char*)calloc(MAX_STR_SIZE, sizeof(char)); //// ??????????
	scanf("%s", answer);
	Akinator.LoadBase(answer);

	Akinator.Game();

	free(answer);
	return 0;
}