cmake_minimum_required(VERSION 3.10)

project (faac_static LANGUAGES C)
add_compile_options(-Wall -O2 -g)
set(CMAKE_BUILD_TYPE "Debug")

add_compile_definitions(
    # Define if you have the <immintrin.h> header file.
    HAVE_IMMINTRIN_H

    # Define if you have the <inttypes.h> header file.
    # HAVE_INTTYPES_H
    
    # Define  if you have the <stdint.h> header file.
    # HAVE_STDINT_H
    
    # Define to 1 if you have the <sys/types.h> header file.
    # HAVE_SYS_TYPES_H
    )

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
    ./tns.c
    ./util.c
)

include_directories(../include)

# Éú³É¾²Ì¬¿â
add_library(faac STATIC ${FAAC_SOURCE})
