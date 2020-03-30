#include "ennemy.hpp"
#include <SFML/Graphics.hpp>

Ennemy::Ennemy( std::string const& path, std::string n )
    : Character( path, Type::ENNEMY, true, 0.1, n, 10, 10, 0, 1 ) {}

Ennemy::Ennemy( Ennemy* ennemy ) : Character( ennemy ) {}

void Ennemy::ennemyControler( void ) {}