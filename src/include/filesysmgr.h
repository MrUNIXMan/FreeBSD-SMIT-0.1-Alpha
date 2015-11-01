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
 */

#ifndef FILESYSMGR_H_
#define FILESYSMGR_H_

	static char fsmgr_title[] = "Filesystem Manager";
	static char fsnode_title[] = "Filesystem Node";
	static char fstype_title[] = "FS-Type";
	static char fsopts_title[] = "FS-Options";
	static char mountpt_title[] = "Mount Point";
	
	static char FS_OPT_TITLE[] = "Filesystem operations";
	static char FSMGR_OPT1[] = "1. Mount		2. Dismount		3. Edit";
	
	static char FKEY1[] = "F1=Help		F2=Refresh		F3=Cancel";
	static char FKEY2[] = "F9=Shell		F10=Quit		Enter=Do";	
	
	
/* Functions */
	
int listfstab(void);
int fsmgrmain(void);
	
	
#endif



