#include "player.hpp"

Player::Player( std::string const& path, std::string n )
    : Character( path, Type::PLAYER, true, 0.2, n, 20, 20, 0, 1 ) {}

Player::Player( std::string const& path, std::string n, int h, int d, int s )
    : Character( path, Type::PLAYER, true, 0.2, n, h, h, d, s ) {}

Player::Player( Player* player ) : Character( player ) {}

/*
void Player:: equip(Item i) {
        // on souhaite retirer l'item de l'inventaire pour le placer dans l'�quipement
        stuff.push_back(i);
}
*/