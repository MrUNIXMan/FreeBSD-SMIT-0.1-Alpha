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
 * User Manager - Interface for managing users.
 * 
 * Written from Scratch using ideas from FreeBSD mount.c and friends.
 */

#ifndef USERMGR_H_
#define USERMGR_H_

	static char usermgr_title[] = "User Manager";
	static char user_title[] = "User";
	static char UID_title[] = "UID";
	static char GID_title[] = "GID";
	static char Comment_title[] = "Comment";
	
	static char FS_OPT_TITLE[] = "User Operation";
	static char USRMGR_OPT1[] = "1. Add		2. Remove		3. Modify";
	
	static char FKEY1[] = "F1=Help		F2=Refresh		F3=Cancel";
	static char UKEYS[] = "F4=Add User		F5=Remove User		F6=Modify User";  // User manager Keys
	static char FKEY2[] = "F9=Shell		F10=Quit		Enter=Do";	
	
	
/* Functions */
	
int listusers(void);
int usermgrmain(void);
	
	
#endif



