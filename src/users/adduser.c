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
 * adduser.c  - Add User Dialog
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pwd.h>
#include <time.h>
#include <sys/types.h>
#include <ncurses.h>
#include <string.h>
/* My Includes */
#include "../include/userinfo.h"
#include "../include/smitinfo.h"



int x, y;

/* Global Chars for all functions to see 
 *  See userinfo.h for the static chars of the entry fields 
 * */

	WINDOW *audlg; /* Confirmation Window */

int drawauscreen()
{
	
	char addusertitle[] = "Add a User";
	
	/* Draw to screen */
	
	clear();
	box(stdscr, ACS_VLINE, ACS_HLINE);
	
	curs_set(0);

/* TUI Basic Parts */	
 	 attron(A_BOLD);
	 mvaddstr(1, 27, addusertitle);
	 mvaddstr(3, 2, usersubmesg_one); /* Message Below the title */
	 mvaddstr(4, 2, usersubmesg_two);
	 
	 mvaddstr(14,2, "[Edit Fields Controls]");
	 mvaddstr(15,2,  addedituser_one); /* Edit Fields 1*/
	 mvaddstr(16,2,  addedituser_two); /* Edit Fields 2*/
	 
	 mvaddstr(18,2,  FKEY1); /* Bottom Bar 1*/
	 mvaddstr(19,2,  FKEY2); /* Bottom Bar 2*/
	 mvaddstr(19,48, F6_KEYAU); /* Function Key 6 */
	 mvaddstr(20,2,  FKEY3); /* Bottom Bar 3*/
	 attroff(A_BOLD);  /* Turn off BOLD */
	
	
/* Fields */
	
	 mvprintw(6,35, "[Entry Fields]");
	 attron(A_BOLD);
	 mvprintw(7,10, "Username:");
	 mvprintw(8,10, "Comment:");
	 mvprintw(9,10, "User ID(UID):");
	 mvprintw(10,10, "Group ID(GID):");
	 mvprintw(11,10, "Login Shell:");
	 mvprintw(12,10, "Home Directory:");
	 attroff(A_BOLD);
	 
	 /* Entry Fields */
	  mvprintw(7, 35, "_________________");
	  mvprintw(8, 35, "_________________");
	  mvprintw(9, 35, "_________________");
	 mvprintw(10, 35, "_________________");
	 mvprintw(11, 35, "_________________");
	 mvprintw(12, 35, "_________________");
	 mvprintw(7, 35, "%s", loginname);
	 mvprintw(8, 35, "%s", usergecos);
	 mvprintw(11, 35, "%s", usershell);
	 mvprintw(12, 35, "%s", homedir);
	 
	 mvprintw(9, 35, "%s", userid);
	 mvprintw(10, 35, "%s", groupid);
	 
	 
 return 0;	
}

int drawverifyadd()
{
	
	audlg = newwin(16, 55, 3, 15);
	box(audlg, ACS_VLINE, ACS_HLINE);
	wattron(audlg, A_UNDERLINE);
	mvwprintw(audlg, 1, 15, "Confirm Add User");
	wattroff(audlg, A_UNDERLINE);
	mvwprintw(audlg, 3,2, "Username:");
	mvwprintw(audlg, 3, 20, "%s", loginname);
	mvwprintw(audlg, 4,2, "Comment:");
	mvwprintw(audlg, 4, 20, "%s", usergecos);
	mvwprintw(audlg, 5,2, "User ID(UID):");
	mvwprintw(audlg, 5, 20, "%s", userid);
	mvwprintw(audlg, 6,2, "Group ID(GID):");
	mvwprintw(audlg, 6, 20, "%s", groupid);
	mvwprintw(audlg, 7,2, "Login Shell:");
	mvwprintw(audlg, 7, 20, "%s", usershell);
	mvwprintw(audlg, 8,2, "Home Directory:");
	mvwprintw(audlg, 8, 20, "%s", homedir);
	
	mvwprintw(audlg, 10, 1, "NOTE: If fields contain (null) or (cleared)");
	mvwprintw(audlg, 11, 1, "please re-edit them");
	mvwprintw(audlg, 13, 1, "Do you wish to add the user? Y/N: ");
	wrefresh(audlg);
/*	wgetch(audlg);
	werase(audlg); */
	
	
	return 0;
}

