//
// Created by darklinkz42 on 26/02/2020.
//

#ifndef ZZMAKER_CASESTOCK_HPP
#define ZZMAKER_CASESTOCK_HPP

#include <utils/sprite.hpp>
#include <components/physic/map_element.hpp>
#include <bloc.hpp>
#include <player.hpp>
#include <ennemy.hpp>
#include <item.hpp>
#include <deco.hpp>
#include "case.hpp"

class CaseStock {

public:
    QString path;
    MapElement * mapElement;
    int x;
    int y;

public:
    CaseStock() {}
    CaseStock(Case * _case) :
            path(_case->getSprite()->getPath()),
            x(_case->getX()),
            y(_case->getY())
            {
                switch (_case->getMapElement()->type()) {
                    case Type::BLOC:
                        mapElement = new Bloc((Bloc *) _case->getMapElement());
                        break;
                    case Type::PLAYER:
                        mapElement = new Player((Player *) _case->getMapElement());
                        break;
                    case Type::ENNEMY:
                        mapElement = new Ennemy((Ennemy *) _case->getMapElement());
                        break;
                    case Type::ITEM:
                        mapElement = new Item((Item *) _case->getMapElement());
                        break;
                    case Type::DECO:
                        mapElement = new Deco((Deco *) _case->getMapElement());
                        break;
                    case Type ::NONE:
                        mapElement = new MapElement(_case->getMapElement());
                        break;
                }
            }
};


QDataStream & operator<<(QDataStream & out, CaseStock const &caseStock);

QDataStream & operator>>(QDataStream & in, CaseStock &caseStock);

#endif //ZZMAKER_CASESTOCK_HPP
