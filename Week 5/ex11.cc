/*
 * Copyright 2013 Chun-Wei Chen
 * 1267040
 * mijc0517@cs
 * 07/26/13
 */

#include <iostream>
#include <cstdlib>
#include <vector>
#include <algorithm>

using namespace std;

// Reads input from user and check if
// the input can be converted into type T.
template <class T> T ReadValue(istream& in);

// Prints out the values.
template <class T> void PrintValue(const T &v);

// Asks 10 doubles from user, and prints them out in ascending order.
int main(int argc, char **argv) {
  cout << "Input 10 doubles:" << endl;

  // read the inputs from user and store them into a vector
  double x;
  vector<double> vec;
  for (int i = 0; i < 10; i++) {
    x = ReadValue<double>(cin);
    vec.push_back(x);
  }

  // sort the doubles and print them out
  sort(vec.begin(), vec.end());
  cout << "Your sorted doubles are:" << endl;
  for_each(vec.begin(), vec.end(), &PrintValue<double>);

  return EXIT_SUCCESS;
}

template <class T> T ReadValue(istream& in) {
  T test;

  // store the input into test if it can be converted into type T;
  // otherwise, terminate the program
  if (in >> test) {
    in.clear();
    return test;
  } else {
    if (in.eof()) {
      cerr << "EOF is detected." << endl;
      exit(EXIT_FAILURE);
    } else {
      cerr << "Invalid input! The program takes 10 doubles as inputs." << endl;
      exit(EXIT_FAILURE);
    }
  }
}

template <class T> void PrintValue(const T &v) {
  cout << v << endl;
}
