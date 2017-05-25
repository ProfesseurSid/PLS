## DEFINITION DES VARIABLES ##
EXE=lzw
CC=gcc
CFLAGS=-g -Iheaders -Wall -Werror

SRCS=src/*
OBJS=$(SRCS:.c=.o)

## REGLE PAR DEFAUT ##
all: $(EXE)

## REGLES DE COMPILATION ##
$(EXE): $(OBJS)
	$(CC) -o bin/lzw $(OBJS) $(CFLAGS)

#.c.o:
#	$(CC) -o $@ -c $< $(CFLAGS)

## REGLE DE NETTOYAGE ##
clean:
	rm -f bin/$(EXE)
.PHONY : clean