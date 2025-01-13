// @author: gezhipeng @ 20250101
// @file: ListNode.h
// @brief: ListNode
#ifndef SRC_LEETCODE_BASE_LISTNODE_H_
#define SRC_LEETCODE_BASE_LISTNODE_H_
#include "common/glog.h"
namespace leetcode {
struct ListNode {
  int val;
  ListNode *next;
  ListNode(int x) : val(x), next(nullptr) {}
};

inline ListNode *AssignListNode(const std::vector<int> &values) {
  if (values.empty()) {
    return nullptr;
  }
  ListNode *head = new ListNode(0); // dummy head
  ListNode *cur = head;
  for (const auto &value : values) {
    cur->next = new ListNode(value);
    cur = cur->next;
  }
  return head->next;
}

inline void PrintListNode(ListNode *head) {
  std::string res = "";
  while (head) {
    res += std::to_string(head->val) + "->";
    head = head->next;
  }
  res += "nullptr";
  LOG_DEBUG << res;
}
} // namespace leetcode
#endif // SRC_LEETCODE_BASE_LISTNODE_H_