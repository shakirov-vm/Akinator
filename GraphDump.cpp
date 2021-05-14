#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "Tree.h"

#define MAX_NAME_SIZE 100

void Tree::DUMP()
{
	struct Knot* knot = (struct Knot*)calloc(1, sizeof(struct Knot));
	knot->data = root->data;
	knot->right = root->right;
	knot->left = root->left;

	FILE* potok = fopen("graph.dot", "w");

	fprintf(potok, "digraph G {\n");
	KnotPrint(knot, potok);

	fprintf(potok, "}\n");

	fclose(potok);
}

void KnotPrint (struct Knot* knot, FILE* potok)
{
	if (knot->left != nullptr) 
	{	
		fprintf(potok, "\"%s\" -> \"%s\";\n", knot->data, knot->left->data);
		fprintf(potok, "\"%s\" -> \"%s\";\n", knot->data, knot->right->data);
		KnotPrint(knot->left, potok); 
		KnotPrint(knot->right, potok);
	}
}

void Tree::Play()
{
	char* answer = (char*) calloc (MAX_NAME_SIZE, sizeof(char));
	struct Knot* knot = *(&root);

	printf("Is it %s?\n", knot->data);

	while(1)
	{
		scanf("%s", answer);

		if (!strncmp(answer, "y", 1) || !strncmp(answer, "Y", 1))
		{
			if (knot->left != nullptr) 
			{
				knot = knot->left;
				printf("Is it %s?\n", knot->data);				
			}
			else
			{
				printf("This is %s?\n", knot->data);
				break;
			}
		}
		else if (!strncmp(answer, "n", 1) || !strncmp(answer, "N", 1))
		{
			if (knot->right != nullptr) 
			{
				knot = knot->right;
				printf("Is it %s?\n", knot->data);				
			}
			else
			{
				printf("This is %s?\n", knot->data);
				break;
			}
		}
		else if(!strncmp(answer, "e", 1) || !strncmp(answer, "E", 1))
		{
			return;
		}
	}
	scanf("%s", answer);
	if (!strncmp(answer, "y", 1) || !strncmp(answer, "Y", 1)) printf("I guess\n");
	else if (!strncmp(answer, "n", 1) || !strncmp(answer, "N", 1)) printf("I screwed up\n");

	free(answer);
}