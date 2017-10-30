/* 
 * File:   easyTests.h
 * Author: alec
 *
 * Created on October 25, 2017, 2:53 PM
 */

#ifndef LEETCODETESTS_H
#define LEETCODETESTS_H
#include <cstdlib>
#include <string>
#include <map>
#include <iostream>
#include <unordered_set>
#include <string>
#include <exception>
#include <vector>
#include <utility>
using namespace std;
//! Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;

    ListNode(int x) : val(x), next(NULL) {
    }
};
inline void deleteList(ListNode*);
//! Easy
//! Reverse string in place and return it
//! https://leetcode.com/problems/reverse-string/description/
string reverseString(const string & s) {
    //fast option 2N memory:
    string result;
    for (int i = s.length()-1; i>=0; --i) 
        result.push_back(s[i]);

    return result;
}
void reverseStringInPlace(string & s) {
    //slow option:
    int strLen = s.length();
    string buffer;
    for (int i = 0; i < strLen / 2; ++i) {
        buffer = s[i];
        s[i] = s[strLen - i - 1];
        s[strLen - i - 1] = buffer[0];
    }
}
//! Easy. Given a roman numeral, convert it to an integer. Input is guaranteed to be within the range from 1 to 3999.
//! https://leetcode.com/problems/roman-to-integer/description/
int romanToInt(const string & s) {
    //O(N) running time
    //MCIV or LIX or whatever
    //Map of values
    map<char, int> romanNum;
    romanNum.insert(make_pair('I', 1));
    romanNum.insert(make_pair('V', 5));
    romanNum.insert(make_pair('X', 10));
    romanNum.insert(make_pair('L', 50));
    romanNum.insert(make_pair('C', 100));
    romanNum.insert(make_pair('D', 500));
    romanNum.insert(make_pair('M', 1000));
    //accumulators:
    int intSum = 0, intBuffer, intLastNumber = 0;

    //traverse from end to start
    for (int i = s.length() - 1; i >= 0; --i) {
        //get decimal of the sign:
        intBuffer = romanNum[s[i]];
        //if the decimal value is less then last decimal then this is substruction number
        intBuffer = intBuffer < intLastNumber ? intBuffer*-1 : intBuffer;
        //save last decimal after that
        intLastNumber = intBuffer > 0 ? intBuffer : intLastNumber;
        //accumulate values
        intSum += intBuffer;
    }
    return intSum;
}

