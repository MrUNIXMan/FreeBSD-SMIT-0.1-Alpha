/*-
 * Copyright (c) 1980, 1990, 1993, 1994
 *	The Regents of the University of California.  All rights reserved.
 * (c) UNIX System Laboratories, Inc.
 * All or some portions of this file are derived from material licensed
 * to the University of California by American Telephone and Telegraph
 * Co. or Unix System Laboratories, Inc. and are reproduced herein with
 * the permission of UNIX System Laboratories, Inc.
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

#if 0
#ifndef lint
static const char copyright[] =
"@(#) Copyright (c) 1980, 1990, 1993, 1994\n\
	The Regents of the University of California.  All rights reserved.\n";
#endif /* not lint */

#ifndef lint
static char sccsid[] = "@(#)df.c	8.9 (Berkeley) 5/8/95";
#endif /* not lint */
#endif
#include <sys/cdefs.h>

#include <sys/param.h>
#include <sys/stat.h>
#include <sys/mount.h>
#include <sys/sysctl.h>
#include <ufs/ufs/ufsmount.h>
#include <err.h>
#include <libutil.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sysexits.h>
#include <unistd.h>

#include <ncurses.h>

#include "extern.h"
#include "../include/smitinfo.h"

#define UNITS_SI	1
#define UNITS_2		2

WINDOW *spare;
WINDOW *listbox;
int listctr = 0;
int dummyshit;
char dummyargv;

/* Maximum widths of various fields. */
struct maxwidths {
	int	mntfrom;
	int	total;
	int	used;
	int	avail;
	int	iused;
	int	ifree;
};

static void	  addstat(struct statfs *, struct statfs *);
static char	 *getmntpt(const char *);
static int	  int64width(int64_t);
static void	  prthuman(const struct statfs *, int64_t);
static void	  prthumanval(int64_t);
static intmax_t	  fsbtoblk(int64_t, uint64_t, u_long);
static void	  prtstat(struct statfs *, struct maxwidths *);
static size_t	  regetmntinfo(struct statfs **, long, const char **);
static void	  update_maxwidths(struct maxwidths *, const struct statfs *);


static __inline int
imax(int a, int b)
{
	return (a > b ? a : b);
}

static int	aflag = 1, cflag, hflag, iflag, kflag, lflag = 0, nflag;
static struct	ufs_args mdev;

int dfmain()

