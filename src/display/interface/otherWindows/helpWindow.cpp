//
// Created by darklinkz42 on 13/02/2020.
//

#include <QLabel>
#include "helpWindow.hpp"

/**
 * Create a HelpWindow with a Qlabel to display
 * it contains information about how to use the application
 *
 * @param parent --> pointer of the widget which contain the element
 */
HelpWindow::HelpWindow(QWidget *parent) : QMainWindow(parent) {
    setWindowTitle("Commande de l'éditeur");
    QString lyrics = "Pour placer un objet élément dans la map :\n"
                     "\t - clickez sur le menu de votre élément à gauche de l'éditeur\n"
                     "\t - clickez sur l'élément souhaité\n"
                     "\t - placez la souris sur la case visée\n"
                     "\t - cliquez sur la case pour déposer l'élément\n\n"
                     "Vous pouvez posez des instances de l'élément en boucle\n"
                     "Pour changer d'élément, cliquez sur un autre élément dans les menus\n"
                     "Pour arrêter de poser l'élément, appuyer sur \"échap\"\n\n"
                     "Pour supprimer un élément posé sur la map : \"click droit\"\n"
                     "Pour déplacer un élément sur la map : \"click gauche\"\n"
                     "Pour accéder au mode de dépose continue :\n"
                     "\t - Double click gauche --> Active/désactive dépose continue\n"
                     "\t - Double click droit --> Active/désactive éffacement continue\n"
                     "\t - Shift --> Active/désactive dépose continue\n"
                     "\t - Suppr --> Active/désactive éffacement continue\n"
                     "\t - Echap --> Desactive la pose ou l'effacement\n\n"
                     "Déplacement dans la grille -->flèches directionnelles du clavier\n";

    QLabel * label = new QLabel(lyrics, this);
    label->setFont(QFont("Calibri", 12));
    label->setContentsMargins(24,24,24,24);
    label->setFixedSize(width(), height());

    this->setCentralWidget(label);
}