#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <sys/stat.h>
#include <iostream>

#ifndef TREE_H_
#define TREE_H_
#include "Tree.h"
#endif

#ifndef ERRORS_H
#define ERRORS_H
#include "Errors.h"
#endif

Tree::Tree()
{
	root = (struct Node*)calloc_error(1, sizeof(struct Node)); 
	root->data = (char*)calloc_error(MAX_DATA_SIZE, sizeof(char));
	root->left = nullptr;
	root->right = nullptr;
	root->parent = nullptr;
}
Tree::~Tree()
{
	DeleteBranch(root);
}

void NodeConstruct(struct Node* node, struct Node* parent)
{
	node = (struct Node*)calloc_error(1, sizeof(struct Node));
	node->data = (char*)calloc_error(MAX_DATA_SIZE, sizeof(char));
	node->left = nullptr;
	node->right = nullptr;
	node->parent = parent;
}

void DeleteBranch(struct Node* node)
{
	if (node != NULL) {

		DeleteBranch(node->left);
		DeleteBranch(node->right);

		free(node->data);
		free(node);
	}
}

void Tree::LoadBase()
{
	printf("You need load base. Enter name\n");
	char* base_name = (char*)calloc_error(100, sizeof(char));

	std::cin.getline(base_name, MAX_NAME_SIZE, '\n');

	FILE* potok = fopen_error(base_name, "r");

	struct stat buff;
	stat(base_name, &buff);
	size_t base_size = buff.st_size;

	free(base_name);

	char* base = (char*)calloc_error(base_size, sizeof(char));

	fread(base, sizeof(char), base_size, potok);

	char* end = base + base_size;

	fclose(potok);

	struct Node* node = (struct Node*)calloc_error(1, sizeof(struct Node));

	char* counter = base;
	node->left = nullptr;
	node->right = nullptr;
	node->data = (char*)calloc_error(MAX_DATA_SIZE, sizeof(char));
	node->parent = nullptr;
	// Load root
	while (isspace(*counter)) counter++;
	if (*counter == '{') {
		counter++;
		while (isspace(*counter)) counter++;
		counter = strtok(counter, "$");

		size_t len = strlen(counter);
		for (int i = 0; i < len; i++)
		{
			node->data[i] = counter[i];
		}
		counter = counter + strlen(counter) + 1;
	}

	for (; counter != end; counter++)
	{
		if (*counter == '{')
		{
			counter++;
			while (isspace(*counter)) counter++;
			counter = strtok(counter, "$");

			node = ChargeNode(node->left, counter, node);

			counter = counter + strlen(counter) + 1;
			continue;
		}
		if (*counter == '$')
		{
			counter++;
			while (isspace(*counter)) counter++;
			counter = strtok(counter, "$");

			node->parent->left = node;
			node = node->parent;

			node = ChargeNode(node->right, counter, node);

			counter = counter + strlen(counter) + 1;
			continue;
		}
		if (*counter == '}')
		{
			if (node->parent != nullptr)
			{
				node->parent->right = node;
				node = node->parent;
			}
			continue;
		}
	}
	root->left = node->left;
	root->right = node->right;
	root->data = node->data;

	free(base);
}

struct Node* ChargeNode(struct Node* node, char* counter, struct Node* parent)
{
	node = (struct Node*)calloc_error(1, sizeof(Node));
	node->data = (char*)calloc_error(MAX_DATA_SIZE, sizeof(char));

	size_t len = strlen(counter);
	for (int i = 0; i < len; i++)
	{
		node->data[i] = counter[i];
	}

	node->left = nullptr;
	node->right = nullptr;
	node->parent = parent;

	return node;
}
