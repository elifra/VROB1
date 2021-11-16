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

using namespace std;

// QUESTION 2 : LIMITE DE PERCEPTION VISUELLE
void question2(){
  vpImage<unsigned char> I = vpImage<unsigned char>(384,384);

  for (int i=0; i<192; i++) 
		for (int j=0; j<384; j++){
			I[i][j] = 128;
		}
  for (int i=192; i<384; i++) 
		for (int j=0; j<384; j++){
			I[i][j] = 244;
		}

  for (int i=64; i<128; i++) 
		for (int j=64; j<128; j++){
			I[i][j] = 130;
		}
  for (int i=64; i<128; i++) 
		for (int j=256; j<320; j++){
			I[i][j] = 132;
		}

  for (int i=256; i<320; i++) 
		for (int j=64; j<128; j++){
			I[i][j] = 246;
		}
  for (int i=256; i<320; i++) 
		for (int j=256; j<320; j++){
			I[i][j] = 248;
		}

  vpDisplayX d1(I,384,384) ;
	vpDisplay::setTitle(I, "Question 2");
	vpDisplay::display(I);
	vpDisplay::flush(I) ;	
	vpDisplay::getClick(I);

  vpDisplay::close(I) ;
}

// QUESTION 3 : PERCEPTION DES COULEURS
void question3(){
  int sIm;

  cout << "rentrer le parametre x : ";
	cin >> sIm; 

  //Image 1
  vpImage<vpRGBa> Irouge = vpImage<vpRGBa>(384,384);
  for (int i=0; i<384; i++) 
		for (int j=0; j<384; j++){
			Irouge[i][j].R=128;
			Irouge[i][j].G=0;
			Irouge[i][j].B=0;
		}
  for (int i=160; i<224; i++) 
		for (int j=160; j<224; j++){
			Irouge[i][j].R=128+sIm;
			Irouge[i][j].G=0;
			Irouge[i][j].B=0;
		}

  //Image 2
  vpImage<vpRGBa> Ibleu = vpImage<vpRGBa>(384,384);
  for (int i=0; i<384; i++) 
		for (int j=0; j<384; j++){
			Ibleu[i][j].R=0;
			Ibleu[i][j].G=0;
			Ibleu[i][j].B=128;
		}
  for (int i=160; i<224; i++) 
		for (int j=160; j<224; j++){
			Ibleu[i][j].R=0;
			Ibleu[i][j].G=0;
			Ibleu[i][j].B=128+sIm;
		}

  //Image 3
  vpImage<vpRGBa> Ivert = vpImage<vpRGBa>(384,384);
  for (int i=0; i<384; i++) 
		for (int j=0; j<384; j++){
			Ivert[i][j].R=0;
			Ivert[i][j].G=128;
			Ivert[i][j].B=0;
		}
  for (int i=160; i<224; i++) 
		for (int j=160; j<224; j++){
			Ivert[i][j].R=0;
			Ivert[i][j].G=128+sIm;
			Ivert[i][j].B=0;
		}

  vpDisplayX d1(Irouge,384,384) ;
	vpDisplay::setTitle(Irouge, "Question 3");
	vpDisplay::display(Irouge);
	vpDisplay::flush(Irouge) ;	

  vpDisplayX d2(Ibleu,384,384) ;
	vpDisplay::setTitle(Ibleu, "Question 3");
	vpDisplay::display(Ibleu);
	vpDisplay::flush(Ibleu) ;	

  vpDisplayX d3(Ivert,384,384) ;
	vpDisplay::setTitle(Ivert, "Question 3");
	vpDisplay::display(Ivert);
	vpDisplay::flush(Ivert) ;	
  vpDisplay::getClick(Ivert);

 

  vpDisplay::close(Irouge) ;
  vpDisplay::close(Ibleu) ;
  vpDisplay::close(Ivert) ;
}

// QUESTION 4 : ILLUSION DU GRADIENT
void question4(){
  vpImage<unsigned char> I1 = vpImage<unsigned char>(384,256);

  //Image 1
  for (int i=0; i<384; i++) 
		for (int j=0; j<256; j++){
			I1[i][j] = 255;
		}
  for (int i=188; i<196; i++) 
		for (int j=0; j<256; j++){
			I1[i][j] = 128;
		}

  vpImage<unsigned char> I2 = vpImage<unsigned char>(384,256);

  //Image 2
  for (int i=0; i<384; i++) 
		for (int j=0; j<256; j++){
			I2[i][j] = j;
		}
  for (int i=188; i<196; i++) 
		for (int j=0; j<256; j++){
			I2[i][j] = 128;
		}

  vpDisplayX d1(I1,384,256) ;
	vpDisplay::setTitle(I1, "Question 4");
	vpDisplay::display(I1);
	vpDisplay::flush(I1) ;

  vpDisplayX d2(I2,384,256) ;
	vpDisplay::setTitle(I2, "Question 4");
	vpDisplay::display(I2);
	vpDisplay::flush(I2) ;	
  vpDisplay::getClick(I2);

  vpDisplay::close(I1) ;
  vpDisplay::close(I2) ;
}

