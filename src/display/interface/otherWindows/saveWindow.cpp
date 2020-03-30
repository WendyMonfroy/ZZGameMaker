//
// Created by darklinkz42 on 18/02/2020.
//

#include <QHBoxLayout>
#include "saveWindow.hpp"
#include <iostream>

SaveWindow::SaveWindow(QWidget *parent) : QMainWindow(parent) {
    pathSelector = new PathSelector("Enregistrer sous", "enregistrer",false, this);

    connect(pathSelector, &PathSelector::pathEntered, this, &SaveWindow::save);

    SaveWindow::setCentralWidget(pathSelector);
}



void SaveWindow::save(QString path) {
    emit savePathEntered(path);
    close();
}