#include "grid.h"

namespace twentyfortyeight {
	void Grid::moveUp (void) {
		for (decltype(size_) y = 1; y < size_; ++y) {
			for (decltype(size_) x = 0; x < size_; ++x) {
				if (possible(x, y) != 0) {
					for (decltype(size_) i = 0; i < y; ++i) {
						if (possible(x, i) == 0) {
							possible(x, i) = possible(x, y);
							possible(x, y) = 0;
							break;
						}
					}
				}
			}
		}

		// Combine things
		for (decltype(size_) y = 1; y < size_; ++y) {
			for (decltype(size_) x = 0; x < size_; ++x) {
				if (possible(x, y) == possible(x, y - 1)) {
					possible(x, y - 1) = possible(x, y - 1) << 1;
					for (decltype(size_) i = y; i < size_ - 1; ++i) possible(x, i) = possible(x, i + 1);
					possible(x, size_ - 1) = 0;
				}
			}
		}
	}

	void Grid::moveDown (void) {
		for (decltype(size_) y = size_ - 2; y != static_cast<decltype(size_)>(-1); --y) {
			for (decltype(size_) x = 0; x < size_; ++x) {
				if (possible(x, y) != 0) {
					for (decltype(size_) i = size_ - 1; i > y; --i) {
						if (possible(x, i) == 0) {
							possible(x, i) = possible(x, y);
							possible(x, y) = 0;
							break;
						}
					}
				}
			}
		}

		// Combine things
		for (decltype(size_) y = size_ - 2; y != static_cast<decltype(size_)>(-1); --y) {
			for (decltype(size_) x = 0; x < size_; ++x) {
				if (possible(x, y) == possible(x, y + 1)) {
					possible(x, y + 1) = possible(x, y + 1) << 1;
					for (decltype(size_) i = y; i > 0; --i) possible(x, i) = possible(x, i - 1);
					possible(x, 0) = 0;
				}
			}
		}
	}

	void Grid::moveRight (void) {
		for (decltype(size_) y = 0; y < size_; ++y) {
			for (decltype(size_) x = size_ - 2; x != static_cast<decltype(size_)>(-1); --x) {
				if (possible(x, y) != 0) {
					for (decltype(size_) i = size_ - 1; i > x; --i) {
						if (possible(i, y) == 0) {
							possible(i, y) = possible(x, y);
							possible(x, y) = 0;
							break;
						}
					}
				}
			}
		}

		// Combine things
		for (decltype(size_) y = 0; y < size_; ++y) {
			for (decltype(size_) x = size_ - 2; x != static_cast<decltype(size_)>(-1); --x) {
				if (possible(x, y) == possible(x + 1, y)) {
					possible(x + 1, y) = possible(x + 1, y) << 1;
					for (decltype(size_) i = x; i > 0; --i) possible(i, y) = possible(i - 1, y);
					possible(0, y) = 0;
				}
			}
		}
	}

	void Grid::moveLeft (void) {
		for (decltype(size_) y = 0; y < size_; ++y) {
			for (decltype(size_) x = 1; x < size_; ++x) {
				if (possible(x, y) != 0) {
					for (decltype(size_) i = 0; i < x; ++i) {
						if (possible(i, y) == 0) {
							possible(i, y) = possible(x, y);
							possible(x, y) = 0;
							break;
						}
					}
				}
			}
		}

		// Combine things
		for (decltype(size_) y = 0; y < size_; ++y) {
			for (decltype(size_) x = 1; x < size_; ++x) {
				if (possible(x, y) == possible(x - 1, y)) {
					possible(x - 1, y) = possible(x - 1, y) << 1;
					for (decltype(size_) i = x; i < size_ - 1; ++i) possible(i, y) = possible(i + 1, y);
					possible(size_ - 1, y) = 0;
				}
			}
		}
	}

	void Grid::add (void) {
		int number = 2;
		if (random_device() % 5 == 0) number = 4;
		decltype(size_) nullcount = 0;
		for (decltype(size_) i = 0; i < size_ * size_; ++i)
			if (data_[i] == 0) ++nullcount;
		if (nullcount == 0) {
			bool alright = false;
			for (decltype(size_) y = 0; y < size_ - 1 && alright == false; ++y)
				for (decltype(size_) x = 0; x < size_ - 1 && alright == false; ++x)
					if (operator()(x, y) == operator()(x + 1, y) || operator()(x, y) == operator()(x, y + 1)) alright = true;
			if (alright == false) unmovable_ = true;
			return;
		}
		decltype(size_) *nos = new decltype(size_)[nullcount];
		for (decltype(size_) i = 0, n = 0; i < nullcount; ++n)
			if (data_[n] == 0) nos[i++] = n;
		int place = nos[random_device() % nullcount];
		data_[place] = number;
		delete[] nos;
	}
} // namespace twentyfortyeight
