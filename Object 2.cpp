#include <conio.h>
#include <fstream.h>
#include <string.h>
#include <stdio.h>
#include <dos.h>
#include <stdlib.h>
#include <ctype.h>
#include <iomanip.h>
#include <math.h>
#include <time.h>
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
bool debug_mode = false;
int Navigate();
void welcome();
void Customerlogin();
void CustomerSignUp();
void CustomerTime();
void CustomerIndex();
void CustomerHome();
void CustomerConfirm();
void AdminLogin();
void AdminSignUp();
void AdminHome();
void Theatre_Settings();
void Database_Settings();
void Movie_Settings();
void about();
void CancelTicket();
void ChangePassword();
void ViewBookingHistory();
void Default(){return;}
int Seats_Occupied();
void EnterSeats();
void PrintLogo(int);
void about();
void seats(int Seats_Needed);
int CheckFile(char *username,char *password);
int AdminCheckID(char *username,char *password);

class MOVIE
{
    public:
    char Mn[80],Timing[5], CustUserId[50];
    float Price, CustFinalPrice;
    char* MovieName();
    int Seats;
    char ID[15];
    bool Status;

}Choice;
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
	int myseats[25];
	CUSTOMER();
    //CUSTOMER(char *user,char *pass);
    void inputdata(char *name, char *username,char *password, char *email, char *phone);
    int CheckPassword(char *password);
    void ChangePassword(char *password);


};
CUSTOMER::CUSTOMER()
{
	for(int i=0;i<25;i++)
		myseats[i]=0;

}
int CUSTOMER::CheckPassword(char *password)
{
    if(strcmp(Password,password)==0)
	return 1;
    else{
	return 0;
    }
}
void CUSTOMER::ChangePassword(char *password)
{
    strcpy(Password,password);
}
void CUSTOMER::inputdata(char *name, char *username,char *password, char *email, char *phone)
{
    strcpy(Name,name);
    strcpy(Username,username);
    strcpy(Password,password);
    strcpy(EMail,email);
    strcpy(Phone,phone);
}
CUSTOMER current_customer;
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
    fil.open("admintext.dat",ios::binary|ios::in);
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
    fil.open("customertext.dat",ios::binary|ios::in);
    while(fil.read((char *)&Customer,sizeof(Customer)))
    {
	if(strcmp(Customer.Username,username)==0 && Customer.CheckPassword(password))
	{
		exists=1;
		current_customer=Customer;
		strcpy(Choice.CustUserId,current_customer.Username);
	}
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
    char h =char(186);
    if(bReadOnly)
    {
	_setcursortype(_NOCURSOR);
	char w[70] = " ";
    //h[0] = char(179);
	for(int i = 0;i<Width;i++)
	{
         w[i] = a;
         //h[i+1] = ' ';
    }   
    //h[a] = char(179);
	textcolor(RED);
    gotoxy(X,Y);
    cprintf("%c",h);
    gotoxy(X+Width-1,Y+1);
    cprintf("%c",h);
    gotoxy(X,Y+1);
    cprintf("%c",h);
    gotoxy(X,Y+Height+1);
    cprintf(w);
    textcolor(3);
    }
    else{
	char w[70] = " ";
	for(int i = 0;i<Width;i++)
	    w[i] = a;
	textcolor(RED);
    gotoxy(X,Y);
    cprintf(w);
	gotoxy(X,Y+Height+1);
	cprintf(w);
	gotoxy(X+Width-1,Y+1);
    cprintf("%c",h);
    gotoxy(X,Y+1);
    cprintf("%c",h);
    textcolor(3);

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
    gotoxy(X,Y);
    cprintf(w);
    gotoxy(X,Y+Height+1);
    cprintf(w);
    gotoxy(X+Width-1,Y+1);
    cprintf("%c",h);
    gotoxy(X,Y+1);
    cprintf("%c",h);
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
    int X,Y,Color,SColor,I;
    char A;
public:
    int ID;
    char name[3];
    bool Select;
    bool Occupied;
    Seat(int x, int y,int color=YELLOW,int scolor = GREEN, int Id = 0,char a ='A',int i=1);
    void Draw(int color = YELLOW);
    void Highlight();
};
void Seat::Seat(int x, int y,int color,int scolor, int Id,char a,int i)
{
    X=x;
    Y=y;
    ID=Id;
    Color = color;
    SColor = scolor;
    I=i;
    A=a;
    Select=false;
    Occupied = false;
    name[0]=A;
    char b[10];
    itoa(I,b,10);
    name[1]=b[0];
    //strcat(name,b);
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
            if(debug_mode)
            {
		cout<<Caption<<"deleted";
                getch();
	    }
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
    textbox[currentitem]->Highlight(char(196));
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
             textbox[(current_item+1)]->Highlight(char(205));
        }
	else if(current_item ==itemnumber)
        {
	     currentitem = 0;
	     textbox[currentitem]->Highlight(char(205));
	}
	}
          break;
	  case UP:
           {
        if(current_item>0)
	{
             currentitem--;
             textbox[currentitem]->Highlight(char(205));
	}
        else if(currentitem == 0)
	{
	     currentitem = itemnumber;
	     textbox[currentitem]->Highlight(char(205));
	}
           }
	break;
    }
}
void Menu::EnableClickHandler(int current_item)
{
    textbox[current_item]->EnableClickHandler();
}
//Menu *menu[30];
int Navigate(Menu menu)
{
    char a,b;
    int p;
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
                    menu.Scroll(currentitem,DOWN); 

        }
                break;
		case UP:
                case RIGHT:
                {
		    menu.Scroll(currentitem,UP);
                    
		}
		break;
	    }// switch b ends
	    }// case :0 ends
            break;
	    case 13:{
                return menu.ReturnID(currentitem);
            }
	    break;
            case 'e':
            exit(0);
	    break;
            // default:
	    //     return (int)a;
	    // break;
	}// switch a ends
    }while(a!='b');
}
void welcome()
{
    clrscr();
    _setcursortype(_NOCURSOR);
    //flushall();
    //currentmenu=0;
    TextBox *pAdmin = new TextBox(30,5,20,1,"ADMIN",0,CYAN,0,AdminLogin);
    TextBox *pCustomer = new TextBox(30,8,20,1,"CUSTOMER",0,CYAN,1,Customerlogin);
    Menu mWelcome(0,"WELCOME");
    mWelcome.AddItem(pAdmin);
    mWelcome.AddItem(pCustomer);
    mWelcome.Draw();
    switch(Navigate(mWelcome))
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
                CustomerIndex();

            else {Customerlogin();}
        }
	break;
    }
}

