##
## Makefile for arcade in /home/galibe_s/rendu/cpp_arcadeold/src/graphics/sfml
## 
## Made by stephane galibert
## Login   <galibe_s@epitech.net>
## 
## Started on  Thu Mar 24 13:00:42 2016 stephane galibert
## Last update Sat Apr  2 22:44:06 2016 stephane galibert
##

CXX		=	g++
RM		=	rm -f

CXXFLAGS	+=	-std=c++11 -fPIC
CXXFLAGS	+=	-W -Wextra -Wall -Werror
CXXFLAGS	+=	-I../
CXXFLAGS	+=	-I../../common/include/
CXXFLAGS	+=	-I./include/
CXXFLAGS	+=	-I./deps/SFML-2.2/include
CXXFLAGS	+=	-I./deps/glew/include

NAME		=	../../../lib/lib_arcade_sfml.so
SRCS		+=	../../common/src/Exception.cpp
SRCS		+=	src/SFMLGraphic.cpp
OBJS		=	$(SRCS:.cpp=.o)

LDFLAGS		+=	-L./deps/glew/lib -lGLEW -lGLEWmx
LDFLAGS		+=	-L./deps/SFML-2.2/lib -lsfml-audio
LDFLAGS		+=	-lsfml-graphics -lsfml-window -lsfml-network -lsfml-system
LDFLAGS		+=	-Wl,--rpath=./deps/glew/lib/
LDFLAGS		+=	-Wl,--rpath=./deps/SFML-2.2/lib

all:		$(NAME)

$(NAME):	$(OBJS)
		$(CXX) -shared $(OBJS) -o $(NAME) $(LDFLAGS)

re: 		fclean all

clean:
		$(RM) $(OBJS)

fclean: 	clean
		$(RM) $(NAME)
