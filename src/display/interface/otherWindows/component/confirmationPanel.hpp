//
// Created by darklinkz42 on 20/02/2020.
//

#ifndef ZZMAKER_CONFIRMATIONPANEL_HPP
#define ZZMAKER_CONFIRMATIONPANEL_HPP

#include <QWidget>
#include <QLabel>

class ConfirmationPanel : public QWidget {

    Q_OBJECT

public:
    ConfirmationPanel(QString name, QString label, QWidget * parent = nullptr);

    signals:
    void validated();
    void canceled();
    void saved();

private slots:
    void yesClicked();
    void cancelClicked();
    void saveClicked();

};

#endif //ZZMAKER_CONFIRMATIONPANEL_HPP
