NAME = pipex
SRCDIR = ./src
SOURCES = $(SRCDIR)/pipex.c $(SRCDIR)/pipex_utils.c
OBJECTS = $(SRCDIR)/pipex.o $(SRCDIR)/pipex_utils.o
CFLAGS = -Wall -Wextra 
LIBDIR = ./lib
LIBS = -L$(LIBDIR) -lft -lftprintf 

all: $(NAME)

$(NAME): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJECTS) $(LIBS)

$(SRCDIR)/pipex.o: $(SRCDIR)/pipex.c
	$(CC) $(CFLAGS) -c $< -o $@

$(SRCDIR)/pipex_utils.o: $(SRCDIR)/pipex_utils.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS)

fclean: clean
	rm -f $(NAME)

re: fclean all
