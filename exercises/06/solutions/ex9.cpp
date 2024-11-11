#include <iostream>
#include <memory>

class Base {
public:
  virtual void display() const {
    std::cout << "Displaying from Base class." << std::endl;
  }
  virtual ~Base() { std::cout << "Base destroyed." << std::endl; }
};

class Derived1 : public Base {
public:
  void display() const override {
    std::cout << "Displaying from Derived1 class." << std::endl;
  }

  ~Derived1() { std::cout << "Derived1 destroyed." << std::endl; }
};

class Derived2 : public Base {
public:
  void display() const override {
    std::cout << "Displaying from Derived2 class." << std::endl;
  }

  ~Derived2() { std::cout << "Derived2 destroyed." << std::endl; }
};

int main() {
  // Using unique_ptr with Derived1
  std::unique_ptr<Base> uniquePtr1 = std::make_unique<Derived1>();
  uniquePtr1->display(); // Should call Derived1's display().

  // Using unique_ptr with Derived2
  std::unique_ptr<Base> uniquePtr2 = std::make_unique<Derived2>();
  uniquePtr2->display(); // Should call Derived2's display().

  // Using shared_ptr with polymorphism for Derived1.
  std::shared_ptr<Base> shared_pointer1 = std::make_shared<Derived1>();
  std::shared_ptr<Base> shared_pointer2 = shared_pointer1; // Reference count increases.
  shared_pointer1->display(); // Should call Derived1's display().

  std::cout << "Reference count for shared_pointer1: " << shared_pointer1.use_count()
            << std::endl;

  shared_pointer2.reset(); // Decrease reference count.
  std::cout << "Reference count after reset for shared_pointer1: "
            << shared_pointer1.use_count() << std::endl;

  // Using shared_ptr with polymorphism for Derived2.
  std::shared_ptr<Base> shared_pointer3 = std::make_shared<Derived2>();
  shared_pointer3->display(); // Should call Derived2's display().

  return 0;
}
