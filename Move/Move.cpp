#include <iostream>
#include<string>
#include <Windows.h>
#include<memory>
#include<vector>
#include<algorithm>
#include<numeric>

using namespace std;
//Задание 1

template <typename T>
void move_vectors(vector<T>& source, vector<T>& destination)
{
    destination = move(source);
}
int main()
{
    setlocale(LC_ALL, "ru");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    vector<string> one = { "test_string1", "test_string2" };
    vector<string> two;

    cout << "Вектор one до перемещения: ";
    for (const auto& str : one)
    {
        cout << str << " ";
    }
    cout << endl;

    cout << "Вектор two до перемещения: ";
    for (const auto& str : two)
    {
        cout << str << " ";
    }
    cout << endl;

    move_vectors(one, two);

    cout << "Вектор one после перемещения: ";
    for (const auto& str : one)
    {
        cout << str << " ";
    }
    cout << endl;

    cout << "Вектор two после перемещения: ";
    for (const auto& str : two)
    {
        cout << str << " ";
    }
    cout << endl;

    return 0;
}
//Задание 2

class big_integer {
private:
    vector<int> digits;

public:
    big_integer(const string& str)
    {
        for (auto it = str.rbegin(); it != str.rend(); ++it) {
            digits.push_back(*it - '0');
        }
    }

    big_integer(big_integer&& other) noexcept : digits(move(other.digits)) {}

    big_integer& operator=(big_integer&& other) noexcept
    {
        if (this != &other) {
            digits = move(other.digits);
        }
        return *this;
    }

    big_integer operator+(const big_integer& other) const
    {
        big_integer result("");
        int carry = 0;
        size_t maxSize = max(digits.size(), other.digits.size());

        for (size_t i = 0; i < maxSize || carry; ++i)
        {
            int sum = carry;
            if (i < digits.size()) sum += digits[i];
            if (i < other.digits.size()) sum += other.digits[i];
            result.digits.push_back(sum % 10);
            carry = sum / 10;
        }

        return result;
    }

    big_integer operator*(int num) const
    {
        big_integer result("");
        int carry = 0;

        for (size_t i = 0; i < digits.size() || carry; ++i)
        {
            int product = carry;
            if (i < digits.size()) product += digits[i] * num;
            result.digits.push_back(product % 10);
            carry = product / 10;
        }

        return result;
    }

    friend std::ostream& operator<<(std::ostream& os, const big_integer& num)
    {
        for (auto it = num.digits.rbegin(); it != num.digits.rend(); ++it)
        {
            os << *it;
        }
        return os;
    }
};

int main() {
    auto number1 = big_integer("114575");
    auto number2 = big_integer("78524");
    auto result = number1 + number2;
    cout << result << std::endl;

    auto multiplied = number1 * 2;
    cout << multiplied << std::endl;

    return 0;
}