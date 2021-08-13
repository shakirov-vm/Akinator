
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <locale>
#include <Windows.h>

#ifndef TREE_H_
#define TREE_H_
#include "Tree/Tree.h"
#endif

#ifndef ADDITIONAL_H
#define ADDITIONAL_H
#include "Additional.h"
#endif

int main()
{
	setlocale(LC_ALL, "");
	//SetConsoleCP(1251);
	//SetConsoleOutputCP(1251);
	//system("chcp 1251");

	//printf("Всё на русском\n");

	class Tree Akinator;
	Akinator.LoadBase();
	Akinator.Game();

	return 0;
}