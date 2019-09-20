	#ifndef MOUSE_CPP
	#define MOUSE_CPP 
	
	#include "mouse.h"
    
int Navigate::get_status()
{
   return status;
}
void Navigate::begin()
{
     char a;
     while(kbhit())
     {
     	a=getch();
        switch(tolower(a))
        {
            case 0:
            {
                a = getch();
                switch(a)
                {
                    case 80:
                    {
                    	ARROW_UP=true;
                    }
                        break;
                    case 72:
                    {
                    	ARROW_DOWN=true;                       
                    }
                        break;
                    case 13:
                        IsClicked = true;
                        break;
                }
            }
                break;
            case 13:
                IsClicked = true;
                return;
        }
     }
        
}
	
	
	#endif  // MOUSE_CPP