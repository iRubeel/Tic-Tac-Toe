#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 3

void createInitialBoard(char[N][N]);
void readUserMove(int *, int *, int *);
void printCurrentBoard(char[N][N]);
void computerPlaysRandom(int * , int *);
int computerPlaysToWin(char [N][N], int * , int * );
int getComputerMove(char board[N][N], int *, int *, int, int);
int gameWon(char [N][N], char);
int isInputValid(int, int, int);
void all_sums(char board[N][N], int [N], int [N], int *, int *);
int memberOf(int value, int someArray[N]);
int isBoardFull(char board[N][N]);
// you need the below prototype only if you attempt the additional functionality part
int computerPlaysToBlock(char [N][N], int * , int * );

int main(){
    
    int userRow, userCol, computerRow, computerCol;
    int taken;
    int count = 1;
    int stepsWon = 0;
    
    char board[N][N];
    char winner = 'N';
    
    srand((int) time(0));
    
    printf ("This tic-tac-toe board is of size %d by %d\n", N, N);
    
    printf ("You are using symbol X and the computer program is using symbol O\n");
    
    printf ("Here is the board - spaces are indicated by a ?\n");
    
    createInitialBoard (board);
    
    while ((winner != 'Y') && !(isBoardFull(board)))
    {
        taken = 0;
        
        while (!(taken))
        {
            readUserMove(&userRow, &userCol, &stepsWon);
            printf("You chose row %d and column %d \n", userRow, userCol);
            
            while (!isInputValid(userRow, 1, N) || !isInputValid(userCol, 1, N))
            {
                printf("That's is an invalid row or column number - try again\n");
                readUserMove(&userRow, &userCol, &stepsWon);
                printf("You chose row %d and column %d \n", userRow, userCol);
            }
            
            if (board[userRow-1][userCol-1] == '?')
            {
                board[userRow-1][userCol-1] = 'X';
                taken = 1;
                count++;
            }
            else
            {
                taken = 0;
                printf("That spot is taken - please try another one\n");
            }
        }
        
        if (gameWon(board, 'X'))   //user won
        {
            printf("Congrats - you won against the computer :) in %d steps\n", stepsWon);
            winner = 'Y';
        }
        
        else  if (!(isBoardFull(board)))            //check computer's move if the board is not yet full
        {
            taken = 0;
            
            while (!(taken))
            {
                taken = getComputerMove(board, &computerRow, &computerCol, userRow-1, userCol-1);
                
                if (taken) {
                    break;
                }
                
                getchar();
                
                if (board[computerRow][computerCol] == '?')
                {
                    board[computerRow][computerCol] = 'O';
                    taken = 1;
                    
                }
                else
                {
                    taken = 0;
                    //printf("That spot is taken - computer - try another one\n");
                }
            }
            printf("Computer chose row %d and column %d \n", computerRow+1, computerCol+1);
            if (gameWon(board, 'O'))
            {
                printf("Oh the computer won this time :(( think hard next time\n");
                winner = 'Y';
            }
        }
        
        printCurrentBoard (board);
        
        if (winner != 'Y') {
           printf("Enter to continue \n");
        }
        getchar();
        
    } //end of while
    
    if (winner != 'Y') {
       printf("Game was a tie - no winner!\n\n");
    }
    return 0;
}

int  getComputerMove(char board[N][N], int * computerRow, int * computerCol, int userRow, int userCol){
    
    int winningSpot = 0;
    
    winningSpot = computerPlaysToWin(board, computerRow, computerCol);
    
    /*
     if the computer does not find a winning spot, then it either play randomly or blocks
     */
    if (!winningSpot)
    {
        // comment the next line if you are attempting the 2% functionality
        //computerPlaysRandom(computerRow, computerCol);
        
        //uncomment the next few  lines if you are attempting the 2% functionality
        int blocked = 0;
         
         blocked = computerPlaysToBlock(board, computerRow, computerCol);
         if (blocked == 0) {
            computerPlaysRandom(computerRow, computerCol);
         }
         
         return blocked;
         
    }
    
    return winningSpot;
}

int isInputValid(int entered, int minimum, int maximum)
{
    if(entered>=minimum && entered<=maximum)
    {
        return 1;
    }
    else 
    {
        return 0;
    }
}
void createInitialBoard(char board[N][N])
{
    for(int i=0;i<N;i++)
    {
        for(int j=0; j<N;j++)
        {
            board[i][j]='?';
        }
    }
    printf(" %c | %c | %c  \n", board[0][0], board[0][1], board[0][2]);
	printf("------------\n");
	printf(" %c | %c | %c  \n", board[1][0], board[1][1], board[1][2]);
	printf("------------\n");
	printf(" %c | %c | %c  \n", board[2][0], board[2][1], board[2][2]);
}
int isBoardFull(char board[N][N])
{
    if ((board[0][0] == '?') || (board[0][1] == '?') ||  (board[0][2] == '?') || (board[1][0] == '?') || (board[1][1] == '?') ||  (board[1][2] == '?')||  (board[2][0] == '?')||  (board[2][1] == '?') || (board[2][2] == '?'))
    {     
	    return 0;
    }
    else
    {
        return 1;
    }
}

