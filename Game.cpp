#include <stdio.h>
#include <stdlib.h>

#define MAX_NAME_SIZE 50

#ifndef TREE_H_
#define TREE_H_
#include "Tree.h"
#endif

void Tree::Game()
{
	size_t answer = 0;
	printf("Enter code:\n");
	scanf("%d", &answer);

	printf("answer is %d\n", answer);

	switch (answer)
	{
		case 2:
		{
			printf("LETS START\n");
			Play();
			break;
		}
		case 1:			// LOAD BASE AND LOAD TO TREE
		{
			printf("Enter file name:\n");
			char* base_name = (char*)calloc(MAX_NAME_SIZE, sizeof(char));

			scanf("%s", base_name);

			FillAkinator(base_name);

			break;
		}
		case 3:         //DUMP
		{
			DUMP();
			break;
		}
	}
	printf("WE OUT OF GAME\n\n");
}