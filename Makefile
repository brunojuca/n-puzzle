srcfiles := $(wildcard *.cpp) $(wildcard src/*.cpp)
objects	:= $(patsubst %.cpp, %.o, $(srcfiles))

CC = g++
CC_FLAGS = -I ./include -O3

debug_flags = -g

target = ./n-puzzle 
 
all: $(target)

$(notdir $(target)): $(objects)
	echo "Linking "$@"..."
	$(CC) $(objects) -o $@
 
%.o: %.cpp
	echo "Compiling C "$<"..."
	$(CC) $(CC_FLAGS) $(debug_flags) -c $< -o $@

clean:
	rm -rf $(objects) $(target)

.PHONY: all clean