#include <string>
#include <vector>
#include <queue>
#include <algorithm>
//using namespace std;

unsigned int kittens( const std::string cards, size_t players) {
    
    std::queue<char> cardsQ = std::queue<char>();

    //Put cards in queue
    for (size_t i = 0; i < cards.length(); i++)
    {
        cardsQ.push(cards[i]);
    }

    //Array with the count of saving cards for each player
    std::vector<int> sCards = std::vector<int>();
    //Initialize the array with 0 for all values
    for (size_t i = 0; i < players; i++)
    {
        sCards.push_back(0);
    }

    int initPlayersCount = players;

    while (players > 1)
    {
        for (size_t i = 0; i < initPlayersCount; i++)
        {
            //Draw a card only if the current player is still in the game and if there are cards left in the deck
            if (sCards[i] >= 0 && !cardsQ.empty())
            {
                char topCard = cardsQ.front(); //O B S
                if (topCard == 'S')
                {
                    sCards[i]++;
                }
                else if (topCard == 'B')
                {
                    sCards[i]--;
                    if (sCards[i] >= 0)
                    {            
                        cardsQ.push(topCard);
                    }
                    else
                    {
                        players--;
                    }
                    
                }
                cardsQ.pop();
            }
        }
    }

    //Get the winner of the game
    for (size_t i = 0; i < initPlayersCount; i++)
    {
        if (sCards[i] >= 0) return i + 1;
    }
}

int bfs(const std::vector<std::vector<int>>& g, int from, int to) {
    
    if (from == to) return 0;

    std::vector<int> visitedNodes = { from };
    std::queue<int> currentNodes = std::queue<int>();
    currentNodes.push(from);
    currentNodes.push(-1);

    int distance = 1;

    while (!currentNodes.empty())
    {
        int currentNode = currentNodes.front();

        if (currentNode < 0)
        {
            currentNodes.pop();
            if (currentNodes.empty()) return -1;
            currentNodes.push(-1);         
            distance++;
            continue;
        }

        for (size_t i = 0; i < g[currentNode].size(); i++)
        {
            int newNode = g[currentNode][i];

            if (newNode == to) return distance;
            else if (std::count(visitedNodes.begin(), visitedNodes.end(), newNode) <= 0)
            {
                currentNodes.push(newNode);
                visitedNodes.push_back(newNode);
            }
            
        }
        currentNodes.pop();
    }

    //If we get here, then something went horribly wrong
    return -1;
}

unsigned int horse( const std::string from, const std::string to) {

    //If a tile is -1, then it hasn't been visited before. 
    //Otherwise, the number on the tile shows the least number of steps required to get from the starting tile to that tile
    std::vector<std::vector<int>> board;

    //This holds all the moves that the knight is about to do
    std::queue<std::vector<int>> kMoves;

    //These two arrays hold the offsets for the possible moves of the knight, starting from Top-Left and going clockwise until Left-Top
    std::vector<int> knigthMoves_RowOffsets = std::vector<int>{ -2, -2, -1, 1, 2, 2, 1, -1 };
    std::vector<int> knigthMoves_ColOffsets = std::vector<int>{ -1, 1, 2, 2, 1, -1, -2, -2 };
    
    //Initialize chess board with knights steps from it  
    for (size_t i = 0; i < 8; i++)
    {
        board.push_back(std::vector<int>{});
        for (size_t y = 0; y < 8; y++)
        {
            board[i].push_back(-1);
        }
    }

    //Parse the from and to strings into coordinates
    int startCol = from[0] - 'A';
    int startRow = '8' - from[1]; //In index for array
    int endCol = to[0] - 'A';
    int endRow = '8' - to[1];

    //Add the starting point to the board
    board[startRow][startCol] = 0;

    //Add the starting position to the knight's moves
    kMoves.push(std::vector<int>{startRow, startCol});

    //Create a lambda function for checking if coordinates are inside board
    auto insideBoard = [](int row, int col)
    {
        return row >= 0 && row <= 7 && col >= 0 && col <= 7;
    };

    //Start BFS search of the board
    while (!kMoves.empty())
    {
        std::vector<int> currentMove = kMoves.front();
        kMoves.pop();

        int moveRow = currentMove[0];
        int moveCol = currentMove[1];

        if (moveRow == endRow && moveCol == endCol) return board[moveRow][moveCol];

        //If we get here, then we decide all the possible subsequent moves for the knight from the current position 
        for (size_t i = 0; i < 8; i++)
        {
            int newMoveRow = moveRow + knigthMoves_RowOffsets[i];
            int newMoveCol = moveCol + knigthMoves_ColOffsets[i];

            //If the new move is inside the boundaries of the board and we haven't visited the new tile yet, then add it for visitation
            if (insideBoard(newMoveRow, newMoveCol) && board[newMoveRow][newMoveCol] < 0)
            {
                kMoves.push(std::vector<int> {newMoveRow, newMoveCol});
                board[newMoveRow][newMoveCol] = board[moveRow][moveCol] + 1;
            }
        }
    }

    //This should never happen because the board is bigger than 4x4 which means all tiles are reachable
    return -1;
}

unsigned int islands(const std::vector<std::vector<int>>& g) {
    
    std::queue<std::vector<int>> nextToCheck;

    std::vector<std::vector<int>> gCopy = std::vector<std::vector<int>>();
    for (size_t i = 0; i < g.size(); i++)
    {
        gCopy.push_back(std::vector<int>{});
        for (size_t y = 0; y < g[i].size(); y++)
        {
            gCopy[i].push_back(g[i][y]);
        }
    }

    //The row and col offsets for the adjacent tiles
    std::vector<int> adjacentTiles_RowOffsets = std::vector<int>{ -1, 0, 1, 0 };
    std::vector<int> adjacentTiles_ColOffsets = std::vector<int>{ 0, 1, 0, -1 };

    int countOfIslands = 0;

    for (int i = 0; i < gCopy.size(); i++)
    {
        for (int y = 0; y < gCopy[i].size(); y++)
        {
            int tile = gCopy[i][y];
            if (tile == 1)
            {
                nextToCheck.push(std::vector<int> { i, y });

                while (!nextToCheck.empty())
                {
                    int currentTileX = nextToCheck.front()[0];
                    int currentTileY = nextToCheck.front()[1];
                    nextToCheck.pop();
                    gCopy[currentTileX][currentTileY] = 2;

                    //Make lambda function for checking if coords are inside boundaries of map
                    auto tileInBounds = [gCopy, i](int adjacentTileX, int adjacentTileY)
                    {
                        return adjacentTileX >= 0 && adjacentTileX < gCopy.size() && adjacentTileY >= 0 && adjacentTileY < gCopy[i].size();
                    };

                    //Check the adjacent tiles
                    for (size_t z = 0; z < 4; z++)
                    {
                        int adjacentTileX = currentTileX + adjacentTiles_RowOffsets[z];
                        int adjacentTileY = currentTileY + adjacentTiles_ColOffsets[z];

                        if (tileInBounds(adjacentTileX, adjacentTileY) && gCopy[adjacentTileX][adjacentTileY] == 1) nextToCheck.push(std::vector<int>{adjacentTileX, adjacentTileY});
                    }
                    
                }

                countOfIslands++;
            }
        }
    }

    return countOfIslands;
}

