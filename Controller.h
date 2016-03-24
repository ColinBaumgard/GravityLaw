//
// Created by theti2o on 28/02/16.
//

#ifndef GRAVITYLAW_CONTROLLER_H
#define GRAVITYLAW_CONTROLLER_H

#include <iostream>
#include <string>
#include <thread>
#include <gtkmm.h>
#include <GL/gl.h>
#include <gtkglmm.h>
#include <stdlib.h>
#include <vector>

#include "Simulation.h"


class Controller {
public:
    Controller(int argc, char **argv);

    static void newSimulation_callback(GtkButton *widget, Controller* data);
    void newSimulation(GtkButton *button);



    void start();

private:
    //varialbles de fonctionnement:
    int m_argc;
    char **m_argv;
    std::vector<std::thread*> m_threads;

    //variables graphique fenetre controller:
    GtkWidget * m_MainWindow;

    //fonction privées
    void newThreadSimulation();
    void fenetrePrincipale();


};


#endif //GRAVITYLAW_CONTROLLER_H
