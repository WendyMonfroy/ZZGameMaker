#include "sfElement.hpp"

/**  SFElement constructor
 *
 * @param path  sprite location
 * @param posX  x position of the element
 * @param posY  y position of the element
 */
SFElement::SFElement(std::string path, int posX, int posY) {
    if(! _texture.loadFromFile(path)){
        std::cerr << "Error loading texture" << std::endl;
    }
    _sprite.setTexture(_texture);
    _sprite.setTextureRect(sf::IntRect(0, 0, 50, 50));
    _sprite.setPosition(sf::Vector2f(posX, posY));
}

void SFElement::drawElement(sf::RenderWindow &window) {
    window.draw(_sprite);
}

/** collidesWithGround
 *      check if the element collides with the top of a bloc
 *
 * @param sfBlocs   list of blocs
 * @return          boolean true if collision
 */
bool SFElement::collidesWithGround(std::list<SFElement*> sfBlocs) {
    sf::Sprite _temp = this->_sprite;
    sf::Sprite _bloc;
    sf::FloatRect _playerBound;
    sf::FloatRect _blocBound;

    _temp.setScale(0.8, 0.1);
    _temp.setPosition(_temp.getPosition().x, _temp.getPosition().y + 45);
    _playerBound = _temp.getGlobalBounds();

    for (std::list<SFElement*>::const_iterator it = sfBlocs.begin(); it != sfBlocs.end(); ++it) {
        _bloc = (*it)->_sprite;
        _bloc.setScale(0.7, 0.3);
        _bloc.setPosition(_bloc.getPosition().x + 10, _bloc.getPosition().y);
        _blocBound = _bloc.getGlobalBounds();
        if (_playerBound.intersects(_blocBound)) {
            // reset the position of the element to avoid any bug
            this->_sprite.setPosition(_temp.getPosition().x, _bloc.getPosition().y - 49);
            return true;
        }
    }
    return false;
}

/** collidesWithCeiling
 *      check if the element collides with the bottom of a bloc
 *
 * @param sfBlocs   list of blocs
 * @return          boolean true if collision
 */
bool SFElement::collidesWithCeiling(std::list<SFElement*> sfBlocs) {
    sf::Sprite _temp = this->_sprite;
    sf::Sprite _bloc;
    sf::FloatRect _playerBound;
    sf::FloatRect _blocBound;

    _temp.setScale(0.8, 0.3);
    _temp.move(5, 0);
    _playerBound = _temp.getGlobalBounds();

    for (std::list<SFElement*>::const_iterator it = sfBlocs.begin(); it != sfBlocs.end(); ++it) {
        _bloc = (*it)->_sprite;
        _bloc.setScale(0.8, 0.3);
        _bloc.setPosition(_bloc.getPosition().x + 5, _bloc.getPosition().y + 35);
        _blocBound = _bloc.getGlobalBounds();
        if (_playerBound.intersects(_blocBound)) {
            return true;
        }
    }
    return false;
}

/** collidesWithWall
 *      check if the element collides with a bloc from the sides
 *
 * @param sfBlocs   list of blocs
 * @return          0 if no collision, 1 if collision from the right side of the element, 2 if collision from the left side
 */
int SFElement::collidesWithWall(std::list<SFElement*> sfBlocs) {
    int ans = 0;
    sf::Sprite _temp = this->_sprite;
    sf::Sprite _bound;
    sf::FloatRect _plLeft;
    sf::FloatRect _plRight;
    sf::FloatRect _blLR;

    _bound = _temp;
    _bound.setScale(0.1, 0.9);
    _plLeft= _bound.getGlobalBounds();

    _bound = _temp;
    _bound.setScale(0.1, 0.9);
    _bound.setPosition(_temp.getPosition().x + 45, _temp.getPosition().y);
    _plRight = _bound.getGlobalBounds();

    for (std::list<SFElement*>::const_iterator it = sfBlocs.begin(); it != sfBlocs.end(); ++it) {
        _temp = (*it)->_sprite;
        _bound = _temp;
        _bound.setScale(1.0, 0.8);
        _bound.setPosition(_temp.getPosition().x, _temp.getPosition().y + 5);
        _blLR = _bound.getGlobalBounds();

        if (_plLeft.intersects(_blLR)) {
            ans = 2;
        }
        else if (_plRight.intersects(_blLR)) {
            ans = 1;
        }
    }
    return ans;
}
