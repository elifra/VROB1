/****************************************************************************
 * Copyright (C) 2010 Universite de Rennes 1. All rights reserved.
 *
 * This software was developed at:
 * Universite de Rennes 1
 * Campus Universitaire de Beaulieu
 * 35042 Rennes Cedex
 *
 * This file uses the ViSP library.
*****************************************************************************/

/****************************************************************************
 * NOMS - PRENOMS:
 *  - Le Vot Maël
 *	- Davenel Thomas
 * 
 * Date :
 *****************************************************************************/


#include <iostream>

#include <visp/vpConfig.h>
#include <visp/vpDebug.h>

#include <visp/vpImage.h>
#include <visp/vpImageIo.h>
#include <visp/vpDisplayX.h>
#include <visp3/core/vpUniRand.h>

#include <visp/vpImageFilter.h>
#include <visp/vpImageConvert.h>

using namespace std;

vpImage<double> harris_detector(vpImage<unsigned char> I) {
    vpImage<double> IgradX;
    vpImageFilter::getGradX(I, IgradX);
    vpImage<double> IgradY;
    vpImageFilter::getGradY(I, IgradY);

    vpImage<double> R = vpImage<double>(I.getRows(), I.getCols());
    double k = 0.04;
    for(int i = 0; i < I.getRows(); i++) {
        for(int j = 0; j < I.getCols(); j++) {
            R[i][j] = IgradX[i][j]*IgradY[i][j] - k*pow(IgradX[i][j]+IgradY[i][j], 2);
        }
    }

    return R;
}

void afficheHarris(vpImage<double> I, double seuil) {
    for(int i = 0; i < I.getRows(); i++) {
        for (int j = 0; j < I.getCols(); j++) {
            if(I[i][j] < seuil) I[i][j] = 0;
            else I[i][j] = 1;
        }
    }
    vpImage<unsigned char> Ires(I.getRows(), I.getCols());
    vpImageConvert::convert(I, Ires);

    vpDisplayX d(Ires,100,100) ;
	vpDisplay::setTitle(Ires, "Harris");
	vpDisplay::display(Ires);
	vpDisplay::flush(Ires) ;	
    vpDisplay::getClick(Ires);
}

int main(int argc, char **argv)
{
    vpImage<unsigned char>  I1;
    vpImageIo::read(I1,"images/image.0001.pgm"); 

    vpImage<double> Iharris = harris_detector(I1);
    afficheHarris(Iharris, 1000.0);
}















