##
## Makefile for arcade in /home/galibe_s/rendu/cpp_arcadeold
## 
## Made by stephane galibert
## Login   <galibe_s@epitech.net>
## 
## Started on  Thu Mar 24 13:16:05 2016 stephane galibert
## Last update Sat Apr  2 22:44:27 2016 stephane galibert
##

CXX		=	g++
NAME		=	../../arcade
RM		=	rm -f

CXXFLAGS	+=	-std=c++11 -fPIC
CXXFLAGS	+=	-W -Wextra -Wall -Werror
CXXFLAGS	+=	-I../graphics/
CXXFLAGS	+=	-I../games/
CXXFLAGS	+=	-I../common/include/
CXXFLAGS	+=	-I./include/
CXXFLAGS	+=	-I./include/menu
CXXFLAGS	+=	-I./include/game

LDFLAGS		+=	-ldl

SRCS		+=	src/main.cpp
SRCS		+=	../common/src/Exception.cpp
SRCS		+=	../common/src/RGBA.cpp
SRCS		+=	../common/src/FileCache.cpp
SRCS		+=	src/SoLoader.cpp
SRCS		+=	src/Chrono.cpp
SRCS		+=	src/Core.cpp
SRCS		+=	src/Parser.cpp
SRCS		+=	src/LibConfigFile.cpp
SRCS		+=	src/menu/ArcadeMenu.cpp
SRCS		+=	src/menu/TextBox.cpp
SRCS		+=	src/game/ArcadeGame.cpp
OBJS		+=	$(SRCS:.cpp=.o)

all: 			$(NAME)

$(NAME):		$(OBJS)
			$(CXX) $(OBJS) $(LDFLAGS) -o $(NAME)

re: 			fclean all

clean:
			$(RM) $(OBJS)

fclean: 		clean
			$(RM) $(NAME)
