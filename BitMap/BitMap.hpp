#ifndef __BIT_MAP_HPP_
#define __BIT_MAP_HPP_

#define __SHE_TEST_
#ifdef __SHE_TEST_
#include <iostream>
#endif//!__SHE_TEST_

#include <memory>


class BitMap
{
public:
  BitMap(int size=32){
    m_readSize = size%sizeof(int)+1;
    m_ptr = new unsigned int[m_readSize];
    m_size = size;
    turnAllOff();
  };

  ~BitMap(){
    delete[] m_ptr;
    m_ptr = nullptr;
  };

public:
  //将位图的第N位置1，返回1:操作成功，返回0:N越界
  int turnOn(const int &bitNumber){
    if(checkRange(bitNumber)){
      int index = bitNumber/32;
      m_ptr[index] |= (1<<(bitNumber%32));
      return 1;
    }
    else{
      return 0;
    }
  };

  //将位图的第N位置0，返回1:操作成功，返回0:N越界
  int turnOff(const int &bitNumber){
    if(checkRange(bitNumber)){
      int index = bitNumber/32;
      m_ptr[index] &= ~(1<<(bitNumber%32));
      return 1;
    }
    else{
      return 0;
    }
  };

  //查看第N位的状态，返回1:为1，返回0:为0，返回-1:N越界
  int find(const int &bitNumber){
    if(checkRange(bitNumber)){
      int index = bitNumber/32;
      return (m_ptr[index]>>(bitNumber%32) ) &0x00000001;
    }
    else{
      return -1;
    }
  };

  //将所有位置0
  void turnAllOff(){
    for(int i=0;i<m_readSize;i++){
      m_ptr[i] = 0x00000000;
    }
  };

  //将所有位置1
  void turnAllOn(){
    for(int i=0;i<m_readSize;i++){
      m_ptr[i] = 0xffffffff;
    }
  };

  //测试
  void debug(){
#ifdef __SHE_TEST_
    std::cout<<"test in 33bit\n";
    std::cout<<m_size<<","<<m_readSize<<"\n";
    turnOn(31);

    for(int i=0;i<m_readSize;i++){
      for(int j=0;j<32;j++){
        std::cout<<((m_ptr[i]>>j)&0x00000001)<<",";
      }
      std::cout<<"\n";
    }

    for(int i=0;i<m_size;i++){
      std::cout<<find(i)<<",";
    }
    std::cout<<"\n"<<find(33)<<"\n";
#endif//!__SHE_TEST_
  };

private:
  int checkRange(const int &range){
    if(range>=0 && range<m_size){
      return 1;
    }
    else{
      return 0;
    }
  };

  int m_size;//位图大小
  int m_readSize;//实际位图需要多少个int(需要多少个32位)
  unsigned int* m_ptr;//位图指针

};

#endif//!__BIT_MAP_HPP_