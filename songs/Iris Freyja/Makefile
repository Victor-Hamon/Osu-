##
## EPITECH PROJECT, 2018
## Makefile
## File description:
## Makefile for corewar
##

NAME		=	\033[01m\e[35mosu?\e[0m
NAME_EXE		=	osu?
CC			=	gcc
CPPFLAGS	=	-I./include -ggdb3

SRC_PATH	=	src
SRC			=	main.c

OBJ_PATH	=	obj
OBJ			=	$(SRC:%.c=$(OBJ_PATH)/%.o)

COLOR		=	\e[32m
COLOR_END	=	\e[0m

.SILENT:

all: init $(NAME) finish

init:
	echo -ne "\e[32m\e[01mBuilding $(NAME)\e[32m\e[01m on "
	TZ='Europe/Paris' date +"%x, %T" ; echo ""
	echo ""
	mkdir -p $(OBJ_PATH)

finish:
	if [ "$(compiled)" == "" ]; then \
		echo "\031[01mNo scripts compiled.\e[0m"; \
	else \
		echo -ne "\n\e[32m\e[01m\e[05mCompiled "; \
		echo "$(compiled)" | wc -w | tr -d "\n"; echo -e " script(s).\e[0m"; \
	fi
	echo -e "\033[07m\e[31mGenerated executable \e[0m\"$(NAME)\"."

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	$(eval compiled += $<)
	echo -e "\e[32m\e[01mCompiling \e[33m\e[01m$<"
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(NAME_EXE)

clean:
	rm -Rf obj/
	printf "%-16b \033[07m\e[32mCleaned object files.\e[0m\n" "[$(NAME)]:"

fclean: clean
	rm -f $(NAME)
	printf "%-16b \033[07m\e[32mRemoved executable.\e[0m\n" "[$(NAME)]:"

re:
	make fclean
	echo ""
	make all

.PHONY: all init finish clean fclean re
