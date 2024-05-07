NAME = pipex
SRCDIR = ./src
SOURCES = $(SRCDIR)/pipex.c
OBJECTS = $(SOURCES:.c=.o)
CFLAGS = -Wall -Wextra -fsanitize=leak
LIBDIR = ./lib
LIBS = -L$(LIBDIR) -lft -lftprintf -fsanitize=leak

all: $(NAME)

$(NAME): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJECTS) $(LIBS)

$(SRCDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS)

fclean: clean
	rm -f $(NAME)

re: fclean all


