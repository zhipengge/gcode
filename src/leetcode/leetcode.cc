// @author: gezhipeng @ 20250103
// @file: leetcode.cc
// @brief: leetcode
#include "leetcode.h"
namespace leetcode {
ListNode *ReverseList(ListNode *head) {
  ListNode *prev = nullptr;
  ListNode *cur = head;
  while (cur) {
    ListNode *next = cur->next;
    cur->next = prev;
    prev = cur;
    cur = next;
  }
  return prev;
}

vector<vector<string>> groupAnagrams(vector<string> &strs) {
  unordered_map<string, vector<string>> mp;
  for (const auto &str : strs) {
    string key = str;
    sort(key.begin(), key.end());
    mp[key].push_back(str);
  }
  vector<vector<string>> res;
  for (const auto &[key, value] : mp) {
    res.push_back(value);
  }
  return res;
}
int longestConsecutive(vector<int> &nums) {
  unordered_set<int> st;
  for (const auto &num : nums) {
    st.insert(num);
  }
  int res = 0;
  for (const auto &num : st) {
    if (!st.count(num - 1)) {
      int cur_num = num;
      int cur_len = 1;
      while (st.count(cur_num + 1)) {
        cur_num++;
        cur_len++;
      }
      res = max(res, cur_len);
    }
  }
  return res;
}
int maxArea(vector<int> &height) {
  int res = 0;
  int left = 0;
  int right = height.size() - 1;
  while (left < right) {
    int h = min(height[left], height[right]);
    res = max(res, h * (right - left));
    if (height[left] < height[right]) {
      left++;
    } else {
      right--;
    }
  }
  return res;
}
vector<vector<int>> threeSum(vector<int> &nums) {
  vector<vector<int>> res;
  sort(nums.begin(), nums.end());
  for (int i = 0; i < nums.size(); i++) {
    if (nums[i] > 0) {
      break;
    }
    if (i > 0 && nums[i] == nums[i - 1]) {
      continue;
    }
    int left = i + 1;
    int right = nums.size() - 1;
    while (left < right) {
      int sum = nums[i] + nums[left] + nums[right];
      if (sum == 0) {
        res.push_back({nums[i], nums[left], nums[right]});
        while (left < right && nums[left] == nums[left + 1]) {
          left++;
        }
        while (left < right && nums[right] == nums[right - 1]) {
          right--;
        }
        left++;
        right--;
      } else if (sum < 0) {
        left++;
      } else {
        right--;
      }
    }
  }
  return res;
}

int trap(vector<int> &height) {
  int n = height.size();
  if (n == 0) {
    return 0;
  }
  // calculate left max
  vector<int> left_max(n);
  left_max[0] = height[0];
  for (int i = 1; i < n; ++i) {
    left_max[i] = max(left_max[i - 1], height[i]);
  }

  // calculate right max
  vector<int> right_max(n);
  right_max[n - 1] = height[n - 1];
  for (int i = n - 2; i >= 0; --i) {
    right_max[i] = max(height[i], right_max[i + 1]);
  }
  int res = 0;
  for (int i = 0; i < n; ++i) {
    res += min(left_max[i], right_max[i]) - height[i];
  }
  return res;
}
int trap2(vector<int> &height) {
  int n = height.size();
  if (n == 0) {
    return 0;
  }
  stack<int> st;
  int res = 0;
  for (int i = 0; i < n; ++i) {
    while (!st.empty() && height[i] > height[st.top()]) {
      int top = st.top();
      st.pop();
      if (st.empty()) {
        break;
      }
      int left = st.top();
      int cur_width = i - left - 1;
      int cur_height = min(height[i], height[left]) - height[top];
      res += cur_width * cur_height;
    }
    st.push(i);
  }
  return res;
}
int lengthOfLongestSubstring(string s) {
  int n = s.size();
  if (n == 0) {
    return 0;
  }
  unordered_map<char, int> mp;
  int res = 0;
  int left = 0;
  for (int i = 0; i < n; ++i) {
    if (mp.count(s[i])) {
      left = max(left, mp[s[i]] + 1);
    }
    mp[s[i]] = i;
    res = max(res, i - left + 1);
  }
  return res;
}
} // namespace leetcode