#include <memory.h>
  
  
extern void scanFromRobot(int ceilingState[3][3]);
extern int moveRobot(int mCommand);
  
  
#define MAX_N 30
#define MAX_N2 (2 * MAX_N + 1)
  
  
struct Queue
{
    int x, y, dir, prev;
} Q[MAX_N * MAX_N];
  
  
int dx[4] = { 0,-1,0,1 };
int dy[4] = { -1,0,1,0 };
int sx[4] = { -1,-1,1,1 };
int sy[4] = { -1,1,1,-1 };
int innerdx[4] = { 1,0,-1,0 };
int innerdy[4] = { 0,-1,0,1 };
int outterdx[4] = { 0,1,0,-1 };
int outterdy[4] = { 1,0,-1,0 };
int map[MAX_N2][MAX_N2];
int x, y, dir;
  
  
void init(int N, int subTaskCount)
{
  
  
}
  
  
int reverse(int cur)
{
    int Dir = -1;
  
  
    while (cur)
    {
        Dir = Q[cur].dir;
        cur = Q[cur].prev;
    }
  
  
    return Dir;
}
  
  
int visit[MAX_N2][MAX_N2];
int visitCnt;
  
  
bool findClosestUntouched(int& dir)
{
    int head = 0, tail = 0;
    visitCnt++;
    Q[tail++] = { x,y,-1,-1 };
    visit[x][y] = visitCnt;
  
  
    while (head != tail)
    {
        Queue& cur = Q[head];
  
  
        if (map[cur.x][cur.y] == 0)
        {
            dir = reverse(head);
            return true;
        }
  
  
        for (int i = 0; i < 4; i++)
        {
            int X = cur.x + dx[i];
            int Y = cur.y + dy[i];
            if (visit[X][Y] < visitCnt && map[X][Y] != 1 && map[X][Y] != -1)
            {
                visit[X][Y] = visitCnt;
                Q[tail++] = { X,Y,i,head };
            }
        }
        head++;
    }
    return false;
}
  
  
void cleanHouse(int mLimitMoveCount)
{
    x = MAX_N;
    y = MAX_N;
    dir = 0;
  
  
    memset(map, 0xff, sizeof(map));
    map[x][y] = 0;
  
  
    while (true)
    {
        int surroundings[3][3];
        int dX, dY;
        int nextDir;
  
  
        if (map[x][y] == 0)
        {
            map[x][y] = 2;
            scanFromRobot(surroundings);
  
  
            for (int i = 0; i < 3; i++)
            {
                dX = sx[dir] + i * outterdx[dir];
                dY = sy[dir] + i * outterdy[dir];
  
  
                for (int j = 0; j < 3; j++)
                {
                    if (map[x + dX][y + dY] == -1)
                    {
                        map[x + dX][y + dY] = surroundings[i][j];
                    }
                    dX += innerdx[dir];
                    dY += innerdy[dir];
                }
            }
        }
  
  
        if (findClosestUntouched(nextDir))
        {
            x += dx[nextDir];
            y += dy[nextDir];
            moveRobot((4 + nextDir - dir) % 4);
            dir = nextDir;
        }
        else
        {
            return;
        }
    }
}




<!-- ------------------------------------------------------------------------------------------ -->


extern void scanFromRobot(int ceilingState[3][3]);
extern int moveRobot(int mCommand);
 
int dy[4] = { -1, 0, 1, 0 };
int dx[4] = { 0, -1, 0, 1 };
int N;
int dir, y, x;
bool visited[6000];
 
void init(int n, int subTaskCount)
{
    N = n;
}
 
void dfs() {
    int k = 0;
    int infoRobo[3][3];
    scanFromRobot(infoRobo);
    int new_dir, new_y, new_x;
    for (int s = 0; s < 4; s++) {
        new_dir = (dir + k) % 4;
        new_y = y + dy[new_dir];
        new_x = x + dx[new_dir];
        if (infoRobo[1 + dy[s]][1 + dx[s]] || visited[new_y * 100 + new_x]) {
            k = (k + 1) % 4;
            continue;
        }       
        moveRobot(k);
        dir = new_dir; y = new_y; x = new_x;
        visited[(y * 100 + x)] = true;      
        int prev_dir = dir;
        dfs();      
        int rk = (prev_dir + 2 - dir + 4) % 4;      
        moveRobot(rk);
        dir = (dir + rk) % 4; y = y + dy[dir]; x = x + dx[dir];
        k = 3;
    }
}
 
