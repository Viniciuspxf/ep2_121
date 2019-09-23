# Detecta o sistema operacional
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Darwin) # Se for MACOS
	GLLIB = -framework OpenGL -framework GLUT -framework Cocoa
else 
	GLLIB = -lGL -lGLU -lglut -lm
endif
CC     = gcc
CFLAGS = -Wall -O2 -std=c99 -pedantic -Wno-unused-result -Wno-deprecated-declarations

#------------------------------------------------

ep2: main.o graphic.o imagem.o io.o
	$(CC) main.o graphic.o imagem.o io.o -o ep2 $(GLLIB)

main.o: main.c imagem.h graphic.h io.h  
	$(CC) $(CFLAGS) -c main.c 

graphic.o: graphic.c graphic.h imagem.h  
	$(CC) $(CFLAGS) -c graphic.c 

imagem.o: imagem.c imagem.h
	$(CC) $(CFLAGS) -c imagem.c 

io.o:   io.c io.h imagem.h
	$(CC) $(CFLAGS) -c io.c 

clean:
	$(RM) *~ *.o
