#ifndef __ENNEMY_HPP__
#define __ENNEMY_HPP__

#include <iostream>
#include <string>
#include <vector>

#include "character.hpp"

/* -------------------------------------------------------------------------- *\

class Ennemy

\* -------------------------------------------------------------------------- */

class Ennemy : public Character {
protected:
  // enum pour le type de mouvement possible ?
public:
  //! Constructors
  Ennemy() = default;
  Ennemy( std::string const& path, std::string n );
  Ennemy( Ennemy* ennemy );
  ~Ennemy() = default;

  void ennemyControler( void );

}; // End of class Ennemy

#endif