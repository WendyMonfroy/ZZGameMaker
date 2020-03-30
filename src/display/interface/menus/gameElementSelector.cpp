//
// Created by darklinkz42 on 19/01/2020.
//

#include <bloc.hpp>
#include <player.hpp>
#include <deco.hpp>
#include <item.hpp>
#include <ennemy.hpp>
#include "gameElementSelector.hpp"
#include "../../enums/colors.hpp"
#include "../../enums/assetsFiles.hpp"

/**
 * Create a GameElementSelector
 * Set all the elements in the layout
 * create and set the position of all buttons and GameElements
 *
 * @param width --> width of the widget
 * @param heigth --> heigth of the widget
 * @param parent --> pointer of the widget which contain the element
 */
GameElementSelector::GameElementSelector(unsigned int width, unsigned int heigth, QWidget * parent) : QWidget(parent) {
    vbox = new QVBoxLayout();
    setFixedSize(width, heigth);
    initButtons();
    initElementList();
    setUpDisplay();
    setLayout(vbox);
}

/**
 * Create the buttons of all menus
 * Each button display the list of the elements correponding to its category
 * dispable the button of the first category (opened category can't be reopen again)
 */
void GameElementSelector::initButtons() {

    blocksButton = new QPushButton("Blocs");
    charactersButton = new QPushButton("Personnages");
    enemiesButton = new QPushButton("Ennemis");
    itemsButton = new QPushButton("items");
    decorationsButton = new QPushButton("Décorations");

    connect(blocksButton, &QPushButton::clicked, this, &GameElementSelector::onBlocksButtonClicked);
    connect(charactersButton, &QPushButton::clicked, this, &GameElementSelector::onCharactersButtonClicked);
    connect(enemiesButton, &QPushButton::clicked, this, &GameElementSelector::onEnemiesButtonClicked);
    connect(itemsButton, &QPushButton::clicked, this, &GameElementSelector::onItemsButtonClicked);
    connect(decorationsButton, &QPushButton::clicked, this, &GameElementSelector::onDecorationButtonClicked);

    blocksButton->setDisabled(true);
}

/**
 * Add all GameElements in their corresponding QList
 */
void GameElementSelector::initElementList() {
    addElementToList(blockElements, getAssetsFileQString(AssetsFiles::BLOCK0), true,
                     new Bloc(getAssetsFileName(AssetsFiles::BLOCK0)));
    addElementToList(blockElements, getAssetsFileQString(AssetsFiles::BLOCK1), true,
                     new Bloc(getAssetsFileName(AssetsFiles::BLOCK1)));
    addElementToList(blockElements, getAssetsFileQString(AssetsFiles::BLOCK2), true,
                     new Bloc(getAssetsFileName(AssetsFiles::BLOCK2)));
    addElementToList(blockElements, getAssetsFileQString(AssetsFiles::BLOCK3), true,
                     new Bloc(getAssetsFileName(AssetsFiles::BLOCK3)));
    addElementToList(blockElements, getAssetsFileQString(AssetsFiles::BLOCK4), true,
                     new Bloc(getAssetsFileName(AssetsFiles::BLOCK4)));
    addElementToList(blockElements, getAssetsFileQString(AssetsFiles::BLOCK5), true,
                     new Bloc(getAssetsFileName(AssetsFiles::BLOCK5)));
    addElementToList(blockElements, getAssetsFileQString(AssetsFiles::BLOCK6), true,
                     new Bloc(getAssetsFileName(AssetsFiles::BLOCK6)));
    addElementToList(blockElements, getAssetsFileQString(AssetsFiles::BLOCK7), true,
                     new Bloc(getAssetsFileName(AssetsFiles::BLOCK7)));
    addElementToList(blockElements, getAssetsFileQString(AssetsFiles::BLOCK8), true,
                     new Bloc(getAssetsFileName(AssetsFiles::BLOCK8)));

    addElementToList(characterElements, getAssetsFileQString(AssetsFiles::PLAYER0), false,
                     new Player(getAssetsFileName(AssetsFiles::PLAYER0), "The Guy"));
    addElementToList(characterElements, getAssetsFileQString(AssetsFiles::PLAYER1), false,
                     new Player(getAssetsFileName(AssetsFiles::PLAYER1), "Little Child"));

    addElementToList(enemiesElements, getAssetsFileQString(AssetsFiles::ENEMY0), false,
                     new Ennemy(getAssetsFileName(AssetsFiles::ENEMY0), "Evil0"));
    addElementToList(enemiesElements, getAssetsFileQString(AssetsFiles::ENEMY1), false,
                     new Ennemy(getAssetsFileName(AssetsFiles::ENEMY1), "Evil1"));
    addElementToList(enemiesElements, getAssetsFileQString(AssetsFiles::ENEMY2), false,
                     new Ennemy(getAssetsFileName(AssetsFiles::ENEMY2), "Evil2"));
    addElementToList(enemiesElements, getAssetsFileQString(AssetsFiles::ENEMY3), false,
                     new Ennemy(getAssetsFileName(AssetsFiles::ENEMY3), "Evil3"));
    addElementToList(enemiesElements, getAssetsFileQString(AssetsFiles::ENEMY4), false,
                     new Ennemy(getAssetsFileName(AssetsFiles::ENEMY4), "Evil4"));
    addElementToList(enemiesElements, getAssetsFileQString(AssetsFiles::ENEMY5), false,
                     new Ennemy(getAssetsFileName(AssetsFiles::ENEMY5), "Evil5"));

    addElementToList(itemElements, getAssetsFileQString(AssetsFiles::ITEM_APPLE), false,
                     new Item(getAssetsFileName(AssetsFiles::ITEM_APPLE)));
    addElementToList(itemElements, getAssetsFileQString(AssetsFiles::ITEM_BOMB), false,
                     new Item(getAssetsFileName(AssetsFiles::ITEM_BOMB)));
    addElementToList(itemElements, getAssetsFileQString(AssetsFiles::ITEM_GEM), false,
                     new Item(getAssetsFileName(AssetsFiles::ITEM_GEM)));
    addElementToList(itemElements, getAssetsFileQString(AssetsFiles::ITEM_POT0), false,
                     new Item(getAssetsFileName(AssetsFiles::ITEM_POT0)));
    addElementToList(itemElements, getAssetsFileQString(AssetsFiles::ITEM_POT1), false,
                     new Item(getAssetsFileName(AssetsFiles::ITEM_POT1)));
    addElementToList(itemElements, getAssetsFileQString(AssetsFiles::ITEM_SWORD), false,
                     new Item(getAssetsFileName(AssetsFiles::ITEM_SWORD)));

    addElementToList(decorationElements, getAssetsFileQString(AssetsFiles::DECO0), false,
                     new Deco(getAssetsFileName(AssetsFiles::DECO0)));
    addElementToList(decorationElements, getAssetsFileQString(AssetsFiles::DECO2), false,
                     new Deco(getAssetsFileName(AssetsFiles::DECO2)));
    addElementToList(decorationElements, getAssetsFileQString(AssetsFiles::DECO4), false,
                     new Deco(getAssetsFileName(AssetsFiles::DECO4)));
}

