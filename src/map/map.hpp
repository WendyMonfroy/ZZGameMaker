#ifndef __MAP_HPP__
#define __MAP_HPP__

#include <vector>
#include <map>
#include <QWidget>
#include <QGridLayout>
#include <queue>
#include <iostream>
#include <components/graphic/caseStock.hpp>
#include "map/components/physic/map_element.hpp"
#include "map/components/graphic/case.hpp"
#include "type.hpp"

class Map : public QWidget {

    Q_OBJECT

    using Elements = QMap<int, MapElement *>;
    typedef QVector<QVector<Case *>> Grid;

private:
    Grid grid; //!< Arrays of all Cases
    Elements elements; //!< Map of all elements with physic existence in the game
    QMap<QPoint, CaseStock> activeCases; //!< Map of all case with an element
    QGridLayout * gridLayout; //!< layout to organize the Case
    bool display; //!< boolean which indicate if the grid has to be display or not
    std::queue<unsigned int> availableID; //!< stack of all ID that has been remove and not reattributed yet
    QPoint currentCase;
    bool paint;
    Qt::MouseButton buttonClicked;
    int xVariation, yVariation;

public:
    Map(QWidget * parent = nullptr);
    void createMap();
    void displayGrid(bool display);
    void registerElement(MapElement * mapElement, Case * _case);
    void deleteElement(unsigned int const id, QPoint point);
    void serialize(QString path);
    void deserialize(QString path);
    void clearMap();
    inline QMap<int, MapElement *>& getMapElements() { return elements; }
    inline bool getPaint() { return paint; }
    inline void setPaint(bool paint) { this->paint = paint; }
    inline void setMouseButton(Qt::MouseButton &&buttonClicked) { this->buttonClicked = buttonClicked; }
    void moveRight();
    void moveDown();
    void moveLeft();
    void moveUp();
    inline int getAvailableID() {
        int id;
        if (availableID.empty()) {
            id = elements.size() + 1;
        } else {
            id = availableID.front();
            availableID.pop();
        }
        return id;
    }

private:
    bool event(QEvent *e) override;
    void filterEvent(QEvent * e);
   // bool isInGrid(QPoint mousePosition);
    void callCase(bool paintActive);
    void mousePressEvent(QMouseEvent * e) override;
    // void mouseReleaseEvent(QMouseEvent * e) override;
    void mouseDoubleClickEvent(QMouseEvent * e) override;
    void setDisplay();
    void paintGrid();
    void moveMap(int &&xvariation, int &&yvariation);
    Grid createCopy();
    void restoreMapFromCopy(Grid &copy);
    void deleteCopy(Grid &copy);
    
    signals:
    /**
     * signal the Case that has been clicked
     *
     * @param _case --> pointer on the Case that has been clicked
     */
    void caseClicked(Case * _case);
    /**
     * signal that an element has to be move
     *
     * @param mapElement --> pointer on the mapElement to move
     * @param path --> path of the image associated to the sprite to display and the image of the mapElement
     */
    void spriteMoved(MapElement * mapElement, QString path, QPoint point);
    void serializationError(QString errorMessage);
    void deserializationError(QString errorMessage);

public slots:
    void dropSprite(Case * _case);
    void moveSprite(MapElement * mapElement, QString path, QPoint point);
    void eraseElement(unsigned int const id, QPoint point);
    void getCase(int &x, int &y);
};


bool operator<(QPoint const & first, QPoint const & second);

#endif
