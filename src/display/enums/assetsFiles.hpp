//
// Created by darklinkz42 on 24/02/2020.
//

#ifndef ZZMAKER_ASSETSFILES_HPP
#define ZZMAKER_ASSETSFILES_HPP

#include <QString>

enum class AssetsFiles {
    BLOCK0,
    BLOCK1,
    BLOCK2,
    BLOCK3,
    BLOCK4,
    BLOCK5,
    BLOCK6,
    BLOCK7,
    BLOCK8,
    PLAYER0,
    PLAYER1,
    ENEMY0,
    ENEMY1,
    ENEMY2,
    ENEMY3,
    ENEMY4,
    ENEMY5,
    ITEM_APPLE,
    ITEM_BOMB,
    ITEM_GEM,
    ITEM_POT0,
    ITEM_POT1,
    ITEM_SWORD,
    DECO0,
    DECO2,
    DECO4
};


QString getAssetsFileQString(AssetsFiles asset);
std::string getAssetsFileName(AssetsFiles asset);

#endif //ZZMAKER_ASSETSFILES_HPP
