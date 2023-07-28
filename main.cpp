#include <iostream>
#include <thread>
#include <vector>
#include <future>


void print_vect(std::vector<int>& vect);

template<typename InIt, typename Fn>
void my_for_each(InIt first, InIt last, Fn func);

int main() {
	setlocale(LC_ALL, "ru");
	std::cout << "\tfor_each\n\n" << std::endl;

	int size = 20;
	std::vector<int> vect;
	for (int i = 0; i < size; ++i) {
		vect.push_back(i);
	}

	std::cout << "Вектор до 'my_for_each': ";
	print_vect(vect);
	std::cout << std::endl << std::endl;

	my_for_each(vect.begin(), vect.end(), [](int& x) { x *= 2; });

	std::cout << "Вектор после 'my_for_each': ";
	print_vect(vect);
	std::cout << std::endl << std::endl;

	system("pause > nul");
	return 0;
}

template<typename InIt, typename Fn>
void my_for_each(InIt first, InIt last, Fn func) {
	size_t size = std::distance(first, last);
	if (!size) {
		return;
	}

	if (size < 2) {
		return func(*first);
	}
	else {
		auto middle = first;
		std::advance(middle, size / 2);

		auto ft_first = std::async(my_for_each<InIt, Fn>, first, middle, func);
		auto ft_second = std::async(my_for_each<InIt, Fn>, middle, last, func);

		ft_first.get();
		ft_second.get();
	}
}

void print_vect(std::vector<int>& vect) {
	for (auto it = vect.cbegin(); it != vect.cend(); ++it) {
		std::cout << *it << ' ';
	}
}
