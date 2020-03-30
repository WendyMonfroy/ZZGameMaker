#include "mainGameWindow.hpp"

/** initialize
 *      create lists of game elements from the map of elements given by the editor
 *
 * @param elements      map of elements
 * @param sfBlocs       list of blocs
 * @param sfPlayers     list of players
 * @param sfEnemies     list of enemies
 * @param sfItems       list of items
 * @param sfBackground  lis of background elements
 */
void MainGameWindow::initialize(std::map<int, MapElement *> &elements, std::list<SFElement*> & sfBlocs, std::list<SFPlayer*> & sfPlayers, std::list<SFEnemy*> & sfEnemies, std::list<SFElement*> & sfItems, std::list<SFElement*> & sfBackground){
    std::map<int, MapElement *>::const_iterator it = elements.begin() ;

    while (it != elements.end()){
        MapElement elt = it->second;
        switch (it->second->type()){
            case Type::PLAYER:
                sfPlayers.push_back(new SFPlayer(elt.getSpritePath(), elt.hitboxPosition().y, elt.hitboxPosition().x, "Arthemis", 20, 20, 2, 4));
                break;
            case Type::ENNEMY:
                sfEnemies.push_back(new SFEnemy(elt.getSpritePath(), elt.hitboxPosition().y, elt.hitboxPosition().x, "Zug", 3, -1.0));
                break;
            case Type::BLOC:
                sfBlocs.push_back(new SFElement(elt.getSpritePath(), elt.hitboxPosition().y, elt.hitboxPosition().x));
                break;
            case Type::ITEM:
                sfItems.push_back(new SFElement(elt.getSpritePath(), elt.hitboxPosition().y, elt.hitboxPosition().x));
                break;
            case Type::DECO:
                sfBackground.push_back(new SFElement(elt.getSpritePath(), elt.hitboxPosition().y, elt.hitboxPosition().x));
                break;
            default:
                break;
        }
        ++it;
    }

    if (!font.loadFromFile("../assets/font/slkscr.ttf")) { std::cerr << "error loading font" << std::endl; }
    text.setFont(font);
    text.setString("Player score: 0");
    text.setFillColor(sf::Color(200, 200, 200));
    text.setPosition(50, 20);
}

/** initPlayerSprite
 *      set the players' sprites to grey (unfocused)
 *
 * @param sfPlayers     list of players
 */
void MainGameWindow::initPlayerSprite(std::list<SFPlayer*> & sfPlayers) {
    std::list<SFPlayer*>::const_iterator it = sfPlayers.begin();
    while (it != sfPlayers.end()) {
        (*it)->_sprite.setColor(sf::Color(100, 100, 100));
        ++it;
    }
}

/** updateEnemies
 *      damage players and move every enemy
 *
 * @param sfEnemies     list of enemies
 * @param sfPlayers     list of players
 * @param sfBlocs       list of blocs
 */
void MainGameWindow::updateEnemies(std::list<SFEnemy*> & sfEnemies, std::list<SFPlayer*> & sfPlayers, std::list<SFElement*> & sfBlocs) {
    for (std::list<SFEnemy*>::const_iterator it = sfEnemies.begin(); it != sfEnemies.end(); ++it) {
        (*it)->hitPlayer(sfPlayers);
        (*it)->controller(sfBlocs);
    }
}

/** displayScore
 *      draw a string on the screen to display the focused player's score
 *
 * @param window    display window
 * @param player    focused player
 */
void MainGameWindow::displayScore(sf::RenderWindow & window, const SFPlayer * player) {
    text.setString("Player score: " + std::to_string(player->_score));
    window.draw(text);
}

/** shiftSprite
 *      move the sprite to follow the player
 *
 * @param spr   sprite to move
 * @param df    movement vector
 * @return      sprite moved
 */
sf::Sprite MainGameWindow::shiftSprite( sf::Sprite spr, const sf::Vector2f& df ) {
	if ( _center ) spr.move( df );
	return spr;
}

/** render
 *      clear the screen and draw the elements
 *
 * @param window        pointer to the window
 * @param sfBlocs       list of blocs
 * @param sfPlayers     list of players
 * @param sfEnemies     list of enemies
 * @param sfItems       list of items
 * @param sfBackground  list of background elements
 * @param currentPlayer pointer to the focused player
 */
