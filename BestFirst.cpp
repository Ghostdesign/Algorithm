//
//  main.cpp
//  jeux
//
//  Created by Yann Ouedraogo on 2015-04-02.
//  Copyright (c) 2015 Yann Ghislain Ouedraogo. All rights reserved.
//  eyo3005@umoncton.ca

#include <iostream>
#include <vector>
#include <stack>
#include <array>
#include <climits>
#include <functional>
#include <array>
#include <string>
using namespace std;
int varition=0;int luck=0;int varie=0;int indicedesolution=0;int compteur=0;
//la structure du jeux
class gameStruc
{public:
    string GameArray[7];
    gameStruc(string[]);
    gameStruc* pere;
    int caseVide;
    double estimation;
    double profondeur;
    void jouer(char);
    void afficherMonce();
};//la classe avec les fonction necessaire pour jouer
class jeux
{
public:
    gameStruc* etatInitial;
    vector<gameStruc*> Monceau;
    array<array<string,7>,7> sol;
    void afficherMonceau();
    stack<gameStruc*> Solutione;
    void afficherSolution(gameStruc*);
    jeux(string T[]);
    void generateEtats(gameStruc*);
    void BestFirst();
    bool solution(gameStruc*);
    bool pasAleurplace(gameStruc*);
    int couteur[7];
    int nombredecasepasasaplace[7];
};
//fonction qui determine les case qui sont pas a leur place parapport a la solution
bool jeux::pasAleurplace(gameStruc*E)
{
    array<array<bool,7>,7> reel;
    //initialisation d'un tableau de booleen a deux dimension
    for (int k=0;k<7;k++)
    {
        for (int l=0;l<7 ;l++)
        {
            reel[k][l]=false;//au debut toute les valeurs sont a false
        }
    }
    bool beta=false;//la fonction retourne beta
    sol[0][0]="N";sol[0][1]="N";sol[0][2]="N";sol[0][3]="E";sol[0][4]="B";sol[0][5]="B";sol[0][6]="B";
    sol[1][0]="N";sol[1][1]="N";sol[1][2]="E";sol[1][3]="N";sol[1][4]="B";sol[1][5]="B";sol[1][6]="B";
    sol[2][0]="N";sol[2][1]="E";sol[2][2]="N";sol[2][3]="N";sol[2][4]="B";sol[2][5]="B";sol[2][6]="B";
    sol[3][0]="E";sol[3][1]="N";sol[3][2]="N";sol[3][3]="N";sol[3][4]="B";sol[3][5]="B";sol[3][6]="B";
    sol[4][0]="N";sol[4][1]="N";sol[4][2]="N";sol[4][3]="B";sol[4][4]="E";sol[4][5]="B";sol[4][6]="B";
    sol[5][0]="N";sol[5][1]="N";sol[5][2]="N";sol[5][3]="B";sol[5][4]="B";sol[5][5]="E";sol[5][6]="B";
    sol[6][0]="N";sol[6][1]="N";sol[6][2]="N";sol[6][3]="B";sol[6][4]="B";sol[6][5]="B";sol[6][6]="E";
    //on initialise la liste des solution possible en fonction des restrictions vue en classe
   
    for (int i=0;i<7;i++)
    {
        for (int j=0;j<7 ;j++)
        {
            if ( sol[i][j]==E->GameArray[i])//la fonction prend les element dans le tableau de l'etat passe en parametre
            {
                reel[i][j]=true;//sil sont pareil pour nimporte quel position des solution posible on le met a true
            }
        }
    }
    //initiakisation du tableau qui comptient le nombre d'element qui sont pas a leur place
    for (int v=0; v<7; v++)
    {
        couteur[v]=0;
    }
    for( int i = 0; i < 7; i++ )
    {
        for (int j=0;j<7;j++)
        {
            if (reel[i][j]==false)//on compte ce qui sont pas a leur place
            {
                couteur[i]++;
            }
        }
    }
    for (int xvb=0; xvb<7; xvb++)
    {
        if(couteur[xvb]>0)// si il ya au moins un etat ou toute les case sont pas a leur place
        {
            beta=true;
        }
    }
    return beta;
}
bool jeux::solution(gameStruc* E)
{
   array<array<bool,7>,7> reel; //initialisation d'un tableau de booleen a deux dimension
    for (int k=0;k<7;k++)
    {
        for (int l=0;l<7 ;l++)
        {
            reel[k][l]=false;
        }
    }
    bool alpha=false;int sum[7];//initialiseur du tableau ou on comptera le nombre de true
    for (int xl=0;xl<7 ;xl++)
    {
        sum[xl]=0;
    }

    sol[0][0]="N";sol[0][1]="N";sol[0][2]="N";sol[0][3]="E";sol[0][4]="B";sol[0][5]="B";sol[0][6]="B";
    sol[1][0]="N";sol[1][1]="N";sol[1][2]="E";sol[1][3]="N";sol[1][4]="B";sol[1][5]="B";sol[1][6]="B";
    sol[2][0]="N";sol[2][1]="E";sol[2][2]="N";sol[2][3]="N";sol[2][4]="B";sol[2][5]="B";sol[2][6]="B";
    sol[3][0]="E";sol[3][1]="N";sol[3][2]="N";sol[3][3]="N";sol[3][4]="B";sol[3][5]="B";sol[3][6]="B";
    sol[4][0]="N";sol[4][1]="N";sol[4][2]="N";sol[4][3]="B";sol[4][4]="E";sol[4][5]="B";sol[4][6]="B";
    sol[5][0]="N";sol[5][1]="N";sol[5][2]="N";sol[5][3]="B";sol[5][4]="B";sol[5][5]="E";sol[5][6]="B";
    sol[6][0]="N";sol[6][1]="N";sol[6][2]="N";sol[6][3]="B";sol[6][4]="B";sol[6][5]="B";sol[6][6]="E";
    for (int i=0;i<7;i++)
    {
        for (int j=0;j<7;j++)
        {
            if ( sol[i][j]==E->GameArray[i])//on compte ce qui sont a leur place
            {
                reel[i][j]=true;
            }
        }
    }
   for (int m=0;m<7;m++)
    {
        for (int bx=0; bx<7; bx++)
        {
            
            if (reel[m][bx])
            {
                sum[m]++;// on incremente a lindice du tableau ou le bool est vrai
            }
        }
    }
    for (int bvd=0;bvd<7;bvd++)
    {
        if (sum[bvd]==7)
        {
            indicedesolution=bvd;// si on a un indice qui vaut 7 cest que ces la solution
            alpha=true;// cela voudrait dire qu'il satisfait au moins une solution donc on sor des que sa respect au moins de ces dernier
            break;
        }
        nombredecasepasasaplace[bvd]=sum[bvd];
    }
    return alpha;
}
gameStruc::gameStruc(string tyty[])//fonction qui prend en parametre letat initial
{
    for (int i=0; i<7; i++)
    {
        if (tyty[i]=="E")// on determine la position de la case vide
        {
            caseVide=i;
        }
        GameArray[i]=tyty[i];
    }
    estimation=INT_MAX;//l'estimation pour la fonction heuristique on mettra l'etat initial le plus loin sur le monceau
    pere=NULL;
    profondeur=0;
};
void gameStruc::afficherMonce()// fonction qui affiche le monceau
{
    cout<<endl;
    for (int i=0; i<7; i++)
        cout<< GameArray[i]<<" ";
    cout<<endl;
}

