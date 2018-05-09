#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGraphicsItem>
#include <QInputDialog>
#include <QDebug>
#include <QtMath>
#include <QPushButton>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->mainToolBar->hide();
    ui->menuBar->hide();
    ui->statusBar->hide();
    scene2D=new CustomGraphicsScene(this);
    scene3D=new CustomGraphicsScene(this);
    ui->graphicsView->setMouseTracking(true);
    ui->graphicsView3D->setMouseTracking(true);

    ui->graphicsView->setScene(scene2D);
    ui->graphicsView3D->setScene(scene3D);

    //int w=ui->graphicsView->width();
    //int h=ui->graphicsView->height();

    //scene2D->setscene2DRect(-w/2,h/2,w,-h);
    //scene2D->setscene2DRect(-w/2,h/2,w,-h);

    DrawAxis2D();
    DrawAxis3D();

    //ui->graphicsView->centerOn(ui->graphicsView->width()/2,ui->graphicsView->height()/2);


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::DrawAxis2D()
{
    int w=ui->graphicsView->width();
    int h=ui->graphicsView->height();

    QRectF rect=scene2D->sceneRect();
    rect.setCoords(-w/2,-h/2,w/2,h/2);
    scene2D->setSceneRect(rect);


    scene2D->addLine(-w/2,0,w/2,0,QPen(Qt::red)); //draw horizontal axis
    scene2D->addLine(0,-h/2,0,h/2,QPen(Qt::blue)); //draw vertical axis





}



void MainWindow::on_EnterValuesButton_clicked()
{
    bool ok=false;
    int count=QInputDialog::getInt(this,tr("Enter at least 2 points"),
                                tr("No. of points"),2,2,10,1,&ok);

    if(ok)
    {
        pl.clear();
        for(int i=1 ; i<=count ; i++)
        {

            float x=QInputDialog::getInt(this,QString("enter x%1").arg(i),
                                        QString("enter x%1").arg(i),-100000,0,10000,1);
            float y=QInputDialog::getInt(this,QString("enter y%1").arg(i),
                                        QString("enter y%1").arg(i),-100000,0,10000,1);
            pl.append(QPoint(x,y));
        }
        DrawFig2D();
    }
}
void MainWindow::on_MoveFigureButton_clicked()
{
    int offsetX=QInputDialog::getInt(this,QString("enter new x cordinate"),
                                QString("enter new x cordinate"),0,-10000,10000,1);
    int offsetY=QInputDialog::getInt(this,QString("enter new y cordinate"),
                                QString("enter new y cordinate"),0,-10000,10000,1);



     moveFig(offsetX,offsetY);

     DrawFig2D();
}



void MainWindow::on_QuickDesignButton_clicked()
{
    pl.clear();
    QPoint a(0,0);
    QPoint b(0,200);
    QPoint c(200,200);
    QPoint d(200,0);
    QPoint e(0,0);
    pl.append(a);
    pl.append(b);
    pl.append(c);
    pl.append(d);
    pl.append(e);
    qDebug()<<"Quick Design"<<pl;
    DrawFig2D();
}

void MainWindow::DrawFig2D()
{
    /*for(int i=0 ; i<=pl.count()-2 ; i++)
    {
        scene2D->addLine(QLine(pl.at(i),(pl.at(i+1))));
    }*/
    /*float w=ui->graphicsView->width()/2;
    float h=ui->graphicsView->height()/2;

    for(int i=0 ; i<pl.count()-1 ; i++)
    {
        float x1=pl.at(i).x()+w;
        float y1=-(pl.at(i).y())+h;
        float x2=pl.at(i+1).x()+w;
        float y2=-(pl.at(i+1).y())+h;
        scene2D->addLine(x1, y1, x2, y2);
    }*/

    for(int i=0 ; i<pl.count()-1 ; i++)
    {
        QPointF p1=pl.at(i);
        QPointF p2=pl.at(i+1);
        scene2D->addLine(p1.x(),-p1.y(),p2.x(),-p2.y());
    }

}

