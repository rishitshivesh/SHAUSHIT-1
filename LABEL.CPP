
/*================================================================
                                                               
                          LABEL.CPP                                   
                                                                 
                     GUI for Turbo C++ 3.0                      
		                                                  
                       Label Support
		                                                  
                                                                 
	                                                           
		 Programmer           : Manish Kumar
         Date                 : 22/10/2018
         WEBSITE  : justdocodings.blogspot.com
         Facebook : www.facebook.com/justdocodings
         Twitter  : www.twitter.com/justdocodings

         Check Out other programmes at https://justdocodings.blogspot.com

         Software Details
        ====================
        Developed in   : C++
        Compiler used  : TC++ 3.0
        OS             : Window 98,2000,XP,
		                 Vista,Windows7(only safemode)

        Licence   : Protected (Please give the credit of programming to author.)     
                                                                
		 Copyright (c) 2018 by MANISH KUMAR               
		 All Rights Reserved                              
                                                                
			                                          
                                                                
================================================================*/

	  
	#ifndef __LABEL_CPP
	#define __LABEL_CPP

	#include "label.h"
	


	Label::Label(int left, int top, int width, int height, char caption[], int Align, int bgcolor = LIGHTGRAY, int fgcolor = BLACK, int Id = 0)
	{
		Left = left;
		Top = top;
		Width = width;
		Height = height;
		strcpy(Caption,caption);
		Bgcolor = bgcolor;
		Fgcolor = fgcolor;
		State = false;
		Click = false;
		Alignment = Align;
		ID = Id;
		
	}
	void Label::Draw()
	{
	
		setfillstyle(SOLID_FILL,Bgcolor);
		bar(Left,Top,Left+Width,Top+Height);

		setcolor(Fgcolor);

		settextjustify(Alignment,TOP_TEXT);
		settextstyle(SMALL_FONT,0,0);
		if(Alignment==LEFT_TEXT)
			outtextxy(Left+2,Top+1+((Height/2)-(textheight(Caption)/2)),Caption);
		else
			if(Alignment==RIGHT_TEXT)
				outtextxy(Left+Width-2,Top+1+((Height/2)-(textheight(Caption)/2)),Caption);
		else
			outtextxy(Left+(Width/2),Top+1+((Height/2)-(textheight(Caption)/2)),Caption);
		
		settextstyle(0,0,0);
	
	}
	
	void Label::EnableClickHandler(int bgcolor1 = LIGHTGRAY,int fgcolor1 = BLACK, int bgcolor2 = LIGHTGRAY, int fgcolor2 = BLACK)
	{

		
	
		if(Click)
		{
			LabelId = 0;
			Click = false;
			return;
		}
		

		if(mouse.MouseInside(Left,Top,Left+Width,Top+Height)==1)
		{
			if(!State)
			{

		   Bgcolor = bgcolor1;
		   Fgcolor = fgcolor1;
		   State = true;
		   mouse.HideMouse();
		   Draw();
		   mouse.ShowMouse();
		   
		   }


			if(mouse.GetButton() == MOUSE_LBUTTON)
			{
				btnStatus = LABEL_BUTTON_STATUS_DOWN;
			}

			else if(btnStatus == LABEL_BUTTON_STATUS_DOWN && mouse.GetButton() == MOUSE_NORMAL) 
			{
				
				LabelId = ID;
				btnStatus = LABEL_BUTTON_STATUS_NORMAL;
				Click = true;
				
			}



		}
		else
		{
		     if(!State)
			return;
		     Bgcolor = bgcolor2;
		     Fgcolor = fgcolor2;
		      State = false;
		      mouse.HideMouse();
		      Draw();
		      mouse.ShowMouse();
		}

	}
	
	
	void Label::SetText(char text[])
	{
		
		strcpy(Caption,text);
		Draw();
		
	}

	char *Label::GetText()
	{
		return Caption;
	}
	
	void Label::Clear()
	{
		strcpy(Caption,"");
		Draw();
	}
   	
      
  #endif //__LABEL_CPP  			


















	

 
