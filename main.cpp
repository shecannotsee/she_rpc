#include <iostream>
#include <string>

#include "rpc_register.hpp"

using namespace std;

//假装该函数为调用函数，输入为远程输入参数，输出为返回输出
int main()
{
	string use_function_name;//调用rpc的名称
	rpc_register example;//rpc实例
	string result;//调用结果

	example.regis();//注册服务
	
	//模拟服务端持续开启
	while (1) {
part1:
		use_function_name = "";
		result = "";

		cout << "input use function(class.function)\n";
		cin >> use_function_name;

		if (!example.link_to_function(use_function_name)) {
			cout << "function does not exist\n";
			goto part1;
		}
		else {
			cout << "Functions can work\n";
		}

		cout << "input use function parameter(a,b,c,d)\n";
		use_function_name = "";
		cin >> use_function_name;
		result = example.call_action(use_function_name);
		

		cout << "call result is:" << result << "\n";


		cout << "rpc once over.\n\n";
	}

	return 0;
}


