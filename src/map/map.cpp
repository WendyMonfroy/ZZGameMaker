//
// Created by darklinkz42 on 04/02/2020.
//

#include "map.hpp"
#include <QPainter>
#include <interface/editor.hpp>
#include <iostream>
#include <QDir>
#include <QTextStream>
#include <bloc.hpp>
#include <player.hpp>
#include <ennemy.hpp>
#include <item.hpp>
#include <deco.hpp>
#include "enums/colors.hpp"

/**
 * Create a Map
 * Create all the Cases of the Map and display it into a QGridLayout
 *
 * @param parent --> pointer of the widget which contain the element
 */
Map::Map(QWidget * parent) : QWidget(parent) {

    setAttribute(Qt::WA_Hover);

    gridLayout = new QGridLayout();
    display = false;
    xVariation = 0;
    yVariation = 0;
    createMap();
    setDisplay();
    paint = false;
    setLayout(gridLayout);
}

/**
 * Create all the Cases of the Map and connect the Map to each Case signals
 */
void Map::createMap() {
    int i = 0;
    grid.resize(20);
    for (auto &cases : grid) {
        int j = 0;
        cases.resize(25);
        for (auto &_case : cases) {
            _case = new Case(i, j);
            Map::connect(_case, &Case::onDrop, this, &Map::dropSprite);
            Map::connect(_case, &Case::onMove, this, &Map::moveSprite);
            Map::connect(_case, &Case::onErase, this, &Map::eraseElement);
            Map::connect(_case, &Case::coordonates, this, &Map::getCase);
            ++j;
        }
        ++i;
    }
}

/**
 * add the Cases in the QGridLayout
 */
void Map::setDisplay() {
    setFixedSize(50*grid[0].size(), 50*grid.size());
    gridLayout->setSpacing(0);
    gridLayout->setSizeConstraint(QLayout::SetFixedSize);
    for (int i = 0 ; i < grid.size() ; ++i) {
        for (int j = 0 ; j < grid[0].size() ; ++j) {
            gridLayout->addWidget(grid[i][j], i, j);
      }
    }
}

void Map::moveMap(int &&xvariation, int &&yvariation) {
    for (auto &cases : grid) {
        for (auto &_case : cases) {
            int newX = _case->getX() + xvariation;
            int newY = _case->getY() + yvariation;
            _case->setX(newX);
            _case->setY(newY);
            if (activeCases.contains(QPoint(newX, newY))) {
                auto it = activeCases.find(QPoint(newX, newY));
                _case->setSprite(it->path);
                _case->changeMapElement(it->mapElement);
            } else {
                _case->clean();
            }
        }
    }
}


void Map::moveRight() {
    moveMap(0, 1);
    ++yVariation;
}

void Map::moveDown() {
    moveMap(1, 0);
    ++xVariation;
}

void Map::moveLeft() {
    moveMap(0, -1);
    --yVariation;
}

void Map::moveUp() {
    moveMap(-1, 0);
    --xVariation;
}

/**
 * Display the Map with or without the grid following the display atribut
 */
void Map::paintGrid() {
    for (auto cases : grid) {
        for (auto _case : cases) {
            _case->setDrawGrid(display);
        }
    }

}

/**
 * react to whatever QEvent on the Editor and filter this event
 *
 * @param e --> pointer on a QEvent
 * @return boolean about the event
 */
bool Map::event(QEvent *e) {
    filterEvent(e);
    return QWidget::event(e);
}

/**
 * apply the good process corresponding to the type of event
 * here, react only react to hoverMove to get the position of the mouse when it is on the Editor
 * @param e --> pointer on the QEvent to filter
 */
void Map::filterEvent(QEvent *e) {
    switch (e->type()) {
        case QEvent::HoverMove:
            //getCase(static_cast<QHoverEvent *>(e));
            callCase(paint);
            break;
        default:
            break;
    }
}

