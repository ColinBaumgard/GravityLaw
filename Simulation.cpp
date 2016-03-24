//
// Created by theti2o on 25/02/16.
//

#include "Simulation.h"
#define PI 3.14159265359

using namespace std;
using namespace sf;


Simulation::Simulation()
{
    m_constanteG = 10000;
    m_scale = 1;
    m_centerOn[0] = 0;
    m_centerOn[1] = 0;

    //initialisation fenetre
    m_window.create(VideoMode(800, 800), "Newton's gravitational law");
    m_window.setPosition(Vector2i(200,100));
    m_window.setVerticalSyncEnabled(true);
    m_window.clear(Color::Black);

    //initialisation texte
    if(!m_font.loadFromFile("/home/theti2o/ClionProjects/GravityLaw/fichiers/fonts/FreeMono.ttf")) {}

    m_affichageAux = new Text;
    m_affichageAux->setFont(m_font);
    m_affichageAux->setColor(Color::White);
    m_affichageAux->setCharacterSize(15);


    Text text;
    text.setFont(m_font);
    text.setCharacterSize(15);
    text.setColor(Color::White);
    text.setString("Coucou");


    m_window.display();



}

void Simulation::start()
{



    do
    {

        events();

        simuler();

        afficher();

        //testons();


    }while(m_window.isOpen());


}


void Simulation::events()
{
    Event event;
    while(m_window.pollEvent(event))
    {

        switch (event.type)
        {
            case Event::Closed:
                m_window.close();
                break;
            case Event::MouseButtonReleased:
                if(event.mouseButton.button == Mouse::Left)
                {
                    Vector2u sizeWindow = m_window.getSize();
                    Vector2i mousePosition = Mouse::getPosition(m_window);
                    addCorps((mousePosition.x - m_centerOn[0])*m_scale, (mousePosition.y - m_centerOn[1])*m_scale);
                }
                break;
            case Event::KeyPressed:
                switch (event.key.code)
                {
                    case Keyboard::Left:
                        m_centerOn[0] += 2;
                        break;
                    case Keyboard::Right:
                        m_centerOn[0] += -2;
                        break;
                    case Keyboard::Up:
                        m_centerOn[1] += 2;
                        break;
                    case Keyboard::Down:
                        m_centerOn[1] += -2;
                        break;
                    default:
                        break;
                }
                break;
            case Event::MouseWheelMoved:
                if(m_scale <= 0.2 && event.mouseWheel.delta < 0)
                {
                    break;
                }
                else
                {
                    m_scale += event.mouseWheel.delta*0.1;
                }
                break;

            default:
                break;
        }
    }
}

void Simulation::simuler()
{
    int nbCorps = (int)m_galaxie.size();
    bool stop(false);

    for(int a(0); a < nbCorps && !stop ; a++)
    {
        m_mA = m_galaxie[a].getMasse();
        m_rA = m_galaxie[a].getRayon();
        m_galaxie[a].getPosition(m_xA, m_yA);
        m_galaxie[a].getVitesse(m_vxA, m_vyA);
        m_axA = 0;
        m_ayA = 0;

        for(int b(0); b < nbCorps && !stop; b++)
        {
            if(a != b)
            {
                m_mB = m_galaxie[b].getMasse();
                m_rB = m_galaxie[b].getRayon();
                m_galaxie[b].getPosition(m_xB, m_yB);

                m_distanceAB2 = pow((m_xA - m_xB), 2) + pow((m_yA - m_yB), 2);
                double distanceAB = sqrt(m_distanceAB2);

                if(distanceAB < (m_rA + m_rB))
                {
                    fusionAB(a, b);
                    simuler();
                    stop = true;
                }
                else
                {
                    actionBonA(a, b);
                    /*double newX, newY;
                    newX = 0.3 * m_mB / m_distanceAB2 *  (m_xB - m_xA)/distanceAB;
                    newY = 0.3 * m_mB / m_distanceAB2 *  (m_yB - m_yA)/distanceAB;

                    m_galaxie[a].addVitesse(newX, newY);

                    double vx, vy;
                    m_galaxie[a].getVitesse(vx, vy);
                    m_galaxie[a].addPosition(vx, vy);*/
                }

            }

        }
        m_galaxie[a].setAcceleration(m_axA, m_ayA);

        double ax(0), ay(0);
        m_galaxie[0].getAcceleration(ax, ay);

    }



    action();

}

void Simulation::afficher()
{

    int tailleTableaux = m_galaxie.size();


    //données:
    CircleShape cercle[tailleTableaux];
    RectangleShape vectorX[tailleTableaux];
    RectangleShape vectorY[tailleTableaux];

    double x(0), y(0), rayon(0), ax(0), ay(0);
    int color[3];

    double top = m_chrono.getElapsedTime().asSeconds();
    m_chrono.restart();

    m_window.clear(Color::Black);
    Vector2u sizeWindow = m_window.getSize();

    for(int i(0); i < m_galaxie.size() ; i++)
    {

        //récupération données
        m_galaxie[i].getPosition(x, y);
        rayon = m_galaxie[i].getRayon();

        m_galaxie[i].getAcceleration(ax, ay);

        //mise à l'echelle des données !
        rayon = rayon/m_scale;
        x = x/m_scale +m_centerOn[0];
        y = y/m_scale +m_centerOn[1];


        //implémentation fenetre
        cercle[i].setPosition((int)(x-rayon), (int)(y-rayon));
        cercle[i].setRadius(rayon);
        cercle[i].setFillColor(Color::White);

        vectorX[i].setSize(Vector2f(ax, 1));
        vectorX[i].setPosition(x, y);
        vectorX[i].setFillColor(Color::Green);

        vectorY[i].setSize(Vector2f(1, ay));
        vectorY[i].setPosition(x, y);
        vectorY[i].setFillColor(Color::Green);

        //dessin
        m_window.draw(vectorX[i]);
        m_window.draw(vectorY[i]);
        m_window.draw(cercle[i]);

    }


    m_affichageAux->setString("FPS: " + to_string(1/top) + "/Scale: " + to_string(m_scale) + "Center: " + to_string(m_centerOn[0]));
    m_window.draw(*m_affichageAux);

    m_window.display();

}

