SRCS=./srcs/*.c
GCC=gcc -Wall -Wextra -Werror -fsanitize=address -g -pthread
INCLUDES=./includes
NAME=philo_bonus

all : ${NAME}

${NAME} : 
	${GCC} -I ${INCLUDES} ${SRCS} -o ${NAME}

clean : 
	rm -f *.o

fclean :
	rm -f *.o
	rm -f ${NAME}

re : fclean all

.PHONY : clean fclean re all