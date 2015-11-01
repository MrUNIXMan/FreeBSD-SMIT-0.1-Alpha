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
 * -------------------------------------------------------------------------------
 * 
 * The Kernel Manager for FreeBSD & NextBSD.
 * 
 * This will not work properly on Open or NetBSD due to commands used on FreeBSD
 * 
 *  
 */

#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/utsname.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/wait.h>
#include "../include/menuinfo.h"
#include "../include/kernelmgr.h"
#include "../include/smitinfo.h"
#include "../config/configs.h"




WINDOW *KERROR;   /* Error Window */
WINDOW *DLG;	  /* Dialog Window */
int errorlevel = 0; /* This changes if detects an error */
int archlevel = 0 ; /* archlevel = 0 is AMD64 while 1 is I386 */




char computer[256];
struct utsname uts;


int y,x;
int c;
FILE *infile, *outfile, *editfile;




int kernelmgrTUI(int kmenuitem)
{
	int kmctr; /* Menu Counter */
	
	clear();
	getmaxyx(stdscr, y,x);
	box(stdscr, ACS_VLINE, ACS_HLINE);
	
	/* Declare the Menu Items */
	
	char kernelmenu [KERN_MENU_MAX] [34] = {
		"Load a Kernel Module",
		"Unload a Kernel Module",
		"Copy GENERIC file to new name",
		"Use Existing Kernel config file", 
		"Edit a Kernel Config file",
		"Compile Kernel",
		"Install Kernel", 
		"Quit"
		
	};
	
	
	
	
	
	/* This Decides on error that would occur in the kernelmgrmain Function 
	 * If errorlevel is 0 then system info is printed. If error becomes 1 as
	 * a result of an error in the other function. It will miss off that stuff
	 *  */
	
	if(errorlevel <1) {		
		attron(A_UNDERLINE);
		mvprintw(1, 23, "%s Kernel Configuration Manager", PROG_NAME); /* Title */
		attroff(A_UNDERLINE);
		mvprintw(3, 2, "Host: %s", computer);
		mvprintw(3, 20, "ARCH: %s", uts.machine);
		mvprintw(3, 35, "O/S: %s", uts.sysname);
		mvprintw(3, 55, "Release: %s", uts.release);
		
		/* Uses values from Getmaxyx */
		mvaddstr(y-4,2, FKEY1); /* Bottom Bar */
		//mvaddstr(y-5,65, "F4=Set Config Path");
		//mvaddstr(y-4,2, "F4=Set Config file Path");
		
		mvaddstr(y-3,2, FKEY2); /* Bottom Bar */
	
		if (strcmp(uts.machine, "amd64") == 0) {
			archlevel = 0;
			mvprintw(5, 2, "Configuration File dir: %s", AMD64_CONF);
			}
		else if (strcmp(uts.machine, "i386") == 0) {
			archlevel = 1;
			mvprintw(5, 2, "Configuration File dir: %s", I386_CONF);
		}
		else {
			mvprintw(5,2, "Else");
			}; // End of if (strcmp(uts.machine statments
	
		mvprintw(5, 54, "Conf file: %s", conffilename );
		mvhline(6, 1, ACS_HLINE, 80);
		}
	else {
	//	clear();
		attron(A_UNDERLINE);
		mvprintw(1, 23, "%s Kernel Configuration Manager", PROG_NAME); /* Title */
		attroff(A_UNDERLINE);
		mvprintw(3, 2, "Kernel Configuration File dir: %s", UNKNOWN_CONF);
		mvhline(4, 1, ACS_HLINE, 67);
		
		};  // End of If (errorlevel <1) statment
		
		/* Draw out the Menu */
		
		for (kmctr=0; kmctr < KERN_MENU_MAX; kmctr++)
		{
			if(kmctr==kmenuitem)
			attron(A_REVERSE);
			
			if(errorlevel < 1) {			
				mvaddstr(8+(kmctr*1), 5, kernelmenu[kmctr]);
			}
			else
			{
				mvaddstr(6+(kmctr*1), 5, kernelmenu[kmctr]);
			};		
			attroff(A_REVERSE);
		}
		
		
		
	
	
	
	refresh();

	return 0;
}

