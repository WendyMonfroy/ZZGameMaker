//
// Created by darklinkz42 on 19/01/2020.
//

#include "mainWindow.hpp"
#include <QMenuBar>
#include <QStatusBar>
#include <enums/colors.hpp>
#include <iostream>
#include <QFileInfo>
#include <QDir>

/**
 * create the MainWindow
 * put the Editor at the center of the application and set its background
 * create all header menus (fichier, édition, etc.)
 *
 * @param parent --> pointer of the widget which contain the element
 */
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    setWindowTitle("ZZ Game Maker");

    setBackGround(Colors::DARK_GREY, this);

    buildHeaderFile(file, "Fichier");
    buildHeaderFile(edit, "Edition");
    buildHeaderFile(view, "Affichage");
    buildHeaderFile(help, "Aide");

    editor = new Editor(this);
    MainWindow::setCentralWidget(editor);
    helpWindow = new HelpWindow();
    saveWindow = new SaveWindow();
    openWindow = new OpenWindow();
    errorWindow = new ErrorWindow();
    newConfirmationWindow = new NewConfirmationWindow();
    closeConfirmationWindow = new CloseConfirmationWindow();
    clearProject = false;
    quitProject = false;

    connect(saveWindow, &SaveWindow::savePathEntered, this, &MainWindow::setSavePath);
    connect(openWindow, &OpenWindow::openPathEntered, this, &MainWindow::openProject);
    connect(newConfirmationWindow, &NewConfirmationWindow::clear, this, &MainWindow::newProject);
    connect(newConfirmationWindow, &NewConfirmationWindow::save, this, &MainWindow::saveAndClear);
    connect(editor, &Editor::saveError, this, &MainWindow::displaySavingError);
    connect(editor, &Editor::openError, this, &MainWindow::displayOpeningError);
    connect(closeConfirmationWindow, &CloseConfirmationWindow::closeProject, qApp, QApplication::quit);
    connect(closeConfirmationWindow, &CloseConfirmationWindow::save, this, &MainWindow::saveAndQuit);
    connect(editor, &Editor::gameStart, this, &MainWindow::startGame);

}

/**
 * create a QMenu with the good name
 *
 * @param menu --> Pointer on the QMenu to create
 * @param name --> Name of the QMenu to create
 */
void MainWindow::buildHeaderFile(QMenu * menu, QString name) {
    initMenu(menu, name);
}

/**
 * create the menu and check the name to add the right actions to it
 *
 * @param menu --> Pointer on the QMenu to create
 * @param name --> Name of the QMenu to create
 */
void MainWindow::initMenu(QMenu * menu, QString name) {

    menu = menuBar()->addMenu(name);

    if (QString::compare(name, "Fichier", Qt::CaseInsensitive) == 0) {
        initFichierMenu(menu);
    } else if (QString::compare(name, "Edition", Qt::CaseInsensitive) == 0) {
        initEditionMenu(menu);
    } else if (QString::compare(name, "Affichage", Qt::CaseInsensitive) == 0) {
        initAffichageMenu(menu);
    } else if (QString::compare(name, "Aide", Qt::CaseInsensitive) == 0) {
        initAideMenu(menu);
    } else {
        initDefaultMenu(menu);
    }
}

/**
 * fill menu with the QAction define bellow
 *
 * @param menu --> pointer on the QMenu to fill
 */
void MainWindow::initFichierMenu(QMenu * menu){

    newFile = new QAction("Nouveau", this);
    newFile->setShortcut(tr("CTRL+N"));
    menu->addAction(newFile);
    connect(newFile, &QAction::triggered, this, &MainWindow::openNewProjectConfirmator);

    open = new QAction("Ouvrir", this);
    open->setShortcut(tr("CTRL+O"));
    menu->addAction(open);
    connect(open, &QAction::triggered, this, &MainWindow::openPathWindow);

    menu->addSeparator();

    save = new QAction("Enregistrer", this);
    save->setShortcut(tr("CTRL+S"));
    menu->addAction(save);
    connect(save, &QAction::triggered, this, &MainWindow::saveFile);

    saveFileAs = new QAction("Enregistrer sous", this);
    saveFileAs->setShortcut(tr("CTRL+Shift+S"));
    menu->addAction(saveFileAs);
    connect(saveFileAs, &QAction::triggered, this, &MainWindow::saveAs);

    menu->addSeparator();

    quit = new QAction("Quitter", this);
    quit->setShortcut(tr("CTRL+Q"));
    menu->addAction(quit);
    connect(quit, &QAction::triggered, this, &MainWindow::openCloseEditorConfirmator);

}

