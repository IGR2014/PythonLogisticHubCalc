import subprocess
import random
import datetime
import matplotlib.pyplot as plt


# Функція для генерації випадкових ліній
def generate_random_lines(n):
    # Створюємо список, де кожен елемент - кортеж з шести випадкових чисел
    lines = [(
        str(random.randint(1, 1000)),
        str(random.randint(1, 1000)),
        str(random.randint(1, 1000)),
        str(random.randint(1, 1000)),
        str(random.randint(1, 1000)),
        str(random.randint(1, 1000))
    ) for _ in range(n)]
    return lines


# Функція для виклику зовнішньої С++ програми з випадковими даними та обчисленням часу виконання
def call_cpp_program(n, path):

    lines = generate_random_lines(n)

    # Запускаємо зовнішню C++ програму та вимірюємо час виконання
    start_time = datetime.datetime.now()
    process = subprocess.Popen(path, stdin=subprocess.PIPE, stdout=subprocess.PIPE, text=True)

    process.stdin.write(str(n) + '\n')
    for line in lines:
        process.stdin.write(' '.join(line) + '\n')
    process.stdin.flush()

    output, _ = process.communicate()
    end_time = datetime.datetime.now()

    execution_time = end_time - start_time
    return output, execution_time


# Функція для побудови графіку залежності часу виконання від N для двох алгоритмів
def plot_dependency_graph(N_values, execution_times_golden, execution_times_ternary, execution_times_descent):
    plt.plot(N_values, execution_times_golden, color='blue', label='Золотий переріз')
    plt.plot(N_values, execution_times_ternary, color='red', label='Тернарний пошук')
    plt.plot(N_values, execution_times_descent, color='green', label='Покоординатний спуск')
    plt.title('Залежнійсть Часу Виконання від N')
    plt.xlabel('Кількість ліній (N)')
    plt.ylabel('Час Виконання (секунд)')
    plt.legend()
    plt.show()


# Основна функція
def main():

    # Зберігатиме значення N для побудови графіку
    N_values = []
    # Зберігатиме час виконання для алгоритму "Золотий переріз"
    execution_times_golden = []
    # Зберігатиме час виконання для алгоритму "Тернарний пошук"
    execution_times_ternary = []
    # Зберігатиме час виконання для алгоритму "Покоординатний спуск"
    execution_times_descent = []

     # Порівнюємо два алгоритми для різної кількості ліній
    for n in range(1, 11, 1):

        # Розрахунок реальної кількості ліній
        real_n = n * 10000

        # Викликаємо зовнішні C++ програми та отримуємо час виконання
        execution_time_golden = call_cpp_program(real_n, './install/golden_selection.exe')
        execution_time_ternary = call_cpp_program(real_n, './install/ternary_search.exe')
        execution_time_descent = call_cpp_program(real_n, './install/coordinate_descent.exe')

        # Виводимо результати для аналізу
        print(f'{execution_time_golden[0]}, {execution_time_ternary[0]}, {execution_time_descent[0]}')

        # Зберігаємо дані для побудови графіку
        N_values.append(real_n)
        execution_times_golden.append(execution_time_golden[1].total_seconds())
        execution_times_ternary.append(execution_time_ternary[1].total_seconds())
        execution_times_descent.append(execution_time_descent[1].total_seconds())

    # Побудова графіку
    plot_dependency_graph(N_values, execution_times_golden, execution_times_ternary, execution_times_descent)


# Виклик головної функції
if __name__ == "__main__":
    main()

