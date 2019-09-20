	#ifndef __GLOBAL_H
	#define __GLOBAL_H
	
	
		// Message Box Buttons Type
		#define jcOKOnly 			1
		#define jcOKCancel 			2
		#define jcAbortRetryIgnore 	3
		#define jcYesNoCancel 		4
		#define jcYesNo 			5
		#define jcRetryCancel 		6
		
		// Icons
		#define jcCritical			16
		#define jcQuestion			32
		#define jcExclamation		48
		#define jcInformation       64
		#define jcAbout             80
		#define jcNone				90

		//Buttons 
		#define jcOK				8001
		#define jcCancel			8002
		#define jcAbort             8003
		#define jcRetry             8004
		#define jcIgnore            8005
		#define jcYes               8006
		#define jcNo                8009
		
		
		#define MAX_WORD_IN_LINE      30
		
		#define TITLEBARHEIGHT		  3
		#define BORDERWIDTH			  1
		#define MSGBTNDEFAULTWIDTH    60
		#define MSGBTNDEFAULTHEIGHT   25 
		#define MSGBOXDEFAULTWIDTH	  80
		#define MSGBOXDEFAULTHEIGHT   80
		#define ICONWIDTH			  20
		#define ICONHEIGHT            20

		#define HORIZONTAL 			  100
		#define VERTICAL              101 

		#define Textbox               201
        #define Button 				  202
        #define Label 				  203


		int ButtonId;
		int LabelId;
		int MenuId;
		int MenuItemId;
		int TextBoxId;
		int RadioButtonId;
		int PictureBoxId;
		int WindowLeft;
		int WindowTop;
		int WindowWidth;
		int NumberOfMenus=-1;
		int MenuWidth[70];
		enum bool{false,true};
		bool ARROW_LEFT = false;
		bool ARROW_UP=false;
		bool ARROW_DOWN=false;
		bool ARROW_RIGHT=false;  	
		bool IsComboClick = false;
		bool IsMenuClick = false;
		bool IsMenuBarCreated=false;
		bool IsClicked = false;

		void resetstates(){
			IsComboClick = false;
			IsMenuClick = false;
			IsMenuBarCreated=false;
			IsClicked = false;
			ARROW_LEFT = false;
			ARROW_UP=false;
			ARROW_DOWN=false;
			ARROW_RIGHT=false;
		}
	
	#endif // __GLOBAL_H