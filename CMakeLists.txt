cmake_minimum_required(VERSION 3.0)

project(advcpp)

SET(CMAKE_CXX_STANDARD 20)
#SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20")
#set(CMAKE_CXX_FLAGS " -fcoroutines-ts -fno-exceptions -pthread -fexceptions -stdlib=libc++")
#set(CMAKE_CXX_FLAGS " -fno-exceptions -pthread -fexceptions -std=c++20")
include_directories("cppcoro/include")

add_executable(midterm1 "midterm1.cpp")
add_executable(midterm2 "midterm2.cpp")

add_executable(w1a1 "week1-app1.cpp")
add_executable(w1a2 "week1-app2.cpp")
add_executable(w2a1 "week2-app1.cpp")
add_executable(w3a1 "week3-app1.cpp")
add_executable(w3a2 "week3-app2.cpp")
add_executable(w3a3 "week3-app3.cpp")
add_executable(w4a1 "week4-app1.cpp")
add_executable(w4a2 "week4-app2.cpp")
add_executable(w5a1 "week5-app1.cpp")
add_executable(w5a2 "week5-app2.cpp")
add_executable(w6a1 "week6-app1.cpp")
add_executable(w7a1 "week7-app1.cpp")
add_executable(w7a2 "week7-app2.cpp")
add_executable(w7a3 "week7-app3.cpp")
add_executable(w7a4 "week7-app4.cpp")
add_executable(w8a1 "week8-app1.cpp")
add_executable(w8a2 "week8-app2.cpp")
add_executable(w8a3 "week8-app3.cpp")
add_executable(w8a4 "week8-app4.cpp")
add_executable(w9a1 "week9-app1.cpp")
add_executable(w9a2 "week9-app2.cpp")
add_executable(w9a3 "week9-app3.cpp")
add_executable(w10a1 "week10-app1.cpp")
add_executable(w10a2 "week10-app2.cpp")
add_executable(w10a3 "week10-app3.cpp")
add_executable(w11a1 "week11-app1.cpp")
add_executable(w11a2 "week11-app2.cpp")
add_executable(w12a1 "week12-app1.cpp")
add_executable(w12a2 "week12-app2.cpp")
add_executable(w12a3 "week12-app3.cpp")
add_executable(w12a4 "week12-app4.cpp")
add_executable(w12a5 "week12-app5.cpp")
add_executable(w13a1 "week13-app1.cpp")
add_executable(w13a2 "week13-app2.cpp")
add_executable(w13a3 "week13-app3.cpp")
add_executable(w13a4 "week13-app4.cpp")
add_executable(w13a5 "week13-app5.cpp")
#add_executable(w13a6 "week13-app6.cpp")
#add_executable(w14a1 "week14-app1.cpp")
#add_executable(w14a2 "week14-app2.cpp")
#add_executable(w14a3 "week14-app3.cpp" "less_macro.hpp")
#add_executable(w14a4 "week14-app4.cpp")
#add_executable(w14a5 "week14-app5.cpp" "cppcoro/lib/lightweight_manual_reset_event.cpp")
add_executable(p1 "p1.cpp")
