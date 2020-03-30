//
// Created by darklinkz42 on 20/02/2020.
//

#include <QPushButton>
#include <QtWidgets/QHBoxLayout>
#include "gameManager.hpp"

GameManager::GameManager(unsigned int width, unsigned int heigth, QWidget *parent) : QWidget(parent) {
    setFixedSize(width, heigth);
    QPushButton * gameLauncher = new QPushButton(this);
    QPushButton * gameDeployer = new QPushButton(this);

    gameLauncher->setText("Lancer test");
    gameDeployer->setText("Déployer");

    gameLauncher->setFixedSize(244, 144);
    gameDeployer->setFixedSize(244, 144);

    GameManager::connect(gameLauncher, &QPushButton::clicked, this, &GameManager::launchGame);
    GameManager::connect(gameDeployer, &QPushButton::clicked, this, &GameManager::deployGame);

    QVBoxLayout * layout = new QVBoxLayout();
    layout->addWidget(gameLauncher, 0, Qt::AlignTop | Qt::AlignLeft);
    layout->addWidget(gameDeployer, 0, Qt::AlignBottom | Qt::AlignLeft);
    layout->setContentsMargins(24, 244, 24, 244);

    setLayout(layout);
}

void GameManager::launchGame() {
    emit gameLaunched();
}

void GameManager::deployGame() {
    //TODO
}