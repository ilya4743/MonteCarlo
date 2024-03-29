cmake_minimum_required(VERSION 3.5)

project(MonteCarlo VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

set(PROJECT_SOURCES
        src/main1.cpp
        src/MonteCarloBot.cpp
        src/Player.cpp
        src/TicTacToeGame.cpp
        src/MonteCarloBot.h
        src/Player.h
        src/TicTacToeGame.h
        TTTCommonTypes.h
        AIAgent.h
        MiniMaxAgent.h
        NoAgent.h
        MiniMaxAgent.cpp
        TTTController.h
        TTTController.cpp
        Board.h
        Board.cpp
        TicTacToeGame1.h
        TitleScreen.h
        TitleScreen.cpp
        TicTacToeGame1.cpp
        #main.cpp
        TicTacToeGame.ui
        titlescreen.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(MonteCarlo
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET MonteCarlo APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(MonteCarlo SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(MonteCarlo
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(MonteCarlo PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

set_target_properties(MonteCarlo PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(MonteCarlo)
endif()
