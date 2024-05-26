#include <algorithm>
#include <iostream>
#include <vector>
#include <cmath>

template <typename T>
struct Point;

template <typename T>
struct Vector2d;

template <typename T, typename Container = std::vector<Point<T>>>
struct Polygon;

template <typename T>
struct Point {
    Point() = default;
    Point(const T& x_coor, const T& y_coor) : x_coor(x_coor), y_coor(y_coor) {}
    Point& operator+=(const Vector2d<T>& vec) {
        x_coor += vec.x_coor;
        y_coor += vec.y_coor;
        return *this;
    }
    bool operator==(const Point& other) const {
        return x_coor == other.x_coor && y_coor == other.y_coor;
    }
    T x_coor, y_coor;
};

template <typename T>
std::istream& operator>>(std::istream& in_flow, Point<T>& point) {
    in_flow >> point.x_coor >> point.y_coor;
    return in_flow;
}

template <typename T>
std::ostream& operator<<(std::ostream& out_flow, const Point<T>& point) {
    out_flow << point.x_coor << " " << point.y_coor;
    return out_flow;
}

template <typename T>
Point<T> operator+(const Point<T>& point, const Vector2d<T>& vec) {
    Point<T> copy = point;
    copy += vec;
    return copy;
}

template <typename T>
struct Vector2d {
    Vector2d() = default;
    Vector2d(const T& x_coor, const T& y_coor) : x_coor(x_coor), y_coor(y_coor) {}
    Vector2d(const Point<T>& first, const Point<T>& second)
        : x_coor(second.x_coor - first.x_coor),
        y_coor(second.y_coor - first.y_coor) {}
    Vector2d& operator*=(const T& alpha) {
        x_coor *= alpha;
        y_coor *= alpha;
        return *this;
    }

    Vector2d& operator+=(const Vector2d& other) {
        x_coor += other.x;
        y_coor += other.y;
        return *this;
    }

    Vector2d& operator-=(const Vector2d& other) {
        x_coor -= other.x;
        y_coor -= other.y;
        return *this;
    }

    T CrossProduct(const Vector2d<T>& other) const {
        return x_coor * other.y_coor - y_coor * other.x_coor;
    }

    T DotProduct(const Vector2d<T>& other) const {
        return x_coor * other.x_coor + y_coor * other.y_coor;
    }

    T VectorSquareLength() { return x_coor * x_coor + y_coor * y_coor; }

    T x_coor, y_coor;
};

template <typename T>
Vector2d<T> operator+(const Vector2d<T>& left, const Vector2d<T>& right) {
    Vector2d<T> copy = left;
    copy += right;
    return copy;
}

template <typename T>
Vector2d<T> operator-(const Vector2d<T>& left, const Vector2d<T>& right) {
    Vector2d<T> copy = left;
    copy -= right;
    return copy;
}

template <typename T>
Vector2d<T> operator*(const Vector2d<T>& vec, const T& alpha) {
    Vector2d<T> copy = vec;
    copy *= alpha;
    return copy;
}

template <typename T>
bool SortComparator(const Point<T>& left_point, const Point<T>& right_point) {
    Point<T> null(0, 0);
    Vector2d<T> first_vector(left_point, null);
    Vector2d<T> second_vector(right_point, null);
    if (first_vector.CrossProduct(second_vector) == 0) {
        return first_vector.VectorSquareLength() <
            second_vector.VectorSquareLength();
    }
    return first_vector.CrossProduct(second_vector) > 0;
}

template <typename T, typename Container>
class Polygon {
public:
    Polygon() = default;
    Polygon(size_t index, const Point<T>& point = Point<T>())
        : points_(index, point) {}
    using iterator = typename Container::iterator;             
    using const_iterator = typename Container::const_iterator; 
    using reverse_iterator = std::reverse_iterator<iterator>;  
    using const_reverse_iterator =                              
        std::reverse_iterator<const_iterator>;

    enum struct Situations { INSIDE, BOUNDARY, OUTSIDE };

    iterator begin() { return points_.begin(); } 

    iterator end() { return points_.begin(); }  

    const_iterator cbegin() const { return points_.cbegin(); } 

    const_iterator begin() const { return points_.cbegin(); } 

    const_iterator cend() const { return points_.cend(); } 

    const_iterator end() const { return points_.end(); } 

    reverse_iterator rbegin() { return points_.rbegin(); } 

    reverse_iterator rend() { return points_.rend(); } 

    const_reverse_iterator crbegin() const { 
        return points_.crbegin();
    }

    const_reverse_iterator rbegin() const { return points_.rbegin(); } 

    const_reverse_iterator crend() const { return points_.crend(); } 

    const_reverse_iterator rend() const { return points_.rend(); }

