//
//  skiplist
//
//  Created by Yann Ouedraogo on 2015-03-24.
//  Copyright (c) 2015 Yann Ghislain Ouedraogo. All rights reserved.
//  eyo3005@umoncton.ca

#include <iostream>
#include <ctime>
using namespace std;
//on cree un nouveau type avec les variable necessaire au skiplist
typedef struct Node
{
    int numb;
    Node* sous;
    Node* next;
    int niveau;
    int hauteur;
}Node;
class skip
{
public:
    Node* racine;//racine du skiplist
    int HauteurActuel;
    void add(int);//fonction pour ajouter un element
    void find(int);//fonction pour retrouver un element
    void print();//fonction pour afficher
    skip();//constructeur
    int RadomFlip();//fonction generateur aleatoire pour la probailite d'insertion a different niveau
    Node* NouveauNoeud(int,int,int);
};
//On initialise la racine les niveau et la generation aleatoire en fonction du temps
skip::skip()// constructeur
{
    racine = NULL;
    HauteurActuel = 0;
    srand(time(NULL));
}
/*cette fonction determine de façon aleatoire ou est ce que on vas inserer
 On a 1/2 de chance comme dans le cas d'un lancé pile ou face soit on ecrit sur le meme
 niveau ou on augement le nieau d'au maximun de +1 lors de l'insertion et nous retourne la valeur de 
 l'elevation
 */
int skip::RadomFlip()
{
    int random = 1;
    int elevation = 0;
    while(random)
    {
        random = rand()%2;//on effectue le modulo sur le nombre trouve aleatoirement si on a 0 on sort de la boucle car la hauteur sera egale a la hateur actuel si cest 1 comme initialise on eleve d'un niveau supplementaire notre skiplist
        if(random)
            ++elevation;
        if(elevation > HauteurActuel)
            break;
    }
    return elevation;
}
/*Cette fonction cree un noeud de façon recursive avec la creation de nouveau noeud en dessous 
 on part du principe que la creation de niveau se fait de la racine a la hauteur la plus eleve*/
