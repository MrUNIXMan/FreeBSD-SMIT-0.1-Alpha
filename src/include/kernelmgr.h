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
 * The Kernel Manager Header File for BSD.
 * 
 *  
 */
#ifndef KERNELMGR_H_
#define KERNELMGR_H_


/* BSD Kernel Source Location */

/* This is /usr/src dir for makebuildkernel commands */

static char sourcedir[] = {"/usr/src"};

/* Make command */
static char makecmd[] = {"/usr/bin/make "};

/* Buildkernel KERNCONF= */
char makebuildkernel[] = {"buildkernel KERNCONF="};

/* Install Kernel command */
static char makeinstallkernel[] = {"installkernel KERNCONF="};

/*Temp Buffer */
static char buf[256];


#define KERNEL_SRC_PATH "/usr/src/sys"

/* Kernel Config files for the PC version of BSD */
#define AMD64_CONF KERNEL_SRC_PATH "/amd64/conf/"
#define I386_CONF KERNEL_SRC_PATH "/i386/conf/"

/* Just incase it errors */
#define UNKNOWN_CONF KERNEL_SRC_PATH "/ARCH/conf"

 /* The Default Configuration File which is to be copied 
 * to another filename before configuring the Kernel.
 * 
 * A Kernel master file */

#define GENERIC_FILE "GENERIC"
#define KERNEL_DEST "GENERIC"

/* MENU ITEMS */



/* File info */

static char *conffilename; /* Config File Name Dest */

#define KERNEL_BUFFER 20

/* External Programs */









#endif 