    Situations InPolygon(const Point<T>& check_point) const {
        int ray_count_intersections = 0;
        size_t number_points = points_.size();
        bool is_not_boundary_point = true;
        for (size_t j = 0; j < number_points; ++j) {
            Point<T> first_point = points_[j];
            Point<T> second_point = points_[(j + 1) % number_points];
            if (first_point.y_coor > second_point.y_coor) {
                std::swap(first_point, second_point);
            }
            Vector2d<T> first_vector(check_point, first_point);
            Vector2d<T> second_vector(second_point, first_point);
            T cross = first_vector.CrossProduct(second_vector);
            if (cross == 0 && first_point.y_coor <= check_point.y_coor &&
                check_point.y_coor <= second_point.y_coor &&
                std::min(first_point.x_coor, second_point.x_coor) <=
                check_point.x_coor &&
                check_point.x_coor <=
                std::max(first_point.x_coor, second_point.x_coor)) {
                is_not_boundary_point = false;
                break;
            }
            if (second_point.y_coor <= check_point.y_coor ||
                first_point.y_coor > check_point.y_coor) {
                continue;
            }
            if (cross > 0) {
                ++ray_count_intersections;
            }
        }

        if (is_not_boundary_point) {
            if (ray_count_intersections % 2 != 0) {
                return Situations::INSIDE;
            }
            return Situations::OUTSIDE;
        }
        return Situations::BOUNDARY;
    }

    bool ConvexCheck() const {
        Orientation flag = Orientation::UNDEFINED;
        size_t num_points = points_.size();
        for (size_t i = 0; i < num_points; ++i) {
            Point<T> first_point = points_[i];
            Point<T> second_point = points_[(i + 1) % num_points];
            Point<T> third_point = points_[(i + 2) % num_points];
            Vector2d<T> first_vector(first_point, second_point);
            Vector2d<T> second_vector(second_point, third_point);
            if (flag == Orientation::UNDEFINED) {
                if (first_vector.CrossProduct(second_vector) < 0) {
                    flag = Orientation::NEGATIVE;
                }
                else if (first_vector.CrossProduct(second_vector) > 0) {
                    flag = Orientation::POSITIVE;
                }
            }
            if ((first_vector.CrossProduct(second_vector) < 0 &&
                flag == Orientation::POSITIVE) ||
                (first_vector.CrossProduct(second_vector) > 0 &&
                    flag == Orientation::NEGATIVE)) {
                return false;
            }
        }
        return true;
    }

    Point<T>& operator[](size_t index) { return points_[index]; }

    const Point<T>& operator[](size_t index) const { return points_[index]; }

    size_t Size() const { return points_.size(); }

    void PushBack(const Point<T>& point) { points_.push_back(point); }

    template <typename... Args>
    void EmplaceBack(Args&&... args) {
        points_.emplace_back(std::forward<Args>(args)...);
    }

    Point<T>& Back() { return points_.back(); }

    const Point<T>& Back() const { return points_.back(); }

    void PopBack() { points_.pop_back(); }

    Container GetContainer() { return points_; }

    Container points_;

private:
    enum struct Orientation { UNDEFINED, POSITIVE, NEGATIVE };
};

template <typename T>
std::istream& operator>>(std::istream& in_flow, Polygon<T>& polygon) {
    for (size_t i = 0; i < polygon.Size(); ++i) {
        in_flow >> polygon[i];
    }
    return in_flow;
}

template <typename T>
std::ostream& operator<<(std::ostream& out_flow, const Polygon<T>& polygon) {
    for (size_t i = 0; i < polygon.Size(); ++i) {
        out_flow << polygon[i] << '\n';
    }
    return out_flow;
}

template <typename T, typename Container = std::vector<T>>
Polygon<T> ConvexHull(Container points) {
    size_t num_points = points.size();
    Point<T> left = points[0];
    for (size_t i = 0; i < num_points; ++i) {
        if (points[i].y_coor < left.y_coor) {
            left = points[i];
        }
        if (points[i].y_coor == left.y_coor && points[i].x_coor < left.x_coor) {
            left = points[i];
        }
    }

    for (size_t i = 0; i < num_points; ++i) {
        points[i].x_coor -= left.x_coor;
        points[i].y_coor -= left.y_coor;
    }

    std::sort(points.begin(), points.end(), SortComparator<T>);

    points.erase(unique(points.begin(), points.end()), points.end());
    num_points = points.size();

    for (size_t i = 0; i < num_points; ++i) {
        points[i].x_coor += left.x_coor;
        points[i].y_coor += left.y_coor;
    }

    Polygon<T> ans;
    for (size_t i = 0; i < num_points; ++i) {
        while (ans.Size() > 1) {
            Point<T> left = ans[ans.Size() - 2];
            Point<T> middle = ans[ans.Size() - 1];
            Vector2d<T> first_vector(left, middle);
            Vector2d<T> second_vector(middle, points[i]);
            T orient = first_vector.CrossProduct(second_vector);
            if (orient > 0) {
                break;
            }
            ans.PopBack();
        }
        ans.PushBack(points[i]);
    }
    std::reverse(ans.points_.begin() + 1, ans.points_.end());
    return ans;
}

template <typename T>
long double polygonArea(const Polygon<T>& polygon,  int n){
    long double area = 0.0;
    int j = n - 1;
    for (int i = 0; i <= n - 1; i++){
        area += polygon[i].y_coor * polygon[(i + 1) % n].x_coor - polygon[(i + 1) % n].y_coor * polygon[i].x_coor;
    }
    return fabs(area / 2.0);
}

int main() {
    size_t num_points;
    std::cin >> num_points;
    Polygon<long long> polygon(num_points);
    std::cin >> polygon;
    auto ans = ConvexHull<long long>(polygon.GetContainer());
    size_t size = ans.Size();
    std::cout << size << '\n';
    std::cout << ans;
    std::cout.precision(1);
    std::cout << std::fixed << polygonArea(ans, ans.Size());
}