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
#include "../ClassInCpp/gameengine.h"

void gameOnKeyLeft(GameEngine *Sender)
{
	if ((Sender->Tank->getX() >Sender->Console->getX()) && (1 != list2_contains(Sender->Map, Sender->Tank->getX() - 1, Sender->Tank->getY())))
	{
		Sender->Tank->setX(Sender->Tank->getX() - 1);
	}
}

void gameOnKeyRight(GameEngine *Sender)
{
	if ((Sender->Tank->getX() < Sender->Console->getWidth()) && (1 != list2_contains(Sender->Map, Sender->Tank->getX() + 1, Sender->Tank->getY())))
	{
		Sender->Tank->setX(Sender->Tank->getX() + 1);
	}
}

void gameOnKeyUp(GameEngine *Sender)
{
	if ((Sender->Tank->getY() >Sender->Console->getY()) && (1 != list2_contains(Sender->Map, Sender->Tank->getX(), Sender->Tank->getY() - 1))) {
		Sender->Tank->setY(Sender->Tank->getY() - 1);
	}
}

void gameOnKeyDown(GameEngine *Sender)
{
	if( (Sender->Tank->getY() < Sender->Console->getHeight()) && (1 != list2_contains(Sender->Map, Sender->Tank->getX(), Sender->Tank->getY() + 1)))
	{
		Sender->Tank->setY(Sender->Tank->getY() + 1);
	}
}

void gameOnKeyF1(GameEngine *Sender)
{
	Sender->boom = new TCircle();
	Sender->boom->setBgColor(clLightMagenta);
	Sender->boom->setColor(clBlack);
	Sender->boom->setX(Sender->Tank->getX());
	Sender->boom->setY(Sender->Tank->getY());
	TCircle *boom1 = (TCircle *)Sender->boom;
	boom1->setR(20);
	boom1->PrintSlowBoom();
	list2 *p = list2_gotofirst(Sender->Map);
	while (NULL != p) {
		if (1 == Sender->boom->Contains(p->geom->getX(), p->geom->getY())) {
			list2 *ptemp = p->next;
			if (p == list2_gotofirst(Sender->Map)) {
				Sender->Map = list2_gotolast(Sender->Map);
			}
			if (p == list2_gotolast(Sender->Map)) {
				Sender->Map = list2_gotofirst(Sender->Map);
			}
			if (1 == list2_count(Sender->Map)) {
				Sender->Map = NULL;
			}
			/*if (p == wasOnObject) {
				wasOnObject = NULL;
			}*/
			list2_del(p);
			p = ptemp;
		}
		else {
			p = p->next;
		}
	}
}

void gameOnKeyF2(GameEngine *Sender)
{
	Sender->boom = new TRect();
	Sender->boom->setBgColor(clLightMagenta);
	Sender->boom->setColor(clBlack);
	TRect *boom1 = (TRect *)Sender->boom;
	boom1->setBounds(Sender->Tank->getX() - 30, Sender->Tank->getY() - 20, 40, 60);
	Sender->boom->Print();
	list2 *p = list2_gotofirst(Sender->Map);
	while (NULL != p) {
		if (1 == Sender->boom->Contains(p->geom->getX(), p->geom->getY())) {
			list2 *ptemp = p->next;
			if (p == list2_gotofirst(Sender->Map)) {
				Sender->Map = list2_gotolast(Sender->Map);
			}
			if (p == list2_gotolast(Sender->Map)) {
				Sender->Map = list2_gotofirst(Sender->Map);
			}
			if (1 == list2_count(Sender->Map)) {
				Sender->Map = NULL;
			}
			//if (p == wasOnObject) {
			//	wasOnObject = NULL;
			//}
			list2_del(p);
			p = ptemp;
		}
		else {
			p = p->next;
		}
	}



}

//void gameOnRunBefore(GameEngine *Sender) {
//	list2_print(Sender->Map);
//}

void gameOnProcessKeyBefore(GameEngine *Sender) {

	Sender->Tank->Print();
	consoleGotoXY(Sender->Tank->getX(), Sender->Tank->getY());

	if (NULL != Sender->boom) {
		delete Sender->boom;
		Sender->boom = NULL;
	}
}

void editorOnKeyLeft(GameEngine *Sender)
{
	if (Sender->Tank->getX() > Sender->Console->getX()) {
		Sender->Tank->setX(Sender->Tank->getX() - 1);
	}
}

void editorOnKeyRight(GameEngine *Sender)
{
	if (Sender->Tank->getX() < Sender->Console->getWidth()) {
		Sender->Tank->setX(Sender->Tank->getX() + 1);
	}
}

void editorOnKeyDown(GameEngine *Sender)
{
	if (Sender->Tank->getY() < Sender->Console->getHeight()) {
		Sender->Tank->setY(Sender->Tank->getY() + 1);
	}
}

