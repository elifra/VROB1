#define VP_TRACE

//! \example tutorial-viewer.cpp
//! [Include display]
#include <visp3/gui/vpDisplayD3D.h>
#include <visp3/gui/vpDisplayGDI.h>
#include <visp3/gui/vpDisplayGTK.h>
#include <visp3/gui/vpDisplayX.h>
#include <visp3/gui/vpDisplayOpenCV.h>
#include <visp3/core/vpPoint.h>
#include <visp3/core/vpPlane.h>
#include <visp3/gui/vpPlot.h>
#include <visp3/core/vpMeterPixelConversion.h>
#include <visp3/core/vpCameraParameters.h>

#include <visp3/core/vpExponentialMap.h>
#include <visp3/core/vpVelocityTwistMatrix.h>
#include <cmath>


//! [Include display]
//! [Include io]
#include <visp3/io/vpImageIo.h>
//! [Include io]

using namespace std ;


void
display(vpCameraParameters& cam, vpImage<unsigned char> &I, vpColVector &x, vpColVector &xd)
{
    for (int i = 0 ; i < x.getRows()/2 ; i++)
    {
        vpImagePoint u,ud ;
        vpMeterPixelConversion::convertPoint(cam,x[2*i],x[2*i+1],u) ;
        vpDisplay::displayPoint(I,u,vpColor::red, 2) ;

        vpMeterPixelConversion::convertPoint(cam,xd[2*i],xd[2*i+1],ud) ;
        vpDisplay::displayCircle(I,ud,10,vpColor::green) ;

    }

    vpDisplay::flush(I) ;
}


// Projection d'un point 3D sur le plane image  X(3), x(2)
void
project(vpColVector &X, vpColVector &x)
{
    x[0] = X[0]/X[2];
    x[1] = X[1]/X[2];
}

// Changement de repere bX(3), aX(3), aTb est une matrice homogène
void changeFrame(const vpColVector &bX, const vpHomogeneousMatrix &aTb,  vpColVector &aX)
{
    vpColVector bX_2(4,1);
    vpColVector aX_2(4,1);

    bX_2[0] = bX[0]; bX_2[1] = bX[1]; bX_2[2] = bX[2];
    aX_2 = aTb*bX_2;

    aX[0] = aX_2[0]; aX[1] = aX_2[1]; aX[2] = aX_2[2];
}



// Calcul de la matrice d'interaction d'un point 2D
void
computeInteractionMatrix(vpColVector &cX, double x, double y, vpMatrix &Lx)
{
    Lx[0][0] = -1/cX[2]; Lx[0][1] = 0; Lx[0][2] = x/cX[2]; Lx[0][3] = x*y; Lx[0][4] = -(1+x*x); Lx[0][5] = y;
    Lx[1][0] = 0; Lx[1][1] = -1/cX[2]; Lx[1][2] = y/cX[2]; Lx[1][3] = 1+y*y; Lx[1][4] = -x*y; Lx[1][5] = -x;
}




