cmake_minimum_required(VERSION 3.10.0)
project(c01-win-init VERSION 0.1.0 LANGUAGES C CXX)

set(SRC_FILES
    main.cpp
    Socket.hpp
    Socket.cpp
)

if (WIN32)
    list(APPEND SRC_FILES
        SocketWin.cpp
    )
elseif(UNIX)
    list(APPEND SRC_FILES
        SocketUnix.cpp
    )
endif ()

add_executable(${PROJECT_NAME}
    ${SRC_FILES}
)
