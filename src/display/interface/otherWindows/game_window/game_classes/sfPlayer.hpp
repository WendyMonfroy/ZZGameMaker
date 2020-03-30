#ifndef ZZMAKER_SFPLAYER_HPP
#define ZZMAKER_SFPLAYER_HPP

#include <SFML/Graphics.hpp>
#include <iostream>

#include "sfElement.hpp"
#include "sfEnemy.hpp"

class SFPlayer : public SFElement {
public:
    SFPlayer() = default;
    SFPlayer(std::string path, int posX, int posY, std::string name, int health, int max_health, int strength, float speed);

public:
    std::string _name;
    int _maxHealth;
    int _health;
    int _strength;
    float _speed;
    int _score;

public:
    bool collidesWithItem(std::list<SFElement*> & sfItems);
    void hitEnemy(std::list<SFEnemy*> & sfEnemy, float & jump);
};


#endif //ZZMAKER_SFPLAYER_HPP
