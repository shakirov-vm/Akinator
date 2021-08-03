
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <locale>
#include <Windows.h>

#ifndef TREE_H_
#define TREE_H_
#include "Tree.h"
#endif

int main() ///          Enter code is cicled!!!!!!!!!!!!!!!!!!!!!!!! (In Load base)!!!!!!!
{
	setlocale(LC_ALL, "Russian");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	system("chcp 1251");

	printf("Всё на русском\n");

	class Tree Akinator;

	printf("You need load base. Enter name\n");
	char* answer = (char*)calloc(MAX_NAME_SIZE, sizeof(char)); 
	if (answer == nullptr) {
		printf("Your answer can't be read, because memory can't be allocated\n");
		return 1;
	}
	std::cin.getline(answer, MAX_NAME_SIZE, '\n');
	printf(">>> %s\n", answer);
	Akinator.LoadBase(answer);

	Akinator.Game();

	free(answer);

	return 0;
}