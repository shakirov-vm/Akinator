#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "Tree.h"

void Tree::DUMP()
{
	struct Knot* knot = root;

	FILE* potok = fopen("graph.dot", "w");

	printf("/=============================================\n");
	fprintf(potok, "digraph G {\n");
	printf("digraph G {\n");

	while(1)
	{
		while (knot->left != nullptr)
		{
			fprintf(potok, "[%s] -> [%s];\n", knot->data, knot->left->data);
			printf("[%s] -> [%s];\n", knot->data, knot->left->data);
			knot = knot->left;
		}
		break;

	}

	printf("}\n");
	fprintf(potok, "}\n");
	printf("/=============================================\n");
	
	fclose(potok);
}