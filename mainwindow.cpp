#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setMouseTracking(true);
    checkPos = false;
    firstPos = cursor().pos();
    secondPos = cursor().pos();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::mousePressEvent(QMouseEvent * event){
    curPos = event->pos();
    ui->statusBar->showMessage(tr("(%1,%2)").arg(curPos.x()).arg(curPos.y()), 2000);
    if(!checkPos){
        firstPos = event->pos();
        checkPos = true;
    }
    else{
        secondPos = event->pos();
        checkPos = false;
    }
    repaint();
}
void MainWindow::mouseReleaseEvent(QMouseEvent * event){
    curPos = event->pos();
    ui->statusBar->showMessage(tr("(%1,%2)").arg(curPos.x()).arg(curPos.y()), 2000);
}

void MainWindow::mouseMoveEvent(QMouseEvent * event){
    curPos = event->pos();
    ui->statusBar->showMessage(tr("(%1,%2)").arg(curPos.x()).arg(curPos.y()), 2000);
}

void MainWindow::paintEvent(QPaintEvent * event){
    Q_UNUSED(event);
    QPainter painter(this);
    QPen pen(Qt::black, 3, Qt::SolidLine, Qt::FlatCap);
    painter.setPen(pen);
    if(checkPos){
        painter.drawPoint(firstPos);
        return;
    }
    if(sqrt(pow(firstPos.x(), 2) + pow(firstPos.y(), 2)) > sqrt(pow(secondPos.x(), 2) + pow(secondPos.y(), 2))){
        QPoint temp = firstPos;
        firstPos = secondPos;
        secondPos = temp;
    }

    if(ui->rbLine->isChecked()){
        double dx = abs(secondPos.x() - firstPos.x());
        double dy = abs(secondPos.y() - firstPos.y());

        int x = 0;
        int y = 0;

        if(dy < dx){
            int d = 2 * dy - dx;
            while(x < dx){
                x++;
                if(d >= 0){
                    y++;
                    d += 2 * (dy - dx);
                }
                else{
                    y=y;
                    d += 2 * dy;
                }
                if(secondPos.y() - firstPos.y() > 0 && secondPos.x() - firstPos.x() > 0)
                    painter.drawPoint(firstPos.x() + x, firstPos.y() + y);
                else if(secondPos.x() - firstPos.x() < 0 && secondPos.y() - firstPos.y() > 0)
                    painter.drawPoint(firstPos.x() - x, firstPos.y() + y);
                else if(secondPos.x() - firstPos.x() > 0 && secondPos.y() - firstPos.y() < 0)
                    painter.drawPoint(firstPos.x() + x, firstPos.y() - y);
                else
                    painter.drawPoint(firstPos.x() - x, firstPos.y() - y);
            }
        }
        else{
            int d = 2 * dx - dy;
            while(y < dy){
                y++;
                if(d >= 0){
                    x++;
                    d += 2 * (dx - dy);
                }
                else{
                    x=x;
                    d += 2 * dx;
                }
                if(secondPos.y() - firstPos.y() > 0 && secondPos.x() - firstPos.x() > 0)
                    painter.drawPoint(firstPos.x() + x, firstPos.y() + y);
                else if(secondPos.x() - firstPos.x() < 0 && secondPos.y() - firstPos.y() > 0)
                    painter.drawPoint(firstPos.x() - x, firstPos.y() + y);
                else if(secondPos.x() - firstPos.x() > 0 && secondPos.y() - firstPos.y() < 0)
                    painter.drawPoint(firstPos.x() + x, firstPos.y() - y);
                else
                    painter.drawPoint(firstPos.x() - x, firstPos.y() - y);
            }
        }
    }
    else{
        double r = sqrt(pow(secondPos.x() - firstPos.x(), 2) + pow(secondPos.y() - firstPos.y(), 2));

        int x = 0;
        int y = int(r) + 1;
        int d = int(double(3) - double(2) * r);
        do{
            painter.drawPoint(firstPos.x() + x, firstPos.y() + y);
            painter.drawPoint(firstPos.x() + x, firstPos.y() - y);
            painter.drawPoint(firstPos.x() - x, firstPos.y() + y);
            painter.drawPoint(firstPos.x() - x, firstPos.y() - y);

            if(d < 0){
                d += 4 * x + 6;
                y=y;

            }
            else{
                d += 4 * (x - y) + 10;
                y--;
            }
            x++;
        } while(x < int(r / sqrt(2)));
        do{
            painter.drawPoint(firstPos.x() + x, firstPos.y() + y);
            painter.drawPoint(firstPos.x() + x, firstPos.y() - y);
            painter.drawPoint(firstPos.x() - x, firstPos.y() + y);
            painter.drawPoint(firstPos.x() - x, firstPos.y() - y);

            if(d < 0){
                d += 4 * y + 6;
                x=x;
            }
            else{
                d += 4 * (y - x) + 10;
                x++;
            }
            y--;
        }while(y >= 0);
    }
}
