#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "svg_handler.h"

#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>
#include <QtDebug>
#include <QXmlStreamReader>
#include <QGraphicsSvgItem>
#include <QGraphicsView>
#include <QSvgRenderer>

#define WAIT_LONG    8000
#define WAIT_NORMAL  4000
#define MSG_SAVED    "File saved!"
#define MSG_ERROR    "There was something wrong! Nothing done!"
#define MSG_IGNORE   "There is nothing to do!"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btn_open_clicked();
    void on_btn_save_clicked();
    void on_btn_undo_clicked();
    void on_btn_redo_clicked();
    void on_btn_refresh_clicked();

private:
    Ui::MainWindow *ui;
    SvgHandler svg;
    string path;

    void refreshView();

};
#endif // MAINWINDOW_H
