
  #  Project : Compression sans perte
	#
  #  Authors : CHANET Zoran, EZ-ZINE Najwa, LAFRASSE Cedric, MANEVAL Thibaud
	#
  #  Date : 30/05/2017


all: executable

CC = gcc
INC_DIR= ../headers
BIN_DIR = ../bin
SRCS = main.c compression.c decompression.c dict.c 

OBJS := $(SRCS:%.c=$(BIN_DIR)/%.o)

C_FLAGS= -g -Wmissing-prototypes -Wall -Werror

$(OBJS): $(BIN_DIR)/%.o : %.c
	  $(CC) $(C_FLAGS) -c $< -o $@

executable :	$(OBJS)
	$(CC) -o executable $(OBJS) $(LFLAGS)


clean:
	rm -f *.o compression decompression executable *~ $(BIN_DIR)/*.o
