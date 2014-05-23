#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <memory>
#include <vector>

#include "./DividendStock.h"
#include "./Stock.h"

using namespace std;

int main() {
  // create several investments
  std::unique_ptr<Stock> stock(new Stock("MSFT"));
  stock->Purchase(50, 10.00);
  stock->set_share_price(9.50);

  std::unique_ptr<DividendStock> dividend(new DividendStock("INTC"));
  dividend->Purchase(100, 20.00);
  dividend->PayDividend(5.00);
  dividend->set_share_price(30);

  // display info about each investment
  stock->Print();
  cout << endl;
  dividend->Print();

  return EXIT_SUCCESS;
}
