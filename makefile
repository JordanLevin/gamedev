all: shaders main gamemodels
	g++ main.o GameModels.o ShaderLoader.o -o main -lglut -lGL -lGLEW -g

main: main.cpp
	g++ main.cpp -c -g

shaders: ./core/ShaderLoader.cpp ./core/ShaderLoader.hpp
	g++ ./core/ShaderLoader.cpp -c -g

gamemodels: ./core/GameModels.cpp ./core/GameModels.hpp
	g++ ./core/GameModels.cpp -c -g

clean:
	rm -f *.o main
