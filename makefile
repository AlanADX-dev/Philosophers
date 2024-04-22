INCCORE=./core/

NAME = philo

SRC = $(INCCORE)philo.c $(INCCORE)utils.c $(INCCORE)utils2.c $(INCCORE)threads.c $(INCCORE)inits.c

FLAGS = -Wall -Wextra -Werror -pthread

OBJS = $(SRC:%.c=%.o)

all: $(NAME)

RM = rm -rf

$(NAME):	$(OBJS)
		gcc $(FLAGS) -o $(NAME) $(OBJS)

all: $(NAME)

clean:
	rm -rf *.o
	rm -rf $(INCCORE)*.o

fclean:
	rm -rf $(NAME)
	rm -rf *.o
	rm -rf $(INCCORE)*.o

re: clean $(NAME)

.phony: all clean fclean re
