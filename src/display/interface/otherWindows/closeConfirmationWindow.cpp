//
// Created by darklinkz42 on 20/02/2020.
//

#include "closeConfirmationWindow.hpp"

CloseConfirmationWindow::CloseConfirmationWindow(QWidget *parent) : QMainWindow(parent) {
    setWindowTitle("Fermeture");
    QString label = "Voulez vous vraiment fermer l'éditeur ?\n"
                    "Les données non sauvegardées seront supprimées";
    confirmationPanel = new ConfirmationPanel("Fermeture", label, this);
    connect(confirmationPanel, &ConfirmationPanel::validated, this, &CloseConfirmationWindow::closing);
    connect(confirmationPanel, &ConfirmationPanel::canceled, this, &CloseConfirmationWindow::canceling);
    connect(confirmationPanel, &ConfirmationPanel::saved, this, &CloseConfirmationWindow::saving);

    setCentralWidget(confirmationPanel);
}

void CloseConfirmationWindow::closing() {
    emit closeProject();
    close();
}

void CloseConfirmationWindow::canceling() {
    close();
}

void CloseConfirmationWindow::saving() {
    emit save();
    close();
}