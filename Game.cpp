#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

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
		std::cin >> answer;

		switch (answer)
		{
		case 1: //It's working
			printf("Let's start. Press \"y\" or \"n\" to start\n");
			Play();
			break;
		case 2: {			// LOAD BASE AND LOAD TO TREE
			printf("Enter file name:\n");
			char* base_name = (char*)calloc(MAX_NAME_SIZE, sizeof(char));

			std::cin.getline(base_name, MAX_NAME_SIZE, '\n');

			LoadBase(base_name);
			free(base_name);
			break;
		}
		case 3:     
			DumpGraph();
			break;
		case 4:
			DumpBase();
			break;
		case 5:
			exit(0);
		default:
			printf("Unknown command\n");
		}
	}
}


void Tree::Play()
{
	char* answer = (char*)calloc(MAX_NAME_SIZE, sizeof(char));
	NO_MEMORY(answer)

	struct Node* node = root;
	printf("Is it %s?\n", node->data);

	while (1)                        
	{                            
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
			else if (node->right != nullptr && (node->right->left != nullptr || node->left->left != nullptr))
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
		std::cin.getline(answer, MAX_NAME_SIZE, '\n');
	}
	std::cin.getline(answer, MAX_NAME_SIZE, '\n');
	if (!strncmp(answer, "y", 1) || !strncmp(answer, "Y", 1)) printf("I guess\n");
	else if (!strncmp(answer, "n", 1) || !strncmp(answer, "N", 1))
	{
		printf("I screwed up\n");
		printf("Enter your answer\n");
		std::cin.getline(answer, MAX_NAME_SIZE, '\n');

		node = ChargeNode(node->right, node->data, node);
		node->parent->right = node;
		node = node->parent;
		node = ChargeNode(node->left, answer, node);
		node->parent->left = node;

		printf("Enter the attribute that distinguishes YOUR character FROM the named one\n");
		std::cin.getline(answer, MAX_NAME_SIZE, '\n');

		node->parent->data = answer;

		node = root;

		return;                                     // HOW IT GOING?!!

		printf("One more time?\n");
		std::cin.getline(answer, MAX_NAME_SIZE, '\n');

		if (!strncmp(answer, "n", 1) || !strncmp(answer, "N", 1)) return;
	}

	free(answer);
}