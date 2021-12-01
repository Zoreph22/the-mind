# CMakeList.txt : CMake project for ServerProject, include source and define
# project specific logic here.
cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
add_executable (ServerProject
	"main.c" "main.h"
	"socket.c" "socket.h"
	"joueur.c" "joueur.h"
	"lobby.c" "lobby.h"
	"mind.c" "mind.h"
	"partie.c" "partie.h"
	"handlers.c")

# Link libraries to this project.
target_link_libraries (ServerProject PRIVATE sds)
target_link_libraries (ServerProject PRIVATE pthread)

# Link shared source files to this project.
target_link_libraries(ServerProject PRIVATE shared_socket)

# Compile options.
target_compile_options (ServerProject PRIVATE -Wall -Wextra -pedantic -Wno-unused-parameter -Wno-return-type)