int kernelmgrmain()
{
	int kmkey, kmitem;  // Menu Stuff
	kmitem = 0;			// Menuitem
	
	
	if (gethostname(computer, 255) != 0 || uname(&uts) <0)
	{
		errorlevel = 1;
		KERROR = newwin(6,51,6,15);
		box(KERROR, ACS_VLINE, ACS_HLINE);
		mvwprintw(KERROR, 1, 2, "Unable to open host information");
		mvwprintw(KERROR, 2, 2, "Press any key to use the kernel manager");
		mvwprintw(KERROR, 3, 2, "without information");
		
		wgetch(KERROR);
		werase(KERROR);
	}
	
	while(kmitem != 7)
	{
		kernelmgrTUI(kmitem); 
		refresh();
	do
	{
		kmkey = getch();
		switch(kmkey)
		{
			/* Arrow Keys */
			case KEY_DOWN:
				kmitem++;
				if(kmitem > KERN_MENU_MAX) kmitem = 0;
			break;
			case KEY_UP:
				kmitem--;
				if(kmitem < 0) kmitem = KERN_MENU_MAX-1;
			break;
				
			/* F-Keys */
			case KEY_F(9):
				executedefaultshell();
			break;
			case KEY_F(10):
				return 0;
			break;
			
		}
		kernelmgrTUI(kmitem); 
		refresh();
		
	} while(kmkey != '\n');
	
	/* Add your Stuff here 
	 * 
	 * Option 0 and 1 are related to the kernel
	 * modules. They are not implented yet.
	 * */
		
		if(kmitem == 2) {
			copyconffile();
		}
		else if(kmitem == 3) {
			select_existing_conf_file();
		}
		else if(kmitem == 4) {
			edit_Kernel_file();
		}
		else if(kmitem == 5) {
			compilekernel();
		}
		else if(kmitem == 6) {
			installkernel();
		}
		else if(kmitem == 7) {
			return 0;
		}
	
	};
	
	
	free(conffilename);	
	return 0;
}



int copyconffile()
{
	
	
	if ((conffilename = malloc(sizeof(char) * KERNEL_BUFFER + 1)) == NULL)
		return(1);
		
	echo();
	DLG = newwin(8,50, 3, 2);
	box(DLG, ACS_VLINE, ACS_HLINE);
	mvwprintw(DLG,2,2, "Please Type a new filename to give for the");
	mvwprintw(DLG,3,2, "Kernel configuration file");
	mvwprintw(DLG,5,2, "[__________________________]");
	wrefresh(DLG);

	wattron(DLG, A_REVERSE);
	mvwprintw(DLG,5,2, "[__________________________]");
	wrefresh(DLG);
	
	mvwgetnstr(DLG,5,3, conffilename, 20);
	wattroff(DLG, A_REVERSE);
	wrefresh(DLG);
	
	wclear(DLG);
	box(DLG, ACS_VLINE, ACS_HLINE);
	mvwprintw(DLG, 2, 2, "Copying %s to %s", GENERIC_FILE, conffilename);
	wrefresh(DLG);
	
	
	/* Changes to the Directory */
	
	if(archlevel < 1) {
		if(chdir(AMD64_CONF) < 0) {
			perror("chdir");
			//getch();
		  }
		}
	else 
		{
		if(chdir(I386_CONF) < 0) {
			perror("chdir");
		//	getch();
		}
	};
	
		
	/* Copies the File */
	
	infile=fopen(GENERIC_FILE, "r");
	outfile=fopen(conffilename, "w");
	
	while((c = 	fgetc(infile)) != EOF)
		fputc(c,outfile);
	
	wclear(DLG);
	box(DLG, ACS_VLINE, ACS_HLINE);
	mvwprintw(DLG, 2, 2, "Completed Copying");
	wrefresh(DLG);
	wgetch(DLG);
	
	delwin(DLG);
	
	noecho();
	fclose(outfile);
	return 0;
}

