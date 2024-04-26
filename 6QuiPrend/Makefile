CC = gcc
CFLAGS = -Wall -m64
LIBS = -lm

SRCS = jeu.c gestionjeu.c joueur.c carte.c main.c
OBJS = $(SRCS:.c=.o)
EXEC = 6quiprendLinux

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(EXEC) $(OBJS)
