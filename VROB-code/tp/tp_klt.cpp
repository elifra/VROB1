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

std::vector<vpImagePoint> Harris(vpImage<double>& I, double seuil, int tailleFenetre) {
    //Seuillage
    std::vector<vpImagePoint> res;
    int moitie = (int)(tailleFenetre/2);
    for(int i = 0; i < I.getRows(); i++) {
        for (int j = 0; j < I.getCols(); j++) {
            if(I[i][j] < seuil || i-moitie < 0 || i+moitie >= I.getRows() || j-moitie < 0 || j+moitie >= I.getCols()) {
                I[i][j] = 0;
            }
        }
    }
    //Calcul max locaux
    for(int i = 0; i < I.getRows(); i++) {
        for (int j = 0; j < I.getCols(); j++) {
            maxLocale(I,i,j,tailleFenetre);
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

std::vector<vpImagePoint> afficheHarris(vpImage<unsigned char>& I, double seuil, vpImage<vpRGBa> & Ires){
//TRAITEMENT HARRIS
    vpImage<double> Iharris = harris_detector(I);

    std::vector<vpImagePoint> ptHarris = Harris(Iharris,seuil,11);
//FIN TRAITEMENT HARRIS

//A SUPPRIMER, UTILE POUR TEST
    std::vector<vpImagePoint> newPt;
    newPt.push_back(ptHarris[int(ptHarris.size()/4)]);
    ptHarris = newPt;

    
    vpImageConvert::convert(I, Ires);

    for(auto pt : ptHarris){
        vpImageDraw::drawCross(Ires,pt,5,vpColor::green);
    }

    return ptHarris;
}

//TODO: a modifier pour h
vpImage<double> createTemplate(vpImage<unsigned char>& Iuc,vpImagePoint pt,int tailleFenetre, vpColVector h){
    vpImage<double> I;
    vpImageConvert::convert(Iuc,I);
    vpImage<double> newtemplate(tailleFenetre,tailleFenetre);
    int iT = 0;
    int jT = 0;
    int i = pt.get_i();
    int j = pt.get_j();
    for(int k = i - (int)(tailleFenetre/2); k <= i + (int)(tailleFenetre/2); k++) {
        jT = 0;
        for(int l = j - (int)(tailleFenetre/2); l <= j + (int)(tailleFenetre/2); l++) {
            newtemplate[iT][jT] = I.getValue(h[0]+k, h[1]+l);
            jT++;
        }
        iT++;
    }
    return newtemplate;
}

vpImage<double> createTemplate(vpImage<double>& I,vpImagePoint pt,int tailleFenetre, vpColVector h){
    vpImage<double> newtemplate(tailleFenetre,tailleFenetre);
    int iT = 0;
    int jT = 0;
    int i = pt.get_i();
    int j = pt.get_j();
    for(int k = i - (int)(tailleFenetre/2); k <= i + (int)(tailleFenetre/2); k++) {
        jT = 0;
        for(int l = j - (int)(tailleFenetre/2); l <= j + (int)(tailleFenetre/2); l++) {
            newtemplate[iT][jT] = I.getValue(h[0]+k, h[1]+l);
            jT++;
        }
        iT++;
    }
    return newtemplate;
}

double EQM(vpImage<double> I0, vpImage<double> I1){
    assert(I0.getRows() == I1.getRows() && I0.getCols() == I1.getCols());  
    double eqm = 0;
    for(int i = 0; i < I0.getRows(); i++) {
        for(int j = 0; j < I0.getCols(); j++) {
            eqm += pow(I0[i][j]-I1[i][j], 2);
        }
    }
    eqm = double (eqm/(I0.getRows()*I1.getCols()));
    return eqm;  
}

vpColVector erreurImages(vpImage<double> I0, vpImage<double> I1) {
    assert(I0.getRows() == I1.getRows() && I0.getCols() == I1.getCols());  
    vpColVector e(I0.getRows()*I0.getCols());
    int indE = 0;
    for(int i = 0; i < I0.getRows(); i++) {
        for(int j = 0; j < I0.getCols(); j++) {
            e[indE] = (I1[i][j]-I0[i][j]);
            indE++;
        }
    }
    return e; 
}

vpMatrix jacobienne(vpImage<double>& I, vpImage<double>& IgradX, vpImage<double>& IgradY) {
   vpMatrix jacob(I.getRows()*I.getCols(), 2);
    
    int indJ = 0;
    for(int i = 0; i < I.getRows(); i++) {
        for(int j = 0; j < I.getCols(); j++) {
            //if(i==0) cout << "IgradX : " << IgradX[i][j] << " IgradY : " << IgradY[i][j] << endl;
            jacob[indJ][0] = IgradX[i][j];
            jacob[indJ][1] = IgradY[i][j];
            indJ++;
        }
    }
    //cout << jacob << endl << endl;
    vpMatrix jacobPI = jacob.pseudoInverse();
    return jacobPI;
}

double norm(vpColVector v) {
    double n = 0;
    for(int i = 0; i < v.size(); i++) {
        n += pow(v[i],2);
    }
    n = sqrt(n);
    return n;
}

std::vector<vpImagePoint> KLT(vpImage<unsigned char>& I0,vpImage<unsigned char>& I, std::vector<vpImagePoint> harrisPoints, int tailleFenetre){
    std::vector<vpImagePoint> newHarrisPoints;
    vpImage<double> IgradX;
    vpImageFilter::getGradX(I, IgradX);
    vpImage<double> IgradY;
    vpImageFilter::getGradY(I, IgradY);

    vpImage<double> templateIgradX;
    vpImage<double> templateIgradY;

    vpColVector un(2,1);

    for(auto pt : harrisPoints){

        cout << I0.getRows()<< " " << I0.getCols() << endl;
        cout << I.getRows()<< " " << I.getCols() << endl;

        vpColVector h(2,0);
        vpImage<double> templateRef = createTemplate(I0,pt,tailleFenetre,h);
        vpImage<double> newtemplate = createTemplate(I,pt,tailleFenetre,h); 
        vpColVector oldH = h+un;
        //double eqm = EQM(templateRef, newtemplate);
        int i =0;
        while(norm(h-oldH) > 0.001) {
            cout << norm(h-oldH)  << endl;
            i++;
            vpColVector erreurTemplates = erreurImages(templateRef, newtemplate);

            templateIgradX = createTemplate(IgradX,pt,tailleFenetre,h);
            templateIgradY = createTemplate(IgradY,pt,tailleFenetre,h);

            vpMatrix jacob = jacobienne(newtemplate, templateIgradX, templateIgradY);
            vpColVector dh = -jacob*erreurTemplates;
            //cout << dh << endl;
            oldH =  h;
            //cout << "dh : " << dh << endl << endl;
            h = h+0.1*dh;
            //cout << "h : " << h << endl << endl;
            //cout << "dh[0] = " << dh[0] << " dh[1] = " << dh[1] << endl;

            newtemplate = createTemplate(I,pt,tailleFenetre,h);
            //eqm = EQM(templateRef, newtemplate);
            //cout << eqm << endl;
/*
            vpImagePoint p(pt.get_i()+h[0],pt.get_j()+h[1]);
            vpImage<vpRGBa> IresKLT(I.getRows(), I.getCols());
            vpImageConvert::convert(I, IresKLT);
            
            vpImageDraw::drawCross(IresKLT,p,5,vpColor::green);
            
            vpDisplayX d2(IresKLT,100,100);
            vpDisplay::setTitle(IresKLT, "KLT");
            vpDisplay::display(IresKLT);
            vpDisplay::flush(IresKLT) ;	
            vpDisplay::getClick(IresKLT);
*/
        }
        cout << "old : "<< pt.get_i()<< " ; " <<pt.get_j() << endl;
        cout << "new : "<< pt.get_i() + h[0]<<" ; " <<pt.get_j()+h[1] << endl;
        vpImagePoint newPoint(pt.get_i()+h[0], pt.get_j()+h[1]);
        newHarrisPoints.push_back(newPoint);
    }
    return newHarrisPoints;
}

int main(int argc, char **argv)
{
    bool affichage = true;
    int nbImage = 8;

    vpImage<unsigned char>  I1;
    vpImageIo::read(I1,"images/image.0001.pgm"); 
    vpImage<unsigned char>  I2;
    vpImageIo::read(I2,"images/image.0002.pgm"); 

    vpImage<vpRGBa> IresHARRIS(I1.getRows(), I1.getCols());
    std::vector<vpImagePoint> ptsHarris = afficheHarris(I1, 50000,IresHARRIS);
    if(affichage){ 
        vpDisplayX d(IresHARRIS,100,100);
        vpDisplay::setTitle(IresHARRIS, "Harris");
        vpDisplay::display(IresHARRIS);
        vpDisplay::getClick(IresHARRIS);
    }

    for(int indexImage =2;indexImage<=nbImage+1;indexImage++){

        std::vector<vpImagePoint> newHarrisPoints = KLT(I1,I2,ptsHarris,3);
        vpImage<vpRGBa> IresKLT(I1.getRows(), I1.getCols());
        vpImageConvert::convert(I2, IresKLT);

        for(auto pt : newHarrisPoints){
            vpImageDraw::drawCross(IresKLT,pt,3,vpColor::green);
        }
            vpDisplay::flush(IresKLT);

        vpImage<vpRGBa> outImage;
        vpDisplay::getImage(IresKLT,outImage);
        vpImageIo::write(outImage,"outImages/image.000+"+std::to_string(indexImage+1)+".png");

        if(affichage){ 
            vpDisplayX d2(IresKLT,100,100);
            vpDisplay::setTitle(IresKLT, "KLT");
            vpDisplay::display(IresKLT);
            vpDisplay::flush(IresKLT) ;	
            vpDisplay::getClick(IresKLT);

        }

        string filename1 = "images/image.000"+std::to_string(indexImage)+".pgm";
        vpImageIo::read(I1,filename1); 
        
        string filename2 = "images/image.000"+std::to_string(indexImage+1)+".pgm";
        vpImageIo::read(I2,filename2);

        ptsHarris = newHarrisPoints;
    }
    
    
    /* TEST pour verifier createTemplate()
    for (int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            cout<< (int)(I1[i][j]) << " ; ";
        }
        cout<<endl;
    }
    cout<<endl;
    
    vpColVector h(2,0.5);
    vpImagePoint p(1,1);
    cout<<h<<endl;

    cout<<createTemplate(I1,p,1,h);
    */
}















