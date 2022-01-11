CLIENT		= client
SERVER		= server

SERC		= server.c
CLIC		= client.c

all : $(CLIENT) $(SERVER)

$(CLIENT) : $(CLOBJ)
	@cc -Wall -Werror -Wextra client.c -o client

$(SERVER) : $(SEROBJ)
	@cc -Wall -Werror -Wextra server.c -o server

clean :
	@rm -rf server client

fclean : clean
	@rm -rf server client

re : fclean all