#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QResizeEvent>
#include <customgraphicsscene.h>
#include <QVector3D>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    CustomGraphicsScene *scene2D;
    CustomGraphicsScene *scene3D;
    void DrawAxis2D();
    void DrawAxis3D();
    QList<QPointF> pl;
    QList<QVector3D> pl3D;
    void DrawFig2D();
    void DrawFig3D();
    void Rotate2D(float angle);
    void Rotate3D(float angle, int type);
    void resizeEvent(QResizeEvent * event);

    void mapFig(int wx1, int wy1, int wx2, int wy2,int vx1, int vy1, int vx2, int vy2);

private slots:
    void on_EnterValuesButton_clicked();

    void on_MoveFigureButton_clicked();


    void on_QuickDesignButton_clicked();

    void on_Rotate2DButton_clicked();

    void on_clearButton_clicked();

    void on_scaleButton_clicked();

    void scaleFigure(int &scaleX, int &scaleY);
    void scaleFigure3D(float &scaleX, float &scaleY, float scaleZ);
    void mirrorFig3D(int type);

    void on_shearButton_clicked();

    void shearFigure(int &shearX, int &shearY, int &xp, int &yp);



    void on_mappingrButton_clicked();

    void moveFig(int offsetX, int offsetY);
    void moveFig3D(float offsetX, float offsetY, float offsetZ);

    void on_reflectButton_clicked();

    void reflectFig(int type);

    void on_QuickDesign2Button_clicked();

    void on_QuickDesign3DButton_clicked();

    void on_QuickDesign3D2Button_clicked();

    void on_scale3DButton_clicked();

    void on_clear3DButton_clicked();

    void on_MoveFigure3DButton_clicked();

    void on_Rotate3DButton_clicked();

    void on_mirror3DButton_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
