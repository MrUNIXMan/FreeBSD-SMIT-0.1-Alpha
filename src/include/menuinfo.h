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
 
 #ifndef MENUINFO_H_
 #define MENUINFO_H_
 
 
 /* Global Chars to be reused*/
 
   static char submesg[] = "Please move the cursor to the desired item and press Enter";
   static char FKEY1[] = "F1=Help		F2=Refresh		F3=Cancel";
   static char FKEY2[] = "F9=Shell		F10=Quit		Enter=Do"; 			/*Controls on bottom */
 
 /* Main Menu Prototye and Declares*/
 
 #define MAIN_MENU_MAX 9 /* Max menu items 0-9 */

 void drawsmitmainmenu(int smitmainmenuitem); /* Draw Main Menu declaring Menu item as Integer*/
 int smitmainmenu(void); /* Main menu's main function */

/* User Menu Prototypes and Declars */

 #define USER_MENU_MAX 11
 
/* Filesystem Menu Prototypes and Declares */

 #define FS_MENU_MAX 9
 
/* Software Menu Defines */

  #define SFW_MENU_MAX 9
  
/* System Cofiguration Menu */  
  #define SC_MENU_MAX 8

/* Kernel Configuration Manager Menu */

  #define KERN_MENU_MAX 8

 #endif
