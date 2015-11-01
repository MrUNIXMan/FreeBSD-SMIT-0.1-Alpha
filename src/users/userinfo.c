/*-
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
 * ----------------------------------------------------------------------------------
 * userinfo.c  - Display information about a user
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pwd.h>
#include <time.h>
#include <sys/types.h>
#include <ncurses.h>
/* My Includes */
#include "../include/userinfo.h"
#include "../include/smitinfo.h"

int x, y;

// See userinfo.h for static char *loginname
//char *loginname;  /* Char username for getnstring */

/* error dialog */
int progerror(void)
{
	WINDOW *winerror;
	
	winerror = newwin(7,61,6,8);
	box(winerror, ACS_VLINE, ACS_HLINE);
	wattron(winerror, A_BOLD);
	mvwprintw(winerror, 1, 15, "%s - Error", PROG_NAME);
	wattroff(winerror, A_BOLD);
	mvwprintw(winerror, 3, 17, "User Name '%s' ", loginname);
	mvwprintw(winerror, 4, 10, "does not exist on the system.");
	wgetch(winerror);
	werase(winerror);
	return 0;
	
}

int userinfo(void)
{
	
	/* Declarations */
	getmaxyx(stdscr, y,x); /* Screen Sizes */
	
	uid_t uid;
	gid_t gid;
	struct passwd *pw;
	
	uid = getuid();
	gid = getgid();
	
	WINDOW *uidlg; /* Prompt Username Window */
	
	
	
	/* Draw to screen */
	
	clear();
	box(stdscr, ACS_VLINE, ACS_HLINE);
	
	/*                  y x  - Screens */
	uidlg = newwin(6,61,6,8); /* User name input dialog */
	box(uidlg, ACS_VLINE, ACS_HLINE);
	wattron(uidlg, A_UNDERLINE);
	mvwprintw(uidlg, 1, 20, "User Information");
	wattroff(uidlg, A_UNDERLINE);
	
	/*  Buffer control */
	
	if((loginname = malloc(sizeof(char) * USER_BUFFER + 1)) == NULL)
		return(1);
	
	echo();    /* Turns on Echo to see the text typed */
	/* Username Prompt */
	mvwprintw(uidlg, 3, 1,  "Please type in username to look up:");
	mvwprintw(uidlg, 3, 37, "______________");
	wrefresh(uidlg);
	/* Now We need to gain strings that is typed in */
	
	
	/* Show a highlighted Field */
	wattron(uidlg, A_REVERSE);
	mvwprintw(uidlg, 3, 37, "______________");
	wrefresh(uidlg);
	mvwgetnstr(uidlg, 3,37, loginname, 15);
	wattroff(uidlg, A_REVERSE);
	noecho(); /* Removes Echo */
	

	werase(uidlg);	
	
	/* Shows User Information */
	refresh();
	
	attron(A_UNDERLINE);
	mvprintw(1, 25, "%s User Information", PROG_NAME); /* Title */
	attroff(A_UNDERLINE);
	
	refresh();
	

	/* Process User Info now has error handling */
		
	if (pw = getpwnam(loginname) == NULL) {
		progerror();
		free(loginname);
		return 1;
	} 
	else {
		pw = getpwnam(loginname);
	} 

	 
	mvprintw(4, 10, "Username: ");
	mvprintw(4, 25, "%s", pw->pw_name); 
	mvprintw(5, 10, "User ID: "); 
	mvprintw(5, 25, "%d", pw->pw_uid);
	mvprintw(6, 10, "Group ID: ");
	mvprintw(6, 25, "%d", pw->pw_gid);
	mvprintw(7, 10, "Shell: ");
	mvprintw(7, 25, "%s", pw->pw_shell);
	mvprintw(8, 10, "Home dir: ");
	mvprintw(8, 25, "%s", pw->pw_dir);
	mvprintw(9, 10, "Comment: ");
	mvprintw(9, 25, "%s", pw->pw_gecos); 
	
	mvprintw(15,20, "Press Enter to return after viewing");
	
	getch();
	
	free(loginname);
	return 0;
}
