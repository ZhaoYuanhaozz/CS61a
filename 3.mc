```
void dfs() {
    int k = 0;
    int infoRobo[3][3];
    
    //Scan current area seen by the robot and store in infoRobo array
    scanFromRobot(infoRobo);  

    int new_dir, new_y, new_x;
    
    //Iterate over all 4 possible directions in a clockwise manner
    for (int s = 0; s < 4; s++) {
        //Calculate new direction, y-coordinate, and x-coordinate based on previous direction and movement
        new_dir = (dir + k) % 4;
        new_y = y + dy[new_dir];
        new_x = x + dx[new_dir];
        
        //If next cell is an obstacle or has already been visited, skip to next direction
        if (infoRobo[1 + dy[s]][1 + dx[s]] || visited[new_y * 100 + new_x]) {
            k = (k + 1) % 4;
            continue;
        }       

        //Move robot according to next direction and update direction, y-coordinate, and x-coordinate 
        moveRobot(k);
        dir = new_dir; 
        y = new_y; 
        x = new_x;
        visited[(y * 100 + x)] = true;      
        int prev_dir = dir;

        //Recursive call to continue cleaning in new position
        dfs();      

        //Calculate reverse direction and move robot back to previous position
        int rk = (prev_dir + 2 - dir + 4) % 4;      
        moveRobot(rk);
        dir = (dir + rk) % 4; 
        y = y + dy[dir]; 
        x = x + dx[dir];
        k = 3;
    }
}

/* 
1. `prev_dir + 2`将之前的方向`prev_dir`旋转180度，因为有四个方向（0,1,2,3），加2可以有效的反转方向。 例如，如果 `prev_dir` 为 0（向上），则 `prev_dir + 2` 将为 2（向下）。

2. `-dir` 给出反向方向相对于当前方向`dir` 的相对位置。 例如，如果 `dir` 为 1（左）且 `prev_dir` 为 0（上），则 `prev_dir + 2 - dir` 将为 -1。

3. `(prev_dir + 2 - dir + 4)` 将步骤 2 的结果加 4。这确保结果为正，并且它映射到范围 `[0, 3]`。 例如，如果 `prev_dir` 为 0 (UP)，`dir` 为 1 (LEFT)，并且步骤 2 的结果为 -1，则此表达式将为 `(0 + 2 - 1 + 4)`，即 等于 5。

4. `(prev_dir + 2 - dir + 4) % 4` 取模 4 以确保结果在 `[0, 3]` 范围内。 例如，如果第 3 步的结果为 5，则模数乘以 4 将得到 1，如果机器人的方向为 1（左）且之前的方向为 0（上），这就是 `rk` 的正确值 .

因此，对`rk`的简单解释是，它表示机器人当前方向的反方向，将之前的方向旋转180度减去当前方向计算得到。


当然！

rk 计算如下：
- prev_dir 是递归调用 dfs() 之前机器人所面对的方向。
- dir 是递归调用 dfs() 后机器人当前面对的方向。
- rk 是使机器人沿与它刚刚移动的相反方向移动的命令，以返回到递归调用 dfs() 之前它所在的先前位置。

所以，为了计算rk，我们首先将2加到prev_dir来转身面向相反的方向。 然后我们从这个值中减去 dir 以找到两个位置之间的方向差异。 我
们将这个差值加 4 以确保它是一个正值，最后我们将结果对 4 取模以获得使机器人朝相反方向移动的正确命令。

这是一个例子：
- 假设机器人面朝北（方向 0）并向前移动到一个新位置，面朝东（方向 3）。
- 机器人从这个新位置递归调用 dfs()。
- 递归调用后，机器人需要回到原来的位置，面向北方。
- prev_dir 为 0，dir 为 3。
- 我们将 2 添加到 prev_dir 以转身面向南（方向 2）。
- 我们从这个值中减去 dir 得到 -1 (2 - 3 = -1)。
- 我们加 4 得到 3 (4 - 1 = 3)。
- 最后，我们将结果对 4 取模得到使机器人向相反方向移动的命令，即 1 (3 % 4 = 1)。 这对应于左转。


我们不能直接设置 rk = 2 的原因是机器人需要移动以返回其先前位置的方向取决于它递归调用 dfs() 时它所面对的方向。

例如，假设机器人面朝北（方向 0）并向前移动到一个新位置，面朝东（方向 3）。 
在对 dfs() 进行递归调用后，机器人需要移回其先前的位置，面向北方。 如果我们简单地设置 rk = 2，机器人就会转身面向南方，这是错误的方向。

为了回到之前的位置，机器人需要转身并面向与之前面对的方向相反的方向。 
这意味着 rk 的值取决于先前的方向 (prev_dir) 和当前的方向 (dir)。 因此，我们需要根据这些值来计算 rk，正如我在之前的回答中所解释的那样。



当机器人处于某个位置并面向某个方向时，它可以执行四种可能的命令：前进、左转、右转或掉头。 
将机器人朝刚移动的相反方向移动的命令取决于它移动前所面对的方向，以及它现在所面对的方向。

假设机器人面朝北（方向 0）并向前移动到一个新位置，面朝东（方向 3）。 在对 dfs() 进行递归调用后，机器人需要移回其先前的位置，面向北方。 为此，机器人需要执行将其移动到与刚刚移动的相反方向的命令，即转身并面向南方。

如果我们简单地设置 rk = 2，机器人将向左转而不是转身，因为 rk 的值取决于先前的方向 (prev_dir) 和当前的方向 (dir)。 本例中prev_dir为0，dir为3，所以我们需要计算rk如下：

- 将 2 添加到 prev_dir 以转身面向南（方向 2）。
- 从该值中减去 dir 得到 -1 (2 - 3 = -1)。
- 添加 4 得到 3 (4 - 1 = 3)。
- 最后，将结果取模 4 以获得使机器人朝相反方向移动的正确命令，即 1 (3 % 4 = 1)。 这对应于左转。

我希望这个解释更清楚。 如果您还有其他问题，请告诉我！

好的，下面是整个dfs()函数的流程：

1. 首先，我们定义一个3x3的矩阵infoRobo，用来存储当前机器人周围的地图状态。

2. 调用scanFromRobot()函数，将当前机器人周围的地图状态存储到infoRobo矩阵中。

3. 接下来，我们循环4次，分别表示机器人向上、向左、向下、向右移动。

4. 对于每个方向，我们计算出新的方向new_dir、新的坐标new_y和new_x。

5. 如果新坐标已经被访问过，或者新坐标对应的地图状态为1（即障碍物），则我们跳过这个方向，继续下一个方向的尝试。

6. 否则，我们调用moveRobot()函数，将机器人移动到新的坐标，并更新机器人的方向和坐标。

7. 标记新的坐标为已访问。

8. 接下来，我们递归调用dfs()函数，处理下一个格子。

9. 递归返回后，我们需要将机器人移动回到上一个格子。

10. 我们计算出机器人需要先向相反的方向（即旋转180度）转身，然后移动到上一个格子。

11. 调用moveRobot()函数，将机器人移动到上一个格子，并更新机器人的方向和坐标。

12. 标记上一个格子为已访问。

13. 最后，我们设置k=3，表示下一次循环尝试向右移动。

14. 如果所有的方向都尝试过了，函数将会返回。



 */







```

