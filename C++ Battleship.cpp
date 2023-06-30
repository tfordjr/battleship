
// C++ Battleship
// Completed 10/06/2021

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <stdlib.h>
#include <stdio.h>
using namespace std;

// functions
void setup(), oppSetup(), playerShots(), display(), isPlayerShipSunk(), isOppShipSunk(), oppAI();
int oppShots();

// global variables
bool gameOver = false, recentHit = false;
int playerShips = 5, oppShips = 5, coorA, coorB, shotCount = 0;
char let;
int num, letAdj;

int shipSize[5] = { 2,3,3,4,5 };
string shipNames[5] = { "Patrol Boat", "Cruiser", "Destroyer", "Battleship", "Carrier" };
bool playerSunkShips[5] = { false, false, false, false, false };
bool oppSunkShips[5] = { false, false, false, false, false };
int lastHit[11][11];

int oppShipPos[5][11][11];
int playerShipPos[5][11][11];

char trueOppBoard[11][11] = {
    {' ', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'T'},
    {'A', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-'},
    {'B', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-'},
    {'C', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-'},
    {'D', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-'},
    {'E', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-'},
    {'F', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-'},
    {'G', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-'},
    {'H', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-'},
    {'I', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-'},
    {'J', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-'},
};

char oppBoard[11][11] = {
    {' ', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'T'},
    {'A', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-'},
    {'B', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-'},
    {'C', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-'},
    {'D', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-'},
    {'E', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-'},
    {'F', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-'},
    {'G', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-'},
    {'H', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-'},
    {'I', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-'},
    {'J', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-'},
};

char playerBoard[11][11] = {
    {' ', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'T'},
    {'A', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-'},
    {'B', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-'},
    {'C', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-'},
    {'D', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-'},
    {'E', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-'},
    {'F', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-'},
    {'G', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-'},
    {'H', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-'},
    {'I', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-'},
    {'J', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-'},
};




int main()
{
    cout << "** Welcome to Battleship in C++ **\n ** TURN ON YOUR CAPS LOCK **\n\n";
    display();
    oppSetup();
    setup();

    do
    {
        oppShots();
        display();
        playerShots();
    } while (!gameOver);

    return 0;
}



void oppSetup()
{
    bool validPlacement;
    int a, b, vert;
    int goodAValues[5], goodBValues[5];

    cout << "Opponent is choosing where to place his ships..." << endl;

    for (int i = 0; i < oppShips; i++)
    {
        do
        {
            validPlacement = true;
            unsigned seed = time(0);
            srand(seed);

            a = 1 + (rand() % 10);
            b = 1 + (rand() % 10);
            vert = (rand() % 2);

            if (trueOppBoard[a][b] == 'B')
                validPlacement = false;
            else
            {
                goodAValues[0] = a;
                goodBValues[0] = b;
            }

            for (int j = 1; j < shipSize[i]; j++)
            {

                if (vert)
                {
                    if (trueOppBoard[a + j][b] != '-')
                        validPlacement = false;
                    else
                        goodAValues[j] = a + j;
                }

                else
                {
                    if (trueOppBoard[a][b + j] != '-')
                        validPlacement = false;
                    else
                        goodBValues[j] = b + j;

                }
            }
        } while (!validPlacement);

        for (int j = 0; j < shipSize[i]; j++)
        {
            if (vert)
            {
                trueOppBoard[goodAValues[j]][b] = 'B';
                oppShipPos[i][goodAValues[j]][b] = 'B';
            }
            else
            {
                trueOppBoard[a][goodBValues[j]] = 'B';
                oppShipPos[i][a][goodBValues[j]] = 'B';
            }
        }
    }
}

void setup()
{
    char rawa, rawc;
    int a, b, c, d;
    int shipSize[5] = { 2,3,3,4,5 };
    string shipNames[5] = { "Patrol Boat", "Cruiser", "Destroyer", "Battleship", "Carrier" };

    cout << "\n  Place your Battleships\n";
    for (int i = 0; i < playerShips; i++)
    {
        do
        {
            cout << "Where will the hind of the " << shipNames[i] << " lie? The " << shipNames[i] << " is " << shipSize[i] << " units long. ";
            do
            {
                cin >> rawa;
                cin >> b;
            } while (rawa < 'A' || rawa > 'J' || b < 1 || b > 10);

            a = int(rawa) % 64;

            cout << "Where will the nose of the " << shipNames[i] << " lie? The " << shipNames[i] << " is " << shipSize[i] << " units long. ";
            do
            {
                cin >> rawc;
                cin >> d;
            } while (rawc < 'A' || rawc > 'J' || d < 1 || d > 10);

            c = int(rawc) % 64;
        } while (abs(rawa - rawc) != (shipSize[i] - 1) && abs(b - d) != (shipSize[i] - 1) || playerBoard[a][b] == 'B' || playerBoard[c][d] == 'B' || (a != c && b != d));

        playerBoard[a][b] = 'B';
        playerBoard[c][d] = 'B';
        playerShipPos[i][a][b] = 'B';
        playerShipPos[i][c][d] = 'B';

        if (shipSize[i] > 2)
        {
            if (b != d)
            {
                if (b > d)
                {
                    int swap = d;
                    d = b;
                    b = swap;
                }
                for (int j = 0; j < shipSize[i]; j++, b++)
                {
                    playerBoard[a][b] = 'B';
                    playerShipPos[i][a][b] = 'B';
                }
            }
            else if (a != c)
            {
                if (c > a)
                {
                    int swap = c;
                    c = a;
                    a = swap;
                }
                for (int j = 0; j < shipSize[i]; j++, c++)
                {
                    playerBoard[c][d] = 'B';
                    playerShipPos[i][c][d] = 'B';
                }
            }
        }


        display();
    }

}

void display()
{
    cout << "\tOpponent's Board" << endl;
    for (int r = 0; r < 11; r++)
    {
        for (int c = 0; c < 11; c++)
        {
            cout << oppBoard[r][c] << "  ";
        }
        cout << endl;
    }
    cout << endl;
    cout << "\tPlayer's Board" << endl;
    for (int r = 0; r < 11; r++)
    {
        for (int c = 0; c < 11; c++)
        {
            cout << playerBoard[r][c] << "  ";
        }
        cout << endl;
    }
    /*
    cout << "\tOpp true board" << endl;
    for (int r = 0; r < 11; r++)
    {
        for (int c = 0; c < 11; c++)
        {
            cout << trueOppBoard[r][c] << "  ";
        }
        cout << endl;
    }
    */
}

void playerShots()
{
    char rawa, hitListA[5] = { '0', '0', '0', '0', '0' };
    int a, b, hitListB[5] = { 0, 0, 0, 0, 0 };
    bool hit = false;

    cout << "Choose your shots." << endl;
    for (int i = 1; i <= playerShips; i++)
    {
        bool validShot = true;
        do
        {
            if (gameOver)
                exit(0);
            validShot = true;
            cout << "Shot " << i << ": ";
            do
            {
                cin >> rawa;
                cin >> b;
            } while (rawa < 'A' || rawa > 'J' || b < 1 || b > 10);

            a = int(rawa) % 64;

            if (trueOppBoard[a][b] == 'X' || trueOppBoard[a][b] == 'O')
            {
                validShot = false;
                cout << "Shot invalid, please try again." << endl;
            }
        } while (!validShot);

        if (trueOppBoard[a][b] == 'B')
        {
            trueOppBoard[a][b] = 'X';
            oppBoard[a][b] = 'X';
            hit = true;

            hitListA[i - 1] = rawa;
            hitListB[i - 1] = b;

            for (int j = 0; j < 5; j++)
            {
                oppShipPos[j][a][b] = 'X';
            }
        }
        else
        {
            oppBoard[a][b] = 'O';
        }
    }
    if (hit)
    {
        bool andSign;
        andSign = false;

        cout << "!! You have hit on...   ";
        for (int i = 0; i < 5; i++)
        {
            if (hitListA[i] != '0')
            {
                if (andSign)
                    cout << "& ";
                cout << hitListA[i] << hitListB[i] << " ";
                andSign = true;
            }
        }
    }
    cout << endl;
    isOppShipSunk();
}

void oppAI()
{
    bool validShot = false;

    while (!validShot)
    {

        if (shotCount == 0)
            coorA++;
        if (shotCount == 1)
            coorA -= 2;
        if (shotCount == 2)
        {
            coorA++;
            coorB++;
        }

        if (shotCount == 3)
        {
            coorB -= 2;
        }


        if (playerBoard[coorA][coorB] == 'B' || playerBoard[coorA][coorB] == '-')
        {
            validShot = true;
            shotCount++;
        }
        else
        {
            shotCount++;
            if (shotCount >= 3)
            {
                recentHit = false;
                do
                {
                    unsigned seed = time(0);
                    srand(seed);

                    let = 65 + (rand() % 10);
                    num = 1 + (rand() % 10);

                    letAdj = int(let) % 64;

                    if (playerBoard[letAdj][num] == 'X' || playerBoard[letAdj][num] == 'O')
                        validShot = false;
                    else
                        validShot = true;
                } while (!validShot);
                return;
            }
        }
    }

    letAdj = coorA;
    num = coorB;
    let = char(coorA + 64);
}

int oppShots()
{
    cout << "Opponent is choosing his shots, please wait..." << endl;
    bool validShot = true;

    for (int i = 0; i < oppShips; i++)
    {
        if (recentHit)
            oppAI();
        else
        {
            do
            {
                unsigned seed = time(0);
                srand(seed);

                let = 65 + (rand() % 10);
                num = 1 + (rand() % 10);

                letAdj = int(let) % 64;

                if (playerBoard[letAdj][num] == 'X' || playerBoard[letAdj][num] == 'O')
                    validShot = false;
                else
                    validShot = true;
            } while (!validShot);
        }

        cout << "Shot " << i + 1 << ": " << let << num << "  ";


        if (playerBoard[letAdj][num] == 'B')
        {
            playerBoard[letAdj][num] = 'X';
            cout << "Hit!  " << endl;
            shotCount = 0;
            recentHit = true;
            coorA = letAdj;
            coorB = num;
            lastHit[coorA][coorB] = 'X';
            for (int j = 0; j < 5; j++)
            {
                playerShipPos[j][letAdj][num] = 'X';
            }
            isPlayerShipSunk();
        }
        else
        {
            playerBoard[letAdj][num] = 'O';
            cout << "Miss!  " << endl;
        }

        /*
        if (i != oppShips-1)
        {
            // DELAY
            int c, d;

            for (c = 1; c <= 32767; c++)
                for (d = 1; d <= 32767; d++)
                 {}
            // DELAY
        }
        */
    }
    cout << endl;

    return 0;
}

void isOppShipSunk()
{
    for (int x = 0; x < 5; x++)
    {
        bool sunk = true;
        for (int y = 1; y < 11; y++)
        {
            for (int z = 1; z < 11; z++)
            {
                if (oppShipPos[x][y][z] == 'B' || oppSunkShips[x])
                    sunk = false;
            }
        }

        if (sunk)
        {
            cout << "You have sunk the opponent's " << shipNames[x] << "!" << endl;
            oppSunkShips[x] = true;
            oppShips--;
            if (oppShips == 0)
            {
                gameOver = true;
                cout << "Congratulations! You win!!" << endl;
            }
        }
    }
}

void isPlayerShipSunk()
{
    for (int x = 0; x < 5; x++)
    {
        bool sunk = true;
        for (int y = 1; y < 11; y++)
        {
            for (int z = 1; z < 11; z++)
            {
                if (playerShipPos[x][y][z] == 'B' || playerSunkShips[x])
                    sunk = false;
            }
        }

        if (sunk)
        {
            cout << "The opponent has sunk your " << shipNames[x] << "!" << endl;
            playerSunkShips[x] = true;
            playerShips--;
            recentHit = false;
            if (playerShips == 0)
            {
                gameOver = true;
                cout << "Tough break! You lose." << endl;
            }
        }
    }
}
