## Course 04 Modern C++: Move Semantics, Classes
This is a learning notebook for this Modern C++ course from Dr. Igor Bogoslavskyi. Many many thanks to his excellent [lectures](https://www.youtube.com/playlist?list=PLgnQpQtFTOGR50iIOtO36nK6aNPtVq98C)!:joy::joy:



### 1. Intuition Ivalues, rvalues
* lvalues can be written on the left of assignment operator; 
* rvalues are all the other expressions
* Explicit rvalue defined using &&

```
int a;                 // "a" lvalue
int& a_ref = a;        // "a_ref" is a reference to an lvalue

a = 2 + 2;             // "a" is an lvalue; "2+2" is an rvalue

int b = a + 2;         // "b" is an lvalue, "a+2" is an rvalue 

int &&c = std::move(a); // "c" is an rvalue
```

So it is not about what is actually on the left or right side of the assignment operator, but it is what potentially can be on the left or right side.

#### Hands on example
```
#include <iostream>
#include <string>

using namespace std;

void Print(const string& str) {
    cout << "lvalue: " << str << endl;
}

void Print(string&& str) {
    cout << "rvalue: " << str << endl;
}

int main() {
    string hello = "Hi";
    
    Print(hello);
    Print("world");
    Print(std::move(hello));
    // DO NOT access "hello" after move!

    return 0;
}
```

The idea is that what rvalues are useful is for being temporary. So anything that is a r-value is not bound to something that you want to keep your access to. Like above, if you created this _string hello_ over here but I don't need it in the function anymore. 
 
#### Further speaking example

```
#include <iostream>
#include <string>

class Printer {
public:
    void Print(const std::string& str) {
        std::cout << "lvalue: " << str << std::endl;
    }

    void Print(std::string&& str) {
        std::cout << "rvalue: " << str << std::endl;
    }

private:
    std::string some_str;
};

int main() {
    std::string hello = "Hi";
    Printer printer;
    
    printer.Print(hello);
    printer.Print("world");
    printer.Print(std::move(hello));
    // DO NOT access "hello" after move!

    return 0;
}
```

#### Move over instead of copy then delete

Now it's all boils down to how much work does the processor has to do to do what you asked it to do. And what you want on a high-level is you want your class Printer to store your string now at this point. That's what you want on a very high level, and you generally don't care how it's done but you want it to be done as efficient as possible. You don't need your string anymore after that point. 

So it would be nice to just not copy that string over and then delete this one, because it takes time, everytime you copy some memory it takes time. Why not just take this and move it over there? Whennever you use an r-value, you are telling the processor that you can move it, like you can take shi memory, and reassign it to the object, the other object gets invalidated. That's why it's important that it works for all the temporary object, because temporary objects will anyway we delete it and the compiler is smart enough to see that.


#### std::move can be dangerous
If you are using something after it's been moved, the C++ standard suggests everybody whoever implements their class to make sure that after moving something from their class it needs to be empty. It's just a suggestion but generally it's undefined. So you never know if there is anything left in your variable after move. You should never use something after you've moved it somewhere. In the best case, it's going to be empty; in the worse case, it's gonna to be arbitrary value or not defined at all.


### 2. How to think about std::move

* Think about ownership
* Moving a variable transfers ownership
* when designing your program think
"who should own this thing?"
* Runntime: better than copying, worse than passing by reference

For example, if you have a function, there is gonna be a variable in this function, so the local scope of that function owns that variable. When the scope reaches the end, the scope delete all the variables that were defined in that scope. That means that the scope owns the variables. Whenever you move a variable, you transfer ownership, you say, I don't own it anymore, you own it now.

So when you design something, you generally think like, don't think about code from the start, think about high-level representation. Your code should reflect some high-level representation. If you are modeling, like a car, and it should probably have four wheels. This car should own those wheels. Try to reduce your work by thinking of it abstractly.


### 3. Operators overloading

```
#include <vector>
#include <iostream>
#include <algorithm>

class Human {
public:
    Human(int kindness) 
        : kindness_(kindness) {

    }   

    bool operator<(const Human& other) const {
        return kindness_ < other.kindness_;
    } 

    int getKindness() const {
        return kindness_;
    }

private:
    int kindness_ = 100;
};

int main() {
    std::vector<Human> humans{Human(3), Human(0), Human(10)};
    std::sort(humans.begin(), humans.end());

    std::cout << humans.at(0).getKindness() << std::endl;
    std::cout << humans.at(1).getKindness() << std::endl;

    return 0;
}
```


### 4. Constructors && Operators

#### copy constructor
* Called automatically when the object is copied
* For a class Myclass has the signature:
  MyClass(const MyClass& other);


#### copy assignment operator
* Copy assignment operator is called automatically when the object is assigned a new value from an Lvalue

* For class MyClass has a signature:
  MyClass& operator=(const MyClass& other)

* Returns a reference to the changed object

* Use *this from within a function of a class to get a reference to the current object

_Example 1_
```
MyClass a;        // calling default constructor
MyClass b(a);     // calling copy constructor
MyClass c = a;    // calling copy constructor
a = b;            // calling copy assignment operator
```


#### move constructor

* Called automatically when the object is moved
* For a class MyClass has a signature:
  MyClass(MyClass&& other)

_Example 2_
```
MyClass a;                 // Default constructor
MyClass b (std::move(a));  // Move constructor
MyClass c = std::move(a);  // Move constructor
```  

#### move assignment operator

* Called automatically when the object is assigned a new value from an Rvalue

* For class MyClass has a signature:
  MyClass& operator=(MyClass && other)

* Returns a reference to the changed object

_Example 3_

```  
MyClass a;
MyClass b(std::move(a));
MyClass c = std::move(a);  
b = std::move(c);          // Move assignment operator
```  

_All in one place example:_


``` 
#include <iostream>

class Hmm {
public:
    Hmm() {std::cout << "default" << std::endl;}
    Hmm(const Hmm& other) {std::cout << "copy constructor" << std::endl;}
    Hmm(Hmm&& other) {std::cout << "move constructor" << std::endl;}
    
    Hmm& operator=(const Hmm& other) {
        std::cout << "copy assignment operator" << std::endl;
        return *this;
    }

    Hmm& operator=(Hmm&& other) {
        std::cout << "move assignment operator" << std::endl;
        return *this;
    }
};

int main()
{
    Hmm a;
    Hmm b = a;
    a = b;
    Hmm c = std::move(a);
    c = std::move(b);

    return 0;
}
``` 

### 5. Rule of all or nothing

* Try to define none of the special functions
* If you must define one of them, define all
* Use <font color='blue'>= default</font> to use default implementation


``` 
class MyClass {
public:
    MyClass() = default;
    MyClass(MyClass&& var) = default;
    MyClass(const MyClass& var) = default;
    MyClass& operator=(MyClass&& var) = default;
    MyClass& operator=(const MyClass& var) = default;    
};
``` 


### 6. Deleted functions

* Any function can be set as <font color='blue'>deleted</font>
  ``` 
  void SomeFunc(..) = delete;
  ``` 
* Calling such a function will result in compilation error
* Example: remove copy constructors when only one instance of the class must be guaranted
* Compiler marks some functions deleted automatically
* Example: if a class has a constant data member, the copy/move constructors and assignment operators are implicitly deleted

 
### 7. Inheritance

* Public inheritance stands for <font color='red'>"is a"</font> relationship, i.e. if class <font color='blue'>Derived</font> inherits publicly from class <font color='blue'>Base</font> we say, that Derived is a kind of Base


* Derived still gets its own special functions: constructors, destructor, assignment operators

It should make sense in high-level, if you think about things correctly, you will create less errors.


### 8. Function overriding
* A function is virtual in Base class it can be overridden in <font color='blue'>Derived</font> class:
Func(<PARAMS>) override;

* <font color='blue'>Base</font> can force all <font color='blue'>Derived</font> classes to override a function by making it <font color='red'>"pure virtual"</font> 

A very powerful tool that is kind of cornerstone of the whole design of systems that can behave dynamically depending on what is coming into them in C++ is based on using the pure virtual functions. So you can force everybody who inherits from you to implement a function. 


### 9. Overloading vs overriding

_Overloading_ means that a function can have the same name but different parameters or different constant specifiers. The compiler will find which function to use depending on the parameters on the signature of the function.

_Overriding_ is different, they have exactly the same signature they have the same parameters, they hae the same constant and so on. The only different is that they belong to the different class and this happens at runtime. The processor has to go through some table stored within your class and find I need this function overthere in this particular class.

* Do not confuse function overloading and overriding

* Overloading:
    * Pick from all functions with the <font color='red'>same name</font>, but  <font color='red'>different parameters</font> 
    * Pick a function <font color='red'>at compile time</font> 
    * Functions don't have to be in a class


* Overriding
    * Pick from functions with the <font color='red'>same arguments and names</font> in different classes of <font color='red'>one class hierarchy</font>
    * Pick <font color='red'>at runtime</font> 


### 10. Abstract classes and interfaces

* Abstract class: class that has at least one pure virtual function
* Interface: class that has only pure virtual functions and no data members 

### 11. How virtual works

Whenever you use virtual, you are acutally using runtime polymorphism. It means that if you have a reference to say your base class, it can be any of the references of your derived classes. 


* A class with virtual functions has a virtual table
* When calling a function the class checks which of the virtual functions that match the signature should be called
* Called <font color='red'>runtime polymorphism</font>
* Costs some time but is very convenient 