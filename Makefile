LIBS=-lGL -lglfw -lGLEW
HEADERS=
FILES=./src/main.cpp ./src/shader.cpp ./src/game.cpp

main_file: $(FILES) $(HEADERS)
	g++ $(FILES)  $(LIBS) -I./include -I./src/headers
	./a.out