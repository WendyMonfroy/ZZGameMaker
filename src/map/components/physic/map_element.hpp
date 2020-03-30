#ifndef __MAP_ELEMENT_HPP__
#define __MAP_ELEMENT_HPP__

#include <QWidget>
#include <utils/sprite.hpp>
#include <utils/dimensions.hpp>
#include "enums/type.hpp"
#include "enums/direction.hpp"
#include "utils/hitbox.hpp"

/* -------------------------------------------------------------------------- *\

class MapElement

\* -------------------------------------------------------------------------- */
class MapElement {
protected:
   Type _type; //!< Block type of the element

protected:
   Hitbox _hitbox; //!< Position of the hitbox
   Dimensions _dim; //< Dimensions of the element

protected:
   bool _movable; //!< If the element is movable
   long _speed;   //!< Base move speed of the element

   unsigned int id; //!< ID of the element
   std::string spritePath; //!< path to the image representing the element

private:

public:
    MapElement();
    MapElement(std::string const &path, Type t, bool m, long s, long hitWidth = 50, long hitHeigth = 50, long width = 50, long heigth = 50);
    MapElement(MapElement * mapElement);
   ~MapElement() = default;

public:
   //! Gets the type of the element
   inline Type type() const { return _type; }
   inline void setType(Type &&type) { this->_type = type; }

public:
    inline bool move() const { return _movable; }
    inline void setMove(bool move) { _movable = move; }
    inline long speed() const { return _speed; }
    inline void setSpeed(qlonglong speed) { _speed = speed; }

public:
   //! Gets the current position of the element
   inline Hitbox hitboxPosition() const { return _hitbox; }
   inline void setHitboxPosition(qlonglong x, qlonglong y) { _hitbox.x = x, _hitbox.y = y; }
    inline void setHitboxDimensions(qlonglong w, qlonglong h) { _hitbox.w = w, _hitbox.h = h; }
    inline Dimensions dimensions() const { return _dim; }
   inline void setPosition(qlonglong x, qlonglong y) { _dim.x = x, _dim.y = y; }
   inline void setDimensions(qlonglong width, qlonglong heigth) { _dim.width = width; _dim.heigth = heigth; }

public:
   //! Moves the bloc in a direction
   /**
    * \param dir Wanted moving direction
    * \return Traveled distance
    */
   long move( Direction dir );

public:
    //! Gets the ID of the element
    inline int const getID() const { return id; }
    //! Sets the ID of the element
    inline void setID(unsigned int const id) { this->id = id; }
    //! Gets the path to the image of the element
    inline std::string const getSpritePath() const { return spritePath; }
    //! Sets the path to the image of the element
    inline void setSpritePath(std::string const &spritePath) { this->spritePath = spritePath; }

    std::string toString();

}; // End of class MapElement

QDataStream & operator<<(QDataStream & out, const MapElement * element);

QDataStream & operator>>(QDataStream & in, MapElement * &element);

#endif
