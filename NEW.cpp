#include <conio.h>
#include <fstream.h>
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
int LoginStatus=0;


void Navigate();
void welcome();
void Customerlogin();
void CustomerSignUp();
void CustomerTime();
void CustomerHome();
void AdminLogin();
void AdminSignUp();
void AdminHome();
void about();
void del()
{}
int CheckFile(char *username,char *password);
int AdminCheckID(char *username,char *password);

class MOVIE
{
    public:
    char MovieName[50],Timing[5];
    float Price;
    char* Mn()
    {return MovieName;}

};
class CUSTOMER
{
    char Password[50];
public:
    char Username[50];
    char Name[50], EMail[25];
    char Phone[10];

    //CUSTOMER(char *user,char *pass);
    void inputdata(char *name, char *username,char *password, char *email, char *phone);
    int CheckPassword(char *password);


};
class ADMIN
{
    char Password[50];
public:
    char Username[50];
    char Name[50], EMail[25];
    char Phone[10];
    void inputdata(char *name, char *username,char *password, char *email, char *phone);
    int CheckPassword(char *password);


};
int ADMIN::CheckPassword(char *password)
{
    if(strcmp(Password,password)==0)
        return 1;
    else{
        return 0;
    }
}
void ADMIN::inputdata(char *name, char *username,char *password, char *email, char *phone)
{
    strcpy(Name,name);
    strcpy(Username,username);
    strcpy(Password,password);
    strcpy(EMail,email);
    strcpy(Phone,phone);
}
int CUSTOMER::CheckPassword(char *password)
{
    if(strcmp(Password,password)==0)
        return 1;
    else{
        return 0;
    }
}
void CUSTOMER::inputdata(char *name, char *username,char *password, char *email, char *phone)
{
    strcpy(Name,name);
    strcpy(Username,username);
    strcpy(Password,password);
    strcpy(EMail,email);
    strcpy(Phone,phone);
}
int AdminCheckID(char *username,char *password=" ")
{
    ADMIN Admin;
    fstream fil;
    int exists=0;
    fil.open("admin.dat",ios::binary|ios::in);
    while(fil.read((char *)&Admin,sizeof(Admin)))
    {
        if(strcmp(Admin.Username,username)==0&&Admin.CheckPassword(password))
            exists=1;

    }
    fil.close();
    return exists;
}

int CheckFile(char *username,char *password=" ")
{
    CUSTOMER Customer;
    fstream fil;
    int exists=0;
    fil.open("customer.dat",ios::binary|ios::in);
    while(fil.read((char *)&Customer,sizeof(Customer)))
    {
        if(strcmp(Customer.Username,username)==0 && Customer.CheckPassword(password))
            exists=1;
        else if(strcmp(Customer.Username,username)==0)
            exists=2;

    }

    fil.close();
    return exists;
}
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
    TextBox *menubar = new TextBox(1,1,80,1,Caption,0,YELLOW,-1,Customerlogin);
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
    char a='*',b;
    
    do
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
            }// switch b ends
            }// case :0 ends
            break;
            case 13:{
                return;
            }
            break;
            case 'x':
                exit(0);
            break;
        }// switch a ends
    }while(a!='x');
}
void welcome()
{
    clrscr();
    _setcursortype(_NOCURSOR);
    TextBox *pAdmin = new TextBox(30,5,20,1,"ADMIN",0,YELLOW,0,AdminLogin);
    TextBox *pCustomer = new TextBox(30,8,20,1,"CUSTOMER",0,GREEN,1,Customerlogin);
    menu[0] = new Menu(0,"WELCOME");
    menu[0]->AddItem(pAdmin);
    menu[0]->AddItem(pCustomer);
    menu[0]->Draw(); 
    currentmenu = 0;
    Navigate();
    menu[currentmenu]->EnableClickHandler(currentitem);
    delete menu[currentmenu];
    //menu[0]->Draw();
}
void Customerlogin()
{
    clrscr();
    TextBox *pUsername = new TextBox(30,5,20,1,"Username",0,YELLOW,0,welcome);
    TextBox *pPassword = new TextBox(30,8,20,1,"Password",0,GREEN,1,welcome);
    menu[1]= new Menu(1,"Customer Login");
    menu[1]->AddItem(pUsername);
    menu[1]->AddItem(pPassword);
    menu[1]->Draw(); 
    currentmenu=1;
    Navigate();
    menu[currentmenu]->EnableClickHandler(currentitem);
    delete menu[currentmenu];
    //clrscr();
}
void AdminLogin()
{
    clrscr();
    TextBox *pUsername = new TextBox(30,5,20,1,"Username",0,YELLOW,0,welcome);
    TextBox *pPassword = new TextBox(30,8,20,1,"Password",0,GREEN,1,welcome);
    menu[1]= new Menu(1,"Admin Login");
    menu[1]->AddItem(pUsername);
    menu[1]->AddItem(pPassword);
    menu[1]->Draw(); 
    currentmenu=1;
    Navigate();
    menu[currentmenu]->EnableClickHandler(currentitem);
    delete menu[currentmenu];
}
void chkadmin()
{
    fstream fil;
    fil.open("Admin.dat",ios::binary|ios::in|ios::out);
    fil.seekg(0,ios::end);
    if(fil.tellg()==0)
    {
       fil.close();
       //AdminSignUp();
    }
    else
    {
       fil.close();
       welcome();
    }
}
void main()
{
    welcome();
}