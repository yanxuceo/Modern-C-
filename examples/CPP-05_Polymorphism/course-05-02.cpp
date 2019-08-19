// Learncpp.com example to demonstrate explicit keyword to suppress implicit 
// conversion caused by initializztion list

#include <string>
#include <iostream>
 
class MyString {
public:
    // explicit keyword makes this constructor ineligible for implicit conversions
	explicit MyString(int x)     // allocate string of size x
	{
		m_string.resize(x);
	}
 
	MyString(const char *string) // allocate string to hold string value
	{
		m_string = string;
	}
 
	friend std::ostream& operator<<(std::ostream& out, const MyString &s);

private:
	std::string m_string;
};
 
std::ostream& operator<<(std::ostream& out, const MyString &s)
{
	out << s.m_string;
	return out;
}
 
int main()
{
	MyString mine = "abc"; // compile error, since MyString(int) is now explicit and nothing will match this
	std::cout << mine << std::endl;
	return 0;
}