#include <algorithm>
#include <chrono>
#include <iostream>
#include <map>
#include <string>

using namespace std;

// Solution O(n^2)
string duplicate_encoder1(const string& word) {
  string ret = "";

  string lowerCaseWord = word;
  transform(lowerCaseWord.begin(), lowerCaseWord.end(), lowerCaseWord.begin(), ::tolower);

  for (int i = 0; i < lowerCaseWord.length(); i++) {
    if (lowerCaseWord.find_last_of(lowerCaseWord[i]) != lowerCaseWord.find(lowerCaseWord[i])) {
      ret += ')';
    } else {
      ret += '(';
    }
  }
  
  return ret;
}

// Solution O(n log n)
string duplicate_encoder2(const string& word) {
  string ret = "";
  
  unsigned ascii[128] = {0};
  unsigned n = word.length();
  
  for (int i = 0; i < n; i++) {
    ascii[unsigned(tolower(word[i]))]++;
  }
  
  for (int i = 0; i < n; i++) {
    int t = ascii[unsigned(tolower(word[i]))];
    if (t == 1) {
      ret += '(';
    } else if (t > 1) {
      ret += ')';
    }
  }
  
  return ret;
}

int main()
{
    // Test Cases
    map<string, string> m = {
        { "din", "(((" },
        { "recede", "()()()" },
        { "Success", ")())())" },
        { "(( @", "))((" },
        { "CodeWarrior", "()(((())())" },
        { "Supralapsarian", ")()))()))))()(" },
        { " ( ( )", ")))))(" }
    };
    
    for (const auto& [i, j] : m) {
        string res;
        chrono::steady_clock::time_point begin;
        chrono::steady_clock::time_point end;
        
        begin = std::chrono::steady_clock::now();
        res = duplicate_encoder1(i) == j ? "passed" : "failed";
        end = std::chrono::steady_clock::now();
        cout << "Solution 1 " << res << " in " << (end - begin).count() << " ns" << endl;
        
        begin = std::chrono::steady_clock::now();
        res = duplicate_encoder2(i) == j ? "passed" : "failed";
        end = std::chrono::steady_clock::now();
        cout << "Solution 2 " << res << " in " << (end - begin).count() << " ns" << endl;
    }

    return 0;
}
