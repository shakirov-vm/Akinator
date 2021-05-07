#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "Tree.h"

#define MAX_DATA_SIZE 100
#define MAX_BASE_SIZE 100000

Tree::Tree()
{
	root = {};
	//root = (struct Knot*) calloc (1, sizeof(struct Knot));
	KnotConstruct(root, nullptr);
}
Tree::~Tree()
{
	printf("ROOT IS %p - WILL BE DEAD\n", root);
	DeleteBranch(root);
}
Tree& Tree::operator= (const Tree& tree)
{
	printf("WE INTO OPERATOR=\n");
	root = (struct Knot*) calloc (1, sizeof(struct Knot));
	root->data = tree.root->data;
	root->left = tree.root->left;
	root->right = tree.root->right;
	root->parent = tree.root->parent;

	return *this;
}

void KnotConstruct(struct Knot* knot, struct Knot* parent)
{
	printf("ROOT BEFORE CALLOC - %p\n", knot);
	knot = (struct Knot*) calloc (1, sizeof(struct Knot));
	knot->data = (char*) calloc (MAX_DATA_SIZE, sizeof(char));
	knot->left  = nullptr;
	knot->right = nullptr;
	knot->parent = parent;
	printf("ROOT AFTER CALLOC - %p\n", knot);
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

void AddList(struct Knot* knot, char* question, char* answer)
{
	knot->right = (struct Knot*) calloc (1, sizeof(struct Knot));
	KnotConstruct(knot->right, knot);

	knot->left = (struct Knot*) calloc (1, sizeof(struct Knot));
	KnotConstruct(knot->left, knot);

	knot->right->data = knot->data;
	knot->data = question;
	knot->left->data = answer;
}

void Tree::FillAkinator(char* base_name)
{
	printf("WE ENTER INTO AKINATOR\n");

	char* base = (char*) calloc (MAX_BASE_SIZE, sizeof(char));
	
	FILE* potok = fopen(base_name, "r");           
	printf("FILE* is %p\n", potok);

	fread(base, sizeof(char), MAX_BASE_SIZE, potok);      

	fclose(potok);

	struct Knot* knot = (struct Knot*) calloc (1, sizeof(struct Knot));    

	char* string = base;
	knot->left = nullptr;
	knot->right = nullptr;
	knot->data = (char*) calloc (MAX_DATA_SIZE, sizeof(char));
	knot->parent = nullptr;
	
	int left = 0;
	int right = 0;

	for (; *string != '\0'; string++)
	{
		if (isspace(*string)) continue;
		if (*string == '{')
		{
			string++;
			while(isspace(*string)) string++;
			string = strtok(string, "$");
			knot->data = string;
			root->data = string;
			string = string + strlen(string) + 1;
			break;
		}
	}

	for (; *string != '\0'; string++)
	{
		if (isspace(*string)) continue;
		if (*string == '{')
		{
			string++;
			while(isspace(*string)) string++;
			string = strtok(string, "$");
			printf("<<<{%p} - [%s], <%d>\n", string, string, *string);

			knot = FillKnot(knot->left, string, knot);

			if (left == 0) root->left = knot;
			left = 1;

			string = string + strlen(string) + 1;

			continue;
		}
		if (*string == '}')
		{
			if (knot->parent != nullptr) knot = knot->parent;
			else break;
			continue;
		}
		if (*string == '$')
		{
			string++;
			while (isspace(*string)) string++;
			string = strtok(string, "$");
			if (*string == '}') break;                                                       // WERY DANGEROUS
			printf(">>>{%p} - [%s], <%d>\n", string, string, *string);

			knot = FillKnot(knot->right, string, knot);

			if (right == 0) root->right = knot;
			right = 1;

			string = string + strlen(string) + 1;  // Maybe it is dangerous
			continue;
		}
	}
	printf("WE OUT\n");



	free(base);
	//free(string);     ?????   Íå íàäî ñþäà ïàìÿòü âûäåëÿòü íàâåðíîå
	//free(knot);
}

struct Knot* FillKnot(struct Knot* knot, char* string, struct Knot* parent)
{
	printf("WE IN FILL\n");
	knot = (struct Knot*) calloc (1, sizeof(Knot));
	knot->data = (char*) calloc (MAX_DATA_SIZE, sizeof(char));
	knot->data = string;
	knot->left = nullptr;
	knot->right = nullptr;
	knot->parent = parent;
	printf("OUT OF FILL\n");
	return knot;
}