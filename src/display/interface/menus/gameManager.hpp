//
// Created by darklinkz42 on 20/02/2020.
//

#ifndef ZZMAKER_GAMEMANAGER_HPP
#define ZZMAKER_GAMEMANAGER_HPP

#include <QWidget>

class GameManager : public QWidget {

    Q_OBJECT

public:
    GameManager(unsigned int width, unsigned int heigth, QWidget * parent = nullptr);

    signals:
    void gameLaunched();

private slots :
    void launchGame();
    void deployGame();

};


#endif //ZZMAKER_GAMEMANAGER_HPP
