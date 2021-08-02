#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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


void Tree::Play()
{
	char* answer = (char*)calloc(MAX_NAME_SIZE, sizeof(char));
	struct Node* node = root;
	printf("Is it %s?\n", node->data);

	while (1)                         //////                 THERE MISTAKE
	{                             ///////////////////////             Bad order
		if (!strncmp(answer, "y", 1) || !strncmp(answer, "Y", 1))
		{
			if (node->left != nullptr && node->left->left == nullptr)
			{
				node = node->left;
				printf("This is %s?\n", node->data);
				break;
			}
			else if (node->left != nullptr && (node->left->left != nullptr || node->right->left != nullptr)) // Dangerous
			{
				node = node->left;
				printf("Is it %s?\n", node->data);
			}
			else {
				printf("Base is empty\n");
				return;
			}
		}
		else if (!strncmp(answer, "n", 1) || !strncmp(answer, "N", 1))
		{
			if (node->right != nullptr && node->right->right == nullptr)
			{
				node = node->right;
				printf("This is %s?\n", node->data);
				break;
			}
			else if (node->left != nullptr && (node->right->left != nullptr || node->left->left != nullptr))
			{
				node = node->right;
				printf("Is it %s?\n", node->data);
			}
			else {
				printf("Base is empty\n");
				return;
			}
		}
		else if (!strncmp(answer, "e", 1) || !strncmp(answer, "E", 1))
		{
			return;
		}
		scanf("%s", answer);
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