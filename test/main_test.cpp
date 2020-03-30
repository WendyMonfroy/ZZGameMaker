//
// Created by darklinkz42 on 19/01/2020.
//

#include <QApplication>
#include "interface/mainWindow.hpp"

int main(int argc, char *argv[]){

    QApplication app(argc, argv);

    MainWindow window;

    window.showMaximized();

    return app.exec();
}