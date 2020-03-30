cmake_minimum_required( VERSION 3.1 )

project( ZZMaker )

# --  Compiler options  --------------------------------------------------------

set( CMAKE_CXX_STANDARD 14 )
set( CMAKE_CXX_STANDARD_REQUIRED ON )

# -- C++ Warning Level ---------------------------------------------------------

if ( CMAKE_COMPILER_IS_GNUCXX )
	set ( CMAKE_CXX_FLAGS "-Wall -pedantic ${CMAKE_CXX_FLAGS}" )
endif()

# -- Lib  ----------------------------------------------------------------------

set( CMAKE_AUTOMOC ON )
set( CMAKE_AUTORCC ON )
set( CMAKE_AUTOUIC ON )

find_package( Qt5 COMPONENTS Widgets REQUIRED )
set( LIBS "-lsfml-graphics -lsfml-window -lsfml-system" )

# -- C++11  --------------------------------------------------------------------

include ( CheckCXXCompilerFlag )

check_cxx_compiler_flag ( "-std=gnu++14" COMPILER_SUPPORTS_CPP14 )
check_cxx_compiler_flag ( "-std=gnu++1y" COMPILER_SUPPORTS_CPP1Y )
check_cxx_compiler_flag ( "-std=gnu++11" COMPILER_SUPPORTS_CPP11 )
check_cxx_compiler_flag ( "-std=gnu++0x" COMPILER_SUPPORTS_CPP0X )

if ( COMPILER_SUPPORTS_CPP14 )
	set ( CMAKE_CXX_FLAGS "-std=gnu++14 ${CMAKE_CXX_FLAGS}" )
elseif ( COMPILER_SUPPORTS_CPP1Y )
	set ( CMAKE_CXX_FLAGS "-std=gnu++1y ${CMAKE_CXX_FLAGS}" )
elseif ( COMPILER_SUPPORTS_CPP11 )
	set ( CMAKE_CXX_FLAGS "-std=gnu++11 ${CMAKE_CXX_FLAGS}" )
elseif( COMPILER_SUPPORTS_CPP0X )
	set ( CMAKE_CXX_FLAGS "-std=gnu++0x ${CMAKE_CXX_FLAGS}" )
else ()
	message ( STATUS "Compiler ${CMAKE_CXX_COMPILER} has no C++11/14 support." )
endif ()

message ( STATUS "Compiler flags: ${CMAKE_CXX_FLAGS}" )

# --  Includes  ---------------------------------------------------------------

include( src/character/CMakeLists.txt )
include( src/display/CMakeLists.txt )
include( src/map/CMakeLists.txt )
include( src/misc/CMakeLists.txt )

# --  Application  -------------------------------------------------------------

include_directories( src/ )

set( ZZ_MAKER_HEADERS
	${ZZ_MAKER_CHARACTER_HEADERS}
	${ZZ_MAKER_DISPLAY_HEADERS}
	${ZZ_MAKER_MAP_HEADERS}
	${ZZ_MAKER_MISC_HEADERS}
)

set( ZZ_MAKER_SOURCES
	${ZZ_MAKER_CHARACTER_SOURCES}
	${ZZ_MAKER_DISPLAY_SOURCES}
	${ZZ_MAKER_MAP_SOURCES}
	${ZZ_MAKER_MISC_SOURCES}
)

add_executable( ${CMAKE_PROJECT_NAME}
	src/main.cpp
	${ZZ_MAKER_HEADERS}
	${ZZ_MAKER_SOURCES}
)

# --  Tests  -------------------------------------------------------------------

include_directories(
	test/
)

set( ZZ_MAKER_TEST_HEADERS
)

set( ZZ_MAKER_TEST_SOURCES
)

add_executable( tests_${CMAKE_PROJECT_NAME}
		test/main_test.cpp
		${ZZ_MAKER_HEADERS}
		${ZZ_MAKER_SOURCES}
		${ZZ_MAKER_TEST_HEADERS}
		${ZZ_MAKER_TEST_SOURCES}
		)

# --  Build  -------------------------------------------------------------------

set_target_properties( ${CMAKE_PROJECT_NAME} PROPERTIES LINKER_LANGUAGE C )
target_link_libraries( ${CMAKE_PROJECT_NAME} ${LIBS} Qt5::Widgets )

set_target_properties( tests_${CMAKE_PROJECT_NAME} PROPERTIES LINKER_LANGUAGE C )
target_link_libraries( tests_${CMAKE_PROJECT_NAME} ${LIBS} Qt5::Widgets )
