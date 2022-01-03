#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMouseEvent>
#include <QPainter>
#include <QPoint>
#include <QtMath>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QPoint curPos;
    QPoint firstPos;
    QPoint secondPos;
    bool checkPos;
    void mousePressEvent(QMouseEvent * );
    void mouseReleaseEvent(QMouseEvent * );
    void mouseMoveEvent(QMouseEvent * );
    void paintEvent(QPaintEvent *);
};

#endif // MAINWINDOW_H
