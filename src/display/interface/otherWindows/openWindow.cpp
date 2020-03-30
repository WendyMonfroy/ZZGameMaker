//
// Created by darklinkz42 on 19/02/2020.
//

#include <QLabel>
#include <QLineEdit>
#include <QHBoxLayout>
#include "openWindow.hpp"

OpenWindow::OpenWindow(QWidget *parent) : QMainWindow(parent) {
    pathSelector = new PathSelector("Ouvrir", "Ouvrir", true,this);
    connect(pathSelector, &PathSelector::pathEntered, this, &OpenWindow::save);

    OpenWindow::setCentralWidget(pathSelector);
}



void OpenWindow::save(QString path) {
    emit openPathEntered(path);
    close();
}