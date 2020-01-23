# Targil4
Netanel Abu

Shiran Ben-Meir

## Description
This project represents a server that accepts a problem from client and finds the problem's solution using Object-Adapter design pattern 
and SOLID principles.
The program handles several clients by using parallel server. With that, the program can accept multiple problems and find their solutions.
The program is able to save previous solutions and pull solution for a problem that has already been solved by using cache manager and saving
solutions into files. If a solution for a certain problem hasn't been found in previous solutions (in cache or files) -the prgram will 
solve the problem.

In order to determine which algorithm is the best for solving the problem, 4 algorithms were tested in an empirical 
experiment-BFS, Best First Search, DFS, A* Search. The results were compared and the A* Search Algorithm was chosen and used for 
problems solving.

## main classes
- **MySerialServer**\
implements Server and handles one client.
- **MyParallelServer**\
implements Server and handles multiple clients.
- **MyClientHandler**\
implements ClientHandler. Checks if the problem has already been solved via FileCacheManager, 
 creates a Searcher object that solves the problem using search algorithm. 
- **BFS, BestFS, DFS, Astar**\
4 search algorithms that has been tested.


## Running Instructions
  in terminal, run the command:
     
        g++ -std=c++14 *.cpp -Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic -o a.out -pthread
   and then:
       
       ./a.out main.cpp


## More
github link https://github.com/netanelxa/Targil4
