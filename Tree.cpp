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
	printf("WE INTO OPRATOR=\n");
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

	char* string = (char*) calloc (MAX_DATA_SIZE, sizeof(char));       
	struct Knot* knot = (struct Knot*) calloc (1, sizeof(struct Knot));    

	string = base;
	knot->left = nullptr;
	knot->right = nullptr;
	knot->data = (char*) calloc (MAX_DATA_SIZE, sizeof(char));
	knot->parent = nullptr;
	

	//knot = root;

			// ???
	for (; *string != '\0'; string++)
	{
		if (isspace(*string)) continue;
		if (*string == '{')
		{
			string++;
			while(isspace(*string)) string++;
			string = strtok(string, "$");
			printf("<<<{%p} - [%s], <%d>\n", string, string, *string);

			printf(">>> %p\n", knot);
			printf(">>> %p\n", knot->left);
			knot = FillKnot(knot->left, string, knot);

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

			//knot = FillKnot(knot->right, string, knot);

			string = string + strlen(string) + 1;  // Maybe it is dangerous
			continue;
		}
	}
	printf("WE OUT\n");

	free(base);
	//free(string);     ?????   Не надо сюда память выделять наверное
	//free(knot);
}
//knot = FillKnot(root, string, nullptr);

/*for (int i = 0; base[i] != '\0'; i++)
{
	if (isspace(base[i])) continue;
	if (base[i] == '{')
	{
		knot = FillKnot(knot->left, string, knot);
	}
	if (base[i] == '\'')
	{
		knot = FillKnot(knot->right, string, knot);
	}
	if (base[i] == '}')
	{
		knot = knot->parent;
	}
}*/
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