void Simulation::testons()
{
    Event event;
    while(m_window.pollEvent(event))
    {
        if(event.type == Event::Closed)
            m_window.close();

        if(event.type == Event::MouseButtonReleased)//Si on clique, on ajoute un corps
        {
            if(event.mouseButton.button == Mouse::Left)
            {
                Vector2i mousePosition = Mouse::getPosition(m_window);

                m_test.setPosition(mousePosition.x, mousePosition.y);

            }
        }
    }

    //données:
    CircleShape cercle;
    CircleShape base;

    base.setPosition(390, 390);
    base.setRadius(10);
    base.setFillColor(Color::Red);



    double x(0), y(0), rayon(5);
    //int color[3];

    m_test.getPosition(x, y);

    m_window.clear(Color::Black);

    cercle.setPosition((int)x-rayon, (int)y-rayon);
    cercle.setRadius(rayon);
    cercle.setFillColor(Color::White);






    double yb(400), xb(400);


    double coefdir = (yb - y) / (xb - x);
    double angle = atan(coefdir);
    if(x>xb)
    {
        angle = (angle+3.14);
        while(angle > 2*3.14)
        {
            angle -= 2*3.14;
        }
    }
    double angleD = angle*(360/(2*3.14));



    RectangleShape vectorA;
    vectorA.setSize(Vector2f(50, 1));
    vectorA.setPosition(x, y);
    vectorA.setRotation(angleD);

    RectangleShape vectorX;
    vectorX.setSize(Vector2f(50*cos(angle), 1));
    vectorX.setPosition(x, y);
    vectorX.setFillColor(Color::Green);

    RectangleShape vectorY;
    vectorY.setSize(Vector2f(1, 50*sin(angle)));
    vectorY.setPosition(x, y);
    vectorY.setFillColor(Color::Green);


    m_window.draw(base);
    m_window.draw(cercle);
    m_window.draw(vectorA);
    m_window.draw(vectorX);
    m_window.draw(vectorY);



    m_affichageAux->setString("Angle: " + to_string(angleD));
    m_window.draw(*m_affichageAux);

    m_window.display();
}


//simulation pur:
void Simulation::actionBonA(int a, int b)
{
    double g = (m_constanteG*m_mB) / m_distanceAB2;

    //sur x:
    double coefdir = (m_yB - m_yA) / (m_xB - m_xA);
    double angle = atan(coefdir);
    if(m_xA>m_xB)
    {
        angle = (angle+PI);
        while(angle > 2*PI)
        {
            angle -= 2*PI;
        }
    }
    double angleD = angle*(360/(2*PI));

    m_axA += g*cos(angle);
    m_ayA += g*sin(angle);


}




void Simulation::action()
{
    double temps(0.01);
    double temps2(pow(temps, 2));

    double x, y, vx, vy, ax, ay;
    double new_x, new_y, new_vx, new_vy, new_ax, new_ay;



    for(int A(0); A < m_galaxie.size(); A++)
    {

        //récupration données
        m_galaxie[A].getPosition(x,y);
        m_galaxie[A].getVitesse(vx, vy);
        m_galaxie[A].getAcceleration(ax, ay);

        //manipulation
        new_x = (1/2)*ax*temps2 + vx*temps + x;
        new_y = (1/2)*ay*temps2 + vy*temps + y;

        new_vx = ax*temps + vx;
        new_vy = ay*temps + vy;

        //envoie données
        m_galaxie[A].setPosition(new_x, new_y);
        m_galaxie[A].setVitesse(new_vx, new_vy);

    }

}
void Simulation::fusionAB(int a, int b)
{
    double mA = m_galaxie[a].getMasse();
    double mB = m_galaxie[b].getMasse();

    double vxA, vxB, vyA, vyB;
    m_galaxie[a].getVitesse(vxA, vyA);
    m_galaxie[b].getVitesse(vxB, vyB);



    if(mA > mB)
    {
        double rapportDeMasse = (mB/mA);

        m_galaxie[a].setMasse(mA + mB);
        m_galaxie[a].setVitesse((vxB*rapportDeMasse)+vxA, (vyB*rapportDeMasse)+vyA);

        m_galaxie.erase(m_galaxie.begin()+b);

    }
    else
    {
        double rapportDeMasse = (mA/mB);

        m_galaxie[b].setMasse(mA + mB);
        m_galaxie[b].setVitesse((vxA*rapportDeMasse)+vxB, (vyA*rapportDeMasse)+vyB);

        m_galaxie.erase(m_galaxie.begin()+a);

    }
}



void Simulation::addCorps(double x, double y)
{
    Corps newCorps(x, y);
    m_galaxie.push_back(newCorps);

}