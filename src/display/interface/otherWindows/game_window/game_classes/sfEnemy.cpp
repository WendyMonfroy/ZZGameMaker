#include "sfEnemy.hpp"
#include "sfPlayer.hpp"

SFEnemy::SFEnemy(std::string path, int posX, int posY, std::string name, int health, float speed) :
        SFElement(path, posX, posY), _name(name), _health(health), _speed(speed)
{

}

/** controller
 *      move the enemy elements on the blocs
 *
 * @param sfBlocs   list of blocs
 */
void SFEnemy::controller(std::list<SFElement*> & sfBlocs){
    if (this->collidesWithGround(sfBlocs)) {
        if (this->collidesWithWall(sfBlocs) != 0) {
            this->_speed = -this->_speed;
        }
        this->_sprite.move(this->_speed, 0.0);
    } else {
        this->_sprite.move(this->_speed/5, 0.5);
    }
}

/** hitPlayer
 *      check if the enemy collides with a player from its sides and damage him if so
 *
 * @param sfPlayers     list of enemies
 */
void SFEnemy::hitPlayer(std::list<SFPlayer*> & sfPlayers) {
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

    for (std::list<SFPlayer*>::const_iterator it = sfPlayers.begin(); it != sfPlayers.end(); ++it) {
        _temp = (*it)->_sprite;
        _bound = _temp;
        _bound.setScale(1.0, 0.8);
        _bound.setPosition(_temp.getPosition().x, _temp.getPosition().y + 5);
        _blLR = _bound.getGlobalBounds();

        if (_plLeft.intersects(_blLR) || _plRight.intersects(_blLR)) {
            (*it)->_health -= 1;
        }
    }
}