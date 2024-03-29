#include "pch.h"
#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <locale.h>
#include "../ClassInCpp/consts.h"
#include "../ClassInCpp/strutils.h"
#include "../ClassInCpp/consoleroutine.h"
#include "../ClassInCpp/tgeom.h"
#include "../ClassInCpp/tpoint.h"
#include "../ClassInCpp/trect.h"
#include "../ClassInCpp/tcircle.h"
#include "../ClassInCpp/list2link.h"

int main() {
	setlocale(LC_ALL, ".1251");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	list2 *map = list2_loadfromfile(NULL, "d:\\map3.txt");

//	consoleSetColors(clWhite, clBlack);
//	printf("--------------- ORIGINAL LIST: \n");
//	list2_printtext(map);

	/*
	list2_sortby_name(map);
	consoleSetColors(clWhite, clBlack);
	printf("--------------- LIST SORTED BY NAME: \n");
	list2_printtext(map);
	*/
	
	char *searchStr = (char *)malloc(defaultNameLength * sizeof(char));
	do {
		nullStr(searchStr, defaultNameLength);
		consoleSetColors(clWhite, clBlack);
		printf("--------------------------------------------------- \nPlease, enter a searching name or type EXIT:");
		scanf_s("%s", searchStr, defaultNameLength);
		strtoupper(searchStr);
		printf("----------- FOUNDED ITEMS ----------\n");
		
		list2_search_nametype(map, searchStr, ptBank);
	
	} while (strcmp("EXIT", searchStr) != 0);
	free(searchStr);


	return 0;
}