# OOP
## Class vs struct?
Les deux sont pareil. SAUF, pour une différence!
Par défaut les class sont privé.
Par défaut les struct sont public.

So.... why?

La structure est plus symbolique. 
On utilise la struct comme POD (plain old data-type).
Donc juste du data , sans rien de fancy comme des constructors and shit.

## Constructeur / Destructeur
Un constructor est une méthode appelé lorsque l'objet est instancié.  
Constructor/desctructor: Garentie l'intégrité de l'objet lors de sa création et destruction.  
Un constructeur Initialise un objet, mais ne construit pas d'objet en mémoire.

## Example de classe

point.h

    #pragma once        // Plus performant que ifdef
    #ifdef POINT_H      // le ifdef est un double safety. Combiné avec pragma, TES SAFE
    #define POINT_H
    class Point{

        public:
            int x();
            int y();

            void setX(int x);
        private: 
            int mX, mY; // Le tit m, veut dire privé

            const int atchoum;
    }

    #endif



point.cpp

    #include "Point.h"

    void Point::setX(int x){
        mX = x;
    }
    
    void Point::setY(int y){
        mX = y;
    }

    void Point::set(int x, int y){
        setX(x);
        setX(y);
    }
    
    Point::Point()
        :Point(0,0)
    {
    }

    // La list d'initialisation membre permet d'init des constantes et être plus fast
    Point::Point(int x, int y)
        : atchoum{},mX{x}, mY{y}  // Liste d'initialisation membre.
    {
        //mX{} //Illégale, la variable fut déjà init
        mX = 0; //ok

    }

La liste d'initialisation membre est toujours callé avant le constructeur  
  
## Fonction en mode lecture
Par défaut les méthodes en c++ sont en mode lecture/écriture

int x() const{ }    // Définition de méthode en lecture seul
int readY() const;  // Déclaration de méthode en lecture seul
int x() {}    // Méthode en lecture/écriture 


## Fonctions spéciales
Tu peux décider de garder ceux par défaut, les redéfinir, ou même les deletes

    Point(const && point) = default;
    Point(const && point){print(swag)};
    Point(const && point) = delete;


# Polymorphisme

    class Camera:
    {
        public:
            int a;
            int b;
            Camera() = default;

            // virtual permet d'override la méthode dans les sous classes
            virtual std::string grab(); 
            virtual void focus(); 
            
            // Le = 0 rend la classe abstraite
            virtual void init() = 0; 
    }


    class LUM270: public Camera
    {
        public:
            ~LUM270() = default;

            // implémente la classe abstraite
            void init() override; 

            // Le mot override est optionnel, mais très recommandé.
            // Le compilateur raise une erreur si tu met un override
            // sur une méthode qui n'est non asbtraite/virtual
            std::string grab() override; 
    }

    class LUM470: public LUM270
    {
        public:
            std::string grab() override;
    }

    int main(){
        std::vector<Camera*> cams;
        
        cams.push_back(new Camera);
        cams.push_back(new LUM270);

        Camera cam;
        LUM270 lum;

        std::cout << cam.grab();
        std::cout << lum.grab();

        for (auto cam : cams){
            std::cout <<cam->grab() << "\n";
        }

        // Comment utiliser la méthode d'une seule class en particulier?
        // dynamic_cast : retourne pointeur vers la bonne classe, ou rien
        
        for (auto cam : cams){
            if(dynamic_cast<LUM470*>(cam)){
                std::cout << static_cast<LUM470*>(cam)->grab() << "\n";
            }
        }

        // COMMENT FAIRE DES BOUCLES?
        // Version 1: Slow
        for (int i {}; i cams.size();++i){
            delete cams[i];
        }

        // Version 2: faster, en utilisant un itérateur
        std::vector<Camera*>::iterator it(cams.begin());
        std::vector<Camera*>::iterator end(cams.end());
        while(it != end){
            delete it*;
            ++it;
        }

        // version 3:
        for (auto it(cams.begin()); it != cams.end();++it){
            delete it*;
        }

        //version 4: Fais la même chose que la version 2. SUPRA GOOD
        for (auto cam : cams){
            delete cam;
        }

        //version 5: For each avec lambda
        std::for_each(cams.begin(), cams.end(),
        [](Camera * cam){
            delete cam;
        })

    }
