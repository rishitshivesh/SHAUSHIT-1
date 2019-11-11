#include <conio.h>
#include <fstream.h>
#include <string.h>
#include <stdio.h>
#include <dos.h>
#include <stdlib.h>
#include <ctype.h>
#include <iomanip.h>
#include <math.h>

const int UP = 72;
const int DOWN = 80;
const int LEFT = 75;
const int RIGHT = 77;
const int ENTER = 13;
const int Exit = 404;

int Max_Seats=25; 	
int currentitem = 0;
int currentmenu = 0;
int TotalMenus=-1;

enum bool{false,true};
bool Admin_LoggedIn = false;
bool Customer_LoggedIn = false;

int Navigate();
void welcome();
void Customerlogin();
void CustomerSignUp();
void CustomerTime();
void CustomerHome();
void AdminLogin();
void AdminSignUp();
void AdminHome();
void Theatre_Settings();
void Movie_Settings();
void about();
void Default(){return;}
int Seats_Occupied();
void EnterSeats();
void seats(int Seats_Needed);
int CheckFile(char *username,char *password);
int AdminCheckID(char *username,char *password);

class MOVIE
{
    public:
    char Mn[80],Timing[5];
    float Price;
    char* MovieName();

};
char *MOVIE::MovieName()
{
    return Mn;
}
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

class ADMIN
{
    char Password[50];
public:
    char Username[50];
    char Name[50], EMail[50];
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
	int X,Y,Width,Height;
	char Caption[100];
    bool Hide;
    char HiddenText[100];
	
	public:
	
    int ID;
	TextBox(int x, int y, int width, int height, char caption[],int Align,int color, int Id,void (*callback)(void));
	void Draw();
	void Highlight(char a);
	void EnableClickHandler();
	void SetReadOnly(bool ReadOnly);
	void SetText(char text[]);
    void HideText(bool Hide);
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
    Hide = false;
    Callback=callback;
    int i;
        for(i=0;i<strlen(Caption);i++)
        HiddenText[i] = '*';
        HiddenText[i]=0;       
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
    cprintf(w);
    gotoxy(X+2,Y+(Height%2));
    textcolor(WHITE);
    if(Hide)
    cprintf(HiddenText);	
    else{cprintf(Caption);}
}

