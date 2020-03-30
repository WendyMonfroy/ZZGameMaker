//
// Created by darklinkz42 on 18/02/2020.
//

#ifndef ZZMAKER_SAVEWINDOW_HPP
#define ZZMAKER_SAVEWINDOW_HPP

#include <QMainWindow>
#include <QLabel>
#include <QLineEdit>
#include <QKeyEvent>
#include <QPushButton>
#include <interface/otherWindows/component/pathSelector.hpp>

class SaveWindow : public QMainWindow {

    Q_OBJECT

private:
    PathSelector * pathSelector;

public:
    SaveWindow(QWidget * parent = nullptr);


signals:
    void savePathEntered(QString path);

private slots:
    void save(QString path);

};

#endif //ZZMAKER_SAVEWINDOW_HPP
