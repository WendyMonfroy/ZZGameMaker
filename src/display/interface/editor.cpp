//
// Created by darklinkz42 on 19/01/2020.
//

#include "editor.hpp"
#include <QHBoxLayout>
#include <QApplication>
#include <QDesktopWidget>

/**
 * Create an Editor which contains a GameElementSelector and a Map
 * it also create pointer on sprite and mapElement to communicate these information with its attributes
 * it set the layout and connect the Editor to signals of the Map and the GameElementSelector
 * @param parent --> pointer of the widget which contain the element
 */
Editor::Editor(QWidget *parent) : QWidget(parent) {

    setAttribute(Qt::WA_Hover);
    setFocusPolicy(Qt::ClickFocus);
    gameElementSelector = new GameElementSelector(244, 980, this);
    map = new Map(this);
    gameManager = new GameManager(344, 980, this);
    sprite = new Sprite(this);
    move = false;
    movableMap = true;
    timer = new QTimer(this);

    QHBoxLayout * hbox = new QHBoxLayout(this);

    hbox->addWidget(gameElementSelector, 1, Qt::AlignTop);
    hbox->addWidget(map, 1, Qt::AlignTop);
    hbox->addWidget(gameManager, 1, Qt::AlignTop);

    setLayout(hbox);
    hbox->setContentsMargins(1, 1, 1, 1);

    Editor::connect(gameElementSelector, &GameElementSelector::onSpriteCreate, this, &Editor::createSprite);
    Editor::connect(map, &Map::caseClicked, this, &Editor::dropSprite);
    Editor::connect(map, &Map::spriteMoved, this, &Editor::createSpriteForMove);
    Editor::connect(gameManager, &GameManager::gameLaunched, this, &Editor::launchGame);
    Editor::connect(map, &Map::serializationError, this, &Editor::serializeError);
    Editor::connect(map, &Map::deserializationError, this, &Editor::deserializeError);
    Editor::connect(timer, &QTimer::timeout, this, &Editor::updateMapMovability);
}

void Editor::clearProject() {
    map->clearMap();
}

/**
 * react to whatever QEvent on the Editor and filter this event
 *
 * @param e --> pointer on a QEvent
 * @return boolean about the event
 */
bool Editor::event(QEvent *e) {
    filterEvent(e);
    return QWidget::event(e);
}

/**
 * apply the good process corresponding to the type of event
 * here, react only react to hoverMove to get the position of the mouse when it is on the Editor
 * @param e --> pointer on the QEvent to filter
 */
void Editor::filterEvent(QEvent *e) {
    switch (e->type()) {
        case QEvent::HoverMove:
            dragSprite(static_cast<QHoverEvent *>(e));
            break;
        default:
            break;
    }
}

/**
 * move the sprite following the mouse on the screen
 *
 * @param e --> pointer on a QHoverEvent which provide mouse position
 */
void Editor::dragSprite(QHoverEvent *e) {
    if (sprite->getDisplay()) {
        sprite->setGeometry(e->pos().x() + 5, e->pos().y() + 5, sprite->width(), sprite->height());
    }
}



/**
 * if draging mode is available, create a sprite to drag and drop its into the Map
 *
 * @param mapElement --> pointer on the mapElement to create
 * @param path --> path of the image associated to the sprite to display and the image of the mapElement
 */
void Editor::createSprite(MapElement * mapElement, QString path) {
    if (!move || !sprite->getDisplay()) {
        sprite->setPath(path);
        sprite->setDisplay(true);
        this->mapElement = mapElement;
    }
}

/**
 * if draging mode is available, create a sprite to drag and drop its into the Map
 * indicate that the sprite is created from the map and not form the GameElementSelector
 * the mapElement in deleted from the list of physic instance of elements
 * the sprite is created for only one drop
 *
 * @param mapElement --> pointer on the mapElement to create
 * @param path --> path of the image associated to the sprite to display and the image of the mapElement
 */
void Editor::createSpriteForMove(MapElement * mapElement, QString path, QPoint point) {
    move = true;
    map->deleteElement(mapElement->getID(), point);
    createSprite(mapElement, path);
}

/**
 * if an element is currently drag, it drops it into the case
 * it also update properties of mapElement to add it into the physic list of elements
 * if it an existing element moved from the map, it deactivate draging mode
 *
 * @param _case --> pointer on the Case that has been clicked
 */
void Editor::dropSprite(Case *_case) {
    if (sprite->getDisplay()) {
        mapElement->setHitboxPosition(_case->getX() * sprite->width(), _case->getY() * sprite->height());
        mapElement->setPosition(_case->getX() * sprite->width(), _case->getY() * sprite->height());
        mapElement->setID(map->getAvailableID());
        _case->setMapElement(mapElement);
        _case->setSprite(sprite->getPath());
        map->registerElement(mapElement, _case);
    }
    if (move) {
        move = false;
        sprite->setDisplay(false);
        sprite->setSize(0,0);
    }
}

/**
 * react to a key pressed and deactivate draging mode if escape is pressed
 *
 * @param e --> pointer on a QKeyEvent which incidate which key has been pressed
 */
void Editor::keyPressEvent(QKeyEvent *e) {
    switch (e->key()) {
        case Qt::Key_Escape:
            sprite->setDisplay(false);
            sprite->setSize(0,0);
            map->setPaint(false);
            break;
        case Qt::Key_Shift:
            map->setMouseButton(Qt::LeftButton);
            map->setPaint(!map->getPaint());
            break;
        case Qt::Key_Delete:
            map->setMouseButton(Qt::RightButton);
            map->setPaint(!map->getPaint());
            break;
        case Qt::Key_Right:
            if (movableMap) {
                movableMap = false;
                map->moveRight();
                timer->start(100);
            }
            break;
        case Qt::Key_Down:
            if (movableMap) {
                movableMap = false;
                map->moveDown();
                timer->start(100);
            }
            break;
        case Qt::Key_Left:
            if (movableMap) {
                movableMap = false;
                map->moveLeft();
                timer->start(100);
            }
            break;
        case Qt::Key_Up:
            if (movableMap) {
                movableMap = false;
                map->moveUp();
                timer->start(100);
            }
            break;
        default:
            break;
    }
}

/**
 * display the grid on the map or not
 *
 * @param display --> boolean which indicate if grid has to be displayed or not
 */
void Editor::displayMapGrid(bool display) {
    map->displayGrid(display);
}

void Editor::saveStatus(QString path) {
    map->serialize(path);
}

void Editor::openStatus(QString path) {
    map->clearMap();
    map->deserialize(path);
}

void Editor::launchGame() {
    emit gameStart(map->getMapElements());
}

void Editor::serializeError(QString errorMessage) {
    emit saveError(errorMessage);
}

void Editor::deserializeError(QString errorMessage) {
    emit openError(errorMessage);
}


void Editor::updateMapMovability() {
    timer->stop();
    movableMap = true;
}