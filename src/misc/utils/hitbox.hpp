#ifndef __HITBOX_HPP__
#define __HITBOX_HPP__

/* -------------------------------------------------------------------------- *\

struct Hitbox

\* -------------------------------------------------------------------------- */
class Hitbox {
public:
  long x, y; //!< Coordinates of the hitbox
  long w, h; //!< Dimentions of the hitbox

public:
  // Constructors
  Hitbox( long w, long h ) : w( w ), h( h ) {}

public:
  //! Tests if this collides with another hitbox
  /**
   * \param o Other hitbox
   * \return true if the boxes collide
   */
  bool collides( const Hitbox& o ) const {
    return !( x + w <= o.x || y + h <= o.y || o.x + o.w <= x || o.y + o.h <= y );
  }
}; // End of class Hitbox

// --  Operators  ----------------------------------------------------------- */

//! Compares two hitboxes on x, then on y
/**
 * \param hb1 First hitbox
 * \param hb2 Second hitbox
 * \return true if hb1.x < hb2.x, if they are equal, the test is made on the y parameter
 */
inline bool operator<( const Hitbox& hb1, const Hitbox& hb2 ) {
  return ( hb1.x == hb2.x ) ? ( hb1.y < hb2.y ) : ( hb1.x < hb2.x );
}

#endif
