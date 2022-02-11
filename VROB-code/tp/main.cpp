#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <visp3/core/vpImage.h>
#include <visp3/io/vpImageIo.h>
#include "EigenFacesDB.h"
#include <visp/vpImageConvert.h>
#include <visp3/gui/vpPlot.h>

using namespace std;

vpImage<unsigned char> vectToImage(vpColVector v, std::string nom, bool write = true) {
    vpImage<double> I(112,92);
    for(int i = 0; i < 112; i++) {
        for(int j = 0; j < 92; j++) {
            I[i][j]= v[i*92 + j];
        }
    }

    vpImage<unsigned char> Iuchar(I.getHeight(), I.getWidth());
    vpImageConvert::convert(I,Iuchar);
    std::string path = "../results_eigenface/"+nom+".jpg";
    if(write) vpImageIo::write(Iuchar, path);

    return Iuchar;
}

void affichage(const std::vector<std::string>& paths, vpMatrix A, vpColVector & mean, int numImage){
    vpImage<double> I(112,92);
    for(int i = 0; i < 112; i++) {
        for(int j = 0; j < 92; j++) {
            I[i][j]= mean[i*92 + j];
        }
    }

    vpImage<unsigned char> Iuchar(I.getHeight(), I.getWidth());
    vpImageConvert::convert(I,Iuchar);
    std::string path = "../results_eigenface/mean.jpg";
    vpImageIo::write(Iuchar, path);    

    vpImage<double> Ipondere(112,92);
    vpColVector v_Ipondere = A.getCol(numImage-1);
    for(int i = 0; i < 112; i++) {
        for(int j = 0; j < 92; j++) {
            Ipondere[i][j]= v_Ipondere[i*92 + j];
        }
    }
    vpImage<unsigned char> Iuchar_pondere(I.getHeight(), I.getWidth());
    vpImageConvert::convert(Ipondere,Iuchar_pondere);
    path = "../results_eigenface/I_pondere_"+std::to_string(numImage)+".jpg";
    vpImageIo::write(Iuchar_pondere, path);
}

void  writeEigenFaceInImage(int m_w, int m_h, const std::string& path, vpColVector &v)
{
    double maxV = v.getMaxValue();
    double minV = v.getMinValue();
    vpImage<double> I(m_h,m_w);
    for(int i=0; i<m_h; i++)
        for(int j = 0; j<m_w; j++)
        {
            I[i][j] = ((v[i*m_w+j]-minV)/(maxV-minV));
        }
    
    vpImage<unsigned char> Ic(m_h,m_w);
    vpImageConvert::convert(I,Ic);
    vpImageIo::write(Ic, path);
}

void buildMeanImage(const std::vector<std::string>& paths, vpMatrix& A, vpColVector & mean){
    //CALCUL DE A
    int ind_i = 0;
    int ind_j = 0;
    for(std::string path:paths){
        vpImage<unsigned char> I;
        vpImageIo::read(I,path);
        vpImage<double> Id(112,92);
        vpImageConvert::convert(I,Id);
        for(int i = 0; i < I.getHeight(); i++) {
            for(int j = 0; j < I.getWidth(); j++) {
                A[ind_i][ind_j] = Id[i][j];
                ind_i++;
            }
        }
        ind_j++;
        ind_i=0;
    }

    //CALCUL DE MEAN

    for(int i = 0; i < A.getRows(); i++) {
        double sum = 0;
        for(int j = 0; j < A.getCols(); j++) {
            sum += A[i][j];
        }
        mean[i] = sum/A.getCols();
    }
}

void eigenface(vpMatrix & U, vpColVector & S) {
    for(int i = 0; i < 10; i++) {
        vpImage<double> I(112,92);
        vpColVector Uc = U.getCol(i);
        for(int k = 0; k < 112; k++) {
            for(int j = 0; j < 92; j++) {
                I[k][j]= Uc[k*92 + j];
            }
        }
        cout << "Valeur propre " << i << " : " << S[i] << endl;

        vpImage<unsigned char> Iuchar(I.getHeight(), I.getWidth());
        vpImageConvert::convert(I,Iuchar);
        std::string path = "../results_eigenface/eigenface"+std::to_string(i)+".jpg";
        vpImageIo::write(Iuchar, path); 
    } 
}

