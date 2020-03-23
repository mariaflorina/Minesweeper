#include <iostream>
#include <time.h>
#include <stdlib.h>

using namespace std;

int a[11][11];
char b[11][11];

struct coada
{
    int x,y;
}c[1005];

int dx[]={-1,-1,-1,0,0,1,1,1};
int dy[]={-1,0,1,-1,1,-1,0,1};

void pozbombe()
{
    int t,i,x,y,j;
    t=time(0);
    srand(t);
    for(i=1;i<=10;++i)
    {
        x=rand()%10+1;
        y=rand()%10+1;
        if(a[x][y]==-1)
            --i;
        else
        {
            a[x][y]=-1;
        }

    }
}

int nrbombe(int i, int j)
{
    int nr=0;
    if(a[i-1][j-1]==-1) ++nr;
    if(a[i-1][j]==-1) ++nr;
    if(a[i-1][j+1]==-1) ++nr;
    if(a[i][j-1]==-1) ++nr;
    if(a[i][j+1]==-1) ++nr;
    if(a[i+1][j-1]==-1) ++nr;
    if(a[i+1][j]==-1) ++nr;
    if(a[i+1][j+1]==-1) ++nr;
    return nr;
}

void crearea()
{
    int i,j;
    for(i=1;i<=10;++i)
        for(j=1;j<=10;++j)
            if(a[i][j]!=-1) a[i][j]=nrbombe(i,j);
}

void creareb()
{
    int i,j;
    for(i=1;i<=10;++i)
        for(j=1;j<=10;++j)
            b[i][j]=63;
}

void afis()
{
    int i, j;
    for(i=1;i<=10;++i)
    {
        for(j=1;j<=10;++j)
            cout<<a[i][j]<<' ';
        cout<<'\n';
    }
}

void afisb(int ok)
{
    if(ok)
    {
        int i,j;
        cout<<"  |  ";
        for(j=1;j<=10;++j)
            cout<<j<<"   ";
        cout<<'\n'<<"__|_";
        for(j=0;j<=9;++j)
            cout<<"____";
        cout<<'\n'<<"  |"<<'\n';
        for(i=1;i<=9;++i)
        {
            cout<<i<<" |  ";
            for(j=1;j<=10;++j)
                {
                    cout<<b[i][j]<<"   ";
                }
            cout<<'\n'<<"  |"<<'\n';
        }
        cout<<"10|  ";
        for(j=1;j<=10;++j)
            cout<<b[10][j]<<"   ";
        cout<<'\n';
    }
}

int interior(int x, int y)
{
    return(x>=1&&x<=10&&y>=1&&y<=10);
}

void elib(int x, int y)
{
    int p,u,i,xv,yv;
    p=u=1;
    c[p].x=x;
    c[p].y=y;
    b[x][y]=a[x][y]+'0';
    a[x][y]=-2;
    while(p<=u)
    {
        x=c[p].x;
        y=c[p++].y;
        for(i=0;i<=7;++i)
        {
            xv=x+dx[i];
            yv=y+dy[i];
            if(interior(xv,yv))
            {
                if(a[xv][yv]==0)
                {
                    c[++u].x=xv;
                    c[u].y=yv;
                    b[xv][yv]=a[xv][yv]+'0';
                    a[xv][yv]=-2;
                }
                else if(a[xv][yv]>0)
                {
                    b[xv][yv]=a[xv][yv]+'0';
                    a[xv][yv]=-2;
                }
            }
        }

    }
}


void decizie(int &ok,int &okw)
{
    cout<<'\n'<<"a. Marcare bomba (F)  ";
    cout<<'\n'<<"b. Eliberare casuta (A) ";
    cout<<'\n'<<"c. Renuntare la joc (orice alta tasta)";
    cout<<'\n'<<"Raspunsul dumneavoastra : ";
    char c;
    int i,j;
    cin>>c;
    if(c=='F')
    {
        cout<<'\n'<<"a. Introducere coordonate bomba (a)";
        cout<<'\n'<<"b. Intoarcere la pasul anterior (b)";
        cout<<'\n'<<"c. Renuntare la joc (orice alta tasta)";
        cout<<'\n'<<"Raspunsul dumneavoastra : ";
        char c1;
        cin>>c1;
        if(c1=='a')
            {
                cout<<'\n'<<" Introducere coordonate bomba : ";
                cin>>i>>j;
                cout<<'\n';
                b[i][j]='F';
                a[i][j]=-3;
                afisb(ok);
            }
        else if(c1=='b')
        {
            afisb(ok);
            decizie(ok, okw);
        }
            else
            {
                cout<<"EROARE!";
                ok=0;
                okw=0;
            }
    }
    else if(c=='A')
    {
        cout<<'\n'<<"a. Introducere coordonate casuta goala (a) ";
        cout<<'\n'<<"b. Intoarcere la pasul anterior (b) ";
        cout<<'\n'<<"c. Renuntare la joc (orice alta tasta)";
        cout<<'\n'<<"Raspunsul dumneavoastra : ";
        char c2;
        cin>>c2;
        if(c2=='a')
        {
            cout<<'\n'<<" Introducere coordonate casuta goala : ";
            cin>>i>>j;
            cout<<'\n';
            if(a[i][j]==-1)
            {
                cout<<"Era o bomba. Ati pierdut! o(>~<)o ";
                cout<<'\n';
                ok=0;
                okw=0;
            }
            else if(a[i][j]!=-2)
            {
                elib(i,j);
                ok=1;
                afisb(ok);
            }
        }
        else if(c2=='b')
            {
                afisb(ok);
                decizie(ok, okw);
            }
            else
            {
                cout<<"EROARE!";
                ok=0;
                okw=0;
            }
    }
    else
    {
        cout<<"EROARE!";
        ok=0;
        okw=0;
    }
}

int verifbomb(int &ok)
{
    int i,j;
    ok=0;
    for(i=1;i<=10&&!ok;++i)
        for(j=1;j<=10&&!ok;++j)
            if(a[i][j]==-1) ok=1;
    return ok;
}

int main()
{
    int ok=1,okw=1;
    pozbombe();
    crearea();
    creareb();
    afisb(ok);
    cout<<'\n';
    while(ok)
    {
        if(okw==1)
            decizie(ok,okw);
        else break;
        if(verifbomb(ok)==0) break;
        cout<<'\n';
    }
    if(okw) cout<<"Bombele au fost eliminate. Ati castigat!  \(^o^)/ ";
    return 0;
}
