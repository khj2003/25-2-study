#pragma once
template <typename T>
T add(T& x, T& y);
template <typename T>
T add(T& x, T& y) {
	T sum;
	sum = x + y;
	return sum;
}