void ssd(vpImage<unsigned char>& I1,vpImage<unsigned char>& I2,vpImage<unsigned char>& e){
    for(int i = 0; i < 112; i++) {
        for(int j = 0; j < 92; j++) {
            e[i][j] = pow(double(I1[i][j])-double(I2[i][j]),2);
        }
    }
}

void courbeErreurPrediction(vpColVector erreurPrediction){
    vpPlot plot(1);

    // Initialize the number of curve for each graphic
    plot.initGraph(0, 1);
    // Set the color of the curves
    plot.setColor(0, 0, vpColor::blue);
    // Set the titles of the graphic
    char title[40];
    strncpy(title, "courbe Erreur prediction", 40);
    plot.setTitle(0, title);
    // Set the legend of each curves
    char legend[40];
    strncpy(legend, "Erreur prediction", 40);
    plot.setLegend(0, 0, legend);
    // Set the x axis legend of each curves
    char unit[40];
    strncpy(unit, "k", 40);
    plot.setUnitX(0, unit);
    // Set the y axis legend of each curves
    strncpy(unit, "SSD", 40);
    plot.setUnitY(0, unit);

    for(int i=0;i<erreurPrediction.size();i++){
        plot.plot(0,0,i,erreurPrediction[i]);
    }

    vpDisplay::getClick(plot.I);
}


void project(const std::vector<std::string>& paths, vpMatrix & A, vpMatrix & U, vpColVector & mean, int k, int num_image, std::string path_test) {
    k = min(k,(int)paths.size());
    
    vpColVector Wk(k);
    vpImage<unsigned char> I;
    std::string name;
    if(false && num_image<=A.getCols()){        
        cout<<"L'image predite fait partie des images de references"<<endl;
        //Calcul Image origine
        I = vectToImage(A.getCol(num_image-1)+mean,"image_origine_"+std::to_string(num_image));
    
        //Calcul Wk reférence 
        for(int i = 0; i < k; i++) {
            vpColVector Ukt = U.getCol(i);
            Wk[i] = Ukt*A.getCol(num_image-1);
        }
        name ="image_reconstruite_"+std::to_string(num_image);
    }
    else{
        cout<<"L'image predite ne fait pas partie des images de references"<<endl;
        //Calcul Image origine
        std::ostringstream ss;
        int num_doss = int((num_image)/10);
        ss << "../att_faces/s" << num_doss << "/" << num_image -((num_doss-1)*10) << ".pgm";
        vpImageIo::read(I,ss.str());
        //vpImageIo::write(I, "../results_eigenface/image_test_origine.jpg");

        //Calcul Wk test
        vpImage<double> Id(112,92);
        vpImageConvert::convert(I,Id);
        vpColVector Ic(112*92);
        int ind = 0;
        for(int i = 0; i < 112; i++) {
            for(int j = 0; j < 92; j++) {
                Ic[ind] = Id[i][j] - mean[ind];
                ind+=1;
            }
        }
        cout<<(A.getCol(num_image-1)-Ic).sum()<<endl;
        //Calcul Image origine
        I = vectToImage(Ic+mean,"image_test_origine");
    

        for(int i = 0; i < k; i++) {
            vpColVector Ukt = U.getCol(i);
            Wk[i] = Ukt*Ic;
        }
        name = "image_test";
    }

    vpColVector Jp = mean;
    vpColVector erreurPrediction(k);
    for(int i = 0; i < k; i++) {
        Jp += Wk[i]*U.getCol(i);        
        
        vpImage<unsigned char> I_tmp = vectToImage(Jp,"",false);
        vpImage<unsigned char> erreur_tmp(112,92);// = I-I_reconstruite;
        ssd(I_tmp,I,erreur_tmp);   

        erreurPrediction[i] = erreur_tmp.getSum();
    }

    courbeErreurPrediction(erreurPrediction);

    vpImage<unsigned char> I_reconstruite = vectToImage(Jp,name);


    vpImage<unsigned char> erreur(112,92);// = I-I_reconstruite;
    ssd(I_reconstruite,I,erreur);
    cout << "MSE = " << erreur.getSum()/(112*92) << endl;
    std::string path = "../results_eigenface/erreur"+std::to_string(num_image)+".jpg";
    vpImageIo::write(erreur, path);
}

