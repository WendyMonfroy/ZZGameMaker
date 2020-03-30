//
// Created by darklinkz42 on 03/02/2020.
//

#ifndef ZZMAKER_SPRITE_HPP
#define ZZMAKER_SPRITE_HPP

#include <QFrame>

class Sprite : public QFrame {

private:
    QString path; //!< path to the image of the Sprite
    QImage image; //!< image to display
    bool display; //!< boolean which indicate if the Sprite is visible or not

public:
    Sprite(QWidget * parent = nullptr);
    Sprite(QString path, bool display, QWidget * parent = nullptr);
    Sprite(unsigned int width, unsigned int height, QWidget * parent = nullptr);
    void paintEvent(QPaintEvent * e) override;
    /**
     * change the visibility of the Sprite and repaint it
     *
     * @param display --> new state of the Sprite
     */
    inline void setDisplay(bool display) { this->display = display; repaint(); }
    //! Gets the visibility of the Sprite
    inline bool getDisplay() { return display; }
    /**
     * Change the path to the image of the sprite and reload it
     *
     * @param path --> path to the image of the Sprite
     */
    inline void setPath(QString path) { this->path = path; image.load(path); setFixedSize(image.size()); }
    /**
     * Change the size of the Sprite
     *
     * @param width --> width of the Sprite
     * @param heigth --> heigth of the Sprite
     */
    inline void setSize(unsigned int width, unsigned int heigth) { this->setFixedSize(width, heigth); }
    //! Gets the path of the image of the Sprite
    inline QString getPath() { return path; }


private slots:
    void print(QPainter &qp);
};

#endif //ZZMAKER_SPRITE_HPP
