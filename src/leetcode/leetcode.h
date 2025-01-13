// @author: gezhipeng @ 20250103
// @file: leetcode.h
// @brief: leetcode
#ifndef SRC_LEETCODE_LEETCODE_H_
#define SRC_LEETCODE_LEETCODE_H_
#include "base/list_node.h"
#include <stack>
#include <string>
#include <unordered_set>
#include <vector>
namespace leetcode {
using namespace std;
/**
 * 反转链表
 */
ListNode *ReverseList(ListNode *head);
/**
 * 49. 字母异位词分组
 * 给你一个字符串数组，请你将 字母异位词
 * 组合在一起。可以按任意顺序返回结果列表。 字母异位词
 * 是由重新排列源单词的所有字母得到的一个新单词。
 */
vector<vector<string>> groupAnagrams(vector<string> &strs);
/**
 * 128. 最长连续序列
 * 给定一个未排序的整数数组 nums
 * ，找出数字连续的最长序列（不要求序列元素在原数组中连续）的长度。
 * 请你设计并实现时间复杂度为 O(n) 的算法解决此问题。
 */
int longestConsecutive(vector<int> &nums);
/**
 * 11. 盛最多水的容器
 * 给你 n 个非负整数 a1，a2，...，an，每个数代表坐标中的一个点(i, ai)。
 * 在坐标内画 n 条垂直线，垂直线 i 的两个端点分别为(i, ai)和(i, 0)。
 * 找出其中的两条线，使得它们与 x 轴共同构成的容器可以容纳最多的水。
 * 说明：你不能倾斜容器。
 */
int maxArea(vector<int> &height);
/**
 * 15. 三数之和
 * 给你一个包含 n 个整数的数组 nums，判断 nums 中是否存在三个元素 a，b，c ，
 * 使得 a + b + c = 0 ？请你找出所有满足条件且不重复的三元组。
 */
vector<vector<int>> threeSum(vector<int> &nums);
/**
 * 42. 接雨水
 * 给定 n 个非负整数表示每个宽度为 1
 * 的柱子的高度图，计算按此排列的柱子，下雨之后能接多少雨水。
 */
int trap(vector<int> &height);
/**
 * 42. 接雨水--单调栈
 * 给定 n 个非负整数表示每个宽度为 1
 * 的柱子的高度图，计算按此排列的柱子，下雨之后能接多少雨水。
 */
int trap2(vector<int> &height);
/**
 * 3. 无重复字符的最长子串
 * 给定一个字符串，请你找出其中不含有重复字符的 最长子串 的长度。
 */
int lengthOfLongestSubstring(string s);
} // namespace leetcode
#endif // SRC_LEETCODE_LEETCODE_H_