cmake_minimum_required(VERSION 3.6)
enable_language(CXX)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# TODO project_nameを書き換える
project(MosaBackend)

# TODO ソースファイルを追加
set(proj_src
	src/main.cpp
    src/Server/Server.cpp
    src/Connection/Connection.cpp
    src/Room/RoomManager.cpp
    src/Room/Room.cpp
    src/Protocol/PacketParser.cpp
)

# add executable
add_executable(${CMAKE_PROJECT_NAME} ${proj_src})

# find boost
find_package(Boost 1.71.0 REQUIRED)
include_directories(${Boost_INCLUDE_DIRS}) 
target_link_libraries(${CMAKE_PROJECT_NAME} ${Boost_LIBRARIES})

target_compile_features(${CMAKE_PROJECT_NAME} PUBLIC cxx_std_20)
target_compile_options(${CMAKE_PROJECT_NAME} PUBLIC
    $<$<CXX_COMPILER_ID:GNU>: -O3 -Wall -Wextra -Wpedantic>
    $<$<CXX_COMPILER_ID:MSVC>: /W4 >
)

include_directories(
    ${PROJECT_SOURCE_DIR}
)

# pthreadのlink
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(${CMAKE_PROJECT_NAME} PUBLIC "-pthread")

# GoogleTest ここから
# GoogleTestをダウンロード
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/release-1.12.0.zip
)

# googletestをターゲットとして使えるようにする
FetchContent_MakeAvailable(googletest)

enable_testing()

# # TODO 単体テスト名をセット
# set(UNIT_TEST_EXECUTABLE_NAME
    # Test_FruitsGroove
# )

# # TODO 単体テスト用ソースをセット
# set(UNIT_TEST_SRC
    # src/Test/Test.cpp
# )

# # 単体テストの定義
# add_executable(${UNIT_TEST_EXECUTABLE_NAME} ${UNIT_TEST_SRC})
# target_link_libraries(${UNIT_TEST_EXECUTABLE_NAME} PRIVATE gtest_main)

# target_compile_features(${UNIT_TEST_EXECUTABLE_NAME} PUBLIC cxx_std_20)
# target_compile_options(${UNIT_TEST_EXECUTABLE_NAME} PUBLIC
    # $<$<CXX_COMPILER_ID:GNU>: -O3 -Wall -Wextra -Wpedantic>
    # $<$<CXX_COMPILER_ID:MSVC>: /W4 >
# )

# # CTestへ単体テストを登録
# include(GoogleTest)
# gtest_discover_tests(${UNIT_TEST_EXECUTABLE_NAME})


# spdlog導入
FetchContent_Declare(
    spdlog 
    GIT_REPOSITORY https://github.com/gabime/spdlog.git
    GIT_TAG v1.x
)

FetchContent_MakeAvailable(spdlog)
# target_link_libraries(${UNIT_TEST_EXECUTABLE_NAME} PUBLIC spdlog)
target_link_libraries(${CMAKE_PROJECT_NAME} PUBLIC spdlog::spdlog_header_only)