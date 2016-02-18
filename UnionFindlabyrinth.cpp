//
//
//  Created by Yann Ouedraogo on 2015-01-19.
//  Copyright (c) 2015 Yann Ghislain Ouedraogo. All rights reserved.
//

#define MAX 5   //definir la taille maximal pour le double tableau
#include <iostream>
#include <vector>//librairie pour utiliser tableau dynamique
#include <time.h>// librairie pour generer nombre aleatoire en fonction du temps
using namespace std;

// classe labyrinthe avec les fonction necessaire
class labyrinthe
{
private:
    vector<int>block;//correspond a une case
    vector<int>wall;// correspond a un mur
public:
    labyrinthe();//constructeur
    void chemin();
    void breakWall(int);
    void print();//fonction pour afficher le labyrinthe
	void breakWall2(int);
    void breakWall3(int);
    int find(int);//fonction find
    int UnionBySize(int,int);//fonction pour associer les block et par la meme occassion faire svoir qu'il faut pas afficher de mur a cette place.
};
labyrinthe::labyrinthe()// initialisation
{
    for (int i=0;i<25; i++)
    {
        block.push_back(-1);//au debut le contenant du tableau est initialise a -1
    }
    for (int i=0;i<25; i++)
    {
        wall.push_back(0);// les mur sont initialiser a 0 si il ne faut pas en mettre on change la valeur a 1
    }
	int mur=0;
}

int labyrinthe::find(int indice)//fonction qui prend en parametre un indice et qui retourne la racine de l'ensemble contenant cette indice
{
	if (block[indice]==-1)
    {
        return indice;
    }
    else
    {
        return find(block[indice]);
    }
}
//d'abord on cherche les racine des case a unifier a l'Aide dun find
//Ensuite on verifie qu'il sont pas deja uni en observant s'il n'ont pas la meme racine
//une fois tous ce la fait on peut changer la racine par la meme occasion unir les cellule car elle on la meme racine desormais.
int labyrinthe::UnionBySize(int block1, int block2)
{
    int racine1=find(block1);
    int racine2=find(block2);
    if (racine1==racine2)
        return 0;
    else if (racine1<racine2)
        block[racine2]=racine1;
    else
        block[racine1]=racine2;
    return 0;
}
/*Break Wall est le premier briseur de mur.le contenue de la variable mur sera  choisi aleatoirement donc, sa cellule 
adjacente aussi. on fait un union tant que les racine sont egales.
*/

void labyrinthe::breakWall(int mur)
{
    if(find( mur) != find( mur+1))
    {
        UnionBySize( mur, mur+1);
        wall[mur] = 1;
    }
    
}
/*
BreakWall2  et BreakWall3 ont le meme principe que le deuxieme sauf qu'il ont un decalage de plus 1 

*/
void labyrinthe::breakWall2(int mur)
{
    if(find( mur+1) != find( mur +2))
    {
        UnionBySize( mur+1, mur +2);
        wall[mur] = 1;
    }
    
}
void labyrinthe:: breakWall3(int mur)
{
    if(find( mur+2) != find( mur +3))
    {
        UnionBySize( mur+1, mur +2);
        wall[mur] = 1;
    }
}
/*
Pour avoir un resultat aleatoire a chaque execution on decide de
faire adopter des comportement a notre labyrinthe en fonction des valeur aleatoire fournis par le rand 
Ainsi pour des valeur entre 3, 8 ,13... notons que l'on choisi ces valeur pour eviter que la celule 4 fussion avec la 5 par exmple
*/
void labyrinthe::chemin()
{
     srand(time(NULL));//initialisation du temps pour la fonction rand()
    int mur;
    while(find(0)!=find(24))
    {
        mur =rand()%24;//nombre aleatoire entre 0 et 24
        if(mur <=3)
        {
            breakWall(mur);
        }
        else if(mur > 4 && mur <= 8)
        {
            breakWall(mur);
			breakWall2(mur);
            breakWall3(mur);
        }
        else if(mur > 9 && mur <= 13)
        {
            breakWall(mur);
			breakWall2(mur);
			breakWall3(mur);
        }
        else if(mur > 14 && mur <= 18)
        {
            breakWall(mur);
			breakWall2(mur);
			breakWall3(mur);
        }
        else if(mur > 19 && mur <= 23)
        {
            breakWall(mur);
        }
        else
        {
            breakWall(mur);
        }
    }
}

