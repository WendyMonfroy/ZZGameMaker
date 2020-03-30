//
// Created by darklinkz42 on 19/02/2020.
//

#ifndef ZZMAKER_OPENWINDOW_HPP
#define ZZMAKER_OPENWINDOW_HPP

#include <QMainWindow>
#include <QKeyEvent>
#include <interface/otherWindows/component/pathSelector.hpp>

class OpenWindow : public QMainWindow {

Q_OBJECT

private:
    PathSelector * pathSelector;

public:
    OpenWindow(QWidget * parent = nullptr);


signals:
    void openPathEntered(QString path);

private slots:
    void save(QString path);
};

#endif //ZZMAKER_OPENWINDOW_HPP
