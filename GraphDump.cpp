#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <iostream>

#ifndef TREE_H_
#define TREE_H_
#include "Tree.h"
#endif

#ifndef ERRORS_H
#define ERRORS_H
#include "Errors.h"
#endif

void Tree::DumpGraph()
{
	FILE* potok = file_open("Enter file name, where will be dump graph\n", "w");

	fprintf(potok, "digraph G {\n");
	PrintGraph(root, potok);

	fprintf(potok, "}\n");

	fclose(potok);
}

void PrintGraph(struct Node* node, FILE* potok)
{
	if (node->left != nullptr)
	{
		fprintf(potok, "\"%s\" -> \"%s\";\n", node->data, node->left->data);
		fprintf(potok, "\"%s\" -> \"%s\";\n", node->data, node->right->data);
		PrintGraph(node->left, potok);
		PrintGraph(node->right, potok);
	}
}

void PrintBase(struct Node* node, FILE* potok, int* depth, int equalizer) //The value of the equalizer is selected so that there are no extra brackets
{
	if (node != nullptr) 
	{
		if (!equalizer) {
			for (int j = 0; j < *depth; j++) fprintf(potok, "\t");
			fprintf(potok, "{\n");
			++(*depth);
			++(*depth);
		}
		for (int j = 0; j < (*depth) - 1; j++) fprintf(potok, "\t");
		fprintf(potok, "$%s$\n", node->data);
		PrintBase(node->left, potok, depth, 0);
		PrintBase(node->right, potok, depth, 1);
		if (equalizer) {
			--(*depth);
			--(*depth);
			for (int j = 0; j < *depth; j++) fprintf(potok, "\t");
			fprintf(potok, "}\n");
		}
	}
}

void Tree::DumpBase()  //          DO text for writing
{
	FILE* potok = file_open("Enter file name, where will be dump base\n", "w");

	int depth = 0;
	PrintBase(root, potok, &depth, 0);
	fprintf(potok, "}\n");
	fclose(potok);
}