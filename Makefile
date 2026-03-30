##
## EPITECH PROJECT, 2023
## B-CCP-400-MPL-4-1-panoramix-marlon.pegahi
## File description:
## Makefile
##

SRC = src/main.c \
	src/displays/displays_usage.c \
	src/error_gestion/error_gestion.c \
	src/p_panoramix/panoramix.c \
	src/p_panoramix/villager.c \
	src/p_panoramix/druid.c

SRC_TESTS = tests/tests_main.c

OBJ = $(SRC:.c=.o)

CFLAGS = -W -Wall -Wextra -Werror

CPPFLAGS = -I./include

TARGET = panoramix

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) -o $(TARGET) $(OBJ)

clean:
	$(RM) $(OBJ)
	$(RM) *.gcno
	$(RM) *.gcda

fclean: clean
	$(RM) $(TARGET)
	$(RM) unit_tests

re: fclean all

tests_run:
	$(CC) -o unit_tests $(SRC_TESTS) $(CFLAGS) $(CPPFLAGS) \
	--coverage -lcriterion
	./unit_tests

gcovr_tests_run: tests_run
	gcovr . --exclude tests/
	gcovr . --branches --exclude tests/
