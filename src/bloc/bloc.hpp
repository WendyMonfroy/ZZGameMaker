#ifndef __BLOC_HPP__
#define __BLOC_HPP__

#include "map_element.hpp"
#include <iostream>
#include <string>

/* -------------------------------------------------------------------------- *\

class Bloc

\* -------------------------------------------------------------------------- */

class Bloc : public MapElement {
public:
  //! Constructors
  Bloc( std::string const& path );
  Bloc( Bloc* bloc );
  ~Bloc();

}; // End of class Bloc

#endif
