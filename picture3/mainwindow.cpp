#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_openFile_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Image"), "/desktop", tr("Image Files (*.png *.jpg *.bmp)"));

    img = cv::imread(fileName.toStdString());
    image = QImage(img.data, img.cols, img.rows, QImage::Format_RGB888).rgbSwapped();
    pixel = QPixmap::fromImage(image);
    ui->image->setPixmap(pixel);
}


void MainWindow::on_rectangle_stateChanged(int arg1)
{
    if (arg1 != 0)
    {
        img.copyTo(img_prev);
        cv::rectangle(img, cv::Point(5.0, 5.0), cv::Point(50.0, 50.0), cv::Scalar(0, 255.0, 0), cv::LINE_4);
        image = QImage(img.data, img.cols, img.rows, QImage::Format_RGB888).rgbSwapped();
        pixel = QPixmap::fromImage(image);
        ui->image->setPixmap(pixel);
    }
     else
    {
        img_prev.copyTo(img);
        image = QImage(img.data, img.cols, img.rows, QImage::Format_RGB888).rgbSwapped();
        pixel = QPixmap::fromImage(image);
        ui->image->setPixmap(pixel);
    }
}


void MainWindow::on_circle_stateChanged(int arg1)
{
    if (arg1 != 0)
    {
        img.copyTo(img_prev);
        cv::circle(img, cv::Point(100.0, 100.0), 60, cv::Scalar(0, 0, 255.0), cv::LINE_4);
        image = QImage(img.data, img.cols, img.rows, QImage::Format_RGB888).rgbSwapped();
        pixel = QPixmap::fromImage(image);
        ui->image->setPixmap(pixel);
    }
     else
    {
        img_prev.copyTo(img);
        image = QImage(img.data, img.cols, img.rows, QImage::Format_RGB888).rgbSwapped();
        pixel = QPixmap::fromImage(image);
        ui->image->setPixmap(pixel);
    }
}


void MainWindow::on_line_stateChanged(int arg1)
{
    cv::line(img, cv::Point(200.0, 200.0),cv::Point(300.0, 300.0), cv::Scalar(255.0, 0.0, 255.0), cv::LINE_4);
    image = QImage(img.data, img.cols, img.rows, QImage::Format_RGB888).rgbSwapped();
    pixel = QPixmap::fromImage(image);
    ui->image->setPixmap(pixel);
}


void MainWindow::on_elipse_stateChanged(int arg1)
{
    cv::ellipse(img, cv::Point(300.0, 400.0),cv::Size(20,80), 0.0, 0.0, 360.0, cv::Scalar(255.0, 0, 128.0), cv::LINE_4);
    image = QImage(img.data, img.cols, img.rows, QImage::Format_RGB888).rgbSwapped();
    pixel = QPixmap::fromImage(image);
    ui->image->setPixmap(pixel);
}


void MainWindow::on_fiiledPolygon_stateChanged(int arg1)
{
    cv::Point pt[1][4];
    pt[0][0] = cv::Point(100.0, 30.0);
    pt[0][1] = cv::Point(140.0, 30.0);
    pt[0][2] = cv::Point(100.0, 80.0);
    pt[0][3] = cv::Point(140.0, 80.0);

    const cv::Point* ppt[1] = {pt[0]};

    int npt[]= {4};

    cv::fillPoly(img, ppt, npt, 1, cv::Scalar(255.0, 0, 128.0), cv::LINE_4);
    image = QImage(img.data, img.cols, img.rows, QImage::Format_RGB888).rgbSwapped();
    pixel = QPixmap::fromImage(image);
    ui->image->setPixmap(pixel);
}