void Map::getCase(int &x, int &y) {
    currentCase.setX(x);
    currentCase.setY(y);
    // glitch version permettant clic continu mais pas explicable donc abandonnée
    /*
     * Lors du clic, le curseur appartient à la map et n'est plus capté par les cases --> impossible de récupérer les coordonnées en provenance de la case
     * possible de récupéré la position sur la map mais les cases ne font pas la bonne taille. il y a un grow automatique qui n'a pas réussit à etre enlevé
     * du coup découpage incorect
     * Avec un strech(1) sur toutes les cases et colonne, le grow est le meme partout --> découpage avec -12 semble fonctionner
     * Impossible de valider ce fonctionnement donc abandon de la piste au profit du activate/desactivate
     */
/*void Map::getCase(QHoverEvent * e) {
    currentCase.setX((e->pos().y() - 12) / 50);
    currentCase.setY((e->pos().x() - 12) / 50);
}

bool Map::isInGrid(QPoint mousePosition) {
    return mousePosition.x() >= 0 && mousePosition.x() < grid.size()
    && mousePosition.y() >= 0 && mousePosition.y() < grid[0].size();
}

void Map::mousePressEvent(QMouseEvent *e) {
    if (e->button() == Qt::RightButton || e->button() == Qt::LeftButton ) {
        paint = false;
    }
*/
}

void Map::callCase(bool paintActive) {
    if (paintActive) {
       // if (isInGrid(currentCase)) {
            grid[currentCase.x() - xVariation][currentCase.y() - yVariation]->caseClicked(buttonClicked);
       // }
    }
}

void Map::mousePressEvent(QMouseEvent *e) {
    if (e->button() == Qt::RightButton || e->button() == Qt::LeftButton ) {
        buttonClicked = e->button();
        callCase(true);
    }
}

void Map::mouseDoubleClickEvent(QMouseEvent *e) {
    if (e->button() == Qt::RightButton || e->button() == Qt::LeftButton ) {
        paint = !paint;
        buttonClicked = e->button();
    }
}

Map::Grid Map::createCopy() {
    Grid copy;
    copy.resize(grid.size());
    for (auto &cases : copy) {
        cases.resize(grid[0].size());
    }
    return copy;
}

void Map::restoreMapFromCopy(Map::Grid &copy) {
    for (int i = 0 ; i < grid.size() ; ++i) {
        for (int j = 0 ; j < grid[0].size() ; ++j) {
            if (copy[i][j]->getSprite()->getDisplay()) {
                grid[i][j]->setSprite(copy[i][j]->getSprite()->getPath());
                grid[i][j]->setMapElement(copy[i][j]->getMapElement());
            }
        }
    }
}

void Map::deleteCopy(Grid &copy) {
    for (auto &cases : copy) {
        for (auto &_case : cases) {
            delete _case;
        }
        cases.resize(0);
    }
    copy.resize(0);
    copy.clear();
}

/**
 * React when a Case is clicked and signal it
 *
 * @param _case --> pointer on the Case that has been clicked
 */
void Map::dropSprite(Case * _case) {
    emit caseClicked(_case);
}

/**
 * react when a Case has been clicked to move an element and signal it
 *
 * @param mapElement --> pointer on the mapElement to move
 * @param path --> path of the image associated to the sprite to display and the image of the mapElement
 */
void Map::moveSprite(MapElement * mapElement, QString path, QPoint point) {
    emit spriteMoved(mapElement, path, point);
}

/**
 * react when the state of the grid display parameter change
 *
 * @param display --> new state of the grid display parameter
 */
void Map::displayGrid(bool display) {
    this->display = display;
    paintGrid();
}

/**
 * add an Element to the map of MapElement
 *
 * @param mapElement --> pointer on the mapElement to add
 */
void Map::registerElement(MapElement * mapElement, Case * _case) {
    activeCases.insert(QPoint(_case->getX(), _case->getY()), CaseStock(_case));
    switch (mapElement->type()) {
        case Type::BLOC:
            elements.insert(mapElement->getID(), new Bloc((Bloc *) mapElement));
            break;
        case Type::PLAYER:
            elements.insert(mapElement->getID(), new Player((Player *) mapElement));
            break;
        case Type::ENNEMY:
            elements.insert(mapElement->getID(), new Ennemy((Ennemy *) mapElement));
            break;
        case Type::ITEM:
            elements.insert(mapElement->getID(), new Item((Item *) mapElement));
            break;
        case Type::DECO:
            elements.insert(mapElement->getID(), new Deco((Deco *) mapElement));
            break;
        case Type ::NONE:
            elements.insert(mapElement->getID(), new MapElement(mapElement));
            break;
    }
}

