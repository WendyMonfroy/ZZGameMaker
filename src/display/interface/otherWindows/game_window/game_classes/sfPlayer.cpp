#include "sfPlayer.hpp"

SFPlayer::SFPlayer(std::string path, int posX, int posY, std::string name, int max_health, int health, int strength, float speed) :
SFElement(path, posX, posY), _name(name), _maxHealth(max_health), _health(health), _strength(strength), _speed(speed), _score(0)
{

}

/** collidesWithItem
 *      check if the player collides with an item
 *      if so, the item is destroyed and the player's score is increased
 *
 * @param sfItems   list of items
 * @return
 */
bool SFPlayer::collidesWithItem(std::list<SFElement*> & sfItems) {
    sf::Sprite _temp = this->_sprite;
    _temp.setScale(0.8, 1.0);
    _temp.setPosition(_temp.getPosition().x + 5, _temp.getPosition().y);
    sf::FloatRect _playerBound = _temp.getGlobalBounds();
    sf::FloatRect _itemBound;

    for (std::list<SFElement*>::const_iterator it = sfItems.begin(); it != sfItems.end(); ++it) {
        _temp = (*it)->_sprite;
        _temp.setScale(0.6, 0.6);
        _temp.setPosition(_temp.getPosition().x + 10, _temp.getPosition().y + 10);
        _itemBound = _temp.getGlobalBounds();
        if (_playerBound.intersects(_itemBound)) {
            // destroy item
            this->_score += 1;
            sfItems.erase(it);
            return true;
        }
    }
    return false;
}

/** hitEnemy
 *      check if the focused player hit an enemy on his head and damage it if so
 *
 * @param sfEnemy   list of enemies
 * @param jump      player's velocity on the y axis (jumps after a hit)
 */
void SFPlayer::hitEnemy(std::list<SFEnemy*> & sfEnemy, float & jump) {
    sf::Sprite _temp = this->_sprite;
    sf::Sprite _enemy;
    sf::FloatRect _playerBound;
    sf::FloatRect _enemyBound;

    _temp.setScale(1.0, 0.1);
    _temp.setPosition(this->_sprite.getPosition().x, this->_sprite.getPosition().y + 45);
    _playerBound = _temp.getGlobalBounds();

    for (std::list<SFEnemy*>::const_iterator it = sfEnemy.begin(); it != sfEnemy.end(); ++it) {
        _enemy = (*it)->_sprite;
        _enemy.setScale(0.9, 0.3);
        _enemy.setPosition(_enemy.getPosition().x + 3, _enemy.getPosition().y);
        _enemyBound = _enemy.getGlobalBounds();
        if (_playerBound.intersects(_enemyBound)) {
            jump = -8;
            (*it)->_health -= 1;
            if ((*it)->_health < 1) {
                this->_score += 5;
                sfEnemy.erase(it);
                return;
            }
        }
    }
}

