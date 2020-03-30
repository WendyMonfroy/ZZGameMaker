#ifndef ZZMAKER_MAINGAMEWINDOW_HPP
#define ZZMAKER_MAINGAMEWINDOW_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <list>
#include <map>

#include <interface/otherWindows/game_window/game_classes/sfElement.hpp>
#include <interface/otherWindows/game_window/game_classes/sfPlayer.hpp>
#include <interface/otherWindows/game_window/game_classes/sfEnemy.hpp>

#include "map_element.hpp"
#include "player.hpp"
#include "ennemy.hpp"
#include "bloc.hpp"

/*
 * Class MainGameWindow
 */
class MainGameWindow {
private:
    bool _center = true; // centrer sur le personnage principal
    sf::Text text;
    sf::Font font;

public:
    void run(std::map<int, MapElement *> &&elements);   // run function called by de game editor

private:
    // to be called by run()
    void initialize(std::map<int, MapElement *> &elements, std::list<SFElement*> & sfBlocs, std::list<SFPlayer*> & sfPlayers, std::list<SFEnemy*> & sfEnemies, std::list<SFElement*> & sfItems, std::list<SFElement*> & sfBackground);  // create SFML game elements from the map given by the editor
    void initPlayerSprite(std::list<SFPlayer*> & sfPlayers);    // initialisation of the player sprites to grey (unfocused)
    void updateEnemies(std::list<SFEnemy*> & sfEnemies, std::list<SFPlayer*> & sfPlayers, std::list<SFElement*> & sfBlocs);
    void displayScore(sf::RenderWindow & window, const SFPlayer * player);
    inline sf::Sprite shiftSprite( sf::Sprite spr, const sf::Vector2f& df );
    void render(sf::RenderWindow * window, std::list<SFElement*> & sfBlocs, std::list<SFPlayer*> & sfPlayers, std::list<SFEnemy*> & sfEnemies, std::list<SFElement*> sfItems, std::list<SFElement*> sfBackground, SFPlayer * currentPlayer);
};

#endif //ZZMAKER_MAINGAMEWINDOW_HPP