void cleanHouse(int mLimitMoveCount)
{
    for (int i = 0; i < 2 * N * 100; i++) {
        visited[i] = false;
    }   
    dir = 0; y = N; x = N;
    visited[y * 100 + x] = true;
    dfs();
}


<!-- ------------------------------------------------------------------------------- -->



#include <memory.h>
  
  
extern void scanFromRobot(int ceilingState[3][3]);
extern int moveRobot(int mCommand);
  
  
#define MAX_N 30
#define MAX_N2 (2 * MAX_N + 1)
  
  
struct Queue
{
    int x, y, dir, prev;
} Q[MAX_N * MAX_N];
  
  
int dx[4] = { 0,-1,0,1 };
int dy[4] = { -1,0,1,0 };
int sx[4] = { -1,-1,1,1 };
int sy[4] = { -1,1,1,-1 };

int innerdx[4] = { 1,0,-1,0 };
int innerdy[4] = { 0,-1,0,1 };
int outterdx[4] = { 0,1,0,-1 };
int outterdy[4] = { 1,0,-1,0 };
int map[MAX_N2][MAX_N2];
int x, y, dir;
  
  
void init(int N, int subTaskCount)
{
  
  
}
  
  
int reverse(int cur)
{
    int Dir = -1;
    
    while (cur)
    {
        Dir = Q[cur].dir;
        cur = Q[cur].prev;
    }
  
  
    return Dir;
}
  
  
int visit[MAX_N2][MAX_N2];
int visitCnt;
  
  
bool findClosestUntouched(int& dir)
{
    int head = 0, tail = 0;
    visitCnt++;
    Q[tail++] = { x,y,-1,-1 };
    visit[x][y] = visitCnt;
  
  
    while (head != tail)
    {
        Queue& cur = Q[head];
  
  
        if (map[cur.x][cur.y] == 0)
        {
            dir = reverse(head);
            return true;
        }
  
  
        for (int i = 0; i < 4; i++)
        {
            int X = cur.x + dx[i];
            int Y = cur.y + dy[i];
            if (visit[X][Y] < visitCnt && map[X][Y] != 1 && map[X][Y] != -1)
            {
                visit[X][Y] = visitCnt;
                Q[tail++] = { X,Y,i,head };
            }
        }
        head++;
    }
    return false;
}
  
  
void cleanHouse(int mLimitMoveCount)
{
    x = MAX_N;
    y = MAX_N;
    dir = 0;
  
  
    memset(map, 0xff, sizeof(map));
    map[x][y] = 0;
  
  
    while (true)
    {
        int surroundings[3][3];
        int dX, dY;
        int nextDir;
  
  
        if (map[x][y] == 0)
        {
            map[x][y] = 2;
            scanFromRobot(surroundings);
  
  
            for (int i = 0; i < 3; i++)
            {
                dX = sx[dir] + i * outterdx[dir];
                dY = sy[dir] + i * outterdy[dir];
  
  
                for (int j = 0; j < 3; j++)
                {
                    if (map[x + dX][y + dY] == -1)
                    {
                        map[x + dX][y + dY] = surroundings[i][j];
                    }
                    dX += innerdx[dir];
                    dY += innerdy[dir];
                }
            }
        }
  
  
        if (findClosestUntouched(nextDir))
        {
            x += dx[nextDir];
            y += dy[nextDir];
            moveRobot((4 + nextDir - dir) % 4);
            dir = nextDir;
        }
        else
        {
            return;
        }
    }
}


<!-- ------------------------------------------------------------------------------------------- -->


#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>

extern void init(int, int);
extern void cleanHouse(int);

#define MAX_N (30)

static int mLimitMoveCnt = 0;
static int houseInfo[MAX_N][MAX_N];
static int isCleaned[MAX_N][MAX_N];
static int robotInfo[3] = { 0, }; // [0] : y, [1] : x, [2] : direction
static int moveRobotsCallCnt = 0;

