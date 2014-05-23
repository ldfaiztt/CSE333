#ifndef LEC14_CODE_TOYPTR_H_
#define LEC14_CODE_TOYPTR_H_

template <class T> class ToyPtr {
 public:
  // Constructor that accepts the ptr.
  ToyPtr(T *ptr) : ptr_(ptr) { }

  // Destructor that deletes the ptr.
  ~ToyPtr() {
    if (ptr_ != NULL) {
      delete ptr_;
      ptr_ = NULL;
    }
  }

  // Implement the "*" operator
  T &operator*() {
    return *ptr_;
  }

  // Implement the "->" operator
  T *operator->() {
    return ptr_;
  }

 private:
  // The pointer itself.
  T *ptr_;
};

#endif  // LEC14_CODE_TOYPTR_H_
