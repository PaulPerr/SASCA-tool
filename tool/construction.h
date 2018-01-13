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


/**
 * @brief modelCreation
 * @param numberOfVar nombre de variable dans le model
 * @param fonction fonction composant le model
 * @param link lien entre fonction est variable le string étant la fonction est le vecteur de int les variables
 * @param vars variabel composant le model
 * @return
 */
 typedef opengm::GraphicalModel<float, opengm::Adder> Model;
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

void beliefPropagation(Model gm, std::vector<std::__cxx11::string> &output, int iteration);
void beliefPropagationMul(Model gm);
std::map<std::string, int> transformationASM(std::vector<std::string> contenue, std::map<std::string, std::vector<std::vector<std::vector<float> > > > &probaTab,  std::map<std::string,std::vector<int> > &link, std::vector<int> &var, std::map<std::__cxx11::string, int> &fonctions, std::__cxx11::string hammingweight, std::map<std::__cxx11::string, std::vector<int> > valeurFixer, std::map<int,int >valeurResultat, std::map<int,std::vector<int> >box, bool graph, bool cycle);

bool findCycle(std::map<int,std::vector<std::string> > varFonc, std::map<std::string,std::vector<int> > link , std::__cxx11::string cible, int id, std::map<std::__cxx11::string,int> &vue);
std::vector<int> hammingToDecimal(int h);
int NumberOfSetBits(int i);
bool findLittleCycle(std::map<int,std::vector<std::string> > varFonc, std::string cible, int id );

void hammingInstructionIteration( std::string key,int &ValeurKey , std::string &hammingweight ,std::vector<std::string> contenue,int i ,std::map<std::string,int> instruction);
void instructionTaken(std::map<std::string, int> &instruction , std::map<std::string, int> &traitement);

void specialInstruction(std::string key, std::map<std::string,int> traitement, std::vector<std::vector<std::vector<float> > > &tmpProba , std::vector<std::vector<float > > tabProbFonc, int nbLabel);
void standartInstruction(std::string key, std::vector<std::vector<std::vector<float> > > &tmpProba, int nbLabel, std::map<std::__cxx11::string, int> &fonctions, std::string nomFonction , std::vector<std::vector<float > > tabProbFonc, std::vector<int> stockR30, std::vector<int>  stockR28, std::vector<int> stockR26, std::vector<int> stockLPMR30, std::vector<int>  stockLPMR28, std::vector<int> stockLPMR26, std::map<std::string,int> varIndex, std::map<int,std::vector<std::string> > &varFonc, int i, bool LPMReg , int idLPMReg, std::string ligneEnCours, std::map<int,std::vector<int> > box, std::vector<int> &lienF);

#endif // CONSTRUCTION_H
