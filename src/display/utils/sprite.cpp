//
// Created by darklinkz42 on 03/02/2020.
//

#include "sprite.hpp"
#include <QPainter>
#include "enums/colors.hpp"

/**
 * Create a Sprite and fix its size
 *
 * @param parent --> pointer of the widget which contain the element
 */
Sprite::Sprite(QWidget * parent) : QFrame(parent), path(""), display(false) {
    setFixedHeight(0);
    setFixedWidth(0);
}

/**
 * Create a Sprite, load the associated image and set its size
 *
 * @param path --> path of the image to load in the sprite
 * @param display --> boolean which indicate if the sprite is visible or not
 * @param parent --> pointer of the widget which contain the element
 */
Sprite::Sprite(QString path, bool display, QWidget * parent) : QFrame(parent), path(path), display(display) {
    if (path.size() != 0) {
        image.load(path);
        setFixedSize(image.size());
    }
}

/**
 * Create a Sprite with required dimensions
 *
 * @param width --> width of the sprite
 * @param height --> height of the sprite
 * @param parent --> pointer of the widget which contain the element
 *//*
Sprite::Sprite(unsigned int width, unsigned int height, QWidget * parent) : QFrame(parent), path(""), display(false)  {
    setFixedHeight(height);
    setFixedWidth(width);
}*/

/**
 * Paint the Sprite if it is visible
 *
 * @param e --> pointer on a QPaintEvent
 */
void Sprite::paintEvent(QPaintEvent *e) {
    if (display) {
        QPainter qp(this);
        print(qp);
        QFrame::paintEvent(e);
    }
}

/**
 * print the image (currently a red box)
 *
 * @param qp --> pointer on a QPainter use to paint the Sprite
 */
void Sprite::print(QPainter &qp) {
    qp.drawImage(0, 0, image);
}

