//
// Created by darklinkz42 on 19/01/2020.
//

#ifndef ZZMAKER_MAINWINDOW_HPP
#define ZZMAKER_MAINWINDOW_HPP

#include <QMainWindow>
#include <QApplication>
#include <QMenu>
#include <interface/otherWindows/helpWindow.hpp>
#include <interface/otherWindows/saveWindow.hpp>
#include <interface/otherWindows/openWindow.hpp>
#include <interface/otherWindows/newConfirmationWindow.hpp>
#include <interface/otherWindows/closeConfirmationWindow.hpp>
#include <interface/otherWindows/game_window/mainGameWindow.hpp>
#include <interface/otherWindows/errorWindow.hpp>
#include "editor.hpp"

/**
 * Main Window of the Application
 */
class MainWindow : public QMainWindow {

    Q_OBJECT

private:
    // Menus
    QMenu * file; //!< Pointer on the QMenu for file actions
    QMenu * edit; //!< Pointer on the QMenu for edit actions
    QMenu * view; //!< Pointer on the QMenu for view actions
    QMenu * help; //!< Pointer on the QMenu for help actions

    // all Actions
    QAction * newFile; //!< Pointer on a QAction which create a virgin Editor (not implemented)
    QAction * open; //!< Pointer on a QAction which open a zzm file (not implemented)
    QAction * save; //!< Pointer on a QAction which save the editor's state in the current zzm file (not implemented)
    QAction * saveFileAs; //!< Pointer on a QAction which define the path of the zzm file and save the editor's state (not implemented)
    QAction * quit; //!< Pointer on a QAction which check if state is save and quit the application (not fully implemented)

    QAction * cancel; //!< Pointer on a QAction which cancel le last action (not implemented)
    QAction * repeat; //!< Pointer on a QAction which repeat le last action (not implemented)
    QAction * copy; //!< Pointer on a QAction which copy a part of the grid (not implemented)
    QAction * cut; //!< Pointer on a QAction which cut a part of the grid (not implemented)
    QAction * paste; //!< Pointer on a QAction which past the copy or cut element into the grid (not implemented)

    QAction * showGrid; //!< Pointer on a QAction which show the grid or not

    QAction * showCommand; //!< Pointer on a QAction which display advice on how to use the application

    // Objects
    Editor * editor; //!< Pointer on the Editor which is the central widget of the application
    HelpWindow * helpWindow; //!< Pointer on a HelpWindow which is the window with all the information about the application
    SaveWindow * saveWindow;
    OpenWindow * openWindow;
    NewConfirmationWindow * newConfirmationWindow;
    CloseConfirmationWindow * closeConfirmationWindow;
    ErrorWindow * errorWindow;

    // project folder
    QString folderPath;

    // utils
    bool clearProject;
    bool quitProject;

    // game
    MainGameWindow mainGameWindow;

public:
    MainWindow(QWidget *parent = nullptr);

private:
    void buildHeaderFile(QMenu * menu, QString name);
    void initMenu(QMenu * menu, QString name);
    void initFichierMenu(QMenu * menu);
    void initEditionMenu(QMenu * menu);
    void initAffichageMenu(QMenu * menu);
    void initAideMenu(QMenu * menu);
    void initDefaultMenu(QMenu * menu);

private slots:
    void displayGrid();
    void displayAdvice();
    void openNewProjectConfirmator();
    void openCloseEditorConfirmator();
    void newProject();
    void saveAndClear();
    void saveFile();
    void saveAs();
    void openPathWindow();
    void setSavePath(QString path);
    void openProject(QString path);
    void saveAndQuit();
    void startGame(QMap<int, MapElement *>& elements);
    void displaySavingError(QString errorMessage);
    void displayOpeningError(QString errorMessage);
};

#endif //ZZMAKER_MAINWINDOW_HPP
