NAME = sokoban

SRCS = main.c \
	

# Cible principale
all: $(NAME)

# Règle de compilation
$(NAME): $(SRCS)
	gcc $(SRCS) -o $(NAME)  

# Supprime le fichier compilé
fclean:
	rm -f $(NAME)  

# Récompile tout
re: fclean all
