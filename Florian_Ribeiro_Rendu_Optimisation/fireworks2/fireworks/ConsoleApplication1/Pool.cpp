#include "Pool.h"
#include <iostream>

template<typename T>
Pool<T>::Pool() {
	_pool = new std::queue<T>();
}

template<typename T>
Pool<T>::~Pool() = default;

template<typename T>
void Pool<T>::Push(T* value) {
	_pool.push(value);
}

template<typename T>
T* Pool<T>::Pop() {
	T* obj = _pool.front();
	_pool.pop();
	return obj;
}

template<typename T>
bool Pool<T>::NotEmpty() {
	return !_pool.empty();
}