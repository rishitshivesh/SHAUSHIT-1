	#ifndef __WINDOW_CPP
	#define __WINDOW_CPP

	#include "window.h"
	#include <stdlib.h>
    #include <conio.h>

    #include "global.h"
	Window::Window(int left, int top, int width, int height, char caption[])
	{
		X = left;
		Y = top;
		Width = width;
		Height = height;
		WindowLeft=X;
		WindowTop=Y;
		WindowWidth=Width;
		strcpy(Caption,caption);
	}
	
void Window::Draw(int color)
{
	
	textcolor(color);
    int n = Y;
    int a = Width-1;
    gotoxy(X,Y);
    char w[70] = " ";
    char h[25] = " ";
    h[0] = char(179)    ;
    for(int i = 0;i<Width;i++)
    {
        w[i]=char(196);
        h[i+1] = ' ';
    }
    h[a] = char(179);
    cprintf(w);
    n++;
    for(int j = 0 ;j<Height;j++)
    {
        gotoxy(X,n);
        cprintf(h);
        n++;
    }
    gotoxy(X,n);
    cprintf(w);
    gotoxy(X+2,Y+(Height%2));
    textcolor(WHITE);
    cprintf(Caption);
		CloseBtn = new Buttn((X+Width)-TITLEBARHEIGHT,Y,TITLEBARHEIGHT, TITLEBARHEIGHT-2, "X", 9809);
		CloseBtn->Draw(RED);
}

void Window::EnableClickHandler()
{
		CloseBtn->EnableClickHandler();
		if (ButtonId == 9809)
		exit(0);
		
}
   	
      
  #endif __WINDOW_CPP  			


















	

 
