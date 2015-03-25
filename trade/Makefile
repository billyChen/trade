##
## Makefile for Makefile in /home/chen_c/rendu/trade
## 
## Made by Billy CHEN
## Login   <chen_c@epitech.net>
## 
## Started on  Tue May 27 16:32:21 2014 Billy CHEN
## Last update Tue May 27 16:34:24 2014 Billy CHEN
##

NAME = trade

SRC = 	main.cpp\
	Trade.cpp\

OBJ = $(SRC:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJ)
	g++ -o $(NAME) $(OBJ)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
