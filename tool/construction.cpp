#include "construction.h"
#include <opengm/inference/icm.hxx>
#include <opengm/graphicalmodel/graphicalmodel_hdf5.hxx>

Model modelCreation(std::map<std::__cxx11::string, int> fonctions,  std::map<std::__cxx11::string, std::vector<std::vector<std::vector<float> > > > &probaTab,
                    std::map<std::string,std::vector<int> > link, std::vector<int> var)
{

    opengm::DiscreteSpace<> space;
    for(int i =0 ; i < var.size() ;i++)
    {
        space.addVariable(var[i]);
        //std::cout <<" var "<< var[1]<<" ou var"<< var[0]<<std::endl;
    }
    Model gm(space);
    for(std::map<std::string,int>::iterator ii=fonctions.begin(); ii!=fonctions.end(); ++ii){

        if((*ii).second == 1){
            bool recherche = false;
            int variable = 0;
            std::vector<float> prob;
            for(std::map<std::string,std::vector<int> >::iterator it = link.begin();it!=link.end()|| !recherche;it++ ){
                if((*it).first == (*ii).first){
                    recherche=true;
                    variable=(*it).second[0];
                }

            }recherche =false;
            for(std::map<std::string,std::vector<std::vector<std::vector<float> > > > ::iterator it = probaTab.begin();it!=probaTab.end()|| !recherche;it++ ){
                if((*it).first == (*ii).first){
                    recherche=true;
                    prob = (*it).second[0][0];
                    probaTab.erase(it);

                }
            }
            fonctionPremier(&gm,prob,variable);

        }else if((*ii).second == 2){
            bool recherche = false;
            int variable[2] ={0,0} ;
            int cpt = 0;
            std::vector<std::vector<float> > prob;
            for(std::map<std::string,std::vector<int> >::iterator it = link.begin();it!=link.end()|| !recherche;it++ ){
                if((*it).first == (*ii).first){
                    variable[0]=(*it).second[0];
                    variable[1]=(*it).second[1];
                    cpt ++;

                    recherche =true;


                }

            }recherche =false;
            for(std::map<std::string,std::vector<std::vector<std::vector<float> > > > ::iterator it = probaTab.begin();it!=probaTab.end()|| !recherche;it++ ){
                if((*it).first == (*ii).first){
                    recherche=true;
                    prob = (*it).second[0];
                    probaTab.erase(it);
                }

            }
            int variableF[2];
            variableF[0]= variable[0];
            variableF[1]= variable[1];
            fonctionSecond(&gm,prob,variableF);

        }else if((*ii).second == 3){
            bool recherche = false;
            int variable[3] ={0,0,0} ;
            int cpt = 0;
            std::vector<std::vector<std::vector<float> > > prob;
            for(std::map<std::string,std::vector<int> >::iterator it = link.begin();it!=link.end()|| !recherche;it++ ){
                if((*it).first == (*ii).first){
                    variable[0]=(*it).second[0];
                    variable[1]=(*it).second[1];
                    variable[2]=(*it).second[2];
                    cpt ++;

                    recherche =true;


                }

            }recherche =false;
            for(std::map<std::string,std::vector<std::vector<std::vector<float> > > > ::iterator it = probaTab.begin();it!=probaTab.end()|| !recherche;it++ ){
                if((*it).first == (*ii).first){
                    recherche=true;
                    prob = (*it).second;
                    probaTab.erase(it);

                }

            }
            fonctionTroisieme(&gm,prob,variable);


        }else{
            std::cout << "n'a pas de variable ou en a plus que 3" <<std::endl;
        }

        /** std::cout << "nombre de fonction de degree 1 "<< gm.NrOfFunctionTypes << std::endl;
        std::cout <<" nombre de lien  "<< gm.numberOfFactors() << std::endl;
        std::cout <<" nombre de variable  "<< gm.numberOfVariables() << std::endl;

**/
    }


    return gm;
}

