/*
 Solution:
 The number of squares in a Pythagorean tree grows as 2^N, here N is the layer number (or the number of iteration).
 Aready for N = 30, the number of squares in the last layer is huge, namely 1073741824.
 Let's define by the term "branch" a consecutive sequence of the connected squares.
 In a branch all squares are obtained via the same two consecutive transformations (side scaling and susequent rotation
 around the edge). Thus, there are only two types of branches: with scaling of s1=4.0/5.0
 and anticlockwise scrolling and scaling of s2=3.0/5.0 and clockwise scrolling.
 One can see, that all branches are in fact spirals. One can observe, that each branch scrolls inside itself,
 after a certain number of squares are added. At this point a branch will not contribute to the
 tree expansion any more and can be completely excluded from computations.
 */

#include <stdio.h>
#include <vector>
#include <math.h>
#include <algorithm>

using numType = double;
// double precision is enough for the accurate computation of the tree size till the 10th digit

template<typename T>
class Rectangle
{
private:
	using edgesType = std::vector<T>;
	edgesType _x_edges;
	edgesType _y_edges;
	int _age = 0;

public:
	Rectangle(const edgesType& x_edges, const edgesType& y_edges) :
			_x_edges(x_edges), _y_edges(y_edges) {}

	Rectangle(const Rectangle<T>& rect) : _x_edges { rect.get_x_edges() }, 
			_y_edges { rect.get_y_edges() }, _age {rect.get_age()} {}

	auto get_x_edges() const -> const edgesType&
	{
		return _x_edges;
	}

	auto get_y_edges() const -> const edgesType&
	{
		return _y_edges;
	}

	auto transform_scale(numType factor) -> void
	{
		auto x = _x_edges;
		auto y = _y_edges;

		for (size_t it = 1; it < _x_edges.size(); ++it)
		{
			_x_edges[it] = factor * (x[it] - x[it - 1]) + _x_edges[it - 1];
			_y_edges[it] = factor * (y[it] - y[it - 1]) + _y_edges[it - 1];
		}
	}

	auto transform_rotate(numType angle) -> void
	{
		auto x = _x_edges;
		auto y = _y_edges;

		for (size_t it = 1; it < _x_edges.size(); ++it)
		{
			_x_edges[it] = cos(angle) * (x[it] - x[0]) + sin(angle) * (y[it] - y[0]);
			_y_edges[it] = -sin(angle) * (x[it] - x[0]) + cos(angle) * (y[it] - y[0]);
			_x_edges[it] += x[0];
			_y_edges[it] += y[0];
		}
	}

	auto circular_shift(int number) -> void
	{
		std::rotate(begin(_x_edges), begin(_x_edges) + number, end(_x_edges));
		std::rotate(begin(_y_edges), begin(_y_edges) + number, end(_y_edges));
	}

	auto transform_scale_rotate_shift(numType factor, numType angle, int shift) -> void
	{
		transform_scale(factor);
		transform_rotate(angle);
		circular_shift(shift);
	}

	auto reset_age() -> void
	{
		_age = 0;
	}

	auto get_age() const -> int
	{
		return _age;
	}

	auto increment_age() -> void
	{
		++_age;
	}
};

template<typename T>
class TreeClosureObserver
{
private:
	numType min_x = 0.0;
	numType max_x = 0.0;
	numType min_y = 0.0;
	numType max_y = 0.0;

	numType min_x_init;
	numType max_x_init;
	numType min_y_init;
	numType max_y_init;

public:
	TreeClosureObserver(const Rectangle<T>& rect)
	{
		min_x_init = *min_element(begin(rect.get_x_edges()), end(rect.get_x_edges()));
		max_x_init = *max_element(begin(rect.get_x_edges()), end(rect.get_x_edges()));
		min_y_init = *min_element(begin(rect.get_y_edges()), end(rect.get_y_edges()));
		max_y_init = *max_element(begin(rect.get_y_edges()), end(rect.get_y_edges()));
	}

