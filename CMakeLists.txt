cmake_minimum_required (VERSION 2.8)
project (libuart)
include_directories("include")

SET(CMAKE_C_COMPILER avr-gcc)

#SET(CMAKE_CXX_COMPILER avr-gcc)

SET(CMAKE_SHARED_LIBRARY_LINK_C_FLAGS "")
#set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall")
#set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Werror")
#set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -ggdb3")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -mmcu=$ENV{DEVICE} -DF_CPU=$ENV{FREQ} -Os -Werror -Wall -Wmissing-prototypes" )

add_library(stdioconf STATIC src/stdioconf.c)
add_library(uart STATIC src/uart.c)
add_library(twi STATIC src/twi.c)
add_library(adc STATIC src/adc.c)

#add_executable(main test/main.c)
#target_link_libraries(main uart twi)

