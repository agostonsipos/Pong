cmake_minimum_required(VERSION 3.5)

add_executable(Pong
events.cpp
events.h
game.cpp
game.h
main.cpp
)

set(CMAKE_CXX_FLAGS "-std=c++98")


find_library(SDL_LIB NAME SDL HINTS ${libdir})
find_library(SDL_ttf_LIB NAME SDL_ttf HINTS ${libdir})
find_library(SDL_mixer_LIB NAME SDL_mixer HINTS ${libdir})

target_link_libraries(Pong PUBLIC ${SDL_LIB})
target_link_libraries(Pong PUBLIC ${SDL_ttf_LIB})
target_link_libraries(Pong PUBLIC ${SDL_mixer_LIB})
