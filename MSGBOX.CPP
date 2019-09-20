
/*================================================================
                                                               
                          MSGBOX.CPP                                   
                                                                 
                     GUI for Turbo C++ 3.0                      
		                                                  
                       MessageBox Support
		                                                  
                                                                 
	                                                           
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


	  
	#ifndef __MSGBOX_CPP
	#define __MSGBOX_CPP

	#include "msgbox.h"
	#include <graphics.h>
	#include <stdlib.h>
	#include <stdio.h>
	#include <string.h>

	void MsgBox::CriticalIcon(int left, int top)
	{
		setcolor(RED);
		setfillstyle(SOLID_FILL,RED);
		fillellipse(left+(ICONWIDTH)/2,top+(ICONHEIGHT)/2,ICONWIDTH-5,ICONHEIGHT-5);
		settextstyle(0,0,2);
		setcolor(WHITE);
		outtextxy(left+(ICONWIDTH/2)-6,top+2+((ICONHEIGHT/2)-(textheight("X")/2)),"X");
		settextstyle(0,0,0);
	}
	void MsgBox::QuestionIcon(int left, int top)
	{
		int utr[]={left+(ICONWIDTH)/2-3,top+ICONWIDTH+ICONWIDTH/2-5,   left+(ICONWIDTH)/2+5,top+ICONWIDTH+ICONWIDTH/2+2,    left+(ICONWIDTH)/2+3,top+ICONWIDTH+ICONWIDTH/2-5};
		setcolor(WHITE);
		setfillstyle(SOLID_FILL,WHITE);
		fillellipse(left+(ICONWIDTH)/2,top+(ICONHEIGHT)/2,ICONWIDTH-5,ICONHEIGHT-5);
		fillpoly(3,utr);
		settextstyle(0,0,2);
		setcolor(BLUE);
		outtextxy(left+(ICONWIDTH/2)-5,top+2+((ICONHEIGHT/2)-(textheight("?")/2)),"?");
		settextstyle(0,0,0);
	}
	void MsgBox::ExclamationIcon(int left, int top)
	{
		setcolor(DARKGRAY);
		setfillstyle(SOLID_FILL,YELLOW);
		fillellipse(left+(ICONWIDTH)/2,top+(ICONHEIGHT)/2,ICONWIDTH-5,ICONHEIGHT-5);

		settextstyle(0,0,2);
		setcolor(BLACK);
		outtextxy(left+(ICONWIDTH/2)-5,top+2+((ICONHEIGHT/2)-(textheight("!")/2)),"!");
		settextstyle(0,0,0);

	}
	void MsgBox::InformationIcon(int left, int top)
	{
		int utr[]={left+(ICONWIDTH)/2-3,top+ICONWIDTH+ICONWIDTH/2-5,   left+(ICONWIDTH)/2+5,top+ICONWIDTH+ICONWIDTH/2+2,    left+(ICONWIDTH)/2+3,top+ICONWIDTH+ICONWIDTH/2-5};
		setcolor(WHITE);
		setfillstyle(SOLID_FILL,WHITE);
		fillellipse(left+(ICONWIDTH)/2,top+(ICONHEIGHT)/2,ICONWIDTH-5,ICONHEIGHT-5);
		fillpoly(3,utr);
		settextstyle(0,0,2);
		setcolor(BLUE);
		outtextxy(left+(ICONWIDTH/2)-7,top+2+((ICONHEIGHT/2)-(textheight("i")/2)),"i");
		settextstyle(0,0,0);
	}
	void MsgBox::AboutIcon(int left, int top)
	{

		setcolor(3);
		setfillstyle(SOLID_FILL,3);
		fillellipse(left+(ICONWIDTH)/2,top+(ICONHEIGHT)/2,ICONWIDTH-5,ICONHEIGHT-5);


		setcolor(15);
		setfillstyle(SOLID_FILL,15);
		circle(left+(ICONWIDTH)/2,top+(ICONHEIGHT)/2,ICONWIDTH-8);
		circle(left+(ICONWIDTH)/2,top+(ICONHEIGHT)/2,ICONWIDTH-9);
		settextstyle(0,0,0);
		outtextxy(left+(ICONWIDTH/2)-7,top+2+((ICONHEIGHT/2)-(textheight("JC")/2)),"JC");

	}

	int MsgBox::TotalLines(int x, int y, int width, char *str)
	{
		char text[2];
		int length,start;
		int X_Pos=x,Y_Pos=y,X_Init=X_Pos;
		int totalLines=1;

		  settextstyle(SMALL_FONT,0,0);

		  length=strlen(str)-1;

		  for(start=0;start<=length;start++)
		  {

			  if(str[start]=='\n'||X_Pos>x+width)
			  {
				Y_Pos+=2*textheight("A");
				X_Pos=X_Init;
				totalLines++;
			  }

			  sprintf(text,"%c",str[start]);
			  X_Pos+=textwidth(text);

		  }


		settextstyle(0,0,0);

		return totalLines;

	}

	void MsgBox::WriteMessage(int x, int y, int width, int fontColor, char *str)
	{
		char text[2];
		int length,start;
		int X_Pos=x,Y_Pos=y,X_Init=X_Pos;


		  settextstyle(SMALL_FONT,0,0);

		  length=strlen(str)-1;

		  for(start=0;start<=length;start++)
		  {

			  if(str[start]=='\n'||X_Pos>x+width)
			  {
				Y_Pos+=2*textheight("A");
				X_Pos=X_Init;
			  }

			  sprintf(text,"%c",str[start]);
			  setcolor(fontColor);
			  outtextxy(X_Pos,Y_Pos,text);
			  X_Pos+=textwidth(text);

		  }
		

		settextstyle(0,0,0);

		

	}

	void MsgBox::JCLogo()
	{
		
		setcolor(3);
		setfillstyle(SOLID_FILL,3);
		fillellipse(Left+(BORDERWIDTH)+TITLEBARHEIGHT/2,Top+TITLEBARHEIGHT/2,TITLEBARHEIGHT/2-1,TITLEBARHEIGHT/2-1);
		setcolor(15);
		setfillstyle(SOLID_FILL,15);
		circle(Left+(BORDERWIDTH)+TITLEBARHEIGHT/2,Top+TITLEBARHEIGHT/2,TITLEBARHEIGHT/2-3);
		settextstyle(SMALL_FONT,0,0);
		outtextxy(Left+6,Top+4,"JC");
		settextstyle(0,0,0);
	}
	int MsgBox::MessageBox(int left=200, int top=200, char *title="Confirm", char *msgtext="Confirm", int fontColor=BLACK, int btntype=jcOKOnly , int icon=jcNone)
	{
		int mbId=0;
		int totalButtons=0;
		int maxMsgBoxWidth=0;
		int increaseWidth=0;

		Left=left;
		Top=top;
		Width=MSGBOXDEFAULTWIDTH;

		strcpy(Caption,title);
		MsgBtnType=btntype;
		MsgIcon=icon;
		
		settextstyle(SMALL_FONT,0,0);

		if(MsgBtnType==jcAbortRetryIgnore || MsgBtnType==jcYesNoCancel)
		{
			Width+=2*MSGBTNDEFAULTWIDTH+(MSGBTNDEFAULTWIDTH/2);
		}
		else if(MsgBtnType==jcOKCancel || MsgBtnType==jcYesNo || MsgBtnType==jcRetryCancel)
		{
			Width+=MSGBTNDEFAULTWIDTH+(MSGBTNDEFAULTWIDTH/2);
		}

		if(MsgIcon==jcCritical||MsgIcon==jcQuestion||MsgIcon==jcExclamation||MsgIcon==jcInformation||MsgIcon==jcAbout)
		{
			Width+=2*ICONWIDTH;
			Height = MSGBOXDEFAULTHEIGHT+MSGBTNDEFAULTHEIGHT+2*(textheight("A")*TotalLines(Left+2*ICONWIDTH, Top+2*TITLEBARHEIGHT, Width-10-2*ICONWIDTH, msgtext));
		}
		else
		{
			Height = MSGBOXDEFAULTHEIGHT+MSGBTNDEFAULTHEIGHT+2*(textheight("A")*TotalLines(Left+10, Top+2*TITLEBARHEIGHT, Width-20, msgtext));

		}

		settextstyle(0,0,0);
		if(Width<textwidth(title)+(BORDERWIDTH*2)+(2*TITLEBARHEIGHT+2))
		{
		   int diff;
		   diff= textwidth(title)+(BORDERWIDTH*2)+(2*TITLEBARHEIGHT+2)-Width;
		   Width+=diff+TITLEBARHEIGHT;

		}
		settextstyle(SMALL_FONT,0,0);
		///////////////////////////////////

		if(MsgIcon==jcCritical||MsgIcon==jcQuestion||MsgIcon==jcExclamation||MsgIcon==jcInformation||MsgIcon==jcAbout)
			maxMsgBoxWidth=Width-20-2*ICONWIDTH;
		else
			maxMsgBoxWidth=Width-20;

		 
		if(maxMsgBoxWidth<strlen(msgtext)*textwidth("H"))
		{
			int totalWords=maxMsgBoxWidth/textwidth("H");
			int count=0;

			for(int i=totalWords;i<MAX_WORD_IN_LINE;i++)
			{
				if(maxMsgBoxWidth>=strlen(msgtext)*textwidth("H"))
					break;
				maxMsgBoxWidth+=textwidth("H");
				count++;
			}

			increaseWidth=count*textwidth("H");

		}

		Width+=increaseWidth;


		///////////////////////////////////

		mouse.HideMouse();

		getimage(Left,Top,Left+Width,Top+Height,buffer);

		setfillstyle(SOLID_FILL,LIGHTGRAY);
		bar(Left,Top,Left+Width,Top+Height);

		setcolor(WHITE);
		line(Left,Top,Left+Width,Top);
		line(Left,Top,Left,Top+Height);

		setcolor(BLACK);
		line(Left,Top+Height,Left+Width,Top+Height);
		line(Left+Width,Top,Left+Width,Top+Height);

		setfillstyle(SOLID_FILL,BLUE);
		bar(Left+BORDERWIDTH,Top+BORDERWIDTH,
		Left+Width-(BORDERWIDTH*2),Top+TITLEBARHEIGHT);
		
		settextstyle(0,0,0);
		setcolor(WHITE);
		settextjustify(LEFT_TEXT,TOP_TEXT);
		outtextxy(Left+(BORDERWIDTH*2)+TITLEBARHEIGHT+2,Top+(BORDERWIDTH*2)+(TITLEBARHEIGHT/2)-(textheight(Caption)/2),Caption);
		settextstyle(SMALL_FONT,0,0);
		//Icons

		if(MsgIcon==jcCritical)
			CriticalIcon(Left+10,Top+2*TITLEBARHEIGHT);
		else if(MsgIcon==jcQuestion)
			QuestionIcon(Left+10,Top+2*TITLEBARHEIGHT-10);
		else if(MsgIcon==jcExclamation)
			ExclamationIcon(Left+10,Top+2*TITLEBARHEIGHT);
		else if(MsgIcon==jcInformation)
			InformationIcon(Left+10,Top+2*TITLEBARHEIGHT-10);
		else if(MsgIcon==jcAbout)
			AboutIcon(Left+10,Top+2*TITLEBARHEIGHT);
		else
		{
		}



		if(MsgIcon==jcCritical||MsgIcon==jcQuestion||MsgIcon==jcExclamation||MsgIcon==jcInformation||MsgIcon==jcAbout)
		{

			WriteMessage(Left+2*ICONWIDTH+10, Top+2*TITLEBARHEIGHT, Width-20-2*ICONWIDTH, fontColor, msgtext);
		}
		else
		{
			WriteMessage(Left+10, Top+2*TITLEBARHEIGHT, Width-20, fontColor, msgtext);

		}


		MsgCloseBtn = new Button(Left+Width-TITLEBARHEIGHT-1, Top+2,TITLEBARHEIGHT-2, TITLEBARHEIGHT-2, "X", 9800);
		MsgCloseBtn->Draw();


		if(MsgBtnType == jcOKOnly)
		{
			MsgBtn[0]= new Button(Left+Width/2-(MSGBTNDEFAULTWIDTH/2),Top+Height-MSGBTNDEFAULTHEIGHT-12,MSGBTNDEFAULTWIDTH,MSGBTNDEFAULTHEIGHT,"OK",jcOK);
			MsgBtn[0]->Draw();
			totalButtons=1;
		}
		else if(MsgBtnType == jcOKCancel)
		{
			MsgBtn[0]= new Button(Left+Width/2-MSGBTNDEFAULTWIDTH-(MSGBTNDEFAULTWIDTH/2),Top+Height-MSGBTNDEFAULTHEIGHT-12,MSGBTNDEFAULTWIDTH,MSGBTNDEFAULTHEIGHT,"OK",jcOK);
			MsgBtn[0]->Draw();
			MsgBtn[1]= new Button(Left+Width/2+(MSGBTNDEFAULTWIDTH/2),Top+Height-MSGBTNDEFAULTHEIGHT-12,MSGBTNDEFAULTWIDTH,MSGBTNDEFAULTHEIGHT,"Cancel",jcCancel);
			MsgBtn[1]->Draw();
			totalButtons=2;
		}
		else if(MsgBtnType == jcYesNo)
		{
			MsgBtn[0]= new Button(Left+Width/2-MSGBTNDEFAULTWIDTH-(MSGBTNDEFAULTWIDTH/2),Top+Height-MSGBTNDEFAULTHEIGHT-12,MSGBTNDEFAULTWIDTH,MSGBTNDEFAULTHEIGHT,"Yes",jcYes);
			MsgBtn[0]->Draw();
			MsgBtn[1]= new Button(Left+Width/2+(MSGBTNDEFAULTWIDTH/2),Top+Height-MSGBTNDEFAULTHEIGHT-12,MSGBTNDEFAULTWIDTH,MSGBTNDEFAULTHEIGHT,"No",jcNo);
			MsgBtn[1]->Draw();
			totalButtons=2;
		}
		else if(MsgBtnType == jcRetryCancel)
		{
			MsgBtn[0]= new Button(Left+Width/2-MSGBTNDEFAULTWIDTH-(MSGBTNDEFAULTWIDTH/2),Top+Height-MSGBTNDEFAULTHEIGHT-12,MSGBTNDEFAULTWIDTH,MSGBTNDEFAULTHEIGHT,"Retry",jcRetry);
			MsgBtn[0]->Draw();
			MsgBtn[1]= new Button(Left+Width/2+(MSGBTNDEFAULTWIDTH/2),Top+Height-MSGBTNDEFAULTHEIGHT-12,MSGBTNDEFAULTWIDTH,MSGBTNDEFAULTHEIGHT,"Cancel",jcCancel);
			MsgBtn[1]->Draw();
			totalButtons=2;
		}
		else if(MsgBtnType == jcYesNoCancel)
		{
			MsgBtn[0]= new Button(Left+Width/2-2*MSGBTNDEFAULTWIDTH,Top+Height-MSGBTNDEFAULTHEIGHT-12,MSGBTNDEFAULTWIDTH,MSGBTNDEFAULTHEIGHT,"Yes",jcYes);
			MsgBtn[0]->Draw();
			MsgBtn[1]= new Button(Left+Width/2-(MSGBTNDEFAULTWIDTH/2),Top+Height-MSGBTNDEFAULTHEIGHT-12,MSGBTNDEFAULTWIDTH,MSGBTNDEFAULTHEIGHT,"No",jcNo);
			MsgBtn[1]->Draw();
			MsgBtn[2]= new Button(Left+Width/2+MSGBTNDEFAULTWIDTH,Top+Height-MSGBTNDEFAULTHEIGHT-12,MSGBTNDEFAULTWIDTH,MSGBTNDEFAULTHEIGHT,"Cancel",jcCancel);
			MsgBtn[2]->Draw();
			totalButtons=3;
		}
		else if(MsgBtnType == jcAbortRetryIgnore)
		{
			MsgBtn[0]= new Button(Left+Width/2-2*MSGBTNDEFAULTWIDTH,Top+Height-MSGBTNDEFAULTHEIGHT-12,MSGBTNDEFAULTWIDTH,MSGBTNDEFAULTHEIGHT,"Abort",jcAbort);
			MsgBtn[0]->Draw();
			MsgBtn[1]= new Button(Left+Width/2-(MSGBTNDEFAULTWIDTH/2),Top+Height-MSGBTNDEFAULTHEIGHT-12,MSGBTNDEFAULTWIDTH,MSGBTNDEFAULTHEIGHT,"Retry",jcRetry);
			MsgBtn[1]->Draw();
			MsgBtn[2]= new Button(Left+Width/2+MSGBTNDEFAULTWIDTH,Top+Height-MSGBTNDEFAULTHEIGHT-12,MSGBTNDEFAULTWIDTH,MSGBTNDEFAULTHEIGHT,"Ignore",jcIgnore);
			MsgBtn[2]->Draw();
			totalButtons=3;
		}
		else
		{
			MsgBtn[0]= new Button(Left+Width/2-(MSGBTNDEFAULTWIDTH/2),Top+Height-MSGBTNDEFAULTHEIGHT-12,MSGBTNDEFAULTWIDTH,MSGBTNDEFAULTHEIGHT,"OK",jcOK);
			MsgBtn[0]->Draw();	
			totalButtons=1;
		}
		settextstyle(0,0,0);
		JCLogo();
		
		mouse.ShowMouse();

		while(1)
		{
			mouse.ShowMouse();
			mouse.GetMouseStatus();
			

			MsgCloseBtn->EnableClickHandler();
			for(int b=0;b<totalButtons;b++)
				MsgBtn[b]->EnableClickHandler();

			mbId=ButtonId;
			ButtonId=0;

			switch(mbId)
			{
				case 9800:
					mouse.HideMouse();
					flushall();
					putimage(Left,Top,buffer,COPY_PUT);
					mouse.ShowMouse();
					for(int i=0;i<totalButtons;i++)
						delete MsgBtn[i];
					delete MsgCloseBtn;
				return 0;
				case jcOK:
				case jcCancel:
				case jcAbort:
				case jcRetry:
				case jcIgnore:
				case jcYes:
				case jcNo:
					mouse.HideMouse();
					flushall();
					putimage(Left,Top,buffer,COPY_PUT);
					mouse.ShowMouse();
					for(int k=0;k<totalButtons;k++)
						delete MsgBtn[k];
					delete MsgCloseBtn;
				return mbId;

			}

			while(kbhit()){
				int ch = getch();
				if (ch == 27)  //ESC key pressed
				{
					mouse.HideMouse();
					flushall();
					putimage(Left,Top,buffer,COPY_PUT);
					mouse.ShowMouse();
					for(int i=0;i<totalButtons;i++)
						delete MsgBtn[i];
					delete MsgCloseBtn;
					return 0;
				}
			}
		}

	}
	
	
	
	char * MsgBox::InputBox(int left=200, int top=200, char *title="Input", char *msgtext="Input", int fontColor=BLACK)
	{
		int mbId=0;
		int textboxHeight,textboxLeft,textboxTop,textboxWidth;
		int maxMsgBoxWidth=0;
		int increaseWidth=0;

		Left=left;
		Top=top;
		Width=MSGBOXDEFAULTWIDTH+2*MSGBTNDEFAULTWIDTH;
		
		settextstyle(SMALL_FONT,0,0);
		
		Height = MSGBOXDEFAULTHEIGHT+MSGBTNDEFAULTHEIGHT+2*(textheight("A")*TotalLines(Left+10, Top+2*TITLEBARHEIGHT, Width-20, msgtext));
		settextstyle(0,0,0);
		if(Width<textwidth(title)+(BORDERWIDTH*2)+(2*TITLEBARHEIGHT+2))
		{
		   int diff;
		   diff= textwidth(title)+(BORDERWIDTH*2)+(2*TITLEBARHEIGHT+2)-Width;
		   Width+=diff+TITLEBARHEIGHT;

		}
		settextstyle(SMALL_FONT,0,0);
		///////////////////////////////////

		if(MsgIcon==jcCritical||MsgIcon==jcQuestion||MsgIcon==jcExclamation||MsgIcon==jcInformation||MsgIcon==jcAbout)
			maxMsgBoxWidth=Width-20-2*ICONWIDTH;
		else
			maxMsgBoxWidth=Width-20;

		if(maxMsgBoxWidth<strlen(msgtext)*textwidth("H"))
		{
			int totalWords=maxMsgBoxWidth/textwidth("H");
			int count=0;

			for(int i=totalWords;i<MAX_WORD_IN_LINE;i++)
			{
				if(maxMsgBoxWidth>=strlen(msgtext)*textwidth("H"))
					break;
				maxMsgBoxWidth+=textwidth("H");
				count++;
			}

			increaseWidth=count*textwidth("H");

		}

		Width+=increaseWidth;


		///////////////////////////////////

		textboxLeft=Left+10;
		textboxTop=Top+2*TITLEBARHEIGHT+2*(textheight("A")*TotalLines(Left+10, Top+2*TITLEBARHEIGHT, Width-20, msgtext))+20;
		textboxWidth=Width-20;
		textboxHeight=20;

		Height+=2*textboxHeight;

		strcpy(Caption,title);
		MsgBtnType=jcOKCancel;
		
		mouse.HideMouse();

		getimage(Left,Top,Left+Width,Top+Height,buffer);

		setfillstyle(SOLID_FILL,LIGHTGRAY);
		bar(Left,Top,Left+Width,Top+Height);

		setcolor(WHITE);
		line(Left,Top,Left+Width,Top);
		line(Left,Top,Left,Top+Height);

		setcolor(BLACK);
		line(Left,Top+Height,Left+Width,Top+Height);
		line(Left+Width,Top,Left+Width,Top+Height);

		setfillstyle(SOLID_FILL,BLUE);
		bar(Left+BORDERWIDTH,Top+BORDERWIDTH,
		Left+Width-(BORDERWIDTH*2),Top+TITLEBARHEIGHT);
		
		settextstyle(0,0,0);
		setcolor(WHITE);
		settextjustify(LEFT_TEXT,TOP_TEXT);
		outtextxy(Left+(BORDERWIDTH*2)+TITLEBARHEIGHT+2,Top+(BORDERWIDTH*2)+(TITLEBARHEIGHT/2)-(textheight(Caption)/2),Caption);
		settextstyle(SMALL_FONT,0,0);


			WriteMessage(Left+10, Top+2*TITLEBARHEIGHT, Width-20, fontColor, msgtext);

		


		MsgCloseBtn = new Button(Left+Width-TITLEBARHEIGHT-1, Top+2,TITLEBARHEIGHT-2, TITLEBARHEIGHT-2, "X", 9800);
		MsgCloseBtn->Draw();

		pInputBox = new TextBox(textboxLeft,textboxTop,textboxWidth,textboxHeight,"",LEFT_TEXT,7001);
		pInputBox->Draw();
		
		MsgBtn[0]= new Button(Left+Width/2-MSGBTNDEFAULTWIDTH-(MSGBTNDEFAULTWIDTH/2),Top+Height-MSGBTNDEFAULTHEIGHT-12,MSGBTNDEFAULTWIDTH,MSGBTNDEFAULTHEIGHT,"OK",jcOK);
		MsgBtn[0]->Draw();
		MsgBtn[1]= new Button(Left+Width/2+(MSGBTNDEFAULTWIDTH/2),Top+Height-MSGBTNDEFAULTHEIGHT-12,MSGBTNDEFAULTWIDTH,MSGBTNDEFAULTHEIGHT,"Cancel",jcCancel);
		MsgBtn[1]->Draw();
			
		settextstyle(0,0,0);
		JCLogo();
		
		mouse.ShowMouse();

		while(1)
		{
			mouse.ShowMouse();
			mouse.GetMouseStatus();
			

			MsgCloseBtn->EnableClickHandler();
			for(int b=0;b<2;b++)
				MsgBtn[b]->EnableClickHandler();
			pInputBox->EnableClickHandler();

			mbId=ButtonId;
			ButtonId=0;

			switch(mbId)
			{
				case 9800:
				case jcCancel:
					mouse.HideMouse();
					flushall();
					putimage(Left,Top,buffer,COPY_PUT);
					mouse.ShowMouse();
					for(int i=0;i<2;i++)
						delete MsgBtn[i];
					delete MsgCloseBtn;
					delete pInputBox;
				return NULL;
				case jcOK:
					char inputText[70];
					strcpy(inputText,pInputBox->GetText());
					mouse.HideMouse();
					flushall();
					putimage(Left,Top,buffer,COPY_PUT);
					mouse.ShowMouse();
					for(int k=0;k<2;k++)
						delete MsgBtn[k];
					delete MsgCloseBtn;
					delete pInputBox;
				return inputText;

			}

			while(kbhit()){
				int ch = getch();
				if (ch == 27)  //ESC key pressed
				{
					mouse.HideMouse();
					flushall();
					putimage(Left,Top,buffer,COPY_PUT);
					mouse.ShowMouse();
					for(int i=0;i<2;i++)
						delete MsgBtn[i];
					delete MsgCloseBtn;
					delete pInputBox;
					return NULL;
				}
			}
		}

	}


   	
      
  #endif //__MSGBOX_CPP  			


















	

 
