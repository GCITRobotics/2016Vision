# Basics
cmake_minimum_required( VERSION 2.8 )
project( Vision2016 )

# Files & Binaries
file( GLOB SOURCES "*.hpp" "*.cpp" )
add_executable( Vision2016 ${SOURCES} )

# OpenCV
find_package( OpenCV REQUIRED )
target_link_libraries( Vision2016 ${OpenCV_LIBS} )

# NetworkTables
include_directories( /usr/local/include/llvm )
include_directories( /usr/local/include/networktables )
target_link_libraries( Vision2016 /usr/local/lib/libntcore.so )

# C++11
SET( CMAKE_CXX_FLAGS "${CMAKE_CSS_FLAGS} -std=c++11" )
