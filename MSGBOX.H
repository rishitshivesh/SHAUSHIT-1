
/*================================================================
                                                               
                          MSGBOX.H                                   
                                                                 
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


	  
	#ifndef __MSGBOX_H
	#define __MSGBOX_H
	
	#ifndef __GUI_H
	#include "gui.h"
	#endif //__GUI_H
	

  class MsgBox
  {

	private:
	
	int Left,Top,Width,Height;
	int MsgBtnType;
	int MsgIcon;
	char Caption[50];
	Button *MsgCloseBtn;
	Button *MsgBtn[3];
	TextBox *pInputBox;
	void JCLogo();
	void CriticalIcon(int left, int top);
	void QuestionIcon(int left, int top);			
	void ExclamationIcon(int left, int top);
	void InformationIcon(int left, int top);       
	void AboutIcon(int left, int top);
	int TotalLines(int x, int y, int width, char *str);
	void WriteMessage(int x, int y, int width, int fontColor, char *str);
	public:
	
	int MessageBox(int left, int top, char *title, char *msgtext, int fontColor, int btntype, int icon);
	char *InputBox(int left, int top, char *title, char *msgtext, int fontColor);
	
  }; 	
      
  #endif //__MSGBOX_H  			


















	

 
