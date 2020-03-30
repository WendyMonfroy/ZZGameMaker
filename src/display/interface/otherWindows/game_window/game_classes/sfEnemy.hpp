#ifndef ZZMAKER_SFENEMY_HPP
#define ZZMAKER_SFENEMY_HPP

#include "sfElement.hpp"

class SFPlayer;

class SFEnemy : public SFElement {
public:
    SFEnemy() = default;
    SFEnemy(std::string path, int posX, int posY, std::string name, int health, float speed);

public:
    std::string _name;
    int _health;
    float _speed;

public:
    void hitPlayer(std::list<SFPlayer*> & sfPlayers);
    void controller(std::list<SFElement*> & sfBlocs);
};

#endif //ZZMAKER_SFENEMY_HPP
