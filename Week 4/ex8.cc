/*
 * Copyright 2013 Chun-Wei Chen
 * 1267040
 * mijc0517@cs
 * 07/15/13
 */

#include <cinttypes>
#include <iostream>
#include <cstdlib>

/*
 * Prints out all the positive integer factors of num.
 */
void PrintFactorsOf(uint64_t num);

/*
 * Returns true if fac is a positive integer factor of num; false otherwise.
 */
bool IsFactorOf(uint64_t fac, uint64_t num);

/*
 * Asks a positive integer and prints out 
 * all the positive integer factors of that positive integer.
 */
int main(int argc, char **argv) {
  int64_t num;

  std::cout << "Which positive integer would you like me to factorize? ";
  std::cin >> num;

  // terminate the program if the user passed in a non-positive integer
  if (num <= 0) {
    std::cout << "Passed in a non-positive integer." << std::endl;
    return EXIT_FAILURE;
  }

  uint64_t unum = num;
  PrintFactorsOf(unum);

  return EXIT_SUCCESS;
}

void PrintFactorsOf(uint64_t num) {
  // check if the input is valid
  if (num == 0) {
    std::cout << "Argument num must be > 0." << std::endl;
    exit(EXIT_FAILURE);
  }

  // 1 is factor of any number
  std::cout << 1;

  if (num % 2 == 0) {
    // if num is an even number, check up to num/2
    // since the smallest prime factor for even
    // number is 2.
    for (uint64_t i = 2; i <= num / 2; i++) {
      if (IsFactorOf(i, num))
        std::cout << " " << i;
    }
  } else {
    // if num is an odd number, check up to num/3
    // since the smallest possible prime factor for
    // odd number is 3.
    for (uint64_t i = 3; i <= num / 3; i += 2) {
      if (IsFactorOf(i, num))
        std::cout << " " << i;
    }
  }

  // add the number itself at the end since the number is always
  // a factor of itself and then print out all the factors found
  if (num == 1)
    std::cout << std::endl;
  else
    std::cout << " " << num << std::endl;
}

bool IsFactorOf(uint64_t fac, uint64_t num) {
  // check if the inputs are valid
  if (fac == 0) {
    std::cout << "Argument fac must be > 0." << std::endl;
    exit(EXIT_FAILURE);
  }

  if (num == 0) {
    std::cout << "Argument num must be > 0." << std::endl;
    exit(EXIT_FAILURE);
  }

  return (num % fac == 0);
}