void fonctionPremier(Model * gm,std::vector<float> prob,int var ){
    typedef opengm::ExplicitFunction<float> ExplicitFunction;
    typedef Model::FunctionIdentifier FunctionIdentifier;
    const size_t shape[] = {gm->numberOfLabels(var)};
    ExplicitFunction f(shape, shape + 1);
    for(size_t state = 0; state < prob.size(); ++state) {
        f(state) = prob[state];
        // std::cout <<" state : "<< state << " " << prob[state]<< std::endl;
    }
    // add function
    FunctionIdentifier id = gm->addFunction(f);
    // add factor
    //std::cout<<"creation de la fonction "<< var << std::endl;
    size_t variableIndex[] = {var};
    gm->addFactor(id, variableIndex, variableIndex + 1);


}
void fonctionSecond(Model * gm,std::vector<std::vector<float> > prob,int var[]){ // a verif
    typedef opengm::ExplicitFunction<float> ExplicitFunction;
    typedef Model::FunctionIdentifier FunctionIdentifier;
    const size_t shape[] = {gm->numberOfLabels(var[0]),gm->numberOfLabels(var[1])};

    size_t variableIndex[2];
    int position[2];
    // add factorp
    if(var[0]<var[1]){
        variableIndex[0] =var[0];
        variableIndex[1]=var[1];
        position[0] = 0;
        position[1] = 1;
    }else{
        variableIndex[0] =var[1];
        variableIndex[1]=var[0];
        position[1] = 0;
        position[0] = 1;
    }
    ExplicitFunction f(shape, shape + 2);
    size_t state,stateD;
    size_t * probaPos[2]={&state,&stateD};
    for( state = 0; state < prob.size(); state++) {
        for( stateD = 0; stateD <prob[state].size();stateD++){
            if(prob[*probaPos[position[0]]][*probaPos[position[1]]])
                f(state,stateD) = prob[*probaPos[position[0]]][*probaPos[position[1]]];
        }

    }
    // add function
    FunctionIdentifier id = gm->addFunction(f);
    gm->addFactor(id, variableIndex, variableIndex + 2);


}
void fonctionTroisieme(Model * gm,std::vector<std::vector<std::vector<float> > > prob,int var[]){
    typedef opengm::ExplicitFunction<float> ExplicitFunction;
    typedef Model::FunctionIdentifier FunctionIdentifier;
    const size_t shape[] = {
        gm->numberOfLabels(var[0]),
        gm->numberOfLabels(var[1]),
        gm->numberOfLabels(var[2])
    };
    // construct 3rd order function

    // sequences of variable indices need to be (and in this case are) sorted

    size_t variableIndexSequence[3] ;
    int  position[3];

    variableIndexSequence[0]=var[0];
    variableIndexSequence[1]=var[1];
    variableIndexSequence[2]=var[2];
    position[0]=0;
    position[1]=1;
    position[2]=2;


    if(!(var[0]< var[1] && var[1] <var[2])){

        for(int tmp =0 ; tmp<2 ; tmp++){
            for(int a = 0 ; a <2 ; a++){
                if(variableIndexSequence[a]> variableIndexSequence[a+1]){
                    int b = variableIndexSequence[a];
                    variableIndexSequence[a]=variableIndexSequence[a+1];
                    variableIndexSequence[a+1]=b;
                    int tmpPosition = position[a];
                    position[a]= position[a+1];
                    position[a+1]=tmpPosition;



                }

            }


        }
    }
    int indice1 =gm->numberOfLabels(variableIndexSequence[0]);
    int indice2 =gm->numberOfLabels(variableIndexSequence[0]);
    int indice3 =gm->numberOfLabels(variableIndexSequence[0]);
    ExplicitFunction f(shape, shape + 3,0);
    size_t state1,state2,state3;
    size_t * proba1[3];
    proba1[0]=&state1;
    proba1[1]=&state2;
    proba1[2]=&state3;

    for( state1 = 0; state1 < indice1; ++state1)
        for( state2 = 0; state2 <indice2; ++state2)
            for( state3 = 0; state3 <indice3; ++state3) {
                if(prob[*proba1[position[0]]][*proba1[position[1]]][*proba1[position[2]]]>0.0){

                    f(state1, state2, state3) = prob[*proba1[position[0]]][*proba1[position[1]]][*proba1[position[2]]];
                }
            }
    FunctionIdentifier id = gm->addFunction(f);
    gm->addFactor(id, variableIndexSequence, variableIndexSequence + 3);

}


void beliefPropagation(Model gm, std::vector<std::__cxx11::string> &output, int iteration, bool allVariables, bool keyposition ,std::vector<int> nodeKey){
    typedef opengm::BeliefPropagationUpdateRules<Model, opengm::Maximizer> UpdateRules;
    typedef opengm::MessagePassing<Model, opengm::Maximizer, UpdateRules, opengm::MaxDistance> BeliefPropagation;
    typedef Model::IndependentFactorType IndependentFactor;
    const size_t maxNumberOfIterations = iteration;
    const double convergenceBound = 1e-7;
    const double damping =0.0;
    BeliefPropagation::Parameter parameter(maxNumberOfIterations, convergenceBound, damping);
    BeliefPropagation bp(gm, parameter);

    // optimize (approximately)
    BeliefPropagation::VerboseVisitorType visitor;
    std::cout << "debut optimisation"<< std::endl ;

    bp.infer();
    std::cout << "fin optimisation"<< std::endl ;

    // obtain the (approximate) argmax
    std::vector<size_t> labeling(gm.numberOfVariables());
    bp.arg(labeling);
    Model::IndependentFactorType IF;
    std::vector<std::vector<float>> listValue ;
    for(size_t variable = 0; variable < gm.numberOfVariables(); ++variable) {

        bp.marginal(variable,IF);
        std::vector<float> tmpValue;
        std::cout << "x" << variable << "=" << labeling[variable] <<"\n";
        std::ostringstream trans;
        trans << variable;
        std::ostringstream trans2;
        trans2 << labeling[variable];
        std::string tempo = "x"+trans.str();
        std::string tempo2 = "="+trans2.str();

        float cpt =0;
        output.push_back(tempo+tempo2);
        float borne = 0;

        for(int j=0;j<gm.numberOfLabels(variable);j++)
        {
            if(keyposition && std::find(nodeKey.begin(), nodeKey.end(),(int) variable) != nodeKey.end()){

                tmpValue.push_back((float)IF(j));
                //std::cout << tmpValue[tmpValue.size()] << " \n ";
            }


            if(IF(j)==0 || allVariables){


                std::cout<<"state: "<<j<<" probability value: "<<IF(j)<<" ; ";
                std::ostringstream buff1;
                buff1 << j;
                std::string blob = "state "+buff1.str();
                blob = blob+"probability value :";
                std::ostringstream buff;
                buff <<IF(j);
                std::string blob2 = buff.str();

                output.push_back(blob+blob2);
                std::cout<<"\n";

            }



        }
        if(keyposition && std::find(nodeKey.begin(), nodeKey.end(),(int) variable) != nodeKey.end()){
            listValue.push_back(tmpValue);
        }


        if(keyposition){
            translation(listValue);
        }


    }


}

