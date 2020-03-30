//
// Created by darklinkz42 on 19/02/2020.
//

#ifndef ZZMAKER_PATHSELECTOR_HPP
#define ZZMAKER_PATHSELECTOR_HPP

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QKeyEvent>

class PathSelector : public QWidget {

    Q_OBJECT

private:
    bool file;
    QLineEdit * pathEdit;

public:
    PathSelector(QString name, QString buttonName, bool file, QWidget * parent = nullptr);
    inline QString getPath() { return pathEdit->text(); }

private:
    void keyPressEvent(QKeyEvent * e) override;

signals:
    void pathEntered(QString path);

private slots:
    void save();
    void search();
};

#endif //ZZMAKER_PATHSELECTOR_HPP
