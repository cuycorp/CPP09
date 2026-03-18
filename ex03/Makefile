#Executable name
NAME = PmergeMe

#Compiler and flags 
CC = c++
IFLAGS = -I include
FLAGS = -Wall -Wextra -Werror -std=c++98 ${IFLAGS}

#Header files
HDRS = include/PmergeMe.hpp

#Source files
SRCS = src/main.cpp src/PmergeMe.cpp

#Object files
OBJS = $(SRCS:src/%.cpp=obj/%.o)

all: $(NAME)

obj:
	mkdir -p obj 

$(NAME): obj $(OBJS) 
	$(CC) $(FLAGS) $(OBJS) -o $(NAME) 

#Compile individual object files
obj/%.o: src/%.cpp $(HDRS)
	$(CC) $(FLAGS) -c $< -o $@


# Clean object files
clean:
	rm -f $(OBJS)

# Clean everything
fclean: clean
	rm -f $(NAME)
	rm -rf obj
	
# Rebuild everything
re: fclean all


# Valgrind check
valgrind: $(NAME)
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(NAME)

.PHONY: all clean fclean re valgrind