void translation(std::vector<std::vector<float>> valeur){
    std::vector<std::string> output;
    for (int cpt = 0; cpt <= 5 ; cpt++){

        std::string ligne;
        if(cpt == 0){
            ligne ="scores_example.h \ndouble global_score_10[NB_SUBKEY_INIT][NB_KEY_VALUE_INIT] = {";

        }else if(cpt == 1){
            ligne ="double global_score_21[NB_SUBKEY_INIT][NB_KEY_VALUE_INIT] = {";

        }else if(cpt == 2){
            ligne ="double global_score_25[NB_SUBKEY_INIT][NB_KEY_VALUE_INIT] = {";

        }else if(cpt == 3){
            ligne ="double global_score_29[NB_SUBKEY_INIT][NB_KEY_VALUE_INIT] = {";

        }else if(cpt == 4){
            ligne ="double global_score_34[NB_SUBKEY_INIT][NB_KEY_VALUE_INIT] = {";

        }else{
            ligne ="double global_score_39[NB_SUBKEY_INIT][NB_KEY_VALUE_INIT] = {";

        }

        for(int i = 0; i < valeur.size(); i++){
            std::string par = "{";
            ligne += par;
            for(int p = 0 ; p < valeur[i].size() ; p++){
                std::ostringstream buff;
                buff << valeur[i][p];
                std::string tmp = buff.str();
                ligne += tmp;
                if(p<valeur[i].size()-1){
                    ligne += ",";
                }


            }
            par = "}";
            ligne += par;
            if(i<valeur.size()-1){
                ligne += ",";
            }


        }
        std::string par = "}";
        ligne += par;

        output.push_back(ligne);
    }
    std::ofstream fichierOut("../scores_example_data", std::ios::out);

    if(fichierOut)
    {
        for(int i = 0 ; i < output.size() ; i++){
            fichierOut << output[i] << std::endl;
        }
        fichierOut.close();
    }
    else{

        std::cerr << "Error in output file!" << std::endl;
    }

}
std::map<std::string, int> transformationASM(std::vector<std::string> contenue,std::map<std::string, std::vector<std::vector<std::vector<float> > > > &probaTab,  std::map<std::string,std::vector<int> > &link,std::vector<int> &var,std::map<std::__cxx11::string, int> &fonctions, std::string hammingweight , std::map<std::string,std::vector<int> > valeurFixer,std::map<int,int >valeurResultat,std::map<int,std::vector<int> > box,bool graph,bool cycle){


    std::map<std::string,int> instruction ;



    std::map<std::string,int> traitement;
    instructionTaken(instruction,traitement);


    std::map<std::string,std::vector<int> > RegY ;
    std::map<std::string,std::vector<int> > RegX ;
    std::map<std::string,std::vector<int> > RegZ ;
    int cursorRegX= 0;
    int cursorRegY= 0;
    int cursorRegZ= 0;
    int cursorLDRegX= 0;
    int cursorLDRegY= 0;
    int cursorLDRegZ= 0;
    std::vector<int> stockR30 ;
    std::vector<int>  stockR28;
    std::vector<int> stockR26;
    std::vector<int> stockLPMR30 ;
    std::vector<int>  stockLPMR28;
    std::vector<int> stockLPMR26;
    std::string nameRegX= "";
    std::string nameRegY= "";
    std::string nameRegZ= "";

    int nbLabel;
    if(graph){
        nbLabel = 1;
    }
    else{
        nbLabel=256;
    }

    std::map<std::string,int> varIndex;
    std::map<int,std::vector<std::string> > varFonc;



    for(int i = 0 ; i < contenue.size(); i++){
        bool LPMReg = false;
        int idLPMReg = 0;
        std::string key =contenue[i].substr(0,contenue[i].find(" "));
        if(instruction.find(key)!= instruction.end()){


            std::string nomFonction = key;
            std::string tmpConca = boost::lexical_cast<std::string>(i);

            nomFonction= nomFonction+tmpConca;


            std::vector<int> lienF;

            std::string ligneEnCours;
            ligneEnCours = contenue[i].substr(contenue[i].find(" ")+1);
            int ValeurKey = instruction[key];
            if(instruction[key]>3){
                hammingInstructionIteration(key,ValeurKey,hammingweight,contenue,i,instruction);

            }if(key =="MOV"){
                hammingweight=hammingweight.substr(hammingweight.find(",")+1);

                ValeurKey=1;
            }
            fonctions[nomFonction]=ValeurKey;
            std::vector<std::vector<float > > tabProbFonc;
            /*bool valueZ= false;
            bool valueX= false;
            bool valueY= false;*/

            for(int j = 0 ; j< ValeurKey; j++){
                std::string nomVar;
                std::string nomVarMov;


                std::vector<float> variableProb(nbLabel);
                if(key == "MOV"){
                    nomVarMov=ligneEnCours.substr(0,ligneEnCours.find(","));
                    int posi = ligneEnCours.find(",")+2;
                    nomVar = ligneEnCours.substr(ligneEnCours.find(",")+2,ligneEnCours.substr(0,posi).find(" "));
                    if(nomVar[nomVar.size()-1] ==' '){
                        nomVar = nomVar.substr(0,nomVar.size()-1);
                    }
                    if(nomVar[nomVar.size()-2] ==' '){
                        nomVar = nomVar.substr(0,nomVar.size()-2);
                    }


                }
                else if(j == 0 ){
                    nomVar = ligneEnCours.substr(0,ligneEnCours.find(","));

                }else if(j == 1 ){
                    int posi = ligneEnCours.find(",")+2;
                    nomVar = ligneEnCours.substr(ligneEnCours.find(",")+2,ligneEnCours.substr(0,posi).find(" "));
                    if(nomVar[nomVar.size()-1] ==' '){
                        nomVar = nomVar.substr(0,nomVar.size()-1);
                    }
                    if(nomVar[nomVar.size()-2] ==' '){
                        nomVar = nomVar.substr(0,nomVar.size()-2);
                    }

                }else{
                    // a definir si utile
                    /*    if(valueX){
                        nomVar="R26";

                    }else if(valueY){
                        nomVar="R28";

                    }else if(valueZ){
                        nomVar="R30";

                    }else{*/
                    nomVar = ligneEnCours.substr(0,ligneEnCours.find(","));
                    //}
                }
                // a définir si utile
                if( std::string::npos  != nomVar.find("Z")){
                    //  valueZ=true;
                    if(ValeurKey == 1){
                        nomVar = ligneEnCours.substr(ligneEnCours.find(",")+2,ligneEnCours.find(" "));
                        if(nomVar[nomVar.size()-1] ==' '){
                            nomVar = nomVar.substr(0,nomVar.size()-1);
                        }

                    }else{
                        nomVar="R31";

                    }



                }else if(std::string::npos != nomVar.find("Y")){
                    //  valueY=true;
                    if(ValeurKey == 1 ){
                        nomVar = ligneEnCours.substr(ligneEnCours.find(",")+2,ligneEnCours.find(" "));
                        if(nomVar[nomVar.size()-1] ==' '){
                            nomVar = nomVar.substr(0,nomVar.size()-1);
                        }
                    }else{
                        nomVar="R29";

                    }

                }else if(std::string::npos != nomVar.find("X")){
                    //    valueX=true;
                    if(ValeurKey == 1){
                        nomVar = ligneEnCours.substr(ligneEnCours.find(",")+2,ligneEnCours.find(" "));
                        if(nomVar[nomVar.size()-1] ==' '){
                            nomVar = nomVar.substr(0,nomVar.size()-1);
                        }
                    }else{
                        nomVar="R27";

                    }
                }


                if(varIndex.find(nomVar)!=varIndex.end() && (j < ValeurKey-1 || key =="OUT" || key =="ST"|| key =="STD"|| key =="CPI"|| key=="MOV" || key=="CPC")){


                    int id =varIndex[nomVar];
                    std::map<std::string,int> vue;

                    bool me =false ;
                    if(!cycle){
                       me = findCycle(varFonc,link,nomFonction,id,vue);
                    }else{
                        me = findLittleCycle(varFonc,nomFonction,id);

                    }

                    if(me){
                        std::cout << "var " << nomVar <<" remplacer du a un cycle en " << nomFonction<<std::endl;
                        var.push_back(nbLabel);
                        varIndex[nomVar]=var.size()-1;
                        lienF.push_back(var.size()-1);
                        std::vector<std::string> vec;
                        vec.push_back(nomFonction);
                        varFonc[var.size()-1]=vec;

                    }else{
                        lienF.push_back(id);
                        varFonc[id].push_back(nomFonction);
                        if(key=="MOV"){
                            varIndex[nomVarMov]=id;

                        }
                        if(key=="ST" || key=="STD"){
                            std::string verif = ligneEnCours.substr(0,ligneEnCours.find(","));
                            if(verif.find("Y") != std::string::npos){

                                if(nameRegY != ""){
                                    if(key == "STD"){
                                        int index = ligneEnCours.find("+");
                                        RegY[nameRegY][cursorLDRegY+std::atoi(ligneEnCours.substr(index+1,index+2).c_str())] = id;

                                    }
                                    else{RegY[nameRegY].push_back(id);
                                        cursorRegY++;}
                                }

                            }else if(verif.find("X") !=std::string::npos){
                                if(nameRegX != ""){
                                    if(key == "STD"){
                                        int index = ligneEnCours.find("+");
                                        RegX[nameRegX][cursorLDRegX+std::atoi(ligneEnCours.substr(index+1,index+2).c_str())] = id;

                                    }
                                    else{
                                        RegX[nameRegX].push_back(id);
                                        cursorRegX++;}
                                }


                            }else if(verif.find("Z") != std::string::npos){
                                if(nameRegZ != ""){
                                    if(key == "STD"){
                                        int index = ligneEnCours.find("+");
                                        RegZ[nameRegZ][cursorLDRegZ+std::atoi(ligneEnCours.substr(index+1,index+2).c_str())] = id;

                                    }
                                    else{
                                        RegZ[nameRegZ].push_back(id);
                                        cursorRegZ++;
                                    }
                                }


                            }
                        }
                    }

                }else{
                    bool me = true;
                    int  id = 0;
                    if(key == "LD" || key =="LDD"){
                        std::string verif = ligneEnCours.substr(ligneEnCours.find(",")+2,ligneEnCours.find(" "));

                        if(verif.find("Y") != std::string::npos ){
                            if(nameRegY != ""){
                                if(key == "LDD"){
                                    int index = ligneEnCours.find("+");
                                    int tmpid =RegY[nameRegY][cursorLDRegY+std::atoi(ligneEnCours.substr(index+1,index+2).c_str())];
                                    id = tmpid;
                                }else{
                                    id =RegY[nameRegY][cursorLDRegY];
                                    if(verif.find("+") != std::string::npos ){
                                        cursorLDRegY++;

                                    }else if(verif.find("-") != std::string::npos ){
                                        cursorLDRegY--;

                                    }
                                }

                            }

                        }else if(verif.find("X") != std::string::npos){
                            if(nameRegX != ""){
                                if(key == "LDD"){
                                    int index = ligneEnCours.find("+");
                                    int tmpid =RegX[nameRegX][cursorLDRegX+std::atoi(ligneEnCours.substr(index+1,index+2).c_str())];
                                    id = tmpid;
                                }
                                else{
                                    id =RegY[nameRegX][cursorLDRegX];
                                    if(verif.find("+") != std::string::npos ){
                                        cursorLDRegX++;

                                    }else if(verif.find("-") != std::string::npos ){
                                        cursorLDRegX--;

                                    }
                                }

                            }


                        }else if(verif.find("Z") != std::string::npos){
                            if(nameRegZ != ""){
                                if(key == "LDD"){
                                    int index = ligneEnCours.find("+");
                                    id =RegZ[nameRegZ][cursorLDRegZ+std::atoi(ligneEnCours.substr(index+1,index+2).c_str())];
                                }
                                else{
                                    id =RegZ[nameRegZ][cursorLDRegZ];
                                    if(verif.find("+") != std::string::npos ){
                                        cursorLDRegZ++;

                                    }else if(verif.find("-") != std::string::npos ){
                                        cursorLDRegZ--;

                                    }
                                }

                            }


                        }else{
                            std::cout << "erreur sur les registre Y X Z "<< std::endl;

                        }
                        std::map<std::string,int> vue;
                        me = false ;
                        if(!cycle){
                            me=findCycle(varFonc,link,nomFonction,id,vue);
                        }else{
                            me = findLittleCycle(varFonc,nomFonction,id);

                        }




                    }if(!me){

                        lienF.push_back(id);
                        varFonc[id].push_back(nomFonction);
                        varIndex[nomVar]=id;

                    }else{
                        if(key == "LPM" && (nomVar == "R28" ||nomVar == "R30" || nomVar =="R26" )){
                            LPMReg = true;
                            idLPMReg = varIndex[nomVar];
                        }


                        var.push_back(nbLabel);
                        varIndex[nomVar]=var.size()-1;
                        lienF.push_back(var.size()-1);
                        std::vector<std::string> vec;
                        vec.push_back(nomFonction);
                        varFonc[var.size()-1]=vec;
                        if(key == "SBIW"){
                            int diff = std::atoi(ligneEnCours.substr(ligneEnCours.find(",")+2,ligneEnCours.find(" ")).c_str());

                            if(nomVar == "R28"){
                                cursorRegY -= diff;

                            }else if (nomVar=="R30") {
                                cursorRegZ=-diff;


                            }

                        }else if(key =="ADIW"){
                            int add = std::atoi(ligneEnCours.substr(ligneEnCours.find(",")+2,ligneEnCours.find(" ")).c_str());

                            if(nomVar == "R28"){
                                cursorRegY+=add;

                            }else if (nomVar=="R30") {
                                cursorRegZ += add;

                            }


                        }

                        if(key=="LDI"){
                            if(nomVar =="R26"){
                                if(RegX.find(ligneEnCours.substr(ligneEnCours.find(",")+2,ligneEnCours.find(" "))) == RegX.end()){

                                    RegX[nameRegX]= std::vector<int>(0);

                                }
                                nameRegX = ligneEnCours.substr(ligneEnCours.find(",")+2,ligneEnCours.find(" "));
                                cursorRegX = 0;


                            }
                            else if(nomVar=="R28"){

                                if(RegY.find(ligneEnCours.substr(ligneEnCours.find(",")+2,ligneEnCours.find(" "))) == RegY.end()){
                                    nameRegY = ligneEnCours.substr(ligneEnCours.find(",")+2,ligneEnCours.find(" "));
                                    cursorRegY = 0;
                                    RegY[nameRegY]= std::vector<int>(0);



                                }



                            }
                            else if(nomVar=="R30"){
                                if(RegZ.find(ligneEnCours.substr(ligneEnCours.find(",")+2,ligneEnCours.find(" "))) == RegZ.end()){
                                    RegZ[nameRegZ]= std::vector<int>(0);


                                }
                                nameRegZ = ligneEnCours.substr(ligneEnCours.find(",")+2,ligneEnCours.find(" "));

                                cursorRegZ = 0;


                            }

                        }
                    }



                }

                std::string poid = hammingweight.substr(0,hammingweight.find(","));
                hammingweight=hammingweight.substr(hammingweight.find(",")+1);
                int value = std::atoi(poid.c_str());
                std::vector<int> valueH;
                bool findValuer =false;

                if(valeurFixer.find(nomVar) != valeurFixer.end() && (j < ValeurKey-1 || key == "LPM")){
                    for(int f = 0 ; f< valeurFixer[nomVar].size()-1 && !findValuer; f=f+2 ){
                        if(valeurFixer[nomVar][f] == i){
                            valueH.push_back(valeurFixer[nomVar][f+1]);
                            findValuer=true;
                        }
                    }




                }else if(j== ValeurKey-1 && valeurResultat.find(i) != valeurResultat.end()){
                    valueH.push_back(valeurResultat[i]);
                    findValuer=true;


                }

                if( !findValuer){
                    if(value == 0){
                        valueH.push_back(0);
                    }else{
                        valueH = hammingToDecimal(value);
                    }
                }
                if(nomVar == "R30" || nomVar == "R28" || nomVar =="R26" || key == "MOV" && (nomVarMov == "R30"|| nomVarMov=="R26"|| nomVarMov=="R28")){
                    if(nomVar =="R30"|| nomVarMov=="R30"){
                        if(LPMReg){
                            stockLPMR30=stockR30;

                        }
                        stockR30 = valueH;

                    }else if(nomVar =="R28"|| nomVarMov=="R28"){
                        if(LPMReg){
                            stockLPMR28=stockR28;

                        }

                        stockR28 = valueH;
                    }else {
                        if(LPMReg){
                            stockLPMR26=stockR26;

                        }
                        stockR26 = valueH;
                    }

                }
                for(int cpt = 0 ; cpt<nbLabel ; cpt++){

                    bool trouver = false;
                    for(int taille = 0 ; taille < valueH.size() && !trouver;taille++){
                        if(cpt==valueH[taille]){
                            variableProb[cpt]=(1.0/valueH.size());
                            trouver =true;
                        }
                    }
                    if(!trouver){
                        variableProb[cpt]=0;
                    }



                }
                tabProbFonc.push_back(variableProb);



            }
            if(ValeurKey != 0){
                if(ValeurKey==3){
                    std::vector<std::vector<std::vector<float> > > tmpProba(nbLabel);
                   specialInstruction(key,traitement,tmpProba,tabProbFonc,nbLabel);
                    probaTab[nomFonction]=tmpProba;
                }else if(ValeurKey==2){
                    std::vector<std::vector<std::vector<float> > > tmpProba(1);

                    std::vector<std::vector<float> > tmp(nbLabel);
                    tmpProba[0]=tmp;
                    for(int cpt2=0 ;cpt2 <nbLabel ; cpt2++){
                        std::vector<float> tmp2(nbLabel);
                        tmpProba[0][cpt2]=tmp2;
                        for(int cpt3=0; cpt3<nbLabel; cpt3++){
                            tmpProba[0][cpt2][cpt3]= tabProbFonc[0][cpt2]*tabProbFonc[1][cpt3];
                        }
                    }

                    probaTab[nomFonction]=tmpProba;

                }else{

                    std::vector<std::vector<std::vector<float> > > tmpProba(1);
                    standartInstruction(key,tmpProba,nbLabel,fonctions,nomFonction,tabProbFonc,stockR30,stockR28,stockR26,stockLPMR30,stockLPMR28,stockLPMR26,varIndex,varFonc,i,LPMReg,idLPMReg,ligneEnCours,box,lienF);




                    probaTab[nomFonction]=tmpProba;

                }

                link[nomFonction]=lienF;
            }




        }else {
            std::cout << "instruction non prise en compre "<< key << std::endl;
        }

    }


    return varIndex;


}
bool findCycle(std::map<int,std::vector<std::string> > varFonc, std::map<std::string,std::vector<int> > link, std::string cible, int id , std::map<std::__cxx11::string, int> &vue)
{
    std::vector<std::string>  fonctionTmp = varFonc[id];

    bool parcour = false;
    for (int i = 0 ; i< fonctionTmp.size() && !parcour ;i++){
        if(vue.find(fonctionTmp[i])==vue.end()){
            vue[fonctionTmp[i]]=1;
            if(fonctionTmp[i] == cible){
                parcour= true;
            }
            std::vector<int> lien =  link[fonctionTmp[i]];

            for(int  j = 0 ; j< lien.size() && !parcour;j++){
                if(lien[j]!=id && varFonc[lien[j]].size() > 1){
                    std::map<int,std::vector<std::string> > tmp = varFonc;
                    std::map<int,std::vector<std::string> >::iterator it =tmp.begin();
                    while(it != tmp.end()){
                        if(it->first == id){
                            std::map<int,std::vector<std::string> >::iterator erase=it;
                            ++it;
                            tmp.erase(erase);
                        }else{
                            ++it;
                        }
                    }


                    parcour = findCycle(tmp,link,cible,lien[j],vue);
                }




            }
        }

    }
    return parcour;


}

