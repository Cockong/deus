#include <iostream>
#include <stdlib.h>
#include<string.h>
#include<time.h>
using namespace std;

const int MAX_X=20;
const int MAX_Y=20 ;

struct grille_cell
{
    int tx, ty;
    int nb_viv;
    int nb_mort;
    int etat[MAX_X][MAX_Y] ;

};

grille_cell init_grille()
{
   int i,j ;
   grille_cell G ;
    do {cout << "taille de la grille (entre 1 et 18)?" << endl ;
    cin >> G.tx >> G.ty ;}
    while ((G.tx<1)||(G.tx>18)||(G.ty<1)||(G.ty>18));
    G.tx = G.tx+2;
    G.ty= G.ty+2;
    // ajout dune bordure exterieure
    cout << "cellules en vie ?" << endl ;
    cin  >> G.nb_viv ;
    G.nb_mort = (G.tx*G.ty)-G.nb_viv ;
    for (i=0;i<MAX_X;i++)
    {
        for (j=0;j<MAX_Y;j++)
        {
            G.etat[i][j]=0 ;
        }
    }
    return G ;
}

void place_cell_vivantes (grille_cell &G)
{
    int i,j,k;
    for (k=0;k<G.nb_viv;k++)
    {
       do
    {
        i=rand()%(G.tx-2)+1;
        j=rand()%(G.ty-2)+1;
    } while(G.etat[i][j]==1);
G.etat[i][j]=1;

    }


}

void affiche_grille(grille_cell G)
{
    int i,j;
    for (i=1;i<G.tx-1;i++)
    {
        for (j=1;j<G.ty-1;j++)
        {
            cout << G.etat[i][j] << " " ;
        }
        cout << endl ;
    }
    cout << endl << endl;
}

grille_cell etat_suivant(grille_cell G,int &changement)
{
    int i,j,k,l,m;

    grille_cell futur;
    futur.nb_viv=G.nb_viv ;
    futur.nb_mort=G.nb_mort;
    futur.tx = G.tx;
    futur.ty = G.ty;
    for (i=0;i<MAX_X;i++)
    {
        for (j=0;j<MAX_Y;j++)
        {
            futur.etat[i][j]=G.etat[i][j] ;
        }
    }

    for (i=1;i<G.tx-1;i++)
    {
        for (j=1;j<G.ty-1;j++)
        {
            m=0 ;
           for (k=i-1;k<i+2;k++)
           {
               for (l=j-1;l<j+2;l++)
               {
                  if (G.etat[k][l]==1)
                  {
                      m++ ;
                  }
               }

           }

           if (G.etat[i][j]==1)
           {
               m=m-1;
               if ((m>3)||(m<2))
               {
                  futur.etat[i][j]=0 ;
                  futur.nb_viv=futur.nb_viv-1 ;
                  changement++ ;
               }

           }
           else
           {
               if (m==3)
               {
                   futur.etat[i][j]=1 ;
                   futur.nb_viv++ ;
                   changement ++ ;
               }
           }

        }



    }
futur.nb_mort=(G.tx*G.ty)-futur.nb_viv;

return futur ;

}


int main(void)
{
    int y, changement;
    grille_cell G;
    G=init_grille() ;
    place_cell_vivantes(G) ;
    affiche_grille(G) ;
    changement = 1;

    cout << "etat suivant 1)oui 2)non ?" << endl ;
    cin >> y ;


    while ((y==1)&&(changement>0))
    {
        changement=0 ;
    G=etat_suivant(G,changement) ;
    affiche_grille(G) ;
    cout << "nombre de changements : " << changement << endl ;

    cout << "etat suivant 1)oui 2)non ? " << endl ;
    cin >> y ;

    }

    return 0;
}
