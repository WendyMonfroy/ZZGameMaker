//
// Created by darklinkz42 on 04/02/2020.
//

#ifndef ZZMAKER_CASE_HPP
#define ZZMAKER_CASE_HPP

#include <QWidget>
#include <QHoverEvent>
#include <utils/sprite.hpp>
#include <deco.hpp>
#include <bloc.hpp>
#include <player.hpp>
#include <ennemy.hpp>
#include <item.hpp>
#include "map/components/physic/map_element.hpp"

class Case : public QWidget {

    Q_OBJECT

private:
    bool hover; //!< Boolean which indicate if mouse is on the Case or not
    Sprite * sprite; //!< Pointer on a Sprite --> represent the sprite that can be drag and drop, only one at a time. It will be modified during the process to always use the right Sprite
    MapElement * mapElement; //!< Pointer on a MapElement --> represent the mapElement that can be add or remove to the list, only one at a time. It will be modified during the process to always use the right MapElement
    bool drop; //!< Boolean which indicate if an element has been dropped or not
    bool drawGrid;
    int x; //!< Abscisse of the Case on the grid
    int y; //!< Ordonnee of the Case on the grid

public:
    Case(int const &x, int const &y, QWidget * parent = nullptr);
    void paintEvent(QPaintEvent * e) override;
    /**
     * if there is already a MapElement on the Case erase it from the physic list
     * update the pointer on MapElement with the new MapELement
     *
     * @param mapElement --> pointer on the MapElement to create for the Case
     */
    inline void setMapElement(MapElement * mapElement) {
        if (this->mapElement != nullptr)
            emit onErase(this->mapElement->getID(), QPoint(x, y));
        changeMapElement(mapElement);
    }

    inline void changeMapElement(MapElement * mapElement) {
        switch (mapElement->type()) {
                   case Type::BLOC:
                       this->mapElement = new Bloc((Bloc *) mapElement);
                       break;
                   case Type::PLAYER:
                       this->mapElement = new Player((Player *) mapElement);
                       break;
                   case Type::ENNEMY:
                       this->mapElement = new Ennemy((Ennemy *) mapElement);
                       break;
                   case Type::ITEM:
                       this->mapElement = new Item((Item *) mapElement);
                       break;
                   case Type::DECO:
                       this->mapElement = new Deco((Deco *) mapElement);
                       break;
                   case Type ::NONE:
                       this->mapElement = new MapElement(mapElement);
                       break;
               };
    }
   /**
     * Gets the pointer on MapElement with the new MapELement
     */
    inline MapElement * getMapElement() const { return mapElement; }
    /**
     * udpate the pointer on the Sprite, change the path, set it visible and declare that an element has been dropped
     *
     * @param path --> path of the image to load in the sprite
     */
    inline void setSprite(QString path) { this->sprite->setPath(path); this->sprite->setDisplay(true); drop = true; }
    inline Sprite * getSprite() const { return sprite; } //!< @return the pointer on the Sprite
    inline unsigned int getX() const { return x; } //!< @return abscisse of the Case on the grid
    inline void setX(int x) { this->x = x; }
    inline unsigned int getY() const { return y; } //!< @return ordonnee of the Case on the grid
    inline void setY(int y) { this->y = y; }
    inline void setDrawGrid(bool drawGrid) { this->drawGrid = drawGrid; repaint(); }
    void clearCase();
    void clean();
    void caseClicked(Qt::MouseButton button);

private:
    void enterEvent(QEvent *) override;
    void leaveEvent(QEvent *) override;
    void rightMouseButtonPressed();
    void leftMouseButtonPressed();

signals:
    /**
     * signal that indicate the ID of the element to erase from the physic list
     *
     * @param id --> ID of the element to erase
     */
    void onErase(unsigned int const id, QPoint point);
    /**
     * signal that the case has been clicked and that an element can be dropped
     *
     * @param _case --> pointer on the Case that has been clicked
     */
    void onDrop(Case * _case);
    /**
     * ask to create a new element to drag and drop one time with this MapElement and this Sprite
     *
     * @param mapElement --> pointer on the MapElement to move
     * @param path --> path of the image of the sprite to move
     */

    void onMove(MapElement * mapElement, QString path, QPoint point);
    void coordonates(int &x, int &y);

public slots:
    void doPaint(QPainter &paint);
};

QDataStream & operator<<(QDataStream & out, const Case * _case);

QDataStream & operator>>(QDataStream & in, Case * &_case);

#endif //ZZMAKER_CASE_HPP
