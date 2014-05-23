#include <iostream>
#include <iomanip>
#include <memory>

#include "./Cash.h"
#include "./DividendStock.h"
#include "./Stock.h"

using std::cout;
using std::endl;
using std::fixed;
using std::setprecision;

int main() {
  // create several investments
  std::unique_ptr<Cash> cash(new Cash(1234.56));

  std::unique_ptr<Stock> stock(new Stock("MSFT"));
  stock->Purchase(50, 10.00);
  stock->set_share_price(9.50);

  std::unique_ptr<DividendStock> dividend(new DividendStock("INTC"));
  dividend->Purchase(100, 20.00);
  dividend->PayDividend(5.00);
  dividend->set_share_price(30);
    
  // display info about each investment
  cout << setprecision(2);
  cout << fixed;

  cout << *cash;
  cout << endl;

  cout << *stock;
  cout << endl;

  cout << *dividend;
    
  return 0;
}
