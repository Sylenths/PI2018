/// \brief Permet de gérer les pointages avec les noms du menu Highscore.
/// \details Accessible depuis Highscore, cette classe permettra de trier aisément les pointages associés aux différents joueurs.
/// \author Jade St-Pierre Bouchard
/// \date 04-04-2018
/// \version 0.1
/// \warning Aucun.
/// \bug Aucun.

#ifndef SOURCE_SCORES_H
#define SOURCE_SCORES_H

class Scores{
private:
    std::string name;
    unsigned int score;

public:
    Scores() {
        name = "Empty";
        score = 0;
    }

    void setScore(std::string name, unsigned  int score){
        this->name = name;
        this->score = score;
    }

    std::string getName(){
        return name;
    }

    unsigned int getScore(){
        return score;
    }
};

#endif