/**
 * fill menu with the QAction define bellow
 *
 * @param menu --> pointer on the QMenu to fill
 */
void MainWindow::initEditionMenu(QMenu * menu){
    cancel = new QAction("Annuler", this);
    cancel->setShortcut(tr("CTRL+Z"));
    menu->addAction(cancel);

    repeat = new QAction("Répeter", this);
    repeat->setShortcut(tr("CTRL+Y"));
    menu->addAction(repeat);

    menu->addSeparator();

    copy = new QAction("Copier", this);
    copy->setShortcut(tr("CTRL+C"));
    menu->addAction(copy);

    cut = new QAction("Couper", this);
    cut->setShortcut(tr("CTRL+X"));
    menu->addAction(cut);

    paste = new QAction("Coller", this);
    paste->setShortcut(tr("CTRL+V"));
    menu->addAction(paste);
}

/**
 * fill menu with the QAction define bellow
 *
 * @param menu --> pointer on the QMenu to fill
 */
void MainWindow::initAffichageMenu(QMenu * menu){
    showGrid = new QAction("Afficher la grille", this);
    showGrid->setCheckable(true);
    showGrid->setShortcut(tr("G"));
    menu->addAction(showGrid);
    connect(showGrid, &QAction::triggered, this, &MainWindow::displayGrid);
}

/**
 * fill menu with the QAction define bellow
 *
 * @param menu --> pointer on the QMenu to fill
 */
void MainWindow::initAideMenu(QMenu * menu) {
    showCommand = new QAction("Commandes", this);
    showCommand->setShortcut(tr("CTRL+Shift+H"));
    menu->addAction(showCommand);
    connect(showCommand, &QAction::triggered, this, &MainWindow::displayAdvice);
}

/**
 * fill menu with the QAction define bellow
 *
 * @param menu --> pointer on the QMenu to fill
 */
void MainWindow::initDefaultMenu(QMenu * menu){

}

/**
 * Display the grid on the editor or not
 * Use the state of the "showGrid" action to decide
 */
void MainWindow::displayGrid() {
    editor->displayMapGrid(showGrid->isChecked());
}

/**
 * when "Aide" QAction is sellected, show the HelpWindow
 */
void MainWindow::displayAdvice() {
    helpWindow->show();
}

void MainWindow::openNewProjectConfirmator() {
    newConfirmationWindow->show();
}

void MainWindow::openCloseEditorConfirmator() {
    closeConfirmationWindow->show();
}

void MainWindow::newProject() {
    folderPath.clear();
    editor->clearProject();
}

void MainWindow::saveAndClear() {
    clearProject = true;
    saveFile();
}

void MainWindow::saveFile() {
    if (folderPath.size() == 0) {
        saveAs();
    } else {
        editor->saveStatus(folderPath);
        if (quitProject) qApp->quit();
        if (clearProject) newProject();
    }
}

void MainWindow::saveAs() {
    saveWindow->show();
}

void MainWindow::openPathWindow() {
    openWindow->show();
}

void MainWindow::setSavePath(QString path) {
    folderPath = path;
    saveFile();
}

void MainWindow::openProject(QString path) {
    QFileInfo dir(path);
    folderPath = dir.dir().absolutePath();
    editor->openStatus(path);
}

void MainWindow::saveAndQuit() {
    quitProject = true;
    saveFile();

}

void MainWindow::startGame(QMap<int, MapElement *>& elements) {
    mainGameWindow.run(elements.toStdMap());
}

void MainWindow::displaySavingError(QString errorMessage) {
    folderPath.clear();
    errorWindow->setName("Erreur de sauvegarde");
    errorWindow->setMessage(errorMessage);
    errorWindow->show();
}
void MainWindow::displayOpeningError(QString errorMessage) {
    folderPath.clear();
    errorWindow->setName("Erreur d'ouverture");
    errorWindow->setMessage(errorMessage);
    errorWindow->show();
}