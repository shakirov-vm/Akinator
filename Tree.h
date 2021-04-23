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
public:
	struct Knot* Root;

	Tree();
	~Tree();
	//void DeleteList(struct Knot* knot);
};

void DeleteList(struct Knot* knot);
void DeleteBranch(struct Knot* knot);
void AddList(struct Knot* knot, char* question, char* answer);