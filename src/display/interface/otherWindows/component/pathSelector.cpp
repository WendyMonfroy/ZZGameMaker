//
// Created by darklinkz42 on 19/02/2020.
//

#include "pathSelector.hpp"
#include <QHBoxLayout>
#include <iostream>
#include <QFileDialog>

PathSelector::PathSelector(QString name, QString buttonName, bool file, QWidget *parent) : QWidget(parent), file(file) {
    setFixedHeight(144);
    QLabel * path = new QLabel("Chemin :");
    QPushButton * validate = new QPushButton();
    QPushButton * choseFolder = new QPushButton();
    pathEdit = new QLineEdit();

    pathEdit->setFixedWidth(400);
    path->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    validate->setText(buttonName);
    choseFolder->setText("Parcourir");

    setWindowTitle(name);

    connect(validate, &QPushButton::clicked, this, &PathSelector::save);
    connect(choseFolder, &QPushButton::clicked, this, &PathSelector::search);

    QVBoxLayout * mainLayout = new QVBoxLayout(this);
    QHBoxLayout * layout = new QHBoxLayout();
    QHBoxLayout * buttonLayout = new QHBoxLayout();

    layout->addWidget(path);
    layout->addWidget(pathEdit, 1, Qt::AlignLeft);
    buttonLayout->addWidget(choseFolder, Qt::AlignBottom | Qt::AlignLeft);
    buttonLayout->addWidget(validate, Qt::AlignBottom | Qt::AlignRight);

    mainLayout->addLayout(layout);
    mainLayout->addLayout(buttonLayout);

    this->setLayout(mainLayout);
}

void PathSelector::keyPressEvent(QKeyEvent *e) {
    switch (e->key()) {
        case Qt::Key_Enter:
            emit pathEntered(pathEdit->text());
            break;
        case Qt::Key_Return:
            emit pathEntered(pathEdit->text());
            break;
        default:
            break;
    }
}

void PathSelector::save() {
    if (pathEdit->text().size() != 0) {
        emit pathEntered(pathEdit->text());
    }
}

void PathSelector::search() {
    if (file) {
        pathEdit->setText(QFileDialog::getOpenFileName(this, tr("Choisie le fichier du projet"), QDir::homePath(), "*.zzm"));
    } else {
        pathEdit->setText(QFileDialog::getExistingDirectory(this, tr("Choisir le dossier de sauvegarde"), QDir::homePath()));
    }
}