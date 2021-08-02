#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "Tree.h"

#define MAX_NAME_SIZE 100

void Tree::DumpGraph()
{
	/*struct Node* node = (struct Node*)calloc(1, sizeof(struct Node));
	node->data = root->data;
	node->right = root->right;
	node->left = root->left;*/

	FILE* potok = fopen("graph.dot", "w");

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
	if (node != nullptr)  // i - glubina * 2
	{
		if (!equalizer) {
			for (int j = 0; j < *depth; j++) fprintf(potok, "\t");
			fprintf(potok, "{\n");
			++(*depth);
			++(*depth);
		}
		for (int j = 0; j < (*depth) - 1; j++) fprintf(potok, "\t");
		fprintf(potok, "$%s%$\n", node->data);
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
	char* answer = (char*)calloc(100, sizeof(char)); //                           !!!!!!!
	scanf("%s", answer);

	FILE* potok = fopen(answer, "w");      //   !!!!!
	int depth = 0;
	PrintBase(root, potok, &depth, 0);
	fprintf(potok, "}\n");
	fclose(potok);
	free(answer);
}