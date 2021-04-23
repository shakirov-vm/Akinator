
#include <stdlib.h>
#include <assert.h>

#define MAX_STR_SIZE 100 

struct Knot
{
	char* string;
	struct Knot* left;
	struct Knot* right;
};

class Tree
{
	struct Knot* Root;

	Tree();
	~Tree();
	void DeleteList(struct Knot* knot);
};

Tree::Tree()
{
	Root->string = (char*) calloc (MAX_STR_SIZE, sizeof(char));
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
