#ifndef _LEC14_CODE_PAIR_H_
#define _LEC14_CODE_PAIR_H_

template <class Thing> class Pair {
 public:
   Pair() { };

   Thing &get_first();
   Thing &get_second();
   void set_first(Thing &copyme);
   void set_second(Thing &copyme);

   void Reverse();
 private:
   Thing first_, second_;
};

// The compiler must see the definition for any template that is
// used.  That means customers of Pair.h need to be
// shown the definition of class Pair; one way to do this is to
// include the .cc file associated with the .h file right in 
// the header, as follows.  This is the "inclusion compilation
// model."

#include "Pair.cc"

#endif  // _LEC14_CODE_PAIR_H_
