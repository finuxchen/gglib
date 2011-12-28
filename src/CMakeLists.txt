SET(gglib_src main.c gg_array.c)
SET(CMAKE_C_FLAGS "-std=c99")
ADD_EXECUTABLE(gglib ${gglib_src})
#SET_TARGET_PROPERTIES(gglib PROPERTIES COMPILE_FLAGS “-std=c99”)
