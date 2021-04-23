#include "stdio.h"

#ifndef TREE_H_
#define TREE_H_
#include "Tree.h"
#endif

Tree::Tree()
{
	printf("Con\n");
	Root = (Knot*) calloc (1, sizeof(Knot));
	Root->string = (char*)calloc(MAX_STR_SIZE, sizeof(char));
	
	assert(Root->string);
	Root->left = nullptr;
	Root->right = nullptr;
}
Tree::~Tree()
{
	printf("Dec\n");
	DeleteBranch(Root);
}
void DeleteList(struct Knot* knot)
{
	assert(!(knot->right));
	assert(!(knot->left));
	free(knot->string);
	knot = nullptr;
	printf("%p - %p\n", knot->right, knot->left);
}
void DeleteBranch(struct Knot* knot)
{
	if (knot != nullptr)
	{
		//printf(">>>%X, %X\n", knot, knot->right);
		DeleteBranch(knot->right);
		DeleteBranch(knot->left);

		free(knot->string);
		knot = nullptr;
	}
	printf("There\n");
	DeleteList(knot);
}
void AddList(struct Knot* knot, char* question, char* answer)
{
	assert(!(knot->right));
	assert(!(knot->left));
	struct Knot* Left = (Knot*)calloc(1, sizeof(Knot));
	struct Knot* Right = (Knot*)calloc(1, sizeof(Knot));;

	Right->string = knot->string;
	Left->string = answer;
	knot->string = question;

	Right->left = nullptr;
	Right->right = nullptr;
	Left->left = nullptr;
	Left->right = nullptr;
	knot->left = Left;
	knot->right = Right;
	printf("{%p %p}\n", knot->left, knot->right);
}