## Course 05 Modern C++: Polymorphism, I/O, Stringstreams, CMake find
This is a learning notebook for this Modern C++ course from Dr. Igor Bogoslavskyi. Many many thanks to his excellent [lectures](https://www.youtube.com/playlist?list=PLgnQpQtFTOGR50iIOtO36nK6aNPtVq98C)!:thumbsup::thumbsup:

### 1. Polymorphism
> From Greek polys, "many, much" and morphe, "form, shape".   -wiki

* Allows morphing derived classes into their base class type:
```
const Base& base = Derived(xxx)
```

#### When to use?
* Allows encapsulating the implementation inside a class only asking it to conform to a common interface

* Often used for:
    * Working with all children of some Base class in unified manner
    * Enforcing an interface in multiple classes to force them to implement some functionality
    * In strategy pattern, where some complex functionality is outsourced into separate classes and is passed to the object in a modular fashion. Check my [github](https://github.com/yanxuceo/Design-Pattern/tree/master/strategy%20pattern) for Strategy Pattern.


Let's say, we have a Base class and a derived class, and they are in a relationship "is-a". Then we just want to work with them in a unified manner we want to have them the same interface(public functions). So they have the public functions and we don't really care about which exact class we are working with now; we just want to care that they conform to the same functions. So we hide the implementation from ourselves and from the users of library and we only expose some interface that people should use. 

Sometimes, it can be used to enforce the same interface in otherwise unrelated classes. Say we want all the class to have a print function, all the classes in our library we want to force them to have a print function. We can do that by deriving them from a class that has a public print function. 


Strategy pattern: Basically say that there is a different strategy of writing and reading from disk and I want to be able to replace this strategy on the go without changing any line of code in my Image Class.


#### Creating a class hierarchy

* Sometimes classes must form a hierarchy

* Distinguish between _is a_ and _has a_ to test if the classes should be in one hierarchy:
    * Square is a shape
    * Student is a Human
    * Car has a Wheel: should not inherit each other

* Prefer shallow hierarchies
* GOOGLE-STYLE: Prefer composition
    i.e. including an object of another class as a member of your class


Deep hierarchy, even though it makes sense logically, from the coding perspective, it hides the implementation details that you care about very deep into hierarchies. So when I am looking at the class that implements like the Student of this particular class, and you inherit from just a general student. In order to find something that is hiddent in that class I need to navigate to another file then suddenly I find that it's not even there, it's actually in the human class. So trying not to do it, usually prefer Composition.

#### virtual function
```
class Rect {
public:
    Rect(int w, int h)
         : width_(w), height_(h) {

    }

    virtual void Print() const {
        std::cout << "rect: " << width_ << " " << height_ << std::endl;
    }
    
    int width() const { return width_; }
    int height() const { return height_; }

protected:
    int width_ = 0;
    int height_ = 0;
};

class Square : public Rect {
public:
    explicit Square(int size) 
        : Rect(size, size)
    {}

    virtual void Print() const override{
        std::cout << "square: " << width_ << " " << height_ << std::endl;
    }
};
```

wheneve we see virtual, we say that we expect this class to be part of a class hierarchy. So there are other classes that depend on this class. Whenever you see virtual, your class allocates a table and this table basically just maps from the name of your class to a function. 

#### using interface
* Use interfaces when you must enforce other classes to implement some functionality

* Allow thinking about classes in terms of abstract functionality

* Hide implementation from the caller

* Allow to easily extend functionality by simply adding a new class

```
class Printable {
public:
    virtual void Print() const = 0; 
};

class Rect : public Printable {
public:
    Rect(int w, int h)
         : width_(w), height_(h) {
    }
    virtual void Print() const {
        std::cout << "rect: " << width_ << " " << height_ << std::endl;
    }
    
    int width() const { return width_; }
    int height() const { return height_; }

protected:
    int width_ = 0;
    int height_ = 0;
};
```

#### using strategy pattern

* If a class relies on complex external functionality use strategy pattern

* Allow to add/switch functionality of the class without changing its implementation

* All strategies must conform to one strategy interface

You basically define a bunch of classes that conform to some strategy interface which is just an interface of whatever you want to do and you hold a constant reference to this interface in your class in the one you are actually implementing. 


* Only use these patterns when you need to
* If your class should have a single method for some functionality and will never need another implementation don't make it virtual
* Used mostly to avoid copying code and to make classes smaller by moving some functionality out


### 2. Reading and writing to files

* Use streams from STL
* Syntax similar to cerr, cout

```
#include <fstream>
using std::string;
using Mode = std::ios_base::openmode;

std::ifstream f_in(string& file_name, Mode mode);
std::ofstream f_out(string& file_name, Mode mode);
std::fstream f_in_out(string& file_name, Mode mode);
```
  
|        Mode           |      Meaning               |      
|        ---            |       ---                  | 
|    ios_base::app      |  append output             |
|    ios_base::ate      |  seek to EOF when opened   | 
|    ios_base::binary   |  open the file in binary mode      |
|    ios_base::in       |  open the file for reading         |
|    ios_base::out      |  open the file for writing         |
|    ios_base::trunc    |  overwrite the existing file       |


#### Regular columns
Use it when:
* The file constains organized data
* Every file has to have all columns

#### Writing into text files
With the same syntax as cerr and cout streams, with ofstream we can write directly into files.

```
#include <iomanip>
#include <fstream>
using namespace std;

int main() {
    string filename = "out.txt";
    ofstream outfile(filename);

    if(!outfile.is_open()) {
        return EXIT_FAILURE;
    }
    double a = 1.1314;
    outfile << "Just string" << endl;
    outfile << setprecision(5) << a << endl;

    return 0;
}

```

#### String streams

Already known streams:
* Standard output: cerr, cout
* Standard input: cin
* Filestreams: fstream, ifstream, ofstream

New type of stream: stringstream
* Combine int, double, string, etc. into a sing string
* Break up strings into int, double, string ect.


```
#include <iostream>
#include <iomanip>
#include <sstream>
using namespace std;

int main() {
    stringstream s_out;
    string ext = ".txt";
    string file_name = "";

    for (int i = 0; i < 500; i++) {
        s_out << setw(5) << setfill('0') << i << ext;
        file_name = s_out.str();
        s_out.str("");
        cerr << file_name << endl;
    }

    stringstream s_in(file_name);
    int i;
    string rest;
    s_in >> i >> rest;
    cerr << "Number: " << i << " rest is: " << rest;

    return 0;
}

```


### 3. CMake find
find_path and find_library

* We can use an external library
* Need headers and binary library files
* There is an easy way to find them
* Headers:
  
```
find_path(SOME_PKG_INCLUDE_DIR include/some_file.h
          <path1> <path2> ...)

include_directories(${SOME_PKG_INCLUDE_DIR})
```  

* Libraries:

```  
find_library(SOME_LIB
            NAMES <some_lib>
            PATHS <path1> <path2> ...)

target_link_libraries(target ${SOME_LIB})
```  

find_package
* find_package calls multiple find_path and find_libary functions
* To use find_package() CMake must have a file Find<>.cmake in CMAKE_MODULE_PATH folders
* FindM<>.cmake defines which libraries and headers belong to package xxx
* Pre-defined for most popupar libraries, e.g. OpenCV, libpng, etc.


CMakeLists.txt
```
cmake_minimum_required(VERSION 2.8)
project(first_project)

# CMake will search here for Find<pkg>.cmake files
SET(CMAKE_MODULE_PATH
    ${PROJECT_SOURCE_DIR}/cmake_modules)

# Search for Findsome_pkg.cmake file and load it
find_package(some_pkg)

# Add the include folders from some_pkg
include_directories(${some_pkg_INCLUDE_DIRS})

# Add the executable "main"
add_executable(main small_main.cpp)

# Tell the linker to bind these binary objects
target_link_libraries(main ${some_pkg_LIBRARIES})
```

cmake_modules/Findsome_pkg.cmake
