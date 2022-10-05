SRC= $(wildcard *.cpp)
OBJFILES= $(SRC:.cpp=.o)
COMPILER= g++
PROGRAMNAME= progGrafica
all: $(OBJFILES)
	$(COMPILER) -g $(OBJFILES) -lGL -lGLEW -lglfw  -o $(PROGRAMNAME)
%.o: %.cpp
	$(COMPILER) -g -c $< -o $@
clean:
	rm $(OBJFILES)
