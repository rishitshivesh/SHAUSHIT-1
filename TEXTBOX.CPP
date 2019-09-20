
/*================================================================
                                                               
                          TEXTBOX.CPP                                   
                                                                 
                     GUI for turbo C++ 3.0                      
		                                                  
                       Textbox Support
		                                                  
                                                                 
	                                                           
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


	  
	#ifndef TEXTBOX_CPP
	#define TEXTBOX_CPP 
	
	#include "textbox.h"
	#include <graphics.h>
	#include <string.h>
	#include <conio.h>
	#include <ctype.h>


  
      
    TextBox::TextBox(int left, int top, int width, int height, char caption[],int Align, int Id)
    {
	Left = left;
	Top = top;
	Width = width;
	Height = height;
	strcpy(Caption,caption);
	ID = Id;
	Alignment = Align;
	bReadOnly = false;
    }				


    void TextBox::Draw()
   {
		setfillstyle(SOLID_FILL,WHITE);
		bar(Left,Top,Left+Width,Top+Height);

		setcolor(DARKGRAY);
		rectangle(Left,Top,Left+Width,Top+Height);

		setcolor(BLACK);

		settextjustify(Alignment,TOP_TEXT);
		if(Alignment==LEFT_TEXT)
			outtextxy(Left+2,Top+1+((Height/2)-(textheight(Caption)/2)),Caption);
		else
			if(Alignment==RIGHT_TEXT)
				outtextxy(Left+Width-2,Top+1+((Height/2)-(textheight(Caption)/2)),Caption);
		else
			outtextxy(Left+(Width/2),Top+1+((Height/2)-(textheight(Caption)/2)),Caption);
			
	
   }

   void TextBox::MouseDown()
   {
		
		if(bReadOnly) return; 

		int ch;
		int len=strlen(Caption),curpos,curx;
		

		mouse.HideMouse();
		curpos=len;
		do{
			curx=Left+textwidth(Caption)+1;

			if(!kbhit())
			{
				setwritemode(XOR_PUT);
				setcolor(WHITE);
				line(curx,Top+2,curx,Top+Height-2);
				do{
					line(curx,Top+2,curx,Top+Height-2);
					delay(100);
				  }while(!kbhit());
					setwritemode(COPY_PUT);
			}


			ch=getch();
			if(ch==0) ch=getch();
			switch (ch)
			{
				case 8: 
					if(len>0)
					{
						Caption[curpos-1]=0;
						curpos--;
						len--;
					}
			    break;
			}
			if(isprint(ch))
			{
				Caption[curpos]=ch;
				Caption[curpos+1]=0;
				if(Left+textwidth(Caption)>Left+Width)
				{
					Caption[curpos]=0;
					Draw();
					break;
				}
				else
				{
					curpos++;
					len++;
				}
			}

				Draw();
		}while(ch!=13 && ch!=27);
		mouse.ShowMouse();

		}
		
	void TextBox::SetReadOnly(bool ReadOnly)
	{
		bReadOnly = ReadOnly;
	}
	
	void TextBox::SetText(char text[])
	{
		if (Left + textwidth(Caption) <= Left + Width - textwidth(" "))
		{
			strcat(Caption,text);
			Draw();
		}
	}

	char *TextBox::GetText()
	{
		return Caption;
	}
	
	void TextBox::Clear()
	{
		strcpy(Caption,"");
		Draw();
	}

   void TextBox::EnableClickHandler()
   {
	if(IsComboClick || IsMenuClick)return;
		
		if(mouse.MouseInside(Left,Top,Left+Width,Top+Height) == 1)
		{

			if(mouse.GetButton() == MOUSE_LBUTTON)
			{
			MouseDown();
			TextBoxId = ID;
			}
		}
 
   }
   
   #endif //TEXTBOX_CPP
   
		


















	

 
