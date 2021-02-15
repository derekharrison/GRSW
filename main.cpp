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
    G = 1.0;        //Gravitational constant
    M = 0.2;        //Mass of gravitating object
    L = 1.0;        //Angular momentum of orbiting object

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

    /* Open file for writing data */
    std::ofstream myfile;
    std::string file_name = "data.txt";
    myfile.open(file_name);

    /* Evolve orbit */
    for(int i = 0; i < N; ++i) {
    	/* Advance step */
        u = uh * dtheta + u;
        uh = (3 * G*G * M*M / (L*L) * u*u - u + 1) * dtheta + uh;

        /* Compute radial coordinate */
        r = L*L / (G * M * u);

        /* Compute Cartesian coordinates */
        x = r * cos(theta);
        y = r * sin(theta);

        /* Export location data to file */
        myfile << x << " "
               << y << " "
               << "\n";

        /* Update angle */
        theta = theta + dtheta;
    }

    /* Close file */
    myfile.close();

    printf("done\n");

    return 0;
}
