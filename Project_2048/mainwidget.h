#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>

#include<QMessageBox>

#include<QGridLayout>
#include<QHBoxLayout>
#include<QVBoxLayout>

#include<QButtonGroup>
#include<QPushButton>

#include<QString>
#include<QStringList>
#include<QDebug>

#include<QTimer>

#include<QMouseEvent>
#include<QKeyEvent>
#include<QIcon>

class mainwidget : public QWidget
{

    Q_OBJECT
public:
    mainwidget(QWidget *parent = 0);
    ~mainwidget();
     void init_ok();
    void print();
    void newid();

    void up();
    void down();
    void right();
    void left();
public slots:
    void changeshapeSlots();
protected:
    void mouseMoveEvent(QMouseEvent *);
    void keyPressEvent(QKeyEvent *);
private:
    int map[6][6];               //ok
    int ts[2];
    QButtonGroup* btngroup;
    QPushButton* btn[36];                //

    QTimer* timer;
};

#endif // MAINWIDGET_H
