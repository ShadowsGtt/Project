object = *.c
client:$(object)
	gcc -I/usr/include/mysql $(object) -L/usr/libmysql -lmysqlclient -lpthread  -o client -g
clean:
	rm client
