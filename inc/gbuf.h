#pragma once
#include <vector>
#include <mutex>

namespace go {
	static const int BUF_EMPTY = -1;
	static const int BUF_FULL = -2;

	template<typename T> class gbuf
	{
	private:
		int rIndex;
		int wIndex;
		int bufSize;
		int written;
		std::mutex mtx;
		std::vector<T*> buf;

	public:
		gbuf(int size) : rIndex(0), wIndex(0), bufSize(size), written(0) {
			std::lock_guard<std::mutex> lock(mtx);

			for (int i = 0; i < bufSize; i++) { buf.push_back(new T()); };
		};

		~gbuf() { for (T* a : buf) { delete a; } };

		int read(T &d) {
			std::lock_guard<std::mutex> lock(mtx);

			if (written <= 0) {
				return BUF_EMPTY;
			}

			rIndex = rIndex % bufSize;
			written--;
			d = *buf[rIndex++];
			return sizeof(d);
		};

		int write(T &d) {
			std::lock_guard<std::mutex> lock(mtx);

			if (written >= bufSize) {
				return BUF_FULL;
			}

			wIndex = wIndex % bufSize;
			*buf[wIndex] = d;
			written++;

			wIndex++;
			return sizeof(*buf[wIndex]);
		};
	};
}