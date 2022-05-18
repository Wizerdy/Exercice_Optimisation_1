#pragma once
#include <queue>

template<typename T>
class Pool {
private:
	std::queue<T*> _pool;

public:
	Pool();
	~Pool();
	Pool(const Pool&) = delete;
	Pool(Pool&&) = delete;
	Pool& operator=(const Pool&) = delete;

	T* Pop();
	void Push(T* value);
	bool NotEmpty();
};