static int dy[4] = { -1, 0, 1, 0 };
static int dx[4] = { 0, -1, 0, 1 };

static bool ok = false;

void scanFromRobot(int floorState[3][3])
{
    int robot_y = robotInfo[0];
    int robot_x = robotInfo[1];
    int direction = robotInfo[2];
    
    if (direction == 0) // UP
    {
        for (int y = robot_y - 1, sy = 0; y <= robot_y + 1; y++, sy++)
        {
            for (int x = robot_x - 1, sx = 0; x <= robot_x + 1; x++, sx++)
            {
                floorState[sy][sx] = houseInfo[y][x];
            }
        }
    }

    if (direction == 1) // LEFT
    {
        for (int y = robot_y - 1, sx = 2; y <= robot_y + 1; y++, sx--)
        {
            for (int x = robot_x - 1, sy = 0; x <= robot_x + 1; x++, sy++)
            {
                floorState[sy][sx] = houseInfo[y][x];
            }
        }
    }

    else if (direction == 2) // DOWN
    {
        for (int y = robot_y - 1, sy = 2; y <= robot_y + 1; y++, sy--)
        {
            for (int x = robot_x - 1, sx = 2; x <= robot_x + 1; x++, sx--)
            {
                floorState[sy][sx] = houseInfo[y][x];
            }
        }
    }
    else if (direction == 3) // RIGHT
    {
        for (int y = robot_y - 1, sx = 0; y <= robot_y + 1; y++, sx++)
        {
            for (int x = robot_x - 1, sy = 2; x <= robot_x + 1; x++, sy--)
            {
                floorState[sy][sx] = houseInfo[y][x];
            }
        }
    }
}

int moveRobot(int mCommand)
{
    moveRobotsCallCnt++;

    if (mCommand < 0 || mCommand >= 4)
        return 0;

    int next_dir = (robotInfo[2] + mCommand) % 4;

    int sy = robotInfo[0] + dy[next_dir];
    int sx = robotInfo[1] + dx[next_dir];

    if (houseInfo[sy][sx] == 1)
    {
        return 0;
    }
    else
    {
        robotInfo[0] = sy;
        robotInfo[1] = sx;
        robotInfo[2] = next_dir;
        isCleaned[sy][sx] = 1;
    }

    return 1;
}


static bool run()
{
    int N, subTaskCount;

    scanf("%d%d", &N, &subTaskCount);

    init(N, subTaskCount);
    ok = true;

    
    for (int i = 0; i < subTaskCount; i++)
    {   
        //  初始化设置
        for (int y = 0; y < N; y++)
        {
            for (int x = 0; x < N; x++)
            {
                scanf("%d", &houseInfo[y][x]);
				isCleaned[y][x] = 0;
            }
        }


        scanf("%d %d %d %d", &robotInfo[0], &robotInfo[1], &robotInfo[2], &mLimitMoveCnt);
        isCleaned[robotInfo[0]][robotInfo[1]] = 1;

        moveRobotsCallCnt = 0;

        cleanHouse(mLimitMoveCnt);

        if (mLimitMoveCnt < moveRobotsCallCnt)
            ok = false;
		
		for(int y = 0;y < N;y++)
		{
			for(int x = 0; x < N; x++)
			{
				if(houseInfo[y][x] == 1)
					continue;
				
				if(isCleaned[y][x] == 0)
					ok = false;
			}
		}
    }
    return ok;
}

int main()
{
    setbuf(stdout, NULL);
//    freopen("sample_input.txt", "r", stdin);
    int T, MARK;
    scanf("%d %d", &T, &MARK);

    for (int tc = 1; tc <= T; tc++)
    {
        int score = run() ? MARK : 0;
        printf("#%d %d\n", tc, score);
    }
    return 0;
}



/* ------------------------------------------------------------------------------------------- */
要写的



extern void scanFromRobot(int ceilingState[3][3]);
extern int moveRobot(int mCommand);

void init(int N, int subTaskCount)
{

}

void cleanHouse(int mLimitMoveCount)
{

}
