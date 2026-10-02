#include <iostream>
#include <array>
#include <algorithm> 
#include <functional>
#include <ranges>

using namespace std;

namespace problem {

    void problem1() {
        //Дано пятизначное число. Найдите произведение его цифр.
        unsigned number;
        cout << "Enter five-digit number: ";
        cin >> number;
        
        const array<unsigned,5> powers = {1, 10, 100, 1000, 10000};

        // каждое значение power превращаем в цифру числа
        auto digits = powers | views::transform([number](unsigned power){
            return number / power % 10;
        });
        // все полученные цифры перемножаем
        auto result = ranges::fold_left(digits, 1u, multiplies{});

        cout << "Product of digits: " << result << endl;
    }

    void problem2() {
        /* Дано шестизначное число. Найдите суммы его четных и нечетных элементов.
           Образуйте из этих сумм одно число и выведите его на экран */
    
        unsigned number;
        cout << "Enter six-digit number: ";
        cin >> number;
    
        const array<unsigned, 6> powers = {100000, 10000, 1000, 100, 10, 1};
    
        auto digits = powers | views::transform([number](unsigned power) {
            return number / power % 10;
        });
    
        const array<unsigned, 3> odd_pos = {0, 2, 4};
        const array<unsigned, 3> even_pos = {1, 3, 5};
    
        array<unsigned, 6> digit_array{};
        ranges::copy(digits, digit_array.begin());
    
        auto odd_sum = ranges::fold_left(
            odd_pos,
            0u,
            [&](unsigned sum, unsigned pos) {
                return sum + digit_array[pos];
            }
        );
    
        auto even_sum = ranges::fold_left(
            even_pos,
            0u,
            [&](unsigned sum, unsigned pos) {
                return sum + digit_array[pos];
            }
        );
    
        auto result = odd_sum * 100 + even_sum;
    
        cout << "Result: " << result << endl;
    }

    void problem3(){
        /*Вводится натуральное число N, а затем N чисел.
        Найти среднее арифметическое всех чисел кратных 3. 
        Если таких чисел нет, то вывести -1*/

        unsigned N;
        cout << "Enter one digit (the count of next digits): ";
        cin >> N;

        vector<int> numbers(N);

        ranges::for_each(numbers, [](int& number){
            cin >> number;
        });

        auto multiples_of_three = numbers
            | views::filter([](int number){
                return number % 3 == 0;
            });

        auto sum = ranges::fold_left(
            multiples_of_three,
            0,
            plus{}
        );

        auto count = ranges::distance(multiples_of_three);

        if (count == 0) {
            cout << "Result: -1" << endl;
            return;
        }
        auto result = static_cast<double>(sum) / count;
        cout << "Result: " << result << endl;
    }

    void problem4(){
        /*Дано натуральное число A > 1.
        Определите, каким по счету числом Фибоначчи оно является,
        то есть выведите такое число n, что φ_n = A .
        Если А не является числом Фибоначчи, выведите число -1*/

        unsigned a;
        cout << "Enter a number: ";
        cin >> a;

        unsigned prev = 1;
        unsigned curr = 1;
        unsigned index = 2;

        auto next_fibonacci = [&](){
            auto next = prev + curr;
            prev = curr;
            curr = next;
            ++index;
        };

        while (curr < a){
            next_fibonacci();
        };
        auto result = curr == a ? static_cast<int>(index) : -1;
        cout << "Result: " << result << endl;
    }

    void problem5(){
        /* По данному числу N распечатайте все целые значения
        степени двойки, не превосходящие N, в порядке возрастания.*/
        unsigned n;
        cout << "Enter a number: ";
        cin >> n;

        unsigned power = 1;
        while (power <= n){
            cout << power << " ";
            power *= 2;
        }



    }



        
}

using namespace problem;

int main() {
    unsigned id_problem;
    std::cout << "Enter problem number: ";
    cin >> id_problem;

    switch (id_problem) {
        case 1:
            problem1();
            break;
        case 2:
            problem2();
            break;
        case 3:
            problem3();
            break;
        case 4:
            problem4();
            break;
        case 5:
            problem5();
            break;
        default:
            cout << "Invalid problem number" << endl;
            break;
    }
}