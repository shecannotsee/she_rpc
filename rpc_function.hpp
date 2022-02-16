#ifndef __RPC_FCUNTION_HPP_
#define __RPC_FCUNTION_HPP_

class rpc_function
{
public:
	int j_add(int a, int b) {
		return a + b;
	}

	int j_subtraction(int a, int b) {
		return a - b;
	}

	int c_multiplication(int a, int b) {
		return a * b;
	}
};

#endif // !__RPC_FCUNTION_HPP_