/**
 * delete a MapElement by id from the map of MapElement
 *
 * @param id --> id of the MapElement to delete
 */
void Map::deleteElement(unsigned int const id, QPoint point) {
    activeCases.remove(point);
    elements.remove(id);
    availableID.push(id);
}

/**
 * react when an element has to be deleted and delete it by id
 *
 * @param id --> id of the MapElement to delete
 */
void Map::eraseElement(unsigned int const id, QPoint point) {
    deleteElement(id, point);
}


void Map::serialize(QString path) {
    QDir dir(path);
    if (!dir.exists()) {
        emit serializationError("Le chemin entré n'existe pas");
    } else {

        QString project = "/project.zzm";
        project.prepend(path);
        QString elems = "/data/elems.zze";
        elems.prepend(path);
        QString cases = "/data/cases.zzc";
        cases.prepend(path);
        QString data = "/data";
        data.prepend(path);

        dir.mkdir(data);

        QFile projectFile(project);
        QFile elementsFile(elems);
        QFile casesFile(cases);

        if (!projectFile.open(QIODevice::WriteOnly)) {
            emit serializationError("L'enregistrement a échoué'");
        } else {
            projectFile.resize(0);
            projectFile.write(elems.toUtf8().constData());
            projectFile.write("\n");
            projectFile.write(cases.toUtf8().constData());
            projectFile.close();
            if (!elementsFile.open(QIODevice::WriteOnly)) {
                emit serializationError("L'enregistrement a échoué'");
            } else {
                elementsFile.resize(0);
                QDataStream elementsOut(&elementsFile);
                elementsOut.setVersion(QDataStream::Qt_5_5);
                auto it = elements.find(1);
                (Player *) *it;
                elementsOut << elements;
                elementsFile.flush();
                elementsFile.close();
            }
            if (!casesFile.open(QIODevice::WriteOnly)) {
                emit serializationError("L'enregistrement a échoué'");
            } else {
                casesFile.resize(0);
                QDataStream casesOut(&casesFile);
                casesOut.setVersion(QDataStream::Qt_5_5);
                casesOut << grid;
                casesOut << activeCases;
                casesFile.flush();
                casesFile.close();
            }
        }
    }
}

void Map::deserialize(QString path) {

    if (!path.endsWith(".zzm")) {
        emit deserializationError("Le chemin ne correspond pas à un fichier de projet");
    } else {

        QString project = path;
        QString elems = "";
        QString cases = "";
        QFile projectFile(project);

        if (!projectFile.open(QIODevice::ReadOnly)) {
            emit deserializationError("Le fichier ne s'est pas ouvert correctement");
        } else {
            QTextStream in(&projectFile);
            elems = in.readLine();
            cases = in.readLine();
            projectFile.close();

            if (!elems.endsWith(".zze") || !cases.endsWith(".zzc")) {
                emit deserializationError("les données sont corrompues");
            } else {
                QFile elementsFile(elems);
                QFile casesFile(cases);
                if (!elementsFile.open(QIODevice::ReadOnly)) {
                    emit deserializationError("Les fichiers de restauration ne se sont pas ouvert correctement");
                } else {
                    QDataStream elementsIn(&elementsFile);
                    elementsIn.setVersion(QDataStream::Qt_5_5);
                    elementsIn >> elements;
                    elementsFile.close();
                }

                if (!casesFile.open(QIODevice::ReadOnly)) {
                    emit deserializationError("Les fichiers de restauration ne se sont pas ouvert correctement");
                } else {
                    QDataStream casesIn(&casesFile);
                    casesIn.setVersion(QDataStream::Qt_5_5);
                    Grid copy = createCopy();
                    casesIn >> copy;
                    restoreMapFromCopy(copy);
                    deleteCopy(copy);
                    casesIn >> activeCases;
                    casesFile.close();
                }
            }
        }
    }
}

void Map::clearMap() {
    elements.clear();
    for (auto &cases : grid) {
        for (auto &_case : cases) {
            _case->clearCase();
        }
    }
    activeCases.clear();
}


bool operator<(QPoint const & first, QPoint const & second) {
    return first.x() <second.x() ||
    ( first.x() == second.x() && first.y() < second.y() ) ;
}