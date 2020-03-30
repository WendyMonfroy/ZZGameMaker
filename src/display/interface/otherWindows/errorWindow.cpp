//
// Created by darklinkz42 on 23/02/2020.
//

#include "errorWindow.hpp"
#include <QLabel>

/**
 * Create a HelpWindow with a Qlabel to display
 * it contains information about how to use the application
 *
 * @param parent --> pointer of the widget which contain the element
 */
ErrorWindow::ErrorWindow(QWidget *parent) : QMainWindow(parent) {
    setFixedSize(404, 404);
    label = new QLabel("", this);
    label->setFont(QFont("Calibri", 12));
    label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

    this->setCentralWidget(label);
}