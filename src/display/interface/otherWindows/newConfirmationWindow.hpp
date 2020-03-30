//
// Created by darklinkz42 on 20/02/2020.
//

#ifndef ZZMAKER_NEWCONFIRMATIONWINDOW_HPP
#define ZZMAKER_NEWCONFIRMATIONWINDOW_HPP

#include <QMainWindow>
#include <interface/otherWindows/component/confirmationPanel.hpp>

class NewConfirmationWindow : public QMainWindow {

Q_OBJECT

private:
    ConfirmationPanel * confirmationPanel;

public:
    NewConfirmationWindow(QWidget * parent = nullptr);

signals:
    void clear();
    void save();

private slots:
    void clearing();
    void canceling();
    void saving();

};

#endif //ZZMAKER_NEWCONFIRMATIONWINDOW_HPP
