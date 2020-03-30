//
// Created by darklinkz42 on 20/02/2020.
//

#ifndef ZZMAKER_CLOSECONFIRMATIONWINDOW_HPP
#define ZZMAKER_CLOSECONFIRMATIONWINDOW_HPP

#include <QMainWindow>
#include <interface/otherWindows/component/confirmationPanel.hpp>

class CloseConfirmationWindow : public QMainWindow {

    Q_OBJECT

private:
    ConfirmationPanel * confirmationPanel;

public:
    CloseConfirmationWindow(QWidget * parent = nullptr);

    signals:
    void closeProject();
    void save();

private slots:
    void closing();
    void canceling();
    void saving();

};

#endif //ZZMAKER_CLOSECONFIRMATIONWINDOW_HPP
