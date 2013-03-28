# makefile for luanewt

# Lua setup
# BSD
#LUA= /usr/local
#LUAINC= $(LUA)/include/lua51
#LUALIB= $(LUA)/lib/lua51

# Ubuntu
LUA= /usr
LUAINC= $(LUA)/include/lua5.1
LUALIB= $(LUA)/lib
LUABIN= $(LUA)/bin

# libnewt setup
LNEWT= /usr/local
LNEWTINC= $(LNEWT)/include
LNEWTLIB= $(LNEWT)/lib
 
# probably no need to change anything below here
CC= gcc
CFLAGS= $(INCS) $(WARN) -O2 -fPIC $G
WARN= -ansi -pedantic -Wall
INCS= -I$(LUAINC) -I$(LNEWTINC)
LIBS= -L$(LUALIB) -L$(LNEWTLIB) -lnewt

MYNAME= newt
MYLIB= lua$(MYNAME)

OBJS= $(MYLIB).o
#STATIC_OBJS= foobar.o
T= $(MYNAME).so

all:	so

o:	$(MYLIB).o

so:	$T

$T:	$(OBJS)
	$(CC) -o $@ -shared $(OBJS) $(STATIC_OBJS) $(LIBS) 

clean:
	rm -f $(OBJS) $T core core.*

#doc:
#	@echo "$(MYNAME) library:"
#	@fgrep '/**' $(MYLIB).c | cut -f2 -d/ | tr -d '*' | sort | column

# distribution

D= $(MYNAME)
A= $(MYLIB).tgz
TOTAR= Makefile,$(MYLIB).c,test.lua

tar:	clean
	tar zcvf $A -C .. $D
#	tar zcvf $A -C .. $D/{$(TOTAR)}

distr:	tar
	touch -r $A .stamp

# eof
