#include<iostream>
#include<bits/stdc++.h>
#include<time.h>
#include<conio.h>
#include<stdlib.h>
#include<math.h>
#include<vector>
#include<map>
#define EMPTY 0
using namespace std;
class board
{
	private:
		int grid[4][4];
		vector<pair<int, int> > empt;
		int score;
	public:
		board();
		bool MoveUp();
		bool MoveDown();
		bool MoveLeft();
		bool MoveRight();
		void CombineUp();
		void CombineDown();
		void CombineLeft();
		void CombineRight();
		void ShiftUp();
		void ShiftDown();
		void ShiftLeft();
		void ShiftRight();
		int WinCheck();
		void Display();
		bool Update();
		void GetRand();
		int GetScore();
};
board::board()
{
	//Making the board
	for(int i=0; i<4; i++)
	{
		for(int j=0; j<4; j++)
		{
			grid[i][j]=EMPTY;
			empt.push_back(make_pair(i, j));
		}
	}
    score=0;
}
int board::GetScore()
{
    return score;
}
void board::Display()
{
    cout<<"Score: "<<GetScore();
    cout<<endl<<" ___________________________ "<<endl;
	for(int i=0; i<4; i++)
	{
	    cout<<"|";
		for(int j=0; j<4; j++)
		{
			cout<<" ";
			if(grid[i][j]/10000==0)
			{
				cout<<" ";
				if(grid[i][j]/1000==0)
				{	cout<<" ";
					if(grid[i][j]/100==0)
					{
						cout<<" ";
						if(grid[i][j]/10==0)
							cout<<" ";
					}
				}
			}
			if(grid[i][j]==EMPTY)
				cout<<" ";
			else
				cout<<grid[i][j];
			cout<<"|";
		}
		cout<<endl<<"|______|______|______|______|"<<endl;
	}
}

void board::GetRand()
{
    srand(time(NULL));
	int i=rand()%empt.size(), j=1+rand()%2;
	grid[empt[i].first][empt[i].second]=(int)pow(2, j);
	empt.erase(empt.begin()+i);
}

bool board::Update()
{
    int changes=0;
	for(int i=0; i<4; i++)
	{
		for(int j=0; j<4; j++)
		{
			int k=0;
			if(grid[i][j]!=EMPTY)
			{
				while(k<empt.size()&&(empt[k].first!=i||empt[k].second!=j))
					k++;
				if(k<empt.size())
                {
                    empt.erase(empt.begin()+k);
                    changes++;
                }
			}
			else
            {
                while(k<empt.size()&&(empt[k].first!=i||empt[k].second!=j))
					k++;
				if(k==empt.size())
                {
                    empt.push_back(make_pair(i, j));
                    changes++;
                }
            }
		}
	}
	if(changes)
        return 1;
    return 0;
}

int board::WinCheck()
{
	int fullcount=0;
	for(int i=0; i<4; i++)
	{
		for(int j=0; j<4; j++)
		{
			if(grid[i][j]!=EMPTY)
			{
			    int fc=0;
			    if(i+1>=0&&i+1<=3&&grid[i+1][j]!=EMPTY&&grid[i+1][j]!=grid[i][j])
                    fc++;
                if(i-1>=0&&i-1<=3&&grid[i-1][j]!=EMPTY&&grid[i-1][j]!=grid[i][j])
                    fc++;
                if(j+1>=0&&j+1<=3&&grid[i][1+j]!=EMPTY&&grid[i][j+1]!=grid[i][j])
                    fc++;
                if(j-1>=0&&j-1<=3&&grid[i][j-1]!=EMPTY&&grid[i][j-1]!=grid[i][j])
                    fc++;
                if(fc==(i+1>=0&&i+1<=3)+(i-1>=0&&i-1<=3)+(j+1>=0&&j+1<=3)+(j-1>=0&&j-1<=3))
                    fullcount++;
			}
		}
	}
	if(fullcount==16)
		return -1;
	return 0;
}

bool board::MoveUp()
{
	ShiftUp();
	CombineUp();
	ShiftUp();
	return Update();
}

bool board::MoveDown()
{
	ShiftDown();
    CombineDown();
	ShiftDown();
	return Update();
}

bool board::MoveLeft()
{
	ShiftLeft();
	CombineLeft();
	ShiftLeft();
	return Update();
}

