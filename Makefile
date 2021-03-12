CC = gcc
NAME = pong
SRC = src src/game src/online
OBJ	= $(wildcard src/*.c) $(wildcard src/game/*.c) $(wildcard src/online/*.c)
RM = rm -f
INCLUDES = /usr/include/SDL2 /usr/include/cjson
LIBRARIES = SDL2 SDL2_ttf cjson
CFLAGS = -Wall -Wextra -g -Werror

CFLAGS += $(foreach includedir,$(INCLUDES),-I $(includedir))
LDLIBS += $(foreach library,$(LIBRARIES),-l$(library))

$(NAME):	$(OBJ)
			$(CC) $(OBJ) -o $(NAME) $(CFLAGS) $(LDLIBS)
all:	$(NAME)
prerequisites:  
	./install_prerequisites.sh
clean:
		$(RM) $(NAME)
fclean: 	clean
		$(RM) $(NAME)

re: fclean all