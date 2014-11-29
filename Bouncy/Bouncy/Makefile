CPP_FILES := $(shell find . -name "*.cpp" )
COMPILE_FLAGS := -lglut -lGL -lGLU -lGLEW -std=c++11
EXECUTABLE_NAME := main.out

all:
	g++ $(CPP_FILES) -w -o $(EXECUTABLE_NAME) $(COMPILE_FLAGS)

mac:
	g++ /System/Library/Frameworks/GLUT.framework/GLUT /System/Library/Frameworks/OpenGL.framework/OpenGL /System/Library/Frameworks/Cocoa.framework/Cocoa $(CPP_FILES) -w -o $(EXECUTABLE_NAME) -std=c++11