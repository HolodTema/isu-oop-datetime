#ifndef QUICK_SORT_HPP
#define QUICK_SORT_HPP

#include <vector>
#include <algorithm>

template<typename T>
size_t partition(std::vector<T>& vec, int low, int high) {
	T pivot = vec[high];

	int i = low - 1;
	for (int j = low; j < high; ++j) {
		if (vec[j] <= pivot) {
			++i;
			std::swap(vec[i], vec[j]);
		}
	}

	std::swap(vec[i + 1], vec[high]);
	return i + 1;
}

template<typename T>
void quickSort(std::vector<T>& vec, size_t low, size_t high) {
	if (low < high) {
		size_t pivotIndex = partition(vec, low, high);
		quickSort(vec, low, pivotIndex - 1);
		quickSort(vec, pivotIndex + 1, high);
	}
}

template<typename T>
void quickSort(std::vector<T>& vec) {
	if (!vec.empty()) {
		quickSort(vec, 0, vec.size() - 1);
	}
}

#endif