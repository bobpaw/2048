#include <stdexcept>
#include <random>
#include <memory>
#include <vector>

namespace twentyfortyeight {
	class Grid {
	private:

		std::size_t size_{0};
		std::vector<int> data_;
		std::vector<int> possible_;
		std::vector<int> nos;
		bool moved_{false};
		bool unmovable_{false};
		std::default_random_engine random_device;

		// Move functions
		void moveUp (void);
		void moveDown (void);
		void moveLeft (void);
		void moveRight (void);

		auto &possible (decltype(size_) x, decltype(size_) y) {
			if (x >= size_ || y >= size_) throw std::out_of_range("Grid::operator()");
			return possible_[y * size_ + x];
		}

	public:

		enum Direction { up, down, left, right };

		// Getters
		auto size (void) const noexcept { return size_; }
		auto moved (void) const noexcept { return moved_; }
		auto unmovable (void) const noexcept { return unmovable_; }

		// Constructors, Deconstructors
		Grid () : Grid(4) {}
		Grid (decltype(size_) size) : size_{size}, possible_(size_ * size_), data_(size_ * size_), nos(size_ * size_) {}
		~Grid () = default;

		// Use default copy, move
		Grid (const Grid &) = default;
		Grid &operator= (const Grid &) = default;
		Grid (Grid &&) = default;
		Grid &operator= (Grid &&) = default;

		// Operators
		auto &operator() (decltype(size_) x, decltype(size_) y) {
			if (x >= size_ || y >= size_) throw std::out_of_range("Grid::operator()");
			return data_[y * size_ + x];
		}

		auto operator() (decltype(size_) x, decltype(size_) y) const {
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