void
tp2DVisualServoingOnePoint()
{

    //-------------------------------------------------------------
    // Mise en oeuvre des courbes



    vpPlot plot(4, 700, 700, 100, 200, "Curves...");


    char title[40];
    strncpy( title, "||e||", 40 );
    plot.setTitle(0,title);
    plot.initGraph(0,1);

    strncpy( title, "x-xd", 40 );
    plot.setTitle(1, title);
    plot.initGraph(1,2);

    strncpy( title, "camera velocity", 40 );
    plot.setTitle(2, title);
    plot.initGraph(2,6);


    strncpy( title, "Camera position", 40 );
    plot.setTitle(3, title);
    plot.initGraph(3,6);

    //-------------------------------------------------------------
    // Affichage des images
    vpImage<unsigned char> I(400,600) ;
    vpDisplayX d ;
    d.init(I) ;
    vpDisplay::display(I);
    vpCameraParameters cam(400,400,300,200) ;

    //-------------------------------------------------------------

    //Definition de la scene

    //positions initiale (à tester)

    //Definition de la scene
    vpHomogeneousMatrix cTw (0,0,1,  0,0,0) ;

    //position of the point in the world frame
    vpColVector wX(3) ;
    wX[0] = 0.5 ; wX[1] = 0.2 ; wX[2] = -0.5 ;


    // a chaque fois que vous verez size metter la bonne taille à la place
    int size ;

    vpColVector e(2,1) ; //


    // position courante, position desiree
    vpColVector x(2), xd(2,0) ;
    //matrice d'interaction
    vpMatrix Lx(2,6) ;

    // position desirée  (au centre de l'image x=0, y=0)


    // vitesse de la camera
    vpColVector v(6) ;
    double lambda = 0.1 ;
    int iter = 0 ;
    while (fabs(e.sumSquare()) > 1e-6)
    {
        // calcul de la position des points dans l'image en fonction de cTw
       // instancier x
        vpColVector cX(3);
        changeFrame(wX,cTw,cX);
        project(cX,x);

        //calcul de l'erreur
        e[0] = x[0]-xd[0];
        e[1] = x[1]-xd[1];

        // Calcul de la matrice d'interaction
        computeInteractionMatrix(cX,x[0],x[1],Lx);

        //calcul de la loi de commande v= ...

        v = -lambda*Lx.pseudoInverse()*e ;


        // Ne pas modifier la suite
        //mise a jour de la position de la camera
        cTw = vpExponentialMap::direct(v).inverse()* cTw ;

        cout << "iter "<< iter <<" : "<< e.t() << endl ;

        iter++ ;



        //mise a jour des courbes
        vpPoseVector ctw(cTw) ;
        plot.plot(0,0,iter, e.sumSquare()) ;
        plot.plot(1,iter, e) ;
        plot.plot(2,iter, v) ;
        plot.plot(3,iter, ctw) ;
        //mise a jour de l'image
        display(cam,I,x,xd) ;


    }

    // sauvegarde des courbes

    plot.saveData(0,"e.txt","#");
    plot.saveData(1,"error.txt","#");
    plot.saveData(2,"v.txt","#");
    plot.saveData(3,"p.txt","#");

    int a ; cin >> a ;
    // sauvegarde de l'image finale
    {
        vpImage<vpRGBa>  Irgb ;
        vpDisplay::getImage(I,Irgb) ;
        vpImageIo::write(Irgb,"1pt.jpg") ;
    }
    cout << "Clicker sur l'image pour terminer" << endl ;
    vpDisplay::getClick(I) ;
}




