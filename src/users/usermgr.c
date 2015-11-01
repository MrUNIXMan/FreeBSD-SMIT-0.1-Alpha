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
 * User Manager - Interface for managing Users.
 * 
 * Written from Scratch using ideas from FreeBSD mount.c and friends.
 * 
 * Copyright (C) October 2015 by Vincent
 *
 * 
 * To Compile this cc -l ncurses -o outfile usermgr.c
 * 
 * 
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ncurses.h>
#include <string.h>


#include <pwd.h>

#include "../include/usermgr.h"
#include "../include/smitinfo.h"

int x, y;   // X and Y as Integers


/* Dialog  Pointer*/
WINDOW *Spare;   // Spare Window which is larger than the list so it can have the box drawn in to it


/* User list */
WINDOW *userlistbox;  // User List Window

int usrkey;

int counter = 0;  // Used with moving cursors down lines always set at 0 with windows without box
int userctr = 0;  // Counter for user line

int x, y;   // X and Y as Integers

/* Structs */

// Uses Information from pwd.h
struct passwd *pw;


/* Draws out the main Screen  */
int drawtui(void)
{
	clear(); /* Clear Screen */
	getmaxyx(stdscr, y,x); // Get Window Size
	box(stdscr, ACS_VLINE, ACS_HLINE); // Draw Box around Main Screen 
	attron(A_UNDERLINE); // Turn on Underline
	mvprintw(1, 32, "%s", usermgr_title); // Write Title on line 1 and 32
	attroff(A_UNDERLINE); // Turn off Underline
	
	/* Header for the User List Box and other parts */
	attron(A_BOLD); // Turn on bold
	
	/* see usermgr.h for these varibles */
	mvaddstr(3,3, user_title);  // User name title
	mvaddstr(3,21, UID_title);  // UID
	mvaddstr(3, 28, GID_title); // GID
	mvaddstr(3, 40, Comment_title); // Comments aka full names
	
	/* Bottom Part of the Screen */
	

	mvaddstr(y-5,2, FKEY1);  /* SMIT Controls 1 and 2*/
	mvaddstr(y-4,2, UKEYS);  /* User Manager */
	mvaddstr(y-3,2, FKEY2);
	
	
	
	attroff(A_BOLD); // Turn off bold
	/* End of Header for TUI */
	
	Spare = newwin(12,82,4,1);  // Window to have lines on
	userlistbox = newwin(10,80,5,2); // Make New Window for user list box
	box(Spare, ACS_VLINE, ACS_HLINE); // Box the Spare Window
	scrollok(userlistbox, TRUE); // Enable Scrolling
	
	
	/* Refresh */
	
	refresh();  // Refresh Main Screen
	wrefresh(Spare); // Refresh Spare Window only to show a box
	wrefresh(userlistbox); // Refresh user List Window
	return 0;
}


int usermgrmain(void)
{
	
	curs_set(0);
	while(true)
	{
	 drawtui();  // Call Draw TUI (Text User Interface)
	 listusers();
	 
	 do
		{
	     usrkey=getch();
	     switch(usrkey)
	     {
			case KEY_F(1):
				usermgrhelp();
			break;
			case KEY_F(4):
				adduser();
			break;
			
			case KEY_F(9):
				executedefaultshell();
			break;
			
			case KEY_F(10):
			return 0;
			break;
		 }
	     drawtui();  // Call Draw TUI (Text User Interface)
	     listusers();
	    } while (usrkey != '\n');
	    /* Stuff to go here */
	};
	
	wgetch(userlistbox);  // Wait for response in a Window
	
	
	endwin(); // End Curses Sessions
	return 0; 
}

int listusers(void)
{
	setpwent();  // Set use of Passwd
	while(( pw = getpwent())) {
			
	(void)mvwprintw(userlistbox, counter, 2, "%s", pw->pw_name);  // Username
	(void)mvwprintw(userlistbox, counter, 20, "%d", pw->pw_uid);  // UID
	(void)mvwprintw(userlistbox, counter, 27, "%d	", pw->pw_gid);  // GID
	(void)mvwprintw(userlistbox, counter, 38, "%s", pw->pw_gecos);  // Comment
	
		wmove(userlistbox, counter++, 3);  // Increment downline after each line.
	}
		
		
	endpwent();  // end use of Passwd
	wrefresh(Spare);
	wrefresh(userlistbox);
	counter = 0; // Reset the counter
	return 0;
}
