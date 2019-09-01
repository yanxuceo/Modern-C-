#include <iostream>
#include <map>
#include <vector>


int main() {
  
  std::vector<double> x{4,5,6};
  for(auto it = x.begin(); it != x.end(); ++it) {
    std::cout << *it << std::endl;
  }

  std::map<int, std::string> m{{1, "hello"}, {2, "world"}};
  std::map<int, std::string>::iterator m_it = m.find(1);

  std::cout << m_it->first << ":" << m_it->second << std::endl;
  if(m.find(3) == m.end()) {
    std::cout << "Key 3 not found!\n";
  }
   
  return 0;
}