int verifyadd()
{
	int yn; /* Yes/No */
	
	
	while(true)
	{
		drawverifyadd(); /* Calls Confirmation Dialog */
		do
		{
			echo();
			yn = wgetch(audlg);
			noecho();
			switch(yn)
			{
				case 'Y':
				// smituseradd();
				break;
				case 'y':
				// smituseradd();
				break;
				case 'N':
				werase(audlg);
				return 0;
				break;
				case 'n':
				werase(audlg);
				return 0;
				break;
			}
			drawverifyadd();
		} while(yn != '\n');
	}; /* End of While */
	
	return 0;
}

int adduser(void)
{
	
	/* Declarations */
	getmaxyx(stdscr, y,x); /* Screen Sizes */
	
	int key;
	
	while(true)
	{
	drawauscreen(); /* Draw the Screen */
	refresh();
	 do
	 {
		key = getch();
		switch(key)
		{
			/* Field Edit Keys which are number keys */
			case '1':
			 echo();
				if((loginname = malloc(sizeof(char) * USER_BUFFER + 1)) == NULL)
				return(1);
			 attron(A_REVERSE);
			 mvprintw(7, 35, "_________________");
			 mvwgetnstr(stdscr, 7,35, loginname, 15);
			 attroff(A_REVERSE);
			 noecho();
			break;
			case '2':
			 echo();
				if((usergecos = malloc(sizeof(char) * USER_BUFFER + 1)) == NULL)
				return(1);
			  attron(A_REVERSE);
			  mvprintw(8, 35, "_________________");
			  mvwgetnstr(stdscr, 8,35, usergecos, 15);
			  attroff(A_REVERSE);
			  noecho();
			break;
			case '3':
			 echo();
				if((userid = malloc(sizeof(char) * USER_BUFFER + 1)) == NULL)
				return(1);
			  attron(A_REVERSE);
			  mvprintw(9, 35, "_________________");
			  mvwgetnstr(stdscr, 9,35, userid, 5);
			  attroff(A_REVERSE);
			  noecho();
			break;
			case '4':
			 echo();
				if((groupid = malloc(sizeof(char) * USER_BUFFER + 1)) == NULL)
				return(1);
			  attron(A_REVERSE);
			  mvprintw(10, 35, "_________________");
			  mvwgetnstr(stdscr, 10,35, groupid, 5);
			  attroff(A_REVERSE);
			  noecho();
			break;
			  case '5':
			 echo();
				if((usershell = malloc(sizeof(char) * USER_BUFFER + 1)) == NULL)
				return(1);
			  attron(A_REVERSE);
			  mvprintw(11, 35, "_________________");
			  mvwgetnstr(stdscr, 11,35, usershell, 15);
			  attroff(A_REVERSE);
			  noecho();
			break;
			case '6':
			 echo();
				if((homedir = malloc(sizeof(char) * USER_BUFFER + 1)) == NULL)
				return(1);
			  attron(A_REVERSE);
			  mvprintw(12, 35, "_________________");
			  mvwgetnstr(stdscr, 12,35, homedir, 15);
			  attroff(A_REVERSE);
			  noecho();
			break;
			/* Function Key Controls */
			case KEY_F(1):  /* Help */
			
			break;
			case KEY_F(2):  /* Refresh */
			 refresh();
			break;
			case KEY_F(3): /* Cancel Key */
			
			break;
			case KEY_F(4): 
			/* Reset Fields if statements to prevent crashing if pressed more than once. strcmp does cause segmentation fault */
			 if(loginname != "(cleared)")
			 free(loginname);
		
			 
			 if(usergecos != "(cleared)")
			 free(usergecos);
			 
			 if(usershell != "(cleared)")
			 free(usershell);
			 
			 if(homedir != "(cleared)")
			 free(homedir); 
			 
			 if(userid != "(cleared)")
			 free(userid); 
			 
			 if(groupid != "(cleared)")
			 free(groupid); 
			 
			 loginname = "(cleared)";
			 usergecos = "(cleared)";
			 usershell = "(cleared)";
			 homedir = "(cleared)"; 
			 userid = "(cleared)"; 
			 groupid = "(cleared)"; 
			break;
			case KEY_F(5): /* Run Command */
			 //executecmd(command); /* Execute command */
			break;
			case KEY_F(6): /* Add User */
				verifyadd(); /* Confirms then Add or quits */
			break;
			case KEY_F(9): /* Run Default Shell */
			 executedefaultshell();
			break;
			case KEY_F(10): /* Quits Dialog */
			 return(0);
			break;
			
		}
		drawauscreen();
		refresh();
	} while(key != '\n');
	
	/* Other Statments goes here */
	
	
 };
		
		
	
	/* Finish up */
	
	
	free(loginname);
	free(usergecos);
	free(usershell);
	free(homedir);
	
	return 0;
}
