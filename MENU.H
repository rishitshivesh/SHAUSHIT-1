    #ifndef __MENU_H
	#define __MENU_H
	
	#ifndef __GUI_H
	#include "gui.h"
	#endif //__GUI_H

    #include "global.h"

	enum MENU_BUTTON_STATUS
	{
		 MENU_BUTTON_STATUS_NORMAL,
		 MENU_BUTTON_STATUS_DOWN
	};


  class Menu
  {

	private:

	int Left,Top,Width,Height,Items,MenuItemWidth,Allignment;
	int ID;
	long int totalWidth,maxWidth;
	unsigned char Caption[250];
	char MenuText[50];
	char cap[50];
	bool Click;
	bool State;
	MENU_BUTTON_STATUS btnStatus;
	Buttn *pMenuButton[30];
	// Button *pMenuButton = MenuButton;


	
	int _i, _j;
	
	

	
	public:
	
	Menu(int x,int y,char *name,int allign,int l=16,int b=1);
	void AddItem(char *name);
	void HideItems();
	void Draw();
	void EnableClickHandler();
	
  }; 	
      
  #endif __MENU_H  