{
	
	
	struct stat stbuf;
	struct statfs statfsbuf, totalbuf;
	struct maxwidths maxwidths;
	struct statfs *mntbuf;
	const char *fstype;
	char *mntpath, *mntpt;
	const char **vfslist;
	size_t i, mntsize;
	int ch, rv;

	fstype = "ufs";


	memset(&totalbuf, 0, sizeof(totalbuf));
	totalbuf.f_bsize = DEV_BSIZE;
	strncpy(totalbuf.f_mntfromname, "total", MNAMELEN);
	vfslist = NULL;

	//argc -= optind;
	//dfargv += optind;

	curses_init();

	mntsize = getmntinfo(&mntbuf, MNT_NOWAIT);
	bzero(&maxwidths, sizeof(maxwidths));
	for (i = 0; i < mntsize; i++)
		update_maxwidths(&maxwidths, &mntbuf[i]);

	rv = 0;
	//if (!*dfargv) {
	if (!dummyargv) {
		mntsize = regetmntinfo(&mntbuf, mntsize, vfslist);
		bzero(&maxwidths, sizeof(maxwidths)); 
		for (i = 0; i < mntsize; i++) {
			if (cflag)
				addstat(&totalbuf, &mntbuf[i]);
			update_maxwidths(&maxwidths, &mntbuf[i]);
		}
		if (cflag)
			update_maxwidths(&maxwidths, &totalbuf);
		
		for (i = 0; i < mntsize; i++)
			if (aflag || (mntbuf[i].f_flags & MNT_IGNORE) == 0)
				prtstat(&mntbuf[i], &maxwidths);
				getch();  // This one pauses it
		
		if (cflag)
			prtstat(&totalbuf, &maxwidths);
			listctr = 0;
		return(rv);
	}

	for (; dummyargv; dummyargv++) {
		if (stat(dummyargv, &stbuf) < 0) {
			//if ((mntpt = getmntpt(*dummyargv)) == 0) {
			//	warn("%s", *dfargv);
			//	rv = 1;
			//	continue;
			//}
		} else if (S_ISCHR(stbuf.st_mode)) {
			if ((mntpt = getmntpt(dummyargv)) == 0) {
				mdev.fspec = dummyargv;
				mntpath = strdup("/tmp/df.XXXXXX");
				if (mntpath == NULL) {
					warn("strdup failed");
					rv = 1;
					continue;
				}
				mntpt = mkdtemp(mntpath);
				if (mntpt == NULL) {
					warn("mkdtemp(\"%s\") failed", mntpath);
					rv = 1;
					free(mntpath);
					continue;
				}
				if (mount(fstype, mntpt, MNT_RDONLY,
				    &mdev) != 0) {
					warn("%s", dummyargv);
					rv = 1;
					(void)rmdir(mntpt);
					free(mntpath);
					continue;
				} else if (statfs(mntpt, &statfsbuf) == 0) {
					statfsbuf.f_mntonname[0] = '\0';
					prtstat(&statfsbuf, &maxwidths);
					if (cflag)
						addstat(&totalbuf, &statfsbuf);
				} else {
					warn("%s", dummyargv);
					rv = 1;
				}
				(void)unmount(mntpt, 0);
				(void)rmdir(mntpt);
				free(mntpath);
				continue;
			}
		} //else
			//mntpt = *dfargv;

		/*
		 * Statfs does not take a `wait' flag, so we cannot
		 * implement nflag here.
		 */
		if (statfs(mntpt, &statfsbuf) < 0) {
			warn("%s", mntpt);
			rv = 1;
			continue;
		}

		/*
		 * Check to make sure the arguments we've been given are
		 * satisfied.  Return an error if we have been asked to
		 * list a mount point that does not match the other args
		 * we've been given (-l, -t, etc.).
		 */
		if (checkvfsname(statfsbuf.f_fstypename, vfslist)) {
			rv = 1;
			continue;
		}

	//	if (argc == 1) {
		//	bzero(&maxwidths, sizeof(maxwidths));
		//	update_maxwidths(&maxwidths, &statfsbuf);
	//	}
		prtstat(&statfsbuf, &maxwidths);
		//getch();	
		if (cflag)
			addstat(&totalbuf, &statfsbuf);
	}
	if (cflag)
		prtstat(&totalbuf, &maxwidths);
		//getch();
	return (rv);
	
	
	clear();
	endwin();
	
}

int curses_init()
{
	initscr();
	clear();
	attron(A_UNDERLINE);
	mvprintw(1,25, "%s - View Diskspaces", PROG_NAME );
	attroff(A_UNDERLINE);
	
	attron(A_BOLD);
	mvprintw(3,3, "Mount Point");
	mvprintw(3,22, "Devices");
	mvprintw(3,38, "1K Blocks");
	mvprintw(3,50, "Used");
	mvprintw(3,57, "Available");		
	attroff(A_BOLD);
	box(stdscr, ACS_VLINE, ACS_HLINE);
	refresh();
	spare = newwin(12, 70, 4, 2);
	box(spare, ACS_VLINE, ACS_HLINE);
	wrefresh(spare);
	listbox = newwin(10, 68, 5, 3);
	wrefresh(listbox);
	mvprintw(20, 2, "Press Any key after Finish Viewing");
}

static char *
getmntpt(const char *name)
{
	size_t mntsize, i;
	struct statfs *mntbuf;

	mntsize = getmntinfo(&mntbuf, MNT_NOWAIT);
	for (i = 0; i < mntsize; i++) {
		if (!strcmp(mntbuf[i].f_mntfromname, name))
			return (mntbuf[i].f_mntonname);
	}
	return (0);
}

