# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/09 19:17:15 by tlebon            #+#    #+#              #
#    Updated: 2024/12/11 17:42:08 by tlebon           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

END=\033[0m

# Regular Colors
Black=\033[0;30m         # Black
Red=\033[0;31m          # Red
Green=\033[0;32m        # Green
Yellow=\033[0;33m       # Yellow
Blue=\033[0;34m         # Blue
Purple=\033[0;35m       # Purple
Cyan=\033[0;36m         # Cyan
White=\033[0;37m        # White

# Bold
BBlack=\033[1;30m       # Black
BRed=\033[1;31m         # Red
BGreen=\033[1;32m       # Green
BYellow=\033[1;33m      # Yellow
BBlue=\033[1;34m        # Blue
BPurple=\033[1;35m     # Purple
BCyan=\033[1;36m        # Cyan
BWhite=\033[1;37m       # White

# Underline
UBlack=\033[4;30m       # Black
URed=\033[4;31m         # Red
UGreen=\033[4;32m       # Green
UYellow=\033[4;33m      # Yellow
UBlue=\033[4;34m        # Blue
UPurple=\033[4;35m      # Purple
UCyan=\033[4;36m        # Cyan
UWhite=\033[4;37m       # White

# Background
On_Black=\033[40m       # Black
On_Red=\033[41m         # Red
On_Green=\033[42m         # Green
On_Yellow=\033[43m      # Yellow
On_Blue=\033[44m        # Blue
On_Purple=\033[45m      # Purple
On_Cyan=\033[46m        # Cyan
On_White=\033[47m       # White

# High Intensity
IBlack=\033[0;90m       # Black
IRed=\033[0;91m         # Red
IGreen=\033[0;92m       # Green
IYellow=\033[0;93m      # Yellow
IBlue=\033[0;94m        # Blue
IPurple=\033[0;95m      # Purple
ICyan=\033[0;96m        # Cyan
IWhite=\033[0;97m       # White

# Bold High Intensity
BIBlack=\033[1;90m      # Black
BIRed=\033[1;91m        # Red
BIGreen=\033[1;92m      # Green
BIYellow=\033[1;93m     # Yellow
BIBlue=\033[1;94m       # Blue
BIPurple=\033[1;95m     # Purple
BICyan=\033[1;96m       # Cyan
BIWhite=\033[1;97m      # White

# High Intensity backgrounds
On_IBlack=\033[0;100m   # Black
On_IRed=\033[0;101m     # Red
On_IGreen=\033[0;102m     # Green
On_IYellow=\033[0;103m    # Yellow
On_IBlue=\033[0;104m    # Blue
On_IPurple=\033[0;105m  # Purple
On_ICyan=\033[0;106m    # Cyan
On_IWhite=\033[0;107m   # White

.SUFFIXES:
.SUFFIXES: .c .o

NAME	= minishell

#---------------------COMPILATION-----------------------#
CC = cc -g
LFLAGS = -lreadline
CFLAGS = -Wall -Werror -Wextra

#-------------------------LIBFT-------------------------#
LIBFT_PATH	= libs/libft/
LIBFT_NAME	= libft.a
LIBFT		= $(LIBFT_PATH)$(LIBFT_NAME)

#-------------------------INCLUDES----------------------#
INC			=	-I ./includes/\
				-I ./libs/libft/includes\


#--------------------------SOURCES----------------------#

SRC_PATH = srcs/

BIN_PATH = bin/
EXEC_PATH = execution/
PARS_PATH = parsing/

SRC =																		\
		$(BIN_PATH)bin_utils.c												\
		$(BIN_PATH)cd.c														\
		$(BIN_PATH)echo.c													\
		$(BIN_PATH)env.c													\
		$(BIN_PATH)exec_bin.c												\
		$(BIN_PATH)exit.c													\
		$(BIN_PATH)export.c													\
		$(BIN_PATH)pwd.c													\
		$(BIN_PATH)unset.c													\
		$(BIN_PATH)update_env.c												\
		$(EXEC_PATH)bool.c													\
		$(EXEC_PATH)command.c												\
		$(EXEC_PATH)exec_cmd.c												\
		$(EXEC_PATH)free.c													\
		$(EXEC_PATH)here_doc_norm.c													\
		$(EXEC_PATH)here_doc.c												\
		$(EXEC_PATH)in_out_files.c											\
		$(EXEC_PATH)manager.c												\
		$(EXEC_PATH)pipe.c													\
		$(EXEC_PATH)utils.c													\
		$(PARS_PATH)debug.c													\
		$(PARS_PATH)env.c													\
		$(PARS_PATH)errors.c												\
		$(PARS_PATH)finishes.c												\
		$(PARS_PATH)finishes_normer.c										\
		$(PARS_PATH)parsing.c												\
		$(PARS_PATH)tokens.c												\
		$(PARS_PATH)free.c													\
		$(PARS_PATH)utils.c													\
		$(PARS_PATH)type_readers.c											\
		$(PARS_PATH)init.c													\
		$(PARS_PATH)utils_2.c												\
		main.c																\
		
SRCS		= $(addprefix $(SRC_PATH), $(SRC))

#------------------------------OBJ-------------------------#
OBJ			= $(SRC:.c=.o)
OBJS		= $(addprefix $(OBJ_PATH), $(OBJ))
OBJ_PATH	= obj/

#-------------------------------HDR------------------------#
HDR			=	includes/minishell.h										\

#----------------------------------------------------------#

vpath %.c $(SRC_PATH) $(SRC_PATH)(BIN_PATH) $(SRC_PATH)$(EXEC_PATH) $(SRC_PATH)$(PARS_PATH)

all: $(NAME)

$(NAME): $(OBJS)
	@make -sC $(LIBFT_PATH)
	@$(CC) $(CFLAGS) -o $@ $(OBJS) $(LIBFT) $(LFLAGS) $(INC)
	@echo "\n$(On_Purple)Minishell is ready bébou 😳 👉👈 $(END)\n"

$(OBJ_PATH)%.o: $(SRC_PATH)%.c $(HDR)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@ $(INC)

clean:
	@rm -rf $(OBJ_PATH) 
	@echo "$(Green)\nC'est propre...\n$(END)"	

fclean: clean
	@make -sC $(LIBFT_PATH) fclean  
	@rm -rf $(NAME)
	@echo "$(BGreen)tres tres propre !\n$(END)"

re: fclean all

.PHONY: all re clean fclean% 
