using namespace std;
#define N 9

char const text();
void create(int puzzle[N][N], char dif);
void remove(int puzzle[N][N], int rAmount);
void const printP(int puzzle[N][N]);
bool solve(int puzzle[N][N]);
bool getEmpty(int puzzle[N][N], int &col, int &row);
bool isSafe(int num, int puzzle[N][N], int col, int row);
