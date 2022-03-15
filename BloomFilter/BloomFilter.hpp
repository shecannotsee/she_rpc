#ifndef __BLOOM_FILTER_HPP_
#define __BLOOM_FILTER_HPP_

#define __SHE_TEST_
#ifdef  __SHE_TEST_
#include <iostream>
#endif//!__SHE_TEST_

#include "../BitMap/BitMap.hpp"
#include "../Hash/Hash.cpp"

class BloomFilter
{
public:
  BloomFilter(){
    m_bitmap = new BitMap(1024);
  };

  ~BloomFilter(){
    delete m_bitmap;
    m_bitmap = nullptr;
  };

  void add(const char *str){
    m_bitmap->turnOn(HashBKDR<char>(str)%1024);
    m_bitmap->turnOn(HashAP<char>(str));
    m_bitmap->turnOn(HashDEK<char>(str)%1024);
  };

  int find(const char *str){
    if(m_bitmap->find(HashBKDR<char>(str)%1024)&&
       m_bitmap->find(HashAP<char>(str)%1024)&&
       m_bitmap->find(HashDEK<char>(str)%1024)
    ){
      return 1;
    }
    else{
      return 0;
    }
  };

  void debug(){
#ifdef __SHE_TEST_
    std::cout<<"Bloom Fliter Debug.\n";
#endif//!__SHE_TEST_
  };

private:
  BitMap *m_bitmap;

};


#endif//!__BLOOM_FILTER_HPP_