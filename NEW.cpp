#include <conio.h>
#include <iostream.h>
#include <string.h>
#include <stdio.h>
#include <dos.h>
#include <stdlib.h>
#include <ctype.h>
#include <iomanip.h>

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
		enum BUTTON{MOUSE_NORMAL = 0,MOUSE_LBUTTON=1,MOUSE_RBUTTON=2,MOUSE_MBUTTON=4};  	
		bool IsComboClick = false;
		bool IsMenuClick = false;
		bool IsMenuBarCreated=false;

// class Button
//   {

// 	private:

// 	int X,Y,Width,Height,ID;
// 	char Caption[50];
// 	BUTTON_STATUS btnStatus;
// 	void MouseDown();
// 	void MouseUp();
// 	bool State;

// 	public:
	
// 	Button(int X, int Y, int width, int height, char caption[], int Id);
// 	void Draw(int color);
// 	void Highlight(char a);
// 	void EnableClickHandler();	
	
//   };

//       Button::Button(int x, int x, int width, int height, char caption[], int Id)
//     {
// 	X = x;
// 	Y= y;
// 	Width = width;
// 	Height = height;
// 	strcpy(Caption,caption);
// 	ID = Id;
// 	btnStatus = BUTTON_STATUS_NORMAL;
// 	State = false;
//     }				


//     void Button::Draw(int color)
//    {
// 	textcolor(color);
//     int n = Y;
//     int a = Width-1;
//     gotoxy(X,Y);
//     char w[70] = " ";
//     char h[25] = " ";
//     h[0] = char(179)    ;
//     for(int i = 0;i<Width;i++)
//     {
//         w[i]=char(196);
//         h[i+1] = ' ';
//     }
//     h[a] = char(179);
//     cprintf(w);
//     n++;
//     for(int j = 0 ;j<Height;j++)
//     {
//         gotoxy(X,n);
//         cprintf(h);
//         n++;
//     }
//     gotoxy(X,n);
//     cprintf(w);
//     gotoxy(X+2,Y+(Height%2));
//     textcolor(WHITE);
//     cprintf(Caption);
	
//    }

//    void Textbox::Highlight(char a)
//    {
//    	char w[70] = " ";
//     for(int i = 0;i<Width;i++)
//         w[i] = a;
//     textcolor(RED);
//     gotoxy(X,Y+Height+1);
//     cprintf(w);
//     textcolor(WHITE);
//    }

//    void Button::MouseDown()
//    {




// 				mouse.HideMouse();

// 				draw(RED);

// 				mouse.ShowMouse();




//    }

//    void Button::MouseUp()
//    {



// 					mouse.HideMouse();

// 					draw(YELLOW);

// 					mouse.ShowMouse();






//    }


//    void Button::EnableClickHandler()
//    {

// 		// if(IsComboClick || IsMenuClick)return;

// 		if(State)
// 		{
// 			ButtonId = 0;
// 			State = false;
// 			return;
// 		}
	
// 		if(mouse.MouseInside(X,Top,X+Width,Top+Height) == 1)
// 		{

// 			if(mouse.GetButton() == MOUSE_LBUTTON)
// 			{
// 				MouseDown();
// 				btnStatus = BUTTON_STATUS_DOWN;
// 			}

// 			else if(btnStatus == BUTTON_STATUS_DOWN && mouse.GetButton() == MOUSE_NORMAL) 
// 			{
// 				MouseUp();
// 				ButtonId = ID;
// 				btnStatus = BUTTON_STATUS_NORMAL;
// 				State = true;
				
// 			}

// 		}

// 	}
	
class Mouse

	{
	
	
		private: 
		
			int MouseXpos, MouseYpos;
			BUTTON MouseBtn;
			union REGS in,out;

		public:

			int InstallMouse();
			int ShowMouse();
			int HideMouse();
			void GetMouseStatus();
			BUTTON GetButton();
			int GetPosX();
			int GetPosY();
			void SetMousePosi(int &xpos, int &ypos);
			int MouseInside(int x1, int y1, int x2, int y2);
			void RestrictMousePtr(int x1, int y1, int x2, int y2);

	};

Mouse mouse;

