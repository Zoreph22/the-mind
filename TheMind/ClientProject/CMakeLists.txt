# CMakeList.txt : CMake project for ClientProject, include source and define
# project specific logic here.
cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
add_executable (ClientProject "main.c" "main.h" "socket.c" "socket.h" "handlers.c" "input.h" "input.c" "Logic/joueur.c" "Logic/joueur.h" "Logic/lobby.h" "Logic/lobby.c" "Logic/partie.c" "Logic/partie.h"  )

# Link libraries to this project.
target_link_libraries (ClientProject PRIVATE sds)
target_link_libraries (ClientProject PRIVATE pthread)

# Link shared source files to this project.
target_link_libraries(ClientProject PRIVATE shared_socket)

# Compile options.
target_compile_options (ClientProject PRIVATE -Wall -Wextra -pedantic -Wno-unused-parameter -Wno-return-type)