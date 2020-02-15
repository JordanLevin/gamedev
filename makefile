INITP = ./Core/Init
CPPFLAGS = -g -Wall -Wextra -std=c++17

all: shaders main initglut initglew scenemanager modelmanager triangle quad model 
	g++ main.o InitGlut.o InitGlew.o ShaderManager.o SceneManager.o Model.o\
		ModelManager.o Triangle.o Quad.o \
		-o main -lglut -lGL -lGLEW $(CPPFLAGS)

main: main.cpp
	g++ main.cpp -c $(CPPFLAGS)

initglut: $(INITP)/InitGlew.cpp $(INITP)/InitGlut.cpp $(INITP)/ContextInfo.hpp \
					$(INITP)/FrameBufferInfo.hpp $(INITP)/WindowInfo.hpp
	g++ $(INITP)/InitGlut.cpp -c -o InitGlut.o $(CPPFLAGS)

initglew: $(INITP)/InitGlew.cpp $(INITP)/InitGlew.hpp  
	g++ $(INITP)/InitGlew.cpp -c -o InitGlew.o $(CPPFLAGS)

shaders: ./Managers/ShaderManager.cpp ./Managers/ShaderManager.hpp
	g++ ./Managers/ShaderManager.cpp -c $(CPPFLAGS)

scenemanager: ./Managers/SceneManager.cpp ./Managers/SceneManager.hpp $(INITP)/IListener.hpp
	g++ ./Managers/SceneManager.cpp -c $(CPPFLAGS)

modelmanager: ./Managers/ModelManager.cpp ./Managers/ModelManager.hpp $(INITP)/IListener.hpp
	g++ ./Managers/ModelManager.cpp -c $(CPPFLAGS)

triangle: ./Rendering/Models/Triangle.cpp ./Rendering/Models/Triangle.hpp
	g++ ./Rendering/Models/Triangle.cpp -c $(CPPFLAGS)

quad: ./Rendering/Models/Quad.cpp ./Rendering/Models/Quad.hpp
	g++ ./Rendering/Models/Quad.cpp -c $(CPPFLAGS)

model: ./Rendering/Models/Model.cpp ./Rendering/Models/Model.hpp
	g++ ./Rendering/Models/Model.cpp -c $(CPPFLAGS)

clean:
	rm -f *.o main
