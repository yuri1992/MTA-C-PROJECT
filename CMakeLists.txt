cmake_minimum_required(VERSION 3.3)
project(MTA-C-PROJECT)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wextra -Wall -pedantic -Wvla -std=c99")

#set(SOURCE_FILES utils/keyvalue.c)
#set(SOURCE_FILES utils/keyvalue.h)
#set(SOURCE_FILES utils/lineinteperter.c)
#set(SOURCE_FILES utils/lineinteperter.h)
#set(SOURCE_FILES datastructure.c)
#set(SOURCE_FILES datastructure.h)

file(GLOB files "*.h" "*.c")

add_executable(MTA-C-PROJECT ${files} ${SOURCE_FILES} main.c)