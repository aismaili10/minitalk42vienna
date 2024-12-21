CC            = cc
CFLAGS        = -Wall -Werror -Wextra
RM            = rm -rf

LIBFT_DIR     = ./libft
LIBFT         = $(LIBFT_DIR)/libft.a

SRC_DIR       = src/
INCLUDES      = -I$(LIBFT_DIR) -I$(SRC_DIR)

NAMEC         = client
NAMES         = server
BONUS_NAMEC   = client_bonus
BONUS_NAMES   = server_bonus

SRCC_FILES    = client.c utils.c
SRCS_FILES    = server.c utils.c
BONUSC_FILES  = client_bonus.c utils_bonus.c
BONUSS_FILES  = server_bonus.c utils_bonus.c

SRCC          = $(addprefix $(SRC_DIR), $(SRCC_FILES))
SRCS          = $(addprefix $(SRC_DIR), $(SRCS_FILES))
BONUSC        = $(addprefix $(SRC_DIR), $(BONUSC_FILES))
BONUSS        = $(addprefix $(SRC_DIR), $(BONUSS_FILES))

OBJC          = $(SRCC:.c=.o)
OBJS          = $(SRCS:.c=.o)
OBJBC         = $(BONUSC:.c=.o)
OBJBS         = $(BONUSS:.c=.o)

.PHONY: all bonus clean fclean re

all:    $(NAMEC) $(NAMES)

$(NAMEC) : $(OBJC)
		@$(MAKE) -C $(LIBFT_DIR)
		$(CC) $(CFLAGS) $(OBJC) -o $(NAMEC) $(LIBFT) $(LIBFT_DIR)/printf/libftprintf.a $(INCLUDES)

$(NAMES) : $(OBJS)
		@$(MAKE) -C $(LIBFT_DIR)
		$(CC) $(CFLAGS) $(OBJS) -o $(NAMES) $(LIBFT) $(LIBFT_DIR)/printf/libftprintf.a $(INCLUDES)

bonus : $(BONUS_NAMEC) $(BONUS_NAMES)

$(BONUS_NAMEC) : $(OBJBC)
				@$(MAKE) -C $(LIBFT_DIR)
				$(CC) $(CFLAGS) $(OBJBC) -o $(BONUS_NAMEC) $(LIBFT) $(LIBFT_DIR)/printf/libftprintf.a $(INCLUDES)

$(BONUS_NAMES) : $(OBJBS)
				@$(MAKE) -C $(LIBFT_DIR)
				$(CC) $(CFLAGS) $(OBJBS) -o $(BONUS_NAMES) $(LIBFT) $(LIBFT_DIR)/printf/libftprintf.a $(INCLUDES)

clean :
		$(RM) $(OBJC) $(OBJS) $(OBJBC) $(OBJBS)
		$(MAKE) -C $(LIBFT_DIR) clean

fclean : clean
		$(RM) $(NAMEC) $(NAMES) $(BONUS_NAMEC) $(BONUS_NAMES)
		$(MAKE) -C $(LIBFT_DIR) fclean

re : fclean all

