#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define GRID_SIZE 10
#define SHIP_SIZE 5

typedef struct {
    int x;
    int y;
} Position;

typedef struct {
    Position positions[SHIP_SIZE];
    int hits;
} Ship;

void initializeGrid(int grid[GRID_SIZE][GRID_SIZE]) {
    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            grid[i][j] = 0;
        }
    }
}

void placeShip(int grid[GRID_SIZE][GRID_SIZE], Ship *ship, int startX, int startY, int horizontal) {
    for (int i = 0; i < SHIP_SIZE; i++) {
        if (horizontal) {
            ship->positions[i].x = startX + i;
            ship->positions[i].y = startY;
            grid[startY][startX + i] = 1;
        } else {
            ship->positions[i].x = startX;
            ship->positions[i].y = startY + i;
            grid[startY + i][startX] = 1;
        }
    }
    ship->hits = 0;
}

void displayGrid(int grid[GRID_SIZE][GRID_SIZE], int showShips) {
    printf("  0 1 2 3 4 5 6 7 8 9\n");
    for (int i = 0; i < GRID_SIZE; i++) {
        printf("%d ", i);
        for (int j = 0; j < GRID_SIZE; j++) {
            if (grid[i][j] == 0) printf(". ");
            else if (grid[i][j] == 1 && showShips) printf("S ");
            else if (grid[i][j] == 2) printf("X ");
            else if (grid[i][j] == 3) printf("O ");
            else printf(". ");
        }
        printf("\n");
    }
}

int main() {
    srand(time(NULL));
    
    int playerGrid[GRID_SIZE][GRID_SIZE];
    int enemyGrid[GRID_SIZE][GRID_SIZE];
    int playerTargetGrid[GRID_SIZE][GRID_SIZE];
    
    initializeGrid(playerGrid);
    initializeGrid(enemyGrid);
    initializeGrid(playerTargetGrid);
    
    Ship playerShip, enemyShip;
    
    // Place player ship
    printf("=== Battleship Game ===\n");
    printf("Place your ship (5 cells):\n");
    int px, py, ph;
    printf("Enter start X (0-9): ");
    scanf("%d", &px);
    printf("Enter start Y (0-9): ");
    scanf("%d", &py);
    printf("Horizontal? (1=yes, 0=no): ");
    scanf("%d", &ph);
    
    placeShip(playerGrid, &playerShip, px, py, ph);
    
    // Place enemy ship randomly
    placeShip(enemyGrid, &enemyShip, rand() % 6, rand() % 6, rand() % 2);
    
    int playerShots = 0, enemyShots = 0;
    
    while (playerShip.hits < SHIP_SIZE && enemyShip.hits < SHIP_SIZE) {
        printf("\n--- Your Turn ---\n");
        displayGrid(playerTargetGrid, 0);
        
        int sx, sy;
        printf("Enter target X: ");
        scanf("%d", &sx);
        printf("Enter target Y: ");
        scanf("%d", &sy);
        
        if (playerTargetGrid[sy][sx] == 0) {
            for (int i = 0; i < SHIP_SIZE; i++) {
                if (enemyShip.positions[i].x == sx && enemyShip.positions[i].y == sy) {
                    printf("HIT!\n");
                    playerTargetGrid[sy][sx] = 2;
                    enemyShip.hits++;
                    break;
                }
            }
            if (playerTargetGrid[sy][sx] == 0) {
                printf("MISS!\n");
                playerTargetGrid[sy][sx] = 3;
            }
        }
        
        // Enemy turn
        printf("\n--- Enemy Turn ---\n");
        int ex = rand() % GRID_SIZE;
        int ey = rand() % GRID_SIZE;
        
        for (int i = 0; i < SHIP_SIZE; i++) {
            if (playerShip.positions[i].x == ex && playerShip.positions[i].y == ey) {
                printf("Enemy hit your ship!\n");
                playerGrid[ey][ex] = 2;
                playerShip.hits++;
                break;
            }
        }
    }
    
    if (enemyShip.hits == SHIP_SIZE) {
        printf("\n*** YOU WIN! ***\n");
    } else {
        printf("\n*** YOU LOSE! ***\n");
    }
    
    return 0;
}