void AdminSignUp()
{
    clrscr();
    _setcursortype(_NOCURSOR);
    textcolor(RED);
    //window(6,21,80,25);
    gotoxy(6,21);
    for(int i=0;i<70;i++)
    {
	    cprintf("%c",219);
	    delay(50);
    }
    //window(6,23,55,25);
    gotoxy(6,23);
    cprintf("Loaded! Press any key to proceed...");
    getch();
    //flushall();
    clrscr();
    //window(1,1,80,25);
    textcolor(WHITE);
    currentmenu = 1;
    gotoxy(6,6);
    cout<<"Name: ";
    gotoxy(6,9);
    cout<<"Username: ";
    gotoxy(6,12);
    cout<<"Password: ";
    gotoxy(6,15);
    cout<<"Phone Number: ";
    gotoxy(6,18);
    cout<<"Email Id: ";
    TextBox *pName = new TextBox(20,5,50,1,"",0,YELLOW,0,AdminSignUp);
    TextBox *pUsername = new TextBox(20,8,50,1,"",0,GREEN,1,AdminSignUp);
    TextBox *pPassword = new TextBox(20,11,50,1,"",0,YELLOW,2,AdminSignUp);
    TextBox *pPhone = new TextBox(20,14,50,1,"",0,GREEN,3,AdminSignUp);
    TextBox *pemail = new TextBox(20,17,50,1,"",0,YELLOW,4,AdminSignUp);
    TextBox *pNext = new TextBox(30,21,20,1,"NEXT",0,CYAN,5,welcome);
    pName->SetReadOnly(false);
    pUsername->SetReadOnly(false);
    pPhone->SetReadOnly(false);
    pemail->SetReadOnly(false);
    pPassword->SetReadOnly(false);

    Menu pAdminSignUp(1,"ADMIN SIGN UP");
    pAdminSignUp.AddItem(pName);
    pAdminSignUp.AddItem(pUsername);
    pAdminSignUp.AddItem(pPassword);
    pAdminSignUp.AddItem(pPhone);
    pAdminSignUp.AddItem(pemail);
    pAdminSignUp.AddItem(pNext);
    pAdminSignUp.Draw();
    pPassword->HideText(true);

    if(Navigate(pAdminSignUp)==5){
    ADMIN Admin;
    Admin.inputdata(pName->GetText(),pUsername->GetText(),pPassword->GetText(),pemail->GetText(),pPhone->GetText());
    fstream fil;
    fil.open("admintext.dat",ios::binary|ios::app);
    fil.write((char*)&Admin,sizeof(Admin));
    fil.close();
    pAdminSignUp.EnableClickHandler(currentitem);
    }
}
void CustomerSignUp()
{
    clrscr();
    _setcursortype(_NOCURSOR);
    //flushall();
    //currentmenu = 1;
    gotoxy(6,6);
    cout<<"Name: ";
    gotoxy(6,9);
    cout<<"Username: ";
    gotoxy(6,12);
    cout<<"Password: ";
    gotoxy(6,15);
    cout<<"Phone Number: ";
    gotoxy(6,18);
    cout<<"Email Id: ";
    TextBox *pName = new TextBox(20,5,50,1,"",0,YELLOW,0,CustomerSignUp);
    TextBox *pUsername = new TextBox(20,8,50,1,"",0,GREEN,1,CustomerSignUp);
    TextBox *pPassword = new TextBox(20,11,50,1,"",0,YELLOW,2,CustomerSignUp);
    TextBox *pPhone = new TextBox(20,14,50,1,"",0,GREEN,3,CustomerSignUp);
    TextBox *pemail = new TextBox(20,17,50,1,"",0,YELLOW,4,CustomerSignUp);
    TextBox *pNext = new TextBox(40,22,20,1,"NEXT",0,CYAN,5,Customerlogin);
    TextBox *pBack = new TextBox(10,22,20,1,"BACK",0,CYAN,6,Customerlogin);
    pName->SetReadOnly(false);
    pUsername->SetReadOnly(false);
    pPhone->SetReadOnly(false);
    pemail->SetReadOnly(false);
    pPassword->SetReadOnly(false);

    Menu mCustomerSignUp(1,"CUSTOMER SIGN UP");
    mCustomerSignUp.AddItem(pName);
    mCustomerSignUp.AddItem(pUsername);
    mCustomerSignUp.AddItem(pPassword);
    mCustomerSignUp.AddItem(pPhone);
    mCustomerSignUp.AddItem(pemail);
    mCustomerSignUp.AddItem(pNext);
    mCustomerSignUp.AddItem(pBack);
    mCustomerSignUp.Draw();
    pPassword->HideText(true);

    switch(Navigate(mCustomerSignUp))
    {
	case 6:
	    mCustomerSignUp.EnableClickHandler(currentitem);
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
	    mCustomerSignUp.EnableClickHandler(currentitem);
	break;
    }

}
void Customerlogin()
{
    clrscr();
    _setcursortype(_NOCURSOR);
    gotoxy(18,6);
    cout<<"Username: ";
    gotoxy(18,9);
    cout<<"Password: ";
    TextBox *pUsername = new TextBox(30,5,20,1,"",0,YELLOW,0,Customerlogin);
    TextBox *pPassword = new TextBox(30,8,20,1,"",0,GREEN,1,Customerlogin);
    TextBox *pCustomerSignUp = new TextBox(30,11,20,1,"New Here, SIGN UP",4,LIGHTGREEN,1,CustomerSignUp);
    TextBox *pNext = new TextBox(50,15,20,1,"NEXT",0,CYAN,2,welcome);
    TextBox *pBack = new TextBox(10,15,20,1,"BACK",0,CYAN,3,welcome);
    pUsername->SetReadOnly(false);
    pPassword->SetReadOnly(false);
    Menu mCustomerlogin(2,"Customer Login");
    mCustomerlogin.AddItem(pUsername);
    mCustomerlogin.AddItem(pPassword);
    mCustomerlogin.AddItem(pCustomerSignUp);
    mCustomerlogin.AddItem(pNext);
    mCustomerlogin.AddItem(pBack);
    mCustomerlogin.Draw();
    pPassword->HideText(true);
    switch(Navigate(mCustomerlogin))
    {
	case 3:
	    mCustomerlogin.EnableClickHandler(currentitem);
	break;
	case 2:
	{
	    if(CheckFile(pUsername->GetText(),pPassword->GetText())==1)
	    {
		Customer_LoggedIn =true;
		CustomerIndex();
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
	    mCustomerlogin.EnableClickHandler(currentitem);
	break;
    }
}
void AdminLogin()
{
    clrscr();
    _setcursortype(_NOCURSOR);
    gotoxy(18,6);
    cout<<"Username: ";
    gotoxy(18,9);
    cout<<"Password: ";
    TextBox *pUsername = new TextBox(30,5,20,1,"",0,YELLOW,0,AdminLogin);
    TextBox *pPassword = new TextBox(30,8,20,1,"",0,GREEN,1,AdminLogin);
    TextBox *pNext = new TextBox(50,12,20,1,"NEXT",0,CYAN,2,AdminHome);
    TextBox *pBack = new TextBox(10,12,20,1,"BACK",0,CYAN,3,welcome);
    pUsername->SetReadOnly(false);
    pPassword->SetReadOnly(false);
    Menu mAdminLogin(2,"Admin Login");
    mAdminLogin.AddItem(pUsername);
    mAdminLogin.AddItem(pPassword);
    mAdminLogin.AddItem(pNext);
    mAdminLogin.AddItem(pBack);
    mAdminLogin.Draw();
    pPassword->HideText(true);

    switch(Navigate(mAdminLogin))
    {
	case 3:
	    mAdminLogin.EnableClickHandler(currentitem);
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
	    mAdminLogin.EnableClickHandler(currentitem);
	break;
    }

}

void AdminHome()
{
    clrscr();
    _setcursortype(_NOCURSOR);
    TextBox *M_Settings = new TextBox(25,5,30,1,"Movie Settings",0,YELLOW,0,Movie_Settings);
    TextBox *T_Settings = new TextBox(25,8,30,1,"Theatre Settings",0,YELLOW,1,welcome);
    TextBox *D_Settings = new TextBox(25,11,30,1,"Database Settings",0,YELLOW,2,Database_Settings);
    TextBox *pAbout = new TextBox(25,14,30,1,"ABOUT",0,CYAN,3,about);
    TextBox *pBack = new TextBox(1,23,20,1,"BACK",0,CYAN,4,AdminLogin);
    Menu mAdminHome(3,"Hello Admin");
    mAdminHome.AddItem(M_Settings);
    mAdminHome.AddItem(T_Settings);
    mAdminHome.AddItem(D_Settings);
    mAdminHome.AddItem(pAbout);
    mAdminHome.AddItem(pBack);
    mAdminHome.Draw();
    switch(Navigate(mAdminHome))
    {
	case 4:

	    window(24,24,50,25);
	    clrscr();
	    gotoxy(1,1);
	    cprintf("Do you want to LOG OUT(y/n)");
		if(tolower(getch())=='y')
		{
		    window(20,24,50,25);
		    clrscr();
		    window(1,1,80,25);
		    Admin_LoggedIn=false;
		    mAdminHome.EnableClickHandler(currentitem);
		    break;
		}
		else{
		    window(1,1,80,25);
		    AdminHome();
		}

	break;
	default:
	    mAdminHome.EnableClickHandler(currentitem);
	break;
    }
}

void CustomerIndex()
{
    clrscr();
    _setcursortype(_NOCURSOR);
    TextBox *NewT = new TextBox(25,6,30,1,"Book New Ticket",0,YELLOW,0,CustomerHome);
    TextBox *CancelT = new TextBox(25,9,30,1,"Cancel Ticket",0,YELLOW,1,CancelTicket);
    TextBox *CBStatus = new TextBox(25,12,30,1,"Change Password",0,YELLOW,2,ChangePassword);
    TextBox *VBHistory = new TextBox(25,15,30,1,"View Booking History",0,YELLOW,3,ViewBookingHistory);
    TextBox *ciBack = new TextBox(1,23,20,1,"Sign Out",0,CYAN,4,Customerlogin);

    Menu mCustomerIndex(4,"Customer Home");
    mCustomerIndex.AddItem(NewT);
    mCustomerIndex.AddItem(CancelT);
    mCustomerIndex.AddItem(CBStatus);
    mCustomerIndex.AddItem(VBHistory);
    mCustomerIndex.AddItem(ciBack);
    mCustomerIndex.Draw();
    switch(Navigate(mCustomerIndex))
    {
	case 4:

	    window(24,24,50,25);
	    clrscr();
	    gotoxy(1,1);
	    cprintf("Do you want to LOG OUT(y/n)");
		if(tolower(getch())=='y')
		{
		    window(20,24,50,25);
		    clrscr();
		    window(1,1,80,25);
		    Customer_LoggedIn=false;
		    mCustomerIndex.EnableClickHandler(currentitem);
		    break;
		}
		else{
		    window(1,1,80,25);
		    CustomerIndex();
		}

	break;
	default:
	    mCustomerIndex.EnableClickHandler(currentitem);
	break;
    }
}
void CustomerHome()
{
    clrscr();
    window(1,1,80,25);
    //clrscr();
    _setcursortype(_NOCURSOR);
    MOVIE temp1,temp2;
    char n1[80],n2[80];
    fstream fil1,fil2;
    fil1.open("movie1.dat",ios::binary|ios::in);
    fil1.read((char *)&temp1,sizeof(temp1));
    strcpy(n1,temp1.Mn);
//    m1->Clear();
//    m1->SetText(temp.Mn);
    //fil1.close();
    fil2.open("movie2.dat",ios::binary|ios::in);
    fil2.read((char *)&temp2,sizeof(temp2));
    strcpy(n2,temp2.Mn);
//    m2->Clear();
//    m2->SetText(temp.Mn);
    fil2.close();
    TextBox *m1 = new TextBox(15,10,20,1,n1,0,5,0,EnterSeats);
    TextBox *m2 = new TextBox(40,10,20,1,n2,0,5,1,EnterSeats);
    TextBox *pBack = new TextBox(1,23,8,1,"BACK",0,CYAN,2,CustomerIndex);
    Menu mCustomerHome(5,"Now Playing");
    mCustomerHome.AddItem(m2);
    mCustomerHome.AddItem(m1);
    mCustomerHome.AddItem(pBack);
    mCustomerHome.Draw();
    switch(Navigate(mCustomerHome))
    {
	case 0: //fstream fil3;
		//fil3.open("movie1.dat",ios::in|ios::binary);
		//while(fil1.read((char*)&Movie,sizeof(Movie)))
		Choice=temp1;
        strcpy(Choice.CustUserId,current_customer.Username);
		fil1.close();
		fil2.close();
		mCustomerHome.EnableClickHandler(currentitem);
		break;
	case 1: //fstream fil4;
		//fil4.open("movie2.dat",ios::in|ios::binary);
		//while(fil4.read((char*)&Movie,sizeof(Movie)))
		Choice=temp2;
        strcpy(Choice.CustUserId,current_customer.Username);
		fil1.close();
		fil2.close();
		mCustomerHome.EnableClickHandler(currentitem);
		break;
	// case 4:
	// {
	// 	window(20,24,50,25);
	// 	clrscr();
	// 	gotoxy(1,1);
	// 	cprintf("Do you want to LOG OUT(y/n)");
	// 	if(tolower(getch())=='y')
	// 	{
	// 	    window(20,24,50,25);
	// 	    clrscr();
	// 	    window(1,1,80,25);
	// 	    Customer_LoggedIn=false;
	// 	    mCustomerHome.EnableClickHandler(currentitem);
	// 	    break;
	// 	}
	// 	else{
	// 	    window(1,1,80,25);
	// 	    CustomerHome();
	// 	}
	// }
	break;
	default:
	    mCustomerHome.EnableClickHandler(currentitem);
	break;
    }
    //getch();

}

void Movie_Settings()
{
    clrscr();
    _setcursortype(_NOCURSOR);
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

    Menu mMovie_Settings(4,"Movie Settings");
    mMovie_Settings.AddItem(pName1);
    mMovie_Settings.AddItem(pPrice1);
    mMovie_Settings.AddItem(pTime1);
    mMovie_Settings.AddItem(pName2);
    mMovie_Settings.AddItem(pPrice2);
    mMovie_Settings.AddItem(pTime2);
    mMovie_Settings.AddItem(pSubmit);
    mMovie_Settings.AddItem(pBack);

    MOVIE movie1,movie2,temp;
    int found1=0,found2=0;
    fstream fild,fil1,fil2;
    fil1.open("movie1.dat",ios::binary|ios::in);
    fil1.read((char *)&temp,sizeof(temp));
	pName1->Clear();
	pName1->SetText(temp.Mn);
    fil1.close();
    fil2.open("movie2.dat",ios::binary|ios::in);
    fil2.read((char *)&temp,sizeof(temp));
	pName2->Clear();
	pName2->SetText(temp.Mn);
    fil2.close();

    mMovie_Settings.Draw();

    switch(Navigate(mMovie_Settings))
    {
	case 6:
	    strcpy(movie1.Mn,pName1->GetText());
	    strcpy(movie1.Timing,pTime1->GetText());
	    movie1.Price=atof(pPrice1->GetText());
	    strcpy(movie2.Mn,pName2->GetText());
	    strcpy(movie2.Timing,pTime2->GetText());
	    movie2.Price=atof(pPrice2->GetText());
	    fild.open("database.dat",ios::binary|ios::in);
	    fil1.open("movie1.dat",ios::binary|ios::out);
	    fil2.open("movie2.dat",ios::binary|ios::out);
	    while(fild.read((char *)&temp,sizeof(temp)))
	    {
		if(strcmpi(movie1.Mn,temp.Mn)==0)
		    found1=1;
		if(strcmpi(movie2.Mn,temp.Mn)==0)
		    found2=1;
	    }
	    if(found1&&found2)
	    {
		fil1.write((char *)&movie1,sizeof(movie1));
		fil2.write((char *)&movie2,sizeof(movie2));
	    }
	    else if(found1 && !found2)
	    {
		window(5,22,80,22);
		gotoxy(1,1);
		cout<<"Movie2 doesn't exists. Enter new movie in Database Settings. press Enter";
		getch();
		window(1,1,80,25);
	    }
	    else if(found2 && !found1)
	    {
		window(5,22,80,22);
		gotoxy(1,1);
		cout<<"Movie1 doesn't exists. Enter new movie in Database Settings. press Enter";
		getch();
		window(1,1,80,25);
	    }
	    else{
		window(5,22,80,22);
		gotoxy(1,1);
		cout<<"Movies dont exist. Enter new movie in Database Settings. press Enter";
		getch();
		window(1,1,80,25);
	    }

	    fild.close();
	    fil1.close();
	    fil2.close();
	    AdminHome();
	    //menu[currentmenu].EnableClickHandler(currentitem);
	break;
	case 7:
	    //
	    AdminHome();
	break;
	default:
	    mMovie_Settings.EnableClickHandler(currentitem);
	break;
    }
}
void Database_Settings()
{
    clrscr();
    _setcursortype(_NOCURSOR);
    textcolor(GREEN);
    gotoxy(40,7);
    cprintf("%s","Movie :");
    gotoxy(11,8);
    cprintf("%s","Name");
    TextBox *pName1 = new TextBox(11,9,68,1,"NAME",0,YELLOW,0,welcome);
    pName1->SetReadOnly(false);
    gotoxy(11,12);
    cprintf("%s","Timings");
    TextBox *pTime1 = new TextBox(11,13,10,1,"TIME",0,YELLOW,1,welcome);
    pTime1->SetReadOnly(false);
    gotoxy(24,12);
    cprintf("%s","Price");
    TextBox *pPrice1 = new TextBox(24,13,10,1,"PRICE",0,YELLOW,2,welcome);
    pPrice1->SetReadOnly(false);
    // gotoxy(1,13);
    // cprintf("%s","Movie 2 :");
    // gotoxy(25,13);
    // cprintf("%s","NAME");
    // TextBox *pName2 = new TextBox(11,14,68,1,"NAME",0,YELLOW,3,welcome);
    // pName2->SetReadOnly(false);
    // gotoxy(11,17);
    // cprintf("%s","Timings");
    // TextBox *pTime2 = new TextBox(11,18,10,1,"TIME",0,YELLOW,4,welcome);
    // pTime2->SetReadOnly(false);
    // gotoxy(24,17);
    // cprintf("%s","Price");
    // TextBox *pPrice2 = new TextBox(24,18,10,1,"PRICE",0,YELLOW,5,welcome);
    // pPrice2->SetReadOnly(false);

    TextBox *pSubmit = new TextBox(50,23,20,1,"SUBMIT",0,CYAN,6,AdminHome);
    TextBox *pBack = new TextBox(10,23,20,1,"BACK",0,CYAN,7,AdminHome);

    Menu mDatabase_Settings(4,"Database Settings");
    mDatabase_Settings.AddItem(pName1);
    mDatabase_Settings.AddItem(pPrice1);
    mDatabase_Settings.AddItem(pTime1);
    //mDatabase_Settings.AddItem(pName2);
    // mDatabase_Settings.AddItem(pPrice2);
    // mDatabase_Settings.AddItem(pTime2);
    mDatabase_Settings.AddItem(pSubmit);
    mDatabase_Settings.AddItem(pBack);
    mDatabase_Settings.Draw();
    MOVIE movie,temp;
    int found = 0;
    fstream fil;

    switch(Navigate(mDatabase_Settings))
    {
	case 6:
	    strcpy(movie.Mn,pName1->GetText());
	    strcpy(movie.Timing,pTime1->GetText());
	    movie.Price=atof(pPrice1->GetText());
	    fil.open("database.dat",ios::binary|ios::in);
	    while(!found && fil.read((char *)&temp,sizeof(temp)))
	    {
		if(strcmpi(movie.Mn,temp.Mn)==0)
		    found=1;
	    }
	    fil.close();
	    fil.open("database.dat",ios::binary|ios::app);
	    if(!found)
		fil.write((char *)&movie,sizeof(movie));
	    else{
		window(20,15,50,15);
		gotoxy(1,1);
		cout<<"Movie already exists. Press enter";
		getch();
		clrscr();
		window(1,1,80,25);
	    }
	    fil.close();
	    AdminHome();
	    //menu[currentmenu].EnableClickHandler(currentitem);
	break;
	case 7:

	    AdminHome();
	break;
	default:
	    mDatabase_Settings.EnableClickHandler(currentitem);
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
    int Seats_Needed=1;
    TextBox *nos = new TextBox(30,10,20,1,"",0,GREEN,0,EnterSeats);
    TextBox *pNext = new TextBox(72,23,8,1,"NEXT",0,CYAN,2,welcome);
    TextBox *pBack = new TextBox(1,23,8,1,"BACK",0,CYAN,3,CustomerHome);
    nos->SetReadOnly(false);
    Menu mEnterSeats(5,"Enter number of Seats");
    mEnterSeats.AddItem(nos);
    mEnterSeats.AddItem(pNext);
    mEnterSeats.AddItem(pBack);
    mEnterSeats.Draw();

    switch(Navigate(mEnterSeats))
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
		EnterSeats();
	    }
	}
	break;
	default:
	{
	    mEnterSeats.EnableClickHandler(currentitem);
	}
	break;
    }
}
void seats(int Seats_Needed)
{
    //chkadmin();
    clrscr();
    _setcursortype(_NOCURSOR);
    bool manualmode = false;
    Choice.Seats = Seats_Needed;
    cout<<"Do you want to select seats manually?(y/n)";
    if(tolower(getch())=='y')
    {
	manualmode = true;
    }
    clrscr();
    TextBox *pNext = new TextBox(72,23,8,1,"NEXT",0,CYAN,2,CustomerConfirm);
    TextBox *pBack = new TextBox(1,23,8,1,"BACK",0,CYAN,3,CustomerHome);
    window(1,1,80,25);
    Menu mseats(6,"Seats");
    mseats.AddItem(pNext);
    mseats.AddItem(pBack);
	int d=20;
	gotoxy(d,22);
	for(d;d<=60;d++)
		cprintf("%c",220);
    mseats.Draw();
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
    //             seat[i].Draw();
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
				current_customer.myseats[j]=1;
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
				if(!(seat[i]->Occupied)&&!(seat[i]->Select))
				{
					seat[i]->Select=true;
					seat[i]->Draw();
					seats_selected++;
				}
				else if(!(seat[i]->Occupied)&&(seat[i]->Select))
				{
					seat[i]->Select=false;
					seats_selected--;
					seat[i]->Draw();
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
				current_customer.myseats[j]=1;
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
    switch(Navigate(mseats))
    {
	default:
	    mseats.EnableClickHandler(currentitem);
	break;
    }
}
void CustomerConfirm()
{
    clrscr();
    _setcursortype(_NOCURSOR);
    //TextBox *cc = new TextBox(30,10,20,1,Choice.Mn,0,CYAN,1,CustomerConfirm);
    TextBox *ccNext = new TextBox(72,23,8,1,"NEXT",0,CYAN,2,welcome);
    TextBox *ccBack = new TextBox(1,23,8,1,"BACK",0,CYAN,3,EnterSeats);
    Menu mCustomerConfirm(7,"Confirm Your Booking");
    //mCustomerConfirm.AddItem(cc);
    mCustomerConfirm.AddItem(ccNext);
    mCustomerConfirm.AddItem(ccBack);
    mCustomerConfirm.Draw();
    time_t t=time(NULL);
    char *time=ctime(&t),temp[50],name[50];
    strcpy(temp,time);
    int j,p=0;
    for(int i=0;i<=strlen(temp);i++)
    {
	if((isalpha(temp[i])==0)&&(isspace(temp[i])==0)&&(ispunct(temp[i])==0))
	{
		name[j]=temp[i];
		j++;
	}
    }
    name[0]='M';
    strcpy(Choice.ID,name);
    name[strlen(name)-1]='.';
    strcat(name,"txt");
    textcolor(WHITE);
    float Subtotal = Choice.Seats*Choice.Price;
    gotoxy(15,7);
    cout<<"  	        Movie Time";
    gotoxy(15,8);
    cout<<"               Customer Receipt";
    gotoxy(15,9);
    cout<<"Booking Id: "<<Choice.ID<<endl;
    gotoxy(15,10);
    cout<<"-------------------------------------------";
    gotoxy(15,11);
    cout<<"Movie Selected  	: "<<Choice.Mn;
    gotoxy(15,12);
    cout<<"Time	        : "<<Choice.Timing;
    gotoxy(15,13);
    cout<<"Price(Per Seat} 	: "<<Choice.Price;
    gotoxy(15,14);
    cout<<"No. Of Seats   	: "<<Choice.Seats;
    gotoxy(15,15);
    cout<<"Seat(s) Selected	: ";
	for(p=0;p<25;p++)
		if(current_customer.myseats[p]==1)
			cout<<seat[p]->name<<" ";
	gotoxy(15,16);
	cout<<"-------------------------------------------";
    gotoxy(15,17);
    cout<<"   		       Subtotal : "<<Subtotal;
    gotoxy(15,18);
    cout<<"   		       	    GST : 18.5%";
    gotoxy(15,19);
    cout<<"   	       Convinience Fees : 25";
    gotoxy(15,20);
    cout<<"   	         Service Charge : 2.5%";
    gotoxy(15,21);
    cout<<"___________________________________________";
    gotoxy(15,22);
    Choice.CustFinalPrice=Subtotal*(1.21)+25;
    cout<<"	     		    Total Price : "<<Choice.CustFinalPrice;
    switch(Navigate(mCustomerConfirm))
    {
	case 2: Choice.Status=true;
	 fstream fil;
	 fil.open(name,ios::out);
	 fil<<"  	           Movie Time"<<endl;
	 fil<<"               Customer Receipt"<<endl;
	 fil<<"	   "<<time;
	 fil<<"Booking Id : "<<Choice.ID<<endl;
	 fil<<"-------------------------------------------"<<endl;
	 fil<<"Movie Selected  	: "<<Choice.Mn<<endl;
	 fil<<"Time	       		: "<<Choice.Timing<<endl;
	 fil<<"Price(Per Seat} 	: "<<Choice.Price<<endl;
	 fil<<"No. Of Seats   	        :  "<<Choice.Seats<<endl;
	 fil<<"Seat(s) Selected        : ";
	 for(p=0;p<25;p++)
	 {
		if(current_customer.myseats[p]==1)
			fil<<seat[p]->name<<" ";
	 }
	 fil<<endl;
	 fil<<"-------------------------------------------"<<endl;
	 fil<<"   		       Subtotal : "<<Subtotal<<endl;
	 fil<<"   		       	    GST : 18.5%"<<endl;
	 fil<<"   	       Convinience Fees : 100"<<endl;
	 fil<<"   	         Service Charge : 2.5%"<<endl;
	 fil<<"___________________________________________"<<endl;
	 fil<<"	     		 Total Price : "<<Choice.CustFinalPrice<<endl;
	 fil<<"User Details:"<<endl;
     fil<<current_customer.Name<<endl<<current_customer.Phone<<endl<<current_customer.EMail;
     fil.close();
	 clrscr();
	 gotoxy(12,30);
	 cout<<"Thank you!!\nYour Receipt has been Saved to:"<<name;
	 getch();
	 {
	 fstream fil1;
	 fil1.open("Info.dat",ios::app|ios::binary);
	 fil1.write((char*)&Choice,sizeof(Choice));
	 fil1.close();
	 }
	 CustomerIndex();
	 break;
	 case 3:
		for(int i=0;i<25;i++)
			if(current_customer.myseats[i]==1)
			{
                seat[i]->Occupied=false;
                current_customer.myseats[i]=0;
            }
		CustomerIndex();


	 break;
	default:
	{
	    mCustomerConfirm.EnableClickHandler(currentitem);
	}
	break;
    }
}

void CancelTicket()
{
    clrscr();
    _setcursortype(_NOCURSOR);
    gotoxy(5,11);
    cout<<"ENTER YOUR BOOKING ID:";
    TextBox *cid = new TextBox(30,10,20,1,"",0,GREEN,0,CancelTicket);
    TextBox *cidNext = new TextBox(72,23,8,1,"NEXT",0,CYAN,2,CustomerHome);
    TextBox *cidBack = new TextBox(1,23,8,1,"BACK",0,CYAN,3,CustomerHome);
    cid->SetReadOnly(false);
    Menu mCancelTicket(5,"Cancel Ticket");
    mCancelTicket.AddItem(cid);
    mCancelTicket.AddItem(cidNext);
    mCancelTicket.AddItem(cidBack);
    mCancelTicket.Draw();
    int found=0;
    MOVIE Movie;
    switch(Navigate(mCancelTicket))
    {
	case 2:
	{
		fstream fil;
		fil.open("Info.dat",ios::out|ios::in|ios::binary);
		while(!found && fil.read((char*)&Movie,sizeof(Movie)))
		{
			if((strcmpi(Movie.ID,cid->GetText())==0)&&(Movie.Status==true))
			{
				Movie.Status=false;
				fil.seekp(fil.tellg()-sizeof(Movie),ios::beg);
				fil.write((char*)&Movie,sizeof(Movie));
				found++;
			}
		}
		if(!found)
		{
			clrscr();
			cout<<"Booking Not Found!";
			getch();
		}
		else
		{
			clrscr();
			cout<<"Ticket Successfully Cancelled...";
			getch();
		}
		fil.close();
		CustomerIndex();
		//mCancelTicket.EnableClickHandler(currentitem);
	}
	break;
	default:
	{
	    CustomerIndex();
	    //mCancelTicket.EnableClickHandler(currentitem);
	}
	break;
    }
}
void ChangePassword()
{
    clrscr();
    _setcursortype(_NOCURSOR);
    gotoxy(5,11);
    cout<<"ENTER OLD PASSWORD:";
    gotoxy(5,16);
    cout<<"ENTER NEW PASSWORD";
    //TextBox *cpu = new TextBox(30,5,20,1,"",0,GREEN,0,ChangePassword);
    TextBox *cpop = new TextBox(30,10,20,1,"",0,GREEN,0,ChangePassword);
    TextBox *cpnp = new TextBox(30,15,20,1,"",0,GREEN,0,ChangePassword);
    TextBox *cbsNext = new TextBox(72,23,8,1,"NEXT",0,CYAN,2,CustomerIndex);
    TextBox *cbsBack = new TextBox(1,23,8,1,"BACK",0,CYAN,3,CustomerIndex);
    //cpu->SetReadOnly(false);
    cpop->SetReadOnly(false);
    cpop->HideText(true);
    cpnp->SetReadOnly(false);
    cpnp->HideText(true);
    Menu mChangePassword(5,"Change Password");
    //mChangePassword.AddItem(cpu);
    mChangePassword.AddItem(cpop);
    mChangePassword.AddItem(cpnp);
    mChangePassword.AddItem(cbsNext);
    mChangePassword.AddItem(cbsBack);
    mChangePassword.Draw();
    int found=0;
    switch(Navigate(mChangePassword))
    {
    	case 2:
    	{
    		if(current_customer.CheckPassword(cpop->GetText())==1)
            {
                CUSTOMER temp;
                fstream fil;
                fil.open("Customertext.dat",ios::in|ios::out|ios::binary);
                while((!found)&&fil.read((char*)&temp,sizeof(temp)))
                {
                    if(strcmp(temp.Username,current_customer.Username)==0)
                    {
                        found++;
                    }
                }
                current_customer.ChangePassword(cpnp->GetText());
                fil.seekp(fil.tellg()-sizeof(temp),ios::beg);
                fil.write((char*)&current_customer,sizeof(current_customer));
    	        fil.close();
    	        gotoxy(20,22);
    	        textcolor(GREEN);
    	        cprintf("Password Changed Successfully!");
    	        getch();
    	    }
    	   else if(current_customer.CheckPassword(cpop->GetText())==0)
    	    {
    	        gotoxy(20,22);
    	        textcolor(RED);
    	        cprintf("Incorrect Password");
    	        getch();
            }
            CustomerIndex();
    	}
	    break;
	    default:
	    {
	        CustomerIndex();
	       //mChangePassword.EnableClickHandler(currentitem);
	    }
	    break;
    }
}

void ViewBookingHistory()
{
    clrscr();
    _setcursortype(_NOCURSOR);
    TextBox *vbhBack = new TextBox(1,23,8,1,"BACK",0,CYAN,0,CustomerIndex);
    Menu mViewBookingHistory(5,"Booking History");
    mViewBookingHistory.AddItem(vbhBack);
    mViewBookingHistory.Draw();
    int found=0;
    MOVIE Movie;
    fstream fil;
	fil.open("Info.dat",ios::in|ios::binary);
    int i=6;
	while((fil.read((char*)&Movie,sizeof(Movie))))
	{
		if(strcmpi(Movie.CustUserId,current_customer.Username)==0)
		{
			gotoxy(1,4);
			cout<<" S.No."<<setw(16)<<"Booking ID"<<setw(19)<<"Movie Name"<<setw(11)<<"Time"<<setw(10)<<"Price"<<setw(11)<<"Status";
			for(int j=0;j<78;j++)
			{
				gotoxy(j+2,5);
				cprintf("%c",205);
			}
			//for(int i=5;i<=24;i++)
			//{
				char status[10];
				if(Movie.Status==true)
				strcpy(status,"Confirm");
				else if(Movie.Status==false)
				strcpy(status,"Cancelled");
				gotoxy(2,i);
				cout<<setw(3)<<found+1<<char(186)<<setw(19)<<Movie.ID<<char(186)<<setw(20)<<Movie.Mn<<char(186)<<setw(8)<<Movie.Timing<<char(186)<<setw(9)<<Movie.CustFinalPrice<<char(186)<<setw(12)<<status;
				found++;
				i++;
			//	}
		}

		// else if((strcmp(Movie.ID,cbs->GetText())==0)&&(Movie.Status==false))
		// {
		// 	clrscr();
		// 	cout<<"Your Ticket Has Been Cancelled...";
		// 	getch();
		// 	found++;
		// }
		}
		if(found==0)
		{
//			clrscr();
			gotoxy(5,5);
			cout<<"No Booking Found Under Your ID. Lets Get Going!";
			getch();
		}
		else
		{
		}

//	    CustomerIndex();

		//mChangePassword.EnableClickHandler(currentitem);
    
    switch(Navigate(mViewBookingHistory))
    {
        case 0 : CustomerIndex();
                 break;
	}


 //   }
}

void PrintLogo(int i)
{
    
	gotoxy(21,i);
	cout<<char(177)<<char(177)<<"   "<<char(177)<<char(177)<<"                  "<<char(177)<<char(177)<<char(177)<<char(177)<<char(177);
	gotoxy(21,i+1);
	cout<<char(177)<<" "<<char(177)<<" "<<char(177)<<" "<<char(177)<<"                    "<<char(177);
	gotoxy(21,i+2);
	cout<<char(177)<<"  "<<char(177)<<"  "<<char(177)<<" "<<char(177)<<char(177)<<char(177)<<" "<<char(177)<<"   "<<char(177)<<" ";
	cout<<char(177)<<" "<<char(177)<<char(177)<<char(177)<<"    "<<char(177)<<"  "<<char(177)<<" "<<char(177)<<char(177)<<" "<<char(177)<<char(177)<<" "<<char(177)<<char(177)<<char(177);
	gotoxy(21,i+3);
	cout<<char(177)<<"     "<<char(177)<<" "<<char(177)<<" "<<char(177)<<"  "<<char(177)<<" "<<char(177)<<"  "<<char(177)<<" "<<char(177)<<" "<<char(177)<<"    "<<char(177)<<"  "<<char(177)<<" ";
	cout<<char(177)<<" "<<char(177)<<" "<<char(177)<<" "<<char(177)<<" "<<char(177);
	gotoxy(21,i+4);
	cout<<char(177)<<"     "<<char(177)<<" "<<char(177)<<" "<<char(177)<<"  "<<char(177)<<" "<<char(177)<<"  "<<char(177)<<" "<<char(177)<<"      "<<char(177)<<"  "<<char(177)<<" "<<char(177)<<"   "<<char(177)<<" "<<char(177);
	gotoxy(21,i+5);
	cout<<char(177)<<"     "<<char(177)<<" "<<char(177)<<char(177)<<char(177)<<"   "<<char(177)<<"   "<<char(177)<<" "<<char(177)<<char(177)<<char(177)<<"    "<<char(177)<<"  "<<char(177)<<" " <<char(177)<<"   "<<char(177)<<" "<<char(177)<<char(177)<<char(177);

}
void about()
{
    clrscr();
    _setcursortype(_NOCURSOR);
    TextBox *aBack = new TextBox(1,23,8,1,"BACK",0,CYAN,3,AdminHome);
    Menu mAbout(9,"About Us");
    mAbout.AddItem(aBack);
    mAbout.Draw();
    char ty[30]={'T','h','a','n','k','s',' ','f','o','r',' ','U','s','i','n','g',' ','M','o','v','i','e',' ','T','i','m','e','!'};
    PrintLogo(6);
    for(int p=0;p<30;p++)
    {
	gotoxy(28+p,15);
	textcolor(CYAN);
	cprintf("%c",ty[p]);
	delay(150);
    }
    gotoxy(27,17);
    textcolor(GREEN);
    cprintf("Presented By Shaurya And Rishit");
    switch(Navigate(mAbout))
    {
	default : mAbout.EnableClickHandler(currentitem);
		  break;
    }

}

void main()
{
     int p=0,q=0,r=0,i=1;
     char a='A';

    while(p<25)
    {
	for(q = 0;q<5;q++)
            {
		seat[p] = new Seat(20+(10*q),4+r,YELLOW,GREEN,p,a,i);
                seat[p]->Occupied= false;
				p++;
                i++;
            }
        r+=4;
        a++;
        i=1;
    }
    // for(p =0;p<25;p++)
    // {
    //     cout<<seat[p]->name<<" ";
    //}
    // getch();
    chkadmin();
    //EnterSeats();
    for(p =0;p<25;p++)
    {
        delete seat[p];
    }
    clrscr();
    cout<<"Thank You!";
    getch();
}