void courbeCumulValPropre(vpColVector val_propre){
    double cum = 0;
    vpPlot plot(1);

    // Initialize the number of curve for each graphic
    plot.initGraph(0, 1);
    // Set the color of the curves
    plot.setColor(0, 0, vpColor::red);
    // Set the titles of the graphic
    char title[40];
    strncpy(title, "courbe cumul val propre", 40);
    plot.setTitle(0, title);
    // Set the legend of each curves
    char legend[40];
    strncpy(legend, "cumul val propre", 40);
    plot.setLegend(0, 0, legend);
    // Set the x axis legend of each curves
    char unit[40];
    strncpy(unit, "x", 40);
    plot.setUnitX(0, unit);
    // Set the y axis legend of each curves
    strncpy(unit, "y", 40);
    plot.setUnitY(0, unit);
    //range
    plot.initRange(0,0,val_propre.size(),0,100);

    double norm = val_propre.sum();
    for(int i=0;i<val_propre.size();i++){
        cum += (val_propre[i]/norm) * 100;
        plot.plot(0,0,i,cum);
    }

    vpDisplay::getClick(plot.I);
}

void buildBDFaces(const std::vector<std::string>& paths,const std::vector<std::string>& paths_test)
{
    int m_maxEigenFace = (int)paths.size();
    
    // On calcul les attibuts de l'image
    vpImage<unsigned char> I;
    vpImageIo::read(I,*paths.begin());
    int m_w = I.getWidth();
    int  m_h = I.getHeight();
    int m_size = m_h*m_w;
    
    std::cout << " * Caracteristique de l'images : " << m_h << "x" << m_w << std::endl;
    std::cout << " * Nombre d'image de la base : " << paths.size()<< std::endl;
    std::cout << " * Nombre de U : " << m_maxEigenFace << std::endl;

    // Creation du vpColVector pour le mean face
    std::cout << "[INFO] Creation Mean images ...." << std::endl;
    vpColVector m_vMean ;
    m_vMean = vpColVector(m_size);

    //Build Mean Image
    vpMatrix A(m_size,paths.size());
    std::cout<<"buildMeanImage"<<std::endl;
    buildMeanImage(paths,A,m_vMean);
    
    // Calcul de la matrice A (pondérée par v_mean)
    std::cout << "[INFO] Calcul de A ... " << std::endl;
    for(int i = 0; i < A.getRows(); i++) {
        for(int j = 0; j < A.getCols(); j++) {
            A[i][j] = A[i][j] - m_vMean[i];
        }
    }

    vpMatrix U = A;
    vpMatrix sertArien;
    vpColVector S_valPropre;

    U.svd(S_valPropre, sertArien);
    eigenface(U,S_valPropre);

    project(paths,A,U,m_vMean,300,100,paths_test[10]);
    
    affichage(paths,A,m_vMean,11);

    courbeCumulValPropre(S_valPropre);

    std::cout << "[INFO] Fin calcul BD ... " << std::endl;
}

void buildPathImagesAttFaces(std::vector<std::string>& path_ref,std::vector<std::string>& path_test,int nb_doss)
{
	for(int nbDir=1; nbDir<=nb_doss; nbDir++)
    {
		for(int nbImage=1; nbImage<=10;nbImage++)
		{
			std::ostringstream ss;
			ss << "../att_faces/s" << nbDir << "/" << nbImage << ".pgm";
			if(nbImage<8) path_ref.push_back(ss.str());
            else path_test.push_back(ss.str());
		}
    }
}


void testErreurVpconvert(std::vector<std::string> paths){
    vpImage<unsigned char> I;
    vpImageIo::read(I,paths[99]);
	vpImage<double> Id;
    vpImageConvert::convert(I,Id);
	vpImage<unsigned char> I2;
    vpImageConvert::convert(Id,I2);

    vpImageIo::write(I, "../results_eigenface/original.jpg");
    vpImageIo::write(I, "../results_eigenface/original2.jpg");

    vpImage<unsigned char> e(112,92);
    ssd(I,I2,e);
    vpImageIo::write(e, "../results_eigenface/erreur_original.jpg");
    cout<<e.getSum()/(112*92)<<endl;
}

int main()
{
	std::cout << "[INFO] Construction du path ..." << std::endl;
	std::vector<std::string> paths_ref;
    std::vector<std::string> path_test;
    buildPathImagesAttFaces(paths_ref,path_test,30);
	std::cout << "[INFO] Creation de base de donnees ..." << std::endl;
	
    buildBDFaces(paths_ref,path_test);
	
    //testErreurVpconvert(paths);


	return 0;
}