Node* skip::NouveauNoeud(int data, int position, int height)
{
    if(position < 0)
        return NULL;// le point de depart est 0 la racine est au niveau zero
    else
    {
        //creation d'un nouveau noeud en fonction des prametre
        Node* n= new Node();
        n->numb= data;//assignation donne
        n->niveau= position;//assignation niveau
        n->hauteur= height;//assignation du niveau ou il sera inserer
        n->next= NULL;//pour se deplace sur un niveau
        n->sous= NouveauNoeud(data, position-1, height);//lorsqu'on inserer dans un niveau supperieur on fait un appel recursif
        return n; //Return a Node at the top of the stack
    }
    
}
void skip::add(int data)
{
    //on insert a la racine si la skiplist est vide a niveau et hauteur 0
    if(racine==NULL)
    {
        racine=NouveauNoeud(data, 0, 0);
        return;
    }
    //Si on est rendu a cet etape c'est que la racine existe donc on verifie si la
    //Valeur quon sapprete a inserer est inferieur a la racine
    if(racine->numb > data)
    {
        int temp=racine->numb;
        Node* cur=racine;
        //Comme la valeur a inserer est plus petite on change la valeur de la racine et on met a jour
        //tous les niveau en fonction de la nouvel valeur et on reinsert lanciene valeur de racine plus tard
        for(int i=HauteurActuel; i>=0; i--)
        {
            cur->numb=data;
            cur=cur->sous;
        }
        data=temp;//on reassigne l'ancienne valeur de la racine
    }
    //Avec la fonction aleatoire de probabilite on recupere le niveau a inserer pour savoir si on peut inserer a la valeur actuel ou s'il faut cree un nouveau niveau
    int elevate = RadomFlip();
    if(elevate > HauteurActuel)//si la niveau ou il faut inserer est plus grand que le niveau max actuel
    {
        HauteurActuel++;// on eleve la Hauteur actuel de la skiplist
        Node* NouvelRacine = new Node();
        NouvelRacine->numb = racine->numb;//correspond ala valeur de la racine initial
        NouvelRacine->next = NULL;
        NouvelRacine->niveau = HauteurActuel;
        NouvelRacine->sous = racine;
        racine=NouvelRacine;//on met a jour la racine au cas ou elle etais modifier si elle etais inferieur a la valeur a inserer
    }
    
    Node* newNode = NouveauNoeud(data,elevate,elevate);//A ce niveau on insert on peut inserer le noeud de la valeur en fonction du niveau
    Node* current = racine;
    //On parcourt a partir de la racine et sur touus les niveau
    for(int i = HauteurActuel; i>=0; i--)
    {
        while(current->next != NULL)
        {
            if(current->next->numb > data)
                break;// tant qu'on ne rencontre pas une valeur plus grande ou si il n'existe pas de valeur si ces le cas on sort de la boucle
            current =current->next;// progression sur la line en fonction du niveau
        }
        //on regarde si on peut inserer a ce niveau en verifiant la valeur ou il faut inserer et ou on est rendu dans le skiplist
        if(i <= elevate)
        {
            newNode->next = current->next;
            current->next = newNode;//On insert
            newNode = newNode->sous;
        }
        //Si on pas reussi a inserer a un niveau descendre au niveau en dessous
        current = current->sous;
        
    }
    
}
void skip::find(int valeur)
{
    //Si la liste est vide
    if(racine == NULL)
    {
        cout<<"Liste vide"<<endl;
        return;
    }
    //Si la valeur chercher est la racine
    if(racine->numb == valeur)
    {
         cout<<valeur<<"Est la racine"<<endl;
        return;
    }
    
    Node* current = racine;
    for(int i = HauteurActuel; i>=0 ; i--)
    {
        //On progresse dans la liste jusqua rencontrer un nombre plus grand que la valeur a rechercher
        while( current->next !=NULL )
        {
            if( current->next->numb > valeur)
            {
                break;//si ces le cas ces pas la peine de continuer on sort de la boucle
            }
            else if (current->next->numb == valeur)//si la valeur rechercher est sur ce niveau
            {
                 cout<<valeur<<" Existe dans la liste"<<endl;
                return;
            }
            
            current =current->next;// aide à parcourir
        }
        //si on trouve pas on change de niveau
        current = current->sous;
    }
    cout<<"La recherche n'a pas ete fructueuse"<<endl;
    return;
}
void skip::print()
{
    int aideprint=0;
    Node* temp=racine;
    if (temp==NULL)
    {
        cout<<"SkipList Vide"<<endl;//si la racne est à Null cest que notre liste est vide
        return;
    }
    while(temp->sous !=NULL)//On se rend au niveau le plus bas de la liste
    {
        temp = temp->sous;
    }
    while (temp->next !=NULL)//on affiche jusqu'a ce que on rencontre plus de donne en precissant le niveau ou se trouve la valeur
    {
        cout<<"Niveau"<<temp->hauteur<<": "<<temp->numb<<"\t";
        temp=temp->next;
/* if (aideprint==5)
        {
            cout<<"\n";
            aideprint=0;
			cout<<"\n";
        }
        aideprint++;*/
    }
    cout<<"Niveau"<<temp->hauteur<<": "<<temp->numb<<"\t";//etant donne que notre condition
    //est de verifier si le prochain est null donc on affiche le dernier noeud on est rendu avant que
    //sortir de la fonction
}

int main()
{
    //Meunu et appel de fonction
    skip test;
    int nbInsert=0;int nbRech=0;int numberchoice;
    bool doitagain=true;
    do{
        cout<<"========================="<<endl;
        cout<<"1. Inserer"<<endl;
        cout<<"2. Rechercher"<<endl;
        cout<<"3. Afficher"<<endl;
        cout<<"4. Arret du programme"<<endl;
        cout<<"========================="<<endl;
        do
        {
            cout<<"Entrez votre choix s'il vous plait:";
            cin>>numberchoice;
        }
        while (numberchoice<1 || numberchoice>4);
        switch(numberchoice)
        {
            case 1:
                cout<<"Entrez le nombre a inserer s'il vous plait"<<endl;
                cin>>nbInsert;
                test.add(nbInsert);
                break;
            case 2:
                cout<<"Entrez le nombre a rechercher s'il vous plait"<<endl;
                cin>>nbRech;
                test.find(nbRech);
                break;
            case 3:
                test.print();
                cout<<endl;
                break;
            case 4:
                cout<<"Arret du programe.."<<endl;
                doitagain=false;
                break;
        }
    }
    while(doitagain);
    return 0;
}