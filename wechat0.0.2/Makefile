CC := gcc
LIBDIR := -L/usr/libmysql -lhiredis
LIB := -lpthread -lmysqlclient
IDIR := -I/usr/include/mysql

serv_src := $(wildcard ./server/source/*.c)
cli_src := $(wildcard ./client/source/*.c)

serv_obj := $(patsubst %.c,%.o,$(serv_src))
cli_obj := $(patsubst %.c,%.o,$(cli_src))

.PHONY : all
all: serv cli

serv : $(serv_obj)
	$(CC) $^ $(LIBDIR) -o $@ $(LIB)
cli : $(cli_obj)
	$(CC) $^ $(LIBDIR) -o $@ $(LIB)
%.o:%.c
	$(CC) -c $^ $(IDIR)  -o $@


.PHONY:clean
clean:
	rm ./server/source/*.o 
	rm ./client/source/*.o
	rm ./serv 
	rm ./cli
