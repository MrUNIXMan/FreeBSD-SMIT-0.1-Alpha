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
 * bottombar.c  - Bottom Bar Functions (Shared Stuff)
 * 
 *
 * F1=Help		F2=Refresh		F3=Cancel
 * F9=Shell		F10=Quit		Enter=Do
 * 
 * F5 is to Execute a command on some forms
 * 
 */
 #include <stdio.h>
 #include <stdlib.h>
 #include <ncurses.h>
 #include "../include/smitinfo.h"
 #include <sys/wait.h>
 
 
   int tempexit()
   {
	   clear();
	   endwin();
	   
	   return 0;
   }
 
 /* F1 Funcs*/
 
	int mainmenuhelp()
	{
		
		tempexit();
		system(HELPMAIN);
		return 0;
		
	}
 
	int usermenuhelp()
	{
		tempexit();
		system(HELPUSER);
		return 0;
		
	}
	
	int usermgrhelp()
	{
		tempexit();
		system(HELPUMGR);
		return 0;
	}
 
 
 /* F2 Function  this will only refresh stdscr. Window refresh due to 
  * different names will be requried to call seperately */
  
  int screenrefresh()
  {
	  refresh();
	  return 0;
	  
  }
  
  /* F3 Key for Cancel - Not implented */
  
  int cancelopt()  
  {
	  return 0;
	  
  }
  
 /* F5 Function to Execute Command */
 
 int executecmd(char command)
 {
	 
	 return 0;
	 
 } 
 
 
 
 
 /* F9 Functions To exectute the Default Shell. */
 
 int executedefaultshell()
 {
	 clear();
	 refresh();
	 savetty();
	 reset_shell_mode();
	 curs_set(2);
	 printf("Entering %s\n", DEFAULT_SHELL);
	 printf("Type Exit or press CTRL+D to Return to SMIT when finished\n\n");
	 
	 int ret = fork();
	 
	 if (ret == 0)
		{
			char *params[2]	 = {default_shell, 0};  
			execv(default_shell, params);
		}
		else
		{
			waitpid(ret, 1,0);
			
		}
	 
	 
	 curs_set(0);
	 resetty();
	 
	 return 0;
 }
 
 
  /* F10 - Quit Does not work on all menus */
 
  int quitopt()
  {
	  clear();
	  return 0;
	  
  }
 