// QUESTION 5 : BANDES DE MACH
void question5(){
vpImage<unsigned char> I = vpImage<unsigned char>(290,360);

  //Image 
  for (int i=0; i<290; i++) {
		for (int j=0; j<60; j++){
			I[i][j] = 102;
		}
    for (int j=60; j<120; j++){
			I[i][j] = 127;
    }
    for (int j=120; j<180; j++){
			I[i][j] = 152;
    }
    for (int j=180; j<240; j++){
			I[i][j] = 178;
    }
    for (int j=240; j<300; j++){
			I[i][j] = 202;
    }
    for (int j=300; j<360; j++){
			I[i][j] = 228;
    }
  }
  vpDisplayX d(I,290,360) ;
	vpDisplay::setTitle(I, "Question 5");
	vpDisplay::display(I);
	vpDisplay::flush(I) ;	
  vpDisplay::getClick(I);

  vpDisplay::close(I) ;
}

// QUESTION 6 : GRILLE DE HERMAN
void question6(){
  vpImage<unsigned char> I = vpImage<unsigned char>(168,168);

  for (int i=0; i<168; i++) 
		for (int j=0; j<168; j++){
			I[i][j] = 255;
		}

  for (int i=8; i<40; i++) 
		for (int j=8; j<40; j++){
			I[i][j] = 0;
		}
  for (int i=8; i<40; i++) 
		for (int j=48; j<80; j++){
			I[i][j] = 0;
		}
  for (int i=8; i<40; i++) 
		for (int j=88; j<120; j++){
			I[i][j] = 0;
		}
  for (int i=8; i<40; i++) 
		for (int j=128; j<160; j++){
			I[i][j] = 0;
		}
  for (int i=48; i<80; i++) 
		for (int j=8; j<40; j++){
			I[i][j] = 0;
		}
  for (int i=48; i<80; i++) 
		for (int j=48; j<80; j++){
			I[i][j] = 0;
		}
  for (int i=48; i<80; i++)
		for (int j=88; j<120; j++){
			I[i][j] = 0;
		}
  for (int i=48; i<80; i++) 
		for (int j=128; j<160; j++){
			I[i][j] = 0;
		}
  for (int i=88; i<120; i++) 
		for (int j=8; j<40; j++){
			I[i][j] = 0;
		}
  for (int i=88; i<120; i++) 
		for (int j=48; j<80; j++){
			I[i][j] = 0;
		}
  for (int i=88; i<120; i++) 
		for (int j=88; j<120; j++){
			I[i][j] = 0;
		}
  for (int i=88; i<120; i++) 
		for (int j=128; j<160; j++){
			I[i][j] = 0;
		}
  for (int i=128; i<160; i++) 
		for (int j=8; j<40; j++){
			I[i][j] = 0;
		}
  for (int i=128; i<160; i++) 
		for (int j=48; j<80; j++){
			I[i][j] = 0;
		}
  for (int i=128; i<160; i++) 
		for (int j=88; j<120; j++){
			I[i][j] = 0;
		}
  for (int i=128; i<160; i++) 
		for (int j=128; j<160; j++){
			I[i][j] = 0;
		}

  vpDisplayX d(I,290,360) ;
	vpDisplay::setTitle(I, "Question 6");
	vpDisplay::display(I);
	vpDisplay::flush(I) ;	
  vpDisplay::getClick(I);

  vpDisplay::close(I) ;

}

// QUESTION 7 : EFFET DE MASQUAGE
void question7(){
  int sIm;
  cout << "rentrer le parametre x : ";
	cin >> sIm; 

  vpImage<unsigned char> I = vpImage<unsigned char>(256,256);

  for(int i =0; i<256;i++){
    for(int j=0; j<128; j++){
      	I[i][j] = 255;
    }
  }

  vpUniRand rng;

  if(sIm%2==0){
    sIm = sIm/2;
    for(int j=128-sIm; j<128+sIm; j++){
      int bruit = rng.uniform(0,255);
      for(int i =0; i<256;i++){
      	I[i][j] = bruit;
      }
    }
  }else{
    sIm = sIm/2;
    for(int j=128-sIm; j<128+sIm-1; j++){
      int bruit = rng.uniform(0,255);
      for(int i =0; i<256;i++){
      	I[i][j] = bruit;
      }
    }
  }



  vpDisplayX d(I,256,256) ;
	vpDisplay::setTitle(I, "Question 7");
	vpDisplay::display(I);
	vpDisplay::flush(I) ;	
  vpDisplay::getClick(I);

  vpDisplay::close(I) ;


}


int main(int argc, char **argv)
{

  cout << "BINP TP1 : PERCEPTION VISUELLE " << endl ;
  cout << "--" << endl ;


  // creation du menu
  int choix=0;
  while(choix<7) {

    cout << "1. Limite de perception visuelle" <<endl ;
    cout << "2. Perception des couleurs"<<endl;
	  cout << "3. Illusion du gradient" << endl;
    cout << "4. Bandes de Mach"<<endl;
    cout << "5. Grille de Herman"<<endl;
    cout << "6. Effet de masquage"<<endl;
    cout << "7. Quitter"<<endl;

    cin >> choix ;

    switch(choix) {
    case 1:
      question2();
      break;

    case 2:
      question3();
      break;

    case 3:
      question4();
      break;

    case 4:
      question5();
      break;

    case 5:
      question6();
	  break;
	  
    case 6:
      question7();	  
	  
    default:
      break;
    }
  }

  cout << "Fin du programme " << endl ;
  return(0);
}















