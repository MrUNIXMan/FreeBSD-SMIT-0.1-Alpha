/*
 * BSD-SMIT (BSD System Management Interface Tool)
 * 
 * Copyright (C) 2015 by Vincent (MrUNIXMan@lycos.com)
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 * 
 * Software Manager Menu
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pwd.h>
#include <unistd.h>
#include <sys/utsname.h>
#include <ncurses.h>

/* Extended Headerfiles */
#include "include/smitinfo.h"
#include "include/menuinfo.h"


int x, y;

void drawsmitsfwmenu(int smitsfwmenuitem)
{
	int sfwmctr;  /* Software Menu Counter */
	
	char sfwmenutitle[] = "Software management"; /* Title */
	
	
	/* Menu Items for the main menu */
	
	char sfwmenu [SFW_MENU_MAX] [34] = {
		"Install Package from Binary",
		"Remove a preinstalled package",
		"Portsnap the Ports sources",
		"Compile & Install a ports package",
		"Remove a ports package",
		"View installed Software",
		"Show Disk spaces",
		"Help",
		"Quit"
	};
	
	
	
	/* This Section will draw the menu to screen */
	
	 clear();
	 box(stdscr, ACS_VLINE, ACS_HLINE);  /* Box on Stdscr (Standard Screen) */
	 attron(A_BOLD);
	 mvaddstr(1, 27, sfwmenutitle); /* Title for Main menu */
	 mvaddstr(3, 2, submesg); /* Message Below the title */
	 mvaddstr(19,2, FKEY1); /* Bottom Bar */
	 mvaddstr(20,2, FKEY2); /* Bottom Bar */
	 attroff(A_BOLD);  /* Turn off BOLD */

	 /* Print Menu item during highlight */
	 
	 for (sfwmctr=0; sfwmctr <SFW_MENU_MAX; sfwmctr++)
	 {
		if(sfwmctr==smitsfwmenuitem)
			attron(A_REVERSE);
			mvaddstr(5+(sfwmctr*1), 5, sfwmenu[sfwmctr]);
			attroff(A_REVERSE);
		}
	
	/* Refresh the screen */ 
	 refresh();
	
}


/* Main Function to start the Main menu */
int smitsfwmenu(void)
{
	WINDOW *sfwmdlg; /* Makes a Dialog for main menu */
	
	getmaxyx(stdscr, y,x);
	
	int menuitem, menukey;
	
	menuitem = 0;
	
	while(menuitem != 8)
	{
	 drawsmitsfwmenu(menuitem);
	 refresh();
	 do
	 {
		 menukey = getch();
		 switch(menukey)
		 {
		 case KEY_F(1): /* Display Help */
		//	helpfunc();
			break;
			case KEY_F(2): /* Refresh Screen */
			refresh();
			break;
			case KEY_F(9): /* Runs the Shell */
			  endwin();
			  clear();
			 // executedefaultshell();
			   system("/bin/sh");
			  break;
			case KEY_F(10): /* Exits */
			    clear();
			    return 0;
			 case KEY_DOWN:
			  menuitem++;
			  if(menuitem > SFW_MENU_MAX) menuitem = 0;
			  break;
			case KEY_UP:
			  menuitem--;
			  if(menuitem < 0) menuitem = SFW_MENU_MAX-1;
			  break;
			default:
			  break; 
		    }	
	   drawsmitsfwmenu(menuitem);
	   refresh();
	 
	} while(menukey != '\n');
	
	/* If Statments which reflects on menu items goes here */		

		if(menuitem == 0) 
		{
			/* Runs Sysinfo function */
		//	sysinfo(); 
		}
		else if(menuitem == 2)
		{
			//usrmenu();
		}
		else if(menuitem == 4)
		{
			
			//helpfunc();
			
		}
		else if(menuitem == 5)
		{
			sfwmdlg = newwin(5,51,6,15);   /* Dialog Declared at WINDOW */
			box(sfwmdlg, ACS_VLINE, ACS_HLINE);
			
			mvwprintw(sfwmdlg, 1, 16, "About %s", PROG_NAME);
			
			mvwprintw(sfwmdlg, 2, 11, "%s", COPYRIGHT);
			refresh();
			wgetch(sfwmdlg);
			werase(sfwmdlg);
		};	
			
		
	}; /* End of While statements */ 
	
	clear();

	return 0;
	
	
}

