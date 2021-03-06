#include <iostream>
#include <string>
#include <fstream>
#include "construction.h"
#include <time.h>
#include <opengm/graphicalmodel/graphicalmodel_hdf5.hxx>

using namespace std;



int main()

{

    ifstream fichier("./fantastic_round1", ios::in);
    ifstream fichierH("./fantastic_round1_leak", ios::in);
    std::vector<std::string> instruction;
    std::string hamming ;


    if(fichier && fichierH)

    {
        getline(fichierH,hamming);
        for(int i = 0 ; i < 600 ; i++){

            string contenu;
            std::string token;
            getline(fichier, contenu);
            if(contenu[52]==' '){
                token = contenu.substr(53, contenu.size());


            }else if(contenu.at(60)==' '){
                token = contenu.substr(61, contenu.size());

            }else{
                token = contenu.substr(84, contenu.size());

            }
            // std::cout<<token<<std::endl;
            instruction.push_back(token);




        }
        fichier.close();

    }

    else{

        cerr << "Impossible d'ouvrir le fichier input!" << endl;
    }

    std::map<std::string,std::vector<std::vector<std::vector<float> > > > proba;
    std::map<std::string,std::vector<int> > link;
    std::vector<int> var;
    std::map<std::string,int> fonction ;
    std::map<std::string,std::vector<int> > select ;


    std::vector<int> plaintext(4);
    plaintext[0]=138;
    plaintext[1]=50;
    plaintext[2]=197;
    plaintext[3]=50;
    std::vector<int> plaintext2(4);
    plaintext2[0]=141;
    plaintext2[1]=67;
    plaintext2[2]=200;
    plaintext2[3]=67;
    std::vector<int> plaintext3(4);
    plaintext3[0]=144;
    plaintext3[1]=246;
    plaintext3[2]=203;
    plaintext3[3]=246;
    std::vector<int> plaintext4(4);
    plaintext4[0]=147;
    plaintext4[1]=168;
    plaintext4[2]=206;
    plaintext4[3]=168;
    std::vector<int> plaintext5(4);
    plaintext5[0]=150;
    plaintext5[1]=138;
    plaintext5[2]=209;
    plaintext5[3]=138;
    std::vector<int> plaintext6(4);
    plaintext6[0]=153;
    plaintext6[1]=90;
    plaintext6[2]=212;
    plaintext6[3]=90;
    std::vector<int> plaintext7(4);
    plaintext7[0]=156;
    plaintext7[1]=48;
    plaintext7[2]=215;
    plaintext7[3]=48;
    std::vector<int> plaintext8(4);
    plaintext8[0]=159;
    plaintext8[1]=141;
    plaintext8[2]=218;
    plaintext8[3]=141;
    std::vector<int> plaintext9(4);
    plaintext9[0]=162;
    plaintext9[1]=49;
    plaintext9[2]=221;
    plaintext9[3]=49;
    std::vector<int> plaintext10(4);
    plaintext10[0]=165;
    plaintext10[1]=49;
    plaintext10[2]=224;
    plaintext10[3]=49;
    std::vector<int> plaintext11(4);
    plaintext11[0]=168;
    plaintext11[1]=152;
    plaintext11[2]=227;
    plaintext11[3]=152;
    std::vector<int> plaintext12(4);
    plaintext12[0]=171;
    plaintext12[1]=162;
    plaintext12[2]=230;
    plaintext12[3]=162;
    std::vector<int> plaintext13(4);
    plaintext13[0]=174;
    plaintext13[1]=224;
    plaintext13[2]=233;
    plaintext13[3]=224;
    std::vector<int> plaintext14(4);
    plaintext14[0]=177;
    plaintext14[1]=55;
    plaintext14[2]=236;
    plaintext14[3]=55;
    std::vector<int> plaintext15(4);
    plaintext15[0]=180;
    plaintext15[1]=7;
    plaintext15[2]=239;
    plaintext15[3]=7;
    std::vector<int> plaintext16(4);
    plaintext16[0]=183;
    plaintext16[1]=52;
    plaintext16[2]=242;
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

    res[599]=76;
    res[592]=38;
    res[585]=6;
    res[578]=40;
    res[567]=122;
    res[560]=211;
    res[543]=248;
    res[546]=72;
    res[535]=154;
    res[528]=25;
    res[521]=203;
    res[514]=224;
    res[503]=229;
    res[496]=128;
    res[489]=102;
    res[482]=4;
    res[23]=103;


    std::map<int,std::vector <int> > box;
    std::vector<int> sbox= {99,124,119,123,242,107,111,197,48,1,103,43,254,215,171,118,202,130,201,125,250,89,71,240,173,212,162,175,156,164,114,192,183,253,147,38,54,63,247,204,52,165,229,241,113,216,49,21,4,199,35,195,24,150,5,154,7,18,128,226,235,39,178,117,9,131,44,26,27,110,90,160,82,59,214,179,41,227,47,132,83,209,0,237,32,252,177,91,106,203,190,57,74,76,88,207,208,239,170,251,67,77,51,133,69,249,2,127,80,60,159,168,81,163,64,143,146,157,56,245,188,182,218,33,16,255,243,210,205,12,19,236,95,151,68,23,196,167,126,61,100,93,25,115,96,129,79,220,34,42,144,136,70,238,184,20,222,94,11,219,224,50,58,10,73,6,36,92,194,211,172,98,145,149,228,121,231,200,55,109,141,213,78,169,108,86,244,234,101,122,174,8,186,120,37,46,28,166,180,198,232,221,116,31,75,189,139,138,112,62,181,102,72,3,246,14,97,53,87,185,134,193,29,158,225,248,152,17,105,217,142,148,155,30,135,233,206,85,40,223,140,161,137,13,191,230,66,104,65,153,45,15,176,84,187,22};
    std::vector<int> sbox2={0,2,4,6,8,10,12,14,16,18,20,22,24,26,28,30,32,34,36,38,40,42,44,46,48,50,52,54,56,58,60,62,64,66,68,70,72,74,76,78,80,82,84,86,88,90,92,94,96,98,100,102,104,106,108,110,112,114,116,118,120,122,124,126,128,130,132,134,136,138,140,142,144,146,148,150,152,154,156,158,160,162,164,166,168,170,172,174,176,178,180,182,184,186,188,190,192,194,196,198,200,202,204,206,208,210,212,214,216,218,220,222,224,226,228,230,232,234,236,238,240,242,244,246,248,250,252,254,27,25,31,29,19,17,23,21,11,9,15,13,3,1,7,5,59,57,63,61,51,49,55,53,43,41,47,45,35,33,39,37,91,89,95,93,83,81,87,85,75,73,79,77,67,65,71,69,123,121,127,125,115,113,119,117,107,105,111,109,99,97,103,101,155,153,159,157,147,145,151,149,139,137,143,141,131,129,135,133,187,185,191,189,179,177,183,181,171,169,175,173,163,161,167,165,219,217,223,221,211,209,215,213,203,201,207,205,195,193,199,197,251,249,255,253,243,241,247,245,235,233,239,237,227,225,231,229};

    box[255]=sbox;
    box[291]=sbox;
    box[323]=sbox;
    box[354]=sbox;

    box[395]=sbox;
    box[399]=sbox;
    box[403]=sbox;
    box[407]=sbox;
    box[412]=sbox;
    box[416]=sbox;
    box[420]=sbox;
    box[424]=sbox;
    box[429]=sbox;
    box[433]=sbox;
    box[438]=sbox;
    box[442]=sbox;
    box[447]=sbox;
    box[451]=sbox;
    box[455]=sbox;
    box[459]=sbox;

    box[478]=sbox2;
    box[485]=sbox2;
    box[492]=sbox2;
    box[499]=sbox2;
    box[510]=sbox2;
    box[517]=sbox2;
    box[524]=sbox2;
    box[531]=sbox2;
    box[542]=sbox2;
    box[549]=sbox2;
    box[556]=sbox2;
    box[563]=sbox2;
    box[574]=sbox2;
    box[581]=sbox2;
    box[588]=sbox2;
    box[595]=sbox2;





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
    ofstream fichierOut("../output", ios::out);



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


