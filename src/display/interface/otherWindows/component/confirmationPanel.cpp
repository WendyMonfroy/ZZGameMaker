//
// Created by darklinkz42 on 20/02/2020.
//

#include <QtWidgets/QPushButton>
#include <QtWidgets/QHBoxLayout>
#include "confirmationPanel.hpp"

ConfirmationPanel::ConfirmationPanel(QString name, QString label, QWidget *parent) : QWidget(parent) {
    QLabel * waningMessage = new QLabel(label, this);
    QPushButton * yes = new QPushButton(this);
    yes->setText(name);
    connect(yes, &QPushButton::clicked, this, &ConfirmationPanel::yesClicked);
    QPushButton * cancel = new QPushButton(this);
    cancel->setText("Annuler");
    connect(cancel, &QPushButton::clicked, this, &ConfirmationPanel::cancelClicked);
    QPushButton * save = new QPushButton(this);
    save->setText("Sauvegarder");
    connect(save, &QPushButton::clicked, this, &ConfirmationPanel::saveClicked);

    QVBoxLayout * mainLayout = new QVBoxLayout();
    QHBoxLayout * buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(yes, 0, Qt::AlignLeft | Qt::AlignBottom);
    buttonLayout->addWidget(cancel, 0, Qt::AlignCenter | Qt::AlignBottom);
    buttonLayout->addWidget(save, 0, Qt::AlignRight | Qt::AlignBottom);

    mainLayout->addWidget(waningMessage, Qt::AlignTop);
    mainLayout->addStretch(1);
    mainLayout->addLayout(buttonLayout, Qt::AlignBottom);

    setLayout(mainLayout);

}

void ConfirmationPanel::yesClicked() {
    emit validated();
}

void ConfirmationPanel::cancelClicked() {
    emit canceled();
}

void ConfirmationPanel::saveClicked() {
    emit saved();
}