#include "bloc.hpp"

Bloc::Bloc( std::string const& path ) : MapElement( path, Type::BLOC, false, 0.0 ) {}

Bloc::Bloc( Bloc* bloc ) : MapElement( bloc ) {}