void labyrinthe::print()
{
    //creation d'un double tableau on esaille ici de representer le labyrinthe comme une matrice pour l'affichage bien que l'esthetique 
	//peut etre discutable l'esprtit de cette affichage est de se raprocher le plus du labyrinthe presenter en classe avec des chiffre
    int grille[MAX][MAX];
    grille[0][0]=0;grille[0][1]=1;grille[0][2]=2;grille[0][3]=3;grille[0][4]=4;
    grille[1][0]=5;grille[1][1]=6;grille[1][2]=7;grille[1][3]=8;grille[1][4]=9;
    grille[2][0]=10;grille[2][1]=11;grille[2][2]=12;grille[2][3]=13;grille[2][4]=14;
    grille[3][0]=15;grille[3][1]=16;grille[3][2]=17;grille[3][3]=18;grille[3][4]=19;
    grille[4][0]=20;grille[4][1]=21;grille[4][2]=22;grille[4][3]=23;grille[4][4]=24;
    cout<<"---------------------------"<<endl;
    //l'idée est d'observer chaque ligne avec des boucle et verifier avec des condition pour connaitre la valeur du wall et comme sa on sait si on devrait afficher le mur ou juste un espace
   // Notons aussi le fait qu'on essaille de gerer laffichage par ligne de la "matrice" 
	int u=0;
    for (int i=0; i<=4; i++)
    {
        if (wall[i]==1)
        {
            cout<<" ";
        }
        else
            cout<<"|";
        cout<<" "<<grille[0][i]<<"  ";
        if (grille[0][i]==4)
        {
            cout<<" |";
        }
    }
    cout<<"\n";
    
    int a=0;// compteur pour afficher chaque chaque chiffre de la ligne 1 p
    for (int j= 5; j<10; j++)
    {
       
        if(wall[j] == 1)
        {
            cout << " ";
        }
        else
        {
            cout << "----  ";
        }
    }
    cout<<endl;
    for (int i=5; i<=9; i++)
    {
        if (wall[i]==1)
        {
            cout<<" ";
        }
        else
            cout<<"|";
        cout<<" "<<grille[1][a]<<"  ";
        if (grille[1][a]==9)
        {
            cout<<" |";
        }
         a++;
    }
    cout<<"\n";
    int b=0;// compteur pour afficher chaque chaque chiffre de la deuxime ligne
    for (int j= 10; j<15; j++)
    {
        
        if(wall[j] == 1)
        {
            cout << " ";
        }
        else
        {
            cout << "---   ";
        }
    }
    cout<<endl;
    for (int i=10; i<15; i++)
    {
        if (wall[i]==1)
        {
            cout<<" ";
        }
        else
            cout<<"|";
        cout<<" "<<grille[2][b]<<" ";
        if (grille[2][b]==14)
        {
            cout<<" |";
        }
        b++;
    }
    cout<<"\n";
    int c=0;// compteur pour afficher chaque chaque chiffre de la troisieme ligne
    for (int j=15; j<20; j++)
    {
        
        if(wall[j] == 1)
        {
            cout << " ";
        }
        else
        {
            cout << "---   ";
        }
    }
    cout<<endl;
    //cout<<"|";
    for (int i=15; i<20; i++)
    {
        if (wall[i]==1)
        {
            cout<<" ";
        }
        else
            cout<<"|";
        cout<<" "<<grille[3][c]<<" ";
        if (grille[3][c]==19)
        {
            cout<<" |";
        }
        c++;
    }
    cout<<"\n";
    int d=0;// compteur pour afficher chaque chaque chiffre de la dernier ligne
    for (int j=20; j<25; j++)
    {
        
        if(wall[j] == 1)
        {
            cout << " ";
        }
        else
        {
            cout << "---   ";
        }
    }
    cout<<endl;
    //cout<<"|";
    for (int i=20; i<25; i++)
    {
        if (wall[i]==1)
        {
            cout<<" ";
        }
        else
            cout<<"|";
        cout<<" "<<grille[4][d]<<" ";
        if (grille[4][d]==24)
        {
            cout<<" |";
        }
        d++;
    }
    cout<<"\n";
    cout<<"---------------------------"<<endl;
}
int main()
{
    //appel des fonction
    labyrinthe laby;
    cout<<"Labyrinthe avant de defaire les murs"<<endl;
    laby.print();// on affiche le labyrinthe avant de supprimmer les mur
    cout<<endl<<endl;
    laby.chemin();
    cout<<"Labyrinthe apres avoir defait les murs"<<endl;
    laby.print();
	system("pause");
    return 0;
}
