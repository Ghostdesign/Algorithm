//
//  main.cpp
//
//
//  Created by Yann Ouedraogo on 2015-02-01.
//  Copyright (c) 2015 Yann Ghislain Ouedraogo. All rights reserved.
//  eyo3005@umoncton.ca

#include <iostream>
#include <fstream>//librairie pour la lecture du fichier
#include <vector>
#include <string>
#include <sstream>// librairie pour la conversion de string apres traitement
using namespace std;

struct sommet;// on declare la variable de type sommet pour l'utiliser dans la creation de la variable de type arc qui contient des information sur les sommet
/*
 on cree un nouveau type de variable arc qui contient les informations sur le sommet source d'ou il vient et le sommet destination 
 qu'il relie au sommet source ainsi que le cout de l'arc meme
 */
typedef struct arc
{
    sommet* source;//declaration de variable pour l'information de la source
    sommet* destination;//declaration de variable pour l'information de la destination
    int cout;
    arc(sommet* src, sommet* desti,int weight)//fonction pour stocker les information a l'aide des parametres
    {
        source=src;
        destination=desti;
        cout=weight;
    }
}arc;
/*
 On cree un nouveau type de variable sommet qui sert essentielement pour le calcul du plus court chemin car il possede un tableau de pointeur fils qui nous permettera de stocker les fils de chaque sommet resperctif ainsi qu'un booleen vu pour djikistra
 */
typedef struct sommet
{
    vector<arc*> fils;// tableau dynamique de pointeur de type arc pour stocker les fils
    string numero;
    int distance;//variable pour calculer les distance pour djikstra
    bool vu;
    sommet* parent;//variable pour les information du pere
    sommet(string nom)
    {
        numero=nom;
    }
}sommet;
/* la Classe Graphe avec les principal fonction d'abord on etudit le fichier en ajoutant les sommet et apres avoir calculer le plus cout chemin
au sommet adjacent on met le booleen vu et ensuite on les affiche
 */
class Graphe
{
public:
    Graphe();
    void sup_bracket(string&);
    void initialiser();
    void dijkstra(string);
    sommet* AjouterNoeud(string);
    void etudeFile();
    void afficher(string,int,sommet*);
    vector<sommet*> sommets;
};
//constructeur intitialisateur du tableau dynamique qui contiendra des pointeur fils
Graphe::Graphe()
{
    for(size_t i = 0; i<sommets.size();i++)
    {
        sommets[i]->vu = false;
        sommets[i]->distance = 100;
        sommets[i]->parent = NULL;
    }
}
/*La representation par liste d'Adjacence on recupere les sommet dans un block du tableau chaque block aura un pointeur relier a lui
 pour cest fils
 */
sommet* Graphe::AjouterNoeud(string node)
{
    for(int i=0;i<sommets.size();i++)//on verifie si le noeud existe pas deja si oui on le retourne le contenue de son indice
    {
        if (sommets[i]->numero==node)
        {
            return sommets[i];
        }
    }
    sommet *n=new sommet(node);//s'il nexiste pas alors on initialise la creation d'un nouveau sommet
    sommets.push_back(n);
    return sommets[sommets.size()-1];
}
/*
 cette fonction est utiliser dans le traitement de fichier vu qu'on a des parenthese pour le cout dans le fichier son role est de retrouve les parenthese les supprimer et ajouter des espaces pour pouvoir utiliser l'operateur >> ensuite pour recuperer nos donne!
 */
void Graphe::sup_bracket(string &ligne)
{
    for (int i=0; i<ligne.length(); i++)
    {
        if (ligne[i]==')'||ligne[i]=='(')// Chaque ligne est examiner charactere par charactere a la recherche de paranthese si on en rencontre
        {
            ligne[i]=' ';//echanger le caractere par un espace
        }
    }
}
/*
 Cette fonction etudie le fichier et recupere le sommet ainsi que sa liste d'Enfant et cout on appel supp_bracket qui retire les 
 les parenthese vu que a chaque debut de ligne on a les sommet cest a dire le noeud pere on le recupere lui d'abord et ensuite on fait une boucle tant que la ligne lu n'est pas terminer pour recupere les fils ainsi que leur coup
 
 */
