#include <algorithm>
#include <chrono>
#include <codecvt>
#include <iostream>
#include <locale>
#include <map>
#include <string>
#include <unordered_map>

using namespace std;

// Solution O(n^2)
string duplicate_encoder1(const wstring& word) {
  string ret = "";

  locale loc("");
  wstring lowerCaseWord = word;
  transform(lowerCaseWord.begin(), lowerCaseWord.end(), lowerCaseWord.begin(),
    [loc](wchar_t c) { return tolower(c, loc); });

  for (const auto& i : lowerCaseWord) {
    if (lowerCaseWord.find_last_of(i) != lowerCaseWord.find(i)) {
      ret += ')';
    } else {
      ret += '(';
    }
  }
  
  return ret;
}

// Solution O(2n) only for ASCII
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

// Solution O(n log n)
string duplicate_encoder3(const wstring& word) {
  string ret = "";
  
  locale loc("");
  map<wchar_t, unsigned> m;

  for (const auto& c : word) {
    ++m[tolower(c, loc)];
  }
  
  for (const auto& c : word) {
    int t = m[tolower(c, loc)];
    if (t == 1) {
      ret += '(';
    } else if (t > 1) {
      ret += ')';
    }
  }
  
  return ret;
}

// Solution O(2n)
string duplicate_encoder4(const wstring& word) {
  string ret = "";
  
  locale loc("");
  unordered_map<wchar_t, unsigned> m;
  
  for (const auto& c : word) {
    ++m[tolower(c, loc)];
  }
  
  for (const auto& c : word) {
    int t = m[tolower(c, loc)];
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
    map<wstring, string> m = {
        { L"din", "(((" },
        { L"recede", "()()()" },
        { L"Success", ")())())" },
        { L"(( @", "))((" },
        { L"CodeWarrior", "()(((())())" },
        { L"Supralapsarian", ")()))()))))()(" },
        { L" ( ( )", ")))))(" },
        { L"Тест", ")(()"}
    };
    
    for (const auto& [i, j] : m) {
        string res;
        chrono::steady_clock::time_point begin;
        chrono::steady_clock::time_point end;
        
        begin = chrono::steady_clock::now();
        res = duplicate_encoder1(i) == j ? "passed" : "failed";
        end = chrono::steady_clock::now();
        cout << "Solution 1 " << res << " in " << (end - begin).count() << " ns" << endl;
        
        begin = chrono::steady_clock::now();
        wstring_convert<codecvt_utf8_utf16<wchar_t>> converter;
        res = duplicate_encoder2(converter.to_bytes(i)) == j ? "passed" : "failed";
        end = chrono::steady_clock::now();
        cout << "Solution 2 " << res << " in " << (end - begin).count() << " ns" << endl;
        
        begin = chrono::steady_clock::now();
        res = duplicate_encoder3(i) == j ? "passed" : "failed";
        end = chrono::steady_clock::now();
        cout << "Solution 3 " << res << " in " << (end - begin).count() << " ns" << endl;
        
        begin = chrono::steady_clock::now();
        res = duplicate_encoder4(i) == j ? "passed" : "failed";
        end = chrono::steady_clock::now();
        cout << "Solution 4 " << res << " in " << (end - begin).count() << " ns" << endl;
    }

    return 0;
}