void MainWindow::Rotate2D(float angle)
{

    float Th = angle*M_PI/180;
    qDebug()<<"Th="<<Th;
    for (auto &p : pl)
    {
        float T=p.x();
        p.setX(p.x()*cos(Th) - p.y()*sin(Th));
        p.setY(p.y()*cos(Th) + T*sin(Th));

    }
    qDebug()<<"After 2D"<<pl;
    DrawFig2D();
}

void MainWindow::on_Rotate2DButton_clicked()
{
    float angle=QInputDialog::getDouble(this,QString("enter angle"),
                                QString("enter angle"),0,-360,360,1);
    Rotate2D(angle);
}

void MainWindow::on_clearButton_clicked()
{
    pl.clear();
    scene2D->clear();
    DrawAxis2D();
}

void MainWindow::resizeEvent(QResizeEvent * event)
{
    QMainWindow::resizeEvent(event);

    /*ui->graphicsView->setFixedWidth(event->size().height());

    if(ui->graphicsView->scene2D())
        ui->graphicsView->fitInView(ui->graphicsView->scene2D()->scene2DRect(), Qt::KeepAspectRatio);*/
}

void MainWindow::on_scaleButton_clicked()
{
    int scaleX=QInputDialog::getInt(this,QString("scale x"),
                                QString("scale x"),0,-10000,10000,1);
    int scaleY=QInputDialog::getInt(this,QString("scale y"),
                                QString("scale y"),0,-10000,10000,1);

    scaleFigure(scaleX, scaleY);
    DrawFig2D();
}

void MainWindow::scaleFigure(int &scaleX, int &scaleY)
{
    for (auto &p : pl)
    {
        p.setX(p.x()*scaleX);
        p.setY(p.y()*scaleY);
    }

     //DrawFig();
}

void MainWindow::on_shearButton_clicked()
{
    int shearX=QInputDialog::getInt(this,QString("shear x"),
                                QString("shear x"),0,-10000,10000,1);
    int shearY=QInputDialog::getInt(this,QString("shear y"),
                                QString("shear y"),0,-10000,10000,1);

    int xp=QInputDialog::getInt(this,QString("xp"),
                                QString("xp"),0,-10000,10000,1);
    int yp=QInputDialog::getInt(this,QString("yp"),
                                QString("yp"),0,-10000,10000,1);

    shearFigure(shearX,shearY,xp,yp);
}


void MainWindow::shearFigure(int &shearX, int &shearY, int &xp, int &yp)
{
    for (auto &p : pl)
    {
        float T=p.x();
        p.setX((p.x() + p.y() * shearX) + xp);
        p.setY((p.y() + T     * shearY) + yp);
    }
    DrawFig2D();
    qDebug()<<pl;
}



void MainWindow::on_mappingrButton_clicked()
{
    int wx1=QInputDialog::getInt(this,QString("enter wx1"),
                                QString("wx1"),0,-10000,10000,1);
    int wy1=QInputDialog::getInt(this,QString("enter wy1"),
                                QString("wy1"),0,-10000,10000,1);
    int wx2=QInputDialog::getInt(this,QString("enter wx2"),
                                QString("wx2"),0,-10000,10000,1);
    int wy2=QInputDialog::getInt(this,QString("enter wy2"),
                                QString("wy2"),0,-10000,10000,1);

    int vx1=QInputDialog::getInt(this,QString("enter vx1"),
                                QString("vx1"),0,-10000,10000,1);
    int vy1=QInputDialog::getInt(this,QString("enter vy1"),
                                QString("vy1"),0,-10000,10000,1);
    int vx2=QInputDialog::getInt(this,QString("enter vx2"),
                                QString("vx2"),0,-10000,10000,1);
    int vy2=QInputDialog::getInt(this,QString("enter vy2"),
                                QString("vy2"),0,-10000,10000,1);

    moveFig(-wx1,-wy1);
    mapFig(wx1,wy1,wx2,wy2,vx1,vy1,vx2,vy2);
    moveFig(vx1,vy1);
    DrawFig2D();

    qDebug()<<"mapping" << pl;

}

