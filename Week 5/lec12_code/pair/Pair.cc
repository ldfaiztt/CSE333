template <class Thing> Thing &Pair<Thing>::get_first() {
  return first_;
}

template <class Thing> Thing &Pair<Thing>::get_second() {
  return second_;
}

template <class Thing> void Pair<Thing>::set_first(Thing &copyme) {
  first_ = copyme;
}

template <class Thing> void Pair<Thing>::set_second(Thing &copyme) {
  second_ = copyme;
}

template <class Thing> void Pair<Thing>::Reverse() {
  // makes *3* copies
  Thing tmp = first_;
  first_ = second_;
  second_ = tmp;
}
