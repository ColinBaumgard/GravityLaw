//
// Created by theti2o on 28/02/16.
//

#include "Controller.h"

using namespace std;


Controller::Controller(int argc, char **argv)
{
    m_argc = argc;
    m_argv = argv;

    /* Variables */
    m_MainWindow = NULL;

}

void Controller::start()
{
    //création fenetre principale:
    fenetrePrincipale();

    //boucle principale:
    gtk_main();

}

void Controller::newSimulation_callback(GtkButton *button, Controller* data)
{
        data->newSimulation(button);
}

void Controller::newSimulation(GtkButton *button) //fonction lancé à l'appuie du bouton "Lancer simulation"
{

    thread newThread ([this](){newThreadSimulation();});

    m_threads.push_back(&newThread);
    newThread.join();

}

void Controller::newThreadSimulation()
{
    Simulation newSim;
    newSim.start();
}

void Controller::fenetrePrincipale()
{
    /* Initialisation de GTK+ */
    gtk_init(&m_argc, &m_argv);

    /* Création de la fenêtre */
    m_MainWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    g_signal_connect(G_OBJECT(m_MainWindow), "delete-event", G_CALLBACK(gtk_main_quit), NULL);

    /* Ajout des widget */
    GtkWidget *bouton_newSimulation;
    bouton_newSimulation = gtk_button_new_with_label("Simulation");
    g_signal_connect(G_OBJECT(bouton_newSimulation), "clicked", G_CALLBACK(newSimulation_callback), this);
    gtk_container_add(GTK_CONTAINER(m_MainWindow), bouton_newSimulation);





    /* Affichage */
    gtk_widget_show_all(m_MainWindow);

}





