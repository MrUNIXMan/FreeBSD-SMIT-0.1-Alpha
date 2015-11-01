/*-
 * 
 * Modified in 2015 by Vincent (MrUNIXman@lycos.com) as apart of a SMIT project
 * 
 * Disclaimer: This was modified to be used with Curses which is apart of a BSD
 * SMIT project. This will be called from the usermenu showing logged in Users.
 * 
 *  This had a lot of code that was produced by Tim J Robbins removed due to  it not
 * applicable to SMIT to have arguments. Other areas will be modified to use ncurses.
 * 
 * 
 * ---------------------------------------------------------------------------------------
 * 
 * Copyright (c) 2002 Tim J. Robbins.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#include <sys/cdefs.h>
__FBSDID("$FreeBSD$");

#include <sys/param.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <sys/stat.h>

#include <err.h>
#include <errno.h>
#include <langinfo.h>
#include <limits.h>
#include <locale.h>
#include <paths.h>
#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <timeconv.h>
#include <unistd.h>
#include <utmpx.h>

#include <ncurses.h>

#include "../include/smitinfo.h"

#define HLINE 57	


static void	process_utmp(void);
static void	row(const struct utmpx *);
//static int	ttywidth(void);

static int ctr;


static int	aflag;			/* Print all entries */
static int	bflag;			/* Show date of the last reboot */
static int	Tflag;			/* Show terminal state */
static int	uflag;			/* Show idle time */


WINDOW *Box;
WINDOW *userlist;


int drawdialog()
{
	clear();
	box(stdscr, ACS_VLINE, ACS_HLINE);
	attron(A_BOLD);
	mvprintw(1, 25, "%s - List logged in users", PROG_NAME);
	mvprintw(3, 4, "Name");
	mvprintw(3, 13, "State");
	mvprintw(3, 23, "Line");
	mvprintw(3, 33, "Location");
	attroff(A_BOLD);
	
	refresh();
	
	Box = newwin(15,58,4,2);
	box(Box, ACS_VLINE, ACS_HLINE);
		
	userlist = newwin(13,56,5,3);
	//box(userlist, ACS_VLINE, ACS_HLINE);
	scrollok(userlist, TRUE);  /* Enable Scrolling */
	
	wmove(userlist,2,2);
	mvprintw(19, 2, "Viewing logged  in user list. Press Enter to return to SMIT menu");
	
	
	refresh();
	wrefresh(Box);
	wrefresh(userlist);
	return 0;
}


int loggedinusers(void)
{
	ctr = 1;
		
	drawdialog();
	
	
	aflag = bflag = Tflag = uflag = 1;

	setlocale(LC_TIME, "");

	process_utmp(); /* See below is designed to work with Ncurses */

	wgetch(userlist);
	
	
	endutxent();
	
	return(0);
	
}

/* Code by Original Author of Who command */

static void
row(const struct utmpx *ut)
{
	
	char tty[PATH_MAX];
	struct stat sb;
	time_t idle;
	static int d_first = -1;
	struct tm;
	char state;

	if (d_first < 0)
		d_first = (*nl_langinfo(D_MD_ORDER) == 'd');

	state = '?';
	idle = 0;
	if (Tflag || uflag) {
		snprintf(tty, sizeof(tty), "%s%s", _PATH_DEV, ut->ut_line);
		if (stat(tty, &sb) == 0) {
			state = sb.st_mode & (S_IWOTH|S_IWGRP) ?
			    '+' : '-';
			idle = time(NULL) - sb.st_mtime;
		}
	}
	
	
	/* Display User Information  - My code added in Sept 2015*/
	curs_set(0);
	
	mvwprintw(userlist,ctr, 2, ut->ut_user);
	
	mvwprintw(userlist,ctr, 13, "%c", state);
	
	mvwprintw(userlist,ctr, 22, ut->ut_line);
	
	mvwprintw(userlist,ctr, 32, ut->ut_host);

	wmove(userlist, ctr++, 2);
	wrefresh(userlist);
}


/* Original Author Code */

static int
ttystat(char *line)
{
	struct stat sb;
	char ttybuf[MAXPATHLEN];

	(void)snprintf(ttybuf, sizeof(ttybuf), "%s%s", _PATH_DEV, line);
	if (stat(ttybuf, &sb) == 0) {
		return (0);
	} else
		return (-1);
}

static void
process_utmp(void)
{
	struct utmpx *utx;

	while ((utx = getutxent()) != NULL) {
		if (((aflag || !bflag) && utx->ut_type == USER_PROCESS) ||
		    (bflag && utx->ut_type == BOOT_TIME))
			if (ttystat(utx->ut_line) == 0)
			row(utx);
	
	}
}

