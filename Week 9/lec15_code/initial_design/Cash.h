#ifndef _LEC15_CASH_H_
#define _LEC15_CASH_H_

#include <iostream>

using std::ostream;

// The Cash class represents money owned by the investor.
class Cash {
 public:
  // Construct a cash investment of a given amount.
 Cash(double amount) : amount_(amount) { }

  // Cash's accessor methods.
  void   set_amount(double amount);
  double get_amount() const;

  // Cash's "investment" interface.
  double GetMarketValue() const;
  double GetProfit() const;
  double GetCost() const;

  // Overload (ostream& <<) so we can print Cash.
  friend ostream &operator<<(ostream &out, const Cash &rhs);

 private:
  double amount_;   // amount of money owned
};

#endif  // _LEC15_CASH_H_

