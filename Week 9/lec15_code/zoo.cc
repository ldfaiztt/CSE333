/* CSE 333 lecture demo: zoo.cc. HP */

#include <iostream>
#include <string>

using namespace std;

// Very brief example of use of virtual functions

// Base class for animals - all animals have a name and can make a noise
class Animal {
 public:
  // construct animal with given name
  Animal(string name) : name_(name) { }

  // return sound made by this animal (abstract)
  virtual string noise() = 0;

  // print animal description
  virtual void describe() { cout << name_ << " says " << noise() << endl; }

 private:
  string name_;   // animal's name
};

// Subclass describing a cat
class Cat: public Animal {
public:
  Cat(string name) : Animal(name) { }
  string noise() { return "purrrrr"; }
};

// test program
int main() {
  Cat fluffy("spot");
  fluffy.describe();
}



