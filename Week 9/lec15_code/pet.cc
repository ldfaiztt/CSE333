/* CSE 333 lecture 15: pet.cc: vtable/inheritance example.  HP 5/13 */

// Both specification and implementation included in this file
// to keep the example compact and focus on dispatch issues.

#include <string>
#include <iostream>
using namespace std;

// model a generic household pet
class Pet {
public:
  // initialize new Pet with given name
  Pet(string name) { name_ = name; }

  // return name of this Pet
  virtual string get_name() { return name_; }

  // return a noise made by this Pet
  // (what happens if you omit virtual?)
  // (what if you want an abstract method here? [no implementation])
  virtual string get_noise() { return "wassup?"; }

private:
  string name_;   // name of this pet
};

// a cat is a pet that has a different noise and can scratch
class Cat: public Pet {
public:
  // initialize new Cat with given name
  Cat(string name): Pet(name) { }

  // cat noise - override
  string get_noise() { return "meow"; }

  // cat behavior - scratch
  void scratch() { cout << "scratch " << ++scratch_count << endl; }

private:
  int scratch_count;  // number of cat scratches
};

// a kitten is a cat that bounces off walls
class Kitten: public Cat {
public:
  // initialize new Kitten
  Kitten(string name): Cat(name) { }

  // kitten noise - override
  string get_noise() { return "purrrr"; }

  // additional kitten behavior - hyperactivity
  void bounce() { cout << "boing boing boing" << endl; }
};

// Print name and noise made by Pet p
void prPet(Pet *p) {
  cout << "Pet named " << p->get_name() << " says " << p->get_noise() << endl;
}

// Create a menagerie and run some methods
int main() {
  cout << "pet and cat:" << endl;
  Pet * fred = new Pet("Fred");
  prPet(fred);
  Cat * spot = new Cat("Spot");
  prPet(spot);
  spot->scratch();
  spot->scratch();
  Pet * catp  = spot;
  prPet(catp);
  cout << "kitten:" << endl;
  //catp->scratch();    // won't compile - no scratch() in Pet
  Kitten * kat = new Kitten("Puff");
  prPet(kat);
  kat->scratch();
  kat->scratch();
  kat->bounce();
  // a kitty of many voices or just one?
  Cat * ckat = kat;
  Pet * pkat = kat;
  cout << "kitten noises:" << endl;
  cout << pkat->get_noise() << endl;
  cout << ckat->get_noise() << endl;
  cout << kat->get_noise() << endl;
  return 0;
}

