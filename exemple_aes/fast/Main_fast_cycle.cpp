#include <iostream>
#include <string>
#include <fstream>
#include "construction.h"
#include <time.h>
#include <opengm/graphicalmodel/graphicalmodel_hdf5.hxx>

using namespace std;



int main()

{

    ifstream fichier("./Fast_Aes_Round1", ios::in);
    ifstream fichierH("./Fast_Aes_Round1_leak", ios::in);
    std::vector<std::string> instruction;
    std::string hamming ;


    if(fichier && fichierH)

    {
        getline(fichierH,hamming);
        for(int i = 0 ; i < 528 ; i++){

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

        cerr << "Impossible d'ouvrir le fichier !" << endl;
    }

    std::map<std::string,std::vector<std::vector<std::vector<float> > > > proba;
    std::map<std::string,std::vector<int> > link;
    std::vector<int> var;
    std::map<std::string,int> fonction ;
    std::map<std::string,std::vector<int> > select ;


    std::vector<int> plaintext(4);
    plaintext[0]=168;
    plaintext[1]=50;
    plaintext[2]=226;
    plaintext[3]=50;
    std::vector<int> plaintext2(4);
    plaintext2[0]=171;
    plaintext2[1]=67;
    plaintext2[2]=229;
    plaintext2[3]=67;
    std::vector<int> plaintext3(4);
    plaintext3[0]=174;
    plaintext3[1]=246;
    plaintext3[2]=232;
    plaintext3[3]=246;
    std::vector<int> plaintext4(4);
    plaintext4[0]=177;
    plaintext4[1]=168;
    plaintext4[2]=235;
    plaintext4[3]=168;
    std::vector<int> plaintext5(4);
    plaintext5[0]=180;
    plaintext5[1]=138;
    plaintext5[2]=238;
    plaintext5[3]=138;
    std::vector<int> plaintext6(4);
    plaintext6[0]=183;
    plaintext6[1]=90;
    plaintext6[2]=241;
    plaintext6[3]=90;
    std::vector<int> plaintext7(4);
    plaintext7[0]=186;
    plaintext7[1]=48;
    plaintext7[2]=244;
    plaintext7[3]=48;
    std::vector<int> plaintext8(4);
    plaintext8[0]=189;
    plaintext8[1]=141;
    plaintext8[2]=247;
    plaintext8[3]=141;
    std::vector<int> plaintext9(4);
    plaintext9[0]=192;
    plaintext9[1]=49;
    plaintext9[2]=250;
    plaintext9[3]=49;
    std::vector<int> plaintext10(4);
    plaintext10[0]=195;
    plaintext10[1]=49;
    plaintext10[2]=253;
    plaintext10[3]=49;
    std::vector<int> plaintext11(4);
    plaintext11[0]=198;
    plaintext11[1]=152;
    plaintext11[2]=256;
    plaintext11[3]=152;
    std::vector<int> plaintext12(4);
    plaintext12[0]=201;
    plaintext12[1]=162;
    plaintext12[2]=259;
    plaintext12[3]=162;
    std::vector<int> plaintext13(4);
    plaintext13[0]=204;
    plaintext13[1]=224;
    plaintext13[2]=262;
    plaintext13[3]=224;
    std::vector<int> plaintext14(4);
    plaintext14[0]=207;
    plaintext14[1]=55;
    plaintext14[2]=265;
    plaintext14[3]=55;
    std::vector<int> plaintext15(4);
    plaintext15[0]=210;
    plaintext15[1]=7;
    plaintext15[2]=268;
    plaintext15[3]=7;
    std::vector<int> plaintext16(4);
    plaintext16[0]=213;
    plaintext16[1]=52;
    plaintext16[2]=271;
    plaintext16[3]=52;

    select["R0"]=plaintext;
    select["R1"]=plaintext2;
    select["R2"]=plaintext3;
    select["R3"]=plaintext4;
    select["R4"]=plaintext5;
    select["R5"]=plaintext6;
    select["R6"]=plaintext7;
    select["R7"]=plaintext8;
    select["R8"]=plaintext9;
    select["R9"]=plaintext10;
    select["R10"]=plaintext11;
    select["R11"]=plaintext12;
    select["R12"]=plaintext13;
    select["R13"]=plaintext14;
    select["R14"]=plaintext15;
    select["R15"]=plaintext16;

    std::map<int,int > res ;
    res[525]=73;
    res[522]=80;
    res[519]=106;
    res[516]=2;
    res[513]=156;
    res[510]=76;
    res[509]=26;
    res[472]=67;
    res[458]=234;
    res[455]=53;
    res[451]=91;
    res[448]=107;
    res[445]=122;
    res[407]=249;
    res[393]=127;
    res[389]=159;
    res[23]=103;


    std::map<int,std::vector <int> > box;
    std::vector<int> sbox= {99,124,119,123,242,107,111,197,48,1,103,43,254,215,171,118,202,130,201,125,250,89,71,240,173,212,162,175,156,164,114,192,183,253,147,38,54,63,247,204,52,165,229,241,113,216,49,21,4,199,35,195,24,150,5,154,7,18,128,226,235,39,178,117,9,131,44,26,27,110,90,160,82,59,214,179,41,227,47,132,83,209,0,237,32,252,177,91,106,203,190,57,74,76,88,207,208,239,170,251,67,77,51,133,69,249,2,127,80,60,159,168,81,163,64,143,146,157,56,245,188,182,218,33,16,255,243,210,205,12,19,236,95,151,68,23,196,167,126,61,100,93,25,115,96,129,79,220,34,42,144,136,70,238,184,20,222,94,11,219,224,50,58,10,73,6,36,92,194,211,172,98,145,149,228,121,231,200,55,109,141,213,78,169,108,86,244,234,101,122,174,8,186,120,37,46,28,166,180,198,232,221,116,31,75,189,139,138,112,62,181,102,72,3,246,14,97,53,87,185,134,193,29,158,225,248,152,17,105,217,142,148,155,30,135,233,206,85,40,223,140,161,137,13,191,230,66,104,65,153,45,15,176,84,187};
    std::vector<int> sbox2={198,248,238,246,255,214,222,145,96,2,206,86,231,181,77,236,143,31,137,250,239,178,142,251,65,179,95,69,35,83,228,155,117,225,61,76,108,126,245,131,104,81,209,249,226,171,98,42,8,149,70,157,48,55,10,47,14,36,27,223,205,78,127,234,18,29,88,52,54,220,180,91,164,118,183,125,82,221,94,19,166,185,0,193,64,227,121,182,212,141,103,114,148,152,176,133,187,197,79,237,134,154,102,17,138,233,4,254,160,120,37,75,162,93,128,5,63,33,112,241,99,119,175,66,32,229,253,191,129,24,38,195,190,53,136,46,147,85,252,122,200,186,50,230,192,25,158,163,68,84,59,11,140,199,107,40,167,188,22,173,219,100,116,20,146,12,72,184,159,189,67,196,57,49,211,242,213,139,110,218,1,177,156,73,216,172,243,207,202,244,71,16,111,240,74,92,56,87,115,151,203,161,232,62,150,97,13,15,224,124,113,204,144,6,247,28,194,106,174,105,23,153,58,39,217,235,43,34,210,169,7,51,45,60,21,201,135,170,80,165,3,89,9,26,101,215,132,208,130,41,90,30,123,168,109};

    box[505]=sbox;
    box[279]=sbox;
    box[296]=sbox;
    box[303]=sbox;
    box[322]=sbox;
    box[335]=sbox;
    box[352]=sbox;
    box[359]=sbox;
    box[378]=sbox;
    box[394]=sbox;
    box[414]=sbox;
    box[421]=sbox;
    box[440]=sbox;
    box[459]=sbox;
    box[479]=sbox;
    box[486]=sbox;
    box[285]=sbox2;
    box[290]=sbox2;
    box[310]=sbox2;
    box[316]=sbox2;
    box[341]=sbox2;
    box[346]=sbox2;
    box[366]=sbox2;
    box[372]=sbox2;
    box[400]=sbox2;
    box[408]=sbox2;
    box[428]=sbox2;
    box[434]=sbox2;
    box[454]=sbox2;
    box[465]=sbox2;
    box[473]=sbox2;
    box[493]=sbox2;
    box[499]=sbox2;




    std::cout << "debut transformation "<< std::endl;

    transformationASM(instruction,proba,link,var,fonction,hamming,select,res,box,false,true);

    std::cout << "fini transformation "<< std::endl;

    Model gm = modelCreation(fonction,proba,link,var);

    double elapsedTime;
    clock_t stopTime;
    clock_t startTime = clock();
    std::vector<std::string> output;
    bool keyPosition = true;
     std::vector<int> nodeKey;
     nodeKey.push_back(6);
     nodeKey.push_back(7);
     nodeKey.push_back(8);
     nodeKey.push_back(9);
     nodeKey.push_back(10);
     nodeKey.push_back(11);
     nodeKey.push_back(12);
     nodeKey.push_back(13);
     nodeKey.push_back(14);
     nodeKey.push_back(15);
     nodeKey.push_back(16);
     nodeKey.push_back(17);
     nodeKey.push_back(18);
     nodeKey.push_back(19);
     nodeKey.push_back(20);
     nodeKey.push_back(21);

     beliefPropagation(gm,output,0,true,keyPosition,nodeKey);

    stopTime = clock();
    elapsedTime = (stopTime - startTime) / (CLOCKS_PER_SEC / (double) 1000.0);
    std::cout << "temp :"<<elapsedTime<< std::endl;
    ofstream fichierOut("../output_fast_cycle", ios::out);
    std::ostringstream timeTrans;
    timeTrans << elapsedTime;
    output.push_back(timeTrans.str());

    if(fichierOut)

    {
        for(int i = 0 ; i < output.size() ; i++){
            fichierOut << output[i] << std::endl;
        }
        fichier.close();

    }

    else{

        cerr << "Impossible d'ouvrir le fichier out!" << endl;
    }

    return 0;

}