void
tp2DVisualServoingFourPoint(bool pos_courante)
{



    //-------------------------------------------------------------
    // Mise en oeuvre des courbes

    vpPlot plot(4, 700, 700, 100, 200, "Curves...");


    char title[40];
    strncpy( title, "||e||", 40 );
    plot.setTitle(0,title);
    plot.initGraph(0,1);

    strncpy( title, "x-xd", 40 );
    plot.setTitle(1, title);
    plot.initGraph(1,8);

    strncpy( title, "camera velocity", 40 );
    plot.setTitle(2, title);
    plot.initGraph(2,6);


    strncpy( title, "camera position", 40 );
    plot.setTitle(3, title);
    plot.initGraph(3,6);

    //-------------------------------------------------------------
    // Affichage des images
    vpImage<unsigned char> I(400,600) ;
    vpDisplayX d ;
    d.init(I) ;
    vpDisplay::display(I);
    vpCameraParameters cam(300,300,300,200) ;

    //-------------------------------------------------------------


    //positions initiale (à tester)
    //vpHomogeneousMatrix cTw (-0.2, -0.1, 1.3, vpMath::rad(10), vpMath::rad(20), vpMath::rad(30) ) ;
     // vpHomogeneousMatrix cTw (0.2,0.1,1.3,  0,0,vpMath::rad(5)) ;
      // vpHomogeneousMatrix cTw (0,0,1,  0,0,vpMath::rad(45)) ;
      vpHomogeneousMatrix cTw (0, 0, 1,  0, 0, vpMath::rad(90)) ;
    //vpHomogeneousMatrix cTw (0, 0, 1,  0, 0, vpMath::rad(180)) ;

    // position finale
    vpHomogeneousMatrix cdTw (0,0,1,  0,0,0) ;



    // position des point dans le repere monde Rw
    vpColVector wX[4] ;
    for (int i = 0 ; i < 4 ; i++) wX[i].resize(3) ;

    double M = 0.5 ;
    wX[0][0] = -M     ; wX[0][1] = -M     ; wX[0][2] = 0 ;
    wX[1][0] = M ;      wX[1][1] = -M     ; wX[1][2] = 0 ;
    wX[2][0] = M ;      wX[2][1] =  M;      wX[2][2] = 0 ;
    wX[3][0] =  -M    ; wX[3][1] =  M;      wX[3][2] = 0 ;

    int size ;
    vpColVector e(8,1) ; //

    vpColVector x1(2), xd1(2,0) , Xd1(3,0) ;
    vpColVector x2(2), xd2(2,0) , Xd2(3,0) ;
    vpColVector x3(2), xd3(2,0) , Xd3(3,0) ;
    vpColVector x4(2), xd4(2,0) , Xd4(3,0) ;

    //initialisation de la position désire des points dans l'image en fonction de cdTw
    changeFrame(wX[0],cdTw,Xd1);
    project(Xd1,xd1);
    changeFrame(wX[1],cdTw,Xd2);
    project(Xd2,xd2);
    changeFrame(wX[2],cdTw,Xd3);
    project(Xd3,xd3);
    changeFrame(wX[3],cdTw,Xd4);
    project(Xd4,xd4);

    vpColVector v(6) ;
    double lambda = 0.1 ;
    int iter = 0 ;
    cout << ("before while") << endl;


    vpMatrix Lx ;
    /*
    Lx calculée par rapport à la position désirée
    */
    if(!pos_courante){

        vpMatrix Lx1(2,6) ;
        computeInteractionMatrix(Xd1,xd1[0],xd1[1],Lx1);
        vpMatrix Lx2(2,6) ;
        computeInteractionMatrix(Xd2,xd2[0],xd2[1],Lx2);
        vpMatrix Lx3(2,6) ;
        computeInteractionMatrix(Xd3,xd3[0],xd3[1],Lx3);
        vpMatrix Lx4(2,6) ;
        computeInteractionMatrix(Xd4,xd4[0],xd4[1],Lx4);

        Lx.stack(Lx1);
        Lx.stack(Lx2);
        Lx.stack(Lx3);
        Lx.stack(Lx4);
    }
        

    while (fabs(e.sumSquare()) > 1e-16)
    {
        /*
        Lx Calculée par rapport à la position courante
        */
        
        // calcul de la position des points dans l'image en fonction de cTw
        vpColVector cX1(3);
        changeFrame(wX[0],cTw,cX1);
        project(cX1,x1);

        vpColVector cX2(3);
        changeFrame(wX[1],cTw,cX2);
        project(cX2,x2);

        vpColVector cX3(3);
        changeFrame(wX[2],cTw,cX3);
        project(cX3,x3);

        vpColVector cX4(3);
        changeFrame(wX[3],cTw,cX4);
        project(cX4,x4);

        if(pos_courante){
            // Calcul de la matrice d'interaction
            Lx.clear();

            vpMatrix Lx1(2,6) ;
            computeInteractionMatrix(cX1,x1[0],x1[1],Lx1);
            vpMatrix Lx2(2,6) ;
            computeInteractionMatrix(cX2,x2[0],x2[1],Lx2);
            vpMatrix Lx3(2,6) ;
            computeInteractionMatrix(cX3,x3[0],x3[1],Lx3);
            vpMatrix Lx4(2,6) ;
            computeInteractionMatrix(cX4,x4[0],x4[1],Lx4);


            Lx.stack(Lx1);
            Lx.stack(Lx2);
            Lx.stack(Lx3);
            Lx.stack(Lx4);
        }        

        //calcul de l'erreur

        e[0] = x1[0]-xd1[0]; e[1] = x1[1]-xd1[1];
        e[2] = x2[0]-xd2[0]; e[3] = x2[1]-xd2[1];
        e[4] = x3[0]-xd3[0]; e[5] = x3[1]-xd3[1];
        e[6] = x4[0]-xd4[0]; e[7] = x4[1]-xd4[1];

        //calcul de la loi de commande
        v = -lambda*Lx.pseudoInverse()*e ;

        //mise à jour de la position de la caméra
        cTw = vpExponentialMap::direct(v).inverse()* cTw ;

        cout << "iter "<< iter <<" : "<< e.t() << endl ;
        iter++ ;

       //mise a jour des courbes
        vpPoseVector ctw(cTw) ;
        plot.plot(0,0,iter, e.sumSquare()) ;
        plot.plot(1,iter, e) ;
        plot.plot(2,iter, v) ;
        plot.plot(3,iter, ctw) ;
        //mise a jour de l'image
        display(cam,I,x1,xd1) ;
        display(cam,I,x2,xd2) ;
        display(cam,I,x3,xd3) ;
        display(cam,I,x4,xd4) ;

    }

    // sauvegarde des courbes
    plot.saveData(0,"e.txt","#");
    plot.saveData(1,"error.txt","#");
    plot.saveData(2,"v.txt","#");
    plot.saveData(3,"p.txt","#");

    // sauvegarde de l'image finale
    {
        vpImage<vpRGBa>  Irgb ;
        vpDisplay::getImage(I,Irgb) ;
        vpImageIo::write(Irgb,"4pt.jpg") ;
    }
    cout << "Clicker sur l'image pour terminer" << endl ;
    vpDisplay::getClick(I) ;
}

