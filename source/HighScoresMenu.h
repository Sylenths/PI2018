/// \brief Menu moontrant les scores obtenus par différents joueurs
/// \details Interface accessible depuis le menu principal. Les scores sont stockés dans un fichier et classés en ordre décroissant.
/// \author Mathilde Harnois, Jade St-Pierre Bouchard
/// \date 27 mars 2018
/// \version 0.1
/// \warning
/// \bug Affichage varie en fonction du nombre de caractères, Si les scores sont identiques pour 2 personnes, ça plante.

#ifndef SOURCE_HIGHSCORESMENU_H
#define SOURCE_HIGHSCORESMENU_H

#define TAILLE_MAX 50

class HighScoresMenu : public Menu {
private:
    Scores* scores[11];
    Font* font = ResourceManager::getResource<Font*>("font - arial28");
    std::map<std::string, Model*> labelModels;
    std::string fichierSauvegardeScores;

/// Permet de trier les scores en ordre décroissant.
/// \param numberOfScores permet de savoir combien de fois boucler ( dépends de pourquoi il faut trier).
    void sort(int numberOfScores){
          for (int i = 0; i <numberOfScores ; ++i) {
            for (int j = 0; j <numberOfScores-1 ; ++j) {
                if(scores[j]->getScore()<scores[i]->getScore()){
                    Scores* temp = scores[i];
                    scores[i] = scores[j];
                    scores[j]=temp;
                }
            }
        }
    }

public:

    /// Constructeur
    HighScoresMenu(){
        models["backButtonHighscore"] = new Button (498, 550, 0.l, 284, 113, ResourceManager::getTexture("backButton"),ResourceManager::getTexture("BackButtonOver"));
        models["backButtonHighscore"]->onClick = [this]() { Scene::changeActiveScene(previous); };
        models["fond"] = new Image (0, 0, 0, 1280, 720, ResourceManager::getTexture("FondHighscore"));

        for (int i = 0; i < 10 ; ++i)
            scores[i] = new Scores();
        loadScores();

        int x = 210;
        int y = 185;
        sort(10);
        for (int j = 0; j < 10 ; ++j) {
            std::string labelbuffer;
            std::string labelNameBuffer;
            char intCharBuffer[10];

            sprintf(intCharBuffer, "%d", scores[j]->getScore());
            //itoa(scores[j]->getScore(),intCharBuffer,10);
            labelbuffer = scores[j]->getName()+ "    " + intCharBuffer;
            sprintf(intCharBuffer, "%d", j);
            labelNameBuffer = std::string("HighscoreLabel") + intCharBuffer;



            // Créer mes labels.
            if(j == 5){
                x = 815;
                y = 185;
            }

            labelModels[labelNameBuffer] = new Label(ResourceManager::getResource<Font*>("font - arial28")->getFont(), {128,128,128,0},labelbuffer, x, y, 0.1);
            y += 75;


        }
    }

    /// Destructeur
    ~HighScoresMenu() {
        for (int i = 0; i < 10; ++i)
            delete scores[i];

        for (auto it : labelModels)
            delete it.second;
    }


/// Permet de prendre les scores du fichier et les mettres dans le tableau.
    void loadScores(){
       FILE* fichier = fopen("../../SauvegardeScores.txt","r");
        char charBuffer[TAILLE_MAX];
        std::string buffer;
        std::string name;
        std::string scoreFichier;
        int j = 0;
        if(fichier){
            for (int i = 0; i <10 ; ++i) {
                fgets(charBuffer,TAILLE_MAX,fichier);
                buffer = charBuffer;

                 while (buffer[j] != ' ') {
                     name = name + buffer[j];
                     j++;
                 }
                 j += 2;
                 while (buffer[j] != ' ') {
                   scoreFichier = scoreFichier + buffer[j];
                     j++;
                 }
                int score = std::stoi(scoreFichier);
                scores[i]->setScore(name,score);
                j = 0;
                name = "";
                scoreFichier = "";
            }
            fclose(fichier);
        }
    }

    /// Permet d'ajouter un nouveau score.
    /// \param name nom du joueur qui a fait le score.
    /// \param score pointage du joueur.
    void updateScore(std::string name, unsigned int score){
        Scores* scoreBuffer = new Scores;
        scoreBuffer->setScore(name,score);
       scores[10] = scoreBuffer;

        int position = 0;
        for (int i = 0; i < 10; ++i)
            if(scoreBuffer->getScore() <= scores[i]->getScore())
                position++;

        sort(11);
        delete(scores[10]);
        save();

        // Mettre à jour le label
        char intCharBuffer[10];
        std::string labelNameBuffer;
        std::string labelbuffer;
        sprintf(intCharBuffer, "%d", scores[position]->getScore());
        labelbuffer = scores[position]->getName()+ "    " + intCharBuffer;
        labelNameBuffer = std::string("HighscoreLabel") + intCharBuffer;
        ((Label*)labelModels[labelNameBuffer])->updateTextTexture(labelbuffer,ResourceManager::getResource<Font*>("font - arial28")->getFont(),{128,128,128,0});
    }

    /// Permet d'enregistrer les scores dans le fichier.
    void save(){
        FILE* fichier = fopen("../../SauvegardeScores.txt","w");
        if(fichier){
            for (int i = 0; i <10 ; ++i) {
                const char* name = scores[i]->getName().c_str();
                char score[10];
                SDL_itoa(scores[i]->getScore(),score,10);
                fprintf(fichier, name);
                fprintf(fichier, "  ");
                fprintf(fichier, score);
                fprintf(fichier, " ");
                fprintf(fichier,"\n");
            }
            fclose(fichier);
        }
    }
    /// Permet d'inscrire tous les évènements comme observables.
    /// \param observables une map contenant tous les observables nécessaires.
    void subscribeAll(std::map<unsigned int, Observable<SDL_Event*>*>& observables) {
        if (!observables[SDL_MOUSEBUTTONDOWN]) observables[SDL_MOUSEBUTTONDOWN] = new Observable<SDL_Event*>();
        if (!observables[SDL_MOUSEMOTION]) observables[SDL_MOUSEMOTION] = new Observable<SDL_Event*>();

        for (auto it : models) {
            observables[SDL_MOUSEBUTTONDOWN]->subscribe(it.second);
            observables[SDL_MOUSEMOTION]->subscribe(it.second);
        }
    }

    /// Permet de désinscrire tous les observables.
    /// \param observables une map contenant tous les observables nécessaires.
    void unsubscribeAll(std::map<unsigned int, Observable<SDL_Event*>*>& observables) {
        for (auto it : models) {
            observables[SDL_MOUSEBUTTONDOWN]->unsubscribe(it.second);
            observables[SDL_MOUSEMOTION]->unsubscribe(it.second);
        }
    }

    /// Permet d'afficher le menu.
    void draw(){
        std::string labelNameBuffer;
        char intCharBuffer[10];

        for (int i = 0; i <10 ; ++i) {
            sprintf(intCharBuffer, "%d", i);
            labelNameBuffer = std::string("HighscoreLabel") + intCharBuffer;
            ((Label*)labelModels[labelNameBuffer])->draw();
        }
        ((Button*)models["backButtonHighscore"])->draw();
        ((Image*)models["fond"])->draw();
    }
};

#endif
