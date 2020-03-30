//
// Created by darklinkz42 on 19/01/2020.
//

#include "gameElement.hpp"
#include "../../../enums/colors.hpp"
#include <iostream>
#include <QtWidgets/QHBoxLayout>
#include <QPainter>

/**
 * Create a GameELement with an instance of a sprite and a mapElement
 * the sprite is the image to show
 * size is define corresponding to the display parameter (no size if no display)
 *
 * @param path --> path of the assets to use to load image
 * @param display --> boolean used to decide if the game element is displayed or not
 * @param parent --> pointer of the widget which contain the element
 */
GameElement::GameElement(QString path, bool display, MapElement * element, QWidget *parent) : QFrame(parent), path(path){
    sprite = new Sprite(path, display, this);
    mapElement = element;
    setDisplay(display);
}

/**
 * react when a button of the mouse is pressed on the widget
 *
 * @param e --> mouse event
 */
void GameElement::mousePressEvent(QMouseEvent *e) {
    Q_UNUSED(e);

    mousePressed();
}

/**
 * signal that the mousse has been pressed
 */
void GameElement::mousePressed() {
    emit onSpriteClicked(mapElement, path);
}

/**
 * Set the size corresponding to the display
 * if the GameElement is displayed fixed a static size
 * if not, set size to zero to not deactivate a zone for mouse event on the screen
 * @param display
 */
void GameElement::setDisplay(bool display) {
    if (display) {
        setFixedWidth(sprite->width());
        setFixedHeight(sprite->height());
    } else {
        setFixedWidth(0);
        setFixedHeight(0);
    }
    sprite->setDisplay(display);
}