##
## Makefile for  in /home/avelin_j/Work/cpp_arcade/src/graphics/opengl
## 
## Made by avelin_j
## Login   <avelin_j@epitech.net>
## 
## Started on  Sun Mar 27 23:41:00 2016 avelin_j
## Last update Sun Apr  3 14:20:08 2016 stephane galibert
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

NAME		=	../../../lib/lib_arcade_opengl.so
SRCS		+=	src/OpenGLGraphic.cpp
SRCS		+=	../../common/src/Exception.cpp
OBJS		=	$(SRCS:.cpp=.o)

LDFLAGS		+=	-L./deps/glew/lib -lGLEW -lGLEWmx
LDFLAGS		+=	-L./deps/SFML-2.2/lib -lsfml-audio
LDFLAGS		+=	-lsfml-graphics -lsfml-window -lsfml-network -lsfml-system
LDFLAGS		+=	-lGL -lGLU
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