//! Medium. You are given two non-empty linked lists representing two non-negative integers. The digits are stored in reverse order
//! and each of their nodes contain a single digit. Add the two numbers and return it as a linked list.
//! https://leetcode.com/problems/add-two-numbers/description/
ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
    //O(n) running time
    ListNode* node1 = l1;
    ListNode* node2 = l2;
    ListNode* resultHeadNode = new ListNode(0);
    ListNode* prevNode = resultHeadNode;
    ListNode* currentNode = resultHeadNode;
    int intRegister, intNextOrder = 0;
    bool bContinue;

    bContinue = (node1 || node2) ? true : false;

    while (bContinue) {
        intRegister = intNextOrder;

        if (node1) {
            intRegister += node1->val;
            node1 = node1->next;
        }

        if (node2) {
            intRegister += node2->val;
            node2 = node2->next;
        }

        intNextOrder = intRegister >= 10 ? 1 : 0;
        currentNode->val = intRegister % 10;
        bContinue = (node1 || node2 || intNextOrder) ? true : false;

        if (bContinue) {
            prevNode = currentNode;
            currentNode = new ListNode(0);
            prevNode->next = currentNode;
            currentNode->next = NULL;
        }
    }
    //C style...
    return resultHeadNode;
}
//! Easy
//! Reverse single linked list
//! https://leetcode.com/problems/reverse-linked-list/description/
ListNode* reverseList(ListNode* head) {
    //O(n) running time
    ListNode* current = head;
    ListNode* prevNode = NULL;
    ListNode* nextNode;

    while (current) {
        nextNode = current->next;
        current->next = prevNode;
        prevNode = current;
        current = nextNode;
    }
    head = prevNode;
    return prevNode;
}
//! Easy
//! Given a singly linked list, determine if it is a palindrome.
//! https://leetcode.com/problems/palindrome-linked-list/description/
bool isPalindrome(ListNode* head) {
    //O(n) running time and O(1) space
    //We will make a copy of the list and then break the list in two parts then reverse *left* part and compare left and right.
    //Edge cases:
    if (head == NULL || head->next == NULL)
        return true;

    int intCountNodes = 1;
    ListNode* current = head;
    ListNode* nextNode = NULL;
    ListNode* prevNode = NULL;
    ListNode* newHeadLeft = NULL;
    ListNode* newHeadRight = NULL;
    ListNode* localHead = new ListNode(head->val);
    prevNode = localHead;
    //1. count all nodes
    while (current->next) {
        ++intCountNodes;
        current = current->next;//initial array
        nextNode = new ListNode(current->val);//make a copy
        prevNode->next = nextNode;
        prevNode = nextNode;
    }
    nextNode->next = NULL;
    prevNode = NULL;
    //2. traverse to the middle and revert *left* part
    current = localHead;
    nextNode = localHead;
    
    for (int i = 0; i < intCountNodes / 2; i++) {
        nextNode = current->next;
        current->next = prevNode;
        prevNode = current;
        current = nextNode;
    }
    newHeadLeft = prevNode;
    newHeadRight = current;
    //odd nodes quantity - traverse one step right
    if (intCountNodes%2 != 0)
        current = current->next;
    //3. compare reversed left and right
    //now: prevNode - left head, current - right head

    bool result = true;
    while (current)
    {
        if (current->val != prevNode->val){
            result = false;
            break;
        }
        prevNode = prevNode->next;
        current = current->next;
    }

    deleteList(newHeadLeft);
    deleteList(newHeadRight);
    return result;
}
//! Given an array S of n integers, are there elements a, b, c in S such that a + b + c = 0? Find all unique 
//! triplets in the array which gives the sum of zero.
//! https://leetcode.com/problems/3sum/description/
//vector<vector<int>> threeSum(vector<int>& nums) 

//! Can the string permute to a palindrome?
bool hasPalindromePermutation(const string& str)
{
    // track characters we've seen an odd number of times
    unordered_set<char> unpairedCharacters;

    for (char c : str) {
        if (unpairedCharacters.find(c) != unpairedCharacters.end()) {
            unpairedCharacters.erase(c);
        }
        else {
            unpairedCharacters.insert(c);
        }
    }

    // the string has a palindrome permutation if it
    // has one or zero characters without a pair
    return unpairedCharacters.size() <= 1;
}
class TwoSumSolution{
    public:
        vector<int> twoSumV1(vector<int>& nums, int target)
        {
            for (auto i: nums) {
                for (int j = i + 1; j < nums.size(); j++) {
                    if (nums[j] == target - nums[i]) {
                        return vector<int> { i, j };
                    }
                }
            }
            throw invalid_argument("No two sum solution");
        }
        //! 
        vector<int> twoSumV2(vector<int>& nums, int target)
        {
            map<int,int> hashTable;
            int idx = 0;

            for (auto i: nums) {
                auto complement = target - i;//get diff value: 6-3
                
                if (hashTable.count(complement)) {
                    return vector<int> { hashTable.at(complement), idx };
                }
                //hashTable.insert(make_pair<int,int>((int)nums[idx],(int)idx));
                hashTable.insert(make_pair<int,int>((int)i,(int)idx));
                ++idx;
            }
            
            throw invalid_argument("No two sum solution");
        }
};
//! Two Sum
//! https://leetcode.com/problems/two-sum/description/
/*Given an array of integers, return indices of the two numbers such that they add up to a specific target.
You may assume that each input would have exactly one solution, and you may not use the same element twice.

Example:

Given nums = [2, 7, 11, 15], target = 9,

Because nums[0] + nums[1] = 2 + 7 = 9,
return [0, 1].

*/
void findIndicesOfTwoSum(){
    TwoSumSolution twoSum;
    vector<int> nums = {3,3,1};
    cout << "[";
    for(auto i : nums)
        cout << i << " ";
    cout << "]";
    int target = 6;
    cout << " target number = " << target ;
    
    //vector<int> sums = twoSum.twoSumV1(nums, target);
    vector<int> sums = twoSum.twoSumV2(nums, target);
    cout << " found two indices: [";
    for(auto i : sums)
        cout << i << " " ;
    cout << "]" << endl;
}

