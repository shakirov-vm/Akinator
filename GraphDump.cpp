#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "Tree.h"

void Tree::DUMP()
{
	struct Knot* knot = (struct Knot*)calloc(1, sizeof(struct Knot));
	knot->data = root->data;
	knot->right = root->right;
	knot->left = root->left;

	FILE* potok = fopen("graph.txt", "w");

	printf("/=============================================\n");
	fprintf(potok, "digraph G {\n");
	printf("digraph G {\n");

	printf("knot - [%s], left - [%s], right - [%s]\n\n\n\n", root->data, root->left->data, root->right->data);

	KnotPrint(knot, potok);
	/*while (1)
	{
		while (knot->left != nullptr)
		{
			fprintf(potok, "[%s] -> [%s];\n", knot->data, knot->left->data);
			printf("[%s] -> [%s];\n", knot->data, knot->left->data);
			knot = knot->left;
		}
		break;

	}*/

	printf("}\n");
	fprintf(potok, "}\n");
	printf("/=============================================\n");

	fclose(potok);
}

void KnotPrint (struct Knot* knot, FILE* potok)
{
	if (knot != nullptr) 
	{
		if (knot->left != nullptr)
		{
			fprintf(potok, "[%s] -> [%s];\n", knot->data, knot->left->data);
			printf("[%s] -> [%s];\n", knot->data, knot->left->data);
			fprintf(potok, "[%s] -> [%s];\n", knot->data, knot->right->data);
			printf("[%s] -> [%s];\n", knot->data, knot->right->data);
		}
		if (knot->parent != nullptr)
		{
			fprintf(potok, "[%s] -> [%s];\n", knot->data, knot->parent->data);
			printf("[%s] -> [%s];\n", knot->data, knot->parent->data);
		}
		KnotPrint(knot->left, potok); 
		KnotPrint(knot->right, potok);
	}
}