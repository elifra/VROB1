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
#include <vector> 

#include <visp/vpConfig.h>
#include <visp/vpDebug.h>

#include <visp/vpImage.h>
#include <visp/vpImageIo.h>
#include <visp/vpDisplayX.h>
#include <visp3/core/vpUniRand.h>

#include <visp/vpImageFilter.h>
#include <visp/vpImageConvert.h>
#include <visp/vpImageDraw.h>

using namespace std;

void maxLocale(vpImage<double> & I, int i, int j, int tailleF) {
    assert(tailleF > 0 && tailleF%2 != 0);
    int imax = 0;
    int jmax = 0;
    double max =0;
    for(int k = i - (int)(tailleF/2); k <= i + (int)(tailleF/2); k++) {
        for(int l = j - (int)(tailleF/2); l <= j + (int)(tailleF/2); l++) {
            if(k >=0 && k < I.getRows() && l >=0 && l < I.getCols()){
                if(I[k][l] >0){
                    if(I[i][j] >= max){
                        I[imax][jmax] = 0;
                        imax = k;
                        jmax = l;
                        max = I[k][l];
                    } 
                    else I[k][l] = 0;
                }
            }
        }
    }
}

double sommeVoisinnage(vpImage<double> & I, int i, int j, int tailleF) {
    assert(tailleF > 0 && tailleF%2 != 0);
    double val = 0;
    for(int k = i - (int)(tailleF/2); k <= i + (int)(tailleF/2); k++) {
        for(int l = j - (int)(tailleF/2); l <= j + (int)(tailleF/2); l++) {
            if(k >=0 && k < I.getRows() && l >=0 && l < I.getCols()){
                val += I[k][l];
            }
        }
    }
    return val;
}

vpImage<double> harris_detector(vpImage<unsigned char>& I) {
    vpImage<double> IgradX;
    vpImageFilter::getGradX(I, IgradX);
    vpImage<double> IgradY;
    vpImageFilter::getGradY(I, IgradY);

    vpImage<double> IgradXcarre = vpImage<double>(I.getRows(), I.getCols());
    vpImage<double> IgradYcarre = vpImage<double>(I.getRows(), I.getCols());
    vpImage<double> IgradXIgradY = vpImage<double>(I.getRows(), I.getCols());
    for(int i = 0; i < I.getRows(); i++) {
        for(int j = 0; j < I.getCols(); j++) {
            IgradXcarre[i][j] = IgradX[i][j]*IgradX[i][j];
            IgradYcarre[i][j] = IgradY[i][j]*IgradY[i][j];
            IgradXIgradY[i][j] = IgradX[i][j]*IgradY[i][j];
        }
    }

    vpImage<double> R = vpImage<double>(I.getRows(), I.getCols());
    double k = 0.04;
    int tailleFenetre = 3;
    for(int i = 0; i < I.getRows(); i++) {
        for(int j = 0; j < I.getCols(); j++) {
            double a = sommeVoisinnage(IgradXcarre, i, j, tailleFenetre);
            double bc = sommeVoisinnage(IgradXIgradY, i, j, tailleFenetre);
            double d = sommeVoisinnage(IgradYcarre, i, j, tailleFenetre);
            R[i][j] = a*d-bc*bc - k * pow(a+d, 2);
        }
    }
    return R;
}

std::vector<vpImagePoint> Harris(vpImage<double>& I, double seuil) {
    //Seuillage
    std::vector<vpImagePoint> res;

    for(int i = 0; i < I.getRows(); i++) {
        for (int j = 0; j < I.getCols(); j++) {
            if(I[i][j] < seuil) I[i][j] = 0;
        }
    }
    //Calcul max locaux
    for(int i = 0; i < I.getRows(); i++) {
        for (int j = 0; j < I.getCols(); j++) {
            maxLocale(I,i,j,11);
        }
    }


    for(int i = 0; i < I.getRows(); i++) {
        for (int j = 0; j < I.getCols(); j++) {
            if(I[i][j] > 0) {
                vpImagePoint newval(i,j);
                res.push_back(newval);
            }
        }
    }

    return res;

}

void afficheHarris(vpImage<unsigned char>& I, double seuil){
//TRAITEMENT HARRIS
    vpImage<double> Iharris = harris_detector(I);

    std::vector<vpImagePoint> ptHarris = Harris(Iharris,seuil);
//FIN TRAITEMENT HARRIS

    vpImage<vpRGBa> Ires(I.getRows(), I.getCols());
    vpImageConvert::convert(I, Ires);

    for(auto pt : ptHarris){
        vpImageDraw::drawCross(Ires,pt,5,vpColor::green);
    }

    vpDisplayX d(Ires,100,100);
	vpDisplay::setTitle(Ires, "Harris");
	vpDisplay::display(Ires);
	vpDisplay::flush(Ires) ;	
    vpDisplay::getClick(Ires);
}

void KLT(vpImage<unsigned char>& I0,vpImage<unsigned char>& I, std::vector<vpImagePoint> harrisPoints, int tailleFenetre){
    for(auto pt : harrisPoints){
        vpImage<unsigned char> myTemplate(tailleFenetre,tailleFenetre);
                
    }
}

int main(int argc, char **argv)
{
    vpImage<unsigned char>  I1;
    vpImageIo::read(I1,"images/image.0001.pgm"); 
    afficheHarris(I1, 50000);
}















