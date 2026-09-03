.PHONY: run clean

all: run

test: main.cpp
	g++ -std=c++17 main.cpp -o main \
	-I/opt/homebrew/include \
	-L/opt/homebrew/lib \
       	-lsfml-graphics -lsfml-window -lsfml-system

run: test
	./main

clean:
	rm -f main
