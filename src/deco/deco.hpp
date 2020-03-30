//
// Created by darklinkz42 on 24/02/2020.
//

#ifndef ZZMAKER_DECO_HPP
#define ZZMAKER_DECO_HPP

#include "map_element.hpp"
#include <iostream>

class Deco : public MapElement {

public:
  Deco( std::string const& path );
  Deco( Deco* deco );
};

#endif // ZZMAKER_DECO_HPP
