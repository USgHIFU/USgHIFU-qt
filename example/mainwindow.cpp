#include "mainwindow.h"
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QDebug>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    m_plan = new ConsolePlan(this);

    m_labelAngle = new QLabel("angle: ",this);
    m_labelX = new QLabel("x: ",this);
    m_labelY = new QLabel("y: ",this);

    //  line edit
    m_angle = new QLineEdit(this);
    m_x = new QLineEdit(this);
    m_y = new QLineEdit(this);

    QHBoxLayout* editLayout = new QHBoxLayout;
    editLayout->addWidget(m_labelAngle);
    editLayout->addWidget(m_angle);
    editLayout->addWidget(m_labelX);
    editLayout->addWidget(m_x);
    editLayout->addWidget(m_labelY);
    editLayout->addWidget(m_y);

    //  action
    m_add = new QPushButton(this);
    m_add->setText("add plane");
    m_addSpot = new QPushButton(this);
    m_addSpot->setText("add spot");
    m_remove = new QPushButton(this);
    m_remove->setText("remove plane");
    m_removeSpot = new QPushButton(this);
    m_removeSpot->setText("remove spot");
    m_dispPlane = new QPushButton(this);
    m_dispPlane->setText("display plane");
    m_dispSpot = new QPushButton(this);
    m_dispSpot->setText("display spot");

    QHBoxLayout* btnLayout = new QHBoxLayout;
    btnLayout->addWidget(m_add);
    btnLayout->addWidget(m_addSpot);
    btnLayout->addWidget(m_remove);
    btnLayout->addWidget(m_removeSpot);
    btnLayout->addWidget(m_dispPlane);
    btnLayout->addWidget(m_dispSpot);

    //
    m_status = new QLabel(this);

    QVBoxLayout* layout = new QVBoxLayout;
    layout->addLayout(editLayout);
    layout->addLayout(btnLayout);
    layout->addWidget(m_status);

    QWidget* widget = new QWidget;
    widget->setLayout(layout);

    setCentralWidget(widget);

    connect(m_add,SIGNAL(clicked(bool)),SLOT(btnAdd_Click()));
    connect(m_addSpot,SIGNAL(clicked(bool)),SLOT(btnAddSpot_Click()));
    connect(m_remove,SIGNAL(clicked(bool)),SLOT(btnRemove_Click()));
    connect(m_removeSpot,SIGNAL(clicked(bool)),SLOT(btnRemoveSpot_Click()));
    connect(m_dispPlane,SIGNAL(clicked(bool)),SLOT(btnDispPlane_Click()));
    connect(m_dispSpot,SIGNAL(clicked(bool)),SLOT(btnDispSpot_Click()));
    connect(m_plan,SIGNAL(updatePlaneSpots(QHash<float,QList<Plane2DCoordinate> >)),
            SLOT(setPlaneSpots(QHash<float,QList<Plane2DCoordinate> >)));
    connect(m_plan,SIGNAL(updateSpots(QHash<float,QList<Spot3DCoordinate> >)),
            SLOT(setSpots(QHash<float,QList<Spot3DCoordinate> >)));
}

MainWindow::~MainWindow()
{

}

void MainWindow::btnAdd_Click()
{
    if (m_angle->text().isEmpty() ||
        m_x->text().isEmpty() ||
        m_y->text().isEmpty())
    {
        m_status->setText("Warning: not enough parameters");
        return;
    }

    float angle = m_angle->text().toFloat();
    Plane2DCoordinate coordinate = {m_x->text().toFloat(),m_y->text().toFloat()};

    QList<Plane2DCoordinate> planeCoordinate;
    planeCoordinate.append(coordinate);

    if (m_plan->addPlane(angle,planeCoordinate))
    {
        m_status->setText(QString("The plane is added.\nAngle: %1 X: %2 Y: %3").arg(m_angle->text())
                                                                               .arg(m_x->text())
                                                                               .arg(m_y->text()));
    }else
    {
        m_status->setText("The plane of such angle existed.");
    }


}

void MainWindow::btnRemove_Click()
{
    if (m_angle->text().isEmpty())
    {
        m_status->setText("No plane is removed.");
        return;
    }

    if (m_plan->removePlane(m_angle->text().toFloat()))
    {
        m_status->setText("The required plane is removed.");
    }else
    {
        m_status->setText("Warning: no plane is found.");
    }
}

void MainWindow::btnDispPlane_Click()
{
    m_plan->getPlaneSpots();

    QString str = "";
    QHash<float,QList<Plane2DCoordinate> >::iterator i;

    if (m_planeSpots.size())
    {
        for(i = m_planeSpots.begin();i != m_planeSpots.end(); i++)
        {
            for(int j=0;j<i.value().size();j++)
            {
                str += QString("plane: angle, %1, x, %2, y, %3\n").arg(i.key())
                                                                  .arg(i.value().at(j).x)
                                                                  .arg(i.value().at(j).y);
            }
        }
        m_status->setText(str);
    }else
    {
        m_status->setText("No plane existed.");
    }
}

void MainWindow::btnAddSpot_Click()
{
    if (m_angle->text().isEmpty() ||
        m_x->text().isEmpty() ||
        m_y->text().isEmpty())
    {
        m_status->setText("Warning: not enough parameters");
        return;
    }

    float angle = m_angle->text().toFloat();
    Plane2DCoordinate coordinate = {m_x->text().toFloat(),m_y->text().toFloat()};

    if (m_plan->addSpot(angle,coordinate))
    {
        m_status->setText(QString("The plane of angle: %1 is added.\n X: %2 Y: %3")
                          .arg(angle)
                          .arg(coordinate.x)
                          .arg(coordinate.y));
    }else
    {
        m_status->setText(QString("The plane of angle: %1 is not found.").arg(angle));
    }
}

void MainWindow::btnRemoveSpot_Click()
{
    if (m_angle->text().isEmpty() ||
        m_x->text().isEmpty() ||
        m_y->text().isEmpty())
    {
        m_status->setText("Warning: not enough parameters");
        return;
    }

    float angle = m_angle->text().toFloat();
    Plane2DCoordinate coordinate = {m_x->text().toFloat(),m_y->text().toFloat()};

    if (m_plan->removeSpot(angle,coordinate))
    {
        m_status->setText(QString("The plane of angle: %1 is removed.\n X: %2 Y: %3")
                          .arg(angle)
                          .arg(coordinate.x)
                          .arg(coordinate.y));
    }else
    {
        m_status->setText(QString("The plane of angle: %1 is not found.").arg(angle));
    }
}

void MainWindow::btnDispSpot_Click()
{
    m_plan->getSpots();

    if (m_spots.size())
    {
        QString str = "";
        QHash<float,QList<Spot3DCoordinate> >::iterator i;
        for (i = m_spots.begin();i != m_spots.end();i++)
        {
            for (int j = 0;j < i.value().size();j++)
            {
                str += QString("plane: angle, %1, x, %2, y, %3, z %4\n").arg(i.key())
                                                                        .arg(i.value().at(j).x)
                                                                        .arg(i.value().at(j).y)
                                                                        .arg(i.value().at(j).z);
            }
        }
        m_status->setText(str);
    }else
    {
        m_status->setText("No spot existed.");
    }
}

void MainWindow::setPlaneSpots(QHash<float, QList<Plane2DCoordinate> > planeSpots)
{
    m_planeSpots = planeSpots;
}

void MainWindow::setSpots(QHash<float, QList<Spot3DCoordinate> > spots)
{
    m_spots = spots;
}
