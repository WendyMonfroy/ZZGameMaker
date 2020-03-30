//
// Created by darklinkz42 on 19/01/2020.
//

#ifndef ZZMAKER_COLORS_HPP
#define ZZMAKER_COLORS_HPP

#include <QColor>
#include <QWidget>

/**
 * Enumeration of all the colors used in the application
 */
enum class Colors {
    DARK_GREY,
    GREY,
    LIGHT_GREY,
    RED,
    WHITE
};


QColor get(Colors c);

void setBackGround(Colors c, QWidget * widget);


#endif //ZZMAKER_COLORS_HPP
