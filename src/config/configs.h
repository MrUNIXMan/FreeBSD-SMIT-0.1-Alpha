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
 #ifndef _CONFIGS_H_
 #define _CONFIGS_H_

 #define EDIT_PROG		 " /usr/bin/ee "
 
 #define EDIT_BOOT_LOADER			 EDIT_PROG " /boot/loader.conf"
 #define EDIT_FSTAB_FILE		 	 EDIT_PROG " /etc/fstab"
 #define EDIT_HOSTS_FILE			 EDIT_PROG " /etc/hosts"
 #define EDIT_RCCONF_FILE			 EDIT_PROG " /etc/rc.conf"
 #define EDIT_XORGCONF_FILE	 		 EDIT_PROG " /etc/X11/xorg.conf" 

 //#define BOOTLOADER_CONF "/boot/loader.conf"
 
 //static char *bootloaderconf[] = {EDIT_PROG, "/boot/loader.conf", NULL};
 
 
 
 
 #define GENERIC_FILE	 "GENERIC"
 #define CONFIG_PATH	 "/sys/amd64/conf"
 
 


 #endif
