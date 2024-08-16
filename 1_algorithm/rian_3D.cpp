#include <bits/stdc++.h>
using namespace std;

// 407. 接雨水 II
//  题目：给定一个 m x n
//  的矩阵，其中的值均为非负整数，表示海拔高度。将这个矩阵看作是一个二维的容器，当下雨之后，能够装多少水？
//  例如：下面是一个 3x6 的矩阵
//  [
//    [1, 4, 3, 1, 3, 2],
//    [3, 2, 1, 3, 2, 4],
//    [2, 3, 3, 2, 3, 1]
//  ]
//  返回 4

// 这里使用优先队列来解决这个问题
struct Cell
{
    int x, y, h;
    Cell(int x, int y, int h) : x(x), y(y), h(h)
    {
    }
    bool operator<(const Cell &c) const
    {
        return h > c.h;
    }
};
class Solution_1
{
  public:
    int trap(vector<vector<int>> &heightMap)
    {
        // 先进行边界处理，将边界的点加入到优先队列中
        int m = heightMap.size();
        int n = heightMap[0].size();
        int res = 0;
        vector<vector<bool>> visited(m, vector<bool>(n, false));
        // 优先队列中存放的是边界的点
        priority_queue<Cell> q;
        for (int i = 0; i < m; i++)
        {
            q.push(Cell(i, 0, heightMap[i][0]));
            q.push(Cell(i, n - 1, heightMap[i][n - 1]));
            visited[i][0] = visited[i][n - 1] = true;
        }
        // 这里只需要遍历四个边界，因为四个边界的点已经加入到优先队列中了
        for (int i = 1; i < n - 1; i++)
        {
            q.push(Cell(0, i, heightMap[0][i]));
            q.push(Cell(m - 1, i, heightMap[m - 1][i]));
            visited[0][i] = visited[m - 1][i] = true;
        }
        // 这里使用四个方向来遍历
        vector<vector<int>> dirs = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
        while (!q.empty())
        {
            auto cell = q.top();
            q.pop();
            for (auto dir : dirs)
            {
                int x = cell.x + dir[0];
                int y = cell.y + dir[1];
                if (x >= 0 && x < m && y >= 0 && y < n && !visited[x][y])
                {
                    res += max(0, cell.h - heightMap[x][y]);
                    q.push(Cell(x, y, max(cell.h, heightMap[x][y])));
                    visited[x][y] = true;
                }
            }
        }
        return res;
    }
};

// 通过计算截面积来解决这个问题
class Solution_2
{
  public:
    int trap(vector<vector<int>> &heightMap)
    {
        // 先计算每个位置的左边最大值，右边最大值，上边最大值，下边最大值
        int m = heightMap.size();
        int n = heightMap[0].size();
        int res = 0;
        vector<vector<int>> left_max(m, vector<int>(n));
        vector<vector<int>> right_max(m, vector<int>(n));
        vector<vector<int>> up_max(m, vector<int>(n));
        vector<vector<int>> down_max(m, vector<int>(n));
        // 计算每个位置的左边最大值和右边最大值
        for (int i = 0; i < m; i++)
        {
            left_max[i][0] = heightMap[i][0];
            for (int j = 1; j < n; j++)
            {
                left_max[i][j] = max(left_max[i][j - 1], heightMap[i][j]);
            }
            right_max[i][n - 1] = heightMap[i][n - 1];
            for (int j = n - 2; j >= 0; j--)
            {
                right_max[i][j] = max(right_max[i][j + 1], heightMap[i][j]);
            }
        }
        for (int j = 0; j < n; j++)
        {
            up_max[0][j] = heightMap[0][j];
            for (int i = 1; i < m; i++)
            {
                up_max[i][j] = max(up_max[i - 1][j], heightMap[i][j]);
            }
            down_max[m - 1][j] = heightMap[m - 1][j];
            for (int i = m - 2; i >= 0; i--)
            {
                down_max[i][j] = max(down_max[i + 1][j], heightMap[i][j]);
            }
        }
        // 计算每个位置的蓄水量，取四个方向的最小值
        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < n; j++)
            {
                res += min(left_max[i][j], min(right_max[i][j], min(up_max[i][j], down_max[i][j]))) - heightMap[i][j];
            }
        }
        return res;
    }
};

int main()
{
    vector<vector<int>> heightMap = {
        {3, 3, 3, 3, 3}, {3, 2, 2, 2, 3}, {3, 2, 1, 2, 3}, {3, 2, 2, 2, 3}, {3, 3, 3, 3, 3}}; // 10

    Solution_1 s1;
    cout << s1.trap(heightMap) << endl;

    Solution_2 s2;
    cout << s2.trap(heightMap) << endl;
}