void MainGameWindow::render(sf::RenderWindow * window, std::list<SFElement*> & sfBlocs, std::list<SFPlayer*> & sfPlayers, std::list<SFEnemy*> & sfEnemies, std::list<SFElement*> sfItems, std::list<SFElement*> sfBackground, SFPlayer * currentPlayer) {
    window->clear(sf::Color(50, 50, 50));
    sf::Vector2f df; // position du perso par rapport a la fenetre

    int leftLimit = window->getSize().x / 4.f;
    int rightLimit = 3 * window->getSize().x / 4.f;
    int upLimit = window->getSize().y / 4.f;
    int bottomLimit = 3 * window->getSize().y / 4.f;

    int playerHPosition = currentPlayer->_sprite.getPosition().x;
    int playerVPosition = currentPlayer->_sprite.getPosition().y;

    if (playerHPosition <= leftLimit) {
        df.x = leftLimit - playerHPosition;
    }
    else if (playerHPosition >= rightLimit) {
        df.x = rightLimit - playerHPosition;
    }
    if (playerVPosition <= upLimit) {
        df.y = upLimit - playerVPosition;
    }
    else if (playerVPosition >= bottomLimit ) {
        df.y = bottomLimit - playerVPosition;
    }

    for ( auto& it : sfPlayers ) {
        window->draw( shiftSprite( it->_sprite, df ) );
    }

    for ( auto& it : sfBackground ) { window->draw( shiftSprite( it->_sprite, df ) ); }
    for ( auto& it : sfBlocs ) { window->draw( shiftSprite( it->_sprite, df ) ); }
    for ( auto& it : sfEnemies ) { window->draw( shiftSprite( it->_sprite, df ) ); }
    for ( auto& it : sfItems ) { window->draw( shiftSprite( it->_sprite, df ) ); }
}

/** run
 *      initialize a window and its parameters
 *      initialize the game elements from the map given by the editor
 *      update the focused player acording to keyboard events
 *      update the enemies
 *      render and draw on the window
 *
 * @param elements      map of elements created by the editor
 */
void MainGameWindow::run(std::map<int, MapElement *> &&elements) {
    float speed;
    float _maxSpeed = 10;
    float _right = 0, _down = 0;
    float _velocityY = 0;
    float _gravity = 0.5;
    bool _isJumping = false;
    bool _isOnGround;

    std::list<SFElement*> _blocList;
    std::list<SFPlayer*> _playerList;
    std::list<SFEnemy*> _enemyList;
    std::list<SFElement*> _itemList;
    std::list<SFElement*> _bgList;

    SFPlayer* currentPlayer;
    std::list<SFPlayer*>::const_iterator p;

    // window initialization
    sf::RenderWindow win(sf::VideoMode(1250,1000), "Game Testing");
    win.setFramerateLimit(60);
    initialize(elements, _blocList, _playerList, _enemyList, _itemList, _bgList);
    initPlayerSprite(_playerList);

    if (_playerList.empty()) {
        std::cerr << "pas de joueur, pas de jeu" << std::endl;
        return;
    }

    p = _playerList.begin();

    while(win.isOpen()){
        if (win.hasFocus()) {
            sf::Event event;
            currentPlayer = *p;
            speed = currentPlayer->_speed;
            _isOnGround = currentPlayer->collidesWithGround(_blocList); // controls if the player is on ground
            currentPlayer->_sprite.setColor(sf::Color(255, 255, 255));

            while (win.pollEvent(event)) {
                switch (event.type) {
                    case sf::Event::Closed:
                        win.close();
                        break;
                    case (sf::Event::KeyPressed):   // change focus for the next player in the list
                        if (event.key.code == sf::Keyboard::Tab) {
                            currentPlayer->_sprite.setColor(sf::Color(100, 100, 100));
                            ++p;
                            if (p == _playerList.end()) p = _playerList.begin();
                        }
                        else if (event.key.code == sf::Keyboard::Space || event.key.code == sf::Keyboard::Up) {
                            if (_isOnGround) {
                                _isJumping = true;
                                _velocityY = -12;    // Jump
                            }
                        }
                        break;
                    case (sf::Event::KeyReleased):
                        if (event.key.code == sf::Keyboard::Right || event.key.code == sf::Keyboard::Left) {
                            _right = 0;
                        } else if (event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::Space) {
                            _isJumping = false;
                        }
                        break;
                    default:
                        break;
                }

            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                _right = -speed;
            } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                _right = speed;
            }

            // collisions checking
            int collides = currentPlayer->collidesWithWall(_blocList);
            if (collides == 2) {
                if (_right == -speed) _right=0;
            }
            else if (collides == 1) {
                if (_right == speed) _right=0;
            }
            if (!_isOnGround && _velocityY < _maxSpeed) {
                _velocityY += _gravity;
            } else if (_isOnGround && !_isJumping){
                _velocityY = 0;
            }
            if (currentPlayer->collidesWithCeiling(_blocList)) {
                _velocityY = - _velocityY;
            }

            currentPlayer->hitEnemy(_enemyList, _velocityY);
            currentPlayer->collidesWithItem(_itemList);

            _down = _velocityY;
            updateEnemies(_enemyList, _playerList, _blocList);
            currentPlayer->_sprite.move(_right, _down);
            render(&win, _blocList, _playerList, _enemyList, _itemList, _bgList, currentPlayer);
            displayScore(win, currentPlayer);
            win.display();
        }
    }
}