bool board::MoveRight()
{
    ShiftRight();
	CombineRight();
	ShiftRight();
	return Update();
}
void board::CombineUp()
{
    for(int i=0; i<3; i++)
    {
        int j=i+1;
        for(int k=0; k<4; k++)
        {
            if(grid[i][k]==grid[j][k]&&grid[i][k]!=EMPTY)
			{
				grid[i][k]=grid[j][k]*2;
				grid[j][k]=EMPTY;
				score+=grid[i][k];
			}
        }
    }
}

void board::CombineDown()
{
    for(int i=3; i>0; i--)
    {
        int j=i-1;
        for(int k=0; k<4; k++)
        {
            if(grid[i][k]==grid[j][k]&&grid[i][k]!=EMPTY)
			{
				grid[i][k]=grid[j][k]*2;
				grid[j][k]=EMPTY;
				score+=grid[i][k];
			}
        }
    }
}

void board::CombineLeft()
{
    for(int i=0; i<3; i++)
    {
        int j=i+1;
        for(int k=0; k<4; k++)
        {
            if(grid[k][i]==grid[k][j]&&grid[k][i]!=EMPTY)
			{
				grid[k][i]=grid[k][j]*2;
				grid[k][j]=EMPTY;
				score+=grid[k][i];
			}
        }
    }
}

void board::CombineRight()
{
    for(int i=3; i>0; i--)
    {
        int j=i-1;
        for(int k=0; k<4; k++)
        {
            if(grid[k][i]==grid[k][j]&&grid[k][i]!=EMPTY)
			{
				grid[k][i]=grid[k][j]*2;
				grid[k][j]=EMPTY;
				score+=grid[k][i];
			}
        }
    }
}

void board::ShiftUp()
{
    for(int i=0; i<3; i++)
	{
		int j=i+1;
		for(int k=0; k<4; k++)
		{
			if(grid[i][k]==EMPTY&&grid[j][k]!=EMPTY)
			{
			    int l=i-1;
			    while(l>=0&&grid[l][k]==EMPTY)
                    l--;
                l+=1;
                grid[l][k]=grid[j][k];
				grid[j][k]=EMPTY;
			}
		}
	}
}

void board::ShiftDown()
{
    for(int i=3; i>0; i--)
	{
		int j=i-1;
		for(int k=0; k<4; k++)
		{
			if(grid[i][k]==EMPTY&&grid[j][k]!=EMPTY)
			{
			    int l=i+1;
			    while(l<=3&&grid[l][k]==EMPTY)
                    l++;
                l-=1;
                grid[l][k]=grid[j][k];
				grid[j][k]=EMPTY;
			}
		}
	}
}

void board::ShiftLeft()
{
    for(int i=0; i<3; i++)
	{
		int j=i+1;
		for(int k=0; k<4; k++)
		{
			if(grid[k][i]==EMPTY&&grid[k][j]!=EMPTY)
			{
			    int l=i-1;
			    while(l>=0&&grid[k][l]==EMPTY)
                    l--;
                l+=1;
                grid[k][l]=grid[k][j];
                grid[k][j]=EMPTY;
			}
		}
	}
}

void board::ShiftRight()
{
    for(int i=3; i>0; i--)
	{
		int j=i-1;
		for(int k=0; k<4; k++)
		{
			if(grid[k][i]==EMPTY&&grid[k][j]!=EMPTY)
			{
			    int l=i+1;
			    while(l<=3&&grid[k][l]==EMPTY)
                    l++;
                l-=1;
                grid[k][l]=grid[k][j];
                grid[k][j]=EMPTY;
			}
		}
	}
}
void play()
{
	class board grid;
	int state=0;
	grid.GetRand();
	grid.GetRand();
	while(state==0)
	{
        char mov;
        bool checker=0;
		bool flag=0;
		while(!flag)
		{
			clear;
			grid.Display();
			cout<<"Enter a move (wasd):  ";
			cin>>mov;
			switch(mov)
			{
				case 'w': checker=grid.MoveUp();
                          flag=1;
						  break;
				case 'a': checker=grid.MoveLeft();
                          flag=1;
						  break;
				case 's': checker=grid.MoveDown();
                          flag=1;
						  break;
				case 'd': checker=grid.MoveRight();
                          flag=1;
						  break;
				default: cout<<"Wrong Choice!";
			}
		}
		if(checker)
            grid.GetRand();
		state=grid.WinCheck();
	}
	clear;
    grid.Display();
    cout<<"\tSCORE: "<<grid.GetScore()<<endl<<"\tGAME OVER\n";
}

int main()
{
	play();
	return 1;
}
