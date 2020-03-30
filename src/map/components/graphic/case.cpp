//
// Created by darklinkz42 on 10/02/2020.
//

#include <QPainter>
#include "case.hpp"
#include "map/map.hpp"
#include <QMouseEvent>
#include <QPointF>
#include <enums/colors.hpp>

/**
 * create a Case and pointers on Sprite and MapElement
 * they correspond respectively to the image to display on the case and the mapElement to add or remove from the physic element list
 *
 * @param x --> abscisse of the Case on the grid
 * @param y --> ordonnee of the Case on the grid
 * @param parent --> pointer of the widget which contain the element
 */
Case::Case(int const &x, int const &y, QWidget *parent) : QWidget(parent), x(x), y(y) {

    setBackGround(Colors::GREY, this);

    hover = false;
    sprite = new Sprite(this);
    drop = false;
    drawGrid = false;
    mapElement = nullptr;
    setFixedSize(50,50);

}

void Case::clearCase() {
    if (mapElement != nullptr) {
        sprite->setDisplay(false);
        emit onErase(mapElement->getID(), QPoint(x, y));
        mapElement = nullptr;
    }
}

void Case::clean() {
    sprite->setDisplay(false);
    mapElement = nullptr;
}

/**
 * if there is no sprite to display, paint the Case
 *
 * @param e --> pointer on a QPaintEvent
 */
void Case::paintEvent(QPaintEvent *e) {
    if (!sprite->getDisplay()) {
        QPainter paint(this);
        doPaint(paint);
        QWidget::paintEvent(e);
    }
}

/**
 * repaint the Case when mouse enter the case
 *
 * @param e --> pointer on a unused QEvent
 */
void Case::enterEvent(QEvent * e) {
    Q_UNUSED(e)
    hover = true;
    repaint();
    emit coordonates(x, y);
}

/**
 * repaint the Case when mouse leave the case
 *
 * @param e --> pointer on a unused QEvent
 */
void Case::leaveEvent(QEvent * e) {
    Q_UNUSED(e)
    hover = false;
    repaint();
}

/**
 * react to a mouse button press and attribute the right instructions following the button
 *
 * @param e --> pointer on a QMouseEvent which indicate which mouse button has been clicked
 */
void Case::caseClicked(Qt::MouseButton button) {
   switch (button) {
       case Qt::LeftButton:
           leftMouseButtonPressed();
           break;
       case Qt::RightButton:
           rightMouseButtonPressed();
           break;
       default:
           break;
   }

}

/**
 * react to rigth mouse button pressed
 * if there is an element on the map, erase it from the physic list and undisplay the sprite
 */
void Case::rightMouseButtonPressed() {
    clearCase();
}

/**
 * react to left mouse button pressed
 * ask to drop the dragged element or remove mapElements and undisplay sprite to move it on another Case
 */
void Case::leftMouseButtonPressed() {
    emit onDrop(this);
    if (!drop && sprite->getDisplay()) {
        sprite->setDisplay(false);
        emit onMove(mapElement, sprite->getPath(), QPoint(x, y));
        mapElement = nullptr;
    }
    drop = false;
}

/**
 * set the color of the Case following if the mouse if on the Case or not
 *
 * @param paint --> pointer on a QPainter use to paint the Case
 */
void Case::doPaint(QPainter &paint) {
        if (hover) {
            paint.setBrush(get(Colors::LIGHT_GREY));
            paint.drawRect(this->rect());
        }
        if (drawGrid) {
            QPen pen(get(Colors::WHITE), 1, Qt::SolidLine);
            paint.setPen(pen);
            unsigned int w = width();
            unsigned int h = height();
            paint.drawLine(0, 0, 0, h);
            paint.drawLine(0, 0, w, 0);
            if (x == 19)
                paint.drawLine(0, h-1, h-1, h-1);
            if (y == 24)
                paint.drawLine(w-1, 0, w-1, w-1);
        }
}

QDataStream & operator<<(QDataStream & out, Case const * _case) {
    Sprite * temp = _case->getSprite();
    out << _case->getX() << _case->getY();
    if (temp->getDisplay()) {
        out << temp->getPath() << _case->getMapElement();
    } else {
        out << QString("none");
    }
    return out;
}

QDataStream & operator>>(QDataStream & in, Case * &_case) {
    qint32 x, y;
    in >> x >> y;
    _case = new Case(x, y);
    QString path;
    in >> path;
    if (QString::compare(path, "none") != 0) {
        _case->setSprite(path);
        MapElement * element = new MapElement();
        in >> element;
        _case->setMapElement(element);
    }
    return in;
}
