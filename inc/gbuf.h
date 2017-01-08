#pragma once
#include <vector>
#include <mutex>

namespace gbuf {

	const int EMPTY_BUF = -1;
	const int FULL_BUF = -2;

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
		~gbuf() {
			for (T* a : buf) { delete a; }
		};

		int read(T &d) {
			std::lock_guard<std::mutex> lock(mtx);

			if (written <= 0) {
				return EMPTY_BUF;
			}

			rIndex = rIndex % bufSize;
			written--;
			d = *buf[rIndex++];
			return sizeof(d);
		}

		int write(T &d) {
			std::lock_guard<std::mutex> lock(mtx);

			if (written >= bufSize) {
				return FULL_BUF;
			}

			wIndex = wIndex % bufSize;
			*buf[wIndex] = d;
			written++;

			wIndex++;
			return sizeof(*buf[wIndex]);
		}
	};
}