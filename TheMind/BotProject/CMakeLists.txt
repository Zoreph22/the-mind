# CMakeList.txt : CMake project for BotProject, include source and define
# project specific logic here.
cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
add_executable (BotProject "bot.c" "bot.h")

# Link libraries to this project.
target_link_libraries(BotProject PRIVATE sds)
