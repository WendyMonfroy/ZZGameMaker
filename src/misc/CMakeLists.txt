# --  Miscellaneous  -----------------------------------------------------------

include_directories(
	src/misc/
	src/misc/enums/
	src/misc/utils/
)

set( ZZ_MAKER_MISC_HEADERS
	src/misc/enums/direction.hpp
	src/misc/enums/type.hpp
	src/misc/utils/hitbox.hpp
	src/misc/utils/dimensions.hpp
)

set( ZZ_MAKER_MISC_SOURCES
	src/misc/enums/type.cpp
)
