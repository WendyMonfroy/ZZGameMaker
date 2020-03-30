#ifndef __CHARACTER_HPP__
#define __CHARACTER_HPP__

#include "map_element.hpp"
#include <string>

/* -------------------------------------------------------------------------- *\

class Character

\* -------------------------------------------------------------------------- */
class Character : public MapElement {
public:
  std::string  _name;
  unsigned int _maxHealth;
  unsigned int _health;
  unsigned int _defence;
  unsigned int _strengh;

public:
  Character( std::string const& path, Type const& type, bool const move, long const speed, std::string const& name,
             unsigned int const maxHealth, unsigned int const health, unsigned int const defence,
             unsigned int const strength );
  Character( Character* character );

}; // End of class Character

#endif