/**
 * create a GameElement, connect it to the GameElementSelector to react when GameElement is clicked
 * add the GameElement to the Qlist
 *
 * @param listElement --> reference of the Qlist to fill with the GameElement
 * @param path --> path of the image used in the GameElement
 * @param display --> boolean to determinate if the GameElement is displayed or not
 */
void GameElementSelector::addElementToList(QList<GameElement *> &listElement, QString path, bool display, MapElement * element) {
    GameElement * elem = new GameElement(path, display, element);
    listElement.push_back(elem);
    GameElementSelector::connect(elem, &GameElement::onSpriteClicked, this, &GameElementSelector::spriteCreated);
}

/**
 * Organize the display of all elements
 * each menu is a QVBoxLayout which contains a button on top and a QGridLayout bellow
 * QGridLayouts contain Element of its corresponding QList
 * all menus are in a global QVBoxLayout
 */
void GameElementSelector::setUpDisplay() {
    vblocksButtonbox = new QVBoxLayout();
    vblocksButtonbox->addWidget(blocksButton, 0, Qt::AlignTop);
    blockElementsGridLayout = new QGridLayout();
    fillGridLayout(blockElementsGridLayout, blockElements);
    vblocksButtonbox->addLayout(blockElementsGridLayout);

    vcharactersButtonbox = new QVBoxLayout();
    vcharactersButtonbox->addWidget(charactersButton, 0, Qt::AlignTop);
    characterElementsGridLayout = new QGridLayout();
    fillGridLayout(characterElementsGridLayout, characterElements);
    vcharactersButtonbox->addLayout(characterElementsGridLayout);

    venemiesButtonbox = new QVBoxLayout();
    venemiesButtonbox->addWidget(enemiesButton, 0, Qt::AlignTop);
    enemiesElementsGridLayout = new QGridLayout();
    fillGridLayout(enemiesElementsGridLayout, enemiesElements);
    venemiesButtonbox->addLayout(enemiesElementsGridLayout);

    vitemsButtonbox = new QVBoxLayout();
    vitemsButtonbox->addWidget(itemsButton, 0, Qt::AlignTop);
    itemElementsGridLayout = new QGridLayout();
    fillGridLayout(itemElementsGridLayout, itemElements);
    vitemsButtonbox->addLayout(itemElementsGridLayout);

    vdecorationsButtonbox = new QVBoxLayout();
    vdecorationsButtonbox->addWidget(decorationsButton, 0, Qt::AlignTop);
    decorationElementsGridLayout = new QGridLayout();
    fillGridLayout(decorationElementsGridLayout, decorationElements);
    vdecorationsButtonbox->addLayout(decorationElementsGridLayout);

    vbox->addLayout(vblocksButtonbox, 0);
    vbox->addLayout(vcharactersButtonbox, 0);
    vbox->addLayout(venemiesButtonbox, 0);
    vbox->addLayout(vitemsButtonbox, 0);
    vbox->addLayout(vdecorationsButtonbox, 0);

}

