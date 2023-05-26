srcfiles := $(wildcard *.cpp) $(wildcard src/*.cpp)
objects	:= $(patsubst %.cpp, %.o, $(srcfiles))

CC = g++
CC_FLAGS = -I ./include -O3

target = ./n-puzzle 
 
all: $(target)

$(notdir $(target)): $(objects)
	echo "Linking "$@"..."
	$(CC) $(objects) -o $@
 
%.o: %.cpp
	echo "Compiling C "$<"..."
	$(CC) $(CC_FLAGS) -c $< -o $@

clean:
	rm -rf $(objects) $(target)

.PHONY: all clean