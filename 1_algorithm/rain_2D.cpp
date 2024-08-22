#include <bits/stdc++.h>
using namespace std;

// 42. 接雨水
//  题目：给定 n 个非负整数表示每个宽度为 1
//  的柱子的高度图，计算按此排列的柱子，下雨之后能接多少雨水
//  例如：[0,1,0,2,1,0,1,3,2,1,2,1]，返回 6

// 这里使用两次遍历，第一次遍历找到每个位置左边的最大值，第二次遍历找到每个位置右边的最大值，然后再遍历一次计算每个位置的蓄水量
class Solution_1 {
public:
  int trap(vector<int> &height) {
    int n = height.size();
    int res = 0;
    vector<int> left_max(n);
    vector<int> right_max(n);
    left_max[0] = height[0];
    for (int i = 1; i < n - 1; i++) {
      left_max[i] = max(left_max[i - 1], height[i]);
    }
    right_max[n - 1] = height[n - 1];
    for (int i = n - 2; i > 0; i--) {
      right_max[i] = max(right_max[i + 1], height[i]);
    }
    for (int i = 1; i < n - 1; i++) {
      res += min(left_max[i], right_max[i]) - height[i];
    }
    return res;
  }
};

// 使用单调栈来解决这个问题
class Solution_2 {
public:
  int trap(vector<int> &height) {
    int n = height.size();
    int res = 0;
    stack<int> s;
    for (int i = 0; i < n; i++) {
      // 或者使用 s.size() > 0 来判断是否为空
      while (!s.empty() && height[i] > height[s.top()]) {
        int top = s.top();
        s.pop();
        if (s.empty())
          break;
        int distance = i - s.top() - 1;
        int h = min(height[i], height[s.top()]) - height[top];
        res += distance * h;
      }
      s.push(i);
    }
    return res;
  }
};

// 使用双指针来解决这个问题
class Solution_3 {
public:
  int trap(vector<int> &height) {
    int n = height.size();
    int res = 0;
    int left = 0, right = n - 1;
    int left_max = 0, right_max = 0;
    while (left < right) {
      left_max = max(left_max, height[left]);
      right_max = max(right_max, height[right]);
      if (left_max < right_max) {
        res += left_max - height[left];
        left++;
      } else {
        res += right_max - height[right];
        right--;
      }
    }
    return res;
  }
};

int main() {
  vector<int> height = {0, 4, 0, 2, 1, 3, 1, 3, 2, 0, 2, 1}; // 10

  // 测试
  Solution_1 s1;
  cout << s1.trap(height) << endl;

  Solution_2 s2;
  cout << s2.trap(height) << endl;

  Solution_3 s3;
  cout << s3.trap(height) << endl;
  return 0;
}
