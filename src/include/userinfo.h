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
 *-----------------------------------------------------------------------------
 * userinfo.h
 * 
 * Header files to be included to SMIT programs
 */
#ifndef USERINFO_H_
#define USERINFO_H_

#define USER_BUFFER 20

/* Field Control numbers to edit a field */

static char addedituser_one[] = "1. Username		2. Comment		3. User ID"; 
static char addedituser_two[] = "4. Group ID		5. Shell		6. Home Dir";

/* Dialog Instruction 2nd line copied from AIX SMIT */

static char usersubmesg_one[] = "Press a number to Select an entry field and type";
static char usersubmesg_two[] = "Press Enter AFTER making all desired changes";

/* Bottom Part of the TUI - AIX SMIT Style */

static char FKEY1[] = "F1=Help		F2=Refresh		F3=Cancel";
static char FKEY2[] = "F4=Reset		F5=Run Command"; 			/*Controls on bottom */
static char FKEY3[] = "F9=Shell		F10=Exit		Enter=Do";

static char F6_KEYAU[] = "F6=Add User";  /* Add User Dialog */
static char F6_KEYMU[] = "F6=Modify User"; /* Modify User Dialog */

/* Fields for the Entry Fields */

static char *loginname;  /* Char username for getnstring */
static char *usergecos; /* Char Gecos/Comment for getnstring */
static char  *userid; /* UID */
static char  *groupid; /*GID */
static char *usershell; /*Shell */
static char *homedir;	 /*Home Directory */



/* User Specific Prototypes */

int userinfo(void);
int loggedinusers(void);

#endif
