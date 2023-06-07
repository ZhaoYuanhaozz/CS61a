#include <queue>

void cleanHouse(int mLimitMoveCount)
{
    // Initialize variables
    int N = mLimitMoveCount / 2;
    int dir, y, x, moveCount = 0;
    dir = y = x = N;

    // Create queue and visited array
    std::queue<std::pair<int, int>> q;
    q.push({y, x});
    std::vector<std::vector<bool>> visited(2 * N + 1, std::vector<bool>(2 * N + 1));

    // Mark starting position as visited
    visited[y][x] = true;

    // Process queue
    while (!q.empty()) {
        // Dequeue next element
        std::pair<int, int> curr = q.front();
        q.pop();

        // Scan current state of the house seen by the robot
        int infoRobo[3][3];
        scanFromRobot(infoRobo);

        // Iterate through all four possible directions
        for (int k = 0; k < 4; k++) {
            int new_dir = (dir + k) % 4;
            int new_y = curr.first + dy[new_dir];
            int new_x = curr.second + dx[new_dir];
            
            // Check if move is valid
            if (!visited[new_y][new_x] && !infoRobo[1 + dy[new_dir]][1 + dx[new_dir]]) {
                q.push({new_y, new_x});
                visited[new_y][new_x] = true;
                
                // Move robot to new position
                moveRobot(k);
                dir = new_dir; y = new_y; x = new_x;
                moveCount++;

                // Check if maximum move count is reached
                if (moveCount >= mLimitMoveCount) {
                    return;
                }
            }
        }
    }
}
```
