.PHONY=all run clean format

CXX=g++
CXXFLAGS=-Wall
LDLIBS=-lGL -lglfw -lGLEW

SRCS := $(wildcard src/*.cpp)
OBJ := $(SRCS:%.cpp=%.o)
HEADERS=src/constants.h


all: bin/main.out

run: bin/main.out
	./bin/main.out

clean:
	rm -rf bin/main.out $(OBJ)

bin/main.out: $(OBJ) $(@D)
	$(CXX) -o $@ $(CXXFLAGS) $(OBJ) $(LDLIBS)

bin/:
	mkdir bin/

src/main.o: src/main.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

src/%.o: src/%.cpp src/%.h $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@


format:
	clang-format --style=file -i src/*.cpp src/*.h

check-format:
	@( \
		if ! clang-format --dry-run --Werror -i src/*.cpp src/*.h; then \
			echo "Formatting incorrect for C++ files!"; \
    		echo "Please run 'make format' before committing your changes,"; \
    		echo "or manually apply the changes listed above."; \
			exit 1; \
		fi; \
	)