void readUserMove(int*userRow,int*userCol,int*stepswon)
{
    int condition;
    condition=0;
    while(!condition)
    {
        int Row,Col;

        printf("Your move - enter numbers between 1 and 3\n");
        printf("Enter row number: ");
        scanf("%d",userRow);
    
        printf("Enter Column number: ");
        scanf("%d",userCol);

        Row=*userRow;
        Col=*userCol;

        if(!isInputValid(Row,1,N))
        {
            printf("That's is an invalid row or column number - try again\n");
        }
        else if(!isInputValid(Col,1,N))
        {
            printf("That's is an invalid row or column number - try again\n");
        }
        else
        {
            condition=1;
            *stepswon+=1;
        }
    }
}
void printCurrentBoard(char board[N][N])
{
    for(int i=0; i<N ; i++)
    {
        for(int j=0; j<N ;j++)
        {
            printf(" %c ",board[i][j]);
            if(j<2)
            {
                printf("|");
            }
        }
        if(i<2)
            {
                printf("\n------------\n");
            }
        
    }
}
int gameWon(char board[N][N],char symbol)
{
    int sumR[N],sumC[N],sumLD,sumRD;
    sumLD=0;
    sumRD=0;

    all_sums(board,sumR,sumC,&sumLD,&sumRD);

    if(sumLD == 12 || sumLD == 3 || sumRD == 12 || sumRD == 3)
    {
        return 1;
    } 
    else 
    {
        for(int i=0;i<N;i++)
        {
            if(sumR[i]== 12 || sumR[i] == 3 || sumC[i]==12 || sumC[i]==3)
            {
                return 1;
            }
        }
        return 0;
    }
}
int computerPlaysToWin(char board[N][N],int*cRow,int*cCol)
{
    int sumR[N],sumC[N],sumLD,sumRD;
    sumLD=0;
    sumRD=0;

    all_sums(board,sumR,sumC,&sumLD,&sumRD);

    for(int i=0;i<N;i++)
    {
        if(sumR[i] == 8 )//checks rows
        {
            for(int j=0; j<N;j++)
            {
                if(board[i][j]=='?')
                {
                    board[i][j]='O';
                    *cRow=i;
                    *cCol=j;
                    return 1;
                }
            }
        }
        if(sumC[i] == 8 )
        {
            for(int j=0; j<N;j++)
            {
                if(board[j][i]=='?')
                {
                    board[j][i]='O';
                    *cRow=i;
                    *cCol=j;
                    return 1;
                }
            }
        }
    }
    for(int i=0;i<N;i++)
    {
        if(sumLD == 8 ) //checks left D
        {
            if(board[i][i]=='?')
            {
                board[i][i]='O';
                *cRow=i;
                *cCol=i;
                return 1;
            }
        }
        if(sumRD == 8) //checks right D
        {
            if(board[i][2-i] == '?')
            {
                board[i][2-i]='O';
                *cRow=i;
                *cCol=2-i;
                return 1;
            }
        }
    }
    return 0;
}
int computerPlaysToBlock(char board[N][N], int *cRow , int *cCol)
{
    int sumR[N],sumC[N],sumLD,sumRD;
    sumLD=0;
    sumRD=0;

    all_sums(board,sumR,sumC,&sumLD,&sumRD);

    for(int i=0;i<N;i++)
    {
        if(sumR[i] == 2 )//checks rows
        {
            for(int j=0; j<N;j++)
            {
                if(board[i][j]=='?')
                {
                    board[i][j]='O';
                    *cRow=i;
                    *cCol=j;
                    return 1;
                }
            }
        }
        if(sumC[i] == 2 )
        {
            for(int j=0; j<N;j++)
            {
                if(board[j][i]=='?')
                {
                    board[j][i]='O';
                    *cRow=i;
                    *cCol=j;
                    return 1;
                }
            }
        }
    }
    for(int i=0;i<N;i++)
    {
        if(sumLD == 2 ) //checks left D
        {
            if(board[i][i]=='?')
            {
                board[i][i]='O';
                *cRow=i;
                *cCol=i;
                return 1;
            }
        }
        if(sumRD == 2) //checks right D
        {
            if(board[i][2-i] == '?')
            {
                board[i][2-i]='O';
                *cRow=i;
                *cCol=2-i;
                return 1;
            }
        }
    }
    return 0;
}
void computerPlaysRandom(int*cRow,int*cCol)
{
    *cRow=rand() % 3;
    *cCol=rand() % 3;
}
void all_sums(char board[N][N],int sumR[N],int sumC[N],int*sumLD,int*sumRD)
{
    for(int i=0;i<N;i++)
    {
        //calculates sum of left diagnol
        if(board[i][i] == 'O')
        {
            *sumLD=*sumLD+4;
        }
        else if(board[i][i] == 'X')
        {
            *sumLD=*sumLD+1;
        }
        else
        {
            *sumLD=*sumLD+0;
        }
        //calculates sum of Right diagnol
        if(board[i][2-i] == 'O')
        {
            *sumRD=*sumRD+4;
        }
        else if(board[i][2-i] == 'X')
        {
            *sumRD=*sumRD+1;
        }
        else
        {
            *sumRD=*sumRD+0;
        }
        sumR[i]=0;
        sumC[i]=0;
        for(int j=0;j<N;j++)
        {
            //calculates sum of row
            if(board[i][j]=='O')
            {
                sumR[i]=sumR[i]+4;
            }
            else if(board[i][j]=='X')
            {
                sumR[i]=sumR[i]+1;
            }
            else
            {
                sumR[i]=sumR[i]+0;
            }
            //calculates sum of column
            if(board[j][i]=='O')
            {
                sumC[i]=sumC[i]+4;
            }
            else if(board[j][i]=='X')
            {
                sumC[i]=sumC[i]+1;
            }
            else
            {
                sumC[i]=sumC[i]+0;
            }
        }
    }
}
int memberOf(int aNum,int somearray[N])
{
    for(int i;i<N;i++)
    {
        if(somearray[i] == aNum )
        {
            return 1;
        }
    }
    return 0;
}

