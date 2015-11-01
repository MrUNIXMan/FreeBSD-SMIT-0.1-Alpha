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
 * File System Manager - Interface for managing filesystems.
 * 
 * Written from Scratch using ideas from FreeBSD mount.c and friends.
 * 
 * Copyright (C) October 2015 by Vincent
 *
 * 
 * 
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ncurses.h>
#include <string.h>

#include <sys/mount.h>
#include <fstab.h>

#include "../include/filesysmgr.h"
#include "../include/smitinfo.h"


/* Dialog  Pointer*/
WINDOW *mountbox;   // Dialog for Mounting Filesystems
WINDOW *umountbox;  // Dialog for Un-mounting filesystems

/* Filesystem list */
WINDOW *fslistbox;  // Filesystem List Window
WINDOW *fssparebox;  // Box that contains border

int fskey; // Key

int fscounter = 0;  // Used with moving cursors down lines always set at 1
int fsitem = 0; // Item in Fslistbox window so it does not reset with the counter.

int x, y;   // X and Y as Integers

/* Structs */

// Uses Information from Fstab.h
struct fstab *fs;


/* Draws out the main Screen  */
int drawfstui(void)
{
	
	clear(); /* Clear Screen */
	getmaxyx(stdscr, y,x);
	box(stdscr, ACS_VLINE, ACS_HLINE); // Draw Box around Main Screen 
	attron(A_UNDERLINE); // Turn on Underline
	mvprintw(1, 32, "%s", fsmgr_title); // Write Title on line 1 and 32
	attroff(A_UNDERLINE); // Turn off Underline
	
	/* Header for the FS List Box and other parts */
	attron(A_BOLD); // Turn on bold
	
	/* see filesysmgr.h for these varibles */
	mvaddstr(3,3, fsnode_title);  // Filesystem Node (Devices)
	mvaddstr(3,27, mountpt_title);  // Mount Point 
	mvaddstr(3, 48, fstype_title); // Filesystem Type
	mvaddstr(3, 60, fsopts_title); // Filesystem Opts	
	
	/* Bottom Part of the Screen */
	mvaddstr(17, 2, FS_OPT_TITLE);
	mvaddstr(18, 2, FSMGR_OPT1);  /* Options */
	
	mvaddstr(y-4,2, FKEY1); /* Bottom Bar */
	mvaddstr(y-3,2, FKEY2); /* Bottom Bar */
		
	
	attroff(A_BOLD); // Turn off bold
	/* End of Header for TUI */
	
	fssparebox = newwin(12,70,4,2);
	box(fssparebox, ACS_VLINE, ACS_HLINE);
	fslistbox = newwin(10,68,5,3); // Make New Window for filesystem list box
	//box(fslistbox, ACS_VLINE, ACS_HLINE); // Box that Window
	scrollok(fslistbox, TRUE); // Enable Scrolling
	
	
	/* Refresh */
	
	refresh();  // Refresh Main Screen
	wrefresh(fssparebox);
	wrefresh(fslistbox); // Refresh filesystem List Window
	return 0;
}



int fsmgrmain(void)
{	
	curs_set(0);

	while(true)
	{
		drawfstui();  // Call Draw TUI (Text User Interface)	
		listfstab();  // List Fstab content
		
		do
		 {
		//	fskey = wgetch(fslistbox);  // Wait for response in a Window
			fskey = getch();
			switch(fskey)
			{
					case KEY_F(9):
					executedefaultshell();
					break;
					
					case KEY_F(10):
					return(0);
					break;
				
			}
			drawfstui();  // Call Draw TUI (Text User Interface)	
			listfstab();  // List Fstab content
		} while (fskey != '\n');
		/* Other stuff goes here */
	};
			
	werase(fslistbox);
	fscounter = 0; // Reset the counter
	return 0; 
}

int listfstab(void)
{
	fscounter = 0;
	setfsent();  // Set use of Fstab
	while(( fs = getfsent())) {
			
	(void)mvwprintw(fslistbox, fscounter, 2, "%s", fs->fs_spec);  // Filesystem node (Devices)
	(void)mvwprintw(fslistbox, fscounter, 26, "%s", fs->fs_file);  // Mount Point
	(void)mvwprintw(fslistbox, fscounter, 46	, "%s", fs->fs_vfstype);  // Filesystem Type
	(void)mvwprintw(fslistbox, fscounter, 60, "%s", fs->fs_mntops);  // Mount Opts
		wmove(fslistbox, fscounter++, 3);  // Increment downline after each line.
	}
		
		
	endfsent();  // end use of Fstab
	wrefresh(fslistbox);
	return 0;
}