/*
 * Make a pass over the file system info in ``mntbuf'' filtering out
 * file system types not in vfslist and possibly re-stating to get
 * current (not cached) info.  Returns the new count of valid statfs bufs.
 */
static size_t
regetmntinfo(struct statfs **mntbufp, long mntsize, const char **vfslist)
{
	int error, i, j;
	struct statfs *mntbuf;

	if (vfslist == NULL)
		return (nflag ? mntsize : getmntinfo(mntbufp, MNT_WAIT));

	mntbuf = *mntbufp;
	for (j = 0, i = 0; i < mntsize; i++) {
		if (checkvfsname(mntbuf[i].f_fstypename, vfslist))
			continue;
		/*
		 * XXX statfs(2) can fail for various reasons. It may be
		 * possible that the user does not have access to the
		 * pathname, if this happens, we will fall back on
		 * "stale" filesystem statistics.
		 */
		error = statfs(mntbuf[i].f_mntonname, &mntbuf[j]);
		if (nflag || error < 0)
			if (i != j) {
				if (error < 0)
					warnx("%s stats possibly stale",
					    mntbuf[i].f_mntonname);
				mntbuf[j] = mntbuf[i];
			}
		j++;
	}
	return (j);
}

static void
prthuman(const struct statfs *sfsp, int64_t used)
{

	prthumanval(sfsp->f_blocks * sfsp->f_bsize);
	prthumanval(used * sfsp->f_bsize);
	prthumanval(sfsp->f_bavail * sfsp->f_bsize);
}

static void
prthumanval(int64_t bytes)
{
	char buf[6];
	int flags;

	flags = HN_B | HN_NOSPACE | HN_DECIMAL;
	if (hflag == UNITS_SI)
		flags |= HN_DIVISOR_1000;

	humanize_number(buf, sizeof(buf) - (bytes < 0 ? 0 : 1),
	    bytes, "", HN_AUTOSCALE, flags);

	//(void)printf("  %6s", buf);
}

/*
 * Convert statfs returned file system size into BLOCKSIZE units.
 * Attempts to avoid overflow for large file systems.
 */
static intmax_t
fsbtoblk(int64_t num, uint64_t fsbs, u_long bs)
{

	if (fsbs != 0 && fsbs < bs)
		return (num / (intmax_t)(bs / fsbs));
	else
		return (num * (intmax_t)(fsbs / bs));
}

/*
 * Print out status about a file system.
 */