void TextBox::Highlight(char a)
{
   	if(bReadOnly)
    {
        _setcursortype(_NOCURSOR);
        char w[70] = " ";
        for(int i = 0;i<Width;i++)
            w[i] = a;
        textcolor(RED);
        gotoxy(X,Y+Height+1);
        cprintf(w);
        textcolor(WHITE);
    }
    else{
        char w[70] = " ";
        for(int i = 0;i<Width;i++)
            w[i] = a;
        textcolor(RED);
        gotoxy(X,Y+Height+1);
        cprintf(w);
        textcolor(WHITE);

        int ch;
        int len=strlen(Caption),curpos,curx;
        curpos=len;

        // if(getch()==13){
        //     Clear();
        do{
            curx=X+strlen(Caption)+2;
            gotoxy(curx,Y+(Height%2));
            _setcursortype(_NORMALCURSOR);
            ch=getch();
            // if(ch==0)
            // { ch=getch();
            switch (ch)
            {
                case 8: //backspace
                    if(len>0)
                    {
                        Caption[curpos-1]=0;
                        HiddenText[curpos-1]=0;                     
                        curpos--;
                        len--;
                    }
                break;
            }
            //}//if(ch==0) ended
            if(isprint(ch))
            {
                Caption[curpos]=ch;
                HiddenText[curpos]='*';
                Caption[curpos+1]=0;
                HiddenText[curpos+1]=0;
                if(X+strlen(Caption)>X+Width)
                {
                    Caption[curpos]=0;
                    HiddenText[curpos]=0;
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
        //}//if enter not pressed
    }
    _setcursortype(_NOCURSOR);
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
        int i;
        for(i=0;i<strlen(Caption);i++)
        HiddenText[i] = '*';
        HiddenText[i]=0;  
		Draw();
	}
}

void TextBox::HideText(bool hide)
{
    Hide = hide;
}
char *TextBox::GetText()
{
	return Caption;
}
	
void TextBox::Clear()
{
	strcpy(Caption,"");
    strcpy(HiddenText,"");
	Draw();
}

void TextBox::EnableClickHandler()
{
	Callback();
}



/*****************************************THEATRE**********************************************************/
struct THEATRE
{

};
/*****************************************SEAT***************************************************************/
class Seat
{
    int X,Y,Color,SColor;
public:
    int ID;
    bool Select;
    bool Occupied;
    Seat(int x, int y,int color=YELLOW,int scolor = GREEN, int Id = 0);
    void Draw(int color = YELLOW);
    void Highlight(); 
};
void Seat::Seat(int x, int y,int color,int scolor, int Id)
{
    X=x;
    Y=y;
    ID=Id;
    Color = color;
    SColor = scolor;
    Select=false;
    Occupied = false;
}
void Seat::Draw(int color)
{
    window(X,Y,X+1,Y+1);
    clrscr();
    gotoxy(1,1);
    if(Select){
        textcolor(SColor);
        cprintf("%c",178);
    }
    else if(Occupied){
        textcolor(DARKGRAY);
        cprintf("%c",177);
    }
    else{
        textcolor(color);
        cprintf("%c",177);
    }
    window(1,1,80,25);
}
void Seat::Highlight()
{
    window(X,Y,X+1,Y+1);
    gotoxy(1,2);
    textcolor(RED);
    cprintf("%c",220);
    window(1,1,80,25);
}
Seat *seat[100];


/*****************************************MENU*********************************************/
class Menu
{
public:
    int pageid;
    int itemnumber;
    int left_allign;
    int centre_allign;
    int right_allign;
    TextBox *textbox[25];
    TextBox *menubar;
    char Caption[80];
    Menu(int p,char a[80])
    {
        pageid = p;
        itemnumber=-1;
        currentitem=0;
        TotalMenus++;
        strcpy(Caption,a);
        menubar = NULL;
        for(int i=0;i<25;i++)
        {
            textbox[i]= NULL;
        }
    }
    void Drawbox(int l,int b,int x ,int y,char text[]);
    void Highlight(int l, int b,int x , int y , char a);
    void AddItem(TextBox *tb);
    void Draw();
    void Scroll(int current_item,int dir);
    int ReturnID(int current_item);
    void EnableClickHandler(int current_item);
    ~Menu(){
            delete menubar;
            for(int i = 0;i<itemnumber;i++)
                delete textbox[i];
            //delete this;

        }
};
void Menu::Drawbox(int l,int b,int x ,int y,char text[])
{
    textcolor(YELLOW);
    int n = y;
    int a = l-1;
    gotoxy(x,y);
    char w[80] = " ";
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
int Menu::ReturnID(int current_item)
{
    return textbox[current_item]->ID;
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
Menu *menu[30];
int Navigate()
{
    char a,b;
    
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
                case LEFT://sahi hai mere bhai
                {
                    menu[currentmenu]->Scroll(currentitem,DOWN); 
                
                }
                break;
                case UP:
                case RIGHT:
                {
                    menu[currentmenu]->Scroll(currentitem,UP);
                    
                }
                break;
            }// switch b ends
            }// case :0 ends
            break;
            case 13:{
                return menu[currentmenu]->ReturnID(currentitem);
            }
            break;
            case 'x':
                exit(0);
            break;
            default:
                return (int)a;
            break;
        }// switch a ends
    }while(a!='x');
}
void welcome()
{
    clrscr();
    _setcursortype(_NOCURSOR);
    delete menu[currentmenu];
    flushall();
    currentmenu=0;
    TextBox *pAdmin = new TextBox(30,5,20,1,"ADMIN",0,YELLOW,0,AdminLogin);
    TextBox *pCustomer = new TextBox(30,8,20,1,"CUSTOMER",0,GREEN,1,Customerlogin);
    menu[currentmenu] = new Menu(0,"WELCOME");
    menu[currentmenu]->AddItem(pAdmin);
    menu[currentmenu]->AddItem(pCustomer);
    menu[currentmenu]->Draw(); 
    switch(Navigate())
    {
        case 0:
        {
            if(Admin_LoggedIn)
                AdminHome();
            else {AdminLogin();}
        }
        break;
        case 1:
        {
            if(Customer_LoggedIn)
                CustomerHome();
            else {Customerlogin();}
        }
        break;
    }
}

