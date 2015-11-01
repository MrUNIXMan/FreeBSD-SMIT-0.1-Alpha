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




/* Global header files to use */ 
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


/* Usage shows Help */

int usage()
{
	printf("Usage: smit/smitty [argument]\n\n");
	printf("Following argument will run part of the program\n");
	printf("\nusermenu - User Menu	\
			\nfsmenu  - Filesystem Menu	\
			\nsysconfig - System config menu	\
			\nusermgr - User Manager	\
			\nfsmgr - Filesystem Manager	\
			\nabout - program info	\
			\nhelp - this screen			\
			\nsoftwaremgr - Software manager menu \
			\nkernelmgr - Kernel Manager\n\n");
			
	
	exit(0);
}


/* INIT SMIT's Curses mode */

int smit_init()
{
	initscr(); /* Init Screen (Curses) */
	noecho();	  /* Disable's Echo */
	keypad(stdscr, TRUE); /* Allows use of Keypad */
	curs_set(0); /* Turn off cursor) */
	
	return 0;
}

int clean_exit()
{
	clear();
	refresh();
	endwin();
	exit(0);
}

/* Default Smit is used when no arguments are provided */

int default_smit()
{
	initscr(); /* Init Screen (Curses) */
	noecho();	  /* Disable's Echo */
	keypad(stdscr, TRUE); /* Allows use of Keypad */
	curs_set(0);
	
	/* Loads the Main SMIT Menu */
	smitmainmenu();
	
	/* Cleanly Exit */
	
	clear();
	refresh();
	endwin();
	exit(0); /* Prevent Segemation faults in the main */
}



int main(int argc, char *argv[])
{
		
	if (argv[1] == NULL)
	{
		default_smit();
	}
	
	/* Test any Arguments passed */
	/* About and Usage */
	
	if(strcmp(argv[1], "about") == 0)
	{
		printf("%s Version %s\n", PROG_NAME, PROG_VERSION);
		printf("%s\n", COPYRIGHT);
		exit(0);
	}
	else if(strcmp(argv[1], "help") == 0)
	{
		usage();
	}
	else if(strcmp(argv[1], "sysinfo") == 0)
	{
		smit_init(); /* Init Curses */
		sysinfo(); /* Run System Info */
		clean_exit();  /* End Curses Session */
	}
	else if(strcmp(argv[1], "usermenu") == 0 )
	{
		smit_init();
		smitusermenu();
		clean_exit();
	
	
	}
	else if(strcmp(argv[1], "filesysmenu") == 0 )
	{
		smit_init();
		smitfsmenu();
		clean_exit();
	
	
	}
	else if(strcmp(argv[1], "softwaremgr") == 0 )
	{
		smit_init();
		smitsfwmenu();
		clean_exit();
	
	
	}
	else if(strcmp(argv[1], "sysconfig") == 0 )
	{
		smit_init();
		smitscmenu();
		clean_exit();
	
	
	}
	else if(strcmp(argv[1], "fsmgr") == 0)
	{
		smit_init();
		fsmgrmain();
		clean_exit();
	}
	else if(strcmp(argv[1], "usermgr") == 0)
	{
		smit_init();
		usermgrmain();
		clean_exit();
	}
	else if(strcmp(argv[1], "kernelmgr") == 0)
	{
		smit_init();
		kernelmgrmain();
		clean_exit();
	}
	else
		printf("\nInvaild Option: %s\n\n", argv[1]);
		usage();
		exit(0);
}