//! Test all my leetcode algorithms
void leetcodeTest() {
    //***********************************************************************************
    //1. reverse string in place
    string str = "abcdef";
    string strRev = reverseString(str);
    cout << "1. Reverse of " << str << " is " << strRev << endl;
    //***********************************************************************************
    //2. convert roman number to arabic number
    string romanNumber = "MCDLIV";
    cout << "2. Roman number " << romanNumber << " is actually " << romanToInt(romanNumber) << endl;

    //3. add two numbers with digits split in lists in reverse order, return similar linked list
    ListNode* node1 = new ListNode(2);
    ListNode* node2 = new ListNode(5);
    ListNode* newNode;
    ListNode* currentNode = node1;

    newNode = new ListNode(4);
    currentNode->next = newNode;
    currentNode = newNode;
    newNode = new ListNode(3);
    currentNode->next = newNode;
    newNode->next = NULL;

    currentNode = node2;
    newNode = new ListNode(6);
    currentNode->next = newNode;
    currentNode = newNode;
    newNode = new ListNode(4);
    currentNode->next = newNode;
    currentNode = newNode;
    newNode->next = NULL;
    //***********************************************************************************
    cout << "3. Add two numbers (342 and 465) that were put by digits into two sigle linked lists in reverse order: 2->4->3 and 5->6->4. ";
    currentNode = addTwoNumbers(node1, node2);
    newNode = currentNode;
    string strSum = "", strDigit = "";

    while (currentNode->next) {
        strDigit = std::to_string(currentNode->val);
        strSum.insert(0, strDigit);
        currentNode = currentNode ->next;
    }

    strDigit = std::to_string(currentNode->val);
    strSum.insert(0, strDigit);
    cout << "The sum is: " << strSum << endl;
    deleteList(node1);
    deleteList(node2);
    deleteList(currentNode);
    //***********************************************************************************
    cout << "4. Reverse linked list ";
    ListNode* nodeToReverse = new ListNode(1); //1->2->3 list revert to 3->2->1
    newNode = new ListNode(2);
    currentNode->next = newNode;
    currentNode = newNode;
    newNode = new ListNode(3);
    currentNode->next = newNode;
    currentNode = newNode;
    currentNode = nodeToReverse;
    cout << "[";

    while (currentNode) {
        cout << std::to_string(currentNode->val) << "->";
        currentNode = currentNode ->next;
    }
    
    cout << "NULL] ... reversed to [";
    currentNode = reverseList(nodeToReverse);
    nodeToReverse = currentNode;
    
    while (currentNode) {
        cout << std::to_string(currentNode->val) << "->";
        currentNode = currentNode ->next;
    }
    
    cout << "NULL] " << endl;
    deleteList(nodeToReverse);
    //***********************************************************************************
    cout << "5. Determine the linked list 9->1->5->1->9 is a palindrome number:";
    node1 = new ListNode(9); currentNode = node1;
    newNode = new ListNode(1); currentNode->next = newNode; currentNode = newNode;
    newNode = new ListNode(5); currentNode->next = newNode; currentNode = newNode;
    newNode = new ListNode(1); currentNode->next = newNode; currentNode = newNode;
    newNode = new ListNode(9); currentNode->next = newNode; newNode->next = NULL;
    
    bool bIsPalindrome = isPalindrome(node1);
    cout << (bIsPalindrome ? " is a PALINDROME! " : " is not a palindrome.") << endl;
    deleteList(node1);
    
    string strPermute {"sarar"};
    cout << "6. Can " << strPermute << " permute as a palindrome? ";
    cout << (hasPalindromePermutation(strPermute)?"... YES! this can permute as a palindrome":" ... cannot make a palindrome.") << endl;
    cout << "7. Return indices of the two numbers such that they add up to a specific target: ";
    findIndicesOfTwoSum();
}

//! Memory cleanup
inline void deleteList(ListNode* node) {
    ListNode* nextNode;
    while (node->next) {
        nextNode = node->next;
        delete node;
        node = nextNode;
    }
    delete node;
}

#endif /* LEETCODETESTS_H */
