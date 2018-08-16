CC := g++
LIBDIR := -L/usr/libmysql 
LIB := -lpthread -lmysqlclient -lhiredis 
IDIR := -I/usr/include/mysql

serv_src := $(wildcard ./server/src/*.cpp)
cli_src := $(wildcard ./client/src/*.cpp)

serv_obj := $(patsubst %.cpp,%.o,$(serv_src))
cli_obj := $(patsubst %.cpp,%.o,$(cli_src))

.PHONY : all
all: serv #cli

serv : $(serv_obj)
	$(CC) $^ $(LIBDIR) -o $@ $(LIB)
cli : $(cli_obj)
	$(CC) $^ $(LIBDIR) -o $@ $(LIB)
%.o:%.c
	$(CC) -c $^ $(IDIR)  -o $@


.PHONY:clean
clean:
	rm ./server/src/*.o 
	#rm ./client/src/*.o
	rm ./serv 
	#rm ./cli
