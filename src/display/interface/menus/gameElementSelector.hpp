//
// Created by darklinkz42 on 19/01/2020.
//

#ifndef ZZMAKER_GAMEELEMENTSELECTOR_HPP
#define ZZMAKER_GAMEELEMENTSELECTOR_HPP

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QGridLayout>
#include "components/gameElement.hpp"

/**
 * Menu which provide all GameELements available for the game
 */
class GameElementSelector : public QWidget{

    Q_OBJECT

private:
    // list of all buttons used to display elements of category
    QPushButton * blocksButton; //!< Button used to display block elements
    QPushButton * charactersButton; //!< Button used to display character elements
    QPushButton * enemiesButton; //!< Button used to display enemies elements
    QPushButton * itemsButton; //!< Button used to display item elements
    QPushButton * decorationsButton; //!< Button used to display decoration elements

    // list of items in a category
    QList<GameElement *> blockElements; //!< List of all blocks available for the game
    QList<GameElement *> characterElements; //!< List of all blocks characters for the game
    QList<GameElement *> enemiesElements; //!< List of all blocks enemies for the game
    QList<GameElement *> itemElements; //!< List of all blocks items for the game
    QList<GameElement *> decorationElements; //!< List of all blocks decorations for the game

    // layouts
    QVBoxLayout *vbox; //!< Global layout of the widget which contains all other elements and layouts

    //button with all selectable items bellow
    QVBoxLayout *vblocksButtonbox; //!< Vertical layout of blocks which contain block button on the top and grid of elements bellow
    QVBoxLayout *vcharactersButtonbox; //!< Vertical layout of characters which contain block button on the top and grid of elements bellow
    QVBoxLayout *venemiesButtonbox; //!< Vertical layout of enemies which contain block button on the top and grid of elements bellow
     QVBoxLayout *vitemsButtonbox; //!< Vertical layout of items which contain block button on the top and grid of elements bellow
     QVBoxLayout *vdecorationsButtonbox; //!< Vertical layout of decorations which contain block button on the top and grid of elements bellow

    //grid n * 4 of all selectable elements by category
    QGridLayout *blockElementsGridLayout; //!< Grid layout of blocks which contain all blocks
    QGridLayout *characterElementsGridLayout; //!< Grid layout of characters which contain all characters
    QGridLayout *enemiesElementsGridLayout; //!< Grid layout of characters which contain all characters
    QGridLayout *itemElementsGridLayout; //!< Grid layout of items which contain all items
    QGridLayout *decorationElementsGridLayout; //!< Grid layout of decorations which contain all decorations

public:
    GameElementSelector(unsigned int width, unsigned int heigth, QWidget * parent = nullptr);

private:
    void initButtons();
    void initElementList();
    void addElementToList(QList<GameElement *> &listElement, QString path, bool display, MapElement * element);
    void enableAllButtons();
    void unDisplayAllElement();

    void setUpDisplay();
    void fillGridLayout(QGridLayout * layout, QList<GameElement *> elements);
    void changeDisplay(QPushButton * button);

signals:
    /**
     * signal which provide mapElement and path
     *
     * @param mapElement --> Pointer on the physic game element to create
     * @param path --> path to the image of the sprite
     */
    void onSpriteCreate(MapElement * mapElement, QString path);

private slots:
    void onBlocksButtonClicked();
    void onCharactersButtonClicked();
    void onEnemiesButtonClicked();
    void onItemsButtonClicked();
    void onDecorationButtonClicked();
    void spriteCreated(MapElement * mapElement, QString path);
};

#endif //ZZMAKER_GAMEELEMENTSELECTOR_HPP
