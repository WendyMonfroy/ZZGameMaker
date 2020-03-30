//
// Created by darklinkz42 on 19/01/2020.
//

#ifndef ZZMAKER_EDITOR_HPP
#define ZZMAKER_EDITOR_HPP

#include <QWidget>
#include <QTimer>
#include <map/map.hpp>
#include <interface/menus/gameManager.hpp>
#include "menus/gameElementSelector.hpp"

class Editor : public QWidget {

    Q_OBJECT

private:
    GameElementSelector * gameElementSelector; //!< Pointer on a gameElementSelector --> menu to select elements to drag and drop
    Map * map; //!< Pointer on a Map --> grid in with elements can be dropped
    Sprite * sprite; //!< Pointer on a Sprite --> represent the sprite that can be drag and drop, only one at a time. It will be modified during the process to always use the right Sprite
    MapElement * mapElement; //!< Pointer on a MapElement --> represent the mapElement that can be add or remove to the list, only one at a time. It will be modified during the process to always use the right MapElement
    GameManager * gameManager;
    bool move; //!< Boolean which indicate if the sprite come from the GameElementSelector or from the Map
    bool movableMap; //!< Boolean which indicate if we can move the map or not
    QTimer * timer;

public:
    Editor(QWidget * parent = nullptr);
    void displayMapGrid(bool display);
    void saveStatus(QString path);
    void openStatus(QString path);
    void clearProject();

private:
    bool event(QEvent *e) override;
    void keyPressEvent(QKeyEvent * e) override;
    void filterEvent(QEvent * e);
    void dragSprite(QHoverEvent * e);

    signals:
    void gameStart(QMap<int, MapElement *>& elements);
    void saveError(QString errorMessage);
    void openError(QString errorMessage);

public slots:
    void createSprite(MapElement * mapElement, QString path);
    void createSpriteForMove(MapElement * mapElement, QString path, QPoint point);
    void dropSprite(Case * _case);
    void launchGame();
    void serializeError(QString errorMessage);
    void deserializeError(QString errorMessage);
    void updateMapMovability();
};

#endif //ZZMAKER_EDITOR_HPP
