#ifndef __BUTTON_H
#define __BUTTON_H
	
#ifndef __GUI_H
#include "gui.h"
#endif  // __GUI_H

#include "global.h"
#include <string.h>
#include <conio.h>
#include <stdlib.h>

class Buttn
{
  private:
	int Left,Top,Width,Height,ID;
	char Caption[50];
	bool State;

  public:
	Buttn(int left, int top, int width, int height, char caption[], int Id=0);
	void Highlight(char a);
	void Draw(int color);
	void EnableClickHandler();		
};	   
#endif __BUTTON_H  			


















	

 
