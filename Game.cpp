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
	printf("There are the following possibilities here:\n");
	printf("1 - start game\n");
	printf("2 - load base from file\n");
	printf("3 - see base's graph\n");
	printf("4 - save base\n");
	printf("5 - exit\n");

	while (1) {
		printf("Enter code:\n");
		scanf("%d", &answer);

		switch (answer)
		{
		case 1:
			printf("Let's start. Press \"y\" or \"n\" to start\n");
			Play();
			break;
		case 2: {			// LOAD BASE AND LOAD TO TREE
			printf("Enter file name:\n");
			char* base_name = (char*)calloc(MAX_NAME_SIZE, sizeof(char));

			scanf("%s", base_name);

			LoadBase(base_name);
			free(base_name);
			break;
		}
		case 3:         //DUMP
			DumpGraph();
			break;
		case 4:
			DumpBase();
			break;
		case 5:
			exit(0);
		}
	}
}