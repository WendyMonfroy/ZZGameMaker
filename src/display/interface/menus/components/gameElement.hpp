//
// Created by darklinkz42 on 19/01/2020.
//

#ifndef ZZMAKER_GAMEELEMENT_HPP
#define ZZMAKER_GAMEELEMENT_HPP

#include <QFrame>
#include <QMouseEvent>
#include <map/components/physic/map_element.hpp>
#include "utils/sprite.hpp"

/**
 * Element of the menus which can be clicked to drag it into the grid and create a physic instance of a mapElement for the game
 */
class GameElement : public QFrame {

    Q_OBJECT

private:
    Sprite * sprite; //!< Pointer on a sprite --> contain the QImage to display
    MapElement * mapElement;//!< Pointer on a MapElement -> represent the physic element of the game to create from this GameElement

public:
    QString path; //!<Path to the image used in the sprite

public:
    GameElement(QString path, bool display, MapElement * element, QWidget * parent = nullptr);
    void setDisplay(bool display);

private:
    void mousePressEvent(QMouseEvent * e) override;

    signals:
    /**
     * signal which provide mapElement and path
     *
     * @param mapElement --> Pointer on the physic game element to create
     * @param path --> path to the image of the sprite
     */
    void onSpriteClicked(MapElement * mapElement, QString path);

private slots:
    void mousePressed();
};

#endif //ZZMAKER_GAMEELEMENT_HPP
