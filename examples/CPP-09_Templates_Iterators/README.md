## Course 09 Modern C++: Templates, Iterators, Exceptions, Program input parameters, OpenCV
This is a learning notebook for this Modern C++ course from Dr. Igor Bogoslavskyi. Many many thanks to his excellent [lectures](https://www.youtube.com/playlist?list=PLgnQpQtFTOGR50iIOtO36nK6aNPtVq98C)!:thumbsup::thumbsup:

### 1. Generic programming

Idea:   Separate algorithms from the data type.

#### Template functions

```
template <typename T, typename S>
T awesome_function(const T& var_t, const S& var_s) {
    // some dummy implementation
    T result = var_t;
    return result;
}
```

Explicit type: if the data type cannot be determined by the compiler, we must define it ourselves.

```
template <typename T>
T DummyFunction() {
  T result;
  return result;
}

int main() {
  DummyFunction<int>();
  DummyFunction<float>();
  return 0;
}
```

#### Template classes

```
template <class T>
class MyClass {
public:
  MyClass(const T& smth)
    : smth_(smth)
  {}

private:
  T smth_;  
};

int main() {
  MyClass<int> my_object(10);
  MyClass<double> my_double_object(10.0);

  return 0;
}
```

#### Template specialization

```
template <typename T>
T DummyFunction() {
  T result;
  return result;
}

template <>
int DummyFunction() {
  return 42;
}

int main() {
  DummyFunction<int>();
  DummyFunction<double>();
  return 0;
}
```

#### Template classes headers/source

* There are three options for template classes:
  * Declare and define in header files
  * Declare in NAME.h file, implement in NAME.hpp file, add #include <NAME.hpp> in the end of NAME.h
  * Declare in *.h file, implement in *.cpp file, in the end of the *.cpp add explicit instantiation for types you expect to use


### 2. Iterators
STL uses iterators to access data in containers.


### 3. Error handling with exceptions

If I am getting something that is not really working and I just want to tell somebody else that something is wrong here and I am not gonna work with this data. I just throw an exception over and somebody can actually catch that exception at some point. 

#### throw exceptions

There are a lot of different exceptions and if we are going to use any we are probably going to use these two.

* Runtime Error:
```
// if there is an error
if (badEvent) {
  string msg = "specific error string";
  // throw error
  throw runtime_error(msg);
}
```

* Logic Error: an error in logic of the user
```
throw logic_error(msg);
```


