
#include <iostream>
#include <string>
#include <fstream>
#include "construction.h"
#include <time.h>
#include <opengm/graphicalmodel/graphicalmodel_hdf5.hxx>

using namespace std;

int main()

{

    ifstream fichier("../sample/example_exe", ios::in);
    ifstream fichierH("../sample/example", ios::in);
    std::vector<std::string> instruction;
    std::string hamming ;

    if(fichier && fichierH)
    {
        getline(fichierH,hamming);
        for(int i = 0 ; i < 30 ; i++){
            string contenu;
            std::string token;
            getline(fichier, contenu);
            if(contenu[50]==' '){
                token = contenu.substr(51, contenu.size());
            }else if(contenu.at(60)==' '){
                token = contenu.substr(61, contenu.size());
            }else{
                token = contenu.substr(84, contenu.size());
            }
            instruction.push_back(token);
        }
        fichier.close();
    }

    else{

        cerr << "Error to open the input file!" << endl;
    }
    std::map<std::string,std::vector<std::vector<std::vector<float> > > > proba;
    std::map<std::string,std::vector<int> > link;
    std::vector<int> var;
    std::map<std::string,int> fonction ;
    std::map<std::string,std::vector<int> > paintext ;

    std::vector<int> textOne(4);
    textOne[0]=10;
    textOne[1]=50;
    textOne[2]=16;
    textOne[3]=50;

    std::vector<int> textTwo(4);
    textTwo[0]=13;
    textTwo[1]=67;
    textTwo[2]=17;
    textTwo[3]=67;

    paintext["R18"] = textOne;
    paintext["R19"] = textTwo;

    std::map<int,int > ciphertext ;
    ciphertext[28]=62;
    ciphertext[29]=233;

    std::map<int,std::vector <int> > box;
    std::vector<int> sbox= {99,124,119,123,242,107,111,197,48,1,103,43,254,215,171,118,202,130,201,125,250,89,71,240,173,212,162,175,156,164,114,192,183,253,147,38,54,63,247,204,52,165,229,241,113,216,49,21,4,199,35,195,24,150,5,154,7,18,128,226,235,39,178,117,9,131,44,26,27,110,90,160,82,59,214,179,41,227,47,132,83,209,0,237,32,252,177,91,106,203,190,57,74,76,88,207,208,239,170,251,67,77,51,133,69,249,2,127,80,60,159,168,81,163,64,143,146,157,56,245,188,182,218,33,16,255,243,210,205,12,19,236,95,151,68,23,196,167,126,61,100,93,25,115,96,129,79,220,34,42,144,136,70,238,184,20,222,94,11,219,224,50,58,10,73,6,36,92,194,211,172,98,145,149,228,121,231,200,55,109,141,213,78,169,108,86,244,234,101,122,174,8,186,120,37,46,28,166,180,198,232,221,116,31,75,189,139,138,112,62,181,102,72,3,246,14,97,53,87,185,134,193,29,158,225,248,152,17,105,217,142,148,155,30,135,233,206,85,40,223,140,161,137,13,191,230,66,104,65,153,45,15,176,84,187,22};

    box[21]=sbox;
    box[25]=sbox;

    std::cout << "Begin transformation "<< std::endl;
    transformationASM(instruction,proba,link,var,fonction,hamming,paintext,ciphertext,box,false,false);
    std::cout << "End transformationa "<< std::endl;

    Model gm = modelCreation(fonction,proba,link,var);
    // for write the hdf5 of the graph
    // std::cout << "Writing  "<< std::endl;
    // opengm::hdf5::save(gm,"graph_fantastic.h5","test");

    double elapsedTime;
    clock_t stopTime;
    clock_t startTime = clock();
    std::vector<std::string> output;
    beliefPropagation(gm,output,0,true);

    stopTime = clock();
    elapsedTime = (stopTime - startTime) / (CLOCKS_PER_SEC / (double) 1000.0);
    std::cout << "Time :"<<elapsedTime<< std::endl;
    ofstream fichierOut("../output", ios::out);

    if(fichierOut)
    {
        for(int i = 0 ; i < output.size() ; i++){
            fichierOut << output[i] << std::endl;
        }
        fichier.close();
    }
    else{

        cerr << "Error in output file!" << endl;
    }

    return 0;

}

