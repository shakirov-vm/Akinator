#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

#ifndef TREE_H_
#define TREE_H_
#include "Tree.h"
#endif

#ifndef ERRORS_H
#define ERRORS_H
#include "Errors.h"
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
		while (scanf("%llu", &answer) != 1) {
			printf("Enter valid code\n");
			fseek(stdin, 0, SEEK_END);
		}

		switch (answer)
		{
		case 1: 
			Play();
			break;
		case 2: {			// LOAD BASE AND LOAD TO TREE
			LoadBase();
			break;
		}
		case 3:     
			DumpGraph();
			break;
		case 4:
			DumpBase();
			break;
		case 5:
			return;
		default:
			printf("Unknown command\n");
		}
	}
}

void Tree::Play()
{
	char* answer = (char*)calloc(MAX_NAME_SIZE, sizeof(char));
	if (answer == nullptr) return;

	struct Node* node = root;
	printf("Is it %s?\n", node->data);

	while (1)
	{
		if (check_answer(answer, "yes"))
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
		else if (check_answer(answer, "no"))
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
		else if (check_answer(answer, "exit")) 
			return;
		std::cin.getline(answer, MAX_NAME_SIZE, '\n');
	}
	std::cin.getline(answer, MAX_NAME_SIZE, '\n');
	if (check_answer(answer, "yes"))
		printf("I guess\n");
	else if (check_answer(answer, "no"))
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

		return;                 // Why don't free(answer) ??                    
	}

	free(answer);
}