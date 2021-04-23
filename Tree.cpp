
#ifndef TREE_H_
#define TREE_H_
#include "Tree.h"
#endif

Tree::Tree()
{
	Root->string = (char*) calloc (MAX_STR_SIZE, sizeof(char));
	assert(Root->string);
	Root->left  = nullptr;
	Root->right = nullptr;
}
Tree::~Tree()
{
	DeleteBranch(Root);
}
void Tree::DeleteList(struct Knot* knot)
{
	assert(!(knot->left));
	assert(!(knot->left));
	free(knot->string);
	knot = nullptr;
}
void DeleteBranch(struct Knot* knot)
{
	if (knot != nullptr)
	{
		DeleteBranch(knot->right);
		DeleteBranch(knot->left);

		free(knot->string);
		knot = nullptr;
	}
}
void AddList(struct Knot* knot, char* question, char* answer) 
{
	assert(!(knot->left));
	assert(!(knot->left));
	struct Knot Left;
	struct Knot Right;

	Right.string = knot->string;
	Left.string	 = answer;
	knot->string = question;

	Right.left	= nullptr;
	Right.right = nullptr;
	Left.left	= nullptr;
	Left.right  = nullptr;
	knot->left	= &Left;
	knot->right = &Right;
}