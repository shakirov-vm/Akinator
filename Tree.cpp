#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <sys/stat.h>
#include "Tree.h"

Tree::Tree()
{
	root = (struct Node*)calloc(1, sizeof(struct Node));  //          nullptr??
	root->data = (char*)calloc(MAX_DATA_SIZE, sizeof(char));
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
	node = (struct Node*)calloc(1, sizeof(struct Node));
	node->data = (char*)calloc(MAX_DATA_SIZE, sizeof(char));
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

void Tree::LoadBase(char* base_name)
{
	struct stat buff;
	stat(base_name, &buff);
	size_t base_size = buff.st_size;

	char* base = (char*)calloc(base_size, sizeof(char));

	FILE* potok = fopen(base_name, "r");
	if (potok == nullptr) {
		printf("This file can't be open. Maybe it don't create\n");
		return;
	}

	fread(base, sizeof(char), base_size, potok);

	char* end = base + base_size;

	fclose(potok);

	struct Node* node = (struct Node*)calloc(1, sizeof(struct Node));

	char* counter = base;
	node->left = nullptr;
	node->right = nullptr;
	node->data = (char*)calloc(MAX_DATA_SIZE, sizeof(char));
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
		if (*counter == '}')
		{
			if (node->parent != nullptr)
			{
				node->parent->right = node;
				node = node->parent;
			}
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
	}
	root->left = node->left;
	root->right = node->right;
	root->data = node->data;

	free(base);
}

struct Node* ChargeNode(struct Node* node, char* counter, struct Node* parent)
{
	node = (struct Node*)calloc(1, sizeof(Node));
	node->data = (char*)calloc(MAX_DATA_SIZE, sizeof(char));

	size_t len = strlen(counter);
	for (int i = 0; i < len; i++)
	{
		node->data[i] = counter[i];
	}
	//printf("[%s]\n", node->data);
	node->data[len] = '\0';                        //SegFault?
	node->left = nullptr;
	node->right = nullptr;
	node->parent = parent;

	return node;
}
