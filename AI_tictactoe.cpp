//
//  main.cpp
//  tictactoe_libanese
//
//  Created by Yann Ouedraogo on 2015-04-09.
//  Copyright (c) 2015 Yann Ghislain Ouedraogo. All rights reserved.
//  eyo3005@umoncton.ca

#include <iostream>
#include <sstream>
using namespace std;
int block1=0; int block2=0;
//structure de deplacement pour l'ordinateur
typedef struct Move
{
    int x;
    int y;
}Move;
//structure d'une case de la grille
typedef struct unecase
{
    string valeurcase;//contient les jeton jouer
    int posiVerou;//consititue la position pour acceder au tableau
}cunease;
//classe de la grille
class gril
{
public:
    gril();
    unecase grille[3][3];//grille de jeux
    void affichage();//fonction pour afficher
    void Joeur1Gameur();//fonction pour permetre au joueur 1 de jouer
    void Joeur2Gameur();//fonction pour permetre au joueur 2 de jouer
    void Joeur1DepModeGameur();//fonction pour permetre au joueur 1 de pouvoir faire les deplacements
    void Joeur2DepModeGameur();//fonction pour permetre au joueur 2 de pouvoir faire les deplacements
    void WhoIsEmpty();//pour aider les joueur a savoir qu'elle case est vide
    bool findugame();//pour arreter le jeux
    bool checkWin(string player);//pour savoir qui a gagner
    void play();//pour jouer une partie entre Joueur 1 et l'ordinateur
    int score();
    Move MinMax(unecase G[3][3]);//l'algorithme tient compte des scores des recherche des min et max pour ecrire dans la grille
    int minSearch(unecase G[3][3]);//aide la fonction minmax a connaitre les prochain deplacement possible de l'ordinateur  qui auront un score le plus maximal pour l'ordinateur
    int maxSearch(unecase G[3][3]);//aide la fonction minmax a connaitre les prochain deplacement du joeur1 qui auront un score le plus minimum pour l'ordinateur
};
//initialisation
gril::gril()
{
    for (int v=0; v<3; v++)
    {
        for (int w=0; w<3; w++)
        {
            grille[v][w].valeurcase=" ";//on initialise toute les case on place la valeur
            // de ces cases à vide
        }
    }
    
    int bgv=0;
    for (int n=0; n<3; n++)
    {
        for (int m=0; m<3; m++)
        {
            grille[n][m].posiVerou=bgv;//on initialise la position on donne volonterement sa
            bgv++;//pour eviter au joueur d'entrer les cordonner vu que ces des tableau a 2dimension
            //on veut que cela soit transparent pour l'utilisateur donc les position vont de 0 ...à 8
        }
    }
}
//fonction pour afficher la grille
void gril::affichage()
{
    cout << " ---------------";
    cout<<endl;
    for (int i=0; i<=2; i++)
    {
        cout<<"|";
        cout<<" "<<grille[0][i].valeurcase<<"  ";
        if (i==2)//on affiche par ligne
        {
            cout<<"|";
        }
    }
    cout<<"\n";
    
    int a=0;// compteur pour afficher chaque chaque chiffre de la ligne 1 p
    cout << " ---------------";
    cout<<endl;
    for (int i=3; i<=5; i++)
    {
        cout<<"|";
        cout<<" "<<grille[1][a].valeurcase<<"  ";
        if (a==2)
        {
            cout<<"|";
        }
        a++;
    }
    cout<<"\n";
    int b=0;// compteur pour afficher chaque chaque chiffre de la deuxime ligne
    cout << " ---------------";
    cout<<endl;
    for (int i=6; i<=8; i++)
    {
        cout<<"|";
        cout<<" "<<grille[2][b].valeurcase<<"  ";
        if (b==2)
        {
            cout<<"|";//on affiche par ligne
        }
        b++;
    }
    cout<<"\n";
    cout << " ---------------";
    cout<<endl;
}
//fonction pour le jouer un
void gril::Joeur1Gameur()
{
    cout<<"Joeur 1 a votre tour\n";
    cout<<"Entrez une position entre 0 et 8";
    cout<<endl;
    int position=0;
    cin>>position;//on recupere ou il veut jouer
    for (int n=0; n<3; n++)
    {
        for (int m=0; m<3; m++)
        {
            if (grille[n][m].posiVerou==position)//on trouve l'indice des case ou correspond la position et on ecrit a cet place
            {
                grille[n][m].valeurcase="X";
                block1++;
            }
        }
    }
}
void gril::WhoIsEmpty()//retourne a l'utilisateur les position des case vide
{
    int indice=0;
    for (int n=0; n<3; n++)
    {
        for (int m=0; m<3; m++)
        {
            if (grille[n][m].valeurcase==" ")
            {
                indice=grille[n][m].posiVerou;
                cout<<"Les position vide sont: "<<indice<<"\n";//ces position sont faite pour aider l'utilisateur a voir les position des case vide quil aurait peut etre pas remarquer
            }
        }
    }
}
//une fonction qui permet le joueur1 a faire les deplacements
//on recupere la case quil veut deplacer et celle avec laquelle il veut l'echanger
void gril::Joeur1DepModeGameur()
{
    int dep=0;int recei=0; int j=0;int i=0;int ji=0;int ios=0;
    cout<<"Entrez le numero de la case a deplacer\n";
    cin>>dep;
    cout<<"Avec quel case souhaiter vous l'echanger\n";
    cout<<"La position des cases vides sont\n";
    WhoIsEmpty();
    cin>>recei;
    for (int n=0; n<3; n++)
    {
        for (int m=0; m<3; m++)
        {
            if (grille[n][m].posiVerou==recei)
            {
                i=n; j=m;//a echanger avec
            }
        }
    }
    for (int n=0; n<3; n++)
    {
        for (int m=0; m<3; m++)
        {
            if (grille[n][m].posiVerou==dep)
            {
                ios=n; ji=m;//case a deplacer
            }
        }
    }
    grille[i][j].valeurcase=grille[ios][ji].valeurcase;//echange
    grille[ios][ji].valeurcase=" ";
}
//une fonction qui permet le joueur2 a faire les deplacements
//on recupere la case quil veut deplacer et celle avec laquelle il veut l'echanger
void gril::Joeur2DepModeGameur()
{
    int dep=0;int recei=0; int j=0;int i=0;int ji=0;int ios=0;
    cout<<"Entrez le numero de la case a deplacer\n";
    cin>>dep;
    cout<<"Avec quel case souhaiter vous l'echanger\n";
    cout<<"La position des cases vides sont\n";
    WhoIsEmpty();
    cin>>recei;
    for (int n=0; n<3; n++)
    {
        for (int m=0; m<3; m++)
        {
            if (grille[n][m].posiVerou==recei)//a echanger avec
            {
                i=n; j=m;
            }
        }
    }
    for (int n=0; n<3; n++)
    {
        for (int m=0; m<3; m++)
        {
            if (grille[n][m].posiVerou==dep)//case a deplacer
            {
                ios=n; ji=m;
            }
        }
    }
    
    grille[i][j].valeurcase=grille[ios][ji].valeurcase;
    grille[ios][ji].valeurcase=" ";//echange
    
}
//fonction pour le jouer2
void gril::Joeur2Gameur()
{
    cout<<"Joeur 2 a votre tour\n";
    cout<<"Entrez une position entre 0 et 8";
    cout<<endl;
    int position=0;
    cin>>position;//on recupere la position d'ou il veut jouer
    for (int n=0; n<3; n++)
    {
        for (int m=0; m<3; m++)        {
            if (grille[n][m].posiVerou==position)
            {
                grille[n][m].valeurcase="O";//on trouve l'indice des case ou correspond la position et on ecrit a cet place
                block2++;
            }
        }
    }
}
//Cette fonction verifie s'il n'y a pas de gagnant en regardant les espaces et aider des fonction checkwin
bool gril::findugame()
{
    if(checkWin("X"))
        return true;
    else if(checkWin("O"))
        return true;
    
    bool emptySpace = false;
    for(int i = 0; i < 3; i++)
    {
        if(grille[i][0].valeurcase == " " || grille[i][1].valeurcase == " " || grille[i][2].valeurcase == " ")
            emptySpace = true;
    }
    return !emptySpace;
}
//on verifie s'il n'ya pas pas de serie du charactere en parametre qui implique que ya un gagnant
bool gril::checkWin(string player)
{
    string pieceachecker;
    
    if(player == "X")//pour savoir a quel piece on a affaire pour eviter de dupliquer le code
        pieceachecker = "X";
    else
        pieceachecker = "O";
    
    for(int i = 0; i < 3; i++)//verifie toute les etat possible du jeux pour determiner si on a un gagnant
    {
        
        if(grille[i][0].valeurcase == pieceachecker && grille[i][1].valeurcase == pieceachecker
           && grille[i][2].valeurcase == pieceachecker)
            return true;//veriffie toute les lignes si la chaine en parametre est la meme que la piece a checjer et ainsi de suite
        
        if(grille[0][i].valeurcase== pieceachecker && grille[1][i].valeurcase == pieceachecker
           && grille[2][i].valeurcase == pieceachecker)
            return true;//veriffie toute les colones
    }
    
    if (grille[0][0].valeurcase == pieceachecker && grille[1][1].valeurcase == pieceachecker
        && grille[2][2].valeurcase == pieceachecker)
    {
        return true;//veriffie les diagonal en partant de 0.0 a 2.2
    }
    else if (grille[0][2].valeurcase == pieceachecker && grille[1][1].valeurcase == pieceachecker
             && grille[2][0].valeurcase == pieceachecker)
    {
        return true;//veriffie les diagonal en partant de 0.2 a 2.0
    }
    
    return false;
}
//fonction score qui retourne le gagnant avec un systeme d'affectation de point
int gril::score()
{
    if(checkWin("X"))
        return 10;
    else if(checkWin("O"))
        return -10;
    
    return 0;
}
//fonction qui effectue le moouvement de l'ordinateur
//on utilise deux fonction heuristique avant de reussir a faire le deplacement dans la fontion jeux
//cette fonction appele maxseach qui elle a sont tour apelleminsearch
Move gril::MinMax(unecase G[3][3])
{
    int bestMoveScore = 100;
    Move meilleurcoup;
    
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++)
        {
            if(G[i][j].valeurcase == " ")//on parcour la grille a la recherche d'espace vide
            {
                G[i][j].valeurcase = "O";//on ecris change la valeur de cette cacse temporairement
                int tempMoveScore = maxSearch(G);//et on observe le meilleur mouvement avec une la fonction maxsearch qui appelle minsearch aussi notre but est modifier la valeur du best move
                if(tempMoveScore <= bestMoveScore)// si on une valeur meilleur que celle defini
                {
                    //on recupere les coordonne
                    bestMoveScore = tempMoveScore;
                    meilleurcoup.x = i;
                    meilleurcoup.y = j;
                }
                G[i][j].valeurcase = " ";//et on reinitialise la case a vide
            }
        }
    }
    return meilleurcoup;//on retourne cette meilleur valeur
}
//cette fonction calcul le maximum de degat que peut apporter l,ordinateur sil joue et recuperer le
//meilleur coup en fonction de sa
int gril::maxSearch(unecase G[3][3])
{
    if(findugame())
        return score();
    Move bestMove;
    int bestMoveScore = -1000;
    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            if(G[i][j].valeurcase == " ")
            {
                G[i][j].valeurcase = "X";
                int tempMoveScore = minSearch(G);
                if(tempMoveScore >= bestMoveScore)
                {
                    bestMoveScore = tempMoveScore;
                    bestMove.x = i;
                    bestMove.y = j;
                }
                G[i][j].valeurcase = " ";
            }
        }
    }
    return bestMoveScore;
}
//fonction qui Calul le meilleur coup que l'ordinateur peut jouer pour minimiser le score du joueur
//meilleur coup sera en fonction de sa
int gril::minSearch(unecase G[3][3])
{
    Move bestMove;
    
    int bestMoveScore = 1000;
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            if(G[i][j].valeurcase == " ")
            {
                G[i][j].valeurcase = "O";
                int tempMove = maxSearch(G);
                if(tempMove <= bestMoveScore)
                {
                    bestMoveScore = tempMove;
                    bestMove.x = i;
                    bestMove.y = j;
                }
                G[i][j].valeurcase = " ";
            }
        }
    }
    return bestMoveScore;
}
//fonction qui permet de jouer entre l'ordinateur et le joueur1
void gril::play()
{
    int turn = 0;int bg=0;//on intialise le conteur de tour qui determine qui a la main
    affichage();
    while(true)
    {
        //si le modulo 2 de tour est a 0 ces que cest le tour du joueur
        if(turn % 2 == 0)
        {
            Joeur1Gameur();//appelle la fonction qui permet au joueur1 de jouer
            if(checkWin("X"))
                cout << "Vous avez gagner" << endl;//verifie sil a jouer un coup gagnant
            turn++;//on incremente le tour et affiche quelle move il a effectuer
            affichage();
        }
        else
        {
            cout << endl << "L'ordinateur a jouer:" << endl;
            Move AImove = MinMax(grille);//on appelle minmax
            grille[AImove.x][AImove.y].valeurcase = "O";//et suite a sa apres avoir recuper les cordoner du meille coup pour l'ordinateur on place le jeton de l'ordinateur a cette place
            bg++;//incremente pour que a trois on passe au mode de deplacement
            
            if(checkWin("O"))
                cout << "L'ordinateur a Gagner" << endl;//si l'ordi gagne apres avoir jouer son coup
            turn++;
            affichage();
        }
        if(block1==3 && bg==3)
        {
            break;
        }
        
    }
    
    turn = 0;
    while(!checkWin("X") && !checkWin("O"))
    {
        //on aurait peut etre eu un gagnant de la partie1 donc on si on avait deja un gagnant de la partie placer pion donc on verifie si pn a deja un gagnant et on sort de la boucle
        if (checkWin("X")||checkWin("O"))
        {
            cout<<"On a un gragnant\n";
            cout<<"Fin...\n";
            break;
        }
        cout<<"Deplacement Mood active\n";
        if(turn % 2 == 0)
        {
            Joeur1DepModeGameur();//on appelle la fonction qui permet au joueur1 de faire les deplacements
            if(checkWin("X"))
                cout << "Vous avez gagner" << endl;//en verifiant toujous si sont moov l'a permis de gangner
            turn++;
            affichage();
        }
        else
        {
            //on utilise notre algoritm de minmax pour savoir a quel case l'ordinateur aurait aimer jouer
            //sil lui restait des pions
            //et lorsque on repere cette position on recherche alors un de ces pions deja jouer et on le deplace a la position souhaiter et on remplace par un espace ou etait son pion precedent
            cout << endl << "L'ordinateur a jouer:" << endl;
            int e=0;int z=0;
            for (int n=0; n<3; n++)
            {
                for (int m=0; m<3; m++)
                {
                    if (grille[n][m].valeurcase=="O")
                    {
                        e=n;z=m;
                    }
                }
            }
            Move AImove = MinMax(grille);
            grille[AImove.x][AImove.y].valeurcase=grille[e][z].valeurcase;
            grille[e][z].valeurcase=" ";
            if(checkWin("O"))
                cout << "L'ordinateur a Gagner" << endl;
            turn++;
            affichage();
        }
    }
    
}
int main()
{
    
    gril test;//Appel des fonctions et menu
    int numberchoice;string block="";
    cout<<"Jouons au tictactoe libanais\n";
    cout<<"========================================="<<endl;
    cout<<"1. Jouer contre un Ami"<<endl;
    cout<<"2. Jouer contre votre ordinateur"<<endl;
    cout<<"========================================="<<endl;
    do
    {
        cout<<"Entrez votre choix s'il vous plait:";
        numberchoice=0;
        cin>>numberchoice;
    }
    while (numberchoice<1 || numberchoice>2);
    switch(numberchoice)
    {
            
        case 1:
        {
            test.affichage();
            while (true)
            {
                test.Joeur1Gameur();
                test.affichage();
                test.Joeur2Gameur();
                test.affichage();
                if ((block1==3&&block2==3)||(test.checkWin("X")||test.checkWin("O")))
                {
                    break;//on a incrementer des conteur lorsque les deux jeuton on ete jouer trois fois
                    //on arrete et on passe au mode deplacement
                }
            }
            while (true)
            {
                if (test.checkWin("X")||test.checkWin("O"))
                {
                    cout<<"On a un gragnant\n";
                    cout<<"Fin...\n";
                    break;
                }
                cout<<"Deplacement Mood active\n";
                test.Joeur1DepModeGameur();
                test.affichage();
                test.Joeur2DepModeGameur();
                test.affichage();
                if (test.checkWin("X")||test.checkWin("O"))
                {
                    cout<<"On a un gragnant\n";
                    cout<<"Fin...\n";
                    break;
                }
            }
        }
            break;
        case 2:
        {
            test.play();
        }
            break;
        default:
            cout<<"Erreur choix";
    }
    cout<<"Taper Entrez pour quitter\n";
    cin>>block;
    return 0;
}