static void
prtstat(struct statfs *sfsp, struct maxwidths *mwp)
{

	static u_long blocksize;
	static int headerlen, timesthrough = 0;
	static const char *header;
	int64_t used, availblks, inodes;

	if (++timesthrough == 1) {
		mwp->mntfrom = imax(mwp->mntfrom, (int)strlen("Filesystem"));
		if (hflag) {
			header = "   Size";
			mwp->total = mwp->used = mwp->avail =
			    (int)strlen(header);
		} else {
			header = getbsize(&headerlen, &blocksize);
			mwp->total = imax(mwp->total, headerlen);
		}
		mwp->used = imax(mwp->used, (int)strlen("Used"));
		mwp->avail = imax(mwp->avail, (int)strlen("Avail"));
/*
		(void)printf("%-*s %-*s %*s %*s Capacity",
		    mwp->mntfrom, "Filesystem", mwp->total, header,
		    mwp->used, "Used", mwp->avail, "Avail");
		if (iflag) {
			mwp->iused = imax(mwp->iused, (int)strlen("  iused"));
			mwp->ifree = imax(mwp->ifree, (int)strlen("ifree"));
			(void)printf(" %*s %*s %%iused",
			    mwp->iused - 2, "iused", mwp->ifree, "ifree");
		}
		(void)printf("  Mounted on\n"); */
	}
	/* Devices */
	//(void)printf("%-*s", mwp->mntfrom, sfsp->f_mntfromname);
		(void)mvwprintw(listbox,listctr, 19, "%-*s", mwp->mntfrom, sfsp->f_mntfromname);
		wrefresh(listbox);
		


	used = sfsp->f_blocks - sfsp->f_bfree;
	availblks = sfsp->f_bavail + used;
	if (hflag) {
		prthuman(sfsp, used);
	} else {
		// Spaces - 
		(void)mvwprintw(listbox, listctr, 34, " %*jd %*jd %*jd",
		    mwp->total, fsbtoblk(sfsp->f_blocks,
		    sfsp->f_bsize, blocksize),
		    mwp->used, fsbtoblk(used, sfsp->f_bsize, blocksize),
		    mwp->avail, fsbtoblk(sfsp->f_bavail,
		    sfsp->f_bsize, blocksize));  

	}
	/* Percentage */
	//(void)printf(" %5.0f%%",
	 //   availblks == 0 ? 100.0 : (double)used / (double)availblks * 100.0);
/*	if (iflag) {
		inodes = sfsp->f_files;
		used = inodes - sfsp->f_ffree;
		(void)printf(" %*jd %*jd %4.0f%% ", mwp->iused, (intmax_t)used,
		    mwp->ifree, (intmax_t)sfsp->f_ffree, inodes == 0 ? 100.0 :
		    (double)used / (double)inodes * 100.0);
	} else
		(void)printf("  "); */
		// Mounted on
	if (strncmp(sfsp->f_mntfromname, "total", MNAMELEN) != 0)
	//	(void)printf("  %s", sfsp->f_mntonname);
		(void)mvwprintw(listbox,listctr,1, "  %s", sfsp->f_mntonname);
		wrefresh(listbox);
		
	//(void)printf("\n");
	wmove(listbox, listctr++, 2);
}

void
addstat(struct statfs *totalfsp, struct statfs *statfsp)
{
	uint64_t bsize;

	bsize = statfsp->f_bsize / totalfsp->f_bsize;
	totalfsp->f_blocks += statfsp->f_blocks * bsize;
	totalfsp->f_bfree += statfsp->f_bfree * bsize;
	totalfsp->f_bavail += statfsp->f_bavail * bsize;
	totalfsp->f_files += statfsp->f_files;
	totalfsp->f_ffree += statfsp->f_ffree;
}

/*
 * Update the maximum field-width information in `mwp' based on
 * the file system specified by `sfsp'.
 */
static void
update_maxwidths(struct maxwidths *mwp, const struct statfs *sfsp)
{
	static u_long blocksize = 0;
	int dummy;

	if (blocksize == 0)
		getbsize(&dummy, &blocksize);

	mwp->mntfrom = imax(mwp->mntfrom, (int)strlen(sfsp->f_mntfromname));
	mwp->total = imax(mwp->total, int64width(
	    fsbtoblk((int64_t)sfsp->f_blocks, sfsp->f_bsize, blocksize)));
	mwp->used = imax(mwp->used,
	    int64width(fsbtoblk((int64_t)sfsp->f_blocks -
	    (int64_t)sfsp->f_bfree, sfsp->f_bsize, blocksize)));
	mwp->avail = imax(mwp->avail, int64width(fsbtoblk(sfsp->f_bavail,
	    sfsp->f_bsize, blocksize)));
	mwp->iused = imax(mwp->iused, int64width((int64_t)sfsp->f_files -
	    sfsp->f_ffree));
	mwp->ifree = imax(mwp->ifree, int64width(sfsp->f_ffree));
}

/* Return the width in characters of the specified value. */
static int
int64width(int64_t val)
{
	int len;

	len = 0;
	/* Negative or zero values require one extra digit. */
	if (val <= 0) {
		val = -val;
		len++;
	}
	while (val > 0) {
		len++;
		val /= 10;
	}

	return (len);
}