bool findLittleCycle(std::map<int,std::vector<std::string> > varFonc, std::string cible, int id )
{
    std::vector<std::string>  fonctionTmp = varFonc[id];

    bool parcour = false;
    for (int i = 0 ; i< fonctionTmp.size() && !parcour ;i++){
            if(fonctionTmp[i] == cible){
                parcour= true;
            }





    }
    return parcour;


}
std::vector<int> hammingToDecimal(int h){
    std::vector<int> value;
    for (int i = 0 ;  i < 256 ; i++){
        if(NumberOfSetBits(i) == h){
            value.push_back(i);

        }
    }
    return value;
}
int NumberOfSetBits(int i)
{

    i = i - ((i >> 1) & 0x55555555);
    i = (i & 0x33333333) + ((i >> 2) & 0x33333333);
    return (((i + (i >> 4)) & 0x0F0F0F0F) * 0x01010101) >> 24;
}


void hammingInstructionIteration( std::string key,int &ValeurKey , std::string &hammingweight ,std::vector<std::string> contenue,int i ,std::map<std::string,int> instruction){
    if(instruction[key]>4 && instruction[key]<6){

        if( std::string::npos  != contenue[i].find("Z+")||std::string::npos  != contenue[i].find("X+")||std::string::npos  != contenue[i].find("Y+")){
            hammingweight=hammingweight.substr(hammingweight.find(",")+1);
            hammingweight=hammingweight.substr(hammingweight.find(",")+1);
            std::string tempo = hammingweight.substr(0,hammingweight.find(","));
            hammingweight=hammingweight.substr(hammingweight.find(",")+1);
            hammingweight=hammingweight.substr(hammingweight.find(",")+1);
            hammingweight=hammingweight.substr(hammingweight.find(",")+1);
            hammingweight = tempo+","+hammingweight;
            ValeurKey=1;


        }else{
            hammingweight=hammingweight.substr(hammingweight.find(",")+1);
            std::string tempo = hammingweight.substr(0,hammingweight.find(","));
            hammingweight=hammingweight.substr(hammingweight.find(",")+1);
            hammingweight=hammingweight.substr(hammingweight.find(",")+1);
            hammingweight = tempo+","+hammingweight;
            ValeurKey=1;

        }

    }else if(instruction[key] > 6 || key =="RET"){
        for (int compteur = 0 ; compteur< instruction[key]; compteur++){
            hammingweight=hammingweight.substr(hammingweight.find(",")+1);

        }
        ValeurKey=0;



    }else if(key =="SBIW" || key =="ADIW" || key =="MOVW"){
        hammingweight=hammingweight.substr(hammingweight.find(",")+1);
        hammingweight=hammingweight.substr(hammingweight.find(",")+1);
        std::string tempo = hammingweight.substr(0,hammingweight.find(","));
        hammingweight=hammingweight.substr(hammingweight.find(",")+1);
        hammingweight=hammingweight.substr(hammingweight.find(",")+1);
        hammingweight = tempo+","+hammingweight;
        ValeurKey=1;
    }

    else{
        hammingweight=hammingweight.substr(hammingweight.find(",")+1);
        std::string tempo = hammingweight.substr(0,hammingweight.find(","));
        hammingweight=hammingweight.substr(hammingweight.find(",")+1);
        hammingweight=hammingweight.substr(hammingweight.find(",")+1);
        hammingweight = tempo+","+hammingweight;
        ValeurKey=1;
    }
}


