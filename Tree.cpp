
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "Tree.h"

Tree::Tree()
{
	root = (struct Knot*)calloc(1, sizeof(struct Knot));
	root->data = (char*)calloc(MAX_DATA_SIZE, sizeof(char));
	root->left = nullptr;
	root->right = nullptr;
	root->parent = nullptr;
}
Tree::~Tree()
{
	DeleteBranch(root);
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
	knot = (struct Knot*)calloc(1, sizeof(struct Knot));
	knot->data = (char*)calloc(MAX_DATA_SIZE, sizeof(char));
	knot->left = nullptr;
	knot->right = nullptr;
	knot->parent = parent;
}

void DeleteBranch(struct Knot* knot)
{
	if (knot != NULL) {

		DeleteBranch(knot->left);
		DeleteBranch(knot->right);

		free(knot->data);
		free(knot);
	}
}

void Tree::FillAkinator(char* base_name)
{
	char* base = (char*)calloc(MAX_BASE_SIZE, sizeof(char));

	FILE* potok = fopen(base_name, "r");

	fread(base, sizeof(char), MAX_BASE_SIZE, potok);

	fclose(potok);

	struct Knot* knot = (struct Knot*)calloc(1, sizeof(struct Knot));

	char* string = base;
	knot->left = nullptr;
	knot->right = nullptr;
	knot->data = (char*)calloc(MAX_DATA_SIZE, sizeof(char));
	knot->parent = nullptr;

	for (;; string++)
	{
		if (isspace(*string)) continue;
		if (*string == '[')
		{
			string++;
			while (isspace(*string)) string++;
			string = strtok(string, "@");

			size_t len = strlen(string);
			for (int i = 0; i < len; i++)
			{
				knot->data[i] = string[i];
			}
			knot->data[len] = '\0';

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

			break;
		}
	}

	free(base);
}

struct Knot* FillKnot(struct Knot* knot, char* string, struct Knot* parent)
{
	knot = (struct Knot*)calloc(1, sizeof(Knot));
	knot->data = (char*)calloc(MAX_DATA_SIZE, sizeof(char));

	size_t len = strlen(string);
	for (int i = 0; i < len; i++)
	{
		knot->data[i] = string[i];
	}
	printf("[%s]\n", knot->data);
	knot->data[len] = '\0';
	knot->left = nullptr;
	knot->right = nullptr;
	knot->parent = parent;

	return knot;
}