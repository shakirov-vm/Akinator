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