void gameStruc::jouer(char mvt)// fonction qui effectue les mouvement de deplacement de case vide
{
    switch (mvt)
    {
        case 'd':// si je joue un mouvement d il prend l'indice et lechange avec celui de la case suivante
            GameArray[caseVide]=GameArray[caseVide+1];
            GameArray[caseVide+1]="E";
            caseVide++;
            
            break;
        case 'g':// si on joue a gaucne il prend l'indice de la case precedence et echange
            GameArray[caseVide]=GameArray[caseVide-1];
            GameArray[caseVide-1]="E";
            caseVide--;
            break;
        default:
            cout<<"Erreur Mouvement"<<endl;
            break;
    }
}
jeux::jeux(string T[])
{
    etatInitial=new gameStruc(T);
    Monceau.push_back(etatInitial);// on insert comme dans un vector normale
    make_heap(Monceau.begin(), Monceau.end(), greater<gameStruc*>());// on cree le heap avec une fonction de la STL par defaut il fait un maxhep donc on trie les element avec greater pour pouvoir aviir un mean heap
    push_heap(Monceau.begin(), Monceau.end(), greater<gameStruc*>());
}
void jeux::generateEtats(gameStruc *E)//fonction pour la simulation des etat on deplace la case vide en fonction de sa position pour generer des nouveau etat qui seront trier sur le heap et optimiser en fonction de leur position et estimation sur le heap puis tester pour savoir si elle respecte une solution
{
 // apres chaque deplacement on ajoute le nouvel etat sur le monceau
    switch (E->caseVide)
    {
        case 0:
        {
            gameStruc* temp=new gameStruc(E->GameArray);
            temp->pere=E;
            temp->jouer('d');//deplacement a droite
            temp->jouer('d');//deplacement a droite
            temp->profondeur=E->profondeur+1;
            temp->estimation=nombredecasepasasaplace[0];
            Monceau.push_back(temp);
            push_heap(Monceau.begin(),Monceau.end(),greater<gameStruc*>());
            break;
        }
        case 1:
        {
            gameStruc* temp=new gameStruc(E->GameArray);
            temp->pere=E;
            temp->jouer('d');//deplacement a droite
            temp->jouer('d');//deplacement a droite
            temp->jouer('d');//deplacement a droite
            compteur++;compteur++;
            temp->profondeur=E->profondeur+1;
            temp->estimation=nombredecasepasasaplace[1];
            Monceau.push_back(temp);
            push_heap(Monceau.begin(),Monceau.end(),greater<gameStruc*>());
            break;
        }
        case 2:
        {
            gameStruc* temp=new gameStruc(E->GameArray);
            temp->pere=E;
            temp->jouer('d');//deplacement a droite
            compteur++;
            temp->profondeur=E->profondeur+1;//profondeur dans l'arbre
            temp->estimation=nombredecasepasasaplace[2];//estime le nombre de case pas a sa place n fonction de son etat et quand il est a la position 2
            Monceau.push_back(temp);
            push_heap(Monceau.begin(),Monceau.end(),greater<gameStruc*>());
            break;
        }
        case 3:
        {
            gameStruc* temp=new gameStruc(E->GameArray);
            gameStruc* temp2=new gameStruc(E->GameArray);
            temp->pere=E;
            temp2->pere=E;
            if (varition==0)
            {
                temp->jouer('g');//deplacement a gauche
                temp->jouer('g');//deplacement a gauche
                compteur++;
            }
            else if(varition==1)
            {
                temp->jouer('g');//deplacement a gauche
                temp->jouer('g');//deplacement a gauche
                temp->jouer('g');//deplacement a gauche
                compteur++;compteur++;
            }
            else if(varition==2)
            {
                temp->jouer('d');//deplacement a droite
                temp->jouer('d');//deplacement a droite
                temp->jouer('d');//deplacement a droite
            }
            else if (varition==3)
            {
                temp->jouer('g');//deplacement a gauche
                temp->jouer('g');//deplacement a gauche
                temp->jouer('g');//deplacement a gauche
                compteur++;compteur++;
            }
            varition++;
            temp->profondeur=E->profondeur+1;
            temp->estimation=nombredecasepasasaplace[3];
            Monceau.push_back(temp);
            push_heap(Monceau.begin(),Monceau.end(),greater<gameStruc*>());
            break;
        }
        case 4:
        {
            gameStruc* temp=new gameStruc(E->GameArray);
            temp->pere=E;
            if (luck==0)
            {
                temp->jouer('g');//deplacement a gauche
                compteur++;
            }
            else
            {
                temp->jouer('g');//deplacement a gauche
                temp->jouer('g');//deplacement a gauche
                compteur++;
            }
            luck++;
            temp->profondeur=E->profondeur+1;
            temp->estimation=nombredecasepasasaplace[4];
            Monceau.push_back(temp);
            push_heap(Monceau.begin(),Monceau.end(),greater<gameStruc*>());
            break;
        }
        case 5:
        {
            gameStruc* temp=new gameStruc(E->GameArray);
            temp->pere=E;
            temp->jouer('g');//deplacement a gauche
            temp->jouer('g');//deplacement a gauche
            temp->jouer('g');//deplacement a gauche
            compteur++;compteur++;
            temp->profondeur=E->profondeur+1;
            temp->estimation=nombredecasepasasaplace[5];
            Monceau.push_back(temp);
            push_heap(Monceau.begin(),Monceau.end(),greater<gameStruc*>());
            break;
        }
        case 6:
        {
            gameStruc* temp=new gameStruc(E->GameArray);
            temp->pere=E;
            if(varie==0)
            {
                temp->jouer('g');//deplacement a gauche
                compteur++;
            }
            else if(varie==1)
            {
                temp->jouer('g');//deplacement a gauche
                temp->jouer('g');//deplacement a gauche
                compteur++;
            }
            varie++;
            temp->profondeur=E->profondeur+1;
            temp->estimation=nombredecasepasasaplace[6];
            Monceau.push_back(temp);
            push_heap(Monceau.begin(),Monceau.end(),greater<gameStruc*>());
            break;
        }
        default:
            cout<<"erreur";
            break;
    }
}
void jeux::afficherMonceau()// fonction pour afficher le monceau
{
    sort_heap(Monceau.begin(), Monceau.end(), greater<gameStruc*>());
    cout<< "====Monceau=====\n";
    for (int i=0; i<int(Monceau.size());i++)
    {
        Monceau.at(i)->afficherMonce();
    }
}

