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

void printStatus1(short x, short y, short Left, short Top, list2 *item) {
	char *s = (char *)malloc(255 * sizeof(char));
	nullStr(s, 255);
	strcpy_s(s, 255, "F3=Load");
	consoleSetColors(clBlack, clLightRed);
	consoleGotoXY(Left, Top);
	if (NULL != item) {
		printf("x:3%d y:%3d   %d.%s", x, y, item->geom->id, item->geom->name);
	} else {
		printf("x:3%d y:%3d   %s                                                                            ", x, y, s);
	}
	free(s);
}

int main(){
	setlocale(LC_ALL, ".1251");

	TRect *console = new TRect();
	console->setBounds(1, 1, consoleSizeY() - 2, consoleSizeX() - 2);
/*
	HANDLE hCons = GetStdHandle(STD_OUTPUT_HANDLE);
	PCONSOLE_SCREEN_BUFFER_INFOEX Info = (PCONSOLE_SCREEN_BUFFER_INFOEX)malloc(sizeof(CONSOLE_SCREEN_BUFFER_INFOEX));
	GetConsoleScreenBufferInfoEx(hCons, Info);
	Info->srWindow.Left   = 0;
	Info->srWindow.Top    = 0;
	Info->srWindow.Right  = consoleSizeX();
	Info->srWindow.Bottom = consoleSizeY();
	GetConsoleScreenBufferInfoEx(hCons, Info);
	free(Info);
*/
	TPoint *tank = new TPoint();
	tank->setX(console->getX() + console->getWidth() / 2);
	tank->setY(console->getY() + console->getHeight() / 2);
	tank->setTyp(ptTank);
	tank->setColor(clBlack);
	tank->setBgColor(clLightRed);

	TGeom *boom = NULL;

	list2 *map = list2_loadfromfile(NULL, "d:\\map3.txt");
	list2_sortby_y(map);
	list2_print(map);

	list2 *wasOnObject = NULL;
	int flagExit = 0;
	int keyPressed = 0;
	do {
		printStatus1(tank->getX(), tank->getY(), 0, 0, list2_findxy(map, tank->getX(), tank->getY()) );
		
		if (NULL != wasOnObject) {
			wasOnObject->geom->Print();
			wasOnObject = NULL;
		}

		tank->Print();

		consoleGotoXY( tank->getX(), tank->getY() );
		
		keyPressed = _getch();
		
		wasOnObject = list2_findxy(map, tank->getX(), tank->getY());
		if (NULL != boom) {
			delete boom;
			boom = NULL;
		}
		switch (keyPressed) {
		    case KEY_ESCAPE: {
				flagExit = 1;
				break;
			}
			case KEY_LEFT : { if(tank->getX() > console->getX()     ) tank->setX(tank->getX() - 1); break; }
			case KEY_RIGHT: { if(tank->getX() < console->getWidth() ) tank->setX(tank->getX() + 1); break; }
			case KEY_UP   : { if(tank->getY() > console->getY()     ) tank->setY(tank->getY() - 1); break; }
			case KEY_DOWN : { if(tank->getY() < console->getHeight()) tank->setY(tank->getY() + 1); break; }
			case KEY_F1   : {
				boom = new TCircle();
				boom->setBgColor(clLightMagenta);
				boom->setColor(clBlack);
				boom->setX(tank->getX());
				boom->setY(tank->getY());
				TCircle *boom1 = (TCircle *)boom;
				boom1->setR( 20 );
				boom->Print();
				list2 *p = list2_gotofirst(map);
				while (NULL != p) {
					if (1 == boom->Contains(p->geom->getX(), p->geom->getY())) {
						list2 *ptemp = p->next;
						if (p == list2_gotofirst(map)) {
							map = list2_gotolast(map);
						}
						if (p == list2_gotolast(map)) {
							map = list2_gotofirst(map);
						}
						if (1 == list2_count(map)) {
							map = NULL;
						}
						if (p == wasOnObject) {
							wasOnObject = NULL;
						}
						list2_del(p);
						p = ptemp;
					} else {
						p = p->next;
					}
				}
				break;
			}
			case KEY_F2: {
				boom = new TRect();
				boom->setBgColor(clLightMagenta);
				boom->setColor(clBlack);
				TRect *boom1 = (TRect *)boom;
				boom1->setBounds(tank->getX() - 30, tank->getY() - 20, 40, 60);
				boom->Print();
				list2 *p = list2_gotofirst(map);
				while (NULL != p) {
					if (1 == boom->Contains(p->geom->getX(), p->geom->getY())) {
						list2 *ptemp = p->next;
						if (p == list2_gotofirst(map)) {
							map = list2_gotolast(map);
						}
						if (p == list2_gotolast(map)) {
							map = list2_gotofirst(map);
						}
						if (1 == list2_count(map)) {
							map = NULL;
						}
						if (p == wasOnObject) {
							wasOnObject = NULL;
						}
						list2_del(p);
						p = ptemp;
					}
					else {
						p = p->next;
					}
				}
				break;
			}
		}
	} while (0 == flagExit);

	delete tank;
	//delete console;

	consoleSetColors(clWhite, clBlack);
	return 0;// gg Dortmund
}