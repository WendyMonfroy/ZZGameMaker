#ifndef __PLAYER_HPP__
#define __PLAYER_HPP__

#include <iostream>
#include <item.hpp>
#include <string>
#include <vector>

#include "character.hpp"

/* -------------------------------------------------------------------------- *\

class Player

\* -------------------------------------------------------------------------- */

class Player : public Character {
protected:
  // std::vector<Item> inventory; //!< Items in the inventory of the Player
  // std::vector<Item> stuff; // Stuff items of the Player

public:
  //! Constructors
  Player() = default;
  Player( std::string const& path, std::string n );
  Player( std::string const& path, std::string n, int h, int d, int s );
  Player( Player* player );
  ~Player() = default;

  // void equip(Item i);

}; // End of class Player

#endif
