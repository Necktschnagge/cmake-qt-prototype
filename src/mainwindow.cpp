#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    path = "";
    ui->setupUi(this);
    ui->statusbar->showMessage(tr("Ready ..."), WAIT_NORMAL);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btn_open_clicked()
{
    qInfo() << "OPEN: clicked";
    string text = ui->svgText->toPlainText().toStdString();

    bool progress = true;
    if (!text.empty()) {
        QMessageBox msgBox;
        msgBox.setText("There is an open SVG!");
        msgBox.setInformativeText("Do you want to save your changes?");
        msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Save);
        int ret = msgBox.exec();
        switch (ret) {
        case QMessageBox::Save:
            if (svg.save(path, text)) {
                ui->statusbar->showMessage(tr(MSG_SAVED), WAIT_LONG);
            } else {
                ui->statusbar->showMessage(tr(MSG_ERROR), WAIT_NORMAL);
            }
            break;
        case QMessageBox::Discard:
            // Proceed without saving.
            break;
        case QMessageBox::Cancel:
            // Cancel procedure.
        default:
            // Cancel procedure.
            progress = false;
            break;
        }
    }

    if (progress) {
        QString loc_path = QFileDialog::getOpenFileName(this, tr("Open"), QDir::homePath(), tr("Files (*.svg)"));
        if (svg.load(loc_path.toStdString())) {
            // SVG Text
            ui->svgText->setText(QString::fromStdString(svg.last()));
            this->path = loc_path.toStdString();
            // SVG Image
            refreshView();
        } else {
            ui->statusbar->showMessage(tr(MSG_ERROR), WAIT_NORMAL);
        }
    }
}

void MainWindow::on_btn_save_clicked()
{
    qInfo() << "SAVE: clicked";
    string text = ui->svgText->toPlainText().toStdString();

    if (text.empty()) {
        ui->statusbar->showMessage(tr(MSG_IGNORE), WAIT_NORMAL);
        return;
    }

    QString loc_path = QFileDialog::getSaveFileName(this, tr("Save"), QDir::homePath(), tr("Files (*.svg)"));
    if (svg.save(loc_path.toStdString(), text)) {
        ui->statusbar->showMessage(tr(MSG_SAVED), WAIT_LONG);
    }
}

void MainWindow::on_btn_undo_clicked()
{
    qInfo() << "UNDO: clicked";
    ui->svgText->setPlainText(QString::fromStdString(svg.undo()));
    refreshView();
}

void MainWindow::on_btn_redo_clicked()
{
    qInfo() << "REDO: clicked";
    ui->svgText->setPlainText(QString::fromStdString(svg.redo()));
    refreshView();
}

void MainWindow::on_btn_refresh_clicked()
{
    qInfo() << "REFRESH: clicked";
    string text = ui->svgText->toPlainText().toStdString();

    if (!text.empty()) {
        if (text.compare(svg.last()) != 0) {
            svg.update(text);
        }
        refreshView();
    } else {
        ui->statusbar->showMessage(tr(MSG_IGNORE), WAIT_NORMAL);
    }
}

void MainWindow::refreshView()
{
    const QString loc_data = ui->svgText->toPlainText();

    if (loc_data.isEmpty()) {
        ui->statusbar->showMessage(tr(MSG_IGNORE), WAIT_NORMAL);
    }

    try {
        QXmlStreamReader xml;
        xml.addData(loc_data);

        QSvgRenderer *svgRenderer = new QSvgRenderer(&xml);
        QGraphicsSvgItem *item = new QGraphicsSvgItem();
        QGraphicsScene *scene = new QGraphicsScene();

        item->setSharedRenderer(svgRenderer);
        scene->addItem(item);
        ui->graphicsView->setScene(scene);
        ui->graphicsView->fitInView(scene->sceneRect(), Qt::KeepAspectRatio);
        ui->graphicsView->show();

        string dimension = "Image: " + to_string((int)scene->height()) + " x " + to_string((int)scene->width());
        ui->statusbar->showMessage(tr(dimension.c_str()), WAIT_NORMAL);
    } catch (...) {
        ui->statusbar->showMessage(tr(MSG_ERROR), WAIT_NORMAL);
    }
}
