/// \brief Classe de parametre
/// \details Classe qui contient un double
/// \author Mickaël Grisé-Roy
/// \date 10 Avril 2018
/// \version 0.1
/// \warning Aucun.
/// \bug Aucun.

#ifndef SOURCE_ACTIONDOUBLE_H
#define SOURCE_ACTIONDOUBLE_H



class ActionDouble : public ActionParameter{
private:
    double data;///< La donnée du parametre

public:
    ///Constructeur
    /// \param name nom du param dans la map qui sera returned
    /// \param data La data
    ActionDouble(std::string name, double data) : ActionParameter(name) {
        this->data = data;
    }
    /// Retourne le tyoe d'action
    double getType() {
        return SIMDOUBLE;
    }
    /// retourne la data
    int getData(){
        return data;
    }

};
#endif //SOURCE_ACTIONDOUBLE_H
