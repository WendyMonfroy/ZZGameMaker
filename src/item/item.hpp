//
// Created by darklinkz42 on 24/02/2020.
//

#ifndef ZZMAKER_ITEM_HPP
#define ZZMAKER_ITEM_HPP

#include "map_element.hpp"
#include <iostream>

class Item : public MapElement {

public:
  Item( std::string const& path );
  Item( Item* item );
};

#endif // ZZMAKER_ITEM_HPP
