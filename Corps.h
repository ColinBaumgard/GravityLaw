//
// Created by theti2o on 25/02/16.
//

#ifndef GRAVITYLAW_CORPS_H
#define GRAVITYLAW_CORPS_H

#include <stdlib.h>
#include <cmath>
#include <iostream>


class Corps
{
public:
    Corps();
    Corps(double x, double y);
    Corps(double x, double y, double vx, double vy);

    double getMasse();
    void setMasse(double masse);

    double getRayon();


    void getPosition(double& onX, double& onY);
    void setPosition(double onX, double onY);
    void addPosition(double onX, double onY);

    void getVitesse(double& onX, double& onY);
    void setVitesse(double onX, double onY);
    void addVitesse(double onX, double onY);

    void getAcceleration(double& onX, double& onY);
    void setAcceleration(double onX, double onY);



private:

    double m_masse;
    double m_rayon;
    void calculRayon();

    int m_couleur[3];

    double m_position[2];
    double m_vitesse[2];
    double m_acceleration[2];
};


#endif //GRAVITYLAW_CORPS_H
