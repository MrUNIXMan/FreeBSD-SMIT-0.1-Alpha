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
 * System Configuration Menu
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

void drawsmitscmenu(int smitscmenuitem)
{
	int scmctr;  /* Software Menu Counter */
	
	char scmenutitle[] = "System Configuration Manager"; /* Title */
	
	
	/* Menu Items for the main menu */
	
	char scmenu [SC_MENU_MAX] [34] = {
		"Edit Boot Loader file",
		"Edit hosts file",
		"Edit rc.conf file",
		"Edit fstab file",
		"Edit Xorg.conf file",
		"Kernel Configuration Manager",	
		"Help",
		"Quit"
	};
	
	
	
	/* This Section will draw the menu to screen */
	
	 clear();
	 box(stdscr, ACS_VLINE, ACS_HLINE);  /* Box on Stdscr (Standard Screen) */
	 attron(A_BOLD);
	 mvaddstr(1, 27, scmenutitle); /* Title for Main menu */
	 mvaddstr(3, 2, submesg); /* Message Below the title */
	 mvaddstr(19,2, FKEY1); /* Bottom Bar */
	 mvaddstr(20,2, FKEY2); /* Bottom Bar */
	 attroff(A_BOLD);  /* Turn off BOLD */

	 /* Print Menu item during highlight */
	 
	 for (scmctr=0; scmctr <SC_MENU_MAX; scmctr++)
	 {
		if(scmctr==smitscmenuitem)
			attron(A_REVERSE);
			mvaddstr(5+(scmctr*1), 5, scmenu[scmctr]);
			attroff(A_REVERSE);
		}
	
	/* Refresh the screen */ 
	 refresh();
	
}


/* Main Function to start the Main menu */
int smitscmenu(void)
{
	WINDOW *scmdlg; /* Makes a Dialog for main menu */
	
	getmaxyx(stdscr, y,x);
	
	int menuitem, menukey;
	
	menuitem = 0;
	
	while(menuitem != 7)
	{
	 drawsmitscmenu(menuitem);
	 refresh();
	 do
	 {
		 menukey = getch();
		 switch(menukey)
		 {
		 case KEY_F(1): /* Display Help */
		//	helpfunc();
			mainmenuhelp();
		
			break;
			case KEY_F(2): /* Refresh Screen */
			refresh();
			break;
			case KEY_F(9): /* Runs the Shell */
			    executedefaultshell();
			  break;
			case KEY_F(10): /* Exits */
			    clear();
			    return 0;
			 case KEY_DOWN:
			  menuitem++;
			  if(menuitem > SC_MENU_MAX) menuitem = 0;
			  break;
			case KEY_UP:
			  menuitem--;
			  if(menuitem < 0) menuitem = SC_MENU_MAX-1;
			  break;
			default:
			  break; 
		    }	
	   drawsmitscmenu(menuitem);
	   refresh();
	 
	} while(menukey != '\n');
	
	/* If Statments which reflects on menu items goes here */		

		if(menuitem == 0) 
		{
			/* Edit Boot Loader */
			edit_loader_conf();
		}
		else if(menuitem == 1)
		{
			edit_hosts();
		}
		else if(menuitem == 2)
		{
			edit_rc_conf();
		}
		else if(menuitem == 3)
		{
			edit_fstab();
		}
		else if(menuitem == 4)
		{
			
			edit_xorg_file();
			
		}
		else if(menuitem == 5)
		{
			kernelmgrmain();
		};	
			
		
	}; /* End of While statements */ 
	
	clear();

	return 0;
	
	
}

