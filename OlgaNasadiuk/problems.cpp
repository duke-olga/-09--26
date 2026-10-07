#include <iostream>
#include <array>
#include <algorithm> 
#include <functional>
#include <ranges>
#include <optional>

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

    void problem6(){
        /* Сначала на вход поступает длина последовательности N.
        Затем элементы последовательности – целые числа.
        Подсчитать кол-во положительных чисел среди элементов последовательности.*/
        unsigned N;
        cout << "Enter one digit (the count of next digits): ";
        cin >> N;

        vector<int> numbers(N);

        ranges::for_each(numbers, [](int& number){
            cin >> number;
        });

        auto result = ranges::count_if(numbers, [](int number){
            return number > 0;
        });
        cout << "Result: " << result << endl;
    }

    void problem7(){
        /* Последовательность состоит из натуральных чисел и завершается числом 0.
        Определите кол-во элементов последовательности, которые равны ее наибольшему элементу.*/
        unsigned num;
        unsigned max_num = 0;
        unsigned count = 0;
        
        cout << "Enter numbers (to finish entering, enter 0): ";
        while (cin >> num && num != 0){
            if (num > max_num){
                max_num = num;
                count = 1;
            }
            else if (num == max_num){
                ++count;
            }
        }
        cout << "Result: " << count << endl;
    }

    //problem8
    /* Создайте класс Laptop, у которого есть:
        - Конструктор, принимающий 3 аргумента: бренд, модель и цену ноутбука.
          На основании этих аргументов нужно для экземпляра создать атрибуты brand, model,
          price и также атрибут laptop_name — строковое значение, следующего вида: «brand model»
        - Метод laptop_name возвращающий аналогичное значение поля*/

    class Laptop{
    private:
        string brand_;
        string model_;
        double price_;
        string laptop_name_;
    
    public:
        Laptop(string brand, string model, double price){
            brand_ = brand;
            model_ = model;
            price_ = price;
            laptop_name_ = brand + " " + model;
        }

        string laptop_name() const {
            return laptop_name_;
        }

        string brand() const {
            return brand_;
        }
    
        string model() const {
            return model_;
        }
    
        double price() const {
            return price_;
        }
    };

    void problem8(){
        Laptop laptop("HP", "Omen 15", 95000);
        cout << "Laptop name: " << laptop.laptop_name() << endl;
        cout << "brand: " << laptop.brand() << endl;
        cout << "model: " << laptop.model() << endl;
        cout << "price: " << laptop.price() << endl;
    }

    class Promise {
    private:
        unsigned id_; //СНИЛС
        double salary_;
        bool fulfilled_;

    public:
        Promise(unsigned id, double salary)
            : id_(id), salary_(salary), fulfilled_(false){
        }

        unsigned id() const{
            return id_;
        }

        double salary() const{
            return salary_;
        }

        bool fulfilled() const {
            return fulfilled_;
        }

        void set_fulfilled(bool value) {
            fulfilled_ = value;
        }
    };

    class Employee {
    private:
        string first_name_;
        string second_name_;
        unsigned id_;
        Promise promise_;
    public:
        Employee(string first_name,
                 string second_name,
                 unsigned id,
                 double salary)
            : first_name_(first_name),
            second_name_(second_name),
            id_(id),
            promise_(id, salary) {
        }

        string first_name() const {
            return first_name_;
        }
        
        string second_name() const {
            return second_name_;
        }
        
        unsigned id() const {
            return id_;
        }

        Promise& promise() {
            return promise_;
        }

        const Promise& promise() const {
            return promise_;
        }
    };

    class Director : public Employee {
    public:
        Director(string first_name,
                 string second_name,
                 unsigned id,
                 double salary)
            : Employee(first_name, second_name, id, salary) {
        }

        bool check_promises() const {
            return promise().fulfilled();
        }
    };

    class Company {
    private:
        double balance_;
        optional<Director> director_;
        vector<Employee> employees_;
    public:
        Company(double balance)
            : balance_(balance){
        }

        void create_director(
            string first_name,
            string second_name,
            unsigned id,
            double salary
        ) {
            director_.emplace(first_name, second_name, id, salary);
        }

        void create_employee(
            string first_name,
            string second_name,
            unsigned id,
            double salary
        ) {
            employees_.emplace_back(first_name, second_name, id, salary);
        }

        void set_profit(double profit) {
            balance_ += profit;
        }

        double balance() const {
            return balance_;
        }

        bool fulfill_promise() {
            double total_salary = 0.0;

            if (director_) {
                total_salary += director_->promise().salary();
            }
            ranges::for_each(employees_, [&](const Employee& employee) {
                total_salary += employee.promise().salary();
            });

            bool can_pay = balance_ >= total_salary;
            if (director_) {
                director_->promise().set_fulfilled(can_pay);
            }
            ranges::for_each(employees_, [&](Employee& employee) {
                employee.promise().set_fulfilled(can_pay);
            });

            if (can_pay) {
                balance_ -= total_salary;
            }
            return can_pay;
        }

        Director& director() {
            return director_.value();
        }
        
        const Director& director() const {
            return director_.value();
        }

        void print_info() const {
            cout << "Balance: " << balance_ << endl;
        
            if (director_) {
                cout << "Director: "
                     << director_->first_name() << " "
                     << director_->second_name() << endl;
        
                cout << "Salary: "
                     << director_->promise().salary() << endl;
        
                cout << "Promise: "
                     << boolalpha
                     << director_->promise().fulfilled() << endl;
            }
        
            cout << "Employees:" << endl;
        
            for (const auto& employee : employees_) {
                cout << employee.first_name() << " "
                     << employee.second_name()
                     << ", salary: "
                     << employee.promise().salary()
                     << ", promise: "
                     << boolalpha
                     << employee.promise().fulfilled()
                     << endl;
            }
        }
    };

    void problem9(){
        Company vk(50);

        vk.create_director("Gubka", "Bob", 1, 15);
    
        vk.create_employee("Patric", "Star", 2, 8);
        vk.create_employee("Scvidvard", "Shupalca", 3, 6);
    
        cout << "Before payment:" << endl;
        vk.print_info();
    
        vk.set_profit(150.25);
    
        cout << endl;
        cout << "After profit:" << endl;
        cout << "Fulfill promise: "
             << boolalpha
             << vk.fulfill_promise() << endl;
    
        vk.print_info();
    
        vk.set_profit(-300);
    
        cout << endl;
        cout << "After loss:" << endl;
        cout << "Fulfill promise: "
             << boolalpha
             << vk.fulfill_promise() << endl;
    
        vk.print_info();

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
        case 6:
            problem6();
            break;
        case 7:
            problem7();
            break;
        case 8:
            problem8();
            break;
        case 9:
            problem9();
            break;
        default:
            cout << "Invalid problem number" << endl;
            break;
    }
}