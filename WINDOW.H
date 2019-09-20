  	#ifndef __WINDOW_H
	#define __WINDOW_H
	
	#ifndef __GUI_H
	#include "gui.h"
	#endif //__GUI_H

	
	
  class Window
  {

	private:
	
	int X,Y,Width,Height;
	char Caption[50];
	Buttn *CloseBtn;
	public:
	
	Window(int left, int top, int width, int height, char caption[]);
	void Draw(int color);
	void EnableClickHandler();	
  }; 	
      
  #endif __WINDOW_H  			


















	

 
