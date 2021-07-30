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
/*
Tree& Tree::operator= (const Tree& tree)
{
	printf("WE INTO OPERATOR=\n");                      // This is shit
	root = (struct Node*)calloc(1, sizeof(struct Node));
	root->data = tree.root->data;
	root->left = tree.root->left;
	root->right = tree.root->right;
	root->parent = tree.root->parent;

	return *this;
}*/

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

	fread(base, sizeof(char), base_size, potok);

	char* end = base + base_size;

	fclose(potok);

	struct Node* node = (struct Node*)calloc(1, sizeof(struct Node));

	char* string = base;
	node->left = nullptr;
	node->right = nullptr;
	node->data = (char*)calloc(MAX_DATA_SIZE, sizeof(char));
	node->parent = nullptr;

	while (isspace(*string)) string++;
	if (*string == '{') {
		printf("THERE!\n"); 
		string++;
		while (isspace(*string)) string++;
		string = strtok(string, "$");

		size_t len = strlen(string);
		for (int i = 0; i < len; i++)
		{
			node->data[i] = string[i];
		}
		node->data[len] = '\0';
		printf("{{{%s}}}\n", node->data);
		string = string + strlen(string) + 1;
	}

	for (; string != end; string++)
	{
		if (*string == '{')
		{
			string++;
			while (isspace(*string)) string++;
			string = strtok(string, "$");

			node = ChargeNode(node->left, string, node);

			string = string + strlen(string) + 1;

			continue;
		}
		if (*string == '}')
		{
			if (node->parent != nullptr)
			{
				node->parent->right = node;
				node = node->parent;
			}
			continue;
		}
		if (*string == '$')
		{
			string++;
			while (isspace(*string)) string++;
			string = strtok(string, "$");

			node->parent->left = node;
			node = node->parent;
			node = ChargeNode(node->right, string, node);

			string = string + strlen(string) + 1;
			continue;
		}
	}
	root->left = node->left;
	root->right = node->right;
	root->data = node->data;

	free(base);
}

struct Node* ChargeNode(struct Node* node, char* string, struct Node* parent)
{
	node = (struct Node*)calloc(1, sizeof(Node));
	node->data = (char*)calloc(MAX_DATA_SIZE, sizeof(char));

	size_t len = strlen(string);
	for (int i = 0; i < len; i++)
	{
		node->data[i] = string[i];
	}
	//printf("[%s]\n", node->data);
	node->data[len] = '\0';                        //SegFault?
	node->left = nullptr;
	node->right = nullptr;
	node->parent = parent;

	return node;
}
/*
void NodePrint_2(struct Node* node, FILE* potok, int* i)
{
	if (node->left != nullptr)  // i - glubina * 2
	{
		for (int j = 0; j < *i; j++) fprintf(potok, "\t");
		fprintf(potok, "{\n");
		++(*i);
		for (int j = 0; j < *i; j++) fprintf(potok, "\t");
		fprintf(potok, "$%s%\n", node->left->data);
		++(*i);
		NodePrint_2(node->left, potok, i);
		--(*i);
		for (int j = 0; j < *i; j++) fprintf(potok, "\t");
		fprintf(potok, "$%s%\n", node->right->data);
		--(*i);
		for (int j = 0; j < *i; j++) fprintf(potok, "\t");
		fprintf(potok, "}\n");
		NodePrint_2(node->right, potok, i);
	}
}*/
void NodePrint_2(struct Node* node, FILE* potok, int* i)
{
	if (node != nullptr)  // i - glubina * 2
	{
		for (int j = 0; j < *i; j++) fprintf(potok, "\t");
		fprintf(potok, "{\n");
		++(*i);
		for (int j = 0; j < *i; j++) fprintf(potok, "\t");
		fprintf(potok, "$%s%\n", node->data);
		++(*i);
		NodePrint_2(node->left, potok, i);

		NodePrint_2(node->right, potok, i);
		--(*i);
		--(*i);
		for (int j = 0; j < *i; j++) fprintf(potok, "\t");
		fprintf(potok, "}\n");
		/*--(*i);
		//for (int j = 0; j < *i; j++) fprintf(potok, "\t");
		//fprintf(potok, "$%s%\n", node->data);
		--(*i);
		for (int j = 0; j < *i; j++) fprintf(potok, "\t");
		fprintf(potok, "}\n");*/
	}
}

void Tree::DumpBase()
{
	printf("Enter file name, where will be dump base\n");
	char* answer = (char*)calloc(100, sizeof(char)); //                           !!!!!!!
	scanf("%s", answer);

	FILE* potok = fopen(answer, "w");      //   !!!!!
	int i = 0;
	NodePrint_2(root, potok, &i);
	fclose(potok);
	free(answer);
}