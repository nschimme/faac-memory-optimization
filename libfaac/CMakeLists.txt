cmake_minimum_required(VERSION 3.10)

project (faac_static LANGUAGES C)
add_compile_options(-Wall -O2 -g)
set(CMAKE_BUILD_TYPE "Debug")

# Include CheckIncludeFile module
include(CheckIncludeFile)

# Check for specific header files and define macros accordingly
check_include_file("immintrin.h" HAVE_IMMINTRIN_H)
check_include_file("inttypes.h" HAVE_INTTYPES_H)
check_include_file("stdint.h" HAVE_STDINT_H)
check_include_file("sys/types.h" HAVE_SYS_TYPES_H)

# Add compile definitions based on the header checks
if(HAVE_IMMINTRIN_H)
    add_compile_definitions(HAVE_IMMINTRIN_H)
endif()

if(HAVE_INTTYPES_H)
    add_compile_definitions(HAVE_INTTYPES_H)
endif()

if(HAVE_STDINT_H)
    add_compile_definitions(HAVE_STDINT_H)
endif()

if(HAVE_SYS_TYPES_H)
    add_compile_definitions(HAVE_SYS_TYPES_H)
endif()

list(APPEND FAAC_SOURCE
    ./bitstream.c
    ./blockswitch.c
    ./channels.c
    ./fft.c
    ./filtbank.c
    ./frame.c
    ./huff2.c
    ./huffdata.c
    ./quantize.c
    ./stereo.c
    # ./tns.c
    ./util.c
)

include_directories(../include)

# Éú³É¾²Ì¬¿â
add_library(faac STATIC ${FAAC_SOURCE})