void jeux::BestFirst()//fonction du bestfirst
{
    int performance=1;
    pop_heap(Monceau.begin(), Monceau.end(), greater<gameStruc*>());
    gameStruc* temp=Monceau.back();//on trie l'etat dans le heap
    Monceau.pop_back();
    generateEtats(temp);//on genere l'etat a tester
   do{
        performance++;
        pop_heap(Monceau.begin(), Monceau.end(), greater<gameStruc*>());
        temp=Monceau.back();
        Monceau.pop_back();
        generateEtats(temp);
       if (performance==16)//avec les optimisation effectuer avec au moins 16 on peut savoir s'il a trouver une solution
       {
           break;
       }
    }
    while(pasAleurplace(temp)>0&&!Monceau.empty()&&solution(temp)!=true);// si il a plus d'element a leur place il vaudra 0 si le monceau est vide et si la solution dit quil match avec celle decrite

    cout<<"nombre d'etats developpes: "<<compteur<<endl;
    cout<<"=================\n";
    cout<<"Solution"<<endl;
    for (int i=0; i<7; i++)
        cout<<sol[indicedesolution][i]<<" ";//on affiche la solution avec la quil match
    return;//donc on observe dans notre tableau de solution ppour reperer l'indice avec lequel il concorde pour l'afficher
}
int main()
{
    //appel de fonction
    string etatinitial[7]={"B","B","B","N","N","N","E"};
    jeux jeux(etatinitial);
    jeux.afficherMonceau();
    jeux.BestFirst();
    return 0;
}