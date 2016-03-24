//
// Created by theti2o on 25/02/16.
//

#ifndef GRAVITYLAW_SIMULATION_H
#define GRAVITYLAW_SIMULATION_H

#include <iostream>
#include <time.h>
#include <SFML/Graphics.hpp>
#include <vector>

#include "Corps.h"





class Simulation
{
public:
    Simulation();

    void start();

private:

    std::vector<Corps> m_galaxie;
    double m_constanteG;

    //fenetre
    sf::RenderWindow m_window;
    sf::Text *m_affichageAux;
    sf::Clock m_chrono;
    sf::Font m_font;
    void events();
    void simuler();
    void afficher();
    void testons();

    //test
    Corps m_test;

    //simulation
    double m_mA, m_rA, m_xA, m_yA, m_vxA, m_vyA, m_axA, m_ayA;
    double m_mB, m_rB, m_xB, m_yB, m_vxB, m_vyB, m_axB, m_ayB;
    double m_distanceAB2;
    void actionBonA(int a, int b);
    void fusionAB(int a, int b);
    void action();


    //autre
    void addCorps(double x, double y);

};


#endif //GRAVITYLAW_SIMULATION_H
