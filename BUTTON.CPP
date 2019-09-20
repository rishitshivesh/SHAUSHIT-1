#ifndef BUTTON_CPP
#define BUTTON_CPP 
	
#include "button.h"


Buttn::Buttn(int left, int top, int width, int height, char caption[], int Id)
{

		Left = left;
		Top = top;
		Width = width;
		Height = height;
		strcpy(Caption,caption);
		ID = Id;
		//btnStatus = BUTTON_STATUS_NORMAL;
		State = false;
		IsClicked=false;
}				
    void Buttn::Highlight(char a)
    {
    int m = Left,n=Top;
    char w[70] = " ";
    for(int i = 0;i<Width;i++)
        w[i] = a;
    textcolor(RED);
    gotoxy(m,n+Height+1);
    cprintf(w);
    textcolor(WHITE);
    }

   void Buttn::Draw(int color)
   {
	textcolor(color);
    int n = Top;
    int a = Width-1;
    gotoxy(Left,Top);
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
        gotoxy(Left,n);
        cprintf(h);
        n++;
    }
    gotoxy(Left,n);
    cprintf(w);
    gotoxy(Left+2,Top+(Height%2));
    textcolor(WHITE);
    cprintf(Caption);
   }

void Buttn::EnableClickHandler()
{
  //  if(navigate.get_status()==ID)
  //  	 {
  //  	 	Highlight('*');
	 // }
	if(IsClicked)
	{
		ButtonId = ID;
		//btnStatus = BUTTON_STATUS_NORMAL;
		State = true;
	}
}

   #endif BUTTON_CPP
   
		


















	

 
