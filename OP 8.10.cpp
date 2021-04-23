// OP 8.10.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <Windows.h>

#define grey 8
#define cyan 11
#define red 12
#define yellow 14
#define white 15


using std::cout;
using std::cin;

char mas[3][3];
unsigned short color;

HANDLE nConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	/*  --2---6---10--
	  0 -------------
	  1 - x - x - x - 
	  2 - - - - - - -
	  3 - x - x - x -
	  4 - - - - - - -
	  5 - x - x - x -
	  6 ------------- */ 

COORD player_coord(short C) {
	switch (C) {
	case 1:
		return { 2, 1 };
		break;
	case 2:
		return { 6, 1 };
		break;
	case 3:
		return { 10, 1 };
		break;
	case 4:
		return { 2, 3 };
		break;
	case 5:
		return { 6, 3 };
		break;
	case 6:
		return { 10, 3 };
		break;
	case 7:
		return { 2, 5 };
		break;
	case 8:
		return { 6, 5 };
		break;
	case 9:
		return { 10, 5 };
		break;
	default:
		return { 0, 8 };
		break;
	}
}

short rand_coord_x(short x) {
	switch (x) {
	case 0:
		x = 2;
		break;
	case 1:
		x = 6;
		break;
	case 2:
		x = 10;
		break;
	}
	return x;
}

short rand_coord_y(short y) {
	switch (y) {
	case 0:
		y = 1;
		break;
	case 1:
		y = 3;
		break;
	case 2:
		y = 5;
		break;
	}
	return y;
}


void paint(COORD a, COORD b, COORD c, char simbol) {
	if (simbol == 'x') {
		color = cyan;
		SetConsoleTextAttribute(nConsole, color);
	}
	else {
		color = red;
		SetConsoleTextAttribute(nConsole, color);
	}
	SetConsoleCursorPosition(nConsole, a);
	printf("%c", simbol);
	SetConsoleCursorPosition(nConsole, b);
	printf("%c", simbol);
	SetConsoleCursorPosition(nConsole, c);
	printf("%c", simbol);

	SetConsoleTextAttribute(nConsole, white);
	return;
}

bool check( short step ) {
	if ((mas[0][0] != '_') && ((mas[0][0] == mas[0][1]) && (mas[0][1] == mas[0][2]))) { // case 1
		paint({ 2, 1 }, { 6, 1 }, { 10, 1 }, mas[0][0]);
		return true;
	}
	if ((mas[1][0] != '_') && ((mas[1][0] == mas[1][1]) && (mas[1][1] == mas[1][2]))) { // case 2
		paint({ 2, 3 }, { 6, 3 }, { 10, 3 }, mas[1][0]);
		return true;
	}
	if ((mas[2][0] != '_') && ((mas[2][0] == mas[2][1]) && (mas[2][1] == mas[2][2]))) { // case 3
		paint({ 2, 5 }, { 6, 5 }, { 10, 5 }, mas[2][0]);
		return true;
	}
	if ((mas[0][0] != '_') && ((mas[0][0] == mas[1][0]) && (mas[1][0] == mas[2][0]))) { //case 4
		paint({ 2, 1 }, { 2, 3 }, { 2, 5 }, mas[0][0]);
		return true;
	}
	if ((mas[0][1] != '_') && ((mas[0][1] == mas[1][1]) && (mas[1][1] == mas[2][1]))) { //case 5
		paint({ 6, 1 }, { 6, 3 }, { 6, 5 }, mas[0][1]);
		return true;
	}
	if ((mas[0][2] != '_') && ((mas[0][2] == mas[1][2]) && (mas[1][2] == mas[2][2]))) { //case 6
		paint({ 10, 1 }, { 10, 3 }, { 10, 5 }, mas[0][2]);
		return true;
	}
	if ((mas[0][0] != '_') && ((mas[0][0] == mas[1][1]) && (mas[1][1] == mas[2][2]))) { // case 7
		paint({ 2, 1 }, { 6, 3 }, { 10, 5 }, mas[0][0]);
		return true;
	}
	if ((mas[0][2] != '_') && ((mas[0][2] == mas[1][1]) && (mas[1][1] == mas[2][0]))) { // case 8
		paint({ 10, 1 }, { 6, 3 }, { 2, 5 }, mas[1][1]);
		return true;
	}
	if (step == 9) {
		color = yellow;
		return true;
	}
	else {
		return false;
	}
}


