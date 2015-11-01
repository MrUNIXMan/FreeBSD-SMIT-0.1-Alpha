CC = cc

SRCHELP = ./help
DESTHELP = /usr/local/share/smit
INSTALLDIR = /usr/local
MANSRCDIR = ./man/man1
MANDESTDIR = /usr/local/man/man1


bsdsmit:
	$(CC) -Wall -o smit -l util -l ncurses \
	src/smit.c src/mainmenu.c \
	src/sysinfo/sysinfo.c \
	src/usrandgrpmenu.c \
	src/all/bottombar.c \
	src/fsmenu.c \
	src/sfwmenu.c \
	src/scmenu.c \
	src/users/userinfo.c \
	src/users/adduser.c \
	src/users/who.c \
	src/users/usermgr.c \
	src/config/execprog.c \
	src/mount/listfs.c \
	src/mount/vfslist.c\
	src/df/df.c \
	src/fs/fsmgr.c \
	src/kern/kernmgr.c \

install:
	cp smit $(INSTALLDIR)/bin

	cp -R smitty $(INSTALLDIR)/bin
	mkdir -p $(DESTHELP)
	cp $(SRCHELP)/* $(DESTHELP)
#	gzip -9 $(MANSRCDIR)/smit.1
	cp $(MANSRCDIR)/smit.1.gz $(MANDESTDIR)



clean:
	rm *.o 
#	gunzip $(MANSRCDIR)/smit.1.gz

