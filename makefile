COMPILER = clang++
EXEC = a.out
FLAGS = -std=c++20 -Wall -g
SRC = $(wildcard *.cc)
OBJ = $(SRC:.cc=.o)
HEADERS = $(wildcard *.h)
IMAGE = image.ppm
LOG = log.txt

.PHONY: clean

$(EXEC): $(OBJ)
	$(COMPILER) $(FLAGS) $(OBJ) -o $(EXEC)

run: $(EXEC)
	./$(EXEC) > $(IMAGE)
	open $(IMAGE)

checkLeaks: $(EXEC)
	leaks -atExit -- ./a.out

%.o: %.cc $(HEADERS)
	$(COMPILER) $(FLAGS) -c $<

clean:
	rm -f $(OBJ) $(EXEC)
