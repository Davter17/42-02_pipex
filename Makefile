NAME = pipex

SRCS_DIR = src
OBJ_DIR = .obj
INC_DIR = inc

LIBRARYC_URL = https://github.com/Davter17/MyLibrary.git
LIBRARYC_DIR = .deps/libraryC
LIBRARYC_INC = $(LIBRARYC_DIR)/inc
LIBRARYC_LIB = $(LIBRARYC_DIR)/libraryC.a

SRCS = $(SRCS_DIR)/main.c \
       $(SRCS_DIR)/find_executable.c \
       $(SRCS_DIR)/child_process.c \
       $(SRCS_DIR)/utils.c

SRCS_BONUS = $(SRCS_DIR)/main_bonus.c \
             $(SRCS_DIR)/find_executable.c \
             $(SRCS_DIR)/child_process.c \
             $(SRCS_DIR)/utils.c \
             $(SRCS_DIR)/pipe_utils.c \
             $(SRCS_DIR)/process.c

OBJS = $(patsubst $(SRCS_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))
OBJS_BONUS = $(patsubst $(SRCS_DIR)/%.c,$(OBJ_DIR)/bonus_%.o,$(SRCS_BONUS))

CC = cc
CFLAGS = -Wall -Wextra -Werror -I$(INC_DIR) -I$(LIBRARYC_INC)
AR = ar rcs

.PHONY: all clean fclean re bonus

all: $(LIBRARYC_LIB) $(NAME)

$(OBJ_DIR)/%.o: $(SRCS_DIR)/%.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/bonus_%.o: $(SRCS_DIR)/%.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	@printf "  \033[33m⚙\033[0m  Compiling %d files...\n" $(words $(OBJS))
	@mkdir -p $(OBJ_DIR)

$(LIBRARYC_LIB):
	@if [ ! -d "$(LIBRARYC_DIR)" ]; then \
		printf "  \033[33m⚙\033[0m  Cloning libraryC...\n"; \
		git clone $(LIBRARYC_URL) $(LIBRARYC_DIR) > /dev/null 2>&1; \
	fi
	@$(MAKE) --no-print-directory -C $(LIBRARYC_DIR)

$(NAME): $(OBJS) $(LIBRARYC_LIB)
	@printf "  \033[32m✓\033[0m Compiled %d files → $(NAME)\n" $(words $(OBJS))
	@$(CC) $(CFLAGS) $(OBJS) $(LIBRARYC_LIB) -o $(NAME)

bonus: $(OBJS_BONUS) $(LIBRARYC_LIB)
	@printf "  \033[32m✓\033[0m Compiled %d files → $(NAME) (bonus)\n" $(words $(OBJS_BONUS))
	@$(CC) $(CFLAGS) $(OBJS_BONUS) $(LIBRARYC_LIB) -o $(NAME)

clean:
	@printf "  \033[31m✗\033[0m  Removing object files...\n"
	@rm -rf $(OBJ_DIR)
	@if [ -d "$(LIBRARYC_DIR)" ]; then \
		$(MAKE) --no-print-directory clean -C $(LIBRARYC_DIR); \
	fi

fclean: clean
	@printf "  \033[31m✗\033[0m  Removing $(NAME)...\n"
	@rm -f $(NAME)
	@if [ -d "$(LIBRARYC_DIR)" ]; then \
		$(MAKE) --no-print-directory fclean -C $(LIBRARYC_DIR); \
	fi

re: fclean all
