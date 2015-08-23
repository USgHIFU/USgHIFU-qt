#ifndef MAINWINDOW_H
#define MAINWINDOW_H

class QLineEdit;
class QPushButton;
class QLabel;

#include <QMainWindow>
#include "consoleplan.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void btnAdd_Click();
    void btnAddSpot_Click();
    void btnRemove_Click();
    void btnRemoveSpot_Click();
    void btnDispPlane_Click();
    void btnDispSpot_Click();
    void setPlaneSpots(QHash<float,QList<Plane2DCoordinate> >);
    void setSpots(QHash<float,QList<Spot3DCoordinate> >);

private:
    ConsolePlan* m_plan;
    QHash<float,QList<Plane2DCoordinate> > m_planeSpots;
    QHash<float,QList<Spot3DCoordinate> > m_spots;

    QLabel *m_labelAngle, *m_labelX, *m_labelY;
    QLineEdit* m_angle;
    QLineEdit* m_x;
    QLineEdit* m_y;
    QPushButton* m_add;
    QPushButton* m_addSpot;
    QPushButton* m_remove;
    QPushButton* m_removeSpot;
    QPushButton* m_dispPlane;
    QPushButton* m_dispSpot;
    QLabel* m_status;
};

#endif // MAINWINDOW_H
