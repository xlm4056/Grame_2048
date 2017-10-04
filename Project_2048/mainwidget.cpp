#include "mainwidget.h"
#include<QTime>

int newt()
{
    qsrand(QTime::currentTime().msecsSinceStartOfDay());
    int x=qrand()%2;           //
    return x;
}

int newx()
{
    qsrand(QTime::currentTime().msecsSinceStartOfDay());
    int x=qrand()%36;           //
    return x;
}

mainwidget::mainwidget(QWidget *parent)
    : QWidget(parent)
{

    QGridLayout* grid=new   QGridLayout;
    grid->setSpacing(0);
    btngroup=new QButtonGroup;
    for(int i=0;i<36;i++)
    {
        btn[i]=new QPushButton("");
        btn[i]->setFixedSize(50,50);
        btn[i]->setStyleSheet("QPushButton{color:red}");

        btngroup->addButton(btn[i],i);
        grid->addWidget(btn[i],i/6,i%6);
    }
    this->setLayout(grid);

    for(int i=0;i<6;i++)
    {
        for(int j=0;j<6;j++)
        {
            map[i][j]=0;
        }
    }

    for(int i=0;i<6;i++)
    {
        map[0][i]=map[i][0]=map[5][i]=map[i][5]=1;
        btn[0*6+i]->setIcon(QIcon(":/images/smil1.gif"));
        btn[0*6+i]->setFlat(true);
        btn[i*6+0]->setIcon(QIcon(":/images/smil1.gif"));
        btn[i*6+0]->setFlat(true);
        btn[5*6+i]->setIcon(QIcon(":/images/smil1.gif"));
        btn[5*6+i]->setFlat(true);
        btn[i*6+5]->setIcon(QIcon(":/images/smil1.gif"));
         btn[i*6+5]->setFlat(true);
    }

    ts[0]=2;
    ts[1]=4;
//======================================



    int c1=newx();
    int c2=newx();
    while(c1==c2||c1/6==0||c1/6==5||c1%6==0||c1%6==5||c2/6==0||c2/6==5||c2%6==0||c2%6==5)
    {
        c1=newx();
        c2=newx();
    }

    /*
    while(c2==c1)
    {
        c2=newx();
    }
    qDebug()<<c2;
    */
    map[c1/6][c1%6]=ts[newt()];
    map[c2/6][c2%6]=ts[newt()];
    init_ok();
}

mainwidget::~mainwidget()
{}
//初始化函数
void mainwidget::init_ok()
{
    timer=new QTimer;
    timer->start(100);
    connect(timer,SIGNAL(timeout()),this,SLOT(changeshapeSlots()));
}
//刷新
void mainwidget::print()
{
    QString s;
    for(int i=1;i<5;i++)
    {
        for(int j=1;j<5;j++)
        {
            s=QString::number(map[i][j],10);
            qDebug()<<s;
            if(map[i][j]!=0)
            {
                btn[i*6+j]->setText(s);
            }
            else
            {
                btn[i*6+j]->setText("");
            }
        }
    }
}
//
void  mainwidget::newid()
{
    int a=0;
    for(int i=1;i<5;i++)
    {
        for(int j=1;j<5;j++)
        {
            if(map[i][j]==0)
            {
                a=1;
                break;
            }
        }
    }
    if(a==1)
    {
            int x=newx();
            while(map[x/6][x%6]!=0)
            {
                x=newx();
            }
            map[x/6][x%6]=ts[newt()];
    }
    else
    {}
//++++++++++++++++++++++++++++++++++

    int o=0;
    int k=0;
    for(int i=1;i<5;i++)
    {
        for(int j=1;j<5;j++)
        {
            if((map[i][j]!=map[i-1][j]&&map[i][j]!=map[i+1][j]&&map[i][j]!=map[i][j-1]&&map[i][j]!=map[i][j+1])\
                    &&(map[i-1][j]!=0&&map[i+1][j]!=0&&map[i][j-1]!=0&&map[i][j+1]!=0&&map[i][j]!=0))
            {}
            else
            {
                o=1;
            }

        }
    }
    if(o!=1)
    {
        QMessageBox msgBox;
        msgBox.setText("Grame Over!");
        msgBox.exec();
    }
}

