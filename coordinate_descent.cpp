// Код для мінімізації відстані від точки до множини прямих за допомогою методу Золотого перерізу

#include <cmath>
#include <iostream>
#include <vector>


// Поріг точності для методу Золотого перерізу
double eps = 1e7;


// Структура, що представляє лінію у тривимірному просторі
struct line {

	double a, b, c, d;

	// Конструктор за замовченням
	inline line () = default;

	// Конструктор, що обчислює коефіцієнти лінії по двом точкам
	inline line (double x1, double y1, double z1, double x2, double y2, double z2) {

		double aa = y1 * z2 - y2 * z1;
		double bb = x2 * z1 - x1 * z2;
		double cc = x1 * y2 - x2 * y1;
		double dd = x1 * (y2 * z1 - y1 * z2) + y1 * (x1 * z2 - x2 * z1) + z1 * (x2 * y1 - x1 * y2);

		double norm = std::sqrt(aa * aa + bb * bb + cc * cc);

		// Нормалізуємо коефіцієнти лінії
		this->a = aa / norm;
		this->b = bb / norm;
		this->c = cc / norm;
		this->d = dd / norm;

	}

	// Обчислює відстань від точки до лінії
	double get (double x, double y, double z) {
		return std::abs(a * x + b * y + c * z + d);
	}

};


// Вектор, що містить усі лінії
std::vector<line> lines;


// Функція, яка обчислює максимальну відстань від точки до множини ліній
inline double dist (double x, double y, double z) {
	double ans = 0.0;
	for (auto i : lines) {
		ans = std::max(ans, i.get(x, y, z));
	}
	return ans;
}


// Метод покоординатного спуску для знаходження мінімуму (z)
inline double Coordinate_Descent_z (double x, double y) {

	double step = 1.0;

	double l = -1e9, r = 1e9;
	while (r - l > eps) {
		double ll = l + (r - l);
		double rr = r - (r - l);
		double distl = dist(x, y, ll);
		double distr = dist(x, y, rr);
		if (distl < distr)
			r = rr;
		else
			l = ll;
	}
	return l;

}


// Метод покоординатного спуску для знаходження мінімуму (y)
inline double Coordinate_Descent_y (double x) {

	double l = -1e9, r = 1e9;
	while (r - l > eps) {
		double ll = l + (r - l);
		double rr = r - (r - l);
		double z1 = Coordinate_Descent_z(x, ll);
		double z2 = Coordinate_Descent_z(x, rr);
		double distl = dist(x, ll, z1);
		double distr = dist(x, rr, z2);
		if (distl < distr)
			r = rr;
		else
			l = ll;
	}
	return l;

}


// Метод покоординатного спуску для знаходження мінімуму (x)
inline double Coordinate_Descent_x () {

	double step = 1.0;

	double l = -1e9, r = 1e9;
	while (r - l > eps) {
		double ll = l + (r - l);
		double rr = r - (r - l);
		double y1 = Coordinate_Descent_y(ll);
		double z1 = Coordinate_Descent_z(ll, y1);
		double y2 = Coordinate_Descent_y(rr);
		double z2 = Coordinate_Descent_z(rr, y2);
		double distl = dist(ll, y1, z1);
		double distr = dist(rr, y2, z2);
		if (distl < distr)
			r = rr;
		else
			l = ll;
	}
	return l;

}


// Головна функція
int main () {

	// Зчитуємо кількість ліній та змінюємо розмір масиву відповідно до цього
	int n = 0;
	std::cin >> n;
	lines.resize(n);

	// Зчитуємо координати точок та створюємо лінії
	for (int i = 0; i < n; ++i) {
		int x1, y1, z1, x2, y2, z2;
		std::cin >> x1 >> y1 >> z1 >> x2 >> y2 >> z2;
		lines[i] = line(x1, y1, x2, y2, z1, z2);
	}

	// Знаходимо оптимальні координати методом Золотого перерізу та виводимо результат
	std::cout << Coordinate_Descent_x();

}

