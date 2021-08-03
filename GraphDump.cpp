#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <iostream>
#include "Tree.h"

void Tree::DumpGraph()
{
	FILE* potok = fopen("graph.dot", "w");
	if (potok == nullptr) {
		printf("This file can't be open\n");
		return;
	}

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
	printf("Enter file name, where will be dump base\n");
	char* answer = (char*)calloc(100, sizeof(char)); 
	NO_MEMORY(answer)

	std::cin.getline(answer, MAX_NAME_SIZE, '\n');

	FILE* potok = fopen(answer, "w");     
	if (potok == nullptr) {
		printf("This file can't be open\n");
		return;
	}

	int depth = 0;
	PrintBase(root, potok, &depth, 0);
	fprintf(potok, "}\n");
	fclose(potok);
	free(answer);
}