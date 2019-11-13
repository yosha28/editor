#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <iostream>
#include "consts.h"
#include "strutils.h"
#include "tgeom.h"
#include "tpoint.h"
#include "trect.h"
#include "tcircle.h"
#include "list2link.h"

class GameEngine;
typedef void(*funcOnKeyDown)(GameEngine *Sender);
typedef void(*funcOnEscape)(GameEngine *Sender,int _running);
class GameEngine {
	
private:
	int Running;

	
	 
public:
	TGeom *boom;
	TRect *Console;
	TPoint *Tank;
	list2 *Map;
	GameEngine();
	~GameEngine();
	void Run();
	int  getRunning();
	void setRunning(const int value);
	funcOnKeyDown onRunBefore;
	funcOnKeyDown onProcessKeyBefore;
	funcOnKeyDown onProcessKeyAfter;
	funcOnKeyDown onKeyLeft;
	funcOnKeyDown onKeyRight;
	funcOnKeyDown onKeyDown;
	funcOnKeyDown onKeyUp;
	funcOnKeyDown onKeyF1;
	funcOnKeyDown onKeyF2;
	funcOnKeyDown onKeyF3;
	funcOnKeyDown onKeyF4;
	funcOnKeyDown onKeyF5;
	funcOnKeyDown onKeyF6;
	funcOnKeyDown onKeyDelete;
	funcOnEscape onKeyEscape;

protected:
	virtual void doRunBefore();
	virtual void doRunAfter();
	virtual void doProcessKeyBefore();
	virtual void doProcessKeyAfter();
	virtual void doProcessKey(int pressedKey);
	virtual void doKeyEscape();
	virtual void doKeyDelete();
	virtual void doKeyLeft();
	virtual void doKeyRight();
	virtual void doKeyUp();
	virtual void doKeyDown();
	virtual void doKeyF1();
	virtual void doKeyF2();
	virtual void doKeyF3();
	virtual void doKeyF4();
	virtual void doKeyF5();
	virtual void doKeyF6();
	virtual void doKeyF7();
	virtual void doKeyF8();
	virtual void doKeyF9();
	virtual void doKeyF10();
	virtual void doKeyF11();
	virtual void doKeyF12();
};

#endif