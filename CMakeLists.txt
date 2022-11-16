cmake_minimum_required(VERSION 3.5)

project(MonteCarlo LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(MonteCarlo
    main.cpp
    MonteCarloBot.cpp
    Player.cpp
    TicTacToeGame.cpp
    Player.h
    TicTacToeGame.h
    MonteCarloBot.h
)
