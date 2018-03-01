#ifndef CONSTRUCTION_H
#define CONSTRUCTION_H
#include <iostream>
#include <cstdlib>
#include <string>
#include <boost/lexical_cast.hpp>
#include <opengm/graphicalmodel/graphicalmodel.hxx>
#include <opengm/graphicalmodel/space/simplediscretespace.hxx>
#include <opengm/functions/potts.hxx>
#include <opengm/operations/adder.hxx>
#include <opengm/inference/messagepassing/messagepassing.hxx>

#include <opengm/operations/maximizer.hxx>



 typedef opengm::GraphicalModel<float, opengm::Adder> Model;
/**
 * @brief modelCreation this fonction a factor graph
 * @param numberOfVar number of variable in the model
 * @param fonction the functions which composed the model
 * @param link the link between functions and variables
 * @param vars the variable in the model
 * @return
 */
Model modelCreation(std::map<std::__cxx11::string, int> fonctions,  std::map<std::string,std::vector<std::vector<std::vector<float> > > >  &probaTab,
                     std::map<std::string,std::vector<int> > link, std::vector<int> var);
/**
 * @brief fonctionPremier
 * @param gm
 * @param prob
 * @param var
 */
void fonctionPremier(Model * gm,std::vector<float> prob,int var );
/**
 * @brief fonctionSecond
 * @param gm
 * @param prob
 * @param var
 */
void fonctionSecond(Model * gm,std::vector<std::vector<float> > prob,int var[]);
/**
 * @brief fonctionTroisieme
 * @param gm
 * @param prob
 * @param var
 */
void fonctionTroisieme(Model * gm, std::vector<std::vector<std::vector<float> > > prob, int var[]);

/**
 * @brief beliefPropagation this fonction resolve a factor graph with belief propagation
 * @param gm the model
 * @param output  the final output with all value per variable
 * @param iteration  the number of iteration for the belief propagation
 * @param allVariables true for have all varaible , false for print only the most
 */
void beliefPropagation(Model gm, std::vector<std::__cxx11::string> &output, int iteration, bool allVariables);
/**
 * @brief transformationASM
 * @param contenue the vector whiwh contain the execution stack
 * @param probaTab the propablity table per function
 * @param link link beteween function and varaibel
 * @param var  variables in the model
 * @param fonctions function in the model
 * @param hammingweight the vector which contain the leakage
 * @param valeurFixer  the vector which contain clear text
 * @param valeurResultat  the vector which contain the cypher text
 * @param box the vector wich contain the sbox
 * @param graph  true for juste generate a graph without probability
 * @param cycle true for generate a graph with cycle
 * @return
 */
std::map<std::string, int> transformationASM(std::vector<std::string> contenue, std::map<std::string, std::vector<std::vector<std::vector<float> > > > &probaTab,  std::map<std::string,std::vector<int> > &link, std::vector<int> &var, std::map<std::__cxx11::string, int> &fonctions, std::__cxx11::string hammingweight, std::map<std::__cxx11::string, std::vector<int> > valeurFixer, std::map<int,int >valeurResultat, std::map<int,std::vector<int> >box, bool graph, bool cycle);
/**
 * @brief findCycle
 * @param varFonc
 * @param link
 * @param cible
 * @param id
 * @param vue
 * @return
 */
bool findCycle(std::map<int,std::vector<std::string> > varFonc, std::map<std::string,std::vector<int> > link , std::__cxx11::string cible, int id, std::map<std::__cxx11::string,int> &vue);
/**
 * @brief hammingToDecimal
 * @param h
 * @return
 */
std::vector<int> hammingToDecimal(int h);
/**
 * @brief NumberOfSetBits
 * @param i
 * @return
 */
int NumberOfSetBits(int i);
/**
 * @brief findLittleCycle
 * @param varFonc
 * @param cible
 * @param id
 * @return
 */
bool findLittleCycle(std::map<int,std::vector<std::string> > varFonc, std::string cible, int id );
/**
 * @brief hammingInstructionIteration
 * @param key
 * @param ValeurKey
 * @param hammingweight
 * @param contenue
 * @param i
 * @param instruction
 */
void hammingInstructionIteration( std::string key,int &ValeurKey , std::string &hammingweight ,std::vector<std::string> contenue,int i ,std::map<std::string,int> instruction);
/**
 * @brief instructionTaken
 * @param instruction
 * @param traitement
 */
void instructionTaken(std::map<std::string, int> &instruction , std::map<std::string, int> &traitement);
/**
 * @brief specialInstruction
 * @param key
 * @param traitement
 * @param tmpProba
 * @param tabProbFonc
 * @param nbLabel
 */
void specialInstruction(std::string key, std::map<std::string,int> traitement, std::vector<std::vector<std::vector<float> > > &tmpProba , std::vector<std::vector<float > > tabProbFonc, int nbLabel);
/**
 * @brief standartInstruction
 * @param key
 * @param tmpProba
 * @param nbLabel
 * @param fonctions
 * @param nomFonction
 * @param tabProbFonc
 * @param stockR30
 * @param stockR28
 * @param stockR26
 * @param stockLPMR30
 * @param stockLPMR28
 * @param stockLPMR26
 * @param varIndex
 * @param varFonc
 * @param i
 * @param LPMReg
 * @param idLPMReg
 * @param ligneEnCours
 * @param box
 * @param lienF
 */
void standartInstruction(std::string key, std::vector<std::vector<std::vector<float> > > &tmpProba, int nbLabel, std::map<std::__cxx11::string, int> &fonctions, std::string nomFonction , std::vector<std::vector<float > > tabProbFonc, std::vector<int> stockR30, std::vector<int>  stockR28, std::vector<int> stockR26, std::vector<int> stockLPMR30, std::vector<int>  stockLPMR28, std::vector<int> stockLPMR26, std::map<std::string,int> varIndex, std::map<int,std::vector<std::string> > &varFonc, int i, bool LPMReg , int idLPMReg, std::string ligneEnCours, std::map<int,std::vector<int> > box, std::vector<int> &lienF);

#endif // CONSTRUCTION_H
