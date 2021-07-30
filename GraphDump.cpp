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
	NodePrint(root, potok);

	fprintf(potok, "}\n");

	fclose(potok);
}

void NodePrint(struct Node* node, FILE* potok)
{
	if (node->left != nullptr)
	{
		fprintf(potok, "\"%s\" -> \"%s\";\n", node->data, node->left->data);
		fprintf(potok, "\"%s\" -> \"%s\";\n", node->data, node->right->data);
		NodePrint(node->left, potok);
		NodePrint(node->right, potok);
	}
}

void Tree::Play()
{
	char* answer = (char*)calloc(MAX_NAME_SIZE, sizeof(char));
	struct Node* node = root;

	while (1)
	{
		scanf("%s", answer);
		if (!strncmp(answer, "y", 1) || !strncmp(answer, "Y", 1))
		{
			if (node->left != nullptr)
			{
				printf("Is it %s?\n", node->data);
				node = node->left;
			}
			else
			{
				printf("This is %s?\n", node->data);
				break;
			}
		}
		else if (!strncmp(answer, "n", 1) || !strncmp(answer, "N", 1))
		{
			if (node->right != nullptr)
			{
				printf("Is it %s?\n", node->data);
				node = node->right;
			}
			else
			{
				printf("This is %s?\n", node->data);
				break;
			}
		}
		else if (!strncmp(answer, "e", 1) || !strncmp(answer, "E", 1))
		{
			return;
		}
	}
	scanf("%s", answer);
	if (!strncmp(answer, "y", 1) || !strncmp(answer, "Y", 1)) printf("I guess\n");
	else if (!strncmp(answer, "n", 1) || !strncmp(answer, "N", 1))
	{
		printf("I screwed up\n");
		printf("Enter your answer\n");
		scanf("%s", answer);
		printf("KNOT NOW IS {%s}\n", node->data);
		node = ChargeNode(node->right, node->data, node);
		node->parent->right = node;
		node = node->parent;
		node = ChargeNode(node->left, answer, node);
		node->parent->left = node;
		printf("KNOT NOW IS {%s}\n", node->data);

		printf("Enter the attribute that distinguishes YOUR character FROM the named one\n");
		scanf("%s", answer);

		node->parent->data = answer;
		printf("KNOT NOW IS {%s}\n", node->parent->data);

		node = root;

		printf("ROOT IS {%s}\n", node->data);

		return;                                     // HOW IT GOING?!!

		printf("One more time?\n");
		scanf("%s", answer);

		if (!strncmp(answer, "n", 1) || !strncmp(answer, "N", 1)) return;
	}

	free(answer);
}