void AdminSignUp()
{
    clrscr();
    _setcursortype(_NOCURSOR);

    delete menu[currentmenu];
    flushall();
    currentmenu = 1;
    TextBox *pName = new TextBox(30,5,20,1,"NAME",0,YELLOW,0,AdminSignUp);
    TextBox *pUsername = new TextBox(30,8,20,1,"Username",0,GREEN,1,AdminSignUp);
    TextBox *pPassword = new TextBox(30,11,20,1,"Password",0,YELLOW,2,AdminSignUp);
    TextBox *pPhone = new TextBox(30,14,20,1,"PHONE NUMBER",0,GREEN,3,AdminSignUp);
    TextBox *pemail = new TextBox(10,17,65,1,"EMAIL ID",0,YELLOW,4,AdminSignUp);
    TextBox *pNext = new TextBox(30,21,20,1,"NEXT",0,CYAN,5,welcome);
    pName->SetReadOnly(false);
    pUsername->SetReadOnly(false);
    pPhone->SetReadOnly(false);
    pemail->SetReadOnly(false);
    pPassword->SetReadOnly(false);

    menu[currentmenu]= new Menu(1,"ADMIN SIGN UP");
    menu[currentmenu]->AddItem(pName);
    menu[currentmenu]->AddItem(pUsername);
    menu[currentmenu]->AddItem(pPassword);
    menu[currentmenu]->AddItem(pPhone);
    menu[currentmenu]->AddItem(pemail);
    menu[currentmenu]->AddItem(pNext);
    menu[currentmenu]->Draw(); 
    pPassword->HideText(true);

    if(Navigate()==5){
    ADMIN Admin;
    Admin.inputdata(pName->GetText(),pUsername->GetText(),pPassword->GetText(),pemail->GetText(),pPhone->GetText());
    fstream fil;
    fil.open("admintext.dat",ios::binary|ios::app);
    fil.write((char*)&Admin,sizeof(Admin));
    fil.close();
    menu[currentmenu]->EnableClickHandler(currentitem);
    }
}
void CustomerSignUp()
{
    clrscr();
    _setcursortype(_NOCURSOR);
    delete menu[currentmenu];
    flushall();
    currentmenu = 1;
    TextBox *pName = new TextBox(30,5,20,1,"NAME",0,YELLOW,0,CustomerSignUp);
    TextBox *pUsername = new TextBox(30,8,20,1,"Username",0,GREEN,1,CustomerSignUp);
    TextBox *pPassword = new TextBox(30,11,20,1,"Password",0,YELLOW,2,CustomerSignUp);
    TextBox *pPhone = new TextBox(30,14,20,1,"PHONE NUMBER",0,GREEN,3,CustomerSignUp);
    TextBox *pemail = new TextBox(10,17,65,1,"EMAIL ID",0,YELLOW,4,CustomerSignUp);
    TextBox *pNext = new TextBox(30,21,20,1,"NEXT",0,CYAN,5,Customerlogin);
    TextBox *pBack = new TextBox(10,21,20,1,"BACK",0,CYAN,6,Customerlogin);
    pName->SetReadOnly(false);
    pUsername->SetReadOnly(false);
    pPhone->SetReadOnly(false);
    pemail->SetReadOnly(false);
    pPassword->SetReadOnly(false);

    menu[currentmenu]= new Menu(1,"CUSTOMER SIGN UP");
    menu[currentmenu]->AddItem(pName);
    menu[currentmenu]->AddItem(pUsername);
    menu[currentmenu]->AddItem(pPassword);
    menu[currentmenu]->AddItem(pPhone);
    menu[currentmenu]->AddItem(pemail);
    menu[currentmenu]->AddItem(pNext);
    menu[currentmenu]->AddItem(pBack);
    menu[currentmenu]->Draw(); 
    pPassword->HideText(true);

    switch(Navigate())
    {
        case 6:
            menu[currentmenu]->EnableClickHandler(currentitem);
        break;
        case 5:
        {
            CUSTOMER Customer;

            Customer.inputdata(pName->GetText(),pUsername->GetText(),pPassword->GetText(),pemail->GetText(),pPhone->GetText());
            if(CheckFile(pUsername->GetText())==2)
            {
                gotoxy(15,20);
                cprintf("User Exists. Press Enter to go to LoginPage!");
                if(getch()==13)
                    Customerlogin();
            }
            else
            {
                fstream fil;
                fil.open("customertext.dat",ios::binary|ios::app);
                fil.write((char *)&Customer,sizeof(Customer));
                fil.close();
                Customerlogin();
            }
        }
        break;
        default:
            menu[currentmenu]->EnableClickHandler(currentitem);
        break;
    }
    
}
void Customerlogin()
{
    clrscr();
    _setcursortype(_NOCURSOR);
    delete menu[currentmenu];
    flushall();
    currentmenu = 2;
    TextBox *pUsername = new TextBox(30,5,20,1,"Username",0,YELLOW,0,Customerlogin);
    TextBox *pPassword = new TextBox(30,8,20,1,"Password",0,GREEN,1,Customerlogin);
    TextBox *pCustomerSignUp = new TextBox(30,11,20,1,"New Here, SIGN UP",4,LIGHTGREEN,1,CustomerSignUp);
    TextBox *pNext = new TextBox(50,15,20,1,"NEXT",0,CYAN,2,CustomerHome);
    TextBox *pBack = new TextBox(10,15,20,1,"BACK",0,CYAN,3,welcome);
    pUsername->SetReadOnly(false);
    pPassword->SetReadOnly(false);
    menu[currentmenu]= new Menu(2,"Customer Login");
    menu[currentmenu]->AddItem(pUsername);
    menu[currentmenu]->AddItem(pPassword);
    menu[currentmenu]->AddItem(pCustomerSignUp);
    menu[currentmenu]->AddItem(pNext);
    menu[currentmenu]->AddItem(pBack);
    menu[currentmenu]->Draw(); 
    pPassword->HideText(true);
    switch(Navigate())
    {
        case 3:
            menu[currentmenu]->EnableClickHandler(currentitem);
        break;
        case 2:
        {
            if(CheckFile(pUsername->GetText(),pPassword->GetText())==1)
            {
                Customer_LoggedIn =true;
                CustomerHome();
            }
            else{
                gotoxy(20,14);
                cprintf("Incorrect Password or Username,Press Enter to Retry");
                if(getch()==13)
                    Customerlogin();
            }
        }
        break;
        default:
            menu[currentmenu]->EnableClickHandler(currentitem);
        break;
    }
}
void AdminLogin()
{
    clrscr();
    _setcursortype(_NOCURSOR);
    delete menu[currentmenu];
    flushall();
    currentmenu=2;
    TextBox *pUsername = new TextBox(30,5,20,1,"Username",0,YELLOW,0,AdminLogin);
    TextBox *pPassword = new TextBox(30,8,20,1,"Password",0,GREEN,1,AdminLogin);
    TextBox *pNext = new TextBox(50,12,20,1,"NEXT",0,CYAN,2,welcome);
    TextBox *pBack = new TextBox(10,12,20,1,"BACK",0,CYAN,3,welcome);
    pUsername->SetReadOnly(false);
    pPassword->SetReadOnly(false);
    menu[currentmenu]= new Menu(2,"Admin Login");
    menu[currentmenu]->AddItem(pUsername);
    menu[currentmenu]->AddItem(pPassword);
    menu[currentmenu]->AddItem(pNext);
    menu[currentmenu]->AddItem(pBack);
    menu[currentmenu]->Draw(); 
    pPassword->HideText(true);

    switch(Navigate())
    {
        case 3:
            menu[currentmenu]->EnableClickHandler(currentitem);
        break;
        case 2:
        {
            if(AdminCheckID(pUsername->GetText(),pPassword->GetText())==1)
            {
                Admin_LoggedIn=true;
                AdminHome();
            }
            else{
                gotoxy(20,11);
                cprintf("Incorrect Password,Press Enter to Retry");
                if(getch()==13)
                    AdminLogin();
            }
        }
        break;
        default:
            menu[currentmenu]->EnableClickHandler(currentitem);
        break;
    }
}

