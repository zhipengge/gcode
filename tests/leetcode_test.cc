// @author: gezhipeng @ 20250103
// @file: leetcode_test.cc
// @brief: leetcode_test
#include "leetcode/leetcode.h"
#include <gtest/gtest.h>

TEST(ListNode, ReverseList) {
  std::vector<int> values = {1, 2, 3, 4, 5};
  leetcode::ListNode *head = leetcode::AssignListNode(values);
  leetcode::PrintListNode(head);
  leetcode::ListNode *new_head = leetcode::ReverseList(head);
  leetcode::PrintListNode(new_head);
}

TEST(HASH, groupAnagrams) {
  std::vector<std::string> strs = {"eat", "tea", "tan", "ate", "nat", "bat"};
  auto res = leetcode::groupAnagrams(strs);
  for (const auto &vec : res) {
    for (const auto &str : vec) {
      std::cout << str << " ";
    }
    std::cout << std::endl;
  }
}

TEST(HASH, longestConsecutive) {
  std::vector<int> nums = {100, 4, 200, 1, 3, 2};
  int res = leetcode::longestConsecutive(nums);
  std::cout << res << std::endl;
}

TEST(ARRAY, maxArea) {
  std::vector<int> height = {1, 8, 6, 2, 5, 4, 8, 3, 7};
  int res = leetcode::maxArea(height);
  std::cout << res << std::endl;
}

TEST(ARRAY, threeSum) {
  std::vector<int> nums = {-1, 0, 1, 2, -1, -4};
  auto res = leetcode::threeSum(nums);
  for (const auto &vec : res) {
    for (const auto &num : vec) {
      std::cout << num << " ";
    }
    std::cout << std::endl;
  }
}

TEST(ARRAY, trap) {
  std::vector<int> height = {0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1};
  int res = leetcode::trap(height);
  EXPECT_EQ(res, 6);
}