	auto recompute_closure(const Rectangle<T>& rect) -> bool
	{
		T min_x_edge = *min_element(begin(rect.get_x_edges()), end(rect.get_x_edges()));
		T max_x_edge = *max_element(begin(rect.get_x_edges()), end(rect.get_x_edges()));
		T min_y_edge = *min_element(begin(rect.get_y_edges()), end(rect.get_y_edges()));
		T max_y_edge = *max_element(begin(rect.get_y_edges()), end(rect.get_y_edges()));

		if (min_x_edge < min_x)
		{
			min_x = min_x_edge;
			return true;
		}

		if (max_x_edge > max_x)
		{
			max_x = max_x_edge;
			return true;
		}

		if (min_y_edge < min_y)
		{
			min_y = min_y_edge;
			return true;
		}

		if (max_y_edge > max_y)
		{
			max_y = max_y_edge;
			return true;
		}

		return false;
	}

	auto get_closure_surface() const -> numType
	{
		auto x_min = std::min(min_x, min_x_init);
		auto x_max = std::max(max_x, max_x_init);
		auto y_min = std::min(min_y, min_y_init);
		auto y_max = std::max(max_y, max_y_init);

		return (x_max - x_min) * (y_max - y_min);
	}
};

using vecRectangles = std::vector<Rectangle<numType>>;
using namespace std;

auto main() -> int
{
	const int N_ITER = 100; // number of iteration (number of square layers)
	const int AGE_MAX = 10; // the tree branch dies, if the tree size is not increase after this number of added squares

	// right square
	numType factorRight = 3.0 / 5.0; // scale factor of the right square
	numType angleRight = 0.5 * M_PI + atan(4.0 / 3.0); // rotation angle of the right square
	int circShiftRight = 3; // circular shift of the rotation edge

	// left square
	numType factorLeft = 4.0 / 5.0; // scale factor of the left square
	numType angleLeft = -(0.5 * M_PI + atan(3.0 / 4.0)); // rotation angle of the left square
	int circShiftLeft = 2; // circular shift of the rotation edge

	// initial rectangle with the surface equal to 1.0
	auto rect = Rectangle<numType> { { 0.5, 0.5, -0.5, -0.5 }, { 0.5, -0.5, -0.5, 0.5 } };

	auto treeSizeObserver = TreeClosureObserver<numType>(rect);

	printf("closure surface %f\n", treeSizeObserver.get_closure_surface());

	vecRectangles rectangles { rect };
	vecRectangles rectangles_next_iter; // vector of rectangles is being populated at each iteration

	for (int iter = 0; iter < N_ITER; ++iter)
	{
		rectangles_next_iter.clear();

		for (int itRect = 0; itRect < rectangles.size(); ++itRect)
		{
			auto rectLeft = rectangles[itRect];
			auto rectRight = rectangles[itRect];

			// left rectangle transformation
			rectLeft.circular_shift(circShiftRight);
			rectLeft.transform_scale_rotate_shift(factorLeft, angleLeft, circShiftLeft);

			bool isTreeExpanded = treeSizeObserver.recompute_closure(rectLeft);

			if (isTreeExpanded)
			{
				rectLeft.reset_age();
				rectangles_next_iter.push_back(rectLeft);
			}
			else if (rectLeft.get_age() < AGE_MAX)
			{
				rectLeft.increment_age();
				rectangles_next_iter.push_back(rectLeft);
			}

			// right rectangle transformation
			rectRight.transform_scale_rotate_shift(factorRight, angleRight, circShiftRight);

			isTreeExpanded = treeSizeObserver.recompute_closure(rectRight);

			if (isTreeExpanded)
			{
				rectRight.reset_age();
				rectangles_next_iter.push_back(rectRight);
			}
			else if (rectRight.get_age() < AGE_MAX)
			{
				rectRight.increment_age();
				rectangles_next_iter.push_back(rectRight);
			}
		}

		rectangles = move(rectangles_next_iter);
		printf("iteration %d closure surface %.10f\n", iter, treeSizeObserver.get_closure_surface());
	}
}
