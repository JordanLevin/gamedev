INITP = ./Core/Init
CPPFLAGS = -Wall -Wextra -std=c++17 -Wno-unused-parameter -g #-pg
CC = g++
LIBS = -lglut -lGL -lGLEW -lm

all: ShaderManager.o main.o InitGlut.o InitGlew.o SceneManager.o ModelManager.o \
	Model.o Camera.o CubeCluster.o World.o
	$(CC) main.o InitGlut.o InitGlew.o ShaderManager.o SceneManager.o Model.o\
		ModelManager.o Camera.o CubeCluster.o World.o\
		-o main $(LIBS) $(CPPFLAGS)

main.o: main.cpp
	$(CC) main.cpp -c $(CPPFLAGS)

InitGlut.o: $(INITP)/InitGlew.cpp $(INITP)/InitGlut.cpp $(INITP)/ContextInfo.hpp \
					$(INITP)/FrameBufferInfo.hpp $(INITP)/WindowInfo.hpp $(INITP)/DebugOutput.hpp \
					./Managers/SceneManager.hpp
	$(CC) $(INITP)/InitGlut.cpp -c -o InitGlut.o $(CPPFLAGS)

InitGlew.o: $(INITP)/InitGlew.cpp $(INITP)/InitGlew.hpp  
	$(CC) $(INITP)/InitGlew.cpp -c -o InitGlew.o $(CPPFLAGS)

ShaderManager.o: ./Managers/ShaderManager.cpp ./Managers/ShaderManager.hpp
	$(CC) ./Managers/ShaderManager.cpp -c $(CPPFLAGS)

SceneManager.o: ./Managers/SceneManager.cpp ./Managers/SceneManager.hpp $(INITP)/IListener.hpp ./Input/Camera.hpp
	$(CC) ./Managers/SceneManager.cpp -c $(CPPFLAGS)

ModelManager.o: ./Managers/ModelManager.cpp ./Managers/ModelManager.hpp $(INITP)/IListener.hpp ./Lib/OctTree.hpp
	$(CC) ./Managers/ModelManager.cpp -c $(CPPFLAGS)

#Cube.o: ./Rendering/Models/Cube.cpp ./Rendering/Models/Cube.hpp
	#$(CC) ./Rendering/Models/Cube.cpp -c $(CPPFLAGS)

#IndexCube.o: ./Rendering/Models/IndexCube.cpp ./Rendering/Models/IndexCube.hpp
	#$(CC) ./Rendering/Models/IndexCube.cpp -c $(CPPFLAGS)

CubeCluster.o: ./Rendering/Models/CubeCluster.cpp ./Rendering/Models/CubeCluster.hpp ./Lib/Serialize.hpp
	$(CC) ./Rendering/Models/CubeCluster.cpp -c $(CPPFLAGS)

World.o: ./Rendering/Models/World.cpp ./Rendering/Models/World.hpp
	$(CC) ./Rendering/Models/World.cpp -c $(CPPFLAGS)

Model.o: ./Rendering/Models/Model.cpp ./Rendering/Models/Model.hpp
	$(CC) ./Rendering/Models/Model.cpp -c $(CPPFLAGS)

Camera.o: ./Input/Camera.cpp ./Input/Camera.hpp
	$(CC) ./Input/Camera.cpp -c $(CPPFLAGS)

clean:
	rm -f *.o main
