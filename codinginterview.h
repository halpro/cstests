/* 
 * File:   codinginterview.h
 * Author: alec
 *
 * Created on October 27, 2017, 12:26 PM
 */

#ifndef CODINGINTERVIEW_H
#define CODINGINTERVIEW_H
#include <unordered_set>
#include <string>
//! Calculate factorial with O(n) runtime
int factorial(int n) {
    if (n < 0)
        return -1;
    else if (n == 0)
        return 1;
    else
        return n * factorial(n - 1);
}
//! Test function
void testCodingInterview() {
    cout << "Cracking coding interview tasks:" << endl;
    int intN = 7;
    cout << "1. factorial(" << intN << ") = ";
    cout << factorial(intN) << endl;
}
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

void testInterviewcake()
{
    cout << "Interviewcake:" << endl;
    string strPermute {"sarar"};
    cout << "1. Can " << strPermute << " permute as a palindrome? ";
    cout << (hasPalindromePermutation(strPermute)?"... YES! this can permute as a palindrome":" ... cannot make a palindrome.") << endl;

}

#endif /* CODINGINTERVIEW_H */

