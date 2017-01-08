#include "gbuf.h"

#include <string>
#include <iostream>

using namespace go;

struct mystruct {
	std::vector<int> a;
};

gbuf<mystruct> testBuf(10);

void reader() {

	for (int i = 0; i < 50; i++) {
		mystruct tmp_read;

		int rSize = testBuf.read(tmp_read);

		if (rSize == BUF_EMPTY) {
			std::cout << "Buffer is empty" << std::endl;
			break;
		}

		std::cout << rSize << " byte data was read from buffer." << std::endl;

		for (auto a : tmp_read.a) {
			std::cout << a << "";
		}

		std::cout << std::endl;

	}
}

void writer() {
	mystruct tmp_data;
	tmp_data.a.push_back(1);

	for (int i = 0; i < 100; i++) {

		int wSize = testBuf.write(tmp_data);

		if (wSize == BUF_FULL) {
			std::cout << "Buffer is full" << std::endl;
			break;
		}

		std::cout << wSize << " byte data was written to buffer." << std::endl;
		tmp_data.a.push_back(i);
	}
}

int main() {

	std::thread t1(reader);
	std::thread t2(writer);

	t1.join();
	t2.join();


	return 0;
}