void MainWindow::mapFig(int wx1, int wy1, int wx2, int wy2, int vx1, int vy1, int vx2, int vy2)
{

    int sx= (vx2 - vx1) / (wx2 - wx1);
    int sy= (vy2 - vy1) / (wy2 - wy1);

    scaleFigure(sx,sy);
}

void MainWindow::moveFig(int offsetX, int offsetY)
{
    for (auto &p : pl)
    {
        p.setX(p.x()+offsetX);
        p.setY(p.y()+offsetY);
    }

}

void MainWindow::on_reflectButton_clicked() //isn't complete !
{
    int type=QInputDialog::getInt(this,QString("enter reflection Type"),
                                QString("[(0)X-Axis]        [(1)Y-Axis]       [(2)Original Point]      [(3)About Line Y=x]      [(4) About Line Y=-x]      [(5)About Arbitrary Line]      [(6)About Arbitrary Point]"),0,0,6,1);

    if (type==5)
    {
        int x1=QInputDialog::getInt(this,QString("enter x1"),
                                    QString("x1"),0,-10000,10000,1);
        int y1=QInputDialog::getInt(this,QString("enter y1"),
                                    QString("y1"),0,-10000,10000,1);
        int x2=QInputDialog::getInt(this,QString("enter x2"),
                                    QString("x2"),0,-10000,10000,1);
        int y2=QInputDialog::getInt(this,QString("enter y2"),
                                    QString("y2"),0,-10000,10000,1);
        int dx=x2-x1;
        int dy=y2-y1;
        float d= pow((pow(dx,2)+pow(dy,2)),0.5);

        moveFig(-x1,-y1);
    }
    else
        reflectFig(type);
    DrawFig2D();
}


void MainWindow::reflectFig(int type)
{
    if(type==0)
    {
        for (auto &p : pl)
        {
            p.setX(p.x());
            p.setY(-p.y());
        }
    }
    else if (type==1 || type==5)
    {
        for (auto &p : pl)
        {
            p.setX(-p.x());
            p.setY(p.y());
        }
    }

    else if (type==2 || type==6)
    {
        for (auto &p : pl)
        {
            p.setX(-p.x());
            p.setY(-p.y());
        }
    }
    else if (type==3)
    {
        for (auto &p : pl)
        {
            int t=p.x();
            p.setX(p.y());
            p.setY(t);
        }
    }

    else if (type==4)
    {
        for (auto &p : pl)
        {
            int t=p.x();
            p.setX(-p.y());
            p.setY(-t);
        }
    }

}

void MainWindow::on_QuickDesign2Button_clicked()
{
    pl.clear();
    QPoint a(0,0);
    QPoint b(0,200);
    QPoint c(200,200);
    QPoint d(0,0);
    //QPoint e(0,0);
    pl.append(a);
    pl.append(b);
    pl.append(c);
    pl.append(d);
    //pl.append(e);
    qDebug()<<"Quick Design2"<<pl;
    DrawFig2D();
}

/**********************************3D*******************************************************************************/
void MainWindow::on_QuickDesign3DButton_clicked()
{
    pl3D.clear();
    pl3D.append(QVector3D(0,0,0));
    pl3D.append(QVector3D(0,0,100));
    pl3D.append(QVector3D(0,100,100));
    pl3D.append(QVector3D(0,100,0));

    pl3D.append(QVector3D(100,100,0));
    pl3D.append(QVector3D(100,100,100));
    pl3D.append(QVector3D(0,100,100));
    pl3D.append(QVector3D(0,0,100));

    pl3D.append(QVector3D(100,0,100));
    pl3D.append(QVector3D(100,0,0));
    pl3D.append(QVector3D(100,100,0));
    pl3D.append(QVector3D(100,100,100));

    pl3D.append(QVector3D(100,0,100));
    pl3D.append(QVector3D(100,0,0));
    pl3D.append(QVector3D(0,0,0));
    pl3D.append(QVector3D(0,100,0));
    DrawFig3D();
}

