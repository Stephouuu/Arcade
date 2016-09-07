##
## Makefile for arcade in /home/galibe_s/rendu/cpp_arcadeold
## 
## Made by stephane galibert
## Login   <galibe_s@epitech.net>
## 
## Started on  Thu Mar 24 13:21:42 2016 stephane galibert
## Last update Tue Mar 29 20:37:22 2016 stephane galibert
##

all: 			
	make -C ./src/core/
	make -C ./src/games/nibbler/
	make -C ./src/games/pacman/
	make -C ./src/graphics/sfml/
	make -C ./src/graphics/opengl/
	make -C ./src/graphics/ncurses/

re:	fclean all

clean:
	make clean -C ./src/core/
	make clean -C ./src/games/nibbler/
	make clean -C ./src/games/pacman/
	make clean -C ./src/graphics/sfml/
	make clean -C ./src/graphics/opengl/
	make clean -C ./src/graphics/ncurses/

fclean:
	make fclean -C ./src/core/
	make fclean -C ./src/games/nibbler/
	make fclean -C ./src/games/pacman/
	make fclean -C ./src/graphics/sfml/
	make fclean -C ./src/graphics/opengl/
	make fclean -C ./src/graphics/ncurses/
