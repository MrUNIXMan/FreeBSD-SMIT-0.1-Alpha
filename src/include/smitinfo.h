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
 #include "help.h"
 
 #ifndef SMITINFO_H_
 #define SMITINFO_H_
 
 #define PROG_NAME "FreeBSD SMIT" /* Program Name */
 #define PROG_VERSION "0.1" /* Version */
 #define COPYRIGHT "Copyright (C) 2015 by Vincent" /* Copyright not to be changed */
 #define AUTHOR_EMAIL "MrUNIXMan@lycos.com" /* Author's Email */
 
 #define EXEC_FILE "smit/smitty"  /* File name that it use to execute the program that is used in help */
 #define SMIT_CMD "smit" /* Acutal Command file. Smitty will be a link */
 
 
 /* Default Shell - This one is used for system()*/
 #define DEFAULT_SHELL "/bin/sh" /* Default Shell used with F9 Key */
 
 /* This one is used with exec* inplace of System() */
 static char default_shell[] = {"/bin/sh"};
 
 /* Default Editor */
 static char editor[] = {"/usr/bin/vi"};
 
  
 /* Prototypes */
 
 int sysinfo(void); /* Sysinfo */
 
 int smitmainmenu(void); /* Main menu's main function */
 
 int smitusermenu(void); /* User Menu's Prototype */
 
 int smitfsmenu(void); /* File system menu */
 
 int smitsfwmenu(void); /* Software Menu */
 
 int smitscmenu(void); /* System Configuration Manager */
 
 
 /* Dialogs */
 
 int userinfo(void);
 
 int adduser(void); /* Add a User */
 
 int mntlistmain(); /* Mount Mgr */
 
 
 /* System Configuration Menu */
 
  int edit_loader_conf(void);
  int edit_hosts(void);
  int edit_rc_conf(void);
  int edit_fstab(void);
  int edit_xorg_file(void);
  
 /* Users */
 
 int loggedinusers(void);
 int usermgrmain(void);
 int listusers(void);
 
 /* Filesys Manager */
 
 int fsmgrmain(void);
 int listfstab(void);
 
 
 /* Menu Bar shared Functions */
 
 
  int screenrefresh(); 		   // F2 Key
  int cancelopt();			   // Cancel Opt
  int executedefaultshell();  // F9 Key 
  int quitopt();			  // F10 Key
  
  
  /* Diskspace */
  int curses_init();
  int dfmain();
 
 /* Kernel Manager */
 
 int kernelmgrmain();
 int copyconffile(void);
 int select_existing_conf_file(void);
 int edit_Kernel_file(void);
 
 int compilekernel(void);
 int installkernel(void);
 void pauseme(void);
 
 
 
 #endif
