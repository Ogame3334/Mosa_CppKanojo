cmake_minimum_required(VERSION 3.6)
enable_language(CXX)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# TODO project_nameを書き換える
project(MosaBackend)

# TODO ソースファイルを追加
set(proj_src
	main.cpp
)

add_executable(${CMAKE_PROJECT_NAME} ${proj_src})

target_compile_features(${CMAKE_PROJECT_NAME} PUBLIC cxx_std_20)
target_compile_options(${CMAKE_PROJECT_NAME} PUBLIC
    $<$<CXX_COMPILER_ID:GNU>: -O3 -Wall -Wextra -Wpedantic>
    $<$<CXX_COMPILER_ID:MSVC>: /W4 >
)

include_directories(
    ${PROJECT_SOURCE_DIR}
)