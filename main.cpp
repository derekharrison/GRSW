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

double f1(double t, double y, double G, double M, double L);
double f2(double t, double y);

int main(int argc, char* argv[]) {

    int N;
    double G, M, L, E, uh0, u0, theta0, dtheta;

    /* Parameters */
    N = 5*8000;     //Number of steps
    G = 1.0;        //Gravitational constant
    M = 0.2;        //Mass of gravitating object
    L = 1.0;        //Angular momentum of orbiting object
    E = 1.0;        //Energy of orbiting object

    u0 = 0.5;       //Initial inverse radius test particle
    uh0 = 0.0;      //Initial derivative inverse radius wrt theta
    theta0 = 0;     //Initial angle test particle
    dtheta = 0.005; //Step size

    /* Start calculations */
    double theta = theta0;
    double u = u0;
    double uh = uh0;
    double r = L*L / (G * M * u);
    double x = r * cos(theta);
    double y = r * sin(theta);
    double t = 0;

    /* Open file for writing data */
    std::ofstream myfile;
    std::string file_name = "data.txt";
    myfile.open(file_name);

    /* Evolve orbit */
    for(int i = 0; i < N; ++i) {
    	/* Advance step */
    	double u_o = u;
    	double uh_o = uh;
    	double h = dtheta;

    	/* Integration using the method of Heun */
        double uh_hat = uh_o + h*f1(theta, u_o, G, M, L);
        u = u_o + 0.5*h*(f2(theta, uh_o) + f2(theta, uh_hat));

        double u_hat = u_o + h*f2(theta, uh_o);
        uh = uh_o + 0.5*h*(f1(theta, u_o, G, M, L) + f1(theta, u_hat, G, M, L));

        /* Compute radial coordinate */
        r = L * L / (G * M * u);

        /* Compute time coordinate */
        double d_tao = r * r * dtheta / L;
        double dt = E * d_tao / (1.0 - 2 * G * M / r);

        t = t + dt;

        /* Compute Cartesian coordinates */
        x = r * cos(theta);
        y = r * sin(theta);

        /* Export location data to file */
        myfile << x << " "
               << y << " "
               << t << "\n";

        /* Update angle */
        theta = theta + dtheta;
    }

    /* Close file */
    myfile.close();

    printf("done\n");

    return 0;
}

double f1(double t, double y, double G, double M, double L) {

    double result = (3 * G*G * M*M / (L*L) * y*y - y + 1);

    return result;
}

double f2(double t, double y) {

    double result = y;

    return result;
}
