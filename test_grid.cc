#include <iostream>

#include "grid.h"

int main () {
	twentyfortyeight::Grid me(4);
	me(0, 1) = 1;
	me(2, 2) = 4;
	for (decltype(me.size()) y = 0; y < me.size(); ++y) {
		for (decltype(me.size()) x = 0; x < me.size(); ++x) std::cout << " " << me(x, y);
		std::cout << std::endl;
	}
	std::cout << "-------- ^- Normal | Right -v" << std::endl;
	me.move(me.right);
	for (decltype(me.size()) y = 0; y < me.size(); ++y) {
		for (decltype(me.size()) x = 0; x < me.size(); ++x) std::cout << " " << me(x, y);
		std::cout << std::endl;
	}
	std::cout << "-------- ^- Right | Add 3 and 2 -v" << std::endl;
	me(1, 1) = 3;
	me(0, 3) = 2;
	for (decltype(me.size()) y = 0; y < me.size(); ++y) {
		for (decltype(me.size()) x = 0; x < me.size(); ++x) std::cout << " " << me(x, y);
		std::cout << std::endl;
	}
	std::cout << "-------- ^- Add 3 and 2 | Down -v" << std::endl;
	me.move(me.down);
	for (decltype(me.size()) y = 0; y < me.size(); ++y) {
		for (decltype(me.size()) x = 0; x < me.size(); ++x) std::cout << " " << me(x, y);
		std::cout << std::endl;
	}
	return 0;
}
