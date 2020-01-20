cmake_minimum_required(VERSION 3.15)
project(Ex4)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS -pthread)
add_executable(Ex4 main.cpp Server.cpp Server.h MySerialServer.cpp MySerialServer.h ClientHandler.cpp ClientHandler.h MyTestClientHandler.cpp MyTestClientHandler.h Solver.cpp Solver.h
        FileCacheManager.cpp FileCacheManager.h StringReverser.cpp StringReverser.h CacheManager.cpp CacheManager.h
        Searchable.cpp Searchable.h Searcher.cpp Searcher.h OA.cpp OA.h MyClientHandler.cpp MyClientHandler.h
        Astar.cpp Astar.h BestFS.cpp BestFS.h DFS.cpp DFS.h State.cpp State.h Point.cpp Point.h MatrixBuilder.cpp MatrixBuilder.h)