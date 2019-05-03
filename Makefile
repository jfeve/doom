# **************************************************************************** #
#                                                           LE - /             #
#                                                               /              #
#    Makefile                                         .::    .:/ .      .::    #
#                                                  +:+:+   +:    +:  +:+:+     #
#    By: flombard <flombard@student.le-101.fr>      +:+   +:    +:    +:+      #
#                                                  #+#   #+    #+    #+#       #
#    Created: 2018/01/18 21:26:38 by jfeve        #+#   ##    ##    #+#        #
#    Updated: 2019/05/02 15:14:05 by jfeve       ###    #+. /#+    ###.fr      #
#                                                          /                   #
#                                                         /                    #
# **************************************************************************** #

#******************************************************************************#
#-----------------------------------GCC----------------------------------------#
#******************************************************************************#

CC = gcc
CC_FLAGS = -Wall -Wextra -Werror -g -fsanitize=address -F./lib
SDL_FLAGS = -rpath ./lib -F./lib -framework SDL2 \
                                                -framework SDL2_mixer \
                                                -framework SDL2_ttf \
												-lm -liconv -Wl,-framework,CoreAudio -Wl,-framework,AudioToolbox -Wl,-framework,ForceFeedback -lobjc -Wl,-framework,CoreVideo -Wl,-framework,Cocoa -Wl,-framework,Carbon -Wl,-framework,IOKit -Wl,-weak_framework,QuartzCore -Wl,-weak_framework,Metal

#******************************************************************************#
#----------------------------------LIBFT---------------------------------------#
#******************************************************************************#

NAME_LIB = libft.a
PATH_LIB = ./libft/

#******************************************************************************#
#----------------------------------SDL__---------------------------------------#
#******************************************************************************#

NAME_SDLLIB = libSDL2.a
NAME_SDLTTFLIB = libSDL2_ttf.a
NAME_SDLMIXERLIB = libSDL2_mixer.a
PATH_SDLLIB = ./lib/

#******************************************************************************#
#-----------------------------------DOOM----------------------------------------#
#******************************************************************************#

NAME = doom-nukem
PATH_SRC_DOOM = ./src/
PATH_OBJ_DOOM = ./obj/
PATH_INC_DOOM = ./incs/
FILES_DOOM = $(shell ls src | cut -d "." -f 1)
INCS = $(shell ls incs | cut -d "." -f 1)
OBJ_DOOM = $(addprefix $(PATH_OBJ_DOOM), $(addsuffix .o, $(FILES_DOOM)))
SRC_DOOM = $(addprefix $(PATH_SRC_DOOM), $(addsuffix .c, $(FILES_DOOM)))
INC_DOOM = $(addprefix $(PATH_INC_DOOM), $(addsuffix .h, $(INCS)))

#******************************************************************************#
#----------------------------------RULES---------------------------------------#
#******************************************************************************#

#.PHONY = all re

all: $(NAME)

$(NAME): $(PATH_LIB)$(NAME_LIB) $(PATH_OBJ_DOOM) $(OBJ_DOOM)
	@$(CC) $(CC_FLAGS) $(SDL_FLAGS) $(OBJ_DOOM) $(PATH_LIB)$(NAME_LIB) $(PATH_SDLLIB)$(NAME_SDLLIB) $(PATH_SDLLIB)$(NAME_SDLTTFLIB) $(PATH_SDLLIB)$(NAME_SDLMIXERLIB)\
		-o $(NAME)
	@echo "*******\nexecutable doom-nukem cree.\n*******\n"

$(PATH_OBJ_DOOM):
	@mkdir $(PATH_OBJ_DOOM)
	@echo "*******\ndossier objet cree\n*******\n"

$(PATH_OBJ_DOOM)%.o: $(PATH_SRC_DOOM)%.c $(INC_DOOM)
	@$(CC) $(CC_FLAGS) -o $@ -c $< -I $(PATH_INC_DOOM)

$(PATH_LIB)$(NAME_LIB):
	@make -C $(PATH_LIB)
	@echo "*******\nlibft.a cree\n*******\n"

re: fclean all

re_wolf3d: fclean_doom all

#******************************************************************************#
#----------------------------------CLEAN---------------------------------------#
#******************************************************************************#

#.PHONY = clean clean_lib clean_wolf3d clean_mlx

clean_doom:
	@rm -f $(OBJ_DOOM)
	@rm -rf obj
	@echo "*******\nfichiers objet de doom-nukem supprimes\n*******\n"

clean_lib :
	@make -C $(PATH_LIB) clean
	@echo "*******\nfichiers objet de la lib supprimes\n*******\n"

clean: clean_lib clean_doom
	@echo "******\ntous les fichiers objets supprimes\n*******\n"

#******************************************************************************#
#---------------------------------FCLEAN---------------------------------------#
#******************************************************************************#

fclean_doom: clean_doom
	@rm -f $(NAME)
	@echo "*******\nExecutable doom-nukem supprime\n*******\n"

fclean_lib: clean_lib
	@make -C $(PATH_LIB) fclean
	@echo "*******\nExecutable lib supprime\n*******\n"

fclean : fclean_lib fclean_doom clean
	@echo "*******\nTout executable supprime\n*******\n"
