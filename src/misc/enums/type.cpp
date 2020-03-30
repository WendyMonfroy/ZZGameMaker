//
// Created by darklinkz42 on 18/02/2020.
//

#include "type.hpp"

QString getTypeName( Type const& type ) {
  QString typeName = "";
  switch ( type ) {
  case Type::NONE:
    typeName = "none";
    break;
  case Type::PLAYER:
    typeName = "player";
    break;
  case Type::ENNEMY:
    typeName = "enemy";
    break;
  case Type::BLOC:
    typeName = "bloc";
    break;
  case Type::ITEM:
    typeName = "item";
    break;
  case Type::DECO:
    typeName = "deco";
    break;
  default:
    break;
  }
  return typeName;
}

Type getType( QString& typeName ) {
  Type type = Type::NONE;
  if ( QString::compare( typeName, getTypeName( Type::NONE ) ) == 0 ) {
    type = Type::NONE;
  } else if ( QString::compare( typeName, getTypeName( Type::PLAYER ) ) == 0 ) {
    type = Type::PLAYER;
  } else if ( QString::compare( typeName, getTypeName( Type::ENNEMY ) ) == 0 ) {
    type = Type::ENNEMY;
  } else if ( QString::compare( typeName, getTypeName( Type::BLOC ) ) == 0 ) {
    type = Type::BLOC;
  } else if ( QString::compare( typeName, getTypeName( Type::ITEM ) ) == 0 ) {
    type = Type::ITEM;
  } else if ( QString::compare( typeName, getTypeName( Type::DECO ) ) == 0 ) {
    type = Type::DECO;
  }

  return type;
}

QDataStream& operator<<( QDataStream& out, Type const& type ) {
  out << getTypeName( type );
  return out;
}