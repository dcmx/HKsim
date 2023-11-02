cmake_minimum_required (VERSION 3.1)
project (hk)

set(CMAKE_CXX_STANDARD 11)

add_executable (hk main.cpp nxWindow/window.cpp nxWindow/drawlayer.cpp nxWindow/color.cpp nxWindow/primitives/circle.cpp nxWindow/primitives/dashedline.cpp nxWindow/primitives/disk.cpp nxWindow/primitives/line.cpp nxWindow/primitives/linewidth.cpp nxWindow/primitives/points.cpp nxWindow/primitives/pointsize.cpp nxWindow/textlayer.cpp nxWindow/primitives/disksector.cpp)
target_link_libraries (hk GL GLU glut m pthread )

