NAME				= philo_bonus

HDRS_DIR			= ./headers
SRCS_DIR			= ./src
OBJS_DIR			= ./obj

C_FILES				= philo.c \
					  philo2.c \
					  philo3.c \
					  utils.c

SRCS				= $(addprefix $(SRCS_DIR)/, $(C_FILES))
OBJS				= $(addprefix $(OBJS_DIR)/, $(C_FILES:.c=.o))
DEPENDENCIES		= $(OBJS:.o=.d)

CC					= gcc
CFLAGS				= -O3 -Wall -Werror -Wextra -I$(HDRS_DIR)
LINKER				= $(CFLAGS) -lpthread

AR					= ar
ARFLAGS				= rcs

RM					= rm
RMFLAGS				= -rf

MKDIR				= mkdir
MKDIRFLAGS			= -p

.PHONY : all clean fclean re bonus norm
.DEFAULT_GOAL := all

-include $(DEPENDENCIES)

$(OBJS_DIR)/%.o : $(SRCS_DIR)/%.c Makefile
	$(CC) $(CFLAGS) -c $< -o $@ -MD

$(OBJS_DIR) :
	$(MKDIR) $(MKDIRFLAGS) $(OBJS_DIR)

$(NAME) : $(SRCS) $(OBJS_DIR) $(OBJS) Makefile
	$(CC) $(LINKER) -o $(NAME) $(OBJS)

all : $(NAME)

bonus : $(NAME)

clean :
	$(RM) $(RMFLAGS) $(OBJS) $(DEPENDENCIES)

fclean : clean
	$(RM) $(RMFLAGS) $(NAME) $(OBJS_DIR)

norm :
	norminette $(SRCS_DIR) $(HDRS_DIR)

re: fclean all
