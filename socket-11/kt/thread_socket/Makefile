all:server client

server:server.c wrap.c
	gcc $^ -DDEBUG -lpthread -o $@

client:client.c wrap.c
	gcc $^ -DDEBUG -o $@

.PHONY:clean
clean:
	rm -rf server client
