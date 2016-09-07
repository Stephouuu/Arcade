##
## Makefile for arcade in /home/galibe_s/rendu/cpp_arcadeold/src/graphics/sfml
## 
## Made by stephane galibert
## Login   <galibe_s@epitech.net>
## 
## Started on  Thu Mar 24 13:00:42 2016 stephane galibert
## Last update Sat Apr  2 22:43:48 2016 stephane galibert
##

CXX		=	g++
RM		=	rm -f

CXXFLAGS	+=	-std=c++11 -fPIC
CXXFLAGS	+=	-W -Wextra -Wall -Werror
CXXFLAGS	+=	-I../
CXXFLAGS	+=	-I../../common/include/
CXXFLAGS	+=	-I./include/

NAME		=	../../../lib/lib_arcade_ncurses.so
SRCS		+=	src/NCursesGraphic.cpp
OBJS		=	$(SRCS:.cpp=.o)

LDFLAGS		+=	-lncurses

all:		$(NAME)

$(NAME):	$(OBJS)
		$(CXX) -shared $(OBJS) -o $(NAME) $(LDFLAGS)

re: 		fclean all

clean:
		$(RM) $(OBJS)

fclean: 	clean
		$(RM) $(NAME)
