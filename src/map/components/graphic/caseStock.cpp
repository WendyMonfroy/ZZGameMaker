//
// Created by darklinkz42 on 26/02/2020.
//

#include "caseStock.hpp"

QDataStream & operator<<(QDataStream & out, CaseStock const &caseStock) {
    out << caseStock.path << caseStock.mapElement << caseStock.x << caseStock.y;
    return out;
}

QDataStream & operator>>(QDataStream & in, CaseStock &caseStock) {
    qint32 x, y;
    in >> caseStock.path >> caseStock.mapElement >> x >> y;
    caseStock.x = x;
    caseStock.y = y;
    return in;
}
