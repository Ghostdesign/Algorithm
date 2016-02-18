//
//
//
//  Created by Yann Ouedraogo on 2015-01-23.
//  Copyright (c) 2015 Yann Ghislain Ouedraogo. All rights reserved.

#include <iostream>
#include <fstream>       //librairie pour la lecture du fichier
#include <list>         //librairie pour la liste d'adjacence
#include <queue>       //librairie pour utiliser une file
#include <vector>     //librairie pour utiliser tableau dynamique
using namespace std;

//Class graph avec les declations de prototype de fonction
class graph
{public:
    int V;
    graph(int V);       //Constructeur
    list<int> *adj;    // declation d'une liste de pointeur pour la liste d'adjacence
    int indegree[100];// tableau pour stocker le nombre d'Arc entrant a un sommet
    void addedge();  //fonction pour ajouter des arc dirigé au sommet
    void topsort(); //fonction pour trie des graphe directionné sans cycle
};
graph::graph(int V)// initialisation
{
    this->V=V;   // creation du sommet
    adj=new list<int>[V];// ajout de la liste baser sur le sommet
}
/*Cette foction sert a lire dans le fichier,recuperer les donner a sauvegarder dans les structure de donner
 pour creer le graphe. Son principe est d'ajouter les sommet et chaque arc entrant a un autre sommet, cela 
 increment le indegree de cette autre sommet ainsi on recupere les sommet et permet de connaitre les direction des arc.
 */
void graph::addedge()
{
    int som[100],inde[100],edj[100];//tableau pour stocker les donne recuperer pendant la lecture
	for(int j=0;j<100;j++)
	{
		som[j]=0;
		inde[j]=0;
		edj[j]=0;
		indegree[j]=0;
	}
    string nomFichier="input.txt";// nom du fichier a lire
    ifstream readfile(nomFichier,ios::in);//ouverture du fichier
    int i=0;
    if (readfile.is_open())
    {
        while (!readfile.eof())// tant qu'on est pas arriver a la fin du fichier
        {
            readfile>>som[i]>>inde[i]>>edj[i];// on utilise l'operateur >> pour lire le prochain element  sur une ligne separer par un espace ou tabulation
            // som correspont au sommet inde pour le indegree edj pour les arc à noter que l'on fait expres de ne rien faire avec le indegree car de toute façon on l'incremente enfoncttion du sommet qui recois un arc entrant
           // incrementation du indegree
			 adj[som[i]].push_back(edj[i]);// l'indice correspond au sommet et ce qui est ajouter est la liste des enfant du noeud
            indegree[edj[i]]++;
            i++;
        }
        readfile.close();
    }
    else
        cerr<<"le Fichier n'a pas pu s'ouvrir..."<<endl;//gestion d'erreur au cas ou le fichier n'Est pas lu
}
/*
 Cete fonction permet de faire un trie topologique sur les graphe de type DAG
 */
void graph:: topsort()
{
    //Le zerobox correspond a tous les sommet qui ont un indegree = a zero on recupere d'Abord ce qui n'on aucun arc entrant
    //cest la premiere etape du topsort
    queue<int> zerobox;
    for (int i=1;i<=7; i++)
    {
        if (indegree[i]==0)
        {
            zerobox.push(i);
        }
    }
    // une fois qu'on a recuperer tous les sommet qui ont des indegree egale a zero
    //on vas les sauvegarder dans la liste final triee tout en decrementant les indegree de chaque sommet restant
    // des que le indegree de n'importe quel sommet sera egale a zero il vas dans la zerobox et de la zerobox a la liste final
    // de cette maniere on peut eviter de recuperer des sommet deux fois et par la meme occassion eviter de supprimer les noeud physiquement
    vector<int> tab;
    while (!zerobox.empty())
    {
        int poping = zerobox.front();
        zerobox.pop();
        tab.push_back(poping);//on recupere les donner(les sommet) a la tete de la file (zerobox) pour les inserer dans la liste triee

        for (int i=1;i<=7;i++)
        {
            int value=i;
            indegree[value]--;//on decrement le indegree tout en vefiant les sommet qui auront un indegree egale a 0
            if (indegree[value]==0)
            {
                zerobox.push(value);//si le indegree egale a zero met le dans le zerobox
            }
        }
    }//vu que cest une boucle les nouveau element entrez dans le zerobox seront ajouter a la a la liste final triee(tab) jusqu'A ce qui'il n'y ai plus d'element dans le zerobox
    
    //Affichage de la liste avec les sommets trié
    for (int i=0;i<tab.size(); i++)
    {
        cout<<tab[i]<<" ";
    }
    cout<<"\n";
}
int main()
{
    cout<<"Le fichier input.txt respect le format Noeud Indegre Enfant"<<endl;
	cout<<"\n";
    graph G(8); //8 correspond au nombre de sommet +1 || a modifier au cas ou on change de graphe ainsi que la taille de recherche de zerobox qui ici est 7
    G.addedge();
    G.topsort();
    return 0;
}
