#include <iostream>
#include <thread>
#include <vector>
#include <future>


void print_vect(const std::vector<int>& vect);

template<typename InIt, typename Fn>
void parallel_for_each(InIt first, InIt last, Fn func);

int main() {
	setlocale(LC_ALL, "ru");
	std::cout << "\tparallel_for_each\n\n" << std::endl;

	int size = 20;
	std::vector<int> vect;
	for (int i = 0; i < size; ++i) {
		vect.push_back(i);
	}

	std::cout << "Вектор до 'parallel_for_each': ";
	print_vect(vect);
	std::cout << std::endl << std::endl;

	parallel_for_each(vect.begin(), vect.end(), [](int& x) { x *= 2; });

	std::cout << "Вектор после 'parallel_for_each': ";
	print_vect(vect);
	std::cout << std::endl << std::endl;

	system("pause > nul");
	return 0;
}

template<typename InIt, typename Fn>
void parallel_for_each(InIt first, InIt last, Fn func) {
	size_t size = std::distance(first, last);

	if (size < 5) {
		std::for_each(first, last, func);
	}
	else {
		auto middle = first;
		std::advance(middle, size / 2);

		auto ft = std::async(parallel_for_each<InIt, Fn>, first, middle, func);
		parallel_for_each(middle, last, func);

		ft.get();
	}
}

void print_vect(const std::vector<int>& vect) {
	for (auto it = vect.cbegin(); it != vect.cend(); ++it) {
		std::cout << *it << ' ';
	}
}
