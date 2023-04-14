LIBS=-lGL -lglfw -lGLEW
HEADERS=
FILES=./src/main.cpp

main_file: $(FILES) $(HEADERS)
	g++ $(FILES)  $(LIBS) -I./include
