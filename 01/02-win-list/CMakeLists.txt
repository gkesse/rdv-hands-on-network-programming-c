cmake_minimum_required(VERSION 3.10.0)
project(c01-win-list VERSION 0.1.0 LANGUAGES C CXX)

set(SRC_FILES
    main.cpp
    Adapter.hpp
    Adapter.cpp
    Tools.hpp
    Tools.cpp
)

if (WIN32)
    list(APPEND SRC_FILES
        AdapterWin.cpp
    )
elseif(UNIX)
    list(APPEND SRC_FILES
        AdapterUnix.cpp
    )
endif ()

add_executable(${PROJECT_NAME}
    ${SRC_FILES}
)
