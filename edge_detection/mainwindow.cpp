#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QFileDialog>
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


void MainWindow::on_open_clicked()
{
    cv::Mat det_img;
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Image"), "/desktop", tr("Image Files (*.png *.jpg *.bmp)"));

    std::vector<std::vector<cv::Point>> contours;
    std::vector<cv::Vec4i> hierarchy;
    std::vector<std::vector<cv::Point>> approx;

    img = cv::imread(fileName.toStdString());
    img.copyTo(det_img);

//    cv::blur(det_img, det_img,cv::Size(2,2));
    cv::cvtColor(det_img, det_img, cv::COLOR_BGR2GRAY);
//    cv::Canny(det_img, det_img, 50, 100);
    cv::threshold(det_img, det_img, 80, 150, 0);
    cv::findContours(det_img, contours, hierarchy, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE);
    double epsilon = 3;
    cv::Rect rect;
    cv::Point center;

    for (int i = 0; i < contours.size(); i++)
    {
        cv::drawContours(img, contours, i, {10, 200, 250}, 1, cv::LINE_8, hierarchy);
        rect = cv::boundingRect(contours[i]);
        center = cv::Point(rect.x + rect.width/2, rect.y + rect.height/2);
        approx.resize(contours.size());
        if (contours[i].size() != 0)
        {
            cv::approxPolyDP(contours[i], approx[i], epsilon, true);
            if (approx[i].size() != 0)
            {
                for (int j = 0; j < approx[i].size(); j++)
                {
                    cv::drawMarker(img, approx[i][j], {0, 0, 255});
                }
            }
            switch (approx[i].size()) {
            case 3:
                cv::putText(img, "Triangle", center, cv::FONT_HERSHEY_SIMPLEX, 1.0, {255, 255, 255});
                break;
            case 4:
                cv::putText(img, "Rectangle", center, cv::FONT_HERSHEY_SIMPLEX, 1.0, {255, 255, 255});
                break;
            case 5:
                cv::putText(img, "Pentagon", center, cv::FONT_HERSHEY_SIMPLEX, 1.0, {255, 255, 255});
                break;
            case 6:
                cv::putText(img, "Hexagon", center, cv::FONT_HERSHEY_SIMPLEX, 1.0, {255, 255, 255});
                break;
            default:
                cv::putText(img, "Circle", center, cv::FONT_HERSHEY_SIMPLEX, 1.0, {255, 255, 255});
                break;
            }
        }
    }
    image = QImage(img.data, img.cols, img.rows, QImage::Format_BGR888);
//    image = QImage(canny_img.data, canny_img.cols, det_img.rows, QImage::Format_Grayscale8);
    pixel = QPixmap::fromImage(image);
    ui->image->setPixmap(pixel);
}
