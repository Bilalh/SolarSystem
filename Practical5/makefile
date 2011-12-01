BINARY = p4
OBJS   = Material.o Planet.o main.o
CC     = g++
CFLAGS = -Wall


all: $(BINARY)

# Linux (default)
LDFLAGS = -lGL -lGLU -lglut

# OS X
ifeq "$(shell uname)" "Darwin"
        LDFLAGS = -framework OpenGL -framework GLUT
endif

$(BINARY): $(OBJS)
	${CC} ${CFlAGS} $(LDFLAGS) $^ -o $@

clean:
	@rm  $(OBJS) $(BINARY)