void MainWindow::DrawAxis3D()
{
    //scene3D->setSceneRect(ui->graphicsView3D->rect());
    //ui->graphicsView3D->fitInView(ui->graphicsView3D->scene()->sceneRect(),Qt::KeepAspectRatio);

    int w=ui->graphicsView3D->width();
    int h=ui->graphicsView3D->height();

    QRectF rect=scene3D->sceneRect();
    rect.setCoords(-w/2,-h/2,w/2,h/2);
    scene3D->setSceneRect(rect);
    scene3D->addLine(0,-h/2,0,0,QPen(Qt::blue));
    scene3D->addLine(0,0,w/2,0,QPen(Qt::red));
    scene3D->addLine(0,0,-w/2,h/2,QPen(Qt::green)); //z-axis



}


void MainWindow::DrawFig3D()
{
    /*for(int i=0 ; i<=pl.count()-2 ; i++)
    {
        scene2D->addLine(QLine(pl.at(i),(pl.at(i+1))));
    }*/

    qDebug()<<"called";
    for(int i=0 ; i<pl3D.count()-1 ; i++)
    {
        QVector3D v1=pl3D.at(i);
        QVector3D v2=pl3D.at(i+1);
        //scene3D->addLine(v1.x()-v1.z()*0.7, v1.y()-v1.z()*0.7, v2.x()-v2.z()*0.7, v2.y()-v2.z()*0.7);
        scene3D->addLine((v1.x()-v1.z()*0.7), -(v1.y()-v1.z()*0.7), (v2.x()-v2.z()*0.7), -(v2.y()-v2.z()*0.7));
    }

}

void MainWindow::on_QuickDesign3D2Button_clicked()
{
    pl3D.clear();
    pl3D.append(QVector3D(0,0,0));
    pl3D.append(QVector3D(100,100,100));
    DrawFig3D();
}

void MainWindow::Rotate3D(float angle, int type)
{
    float T; //temp value
    float Th = angle*M_PI/180;
    if (type==1)
    {
        for (auto &p : pl3D)
        {
            T=p.x();
            p.setX(p.x()*cos(Th) - p.y()*sin(Th));
            p.setY(p.y()*cos(Th) + T*sin(Th));
            //p.z() stays the same
        }
    }
    else if (type==2)
    {
        for (auto &p : pl3D)
        {
            T=p.x();
            p.setX(p.x()*cos(Th) - p.z()*sin(Th));
            //p.y() stays the same
            p.setZ(p.z()*cos(Th) + T*sin(Th));
        }
    }
    else if (type==3)
    {
        for (auto &p : pl3D)
        {
            T=p.y();
            //p.x() stays the same
            p.setY(p.y()*cos(Th) - p.z()*sin(Th));
            p.setZ(p.z()*cos(Th) + T*sin(Th));
        }
    }
}

void MainWindow::scaleFigure3D(float &scaleX, float &scaleY, float scaleZ)
{
    for (auto &p : pl3D)
      {
          p.setX(p.x()*scaleX);
          p.setY(p.y()*scaleY);
          p.setZ(p.z()*scaleZ);
      }

}

void MainWindow::on_scale3DButton_clicked()
{
    float scaleX=QInputDialog::getDouble(this,QString("scale x"),
                                QString("scale x"),0,-10000,10000,1);
    float scaleY=QInputDialog::getDouble(this,QString("scale y"),
                                QString("scale y"),0,-10000,10000,1);
    float scaleZ=QInputDialog::getDouble(this,QString("scale Z"),
                                QString("scale Z"),0,-10000,10000,1);

    scaleFigure3D(scaleX, scaleY, scaleZ);
    DrawFig3D();

}

void MainWindow::on_clear3DButton_clicked()
{
    scene3D->clear();
    pl3D.clear();
    DrawAxis3D();
}

void MainWindow::moveFig3D(float offsetX, float offsetY, float offsetZ)
{
    for (auto &p : pl3D)
    {
        p.setX(p.x()+offsetX);
        p.setY(p.y()+offsetY);
        p.setZ(p.z()+offsetZ);
    }
}

