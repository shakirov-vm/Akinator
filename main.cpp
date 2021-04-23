#include <stdio.h>
//void AddList(struct Knot* knot, char* question, char* answer) 

#ifndef TREE_H_
#define TREE_H_
#include "Tree.h"
#endif

int main()
{
	class Tree Akinator;
	char* question = (char*)calloc(MAX_STR_SIZE, sizeof(char));
	char* answer = (char*)calloc(MAX_STR_SIZE, sizeof(char));

	sprintf(question, "Hello!");
	sprintf(answer, "GoodBUUUY");

	printf("main\n");
	//Akinat.Root->string = question;
	AddList(Akinator.Root, question, answer);
}