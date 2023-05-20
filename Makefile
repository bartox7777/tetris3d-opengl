LIBS=-lGL -lglfw -lGLEW
HEADERS=
FILES=./src/main.cpp ./src/shader.cpp ./src/game.cpp ./src/cube.cpp ./src/camera.cpp ./src/mesh.cpp ./src/tetracube.cpp ./src/base.cpp

main_file: $(FILES) $(HEADERS)
	g++ $(FILES)  $(LIBS) -I./include -I./src/headers
	./a.out