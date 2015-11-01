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

void drawsmitusermenu(int smitusermenuitem)
{
	getmaxyx(stdscr, y,x);
	
	int umctr;  /* Main Menu Counter */
	
	char usermenutitle[] = "Users and Groups management"; /* Title */
	
	
	/* Menu Items for the main menu */
	
	char usermenu [USER_MENU_MAX] [34] = {
		"User Manager",
		"List Logged in Users",
		"User Info",
		"Add a User",
		"Remove a User",
		"Modify a User",
		"Add a Group",
		"Remove a Group",
		"Modify a Group",
		"Help",
		"Quit"
	};
	
	
	
	/* This Section will draw the menu to screen */
	
	 clear();
	 box(stdscr, ACS_VLINE, ACS_HLINE);  /* Box on Stdscr (Standard Screen) */
	 attron(A_BOLD);
	 mvaddstr(1, 27, usermenutitle); /* Title for Main menu */
	 mvaddstr(3, 2, submesg); /* Message Below the title */
	 
	 /* When Resized the Items will move with the window resize */
	 mvaddstr(y-4,2, FKEY1); /* Bottom Bar */
	 mvaddstr(y-3,2, FKEY2); /* Bottom Bar */
	 
	 attroff(A_BOLD);  /* Turn off BOLD */

	 /* Print Menu item during highlight */
	 
	 for (umctr=0; umctr <USER_MENU_MAX; umctr++)
	 {
		if(umctr==smitusermenuitem)
			attron(A_REVERSE);
			mvaddstr(5+(umctr*1), 5, usermenu[umctr]);
			attroff(A_REVERSE);
		}
	
	/* Refresh the screen */ 
	 refresh();
	
}


/* Main Function to start the Main menu */
int smitusermenu(void)
{
	WINDOW *umdlg; /* Makes a Dialog for main menu */
	
	getmaxyx(stdscr, y,x);
	
	int menuitem, menukey;
	
	menuitem = 0;
	
	while(menuitem != 10)
	{
	 drawsmitusermenu(menuitem);
	 refresh();
	 do
	 {
		 menukey = getch();
		 switch(menukey)
		 {
		 case KEY_F(1): /* Display Help */
			usermenuhelp();
			break;
			case KEY_F(2): /* Refresh Screen */
			refresh();
			break;
			case KEY_F(9): /* Runs the Shell */
			  endwin();
			  clear();
				executedefaultshell();
			  break;
			case KEY_F(10): /* Exits */
			    clear();
			    return 0;
			 case KEY_DOWN:
			  menuitem++;
			  if(menuitem > USER_MENU_MAX) menuitem = 0;
			  break;
			case KEY_UP:
			  menuitem--;
			  if(menuitem < 0) menuitem = USER_MENU_MAX-1;
			  break;
			default:
			  break; 
		    }	
	   drawsmitusermenu(menuitem);
	   refresh();
	 
	} while(menukey != '\n');
	
	/* If Statments which reflects on menu items goes here */		
		if(menuitem == 0)
		{
			usermgrmain();
		}

		else if(menuitem == 1) 
		{
			loggedinusers();
		}
		else if(menuitem == 2)
		{
			userinfo();
		}
		else if(menuitem == 3)
		{
			
			adduser();
			
		}
		else if(menuitem == 9)
		{
			umdlg = newwin(5,51,6,15);   /* Dialog Declared at WINDOW */
			box(umdlg, ACS_VLINE, ACS_HLINE);
			
			mvwprintw(umdlg, 1, 16, "About %s", PROG_NAME);
			
			mvwprintw(umdlg, 2, 11, "%s", COPYRIGHT);
			refresh();
			wgetch(umdlg);
			werase(umdlg);
		};	
			
		
	}; /* End of While statements */ 
	
	clear();

	return 0;
	
	
}

