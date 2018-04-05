/// \brief Permet de gérer les pointages avec les noms du menu Highscore.
/// \details Accessible depuis Highscore, cette classe permettra de trier aisément les pointages associés aux différents joueurs.
/// \author Jade St-Pierre Bouchard
/// \date 04-04-2018
/// \version 0.1
/// \warning Aucun.
/// \bug Aucun.
#ifndef SOURCE_SCORES_H
#define SOURCE_SCORES_H

#include <string>

class Scores{
private:
    std::string name;
    unsigned int score;
public:
    Scores(std::string name, unsigned int score){
        this->name = name;
        this->score = score;
    }

};
#endif
