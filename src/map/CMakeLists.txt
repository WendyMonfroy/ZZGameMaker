# --  Map  ---------------------------------------------------------------------

include_directories(
	src/map/
	src/map/components/
	src/map/components/graphic/
	src/map/components/physic/
	src/map/components/physic/impl/
	src/map/components/physic/impl/items/
)

set( ZZ_MAKER_MAP_HEADERS
	src/map/map.hpp
	src/map/components/graphic/case.hpp
	src/map/components/graphic/caseStock.hpp
	src/map/components/physic/map_element.hpp
)

set( ZZ_MAKER_MAP_SOURCES
	src/map/map.cpp
	src/map/components/graphic/case.cpp
	src/map/components/graphic/caseStock.cpp
	src/map/components/physic/map_element.cpp
)