int Mouse::InstallMouse()
	{
 
		in.x.ax = 0;
		int86(0x33,&in,&out);
		return out.x.ax;
  
	}
	int Mouse::ShowMouse()
	{
  
		in.x.ax = 1;
		int86(0x33,&in,&out);
		return 1;
  
	}  
	int Mouse::HideMouse()
	{

		in.x.ax = 2;
		int86(0x33,&in,&out);
		return 1;

	}
	void Mouse::GetMouseStatus()
	{

		in.x.ax = 3;
		int86(0x33,&in,&out);
		MouseXpos = out.x.cx;
		MouseYpos = out.x.dx;
		MouseBtn = out.x.bx;

	}
	BUTTON Mouse::GetButton()
	{
		return MouseBtn;
	}
	
	int Mouse::GetPosX()
	{
		return MouseXpos;
	}

	int Mouse::GetPosY()
	{
		return MouseYpos;
	}
	
	void Mouse::SetMousePosi(int &xpos, int &ypos)
	{
		in.x.ax = 4;
		in.x.cx = xpos;
		in.x.dx = ypos;
		int86(0x33,&in,&out);
	}
	int Mouse::MouseInside(int x1, int y1, int x2, int y2)
	{
		int x_pos, y_pos;
		in.x.ax = 3;
		int86(0x33,&in,&out);
		x_pos = out.x.cx;
		y_pos = out.x.dx;
  
		if(x_pos >= x1 && y_pos >= y1 && x_pos <= x2 && y_pos <= y2)
			return 1;
		else 
			return 0;
  
	}
	void Mouse::RestrictMousePtr(int x1, int y1, int x2, int y2)
	{

		in.x.ax = 7;
		in.x.cx = x1;
		in.x.dx = x2;
		int86(0x33,&in,&out);  

		in.x.ax = 8;
		in.x.cx = y1;
		in.x.dx = y2;
		int86(0x33,&in,&out);  

	}

/********************************************************************TEXTBOX************************************************************/

class TextBox
  {

	private:


	int Alignment;
  	bool bReadOnly;

	int X,Y,Width,Height,ID;
	char Caption[50];
	
	void MouseDown();

	public:
	
	TextBox(int x, int y, int width, int height, char caption[],int Align, int Id);
	void Draw();
	void Highlight(char a);
	void EnableClickHandler();
	void SetReadOnly(bool ReadOnly);
	void SetText(char text[]);
	char *GetText();
	void Clear();
  }; 	

  TextBox::TextBox(int x, int y, int width, int height, char caption[],int Align, int Id)
    {
	X= x;
	Y = y;
	Width = width;
	Height = height;
	strcpy(Caption,caption);
	ID = Id;
	Alignment = Align;
	bReadOnly = false;
    }				


    void TextBox::Draw()
   {

	textcolor(YELLOW);
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
	
   }

   void TextBox::Highlight(char a)
   {
   	char w[70] = " ";
    for(int i = 0;i<Width;i++)
        w[i] = a;
    textcolor(RED);
    gotoxy(X,Y+Height+1);
    cprintf(w);
    textcolor(WHITE);
   }

   void TextBox::MouseDown()
   {
		
		if(bReadOnly) return; 

		int ch;
		int len=strlen(Caption),curpos,curx;
		

		mouse.HideMouse();
		curpos=len;
		do{
			curx=X+strlen(Caption)+1;

			if(!kbhit())
			{
				// setwritemode(XOR_PUT);
				// setcolor(WHITE);
				// line(curx,Top+2,curx,Top+Height-2);
				// do{
				// 	line(curx,Top+2,curx,Top+Height-2);
				// 	delay(100);
				//   }while(!kbhit());
				// 	setwritemode(COPY_PUT);
				//window(X+2,Y+(Height%2),X+2+len,Y+(Height%2));
				textcolor(BLACK);
	            textbackground(WHITE);

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
				if(X+strlen(Caption)>X+Width)
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
               textcolor(WHITE);
	            textbackground(BLACK);
				Draw();
		}while(ch!=13 && ch!=27);
		mouse.ShowMouse();
        //window(0,0,80,25);
		}
		
	void TextBox::SetReadOnly(bool ReadOnly)
	{
		bReadOnly = ReadOnly;
	}
	
	void TextBox::SetText(char text[])
	{
		if (X + strlen(Caption) <= X + Width - strlen(" "))
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
	// if(IsComboClick || IsMenuClick)return;
		
		if(mouse.MouseInside(X,Y,X+Width+1,Y+Height+1) == 1)
		{
            Highlight('*');
			if(mouse.GetButton() == MOUSE_LBUTTON)
			{
			MouseDown();
			TextBoxId = ID;
			}
		}
		else{
			//Draw();
		}
 
   }

   void main()
   {
   	clrscr();
   	mouse.InstallMouse();
   	_setcursortype(_NORMALCURSOR);
   	TextBox *pTextBox = new TextBox(20,3,20,1,"hello",0,0);
   	TextBox *pTextBox1 = new TextBox(20,7,20,1,"hello",0,1);
	pTextBox->Draw();
	pTextBox1->Draw();
	while(1){

		 mouse.ShowMouse(); // To show mouse
		 mouse.GetMouseStatus(); // To get position of mouse
		 pTextBox->EnableClickHandler();
		 pTextBox1->EnableClickHandler();
		  while(kbhit()){
		char ch = getch();
		if (ch == 27)  //ESC key pressed
		exit(0);
	   }

	}
         



   }