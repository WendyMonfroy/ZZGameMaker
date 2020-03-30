#ifndef __IDENTITY_HPP__
#define __IDENTITY_HPP__

#include <QDataStream>
/* -------------------------------------------------------------------------- *\

enum class Type

\* -------------------------------------------------------------------------- */
enum class Type { BLOC, PLAYER, ENNEMY, ITEM, DECO, NONE }; // End of enum class Type

QString getTypeName( Type& type );
Type    getType( QString& typeName );

QDataStream& operator<<( QDataStream& out, const Type& type );

#endif
