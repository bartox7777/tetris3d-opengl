LIBS=-lGL -lglfw -lGLEW
HEADERS=
FILES=./src/main.cpp ./src/shader.cpp

main_file: $(FILES) $(HEADERS)
	g++ $(FILES)  $(LIBS) -I./include
	./a.out