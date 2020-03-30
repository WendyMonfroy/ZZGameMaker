//
// Created by wemonfroy on 23/02/2020.
//

#ifndef ZZMAKER_SFELEMENT_HPP
#define ZZMAKER_SFELEMENT_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include <list>


class SFElement {
public:
    sf::Texture _texture;
    sf::Sprite _sprite;

public:
    SFElement() = default;
    SFElement(std::string path, int posX, int posY);
    void drawElement(sf::RenderWindow &window);
    bool collidesWithGround(std::list<SFElement*> sfBlocs);
    bool collidesWithCeiling(std::list<SFElement*> sfBlocs);
    int collidesWithWall(std::list<SFElement*> sfBlocs);
};


#endif //ZZMAKER_SFELEMENT_HPP