int main() ////////////// MAIN
{
	long ltime = time(0);
	int stime = (unsigned int)ltime / 2;
	srand(stime);
	COORD coord;
	short x = 0, y = 0, C;
	short xr, yr;
	unsigned short step = 0;

	puts("-------------\t\tTIC-TAC-TOE");
	puts("|   |   |   |\t\t");
	puts("| - - - - - |\t\t| 0 - to be second");
	puts("|   |   |   |\t\t| 0(x2) - skip");
	puts("| - - - - - |");
	puts("|   |   |   |\t\t| letter for exit");
	puts("-------------");

	color = grey;
	SetConsoleTextAttribute(nConsole, color);
	for (int i = 1; i <= 9; i++) {
		coord = player_coord(i);
		SetConsoleCursorPosition(nConsole, coord);
		printf("%i", i);
	}
	color = white;
	SetConsoleTextAttribute(nConsole, color);

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			mas[i][j] = '_';
		}
	}

	coord = { 0, 8 };
	SetConsoleCursorPosition(nConsole, coord);
	////// GAME
	while (cin >> C) {
		// player step
		do {
			coord = { 0, 8 };
			SetConsoleCursorPosition(nConsole, coord);
			printf("   ");
			SetConsoleCursorPosition(nConsole, coord);
			switch (C) {
			case 1:
				x = 0; y = 0;
				break;
			case 2:
				x = 0; y = 1;
				break;
			case 3:
				x = 0; y = 2;
				break;
			case 4:
				x = 1; y = 0;
				break;
			case 5:
				x = 1; y = 1;
				break;
			case 6:
				x = 1; y = 2;
				break;
			case 7:
				x = 2; y = 0;
				break;
			case 8:
				x = 2; y = 1;
				break;
			case 9:
				x = 2; y = 2;
				break;
			default:
				break;
			}
			if (mas[x][y] != '_') {
				if (cin >> C) {
				}
				else {
					break;
				}
			}
			if (C == 0) {
				break;
			}
		} while (mas[x][y] != '_');

		if (C != 0) {
		coord = player_coord(C);
		SetConsoleCursorPosition(nConsole, coord);
		printf("x");
		mas[x][y] = 'x';
		step++;
		}
		else {}

		if (check(step)) {
			break;
		}

		// rand step
		if (step != 9) {
			do {
				xr = rand() % 3;
				yr = rand() % 3;
			} while (mas[yr][xr] != '_');

			x = rand_coord_x(xr);
			y = rand_coord_y(yr);
			coord = { x, y };
			SetConsoleCursorPosition(nConsole, coord);
			printf("o");
			mas[yr][xr] = 'o';
			step++;
		}
		coord = { 0, 8 };
		SetConsoleCursorPosition(nConsole, coord);
		printf("   ");
		SetConsoleCursorPosition(nConsole, coord);

		if (check(step)) {
			break;
		}
		
	} 
	//////

	coord = { 0, 8 };
	SetConsoleCursorPosition(nConsole, coord);
	printf("-----------------------\n");
	SetConsoleTextAttribute(nConsole, color);
	switch (color) {
	case cyan:
		printf("\tW I N");
		break;
	case red:
		printf("\tL O S E");
		break;
	case yellow:
		printf("\tD R A W");
		break;
	default:
		printf("\tFINALE");
		break;
	}
	SetConsoleTextAttribute(nConsole, white);
	printf("\n-----------------------\n");
	return 0;
}