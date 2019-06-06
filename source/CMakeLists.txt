project(gearbox)
cmake_minimum_required(VERSION 3.0)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(SOURCES Utility.cpp
            Viewer.cpp
			Constants.cpp
			Drawable.cpp
			GLBase.cpp
			GLSLProgram.cpp
			Model.cpp
			ElementModel.cpp
            ArrayModel.cpp
			Material.cpp
			ProgramLoader.cpp
			Projection.cpp
            Types.cpp
			TBN.cpp
            Image2D.cpp
			VertexLayout.cpp
            ArrayDrawable.cpp
			ElementDrawable.cpp
            BezierCubic.cpp
			DrawableLoader.cpp)

set (CMAKE_CXX_FLAGS "-std=c++0x -stdlib=libc++ -g3 -Wall -O0")

string(REGEX REPLACE "\\.cpp" ".h " HEADERS ${SOURCES})
set(HEADERS "${HEADERS} Vector.h")
set(HEADERS "${HEADERS} Matrix.h")
set(HEADERS "${HEADERS} MatrixTransform.h")
set(HEADERS "${HEADERS} Types.h")
set(HEADERS "${HEADERS} glcorearb.h")
separate_arguments(HEADERS)

foreach(arg ${HEADERS})
  set(INCLUDE_HEADERS "${INCLUDE_HEADERS}#include <gearbox/${arg}>\n")
endforeach(arg ${HEADERS})
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Headers.h ${CMAKE_CURRENT_SOURCE_DIR}/Gearbox.h)

include_directories(${FreeImage_INCLUDE_DIR})

find_package(Qt5Widgets REQUIRED)

add_library(gearbox STATIC ${SOURCES})

qt5_use_modules(gearbox Widgets)

install(TARGETS gearbox CONFIGURATIONS Debug ARCHIVE DESTINATION dbg-lib)
install(TARGETS gearbox CONFIGURATIONS Release ARCHIVE DESTINATION lib)
install(FILES ${HEADERS} DESTINATION ${CMAKE_INSTALL_PREFIX}/include/gearbox)
install(FILES Gearbox.h DESTINATION ${CMAKE_INSTALL_PREFIX}/include/gearbox)
