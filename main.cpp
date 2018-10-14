#include <iostream>
using namespace std;

struct moves
{
    int row;
    int column;
};
char comp='x';
char player='o';

bool isLeft(char b[3][3])
{
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++)
        {
            if(b[i][j]=='_')
                return true;
        }
    }
    return false;
}


int evaluate(char b[3][3])
{
    for(int i=0;i<3;i++)
    {
        if(b[i][0]==b[i][1] && b[i][1]==b[i][2])
        {
            if(b[i][0]==comp)
                return +1;
            if(b[i][0]==player)
                return -1;
        }
    }

    for(int i=0;i<3;i++)
    {
        if(b[0][i]==b[1][i] && b[1][i]==b[2][i])
        {
            if(b[0][i]==comp)
                return +1;
            if(b[0][i]==player)
                return -1;
        }
    }

    if(b[0][0]==b[1][1] && b[1][1]==b[2][2])
    {
        if(b[0][0]==comp)
            return +1;
        if(b[0][0]==player)
            return -1;
    }
    if(b[0][2]==b[1][1] && b[1][1]==b[2][0])
    {
        if(b[0][2]==comp)
            return +1;
        if(b[0][2]==player)
            return -1;
    }
    return 0;
}

int minimax(char b[3][3], int d, bool m)
{
    int s=evaluate(b);
    if(s==+1 || s==-1)
        return s;
    if(!isLeft(b))
        return 0;
    if(m)
    {
        int best=-100;
        for(int i=0;i<3;i++)
        {
            for(int j=0;j<3;j++)
            {
                if(b[i][j]=='_')
                {
                    b[i][j]=comp;
                    best=max(best,minimax(b,d+1,!m));
                    b[i][j]='_';
                }
            }
        }
        return best;
    }
    else
    {
        int best=100;
        for(int i=0;i<3;i++)
        {
            for(int j=0;j<3;j++)
            {
                if(b[i][j]=='_')
                {
                    b[i][j]=player;
                    best=min(best,minimax(b,d+1,!m));
                    b[i][j]='_';
                }
            }
        }
        return best;
    }
}

moves bestMove(char b[3][3])
{
    int best=-100;
    moves best_move;
    best_move.column=-1;
    best_move.row=-1;

    for(int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++)
        {
            if(b[i][j]=='_')
            {
                b[i][j]=comp;
                int move_val=minimax(b,0,false);
                b[i][j]='_';
                if(move_val>best)
                {
                    best_move.column=j;
                    best_move.row=i;
                    best=move_val;
                }
            }
        }
    }
    return best_move;
}
int main()
{
    char b[3][3]={'_','_','_',
                   '_','_','_',
                   '_','_','_'};
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++)
        {
            cout<<b[i][j]<<" ";
        }
        cout<<endl;
    }
    while(isLeft(b) && evaluate(b)==0)
    {
        int x,y;
        cout<<"Enter your position\n";
        cin>>x>>y;
        x--;
        y--;
        if(b[x][y]=='_')
        {
            b[x][y]='o';
            cout<<"Your move\n";
            cout<<"--------------------\n";
            for(int i=0;i<3;i++)
            {
                for(int j=0;j<3;j++)
                {
                    cout<<b[i][j]<<" ";
                }
                cout<<endl;
            }
            moves bb=bestMove(b);
            b[bb.row][bb.column]='x';
            cout<<"Computer's move\n";
            cout<<"----------------------\n";
            for(int i=0;i<3;i++)
            {
                for(int j=0;j<3;j++)
                {
                    cout<<b[i][j]<<" ";
                }
                cout<<endl;
            }
        }
        else
        {
            cout<<"Enter another position\n";
        }
    }
    if(evaluate(b)==+1)
        cout<<"You lose!"<<endl;
    else if(evaluate(b)==-1)
        cout<<"You win!"<<endl;
    else
        cout<<"Draw!"<<endl;
    return 0;
}