void editorOnKeyUp(GameEngine *Sender)
{
	if (Sender->Tank->getY() > Sender->Console->getY()) {
		Sender->Tank->setY(Sender->Tank->getY() - 1);
	}
}

void editorOnKeyF2(GameEngine *Sender)
{
	if (NULL != Sender->Map) {
		list2_savetofile(Sender->Map, "d:\\map.txt");
	}
}

void editorOnKeyF3(GameEngine *Sender)
{
	if (0 == list2_contains(Sender->Map, Sender->Tank->getX(), Sender->Tank->getY())) {
		Sender->Map = map_add_TPoint(Sender->Map, Sender->Tank->getX(), Sender->Tank->getY(), ptBank, clBlack, clLightGreen);
	}
}

void editorOnKeyF4(GameEngine *Sender)
{
	if (0 == list2_contains(Sender->Map, Sender->Tank->getX(), Sender->Tank->getY())) {
		Sender->Map = map_add_TPoint(Sender->Map, Sender->Tank->getX(), Sender->Tank->getY(), ptHouse, clWhite, clBrown);
	}
}

void editorOnKeyF5(GameEngine *Sender)
{
	if (0 == list2_contains(Sender->Map, Sender->Tank->getX(), Sender->Tank->getY())) {
		Sender->Map = map_add_TPoint(Sender->Map, Sender->Tank->getX(), Sender->Tank->getY(), ptCafe, clWhite, clLightRed);
	}
}

void editorOnKeyF6(GameEngine *Sender)
{
	if (0 == list2_contains(Sender->Map, Sender->Tank->getX(), Sender->Tank->getY())) {
		Sender->Map = map_add_TPoint(Sender->Map, Sender->Tank->getX(), Sender->Tank->getY(), ptShop, clBlack, clLightCyan);
	}
}

void editorOnKeyDelete(GameEngine *Sender)
{
	if (NULL != Sender->Map) {
		list2 *p = list2_gotofirst(Sender->Map);
		while (NULL != p) {
			if (1 == p->geom->Contains(Sender->Tank->getX(), Sender->Tank->getY())) {
				list2 *ptemp = p->next;
				if (p == list2_gotofirst(Sender->Map)) {
					Sender->Map = list2_gotolast(Sender->Map);
				}
				if (p == list2_gotolast(Sender->Map)) {
					Sender->Map = list2_gotofirst(Sender->Map);
				}
				if (1 == list2_count(Sender->Map)) {
					Sender->Map = NULL;
				}
				list2_del(p);
				p = ptemp;
			}
			else {
				p = p->next;
			}
		}
	}
}


void editorOnProcessKeyBefore(GameEngine *Sender) {

	Sender->Tank->Print();
	consoleGotoXY(Sender->Tank->getX(), Sender->Tank->getY());

}

void editorOnProcessKeyAfter(GameEngine *Sender) {
	list2_print(Sender->Map);
}



//argc-количество аргументов переданных
int main(int argc, char *argv[]) {
	int editorMode = 0;
	char *param1 = (char*)malloc(MAX_PATH * sizeof(char));
	nullStr(param1, MAX_PATH);
	GameEngine *Game = new GameEngine();
	if (1 < argc)
	{
		strcpy_s(param1, MAX_PATH, argv[1]);

	}
	strtoupper(param1);

	if (0 == strcmp("EDITOR", param1))
	{
		Game->Tank->setTyp(ptPen);
		Game->onKeyLeft = &editorOnKeyLeft;
		Game->onKeyRight = &editorOnKeyRight;
		Game->onKeyDown = &editorOnKeyDown;
		Game->onKeyUp = &editorOnKeyUp;
		Game->onKeyF2 = &editorOnKeyF2;
		Game->onKeyF3 = &editorOnKeyF3;
		Game->onKeyF4 = &editorOnKeyF4;
		Game->onKeyF5 = &editorOnKeyF5;
		Game->onKeyF6 = &editorOnKeyF6;
		Game->onProcessKeyBefore = &editorOnProcessKeyBefore;
		Game->onKeyDelete = &editorOnKeyDelete;
		Game->onProcessKeyAfter = &editorOnProcessKeyAfter;
		//editorMode = 1;
	}
	else
	{
		Game->Tank->setTyp(ptTank);
		Game->Map = list2_loadfromfile(NULL, "D:\\Map3.txt");
		Game->onKeyLeft = &gameOnKeyLeft;
		Game->onKeyRight = &gameOnKeyRight;
		Game->onKeyDown = &gameOnKeyDown;
		Game->onKeyUp = &gameOnKeyUp;
		Game->onKeyF1 = &gameOnKeyF1;
		Game->onKeyF2 = &gameOnKeyF2;
		Game->onProcessKeyBefore = &gameOnProcessKeyBefore;
	}


	Game->Run();



	delete Game;

	return 0;
}