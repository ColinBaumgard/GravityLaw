#include <iostream>

#include "Controller.h"



using namespace std;

int main(int argc, char **argv)
{

    srand(time(NULL));


    Controller controller(argc, argv);

    controller.start();


    return EXIT_SUCCESS;
}

