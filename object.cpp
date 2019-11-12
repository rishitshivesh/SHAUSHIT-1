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
bool debug_mode = false;
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
void Database_Settings();
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
    TextBox *pAdmin = new TextBox(30,5,20,1,"ADMIN",0,YELLOW,0,AdminLogin);
    TextBox *pCustomer = new TextBox(30,8,20,1,"CUSTOMER",0,GREEN,1,Customerlogin);
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
    //flushall();
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
    TextBox *pUsername = new TextBox(30,5,20,1,"Username",0,YELLOW,0,Customerlogin);
    TextBox *pPassword = new TextBox(30,8,20,1,"Password",0,GREEN,1,Customerlogin);
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
            mCustomerlogin.EnableClickHandler(currentitem);
        break;
    }
}
void AdminLogin()
{
    clrscr();
    _setcursortype(_NOCURSOR);
    TextBox *pUsername = new TextBox(30,5,20,1,"Username",0,YELLOW,0,AdminLogin);
    TextBox *pPassword = new TextBox(30,8,20,1,"Password",0,GREEN,1,AdminLogin);
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
    TextBox *pAbout = new TextBox(25,14,30,1,"ABOUT",0,CYAN,3,welcome);
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
void CustomerHome()
{
    clrscr();
    window(1,1,80,25);
    //clrscr();
    _setcursortype(_NOCURSOR);
    TextBox *m1 = new TextBox(5,5,10,5,"Movie 1",0,YELLOW,0,EnterSeats);
    TextBox *m2 = new TextBox(50,5,10,5,"Movie 2",0,GREEN,1,EnterSeats);
    TextBox *m3 = new TextBox(5,12,10,5,"Movie 3",0,CYAN,2,EnterSeats);
    TextBox *m4 = new TextBox(50,12,10,5,"Movie 4",0,CYAN,3,EnterSeats);
    TextBox *pBack = new TextBox(1,23,8,1,"BACK",0,CYAN,4,Customerlogin);
    Menu mCustomerHome(3,"Now Playing");
    mCustomerHome.AddItem(m1);
    mCustomerHome.AddItem(m2);
    mCustomerHome.AddItem(m3);
    mCustomerHome.AddItem(m4);
    mCustomerHome.AddItem(pBack);
    mCustomerHome.Draw();
    switch(Navigate(mCustomerHome))
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
                    mCustomerHome.EnableClickHandler(currentitem);
                    break;
                }
                else{
                    window(1,1,80,25);
                    CustomerHome();
                } 
        }
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
    mMovie_Settings.Draw();
    MOVIE movie1,movie2,temp;
    int found1=0,found2=0;
    fstream fild,fil1,fil2;
    
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
    TextBox *nos = new TextBox(30,10,20,1,"Enter Seats",0,GREEN,0,EnterSeats);
    TextBox *pNext = new TextBox(72,23,8,1,"NEXT",0,CYAN,2,welcome);
    TextBox *pBack = new TextBox(1,23,8,1,"BACK",0,CYAN,3,CustomerHome);
    nos->SetReadOnly(false);
    Menu mEnterSeats(4,"Enter number of Seats");
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
    cout<<"Do you want to select seats manually?(y/n)";
    if(tolower(getch())=='y')
    {
        manualmode = true;
    }
    clrscr();
    TextBox *pNext = new TextBox(72,23,8,1,"NEXT",0,CYAN,2,welcome);
    TextBox *pBack = new TextBox(1,23,8,1,"BACK",0,CYAN,3,CustomerHome);
    window(1,1,80,25);
    Menu mseats(5,"Seats");
    mseats.AddItem(pNext);
    mseats.AddItem(pBack);
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
    switch(Navigate(mseats))
    {
        default: 
            mseats.EnableClickHandler(currentitem);
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
    clrscr();
    cout<<"ended";
    getch();
}