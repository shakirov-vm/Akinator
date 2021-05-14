
#include <stdio.h>
#include <stdlib.h>
//void AddList(struct Knot* knot, char* question, char* answer) 
#define MAX_STR_SIZE 100

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

	Akinator.Game();
	printf("JUST DO IT\n");
	Akinator.Game();
	//Akinat.Root->string = question;
	//AddList(Akinator.Root, question, answer);
}