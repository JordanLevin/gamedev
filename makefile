INITP = ./Core/Init
CPPFLAGS = -g -Wall -Wextra -std=c++17

all: shaders main gamemodels initglut initglew scenemanager
	g++ main.o InitGlut.o InitGlew.o GameModels.o ShaderManager.o SceneManager.o \
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

gamemodels: ./Core/GameModels.cpp ./Core/GameModels.hpp
	g++ ./Core/GameModels.cpp -c $(CPPFLAGS)

clean:
	rm -f *.o main
