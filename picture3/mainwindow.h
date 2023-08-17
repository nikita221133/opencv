#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <opencv4/opencv2/opencv.hpp>
#include <QFileDialog>

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

    void on_rectangle_stateChanged(int arg1);

    void on_circle_stateChanged(int arg1);

    void on_line_stateChanged(int arg1);

    void on_elipse_stateChanged(int arg1);

    void on_fiiledPolygon_stateChanged(int arg1);

private:
    Ui::MainWindow *ui;
    cv::Mat img;
    cv::Mat img_prev;
    QImage image;
    QPixmap pixel;
};
#endif // MAINWINDOW_H
