#ifndef __RPC_REGISTER_HPP_
#define __RPC_REGISTER_HPP_
#include <vector>
#include <string>
#include "rpc_function.hpp"

class rpc_register
{
public:
	rpc_register();
	~rpc_register();

	void regis();

	//对传入参数进行检查,rpc_function.j_add
	int link_to_function(std::string class_function_name);

	//调用过程
	std::string call_action(std::string function_parameter);

private:
	std::string m_class_name;//上一次调用的类名,在每次调用之后进行重置
	std::string m_function_name;//上一次调用的函数名,在每次调用之后进行重置
	std::string m_function_parameter;//上一次调用的函数参数,在每次调用之后进行重置

	std::vector<std::string> m_regis_class;//已注册类
	std::vector<std::string> m_regis_function;//已注册函数

	std::string m_rpc_result;//调用结果

	void fool(std::string function_parameter);
	

};

rpc_register::rpc_register()
{
	m_class_name = "";
	m_function_name = "";
	m_function_parameter = "";

	m_rpc_result = "";
}

rpc_register::~rpc_register()
{
}

//将需要使用的远程调用的类和函数注册进去
void rpc_register::regis()
{
	m_regis_class.push_back("rpc_function");
	m_regis_function.push_back("rpc_function::j_add");
	m_regis_function.push_back("rpc_function::j_subtraction");
	m_regis_function.push_back("rpc_function::c_multiplication");
}
//对应调用
void rpc_register::fool(std::string function_parameter)
{
	//1.参数转换为可用参数
	std::vector<int> use_para;
	int temp = 0;
	for (int i = 0; i < function_parameter.size(); i++) {
		if (function_parameter[i] != ',') {
			temp *= 10;
			temp += function_parameter[i] - '0';
		}
		else {
			use_para.push_back(temp);
			temp = 0;
		}
	}
	use_para.push_back(temp);
	temp = 0;

	//2.对实例进行调用，并且将结果存入m_result
	rpc_function rpc_function_example;
	if (m_class_name == "rpc_function") {
		if (m_function_name == "j_add")
			m_rpc_result = std::to_string(rpc_function_example.j_add(use_para[0], use_para[1]));
		else if (m_function_name == "j_subtraction")
			m_rpc_result = std::to_string(rpc_function_example.j_subtraction(use_para[0], use_para[1]));
		else if (m_function_name == "c_multiplication")
			m_rpc_result = std::to_string(rpc_function_example.c_multiplication(use_para[0], use_para[1]));
	}
}

//检查
int rpc_register::link_to_function(std::string class_function_name)
{
	m_class_name = "";
	m_function_name = "";
	m_function_parameter = "";
	//1.解析class和function
	std::string temp = "";
	for (int i = 0; i < class_function_name.size(); i++) {
		if (class_function_name[i] != '.') {
			temp += class_function_name[i];
		}
		else {
			m_class_name = temp;
			temp = "";
		}
	}
	m_function_name = temp;

	//2.对结果进行检查，是否有对应的类和函数可以使用
	temp = "";
	temp += m_class_name;
	temp += "::";
	temp += m_function_name;
	for (int i = 0; i < m_regis_function.size(); i++) {
		if (temp == m_regis_function[i]) {
			return 1;//有对应的函数可用
		}
	}
	return 0;//无可用函数
}

//调用
std::string rpc_register::call_action(std::string function_parameter)
{
	fool(function_parameter);
	return m_rpc_result;
}


#endif // !__RPC_REGISTER_HPP_
