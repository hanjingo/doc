#ifndef ACCOUNT_H
#define ACCOUNT_H
#include <iostream>
#include <iomanip>
#include <string>
#include <utility>
#include "Transaction.h"

using first_name = std::string;
using second_name = std::string;
using Name = std::pair<first_name, second_name>;

class Account
{
private:
    size_t account_number{};
    Name name{"", ""};
    double balance{};

public:
    Account() = default; // 获得默认构造函数
    Account(size_t number, const Name& nm) : account_number{number}, name{nm} {}

    double get_balance() const { return balance; }
    void set_balance(double bal) { balance = bal; }

    size_t get_acc_number() const { return account_number; }
    const Name& get_name() const { return name; }

    bool apply_transaction(const Transaction& transaction)
    {
        if (transaction.credit)
            balance += transaction.amount;
        else
            balance -= transaction.amount;
        return balance < 0.0;
    }

    bool operator<(const Account& acc) const { return account_number < acc.account_number; }
    friend std::ostream& operator<<(std::ostream& out, const Account& Account);
};

std::ostream& operator<<(std::ostream& out, const Account& acc)
{
    return out << std::left << std::setw(20) << acc.name.first + " " + acc.name.second
               << std::right << std::setfill('0') << std::setw(5) << acc.account_number
               << std::setfill(' ') << std::setw(8) << std::fixed << std::setprecision(2)
               << acc.balance;
}
#endif