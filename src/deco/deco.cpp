//
// Created by darklinkz42 on 24/02/2020.
//

#include "deco.hpp"

Deco::Deco( std::string const& path ) : MapElement( path, Type::DECO, false, 0 ) {}

Deco::Deco( Deco* deco ) : MapElement( deco ) {}