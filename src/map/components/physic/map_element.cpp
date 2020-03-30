#include <bloc.hpp>
#include <player.hpp>
#include <ennemy.hpp>
#include <item.hpp>
#include <deco.hpp>
#include "map_element.hpp"

MapElement::MapElement()  :
_type(Type::NONE), _hitbox(-1,-1), _dim(0, 0), _movable(false), _speed(0), id(0), spritePath("")
{}

MapElement::MapElement(std::string const &path, Type t, bool m, long s, long hitWidth, long hitHeigth, long width, long heigth) :
_type(t), _hitbox(hitWidth, hitHeigth), _dim(width, heigth), _movable(m), _speed(s), spritePath(path)
{
}

/**
 * create a copy of the MapElement passed in parameters
 *
 * @param mapElement --> pointer of the MapElement to copy in this object
 */
MapElement::MapElement(MapElement *mapElement)
: _type(mapElement->type()),
  _hitbox(mapElement->hitboxPosition()),
  _dim(mapElement->dimensions()),
  _movable(mapElement->move()),
  _speed(mapElement->speed()),
  id(mapElement->getID()),
  spritePath(mapElement->getSpritePath())
{

}

long MapElement::move( Direction dir ) {
   long distanceMoved = _speed;
   switch ( dir ) {
      case Direction::STATIC:
         distanceMoved = 0l;
         break;
      case Direction::LEFT:
          _hitbox.x -= _speed;
         break;
      case Direction::RIGHT:
          _hitbox.x += _speed;
         break;
      case Direction::UP:
          _hitbox.y -= _speed;
         break;
      case Direction::DOWN:
          _hitbox.y += _speed;
         break;
   }

   return distanceMoved;
}

QDataStream & operator<<(QDataStream & out, const MapElement * element) {
    qlonglong hitX, hitY, hitW, hitH, x, y, width, heigth, speed;
    hitX = element->hitboxPosition().x;
    hitY = element->hitboxPosition().y;
    hitW = element->hitboxPosition().w;
    hitH = element->hitboxPosition().h;
    x = element->dimensions().x;
    y = element->dimensions().y;
    width = element->dimensions().width;
    heigth = element->dimensions().heigth;
    qint32 id = element->getID();
    QString path = element->getSpritePath().c_str();
    speed = element->speed();
    out << element->type() << hitX << hitY << x << y << hitW << hitH << width << heigth << element->move() << speed << id << path;
    switch (element->type()) {
        case Type::BLOC:
            break;
        case Type::PLAYER:
            out << QString(((Player *) element)->_name.c_str())
            << ((Player *) element)->_maxHealth
            << ((Player *) element)->_health
            << ((Player *) element)->_defence
            << ((Player *) element)->_strengh;
            break;
        case Type::ENNEMY:
            out << QString(((Ennemy *) element)->_name.c_str())
            << ((Ennemy *) element)->_maxHealth
            << ((Ennemy *) element)->_health
            << ((Ennemy *) element)->_defence
            << ((Ennemy *) element)->_strengh;
            break;
        case Type::ITEM:
            break;
        case Type::DECO:
            break;
        default:
            break;
    }
    return out;
}

QDataStream & operator>>(QDataStream & in, MapElement * &element) {
    QString typeName;
    qlonglong hitX, hitY, hitW, hitH, x, y, width, heigth, speed;
    bool move;
    qint32 id, maxHealth, health, defence, strengh;
    QString path, name;
    in >> typeName;
    in >> hitX >> hitY >> hitW >> hitH >> x >> y >> width >> heigth >> move >> speed >> id >> path;
    switch (getType(typeName)) {
        case Type::BLOC:
            element = new Bloc(path.toUtf8().constData());
            break;
        case Type::PLAYER:
            in >> name
                    >> maxHealth
                    >> health
                    >> defence
                    >> strengh;
                    element = new Player(path.toUtf8().constData(), name.toUtf8().constData(), maxHealth, defence, strengh);
            break;
        case Type::ENNEMY:
            in >> name
                    >> maxHealth
                    >> health
                    >> defence
                    >> strengh;
                    element = new Ennemy(path.toUtf8().constData(), name.toUtf8().constData());
            break;
        case Type::ITEM:
            element = new Item(path.toUtf8().constData());
            break;
        case Type::DECO:
            element = new Deco(path.toUtf8().constData());
            break;
        default:
            element = new MapElement();
            break;
    }
    element->setType(getType(typeName));
    element->setHitboxPosition(hitX, hitY);
    element->setHitboxDimensions(hitW, hitH);
    element->setPosition(x, y);
    element->setDimensions(width, heigth);
    element->setMove(move);
    element->setSpeed(speed);
    element->setID(id);
    return in;
}
