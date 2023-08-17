#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <string.h>
#include <opencv2/opencv.hpp>
#include <QTimer>

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
    void on_openFile_clicked();

    void update();

private:
    Ui::MainWindow *ui;
    cv::Mat img;
    QImage image;
    QPixmap pixel;
    cv::VideoCapture vc;
    QTimer* timer;
};
#endif // MAINWINDOW_H
