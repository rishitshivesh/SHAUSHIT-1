	#ifndef MENU_CPP
	#define MENU_CPP

	#include "menu.h"
	#include <string.h>
	#include <stdio.h>
    #include <conio.h>


	Menu::Menu(int x,int y,char *name,int allign,int l,int b)
	{
		Left=x;
		Top=y;
		Width=l;
		Height=b;
		ID = ++NumberOfMenus;
		Click = false;
		Allignment=allign; 
		Items = -1;
		strcpy(Caption,name);
	}
    void Menu::AddItem(char *name)
    {
       Items++;
       if(Allignment==HORIZONTAL) {
         pMenuButton[Items] = new Buttn(Left+(Width*Items)+2,Top,Width,Height,name,Items);
   		} 
   	   else if (Allignment==VERTICAL)
   	   {
   	   	pMenuButton[Items] = new Buttn(Left,Top+(Items*Height)+2,Width,Height,name,Items);
   	   }
    }
    
	void Menu::Draw()
	{
         if(Items == -1)return;
         else{
      	for(int i=0;i<=Items;i++)
      		pMenuButton[i]->Draw(YELLOW);
      }
	}
	void Menu::HideItems()
	{
	    if(Items == -1)return;
		int i=0;
		
		do {

			delete pMenuButton[i];

			i++;

		}while(i < Items);

	}


	void Menu::EnableClickHandler()
	{
		for (int i = 0; i < Items;i++)
		{
			pMenuButton[i]->EnableClickHandler();
		}

	}


  #endif MENU_CPP