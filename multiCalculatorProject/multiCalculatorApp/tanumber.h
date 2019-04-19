#ifndef TANUMBER_H
#define TANUMBER_H
#include <string>

class TANumber
{
public:
    TANumber() = default;
    virtual ~TANumber() = default;
    virtual std::unique_ptr<TANumber> clone () = 0;

    virtual std::unique_ptr<TANumber> summ(std::unique_ptr<TANumber> second) = 0;
    virtual std::unique_ptr<TANumber> substract(std::unique_ptr<TANumber> second) = 0;
    virtual std::unique_ptr<TANumber> mult(std::unique_ptr<TANumber> second) = 0;
    virtual std::unique_ptr<TANumber> divide(std::unique_ptr<TANumber> second) = 0;
    virtual std::unique_ptr<TANumber> square() = 0;
    virtual bool equal(std::unique_ptr<TANumber> second) = 0;
    virtual bool not_equal(std::unique_ptr<TANumber> second) = 0;
    virtual std::unique_ptr<TANumber> copy() = 0;

    virtual std::string getNumberAsString() = 0;
};

#endif // TANUMBER_H