void MainWindow::on_MoveFigure3DButton_clicked()
{
    float offsetX=QInputDialog::getDouble(this,QString("enter new x cordinate"),
                                QString("enter new x cordinate"),0,-10000,10000,1);
    float offsetY=QInputDialog::getDouble(this,QString("enter new y cordinate"),
                                QString("enter new y cordinate"),0,-10000,10000,1);
    float offsetZ=QInputDialog::getDouble(this,QString("enter new Z cordinate"),
                                QString("enter new Z cordinate"),0,-10000,10000,1);



     moveFig3D(offsetX,offsetY,offsetZ);
     DrawFig3D();
}

void MainWindow::on_Rotate3DButton_clicked()
{
    float angle=QInputDialog::getDouble(this,QString("enter angle"),
                                QString("enter angle"),0,-360,360,1);
    int type=QInputDialog::getInt(this,QString("rotation Type"),
                                QString("[1]->Rotation About z-Axis     [2]->Rotation About y-Axis   [3]->Rotation About x-Axis     [4]->Rotation About an Arbitrary Axis"),0,-360,360,1);

    Rotate3D(angle,type);
    scene3D->clear();
    DrawAxis3D();
    DrawFig3D();
}

void MainWindow::on_mirror3DButton_clicked()
{
    int type=QInputDialog::getInt(this,QString("enter Type"),
                                QString("[1]->In X-axis     [2]->In Y-axis     [3]->In Z-axis              [4]->In Plane XY     [5]->In Plane YZ     [6]->In Plane XZ     [7]->In Orginal Point"),1,1,7,1);
    mirrorFig3D(type);
    scene3D->clear();
    DrawAxis3D();
    DrawFig3D();
}

void MainWindow::mirrorFig3D(int type)
{
    if(type==1)
    {
        for (auto &p : pl3D)
          {
              //p.setX(p.x());
              p.setY(-p.y());
              p.setZ(-p.z());
          }
    }

    if(type==2)
    {
        for (auto &p : pl3D)
          {
              p.setX(-p.x());
              //p.setY(p.y());
              p.setZ(-p.z());
          }
    }

    if(type==3)
    {
        for (auto &p : pl3D)
          {
              p.setX(-p.x());
              p.setY(-p.y());
              //p.setZ(p.z());
          }
    }
    if(type==4)
    {
        for (auto &p : pl3D)
          {
              //p.setX(p.x());
              //p.setY(p.y());
              p.setZ(-p.z());
          }
    }
    if(type==5)
    {
        for (auto &p : pl3D)
          {
              p.setX(-p.x());
              //p.setY(p.y());
              //p.setZ(p.z());
          }
    }
    if(type==6)
    {
        for (auto &p : pl3D)
          {
              //p.setX(p.x());
              p.setY(-p.y());
              //p.setZ(p.z());
          }
    }
    if(type==7)
    {
        for (auto &p : pl3D)
          {
              p.setX(-p.x());
              p.setY(-p.y());
              p.setZ(-p.z());
          }
    }
}

void MainWindow::on_DrawCirclerButton_clicked()
{
    float radius=QInputDialog::getDouble(this,QString("radius"),
                                QString("enter radius"),1,1,10000,1);
    DrawCircle(radius);
}

void MainWindow::DrawCircle(float r)
{
    float x=-r;
    float y1;
    //float y2;
    float dt=1/r;
    while (x<=r)
    {
        y1=sqrt((pow(r,2)-pow(x,2)));

        scene2D->addLine(x,y1,x,y1);
        scene2D->addLine(x,-y1,x,-y1);
        //qDebug()<<"x"<<x;
        //qDebug()<<y1;
        //qDebug()<<y2;
        //scene2D->addEllipse(x,y1,2,2);
        //scene2D->addEllipse(x,y2,2,2);
        //scene2D->addLine(1,1,1,1);
        x+=dt;
    }
}
