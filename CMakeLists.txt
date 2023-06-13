cmake_minimum_required(VERSION 3.6.2)
project(project)

set(CMAKE_CXX_STANDARD 14)
#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
find_package(Threads)

set(SOURCE_FILES

        1_Genres.cpp
        2_Film.cpp
        3_Collection.cpp
        4_User.cpp
        5_Recommend.cpp

        1_GenresTesty.cpp
        2_FilmTesty.cpp
        3_CollecionTesty.cpp
        4_UserTesty.cpp
        5_RecommendTesty.cpp

        GoogleTest/gtest-death-test.cc
        GoogleTest/gtest-filepath.cc
        GoogleTest/gtest-port.cc
        GoogleTest/gtest-printers.cc
        GoogleTest/gtest-test-part.cc
        GoogleTest/gtest-typed-test.cc
        GoogleTest/gtest.cc
        GoogleTest/gtest_main.cc)

include_directories(GoogleTest)
add_executable(project ${SOURCE_FILES})
target_link_libraries(project ${CMAKE_THREAD_LIBS_INIT})

add_custom_command(TARGET project PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/subor.txt
        #${CMAKE_SOURCE_DIR}/new.txt
        $<TARGET_FILE_DIR:project>
        VERBATIM)
