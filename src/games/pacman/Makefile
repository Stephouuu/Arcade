##
## Makefile for arcade in /home/galibe_s/rendu/cpp_arcadeold/src/games/pacman
## 
## Made by stephane galibert
## Login   <galibe_s@epitech.net>
## 
## Started on  Thu Mar 24 12:45:53 2016 stephane galibert
## Last update Sat Apr  2 22:43:33 2016 stephane galibert
##

CXX		=	g++
RM		=	rm -f

CXXFLAGS	+=	-std=c++11
CXXFLAGS	+=	-W -Wextra -Wall -Werror -fPIC
CXXFLAGS	+=	-I../
CXXFLAGS	+=	-I../../common/include/
CXXFLAGS	+=	-I./include/protocol/
CXXFLAGS	+=	-I./include/game/
CXXFLAGS	+=	-I./include/game/ghost/
CXXFLAGS	+=	-I./include/game/block/
CXXFLAGS	+=	-I./include/game/item/
CXXFLAGS	+=	-I./include/game/bonus/

NAME		=	../../../games/lib_arcade_pacman.so
SRCS		+=	../../common/src/RGBA.cpp
SRCS		+=	../../common/src/Exception.cpp
SRCS		+=	../../common/src/FileCache.cpp
SRCS		+=	../../common/src/AStar.cpp
SRCS		+=	src/game/Pacman.cpp
SRCS		+=	src/game/Generator.cpp
SRCS		+=	src/game/Player.cpp
SRCS		+=	src/game/MapData.cpp
SRCS		+=	src/game/block/PowerUp.cpp
SRCS		+=	src/game/item/PacGum.cpp
SRCS		+=	src/game/item/SPacGum.cpp
SRCS		+=	src/game/bonus/BSPacGum.cpp
SRCS		+=	src/game/ghost/Ghost.cpp
SRCS		+=	src/game/ghost/Blinky.cpp
SRCS		+=	src/game/ghost/Pinky.cpp
SRCS		+=	src/game/ghost/Inky.cpp
SRCS		+=	src/game/ghost/Clyde.cpp
SRCS		+=	src/protocol/CMDBuilder.cpp
SRCS		+=	src/protocol/CMDGetMap.cpp
SRCS		+=	src/protocol/CMDWhereAmI.cpp
SRCS		+=	src/protocol/CMDGoUp.cpp
SRCS		+=	src/protocol/CMDGoDown.cpp
SRCS		+=	src/protocol/CMDGoLeft.cpp
SRCS		+=	src/protocol/CMDGoRight.cpp
SRCS		+=	src/protocol/CMDGoForward.cpp
SRCS		+=	src/protocol/CMDShoot.cpp
SRCS		+=	src/protocol/CMDIllegal.cpp
SRCS		+=	src/protocol/CMDPlay.cpp
OBJS		=	$(SRCS:.cpp=.o)

all:		$(NAME)

$(NAME):	$(OBJS)
		$(CXX) -shared $(OBJS) $(LDFLAGS) -o $(NAME)

re: 		fclean all

clean:
		$(RM) $(OBJS)

fclean: 	clean
		$(RM) $(NAME)
