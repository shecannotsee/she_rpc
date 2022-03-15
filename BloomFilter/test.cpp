#include "BloomFilter.hpp"

int main()
{
  BloomFilter bf;

  bf.add("function_use1");
  bf.add("function_use2");
  bf.add("function_use3");

  std::cout<<bf.find("function_use1")<<"\n";
  std::cout<<bf.find("function_use2")<<"\n";
  std::cout<<bf.find("function_use3")<<"\n";

  std::cout<<bf.find("functionuse1")<<"\n";

  bf.debug();

  return 0;
}