//
// Created by darklinkz42 on 24/02/2020.
//

#include "assetsFiles.hpp"

QString getAssetsFileQString(AssetsFiles asset) {
    QString assetFile = "";
    switch (asset) {
        case AssetsFiles::BLOCK0 :
            assetFile = "../assets/blocks/bloc0.png";
            break;
        case AssetsFiles::BLOCK1 :
            assetFile = "../assets/blocks/bloc1.png";
            break;
        case AssetsFiles::BLOCK2 :
            assetFile = "../assets/blocks/bloc2.png";
            break;
        case AssetsFiles::BLOCK3 :
            assetFile = "../assets/blocks/bloc3.png";
            break;
        case AssetsFiles::BLOCK4 :
            assetFile = "../assets/blocks/bloc4.png";
            break;
        case AssetsFiles::BLOCK5 :
            assetFile = "../assets/blocks/bloc5.png";
            break;
        case AssetsFiles::BLOCK6 :
            assetFile = "../assets/blocks/bloc6.png";
            break;
        case AssetsFiles::BLOCK7 :
            assetFile = "../assets/blocks/bloc7.png";
            break;
        case AssetsFiles::BLOCK8 :
            assetFile = "../assets/blocks/bloc8.png";
            break;

        case AssetsFiles::PLAYER0 :
            assetFile = "../assets/characters/player0.png";
            break;
        case AssetsFiles::PLAYER1 :
            assetFile = "../assets/characters/player1.png";
            break;

        case AssetsFiles::ENEMY0 :
            assetFile = "../assets/enemies/enemy0.png";
            break;
        case AssetsFiles::ENEMY1 :
            assetFile = "../assets/enemies/enemy1.png";
            break;
        case AssetsFiles::ENEMY2 :
            assetFile = "../assets/enemies/enemy2.png";
            break;
        case AssetsFiles::ENEMY3 :
            assetFile = "../assets/enemies/enemy3.png";
            break;
        case AssetsFiles::ENEMY4 :
            assetFile = "../assets/enemies/enemy4.png";
            break;
        case AssetsFiles::ENEMY5 :
            assetFile = "../assets/enemies/enemy5.png";
            break;

        case AssetsFiles::ITEM_APPLE :
            assetFile = "../assets/items/item_apple.png";
            break;
        case AssetsFiles::ITEM_BOMB :
            assetFile = "../assets/items/item_bomb.png";
            break;
        case AssetsFiles::ITEM_GEM :
            assetFile = "../assets/items/item_gem.png";
            break;
        case AssetsFiles::ITEM_POT0 :
            assetFile = "../assets/items/item_pot0.png";
            break;
        case AssetsFiles::ITEM_POT1 :
            assetFile = "../assets/items/item_pot1.png";
            break;
        case AssetsFiles::ITEM_SWORD :
            assetFile = "../assets/items/item_sword.png";
            break;

        case AssetsFiles::DECO0 :
            assetFile = "../assets/decorations/deco0.png";
            break;
        case AssetsFiles::DECO2 :
            assetFile = "../assets/decorations/deco2.png";
            break;
        case AssetsFiles::DECO4 :
            assetFile = "../assets/decorations/deco4.png";
            break;
    }
    return assetFile;
}


std::string getAssetsFileName(AssetsFiles asset) {
    return getAssetsFileQString(asset).toUtf8().constData();
}