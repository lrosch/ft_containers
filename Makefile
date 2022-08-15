CC = c++
CPPFLAGS = -Wall -Wextra -Werror -std=c++98
RM = rm -f
SOURCES = main.cpp
HEADER = vector.hpp is_integral_enable_if.hpp iterator_traits.hpp map_iterator.hpp map.hpp r_map_iterator.hpp \
		r_vector_iterator.hpp rbtree.hpp stack.hpp utils.hpp vector_iterator.hpp
NAME = ft_containers
STD_NAME = std_containers

all: $(NAME) $(STD_NAME)

$(NAME): $(SOURCES) $(HEADER)
	$(CC) $(CPPFLAGS) $(SOURCES) -o $(NAME)

$(STD_NAME): $(SOURCES) $(HEADER)
	$(CC) $(CPPFLAGS) -DSTD $(SOURCES) -o $(STD_NAME)

clean:
	$(RM) $(NAME)
	$(RM) $(STD_NAME)

re: clean all