void AdminHome()
{
    clrscr();
    _setcursortype(_NOCURSOR);
    delete menu[currentmenu];
    flushall();
    currentmenu=3;
    TextBox *M_Settings = new TextBox(25,5,30,1,"Movie Settings",0,YELLOW,0,Movie_Settings);
    TextBox *T_Settings = new TextBox(25,8,30,1,"Theatre Settings",0,YELLOW,1,Theatre_Settings);
    TextBox *D_Settings = new TextBox(25,11,30,1,"Database Settings",0,YELLOW,2,Theatre_Settings);
    TextBox *pAbout = new TextBox(25,14,30,1,"ABOUT",0,CYAN,3,welcome);
    TextBox *pBack = new TextBox(1,23,20,1,"BACK",0,CYAN,4,AdminLogin);
    menu[currentmenu]= new Menu(3,"Hello Motu Admin");
    menu[currentmenu]->AddItem(M_Settings);
    menu[currentmenu]->AddItem(T_Settings);
    menu[currentmenu]->AddItem(D_Settings);
    menu[currentmenu]->AddItem(pAbout);
    menu[currentmenu]->AddItem(pBack);
    menu[currentitem]->Draw();
    switch(Navigate())
    {
        case 4:
        {
                window(20,24,50,25);
                clrscr();
                gotoxy(1,1);
                cprintf("Do you want to LOG OUT(y/n)");
                if(tolower(getch())=='y')
                {
                    window(20,24,50,25);
                    clrscr();
                    window(1,1,80,25);
                    Admin_LoggedIn=false;
                    menu[currentmenu]->EnableClickHandler(currentitem);
                    break;
                }
                else{
                    window(1,1,80,25);
                    AdminHome();
                } 
        }
        break;
        default:
            menu[currentmenu]->EnableClickHandler(currentitem);
        break;
    }
}
void CustomerHome()
{
    clrscr();
    //window(1,1,80,25);
    //clrscr();
    _setcursortype(_NOCURSOR);
    delete menu[currentmenu];
    flushall();
    currentmenu=3;
    TextBox *m1 = new TextBox(5,5,10,5,"Movie 1",0,YELLOW,0,EnterSeats);
    TextBox *m2 = new TextBox(50,5,10,5,"Movie 2",0,GREEN,1,EnterSeats);
    TextBox *m3 = new TextBox(5,12,10,5,"Movie 3",0,CYAN,2,EnterSeats);
    TextBox *m4 = new TextBox(50,12,10,5,"Movie 4",0,CYAN,3,EnterSeats);
    TextBox *pBack = new TextBox(1,23,8,1,"BACK",0,CYAN,4,Customerlogin);
    menu[currentmenu]= new Menu(3,"Now Playing");
    menu[currentmenu]->AddItem(m1);
    menu[currentmenu]->AddItem(m2);
    menu[currentmenu]->AddItem(m3);
    menu[currentmenu]->AddItem(m4);
    menu[currentmenu]->AddItem(pBack);
    menu[currentitem]->Draw();
    switch(Navigate())
    {
        case 4:
        {
                window(20,24,50,25);
                clrscr();
                gotoxy(1,1);
                cprintf("Do you want to LOG OUT(y/n)");
                if(tolower(getch())=='y')
                {
                    window(20,24,50,25);
                    clrscr();
                    window(1,1,80,25);
                    Customer_LoggedIn=false;
                    menu[currentmenu]->EnableClickHandler(currentitem);
                    break;
                }
                else{
                    window(1,1,80,25);
                    CustomerHome();
                } 
        }
        break;
        default:
            menu[currentmenu]->EnableClickHandler(currentitem);
        break;
    }
    //getch();

}
void Movie_Settings()
{
    clrscr();
    _setcursortype(_NOCURSOR);
    delete menu[currentmenu];
    flushall();
    currentmenu=4;
    textcolor(GREEN);
    gotoxy(1,4);
    cprintf("%s","Movie 1 :");
    gotoxy(25,4);
    cprintf("%s","NAME");
    TextBox *pName1 = new TextBox(11,5,68,1,"NAME",0,YELLOW,0,welcome);
    pName1->SetReadOnly(false);
    gotoxy(11,8);
    cprintf("%s","Timings");
    TextBox *pTime1 = new TextBox(11,9,10,1,"TIME",0,YELLOW,1,welcome);
    pTime1->SetReadOnly(false);
    gotoxy(24,8);
    cprintf("%s","Price");
    TextBox *pPrice1 = new TextBox(24,9,10,1,"PRICE",0,YELLOW,2,welcome);
    pPrice1->SetReadOnly(false);
    gotoxy(1,13);
    cprintf("%s","Movie 2 :");
    gotoxy(25,13);
    cprintf("%s","NAME");
    TextBox *pName2 = new TextBox(11,14,68,1,"NAME",0,YELLOW,3,welcome);
    pName2->SetReadOnly(false);
    gotoxy(11,17);
    cprintf("%s","Timings");
    TextBox *pTime2 = new TextBox(11,18,10,1,"TIME",0,YELLOW,4,welcome);
    pTime2->SetReadOnly(false); 
    gotoxy(24,17);
    cprintf("%s","Price");
    TextBox *pPrice2 = new TextBox(24,18,10,1,"PRICE",0,YELLOW,5,welcome);
    pPrice2->SetReadOnly(false);

    TextBox *pSubmit = new TextBox(50,23,20,1,"SUBMIT",0,CYAN,6,AdminHome);
    TextBox *pBack = new TextBox(10,23,20,1,"BACK",0,CYAN,7,AdminHome);

    menu[currentmenu]= new Menu(4,"Movie Settings");
    menu[currentmenu]->AddItem(pName1);
    menu[currentmenu]->AddItem(pPrice1);
    menu[currentmenu]->AddItem(pTime1);
    menu[currentmenu]->AddItem(pName2);
    menu[currentmenu]->AddItem(pPrice2);
    menu[currentmenu]->AddItem(pTime2);
    menu[currentmenu]->AddItem(pSubmit);
    menu[currentmenu]->AddItem(pBack);
    menu[currentmenu]->Draw();
    MOVIE movie,temp;
    fstream fil;
    fil.open("movie.dat",ios::binary|ios::app|ios::in);
    switch(Navigate())
    {
        case 3:
            strcpy(movie.Mn,pName1->GetText());
            strcpy(movie.Timing,pTime1->GetText());
            movie.Price=atof(pPrice1->GetText());
            while(fil.read((char*)&temp,sizeof(temp)))
            {
                if(temp.Mn==movie.Mn)
                {
                    int pos = -1 * sizeof(temp);
                    fil.seekp(pos, ios::cur);
                    fil.write((char *)&movie,sizeof(movie));
                    fil.close();
                    menu[currentmenu]->EnableClickHandler(currentitem);
                    //return;
                }
                else{
                    fil.write((char *)&movie,sizeof(movie));
                    fil.close();
                }
            }
            fil.write((char *)&movie,sizeof(movie));
            fil.close();
            menu[currentmenu]->EnableClickHandler(currentitem);
        break;
        default:
            menu[currentmenu]->EnableClickHandler(currentitem);
        break;
    }

}
void Theatre_Settings()
{

}
void chkadmin()
{
    fstream fil;
    fil.open("admintext.dat",ios::binary|ios::in|ios::out);
    fil.seekg(0,ios::end);
    if(fil.tellg()==0)
    {
       fil.close();
       AdminSignUp();
    }
    else
    {
       fil.close();
       welcome();
    }
    fil.close();
}
int Seats_Occupied()
{
    int s = 0;
    for(int i = 0;i<Max_Seats;i++)
    {
        if(seat[i]->Occupied==true)
            s++;
    }
    return s;
}
void EnterSeats()
{
    clrscr();
    _setcursortype(_NOCURSOR);
    delete menu[currentmenu];
    flushall();
    currentmenu=4;
    int Seats_Needed=1;
    TextBox *nos = new TextBox(30,10,20,1,"Enter Seats",0,GREEN,0,EnterSeats);
    TextBox *pNext = new TextBox(72,23,8,1,"NEXT",0,CYAN,2,welcome);
    TextBox *pBack = new TextBox(1,23,8,1,"BACK",0,CYAN,3,CustomerHome);
    nos->SetReadOnly(false);
    menu[currentmenu]= new Menu(4,"Enter number of Seats");
    menu[currentmenu]->AddItem(nos);
    menu[currentmenu]->AddItem(pNext);
    menu[currentmenu]->AddItem(pBack);
    menu[currentmenu]->Draw(); 

    switch(Navigate())
    {
        case 2:
        {
            Seats_Needed = atoi(nos->GetText());
            if(Seats_Needed<=(25-Seats_Occupied()) && Seats_Needed>0)//
            {
                seats(Seats_Needed);
            }

            else{
                gotoxy(20,20);
                cout<<"only "<<Seats_Occupied()<<" seats are available PRESS ENTER";
                getch();
                delete menu[currentmenu];
                flushall();
                EnterSeats();
            }
        }
        break;
        default:
        {
            menu[currentmenu]->EnableClickHandler(currentitem);
        }
        break;
    }
}
void seats(int Seats_Needed)
{
    //chkadmin();
    clrscr();
    _setcursortype(_NOCURSOR);
    delete menu[currentmenu];
    flushall();
    currentmenu=5;
    bool manualmode = false;
    cout<<"Do you want to select seats manually?(y/n)";
    if(tolower(getch())=='y')
    {
        manualmode = true;
    }
    clrscr();
    TextBox *pNext = new TextBox(72,23,8,1,"NEXT",0,CYAN,2,welcome);
    TextBox *pBack = new TextBox(1,23,8,1,"BACK",0,CYAN,3,CustomerHome);
    window(1,1,80,25);
    menu[currentmenu]= new Menu(5,"Seats");
    menu[currentmenu]->AddItem(pNext);
    menu[currentmenu]->AddItem(pBack);
    menu[currentmenu]->Draw(); 
    int i=0,j=0,k=0,a,l=0,seats_selected=0;
    
    // for(j=0;j<25;j++)
    // {
    //    delete seat[j];
    // }
    // while(i<25)
    // {
    //     for(j = 0;j<5;j++)
    //         {
    //             seat[i] = new Seat(20+(10*j),5+k,YELLOW,GREEN,i);
    //             seat[i]->Draw();
    //             i++;
    //         }
    //     k+=4;
    // }
    for(i=0;i<Max_Seats;i++)
    {
        seat[i]->Draw();
    }
    
    i = 0;
    seat[0]->Highlight();
    if(manualmode)
        seat[i]->Draw(LIGHTGREEN);
    else{
        for(j=i;j<i+Seats_Needed&&j<25;j++)
        {
            seat[j]->Draw(LIGHTGREEN);    
        }
        seat[i]->Highlight();
    }

    do{
        int a = getch();
        
        switch(a)
        {
            case 0:
            {
                a=getch();
                switch(a)
                {
                    case RIGHT:
                    {
                        if(i<24){
                            for(j=0;j<25;j++)
                            {
                                //seat[j]->Select=false;
                                seat[j]->Draw();
                            }
                            seat[++i]->Highlight();
                            seat[i]->Draw(LIGHTGREEN);
                            if(!manualmode){
                                for(j=i;j<i+Seats_Needed&&j<25;j++)
                                {
                                    seat[j]->Draw(LIGHTGREEN);
                                }
                            }
                            seat[i]->Highlight();
                        }
                    }
                    break;
                    case LEFT:
                    {
                        if(i>0){
                            for(j=0;j<25;j++)
                            {
                                //seat[j]->Select=false;
                                seat[j]->Draw();
                            }
                            seat[--i]->Highlight();
                            seat[i]->Draw(LIGHTGREEN);
                            if(!manualmode){
                                for(j=i;j<i+Seats_Needed&&j<25;j++)
                                {
                                    seat[j]->Draw(LIGHTGREEN);
                                }
                            }
                            seat[i]->Highlight();
                        }
                    }
                    break;
                    case UP:
                    {
                        if(i>4&&i<25)
                        {
                            for(j=0;j<25;j++)
                            {
                                //seat[j]->Select=false;
                                seat[j]->Draw();
                            }
                            i-=5;
                            seat[i]->Highlight();
                            seat[i]->Draw(LIGHTGREEN);
                            if(!manualmode){
                                for(j=i;j<i+Seats_Needed&&j<25;j++)
                                {
                                    seat[j]->Draw(LIGHTGREEN);
                                }
                            }
                            seat[i]->Highlight();
                        }
                    }
                    break;
                    case DOWN:
                    {
                        if(i>=0&&i<20)
                        {
                            for(j=0;j<25;j++)
                            {
                                //seat[j]->Select=false;
                                seat[j]->Draw();
                            }
                            i+=5;
                            seat[i]->Highlight(); 
                            seat[i]->Draw(LIGHTGREEN);
                            if(!manualmode){
                                for(j=i;j<i+Seats_Needed&&j<25;j++)
                                {
                                    seat[j]->Draw(LIGHTGREEN);
                                }
                            }
                            seat[i]->Highlight();
                        }
                    }
                    break;
                }
            }
            break;
            case ENTER:
            {
                if(!manualmode)
                {
                    for(j=i;j<i+Seats_Needed&&j<25;j++)
                    {
                        if(!(seat[j]->Occupied))
                        {
                            seat[j]->Select=true;
                            seat[j]->Draw();
                        }
                    }
                    window(20,24,50,25);
                    clrscr();
                    gotoxy(1,1);
                    cprintf("Do you want to continue(y/n)");
                    if(tolower(getch())=='y')
                    {
                        for(j=i;j<i+Seats_Needed&&j<25;j++)
                        {
                            seat[j]->Occupied=true;
                            seat[j]->Select=false;
                            seat[j]->Draw();
                        }
                        window(20,24,50,25);
                        clrscr();
                        window(1,1,80,25);
                        l=1;
                        break;
                    }
                    else{
                        window(1,1,80,25);
                        clrscr();
                        for(j=i;j<i+Seats_Needed&&j<25;j++)
                        {
                            seat[j]->Select=false;
                        }
                        EnterSeats();
                    }
                }
                else{           //MANUAL MODE
                    if(seats_selected!=Seats_Needed)
                    {
                        if(!(seat[i]->Occupied))
                        {
                            seat[i]->Select=true;
                            seat[i]->Draw();
                            seats_selected++;
                        }    
                    }
                    else{
                        window(20,24,50,25);
                    clrscr();
                    gotoxy(1,1);
                    cprintf("Do you want to continue(y/n)");
                    if(tolower(getch())=='y')
                    {
                        for(j=0;j<25;j++)
                        {
                            if(seat[j]->Select==true)
                            {
                                seat[j]->Occupied=true;
                                seat[j]->Select=false;
                                seat[j]->Draw();
                            }                           
                        }
                        window(20,24,50,25);
                        clrscr();
                        window(1,1,80,25);
                        l=1;
                        break;
                    }
                    else{
                        window(1,1,80,25);
                        clrscr();
                        for(j=0;j<25;j++)
                        {
                            seat[j]->Select=false;
                        }
                        EnterSeats();
                    }
                }
            }
            }
            break;
            case 27:
            {
                for(j=i;j<i+Seats_Needed&&j<25;j++)
                {
                    seat[j]->Select=false;
                    seat[j]->Draw();
                }
                seat[i]->Highlight();
            }
            break;
            case 'x':
            {
                for(i =0;i<25;i++)
                {
                    delete seat[i];
                }
                exit(0);
            }
            break;
        }
    }while(a!='x'&&l!=1);
    // for(j =0;j<25;j++)
    // {
    //     delete seat[j];
    // }
    switch(Navigate())
    {
        default: 
            menu[currentmenu]->EnableClickHandler(currentitem);
        break;
    }
}
void main()
{
    int p=0,q=0,r=0;
    while(p<25)
    {
        for(q = 0;q<5;q++)
            {
                seat[p] = new Seat(20+(10*q),5+r,YELLOW,GREEN,p);
                seat[p]->Occupied= false;
                p++;
            }
        r+=4;
    }
    chkadmin();
    //EnterSeats();
    for(p =0;p<25;p++)
    {
        delete seat[p];
    }
    for(p=0;p<10;p++)
    {
        delete menu[p];
    }
}