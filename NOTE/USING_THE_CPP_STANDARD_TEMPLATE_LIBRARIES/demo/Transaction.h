#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <iostream>
#include <iomanip>
#include "Account.h"

class Transaction
{
private:
    size_t account_number{};
    double amount{};
    bool credit{true};

public:
    Transaction() = default;
    Transaction(size_t number, double amnt, bool cr) : 
        account_number{number}, amount{amnt}, credit{cr} {};
    size_t get_acc_number() const { return account_number; }

    bool operator<(const Transaction& transaction) const {
        return account_number < transaction.account_number;
    }
    bool operator>(const Transaction& transaction) const {
        return account_number > transaction.account_number;
    }
    friend std::ostream& operator<<(std::ostream& out, const Transaction& transaction);
    friend std::istream& operator>>(std::istream& in, Transaction& transaction);

    friend class Account;
};

std::ostream& operator<<(std::ostream& out, const Transaction& transaction)
{
    return out << std::right << std::setfill('0') << std::setw(5)
               << transaction.account_number
               << std::setfill('') << std::setw(8) << std::fixed << std::setprecision(2)
               << transaction.amount
               << (transaction.credit ? " CR" : " DR");
}

std::istream& operator>>(std::istream& in, Transaction& tr)
{
    if ((in >> std::skipws >> tr.account_number).eof())
        return in;
    return in >> tr.amount >> std::bcolalpha >> tr.credit;
}

#endif