void instructionTaken(std::map<std::string, int> &instruction , std::map<std::string, int> &traitement){
    instruction["ADD"]=3;
    instruction["ADIW"]= 4;
    instruction["ADC"]=3;
    instruction["LDI"]=1;
    instruction["OUT"]=2;
    instruction["EOR"]=3;
    instruction["CPI"]=1;
    instruction["CPC"]=2;
    instruction["LPM"]=5;
    instruction["MOV"]=2;
    instruction["MOVW"]=2;
    instruction["LDD"]=4;
    instruction["ANDI"]=2;
    instruction["SBCI"]=2;
    instruction["STD"]=4;
    instruction["RCALL"]= 34;
    instruction["CALL"]= 34;
    instruction["SBSR"]= 1;
    instruction["SBIW"]= 4;
    instruction["DEC"]= 2;
    instruction["ST"]=5;
    instruction["LD"]=5;
    instruction["RET"]=4;
    instruction["SUB"]=3;
    instruction["AND"]=3;
    traitement["ADD"]=0;
    traitement["EOR"]=1;
    traitement["SUB"]=2;
    traitement["AND"]=3;
}

void specialInstruction(std::string key, std::map<std::string,int> traitement, std::vector<std::vector<std::vector<float> > > &tmpProba , std::vector<std::vector<float > > tabProbFonc, int nbLabel){
    if(traitement.find(key) != traitement.end()){
        int nombreExis = 0;
        switch(traitement[key])
        {

        case 0:

            for(int cpt=0 ; cpt < nbLabel; cpt++){
                std::vector<std::vector<float> >  tmp(nbLabel);
                tmpProba[cpt]=tmp;
                for(int cpt2=0 ;cpt2 <nbLabel ; cpt2++){
                    std::vector<float> tmp2(nbLabel);
                    tmpProba[cpt][cpt2]=tmp2;
                    for(int cpt3=0; cpt3<nbLabel; cpt3++){
                        if(tabProbFonc[0][cpt] != 0 && tabProbFonc[1][cpt2] != 0 && tabProbFonc[2][cpt3]!= 0){

                            if((cpt + cpt2) == cpt3){
                                tmpProba[cpt][cpt2][cpt3]= 1;
                                nombreExis++;



                            }

                        }else{
                            tmpProba[cpt][cpt2][cpt3]=0;
                        }

                    }
                }
            }
            for(int cpt=0 ; cpt < nbLabel; cpt++){
                for(int cpt2=0 ;cpt2 <nbLabel ; cpt2++){
                    for(int cpt3=0; cpt3<nbLabel; cpt3++){
                        if(tmpProba[cpt][cpt2][cpt3] == 1){
                            tmpProba[cpt][cpt2][cpt3]= 1.0/nombreExis;
                        }
                    }
                }
            }

            break;
        case 1:
            for(int cpt=0 ; cpt < nbLabel; cpt++){
                std::vector<std::vector<float> >  tmp(nbLabel);
                tmpProba[cpt]=tmp;
                for(int cpt2=0 ;cpt2 <nbLabel ; cpt2++){
                    std::vector<float> tmp2(nbLabel);
                    tmpProba[cpt][cpt2]=tmp2;
                    for(int cpt3=0; cpt3<nbLabel; cpt3++){
                        if(tabProbFonc[0][cpt] != 0 && tabProbFonc[1][cpt2] != 0 && tabProbFonc[2][cpt3]!= 0){
                            int xortmp = cpt;
                            xortmp ^=cpt2;
                            if(xortmp == cpt3){
                                tmpProba[cpt][cpt2][cpt3]= 1;
                                nombreExis++;


                            }

                        }
                        else{
                            tmpProba[cpt][cpt2][cpt3]=0;
                        }

                    }
                }
            }
            for(int cpt=0 ; cpt < nbLabel; cpt++){
                for(int cpt2=0 ;cpt2 <nbLabel ; cpt2++){
                    for(int cpt3=0; cpt3<nbLabel; cpt3++){
                        if(tmpProba[cpt][cpt2][cpt3] == 1){
                            tmpProba[cpt][cpt2][cpt3]= 1.0/nombreExis;
                        }
                    }
                }
            }
            break;
        case 2:
            for(int cpt=0 ; cpt < nbLabel; cpt++){
                std::vector<std::vector<float> >  tmp(nbLabel);
                tmpProba[cpt]=tmp;
                for(int cpt2=0 ;cpt2 <nbLabel ; cpt2++){
                    std::vector<float> tmp2(nbLabel);
                    tmpProba[cpt][cpt2]=tmp2;
                    for(int cpt3=0; cpt3<nbLabel; cpt3++){
                        if(tabProbFonc[0][cpt] != 0 && tabProbFonc[1][cpt2] != 0 && tabProbFonc[2][cpt3]!= 0){

                            if((cpt-cpt2) == cpt3){
                                tmpProba[cpt][cpt2][cpt3]= 1;
                                nombreExis++;


                            }

                        }
                        else{
                            tmpProba[cpt][cpt2][cpt3]=0;
                        }

                    }
                }
            }
            for(int cpt=0 ; cpt < nbLabel; cpt++){
                for(int cpt2=0 ;cpt2 <nbLabel ; cpt2++){
                    for(int cpt3=0; cpt3<nbLabel; cpt3++){
                        if(tmpProba[cpt][cpt2][cpt3] == 1){
                            tmpProba[cpt][cpt2][cpt3]= 1.0/nombreExis;
                        }
                    }
                }
            }
            break;
        case 3:
            for(int cpt=0 ; cpt < nbLabel; cpt++){
                std::vector<std::vector<float> >  tmp(nbLabel);
                tmpProba[cpt]=tmp;
                for(int cpt2=0 ;cpt2 <nbLabel ; cpt2++){
                    std::vector<float> tmp2(nbLabel);
                    tmpProba[cpt][cpt2]=tmp2;
                    for(int cpt3=0; cpt3<nbLabel; cpt3++){
                        if(tabProbFonc[0][cpt] != 0 && tabProbFonc[1][cpt2] != 0 && tabProbFonc[2][cpt3]!= 0){
                            int andTmp = cpt;
                            andTmp &=cpt2;
                            if(andTmp == cpt3){
                                tmpProba[cpt][cpt2][cpt3]= 1;
                                nombreExis++;


                            }

                        }
                        else{
                            tmpProba[cpt][cpt2][cpt3]=0;
                        }

                    }
                }
            }
            for(int cpt=0 ; cpt < nbLabel; cpt++){
                for(int cpt2=0 ;cpt2 <nbLabel ; cpt2++){
                    for(int cpt3=0; cpt3<nbLabel; cpt3++){
                        if(tmpProba[cpt][cpt2][cpt3] == 1){
                            tmpProba[cpt][cpt2][cpt3]= 1.0/nombreExis;
                        }
                    }
                }
            }

            break;


        default:
            std::cout << "error isntruction \n";
        }

    }else {


        for(int cpt=0 ; cpt < nbLabel; cpt++){
            std::vector<std::vector<float> >  tmp(nbLabel);
            tmpProba[cpt]=tmp;
            for(int cpt2=0 ;cpt2 <nbLabel ; cpt2++){
                std::vector<float> tmp2(nbLabel);
                tmpProba[cpt][cpt2]=tmp2;
                for(int cpt3=0; cpt3<nbLabel; cpt3++){
                    tmpProba[cpt][cpt2][cpt3]= tabProbFonc[0][cpt]*tabProbFonc[1][cpt2]*tabProbFonc[2][cpt3];

                }
            }
        }
    }
}

