cmake_minimum_required(VERSION 3.9)

add_subdirectory(libft)

include_directories(libft/includes includes)

aux_source_directory(sources LIBSSL_SRC)

add_executable(ft_ssl sources/main.c ${LIBSSL_SRC})
target_link_libraries(ft_ssl ft)