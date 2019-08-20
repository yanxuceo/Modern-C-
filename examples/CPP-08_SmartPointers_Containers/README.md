## Course 08 Modern C++: Smart/Unique/Shared pointers, Associative containers, Type casting, Enumeration, Binary files
This is a learning notebook for this Modern C++ course from Dr. Igor Bogoslavskyi. Many many thanks to his excellent [lectures](https://www.youtube.com/playlist?list=PLgnQpQtFTOGR50iIOtO36nK6aNPtVq98C)!:thumbsup::thumbsup:

### 1. Smart pointers

#### Smart pointers manage memory
Every resource that you allocated, which is either memory, or files, or anything else, should be allocated when you created object and should be deallocated when you destroy this object.


#### Unique pointer (std::unique_ptr)

* Constructor of a unique pointer takes ownership of a provided raw pointer

* No runtime overhead over a raw pointer

* Syntax for a unique pointer to type Type:

```
#include <memory>

// Using default constructor Type()
auto p = std::unique_ptr<Type>(new Type);

// Using constructor Type(<params>)
auto p = std::unique_ptr<Type>(new Type(<params>));
```

* From C++ 14 on:
```
// Forwards <params> to constructor of unique_ptr
auto p = std::make_unique<Type>(<params>);
```

**_What makes it "unique"_**

* Unique pointer has no copy constructor
* Cannot be copied, can be moved
* Guarantees that memory is always owned by a single unique pointer

The copy constructor is explicitly deleted, if you try to use the copy constructor on the unique pointer, your program will fail. Why is it this case? The case for it is that we don't know how to implement copy. Because we don't know what the user wants. Like mentioned in shallow copy and deep copy, the problem with that is the compiler has no idea which copy do we want at this point of time, if you actually copy the data or do we just want to shallow copy, because we just shallow copy into some function, we don't want the overhead of copy the whole bunch of resources hold by the class.

```
#include <iostream>
#include <memory>

struct A {
  int a = 10;
};

int main() {
  auto a_ptr = std::unique_ptr<A>(new A);
  std::cout << a_ptr->a << std::endl;
  auto b_ptr = std::move(a_ptr);
  std::cout << b_ptr->a << std::endl;

  return 0;
}
```

#### Shared pointer (std::shared_ptr)

We don't always want something to be unique, we sometimes want multiple things to point to the same entity of memory (allocate thing once.) The difference of the shared pointer is that along with this raw pointer in this class, there is a counter of in how many places this particular pointer is used. So you create a shared pointer, the count is one; you use this raw pointer in exactly one place; then you copy this pointer to somebody else, the shared pointer keeps track of how many object use it. So if now there is another object is using it, and the first object goes out of scope and gets removed, the other one will still own that memory, and the memory will still not be freed. It will only be freed when nobody uses it.(when the count down to 0)


* Constructed just like a unique_ptr
* Can be copied
* Stores a usage counter and a raw pointer 
  * Increases usage counter when copied
  * Decreases usage counter when destructed

* Frees memory when counter reaches 0
* Can be initialized from a unique_ptr

```
#include <memory>

// Using default constructor Type()
auto p = std::shared_ptr<Type>(new Type);
auto p = std::make_shared<Type>();

// Using constructor Type(<params>)
auto p = std::shared_ptr<Type>(new Type(<params>));
autp p = std::make_shared<Type>(<params>);
```

#### When to use what?

* Use smart pointers when the pointer must manage memory

* By default use unique_ptr

* If multiple objects must share ownership over something, use a shared_ptr to it

* Using smart pointers allows to avoid having destructors in you own classes

* Think of any free standing new or delete as of a memory leak or a dangling pointer:
  * Don't use delete
  * Allocate memory with make_unique, make_shared
  * Only use new in smart pointer constructor if cannot use the functions above


#### Typical beginner error

* Create a smart pointer from a pointer to a stack-managed variable
* The variable ends up being owned both by the smart pointer and the stack and gets deleted twice -> Error!

```
int main() {
  int a = 0;
  auto a_ptr = std::unique_ptr<int>(&a);
  
  return 0;
}
```


#### Polymorphism with Smart pointer

```
#include <iostream>
#include <memory>
#include <vector>

class AbstractShape {
public:
  virtual void Print() const = 0;	
};

class Square : public AbstractShape {
public:
  void Print() const override {std::cout << "Square\n";}
};

class Triangle : public AbstractShape {
public:
  void Print() const override {std::cout << "Triangle\n";}	
};

int main()
{  
  std::vector<std::unique_ptr<AbstractShape>> shapes; 
  shapes.emplace_back(new Square);
  
  auto triangle = std::unique_ptr<Triangle>(new Triangle);
  shapes.emplace_back(std::move(triangle));

  shapes.emplace_back(std::make_unique<Triangle>());

  for(const auto& shape : shapes) {
		shape->Print();
  }

  return 0;
}
```

**Note:**
```
auto triangle = std::unique_ptr<Triangle>(new Triangle);
shapes.emplace_back(std::move(triangle));
```
Here, we have a triangle, which is a unique pointer to a Triangle. We want to put it into the vector, but we cannot copy it. Whenever you want to put something into the vector, by default, it's copied. But we cannot, so we have to move it there.


### 2. Associative containers

#### std::map
* Stores items under unique keys
* Impelmented usually as a Red-Black tree
* Key can be any type with operator < defined
* Create from data:

```
std::map<KeyT, ValueT> m = {
  {key,value}, {key,value}, {key,value}
};
```
* Add item to map: m.emplace(key, value);
* Modify or add item: m[key] = value;
* Get ref to an item: m dot at(key);
* Check if key present: m.count(key) > 0;
* Check size: m.size();


#### std::unordered_map

* Serves same purpose as std::map
* Implemented as a hash table
* Key type has to be _hashable_
* Typically used with int, string as a key
* Exactly same interface as std::map


#### Iterating over maps

```
for (const auto& kv : m) {
  const auto& key = kv.first;
  const auto& value = kv.second;
  // do work here
}
```

* Every stored element is a pair
* map has keys sorted
* unordered_map has keys in random order


### 3. Type casting

#### Casting type of variables
* Every variable has a type
* Types can be converted from one to another
* Type conversion is called type casting
* There are 3 ways of type casting:
  * static_cast
  * reinterpret_cast
  * dynamic_cast


#### static_cast

* Convert type of a variable at compile time
* Rarely needed to be used explicitly
* Can happen implicitly for some types, e.g. float can be cast to int
* Pointer to an object of a Derived class can be upcast to a pointer of a Base class
* Enum value can be caster to int or float


#### reinterpret_cast

* Reinterpret the bytes of a variable as another type
* We must know what we are doing!
* Mostly used when writing binary data


#### dynamic_cast

* Used to convert a pointer to a variable of Derived type to a pointer of a Base type

* Conversion happens at runtime

* If derived_ptr cannot be converted to Base*, returns a nullptr

* GOOGLE_STYLE Avoid using dynamic casting


### 4. Enumeration classes

* Store an enumeration of options
* Usually derived from int type
* Options are assigned consequent numbers
* Mostly used to pick path in switch

```
enum class EnumType {OPTION_1, OPTION_2, OPTION_3};
```


### 5. Read/write binary files

The idea is that you don't write anything meaningful, you just write a sequence of bytes into the binary file, so it's not readable for humans. If you open it, you can see just bytes there and you have no idea what is stored there. Therefore, you must document the structure of the files, you need to make sure that everybody who uses your files knows that it's going to be two doubles followed by 15 integers by two strings, and so on. Because if they don't know it they will not be able to read it, they will just see a sequence of bytes. They can interpret those bytes the way they want to but if they don't know how to interpret.. 

* We wrtie a sequence of bytes
* We must document the structure well, otherwise no one can read the file
* Writing/reading is fast
* No precision loss for floating point types
* Substantially smaller than ascii-files 
* Syntax

```
file.write(reinterpret_cast<char*>*(&a), sizeof(a));
```

