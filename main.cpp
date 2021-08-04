
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <locale>
#include <Windows.h>

#ifndef TREE_H_
#define TREE_H_
#include "Tree.h"
#endif

#ifndef ERRORS_H
#define ERRORS_H
#include "Errors.h"
#endif

int main()
{
	//setlocale(LC_ALL, "Russian");
	//SetConsoleCP(1251);
	//SetConsoleOutputCP(1251);
	//system("chcp 1251");

	//printf("Всё на русском\n");

	class Tree Akinator;
	Akinator.LoadBase();
	Akinator.Game();

	return 0;
}