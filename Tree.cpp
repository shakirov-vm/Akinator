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
		string++;
		while (isspace(*string)) string++;
		string = strtok(string, "$");

		size_t len = strlen(string);
		for (int i = 0; i < len; i++)
		{
			node->data[i] = string[i];
		}
		//node->data[len] = '\0';
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
/*
void PrintBase(struct Node* node, char* base, int* depth, int equalizer) //The value of the equalizer is selected so that there are no extra brackets
{
	if (node != nullptr) // ?? lishnii ++?
	{
		if (!equalizer) {
			for (int j = 0; j < *depth; j++) {
				printf("%p - ", base);
				sprintf(base, "\t");
				printf("%p\n", base);
				base++;
			}
			sprintf(base, "{\n");
			base += 2;
			++(*depth);
			++(*depth);
		}
		for (int j = 0; j < (*depth) - 1; j++) {
			sprintf(base, "\t");
			base++;
		}
		sprintf(base, "$%s$\n", node->data);          //        ???????????
		base += strlen(node->data) + 3;
		PrintBase(node->left, base, depth, 0);
		PrintBase(node->right, base, depth, 1);
		if (equalizer) {
			--(*depth);
			--(*depth);
			for (int j = 0; j < *depth; j++) {
				sprintf(base, "\t");
				base++;
			}
			sprintf(base, "}\n");
			base += 2;
		}
	}
}

void Tree::DumpBase()  //          DO text for writing
{
	printf("Enter file name, where will be dump base\n");
	char* answer = (char*)calloc(100, sizeof(char)); //                           !!!!!!!
	scanf("%s", answer);
	char* base = (char*)calloc(MAX_BASE_SIZE, sizeof(char));
	char* start = base;
	FILE* potok = fopen(answer, "w");      //   !!!!!
	int i = 0;
	PrintBase(root, base, &i, 0);
	printf("%s\n==================================================\n", start);
	for (int i = 0; i < 1000; i++) {
		if (start[i] == '0') printf("!");
		else printf("%c", start[i]);
	}
	free(start);
	fclose(potok);
	free(answer);
}*/

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