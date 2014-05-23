#include <iomanip>

#include "./Cash.h"

using std::endl;
using std::setw;

// Returns this cash's market value, which is equal to the amount of cash.
double Cash::GetMarketValue() const {
  return amount_;
}

// Since cash is a fixed asset, it never makes any profit.
double Cash::GetProfit() const {
  return 0.0;
}

// Returns this cash's cost, which is equal to the amount of cash.
double Cash::GetCost() const {
  return amount_;
}

// Sets the amount of cash invested to the given value.
void Cash::set_amount(double amount) {
  amount_ = amount;
}

// Gets the amount of cash that we have.
double Cash::get_amount() const {
  return amount_;
}

// Print the cash to the ostream; note this is a non-member function.
ostream &operator<<(ostream &out, const Cash &rhs) {
  out << "Cash:" << endl;
  out << "   value: $" << setw(7) << rhs.GetMarketValue() << endl;
  out << "    cost: $" << setw(7) << rhs.GetCost() << endl;
  out << "  profit: $" << setw(7) << rhs.GetProfit() << endl;
  return out;
}
