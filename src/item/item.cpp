//
// Created by darklinkz42 on 24/02/2020.
//

#include "item.hpp"

Item::Item( const std::string& path ) : MapElement( path, Type::ITEM, false, 0 ) {}

Item::Item( Item* item ) : MapElement( item ) {}