/*-
 * Copyright (c) 1980, 1989, 1993, 1994
 *	The Regents of the University of California.  All rights reserved.
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
 * --------------------------------------------------------------------------------
 * listfs.c - This was taken from the mount.c and changed to work with Ncurses
 * and to display the filesystem nodes, mountpoint and filesystem type in an
 * ncurses format for BSD-SMIT Program.
 * 
 * Modification took place in October 2015 by Vincent May
 * 
 */

#ifndef lint
static const char copyright[] =
"@(#) Copyright (c) 1980, 1989, 1993, 1994\n\
	The Regents of the University of California.  All rights reserved.\n";
static const char copyright_of_modified_code[] =
"Source Code Modified & New Code added by Vincent May, 2015 (C).\n";
#if 0
static char wassccsid[] = "@(#)mount.c	8.25 (Berkeley) 5/8/95";
static char sccsid[] = "@(#)listfs.c 0.1 (Vincent May) 11/10/15";
#endif
#endif /* not lint */

#include <sys/cdefs.h>
__FBSDID("$FreeBSD$");

#include <sys/param.h>
#include <sys/mount.h>
#include <sys/stat.h>
#include <sys/wait.h>

#include <ctype.h>
#include <err.h>
#include <errno.h>
#include <fstab.h>
#include <paths.h>
#include <pwd.h>
#include <signal.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <libutil.h>

#include <ncurses.h>
#include "../include/smitinfo.h"


#include "extern.h"
#include "mntopts.h"


/* `meta' options */
#define MOUNT_META_OPTION_FSTAB		"fstab"

static char FS_LIST_TITLE []= "List Mounted Filesystems";

WINDOW *FS_LIST;
WINDOW *FS_SPARE;

int ctr = 0;  /* Counter */

int app_init(void)
{
	//initscr();
	clear();
	noecho();
	keypad(stdscr, TRUE);
	box(stdscr, ACS_VLINE, ACS_HLINE);
	attron(A_UNDERLINE);
	mvaddstr(1, 20, PROG_NAME);
	mvaddstr(1, 33, FS_LIST_TITLE);
	attroff(A_UNDERLINE);
	refresh();
	
	attron(A_BOLD);
	mvaddstr(3, 3, "Filesystem Node");

	mvaddstr(3, 23, "Mount Directory");

	mvaddstr(3, 43, "Filesystem Type");
	attroff(A_BOLD);
	
	
	refresh();
	
	
			//			   Y X Pos
	FS_SPARE = newwin(10,72,4,1);  // Spare Window
	box(FS_SPARE, ACS_VLINE, ACS_HLINE);
	FS_LIST = newwin(8,70,5,2);
	//box(FS_LIST, ACS_VLINE, ACS_HLINE);
	wrefresh(FS_SPARE);
	wrefresh(FS_LIST);
	scrollok(FS_LIST, TRUE);
	
	return 0;
}

static int fstab_style;

struct cpa {
	char	**a;
	ssize_t	sz;
	int	c;
};

char   *catopt(char *, const char *);
struct statfs *getmntpt(const char *);
int	hasopt(const char *, const char *);
int	ismounted(struct fstab *, struct statfs *, int);
int	isremountable(const char *);
char   *update_options(char *, char *, int);
int	mountfs(const char *, const char *, const char *,
		int, const char *, const char *); 

void	prmount(struct statfs *);
void	putfsent(struct statfs *);


/*
 * List of VFS types that can be remounted without becoming mounted on top
 * of each other.
 * XXX Is this list correct?
 */
static const char *
remountable_fs_names[] = {
	"ufs", "ffs", "ext2fs",
	0
};

