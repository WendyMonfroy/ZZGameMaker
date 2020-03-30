//
// Created by darklinkz42 on 20/02/2020.
//

#include "newConfirmationWindow.hpp"
NewConfirmationWindow::NewConfirmationWindow(QWidget *parent) : QMainWindow(parent) {
    setWindowTitle("Nouveau projet");
    QString label = "Voulez vous vraiment créer un nouveau projet ?\n"
                    "Le projet actuel va être fermé et les données non sauvegardées seront supprimées";
    confirmationPanel = new ConfirmationPanel("Nouveau projet", label, this);
    connect(confirmationPanel, &ConfirmationPanel::validated, this, &NewConfirmationWindow::clearing);
    connect(confirmationPanel, &ConfirmationPanel::canceled, this, &NewConfirmationWindow::canceling);
    connect(confirmationPanel, &ConfirmationPanel::saved, this, &NewConfirmationWindow::saving);

    setCentralWidget(confirmationPanel);
}

void NewConfirmationWindow::clearing() {
    emit clear();
    close();
}

void NewConfirmationWindow::canceling() {
    close();
}

void NewConfirmationWindow::saving() {
    emit save();
    close();
}