#include "../menu.h"
#include <iostream>
#include <windows.h>
#include <locale.h>
#include "../Tree.h"
#include <limits>
#include <stdlib.h>


int main()
{ 
	FontsSettings(0, 16);
	console = GetConsoleWindow();
	SetWindowPos(console, NULL, PosConsole.x, PosConsole.y, sizeConsole.x, sizeConsole.y, NULL);
	SetWindowLong(console, GWL_STYLE, WS_BORDER);
	ShowWindow(console, SW_SHOW);
	ExConsole();
	loading();		
				
	pRoot = new Tree_Item();
	pRoot->inf = 1;

	while (1) {
		field A[5] = { "ADD new child vertex", "Delete a vertex", "Show a tree", "Search a vertex", "Exit" };
		bool back = 0;
		int choice = menu(A, 5);

		if (choice == 0) {
			int t1 = stoi(Get_el_console("Enter a parent vertex:"));
			int inf = stoi(Get_el_console("Enter a new vertex:"));
			int res = Push(t1, inf);
			while (!back) {
				field ADD[2] = { "The vertex was added successfully!", "Back" };
				if (res == 0) {
					ADD[0].name = "The parent vertex not found!";
				}
				if (menu(ADD, 2) == 1) back = 1;
			}			
		}

		if (choice == 1) {
			int inf = stoi(Get_el_console("Enter a inf of vertex:"));
			int res = Delete(inf);
			field DEL[2] = { "The vertex was deleted successfully!", "Back" };
			if (res == 0) DEL[0].name = "The vertex not found!";
			while (!back) {
				if (menu(DEL, 2) == 1) back = 1;
			}
		}

		else if (choice == 2) {
			std::string str;
			while (!back) {
				field DEL[3] = { "The current tree:", "Back", Show()};
				if (menu(DEL, 3) == 1) back = 1;
			}
		}

		else if (choice == 3) {
			int inf = stoi(Get_el_console("Enter a inf of vertex:"));
			int res = Search(inf);
			field SEARCH[2] = { "The vertex has parent - || " + std::to_string(res) + " || ", "Back" };
			if (res == -1) SEARCH[0].name = "The vertex has not parent or not found!";
			while (!back) {
				if (menu(SEARCH, 2) == 1) back = 1;
			}
		}

		else if (choice == 4) {
			exit(0);
		}
	}
		
	
	return 0;
}

