#object = open_noblock main.c main_thread_func.c register_epoll_fd.c \
Socket.c threadpool.c handle_connection.c handle_read_request.c

object = *.c
server:$(object)
	gcc -I/usr/include/mysql $(object) -L/usr/libmysql -lmysqlclient -lpthread -lhiredis -o server -g 
	#gcc -I/www/server/mysql/include $(object) -L/www/server/mysql/lib -lmysqlclient -lpthread -o server


clean:
	rm server