/**
 * Put each GameElement in the QGridLayout elements by elements
 * it proceed row by row and put 4 elements max on a row
 * (firts element 0,0 ; second 0,1, etc.)
 *
 * @param layout --> pointer of the QGridLayout to fill
 * @param elements --> QList of the GameElements to put in the QGridLayout
 */
void GameElementSelector::fillGridLayout(QGridLayout * layout, QList<GameElement *> elements) {
    int i = 0, j = 0;
    for (GameElement * gameElement : elements) {
        layout->addWidget(gameElement, i, j, Qt::AlignCenter);
        j = ((j + 1) % 4);
        i += j == 0;
    }
    layout->setVerticalSpacing(15);
    layout->setHorizontalSpacing(20);
}

/**
 * disable the clicked button and display the Elements of the QGridLayout corresponding to the button
 *
 * @param button -> pointer of the button just clicked
 */
void GameElementSelector::changeDisplay(QPushButton * button){

    enableAllButtons();
    unDisplayAllElement();

    if (button == blocksButton) {
        for(GameElement * gameElement : blockElements) {
            gameElement->setDisplay(true);
        }
        blocksButton->setDisabled(true);
    } else if (button == charactersButton) {
        for(GameElement * gameElement : characterElements) {
            gameElement->setDisplay(true);
        }
        charactersButton->setDisabled(true);
    } else if (button == enemiesButton) {
        for(GameElement * gameElement : enemiesElements) {
            gameElement->setDisplay(true);
        }
        enemiesButton->setDisabled(true);
    } else if (button == itemsButton) {
        for(GameElement * gameElement : itemElements) {
            gameElement->setDisplay(true);
        }
        itemsButton->setDisabled(true);
    } else {
        for(GameElement * gameElement : decorationElements) {
            gameElement->setDisplay(true);
        }
        decorationsButton->setDisabled(true);
    }
}

/**
 * Enable all buttons
 */
void GameElementSelector::enableAllButtons() {
    blocksButton->setDisabled(false);
    charactersButton->setDisabled(false);
    enemiesButton->setDisabled(false);
    itemsButton->setDisabled(false);
    decorationsButton->setDisabled(false);
}

/**
 * undisplay all GameElements of all QGridLayout
 */
void GameElementSelector::unDisplayAllElement() {
    for(GameElement * gameElement : blockElements) {
        gameElement->setDisplay(false);
    }

    for(GameElement * gameElement : characterElements) {
        gameElement->setDisplay(false);
    }

    for(GameElement * gameElement : enemiesElements) {
        gameElement->setDisplay(false);
    }

    for(GameElement * gameElement : itemElements) {
        gameElement->setDisplay(false);
    }

    for(GameElement * gameElement : decorationElements) {
        gameElement->setDisplay(false);
    }
}

/**
 * react to the click on the button of block category
 * change display to show blocks
 */
void GameElementSelector::onBlocksButtonClicked(){
    changeDisplay(blocksButton);
}

/**
 * react to the click on the button of character category
 * change display to show characters
 */
void GameElementSelector::onCharactersButtonClicked(){
    changeDisplay(charactersButton);
}

/**
 * react to the click on the button of enemies category
 * change display to show enemies
 */
void GameElementSelector::onEnemiesButtonClicked(){
    changeDisplay(enemiesButton);
}

/**
 * react to the click on the button of item category
 * change display to show items
 */
void GameElementSelector::onItemsButtonClicked(){
    changeDisplay(itemsButton);
}

/**
 * react to the click on the button of decoration category
 * change display to show decorations
 */
void GameElementSelector::onDecorationButtonClicked(){
    changeDisplay(decorationsButton);
}

/**
 * signal that the GameElement has been clicked
 *
 * @param mapElement --> pointer of the mapElement of the GameElement that has been clicked
 * @param path --> path of the sprite that has been clicked
 */
void GameElementSelector::spriteCreated(MapElement * mapElement, QString path) {
    emit onSpriteCreate(mapElement, path);
}