void mainwidget::up()
{
    int b=0;
    for(int j=1;j<5;j++)
    {//
        for(int i=2;i<=4;i++)
        {
            bool r=false;
            if(map[i][j]!=0)
            {
                    for(int k=1;k<=(i-1);k++)
                    {
                                if(map[i-k][j]==0)
                                {
                                    map[i-k][j]=map[i-k+1][j];
                                    map[i-k+1][j]=0;
                                    b=1;
                                }

                                //
                                else if(r==false&&map[i-k][j]==map[i-k+1][j])
                                {
                                    map[i-k][j]=map[i-k+1][j]+map[i-k][j];
                                    map[i-k+1][j]=0;
                                    b=1;
                                    r=true;
                                }
                    }
            }
        }
     }
    if(b==1)
    {
         newid();
    }

}

void mainwidget::down()
{
    int b=0;
    for(int j=1;j<5;j++)
    {
        for(int i=3;i>=1;i--)             //
         {
            bool r=false;
            if(map[i][j]!=0)
            {
                    for(int k=1;k<=(4-i);k++)
                    {
                                if(map[i+k][j]==0)
                                {
                                    map[i+k][j]=map[i+k-1][j];
                                    map[i+k-1][j]=0;
                                    b=1;
                                }
                                else if(r==false&&map[i+k][j]==map[i+k-1][j])
                                {
                                    map[i+k][j]=map[i+k-1][j]+map[i+k][j];
                                    map[i+k-1][j]=0;
                                    b=1;
                                    r=true;
                                }
                    }
            }
        }
     }
    if(b==1)
    {
         newid();
    }

}

void mainwidget::right()
{
    int b=0;
    for(int i=1;i<5;i++)
    {
        for(int j=3;j>=1;j--)
        {
            bool r=false;
            if(map[i][j]!=0)
            {
                    for(int k=1;k<=(4-j);k++)
                    {
                                if(map[i][j+k]==0)
                                {
                                    map[i][j+k]=map[i][j+k-1];
                                    map[i][j+k-1]=0;
                                    b=1;
                                }
                                else if(r==false&&map[i][j+k]==map[i][j+k-1])
                                {
                                    map[i][j+k]=map[i][j+k-1]+map[i][j+k];
                                    map[i][j+k-1]=0;
                                    b=1;
                                    r=true;
                                }
                    }
            }
        }
     }
    if(b==1)
    {
         newid();
    }
}

void mainwidget::left()
{
    int b=0;
    for(int i=1;i<5;i++)
    {
        for(int j=2;j<=4;j++)
        {
            //
            bool r=false;                  //
            if(map[i][j]!=0)
            {
                    for(int k=1;k<=j-1;k++)
                    {
                                if(map[i][j-k]==0)
                                {
                                    map[i][j-k]=map[i][j-k+1];
                                    map[i][j-k+1]=0;
                                    b=1;
                                }
                                else if(r==false&&map[i][j-k]==map[i][j-k+1])
                                {
                                    map[i][j-k]=map[i][j-k+1]+map[i][j-k];
                                    map[i][j-k+1]=0;
                                    b=1
                                            ;
                                    r=true;
                                }
                    }
            }
        }
     }
    if(b==1)
    {
         newid();
    }
}

void mainwidget::changeshapeSlots()
{
    print();
}

void mainwidget::mouseMoveEvent(QMouseEvent *event)
{}

void mainwidget::keyPressEvent(QKeyEvent *event)
{
            if(event->key() ==Qt::Key_W){
               this->up();
            }
            else if(event->key()==Qt::Key_S)
            {
               this->down();
            }
            else if(event->key()==Qt::Key_A)
            {
                this->left();
            }
            else if(event->key()==Qt::Key_D)
            {
                this->right();
            }
            else
            {

            }
            this->update();
            QWidget::keyPressEvent(event);
}
