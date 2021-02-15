/*
 * main.cpp
 *
 *  Created on: Feb 14, 2021
 *      Author: d-w-h
 */

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <math.h>
#include <stdio.h>

int main(int argc, char* argv[]) {

    int N;
    double G, M, L, uh0, u0, theta0, dtheta;

    /* Parameters */
    N = 2000;       //Number of steps
    G = 0.2;        //Gravitational constant
    M = 1.0;        //Mass of gravitating object
    L = 1.0;

    u0 = 0.5;       //Initial inverse radius test particle
    uh0 = 0.0;      //Initial derivative inverse radius wrt theta
    theta0 = 0;     //Initial angle test particle
    dtheta = 0.02;  //Step size

    /* Start calculations */
    double theta = theta0;
    double u = u0;
    double uh = uh0;
    double r = L*L / (G * M * u);
    double x = r * cos(theta);
    double y = r * sin(theta);

    std::ofstream myfile;
    std::string file_name = "data.txt";
    myfile.open(file_name);

    /* Evolve orbit */
    for(int i = 0; i < N; ++i) {
        u = uh * dtheta + u;
        uh = (3 * G*G * M*M / (L*L) * u*u - u + 1) * dtheta + uh;
        r = L*L / (G * M * u);

        x = r * cos(theta);
        y = r * sin(theta);

        myfile << x << " "
               << y << " "
               << "\n";

        theta = theta + dtheta;
    }

    myfile.close();

    printf("done\n");
    return 0;
}
