#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "Tree.h"

#define MAX_DATA_SIZE 100
#define MAX_BASE_SIZE 100000

Tree::Tree()
{
	root = (struct Knot*)calloc(1, sizeof(struct Knot));
	printf("ROOT PTR IS {%p}\n", root);
	root->data = (char*)calloc(MAX_DATA_SIZE, sizeof(char));
	root->left = nullptr;
	root->right = nullptr;
	root->parent = nullptr;
	printf("ROOT: root - [%p]; data - (%p);\nleft -  {%p}; right - {%p}; parent -  {%p}\n\n", root, root->data, root->left, root->right, root->parent);
}
Tree::~Tree()
{
	printf("ROOT IS %p - WILL BE DEAD\n", root);
	//DeleteBranch(root);
}
Tree& Tree::operator= (const Tree& tree)
{
	printf("WE INTO OPERATOR=\n");
	root = (struct Knot*)calloc(1, sizeof(struct Knot));
	root->data = tree.root->data;
	root->left = tree.root->left;
	root->right = tree.root->right;
	root->parent = tree.root->parent;

	return *this;
}

void KnotConstruct(struct Knot* knot, struct Knot* parent)
{
	//printf("ROOT BEFORE CALLOC - %p\n", knot);
	knot = (struct Knot*)calloc(1, sizeof(struct Knot));
	knot->data = (char*)calloc(MAX_DATA_SIZE, sizeof(char));
	knot->left = nullptr;
	knot->right = nullptr;
	knot->parent = parent;
	//printf("ROOT AFTER CALLOC - %p\n", knot);
}

void DeleteBranch(struct Knot* knot)
{
	printf("I - %p - DEAD\n", knot);
	if (knot != NULL) {

		DeleteBranch(knot->left);
		DeleteBranch(knot->right);

		free(knot->data);
		free(knot);
	}
}

void Tree::FillAkinator(char* base_name)
{
	printf("WE ENTER INTO AKINATOR\n");

	//printf("ROOT: root - [%p]; data - (%p);\nleft - {%p}; right - {%p}; parent -  {%p}\n\n", root, root->data, root->left, root->right, root->parent);

	char* base = (char*)calloc(MAX_BASE_SIZE, sizeof(char));

	FILE* potok = fopen(base_name, "r");
	//printf("FILE* is %p\n", potok);

	fread(base, sizeof(char), MAX_BASE_SIZE, potok);

	fclose(potok);

	struct Knot* knot = (struct Knot*)calloc(1, sizeof(struct Knot));

	char* string = base;
	knot->left = nullptr;
	knot->right = nullptr;
	knot->data = (char*)calloc(MAX_DATA_SIZE, sizeof(char));
	knot->parent = nullptr;

	/*for (; *string != '\0'; string++)
	{
		if (isspace(*string)) continue;
		if (*string == '{')
		{
			string++;
			while (isspace(*string)) string++;
			string = strtok(string, "$");
			knot->data = string;
			root->data = string;
			string = string + strlen(string) + 1;
			break;
		}
	}*/
	//printf("ROOT: root - [%p]; data - (%s);\nleft - {%p}; right - {%p}; parent -  {%p}\n\n", root, root->data, root->left, root->right, root->parent);
	printf("START KNOT - [%p]\n\n\n\n", knot);
	for (; *string != '\0'; string++)
	{
		if (isspace(*string)) continue;
		if (*string == '[')
		{
			string++;
			while (isspace(*string)) string++;
			string = strtok(string, "@");

			knot->data = string;

			string = string + strlen(string) + 1;

			continue;
		}
		if (*string == '{')
		{
			string++;
			while (isspace(*string)) string++;
			string = strtok(string, "$");

			knot = FillKnot(knot->left, string, knot);

			string = string + strlen(string) + 1;

			continue;
		}
		if (*string == '}')
		{
			if (knot->parent != nullptr)
			{
				knot->parent->right = knot;
				knot = knot->parent;
			}
			continue;
		}
		if (*string == '$')
		{
			string++;
			while (isspace(*string)) string++;
			string = strtok(string, "$");

			knot->parent->left = knot;
			knot = knot->parent;
			knot = FillKnot(knot->right, string, knot);

			string = string + strlen(string) + 1;
			continue;
		}
		if (*string == ']')
		{
			root->left = knot->left;
			root->right = knot->right;
			root->data = knot->data;

			continue;
		}
	}

	free(base);
}

struct Knot* FillKnot(struct Knot* knot, char* string, struct Knot* parent)
{
	knot = (struct Knot*)calloc(1, sizeof(Knot));
	knot->data = (char*)calloc(MAX_DATA_SIZE, sizeof(char));
	knot->data = string;
	knot->left = nullptr;
	knot->right = nullptr;
	knot->parent = parent;

	return knot;
}