int
mntlistmain()
{
	
	/* NCurses Stuff */
	
	app_init(); /* INIT Ncurses Stuff not needed when becomes part of SMIT*/
	
	const char  **vfslist, *vfstype;
	struct fstab *fs;
	struct statfs *mntbuf;
	int all, i, init_flags, late, failok, mntsize, rval, ro;
	int onlylate;
	char *options;

	all = init_flags = late = onlylate = 0;
	ro = 0;
	options = NULL;
	vfslist = NULL;
	vfstype = "ufs";

// Leave there


#define	BADTYPE(type)							\
	(strcmp(type, FSTAB_RO) &&					\
	    strcmp(type, FSTAB_RW) && strcmp(type, FSTAB_RQ))

	rval = 0;
		/* Might be what I want */

		if ((mntsize = getmntinfo(&mntbuf, MNT_NOWAIT)) == 0)
			err(1, "getmntinfo");
		if (all) {
			while ((fs = getfsent()) != NULL) {
				if (BADTYPE(fs->fs_type))
					continue;
				if (checkvfsname(fs->fs_vfstype, vfslist))
					continue;
				if (hasopt(fs->fs_mntops, "noauto"))
					continue;
				if (!hasopt(fs->fs_mntops, "late") && onlylate)
					continue;
				if (hasopt(fs->fs_mntops, "late") && !late)
					continue;
				if (hasopt(fs->fs_mntops, "failok"))
					failok = 1;
				else
					failok = 0;
				if (!(init_flags & MNT_UPDATE) &&
				    ismounted(fs, mntbuf, mntsize))
					continue;
		
			}
				
		} else if (fstab_style) {
			for (i = 0; i < mntsize; i++) {
				if (checkvfsname(mntbuf[i].f_fstypename, vfslist))
					continue;
			}
		} else {
			for (i = 0; i < mntsize; i++) {
				if (checkvfsname(mntbuf[i].f_fstypename,
				    vfslist))
					continue;
				prmount(&mntbuf[i]);
				wmove(FS_LIST, ctr++, 2);
			}
		}
		wgetch(FS_LIST);
		
		ctr = 0; // Reset the Counter
		return (rval);


}

/* Used by Above */
int
ismounted(struct fstab *fs, struct statfs *mntbuf, int mntsize)
{
	char realfsfile[PATH_MAX];
	int i;

	if (fs->fs_file[0] == '/' && fs->fs_file[1] == '\0')
		/* the root file system can always be remounted */
		return (0);

	/* The user may have specified a symlink in fstab, resolve the path */
	if (realpath(fs->fs_file, realfsfile) == NULL) {
		/* Cannot resolve the path, use original one */
		strlcpy(realfsfile, fs->fs_file, sizeof(realfsfile));
	}

	for (i = mntsize - 1; i >= 0; --i)
		if (strcmp(realfsfile, mntbuf[i].f_mntonname) == 0 &&
		    (!isremountable(fs->fs_vfstype) ||
		     strcmp(fs->fs_spec, mntbuf[i].f_mntfromname) == 0))
			return (1);
	return (0);
}

int
isremountable(const char *vfsname)
{
	const char **cp;

	for (cp = remountable_fs_names; *cp; cp++)
		if (strcmp(*cp, vfsname) == 0)
			return (1);
	return (0);
} 

/* Used by Above */
int
hasopt(const char *mntopts, const char *option)
{
	int negative, found;
	char *opt, *optbuf;

	if (option[0] == 'n' && option[1] == 'o') {
		negative = 1;
		option += 2;
	} else
		negative = 0;
	optbuf = strdup(mntopts);
	found = 0;
	for (opt = optbuf; (opt = strtok(opt, ",")) != NULL; opt = NULL) {
		if (opt[0] == 'n' && opt[1] == 'o') {
			if (!strcasecmp(opt + 2, option))
				found = negative;
		} else if (!strcasecmp(opt, option))
			found = !negative;
	}
	free(optbuf);
	return (found);
}


void
prmount(struct statfs *sfp)
{
	
	/* Prints /dev/ada0a on / (ufs - Removed the other part as it is not Necessary */
	
	(void)mvwprintw(FS_LIST, ctr, 2, "%s", sfp->f_mntfromname);
	(void)mvwprintw(FS_LIST, ctr, 23, "%s", sfp->f_mntonname);
	(void)mvwprintw(FS_LIST, ctr, 43, "%s", sfp->f_fstypename);

	wrefresh(FS_LIST);

	
}  