void Graphe::etudeFile()
{
    string nomFichier="input.txt";// nom du fichier a lire
    string ligne;
    ifstream readfile(nomFichier,ios::in);//ouverture du fichier
    int i=0;
    if (readfile.is_open())
    {
        while (!readfile.eof())// tant qu'on est pas arriver a la fin du fichier
        {
            string source;
            string dest;
            int poid;
            getline(readfile,ligne);// on recupere la ligne avec le getline
            sup_bracket(ligne);// on met des espace a la place des parenthese
            stringstream ss;
            ss<<ligne;//variable de type string stream vu quil n'y a que des chiffres et espace on reconvertit la string avec le traitement de la ligne et surtout pour faire une boucle jusqua la fin de la ligne
            ss>>source; //le premier element correspond au sommet
            sommet* s=AjouterNoeud(source);
            while (!ss.eof())
            {
                ss>>dest>>poid;//et ce qui suit sur la ligne respecte lordre destination et cout donc on le fait jusqua la fin de la ligne
                sommet* d=AjouterNoeud(dest);// sommet de destination
                arc* a=new arc(s,d,poid);// ajout de l'Arc avec les informations sur la source sa destination et son cout
                s->fils.push_back(a);
            }
        }
        readfile.close();//fermeture du fichier
        i++;
    }
    else
        cerr<<"le Fichier n'a pas pu s'ouvrir..."<<endl;//gestion d'erreur au cas ou le fichier n'Est pas lu
 }
/*Cette fonction permet d'Afficher de faon recurssive les sommets et leur distance
 */
void Graphe::afficher(string Sdesti,int distance, sommet* Ssrc)
{
    int indice = 0;
    for(int i=0;i<sommets.size();i++)//on parcour notre tableau de sommets pour recuperer l'indice du sommet source passe en paramtre
    {
        if(sommets[i]->numero==Ssrc->numero)
            indice=i;
    }
    if(Sdesti==sommets[indice]->numero)//un fois qu'on a la destination on vas a son fil et on affiche la distance
    {
        cout<<Sdesti<<"\t  \t"<<distance <<endl;
        return;
    }
    else
    {
        cout<<Sdesti<<"<--";// s'il n'y a plus de fils pour le sommet source qui correspond au sommet au destination on affiche tous les autre sommet qui sont dans le tableau et qui ont pour fils le sommet de destination
        for(size_t i=0;i<sommets.size();i++)
        {
            if(sommets[i]->numero == Sdesti)
                afficher(sommets[i]->parent->numero,distance,Ssrc);
        }
    }
}
/*
 */
void Graphe::initialiser() // pour initialiser tous le djikstra on met la distance a 100 pour pouvoir forcement voir tous les graphes bien sur ce programme ne pourra pas traiter des graphe qui ont des arc avec des cout >99 pour le faire il faudrait changer la valeur
{
    for(size_t i = 0; i<sommets.size();i++)
    {
        sommets[i]->vu=false;
        sommets[i]->distance=100;
        sommets[i]->parent=NULL;
    }
}
void Graphe::dijkstra(string source)
{
    sommet* src=NULL;//On initialise un pointeur temporaire
    for(int i=0;i<sommets.size();i++)// on fait une recherche pour parcourir le tableau qui contient les sommet pour recuperer l'indice dans lequel le sommet se trouve et faire pointer notre pointeur src vers le sommet stocker dans le tableau
    {
        if (sommets[i]->numero==source)
        {
            src=sommets[i];
        }
    }
    if(src==NULL)
        return;//si la source n'existe pas on sort de la fonction
    initialiser();
    src->distance = 0; // initialiser la distance du noeud source  a zero
    sommet* w;
    while(true)
    {
        sommet* temp=NULL; //ceation de pointeur temporaire
        for(size_t i=0; i<sommets.size(); i++)
        {
            sommet* n1=sommets[i];
            if (n1->vu==true || n1->distance==100)//on verifie si le noeud a deja ete visite ou si il a la distance maximal
                continue;
            if (temp==NULL||n1->distance<temp->distance)
                temp=n1;//on pointe tous les sommet a tour de role
        }
        if(temp==NULL)
            break;
        temp->vu=true;
        for(size_t i = 0; i < temp->fils.size(); i++)//on pointe vers le fils pour recuper son cout
        {
            arc* a = temp->fils[i];//on utilise un pointeur temporaire pour pointer ver le fils et recuperer son coup
            w = a->destination;
            int coutadd = a->cout;
            if(w->vu == true)
                continue;
            if(temp->distance + coutadd < w->distance)// si le cout n'est pas mis a jour
            {
                w->distance = temp->distance+coutadd;
                w->parent = temp;
            }		
        }
        afficher(temp->numero,temp->distance,src);//afficher le graphe
    }
}
int main()
{
    // appel de fonction
    Graphe G;
    G.etudeFile();
    string Ssource;
    cout<<"Choisissez le Sommet de Depart Choix entre 1 et 7 pour input.txt"<<endl;
    cin>>Ssource;
    cout<<"\n";
    G.dijkstra(Ssource);
    cout<<"S.destination"<<"<--"<<"S.source"<<"|"<<"cout"<<endl;
	system("pause");
    return 0;
}