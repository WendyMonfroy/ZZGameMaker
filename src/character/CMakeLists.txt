# --  Character  ---------------------------------------------------------------

include_directories(
	src/character/
	src/bloc/
	src/item/
	src/deco/
)


set( ZZ_MAKER_CHARACTER_HEADERS
	src/character/character.hpp
	src/character/ennemy.hpp
	src/character/player.hpp
	src/bloc/bloc.hpp
	src/item/item.hpp
	src/deco/deco.hpp
)

set( ZZ_MAKER_CHARACTER_SOURCES
	src/character/character.cpp
	src/character/ennemy.cpp
	src/character/player.cpp
	src/bloc/bloc.cpp
	src/item/item.cpp
	src/deco/deco.cpp
)
