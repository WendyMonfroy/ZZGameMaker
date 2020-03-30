//
// Created by darklinkz42 on 19/01/2020.
//

#include "colors.hpp"

/**
 * Create a QColor and associate the right RGB code corresponding to the Color in parameter
 *
 * @param c --> Name of a color of the enum Colors
 * @return  QColor associated to the Name of the Color
 */
QColor get(Colors c){
    QColor color = Qt::white;
    switch (c) {
        case Colors::DARK_GREY:
            color = QColor(6, 6, 6);
            break;
        case Colors::GREY:
            color = QColor(66, 66, 66);
            break;
        case Colors::LIGHT_GREY:
            color = QColor(121, 121, 121);
            break;
        case Colors::RED:
            color = QColor(255, 6, 6);
            break;
        case Colors::WHITE:
            color = QColor(220, 220, 220);
            break;
    }
    return color;
}

/**
 * Get the QColor associated to the parameter c and fill the background of the widget with this QColor
 *
 * @param c --> Name of a color of the enum Colors
 * @param widget --> pointer of the widget to have its background set
 */
void setBackGround(Colors c, QWidget * widget) {
    widget->setAutoFillBackground(true);
    QPalette palette = widget->palette();
    palette.setColor(QPalette::Window, get(c));
    widget->setPalette(palette);
}