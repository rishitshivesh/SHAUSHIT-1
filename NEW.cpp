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
int TotalMenus=-1;
int MenuWidth[70];
const int UP = 72;
const int DOWN = 80;
const int ENTER = 13;
const int Exit = 404;
enum bool{false,true};
enum BUTTON{MOUSE_NORMAL = 0,MOUSE_LBUTTON=1,MOUSE_RBUTTON=2,MOUSE_MBUTTON=4};  	
bool IsComboClick = false;
bool IsMenuClick = false;
bool IsMenuBarCreated=false;
bool IsPressed = false;
int currentitem = 0;
int currentmenu = 0;

void Navigate();
void welcome();
void CustomerLogin();

/********************************************************************TEXTBOX************************************************************/

class TextBox
{
	private:

	int Alignment,Color;
  	bool bReadOnly;
    void (*Callback)(void);
	int X,Y,Width,Height,ID;
	char Caption[50];
	
	public:
	
	TextBox(int x, int y, int width, int height, char caption[],int Align,int color, int Id,void (*callback)(void));
	void Draw();
	void Highlight(char a);
	void EnableClickHandler();
	void SetReadOnly(bool ReadOnly);
	void SetText(char text[]);
	char *GetText();
	void Clear();
}; 	

TextBox::TextBox(int x, int y, int width, int height, char caption[],int Align,int color, int Id,void (*callback)(void))
{
	X= x;
	Y = y;
	Width = width;
	Height = height;
	strcpy(Caption,caption);
	ID = Id;
	Alignment = Align;
    Color=color;
	bReadOnly = true;
    Callback=callback;
}				

void TextBox::Draw()
{
	textcolor(Color);
    int n = Y;
    int a = Width-1;
    gotoxy(X,Y);
    char w[100] = " ";
    char h[100] = " ";
    h[0] = char(179);
    for(int i = 0;i<Width;i++)
    {
        w[i]=char(196);
        //cprintf("-");
        h[i+1] = ' ';
    }
    h[a] = char(179);
    cprintf(w);
    n++;
    for(int j = 0;j<Height;j++)
    {
        gotoxy(X,n);
        cprintf(h);
        n++;
    }
    gotoxy(X,n);
    // for(int k = 0;k<Width;k++)
    // {
    //     //w[i]=char(196);
    //     cprintf("-");
    //     //h[i+1] = ' ';
    // }
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
	
void TextBox::SetReadOnly(bool ReadOnly)
{
	bReadOnly = ReadOnly;
}
	
void TextBox::SetText(char text[])
{
	if (X + strlen(Caption) <= X + Width - strlen(" ") && !bReadOnly)
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
	Callback();
}

class Menu
{
public:
    int pageid;
    int itemnumber;
    int left_allign;
    int centre_allign;
    int right_allign;
    TextBox *textbox[10];
    TextBox *menubar;
    char Caption[80];
    Menu(int p,char a[80])
    {
        pageid = p;
        itemnumber=-1;
        currentitem=0;
        TotalMenus++;
        strcpy(Caption,a);
    }
    void Drawbox(int l,int b,int x ,int y,char text[]);
    void Highlight(int l, int b,int x , int y , char a);
    //void AddItem(int l,int b,int x ,int y,char text[],int color=YELLOW);
    void AddItem(TextBox *tb);
    void Draw();
    void Scroll(int currentitem,int dir);
    void EnableClickHandler(int current_item);
    ~Menu(){
 			delete textbox;
 			delete menubar;
 		}
};

void Menu::Drawbox(int l,int b,int x ,int y,char text[])
{
    textcolor(YELLOW);
    int n = y;
    int a = l-1;
    gotoxy(x,y);
    char w[70] = " ";
    char h[25] = " ";
    h[0] = char(179)    ;
    for(int i = 0;i<l;i++)
    {
        w[i]=char(196);
        h[i+1] = ' ';
    }
    h[a] = char(179);
    cprintf(w);
    n++;
    for(int j = 0 ;j<b;j++)
    {
        gotoxy(x,n);
        cprintf(h);
        n++;
    }
    gotoxy(x,n);
    cprintf(w);
    gotoxy(x+2,y+(b%2));
    textcolor(WHITE);
    cprintf(text);
    
}
// void Menu::AddItem(int l,int b,int x ,int y,char text[],int color)
// {
// 	textbox[itemnumber]= new TextBox(l,b,x,y,text,0,color,itemnumber);
// 	itemnumber++;
// }
void Menu::AddItem(TextBox *tb)
{
    itemnumber++;
    textbox[itemnumber]= tb;
}
void Menu::Highlight(int l, int b,int x , int y , char a)
{
    int m = x,n=y;
    char w[70] = " ";
    for(int i = 0;i<l;i++)
        w[i] = a;
    textcolor(RED);
    gotoxy(m,n+b+1);
    cprintf(w);
    textcolor(WHITE);
}

void Menu::Draw()
{
    TextBox *menubar = new TextBox(1,1,80,1,Caption,0,YELLOW,-1,CustomerLogin);
	menubar->Draw();
	for(int i=0;i<=itemnumber;i++)
    {
    	textbox[i]->Draw();
    }
    textbox[currentitem]->Highlight('*');
}

void Menu::Scroll(int current_item,int dir)
{
    textbox[current_item]->Draw();
    switch(dir)
        {
        case DOWN:
        {
        if(current_item<itemnumber)
        {
             currentitem++;
             textbox[(current_item+1)]->Highlight('*');
        }
        else if(current_item ==itemnumber)
        {
             currentitem = 0;
             textbox[currentitem]->Highlight('*');
        }
        }
          break;
          case UP:
           {
        if(current_item>0)
        {
             currentitem--;
             textbox[currentitem]->Highlight('*');
        }
        else if(currentitem == 0)
        {
             currentitem = itemnumber;
             textbox[currentitem]->Highlight('*');
        }
           }
        break;
    }
}
void Menu::EnableClickHandler(int current_item)
{
    textbox[current_item]->EnableClickHandler();
}
Menu *menu[10];
void Navigate()
{
    char a,b;
    
    while(1)
    {
        a=getch();
        switch(tolower(a))
        {
            case 0:
            {
            b = getch();
            switch(b)
            {
                case DOWN:
                {
                    menu[currentmenu]->Scroll(currentitem,DOWN); 
                
                }
                break;
                case UP:
                {
                    menu[currentmenu]->Scroll(currentitem,UP);
                    
                }
                break;
                case 13:
                    menu[currentmenu]->EnableClickHandler(currentitem);
                break;
            }// switch b ends
            }// case :0 ends
            break;
            case 13:{
                menu[currentmenu]->EnableClickHandler(currentitem);
                //return;
            }
            break;
            case 'x':
                return;
            break;
        }// switch a ends
    }
}
void welcome()
{
    clrscr();
    _setcursortype(_NOCURSOR);
    TextBox *pAdmin = new TextBox(30,5,20,1,"ADMIN",0,YELLOW,0,CustomerLogin);
    TextBox *pCustomer = new TextBox(30,8,20,1,"CUSTOMER",0,GREEN,1,CustomerLogin);
    menu[0] = new Menu(0,"WELCOME");
    menu[0]->AddItem(pAdmin);
    menu[0]->AddItem(pCustomer);
    menu[0]->Draw(); 
    Navigate();
    menu[0]->Draw();
}
void CustomerLogin()
{
    clrscr();
    getch();
}
void main()
{
    welcome();
}