int select_existing_conf_file(void)
{
	if ((conffilename = malloc(sizeof(char) * KERNEL_BUFFER + 1)) == NULL)
		return(1);
	echo();
	DLG = newwin(8,50, 3, 2);
	box(DLG, ACS_VLINE, ACS_HLINE);
	mvwprintw(DLG,2,2, "Please Type existing ");
	mvwprintw(DLG,3,2, "Kernel configuration filename");
	mvwprintw(DLG,5,2, "[__________________________]");
	wrefresh(DLG);

	wattron(DLG, A_REVERSE);
	mvwprintw(DLG,5,2, "[__________________________]");
	wrefresh(DLG);
	
	mvwgetnstr(DLG,5,3, conffilename, 20);
	wattroff(DLG, A_REVERSE);
	wrefresh(DLG);
	delwin(DLG);
	noecho();
	return 0;
	
}

/* This will execute an Editor to edit a kernel config file */
int edit_Kernel_file(void)
{
	/* Changes to the Directory */
	
	if(archlevel < 1) {
		if(chdir(AMD64_CONF) < 0) {
			perror("chdir");
		  }
		}
	else 
		{
		if(chdir(I386_CONF) < 0) {
			perror("chdir");
		//	getch();
		}
	};
	
	
	/* Opens File to Edit */
	
	/* Determins if the File exists or not */
	if(fopen(conffilename,  "r") == NULL) {
		DLG = newwin(8,50, 3, 2);
		box(DLG, ACS_VLINE, ACS_HLINE);
		mvwprintw(DLG,2,2, "File: %s ", conffilename);
		mvwprintw(DLG,3,2, "Does not exist");
	
		wrefresh(DLG);
		wgetch(DLG);
		werase(DLG);
	}
	else {
		clear();
		refresh();
		curs_set(1);
		savetty();
		reset_shell_mode();

		
		/* This section deals with Forking a Process to execute another program 
		 * it is wise to default the editor to ee instead of nano or any in the 
		 * /usr/local directory. unless changed by user
		 * 
		 * editor is set in smitinfo.h
		 * 
		 * */
		 
		int ret = fork();
		
		if (ret == 0)
		{
			char *params[4]	 = {editor, conffilename, 0};  
			execv(editor, params);
		}
		else
		{
			waitpid(ret, 1,0);
			
		}
			
		curs_set(0);
		resetty();
		return 1;
	};
	
	
	
	return 0;
}


int compilekernel(void)
{
	
	int countdown;
	countdown = 3;
	
	/* 1st of all need to check if the file exists */
	
	/* Changes to the Directory to the config file dir */
	
	if(archlevel < 1) {
		if(chdir(AMD64_CONF) < 0) {
			perror("chdir");
		  }
		}
	else 
		{
		if(chdir(I386_CONF) < 0) {
			perror("chdir");
		}
	};
	
	/* Check if File exists */
	
	if(fopen(conffilename,  "r") == NULL) {
		DLG = newwin(8,50, 3, 2);
		box(DLG, ACS_VLINE, ACS_HLINE);
		mvwprintw(DLG,2,2, "File: %s ", conffilename);
		mvwprintw(DLG,3,2, "Does not exist");
	
		wrefresh(DLG);
		wgetch(DLG);
		werase(DLG);
	}
	else {
		/* Changes to /usr/src */
		if(chdir(sourcedir) < 0) {
			perror("chdir");
			return 1;
		}
		
		
	
	
	DLG = newwin(6,70,4,5);
	
	
	while(countdown != 0) {
		wclear(DLG);
		box(DLG, ACS_VLINE, ACS_HLINE);
		wattron(DLG, A_BOLD);
		mvwprintw(DLG, 1, 2, "Command: %s %s%s", makecmd, makebuildkernel, conffilename);
		wattroff(DLG, A_BOLD);
		mvwprintw(DLG, 3, 2, "Kernel compile commences in");
		mvwprintw(DLG, 3, 35, "%i   Seconds", countdown);
		wrefresh(DLG);
		sleep(1);
		countdown--;
		
	};
	
		werase(DLG);
		
	/* Kernel Compile commands go here */
  
  
	 clear();
	 refresh();
	 savetty();
	 reset_shell_mode();
	 curs_set(2);
	 printf("Now Commencing to compile the kernel\n");
	 
	 /* Creates a Buffer to Specify the arguments for the Kernel Config file */
	 //char buf[25];
	 sprintf(buf, "KERNCONF=%s", conffilename);
	 
	 int ret2 = fork();
	 
	 if (ret2 == 0)
		{	
			/* This causes errors on KERNCONF= behalf 
			 * 
			 * Seems to work when specified like this
			 * {"make", "buildkernel", "KERNCONF=Test", 0};
			 * Previously it was like
			 * {"make", "buildkernel", "KERNCONF=", conffilename, 0};
			 * It puts  a space between KERNCONF=  conffilename resulting in 
			 * failure.
			 * 
			 * This error for nonexistant config file was corrected
			 * by the  code involving sprintf(buf, "KERNCONF=%s", conffilename);
			 * by outputting the KERNCONF=Selected Filename in to 1 string in buffer 
			 * and then putting it in to an argv array.
			 * 
			 * */
			char *argv[] = {
				"make", "buildkernel", buf, 0
				};
			execv("/usr/bin/make", argv);
			
		
			
			
			printf("\n\nPress Enter after finished Viewing\n");
			pauseme();
			
		}
		else
		{
			printf("\n\nWaiting on PID\n");
			waitpid(ret2, 1,0);
			//printf("\n\nGone in to else waitpid(ret2, 1,0) \n");	
			printf("\n\nPress Enter after finish viewing and return to SMIT \n");
			pauseme();
			
			
		}	
	 
	 curs_set(0);
	 resetty(); 
	   
  }
	
 return 0;
}

