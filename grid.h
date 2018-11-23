#include <stdexcept>
#include <random>

namespace twentyfortyeight {
	class Grid {
	private:

		std::size_t size_;
		int * data_;
		int *possible_;
		bool moved_;
		std::default_random_engine random_device;

		// Move functions
		void moveUp (void);
		void moveDown (void);
		void moveLeft (void);
		void moveRight (void);

		int &possible (decltype(size_) x, decltype(size_) y) {
			if (x >= size_ || y >= size_) throw std::out_of_range("Grid::operator()");
			return possible_[y * size_ + x];
		}

	public:

		enum Direction { up, down, left, right };

		// Getters
		decltype(size_) size (void) const { return size_; }
		decltype(moved_) moved (void) const { return moved_; }

		// Constructors, Deconstructors
		Grid (int size) : size_(size) {
			data_ = new int[size_ * size_]();
			possible_ = new int[size_ * size_]();
		}

		~Grid () {
			delete[] data_;
			delete[] possible_;
		}

		// Operators
		int &operator() (decltype(size_) x, decltype(size_) y) {
			if (x >= size_ || y >= size_) throw std::out_of_range("Grid::operator()");
			return data_[y * size_ + x];
		}

		int operator() (decltype(size_) x, decltype(size_) y) const {
			if (x >= size_ || y >= size_) throw std::out_of_range("Grid::operator()");
			return data_[y * size_ + x];
		}

		void move (Direction dir) {
			for (decltype(size_) i = 0; i < size_ * size_; ++i) possible_[i] = data_[i];
			switch (dir) {
			case up:
				moveUp();
				break;
			case down:
				moveDown();
				break;
			case left:
				moveLeft();
				break;
			case right:
				moveRight();
				break;
			}
			bool same = true;
			for (decltype(size_) i = 0; i < size_ * size_; ++i) if (possible_[i] != data_[i]) same = false;
			if (!same) {
				for (decltype(size_) i = 0; i < size_ * size_; ++i) data_[i] = possible_[i];
				moved_ = true;
			} else moved_ = false;
		}

		void add (void);
	}; // class Grid
} // namespace twentyfortyeight
