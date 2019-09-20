
/*================================================================
                                                               
                          TEXTBOX.H                                   
                                                                 
                     GUI for Turbo C++ 3.0                      
		                                                  
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


	  
	#ifndef __TEXTBOX_H
	#define __TEXTBOX_H
	
	#ifndef __GUI_H
	#include "gui.h"
	#endif //__GUI_H

	


  class TextBox
  {

	private:


	int Alignment;
  	bool bReadOnly;

	int Left,Top,Width,Height,ID;
	char Caption[50];
	
	void MouseDown();

	public:
	
	TextBox(int left, int top, int width, int height, char caption[],int Align, int Id);
	void Draw();
	void EnableClickHandler();
	void SetReadOnly(bool ReadOnly);
	void SetText(char text[]);
	char *GetText();
	void Clear();
  }; 	
      
  #endif //__TEXTBOX_H  			


















	

 