double sinc(const double x)
{
	if (x==0)return 1;
	return sin(x)/x;
}

void
computeError3D(vpColVector & e, vpHomogeneousMatrix & ceTc, vpHomogeneousMatrix & ceTw, vpHomogeneousMatrix & cTw)
{
    ceTc = ceTw*cTw.inverse();
    e[0] = ceTc[0][3]; e[1] = ceTc[1][3]; e[2] = ceTc[2][3];
    vpThetaUVector thetaU(ceTc);
    e[3] = thetaU[0]; e[4] = thetaU[1]; e[5] = thetaU[2]; 
}

void
computeInteractionMatrix3D(vpHomogeneousMatrix & ceTc, vpMatrix & Ls)
{
    vpThetaUVector thetaU(ceTc);
    double theta = thetaU.getTheta();
    vpColVector u = thetaU.getU();
    vpMatrix Lw(3,3,0);

    Lw.diag();
    Lw += theta/2 * vpColVector::skew(u) + vpColVector::skew(u)*vpColVector::skew(u)*(1-sinc(theta)/(pow(sinc(theta/2),2)));

    Ls[0][0] = ceTc[0][0]; Ls[0][1] = ceTc[0][1]; Ls[0][2] = ceTc[0][2];
    Ls[1][0] = ceTc[1][0]; Ls[1][1] = ceTc[1][1]; Ls[1][2] = ceTc[1][2];
    Ls[2][0] = ceTc[2][0]; Ls[2][1] = ceTc[2][1]; Ls[2][2] = ceTc[2][2];
    Ls.insert(Lw,3,3);
}

