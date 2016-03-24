//
// Created by theti2o on 25/02/16.
//

#include "Corps.h"

using namespace std;

Corps::Corps()
{
    m_masse = 10;
    calculRayon();
    //m_masse = ((double)rand() / RAND_MAX)*pow(10, 5) + pow(10, 30);

    m_position[0] = ((double)rand() / RAND_MAX)*800;
    m_position[1] = ((double)rand() / RAND_MAX)*800;

    setVitesse(0, 0);
    setAcceleration(0, 0);

}
Corps::Corps(double x, double y)
{
    m_masse = 10;
    calculRayon();
    //m_masse = ((double)rand() / RAND_MAX)*pow(10, 5) + pow(10, 30);

    setPosition(x, y);
    setVitesse(0, 0);
    setAcceleration(0, 0);
}
Corps::Corps(double x, double y, double vx, double vy)
{
    m_masse = 10;
    calculRayon();
    //m_masse = ((double)rand() / RAND_MAX)*pow(10, 5) + pow(10, 30);

    setPosition(x, y);
    setVitesse(vx, vy);
    setAcceleration(0, 0);

}


double Corps::getMasse()
{
    return m_masse;
}
void Corps::setMasse(double masse)
{
    m_masse = masse;
    calculRayon();
}

double Corps::getRayon()
{
    return m_rayon;
}
void Corps::calculRayon()
{
    m_rayon = sqrt(m_masse/3.14);
}


void  Corps::getPosition(double& onX, double& onY)
{
    onX = m_position[0];
    onY = m_position[1];
}
void Corps::setPosition(double onX, double onY)
{
    m_position[0] = onX;
    m_position[1] = onY;
}
void Corps::addPosition(double onX, double onY)
{
    m_position[0] += onX;
    m_position[1] += onY;
}

void  Corps::getVitesse(double& onX, double& onY)
{
    onX = m_vitesse[0];
    onY = m_vitesse[1];
}
void Corps::setVitesse(double onX, double onY)
{
    m_vitesse[0] = onX;
    m_vitesse[1] = onY;
}
void Corps::addVitesse(double onX, double onY)
{
    m_vitesse[0] += onX;
    m_vitesse[1] += onY;
}

void  Corps::getAcceleration(double& onX, double& onY)
{
    onX = m_acceleration[0];
    onY = m_acceleration[1];
}
void Corps::setAcceleration(double onX, double onY)
{
    m_acceleration[0] = onX;
    m_acceleration[1] = onY;
}