void dfs() {
    // Initialize starting direction, y-coordinate, and x-coordinate of robot
    int direction = 0;
    int y = N;
    int x = N;

    // Mark starting cell as visited
    visited[y * 100 + x] = true;

    // Keep track of the number of clockwise turns made in each cell
    int clockTurns = 0;

    // Continue cleaning until all cells are visited or move limit is reached
    while (clockTurns < 4) {
        // Scan current area seen by the robot and store in infoRobot array
        int infoRobot[3][3];
        scanFromRobot(infoRobot);

        // Look for an unvisited cell in a clockwise direction
        bool found = false;
        for (int i = 0; i < 4; i++) {
            int newDir = (direction + i) % 4;
            int newY = y + dy[newDir];
            int newX = x + dx[newDir];

            // Check if cell is unvisited and not an obstacle
            if (!visited[newY * 100 + newX] && infoRobot[1 + dy[i]][1 + dx[i]] == 0) {
                // Move robot to new cell and update direction, y, and x
                moveRobot(i);
                direction = newDir;
                y = newY;
                x = newX;

                // Mark new cell as visited
                visited[y * 100 + x] = true;

                // Reset clockwise turns counter
                clockTurns = 0;

                // Break out of loop and continue cleaning from new cell
                found = true;
                break;
            }
        }

        // If a valid cell cannot be found, make a clockwise turn
        if (!found) {
            moveRobot(1); // Right turn
            direction = (direction + 1) % 4;
            clockTurns++;
        }
    }

    // Return robot to starting position and direction 
    int reverseCmd = (direction + 2) % 4;
    moveRobot(reverseCmd);
    direction = (direction + reverseCmd) % 4;
    y = N;
    x = N;
    visited[y * 100 + x] = true; // Mark starting cell as visited
}