void
tp3DVisualServoing()
{


    vpTRACE("begin" ) ;

    vpPlot plot(4, 700, 700, 100, 200, "Curves...");


    char title[40];
    strncpy( title, "||e||", 40 );
    plot.setTitle(0,title);
    plot.initGraph(0,1);

    strncpy( title, "x-xd", 40 );
    plot.setTitle(1, title);
    plot.initGraph(1,6);

    strncpy( title, "camera velocity", 40 );
    plot.setTitle(2, title);
    plot.initGraph(2,6);


    strncpy( title, "Camera position", 40 );
    plot.setTitle(3, title);
    plot.initGraph(3,6);

    //-------------------------------------------------------------
    // Affichage des images
    vpImage<unsigned char> I(400,600) ;
    vpDisplayX d ;
    d.init(I) ;
    vpDisplay::display(I);
    vpCameraParameters cam(300,300,300,200) ;

    //-------------------------------------------------------------

    // position des point dans le repere monde Rw
    vpColVector wX[4] ;
    for (int i = 0 ; i < 4 ; i++) wX[i].resize(3) ;

    double M = 0.5 ;
    wX[0][0] = -M     ; wX[0][1] = -M     ; wX[0][2] = 0 ;
    wX[1][0] = M ;      wX[1][1] = -M     ; wX[1][2] = 0 ;
    wX[2][0] = M ;      wX[2][1] =  M;      wX[2][2] = 0 ;
    wX[3][0] =  -M    ; wX[3][1] =  M;      wX[3][2] = 0 ;

    vpColVector x1(2), xd1(2), Xd1(1);
    vpColVector x2(2), xd2(2), Xd2(1);
    vpColVector x3(2), xd3(2), Xd3(1);
    vpColVector x4(2), xd4(2), Xd4(1);

    

    //Definition de la scene
    vpHomogeneousMatrix cTw (-0.2, -0.1, 1.3,
                             vpMath::rad(10), vpMath::rad(20), vpMath::rad(30) ) ;
    vpHomogeneousMatrix cdTw (0,0,1,  0,0,0) ;

    //initialisation de la position désire des points dans l'image en fonction de cdTw
    changeFrame(wX[0],cdTw,Xd1);
    project(Xd1,xd1);
    changeFrame(wX[1],cdTw,Xd2);
    project(Xd2,xd2);
    changeFrame(wX[2],cdTw,Xd3);
    project(Xd3,xd3);
    changeFrame(wX[3],cdTw,Xd4);
    project(Xd4,xd4);


    int size ;
    vpColVector e(6,1) ; //erreur de translation + rotation

    vpMatrix Lx(6,6,0) ;

    vpColVector v(6) ;
    double lambda = 0.1 ;
    int iter = 0 ;
    while (fabs(e.sumSquare()) > 1e-6)
    {
        //projection des points
        vpColVector cX1(3);
        changeFrame(wX[0],cTw,cX1);
        project(cX1,x1);

        vpColVector cX2(3);
        changeFrame(wX[1],cTw,cX2);
        project(cX2,x2);

        vpColVector cX3(3);
        changeFrame(wX[2],cTw,cX3);
        project(cX3,x3);

        vpColVector cX4(3);
        changeFrame(wX[3],cTw,cX4);
        project(cX4,x4);

        // Calcul de l'erreur
        //computeError3D(...) ;
        vpHomogeneousMatrix ceTc;
        computeError3D(e, ceTc, cdTw, cTw);
        cout << e << endl;

        // Calcul de la matrice d'interaction
        //  computeInteractionMatrix3D(...) ;
        computeInteractionMatrix3D(ceTc, Lx);

        //        Calcul de la loi de commande
        v = -lambda*Lx.pseudoInverse()*e;


        // Mis à jour de la position de la camera
        cTw = vpExponentialMap::direct(v).inverse()* cTw ;

        cout << "iter "<< iter <<" : "<< e.t() << endl ;

        iter++ ;

    //mis a jour de courbes
        vpPoseVector crw(cTw) ;
        plot.plot(0,0,iter, e.sumSquare()) ;
        plot.plot(1,iter, e) ;
        plot.plot(2,iter, v) ;
        plot.plot(3,iter,crw) ;
        //mise a jour de l'image
        display(cam,I,x1,xd1) ;
        display(cam,I,x2,xd2) ;
        display(cam,I,x3,xd3) ;
        display(cam,I,x4,xd4) ;


    }

// sauvegarde des courbes
    plot.saveData(0,"e.txt","#");
    plot.saveData(1,"error.txt","#");
    plot.saveData(2,"v.txt","#");
    plot.saveData(3,"p.txt","#");

    int a ; cin >> a ;

}


void
tp2DVisualServoingFourPointMvt()
{

/*
    reprendre votre code pour 4 points
    au debut de la boucle d'av vous considerer que les points sont en mouvement (o
            while (fabs(e.sumSquare()) > 1e-16)
            {
                // les points sont animés d'un mouvement de 1cm/s en x dans Rw
                for (int i = 0 ; i < 4 ; i++) wX[i][0] += 0.01 ;
            }

*/
}


int main(int argc, char** argv)
{

   //tp2DVisualServoingOnePoint() ;
     //tp2DVisualServoingFourPoint(true) ;
    tp3DVisualServoing() ;
      //tp2DVisualServoingFourPointMvt() ;

      /* TEST changeFrame() */
    /*vpColVector aX(3);
    vpColVector bX(3,1);
    vpHomogeneousMatrix aTb;
    vpTranslationVector atb(1,0,0);
    vpMatrix rotMatrice(3,3,{1,0,0,0,1,0,0,0,1});

    bX[0] = 0; bX[1] = 0; bX[2] = 0;
    vpRotationMatrix aRb(rotMatrice);
    aTb.insert(aRb);
    aTb.insert(atb);

    changeFrame(bX,aTb,aX);*/
}
