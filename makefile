.PHONY=all run clean distclean format check-format mostlyclean help

CXX=g++
CXXFLAGS=-Wall
CPPFLAGS=-iquote.
LDLIBS=-lGL -lglfw -lGLEW
LDFLAGS=

SRCS := $(wildcard src/*.cpp)
OBJ := $(SRCS:%.cpp=%.o)
HEADERS=src/constants.h

MY_LIBS := libs/lodepng.o libs/shaderprogram.o

all: bin/main.out

run: bin/main.out
	./bin/main.out

mostlyclean:
	rm -rf bin/ $(OBJ)

clean: mostlyclean
	rm -rf $(MY_LIBS)

distclean: clean
	rm -rf libs/lodepng.*

bin/main.out: $(OBJ) $(MY_LIBS) bin/
	$(CXX) -o $@ $(LDFLAGS) $(OBJ) $(LDLIBS)

bin/:
	mkdir bin/

src/main.o: src/main.cpp $(HEADERS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

src/%.o: src/%.cpp src/%.h $(HEADERS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

libs/%.o: libs/%.cpp libs/%.h
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

libs/lodepng.cpp:
	wget -P libs https://raw.githubusercontent.com/lvandeve/lodepng/7fdcc96a5e5864eee72911c3ca79b1d9f0d12292/lodepng.cpp
libs/lodepng.h:
	wget -P libs https://raw.githubusercontent.com/lvandeve/lodepng/7fdcc96a5e5864eee72911c3ca79b1d9f0d12292/lodepng.h

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

help:
	@echo "Makefile for C++ && OpenGL Project"
	@echo "Computer Graphics and Visualisation - Finall Project"
	@echo "Computing 4 sem, Faculty of Computing and Telecomunications Poznań Univeristy of Technology, Summer 2020/2021."
	@echo "Authors: Jan Bylicki, Jan Chlebek, Marcin Kasznia"
	@echo
	@echo "Make options:"
	@echo "  all:           builds whole project (executable file bin/main.out)"
	@echo "  run:           runs the program (using the exectuable bin/main.out)"
	@echo "  clean:         cleans all intermediate files (.o and .out)"
	@echo "  mostlyclean:   like clean, but doesn't clean libs/*.o"
	@echo "  format:        formats source code"
	@echo "  check-format:  checks the source code formating"
	@echo "  help:          displays this help"
