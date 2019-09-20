

	#ifndef __MOUSE_H
	#define __MOUSE_H
	
	#ifndef __GUI_H
	#include "gui.h"
	#endif // __GUI_H

	#include <dos.h>
	#include <ctype.h>
	#include "global.h"


class Navigate
{
  private: 
		
			int status;
		public:

			void begin();
			int get_status();

};
	#endif // __MOUSE_H

