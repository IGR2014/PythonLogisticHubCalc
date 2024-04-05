// Код для мінімізації відстані від точки до множини прямих за допомогою методу Тернарного пошуку

#include <cmath>
#include <iostream>
#include <vector>


// Поріг точності для методу Тернарного пошуку
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
	inline double get (double x, double y, double z) {
		return std::abs(a * x + b * y + c * z + d);
	}

};


// Вектор, що містить усі лінії
std::vector<line> lines;


// Функція, яка обчислює максимальну відстань від точки до множини ліній
inline double dist(double x, double y, double z) {
	double ans = 0.0;
	for (auto i : lines) {
		ans = std::max(ans, i.get(x, y, z));
	}
	return ans;
}


// Функція для використання методу Тернарного пошуку для знаходження оптимального значення (z)
inline double Ternary_Search_z (double x, double y) {
	double l = -1e9, r = 1e9;
	while (r - l > eps) {
		double ll = l + (1.0 / 3.0) * (r - l);
		double rr = l + (2.0 / 3.0) * (r - l);
		if (dist(x, y, ll) < dist(x, y, rr))
			r = rr;
		else
			l = ll;
	}
	return l;
}

// Функція для використання методу Тернарного пошуку для знаходження оптимального значення (y)
inline double Ternary_Search_y (double x) {
	double l = -1e9, r = 1e9;
	while (r - l > eps) {
		double ll = l + (1.0 / 3.0) * (r - l);
		double rr = l + (2.0 / 3.0) * (r - l);
		double z1 = Ternary_Search_z(x, ll);
		double z2 = Ternary_Search_z(x, rr);
		if (dist(x, ll, z1) < dist(x, rr, z2))
			r = rr;
		else
			l = ll;
	}
	return l;
}

// Функція для використання методу Тернарного пошуку для знаходження оптимального значення (x)
inline double Ternary_Search_x () {
	double l = -1e9, r = 1e9;
	while (r - l > eps) {
		double ll = l + (1.0 / 3.0) * (r - l);
		double rr = l + (2.0 / 3.0) * (r - l);
		double y1 = Ternary_Search_y(ll);
		double z1 = Ternary_Search_z(ll, y1);
		double y2 = Ternary_Search_y(rr);
		double z2 = Ternary_Search_z(rr, y2);
		if (dist(ll, y1, z1) < dist(rr, y2, z2))
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
	std::cout << Ternary_Search_x();

}

