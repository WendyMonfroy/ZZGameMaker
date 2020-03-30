//
// Created by darklinkz42 on 23/02/2020.
//

#ifndef ZZMAKER_ERRORWINDOW_HPP
#define ZZMAKER_ERRORWINDOW_HPP

#include <QMainWindow>
#include <QLabel>

class ErrorWindow : public QMainWindow {

private:
    QLabel * label;

public:
    ErrorWindow(QWidget * parent = nullptr);
    inline void setName(QString name) { setWindowTitle(name); }
    inline void setMessage(QString errorMessage) { label->setText(errorMessage); }
};

#endif //ZZMAKER_ERRORWINDOW_HPP