int installkernel(void)
{
	int countdown;
	countdown = 3;
	
	/* 1st of all need to check if the file exists */
	
	/* Changes to the Directory to the config file dir */
	
	if(archlevel < 1) {
		if(chdir(AMD64_CONF) < 0) {
			perror("chdir");
		  }
		}
	else 
		{
		if(chdir(I386_CONF) < 0) {
			perror("chdir");
		}
	};
	
	/* Check if File exists */
	
	if(fopen(conffilename,  "r") == NULL) {
		DLG = newwin(8,50, 3, 2);
		box(DLG, ACS_VLINE, ACS_HLINE);
		mvwprintw(DLG,2,2, "File: %s ", conffilename);
		mvwprintw(DLG,3,2, "Does not exist");
	
		wrefresh(DLG);
		wgetch(DLG);
		werase(DLG);
	}
	else {
		/* Changes to /usr/src */
		if(chdir(sourcedir) < 0) {
			perror("chdir");
			return 1;
		}
		
		
	
	
	DLG = newwin(6,70,4,5);
	
	
	while(countdown != 0) {
		wclear(DLG);
		box(DLG, ACS_VLINE, ACS_HLINE);
		wattron(DLG, A_BOLD);
		mvwprintw(DLG, 1, 2, "Command: %s %s%s", makecmd, makeinstallkernel, conffilename);
		wattroff(DLG, A_BOLD);
		mvwprintw(DLG, 3, 2, "Kernel Install commences in");
		mvwprintw(DLG, 3, 35, "%i   Seconds", countdown);
		wrefresh(DLG);
		sleep(1);
		countdown--;
		
	};
	
		werase(DLG);
		
	/* Kernel Install commands go here */
	 clear();
	 refresh();
	 savetty();
	 reset_shell_mode();
	 curs_set(2);
	 printf("Now Commencing to Install the kernel\n");
	 
	 /* Creates a Buffer to Specify the arguments for the Kernel Config file */
	 //char buf[25];
	 sprintf(buf, "KERNCONF=%s", conffilename);
	 
	 int ret2 = fork();
	 
	 if (ret2 == 0)
		{	
		char *argv[] = {
				"make", "installkernel", buf, 0
				};
			execv("/usr/bin/make", argv);
				
			printf("\n\nPress Enter after finished Viewing\n");
			pauseme();
			
		}
		else
		{
			printf("\n\nWaiting on PID\n");
			waitpid(ret2, 1,0);
			printf("\n\nPress Enter after finish viewing and return to SMIT \n");
			pauseme();
			
			
		}	
	 
	 curs_set(0);
	 resetty(); 
 
 
 
 }
	
	return 0;
}


/* Pauses */

void pauseme(void)
{
		while(!getchar()); 		
	
}

