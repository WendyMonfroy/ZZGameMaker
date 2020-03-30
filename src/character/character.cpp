#include "character.hpp"

Character::Character( std::string const& path, Type const& type, bool const move, long const speed,
                      std::string const& name, unsigned int const maxHealth, unsigned int const health,
                      unsigned int const defence, unsigned int const strength )
    : MapElement( path, type, move, speed )
    , _name( name )
    , _maxHealth( maxHealth )
    , _health( health )
    , _defence( defence )
    , _strengh( strength ) {}

Character::Character( Character* character )
    : MapElement( character )
    , _name( character->_name )
    , _maxHealth( character->_maxHealth )
    , _health( character->_health )
    , _defence( character->_defence )
    , _strengh( character->_strengh ) {}