void standartInstruction(std::string key,std::vector<std::vector<std::vector<float> > > &tmpProba,int nbLabel,std::map<std::__cxx11::string, int> &fonctions, std::string nomFonction , std::vector<std::vector<float > > tabProbFonc, std::vector<int> stockR30,std::vector<int>  stockR28,std::vector<int> stockR26,std::vector<int> stockLPMR30,std::vector<int>  stockLPMR28,std::vector<int> stockLPMR26,std::map<std::string,int> varIndex,std::map<int,std::vector<std::string> > &varFonc,int i,bool LPMReg ,int idLPMReg,std::string ligneEnCours,std::map<int,std::vector<int> > box,  std::vector<int>& lienF){
    std::vector<std::vector<float> > tmp(1);
    tmpProba[0]=tmp;

    std::vector<float> tmp2(nbLabel);
    tmpProba[0][0]= tmp2;
    if(key == "LPM"&& box.find(i) != box.end() ){
        fonctions[nomFonction]=2;
        int iden;
        std::vector<std::vector<float> > tmp3(nbLabel);
        tmpProba[0] = tmp3;
        for(int att = 0 ; att < nbLabel ; att ++){
            std::vector<float>  tmp4(nbLabel);
            tmpProba[0][att]=tmp4;



        }

        std::vector<int> offset ;
        int indexLigne = ligneEnCours.find(",");
        if(LPMReg){
            iden = idLPMReg;
            if(ligneEnCours.substr(indexLigne,indexLigne+2).find("Z") != std::string::npos){
                offset = stockLPMR30;

            }
            else if(ligneEnCours.substr(indexLigne,indexLigne+2).find("Y") != std::string::npos){
                offset = stockLPMR28;
            }
            else{
                offset = stockLPMR26;
            }

        }else{
            if(ligneEnCours.substr(indexLigne,indexLigne+2).find("Z") != std::string::npos){
                offset = stockR30;
                iden = varIndex["R30"];

            }
            else if(ligneEnCours.substr(indexLigne,indexLigne+2).find("Y") != std::string::npos){
                offset = stockR28;
                iden = varIndex["R28"];
            }
            else{
                offset = stockR26;
                iden = varIndex["R26"];
            }
        }
        lienF.push_back(iden);
        varFonc[iden].push_back(nomFonction);
        //varIndex[nomVar]=iden;


        for(int v = 0 ; v < nbLabel;v++){

            for (int a = 0 ;a < offset.size() ; a++){



                if(offset[a]< box[i].size()){
                    int tmp = box[i][offset[a]];
                    if (tabProbFonc[0][v] >0 && tmp == v){

                        tmpProba[0][v][offset[a]]= 1;

                    }
                }
            }


        }

    }else{
        for(int cpt3=0; cpt3<nbLabel; cpt3++){
            tmpProba[0][0][cpt3]= tabProbFonc[0][cpt3];
        }
    }
}
