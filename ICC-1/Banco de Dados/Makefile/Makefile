CC= gcc
INCLUDES= include 
SOURCES= source/utils.c source/archive.c
BINARY= ./main
PROG= source/main.c
FLAGS= -Wall -Werror -g -lm

all:
	@$(CC) -o $(BINARY) $(PROG) $(SOURCES) -I$(INCLUDES) $(FLAGS)

run:
	$(BINARY)

zip:
	zip -r BancoDados.zip include source main Makefile
