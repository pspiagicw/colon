#include <memory>

class Statement;
using StatementPtr = std::unique_ptr<Statement>;


class Statement {
    public:
        virtual ~Statement() = default;

        virtual std::string type() const = 0;
};

class Expression {
    public:
        virtual ~Expression() = default;

        virtual std::string type() const = 0;
};

class IntegerExpression: public Expression {
    public:
        int value;

        IntegerExpression(int value) {
            this->value = value;
        }

        std::string type() const override {
            return "IntegerExpression";
        };
};

using ExpressionPtr = std::unique_ptr<Expression>;

class LetStatement: public Statement {
    public:
        std::string name;
        ExpressionPtr value;

        LetStatement(std::string name, ExpressionPtr value) {
            // Apparently you have to move the string
            this->name = std::move(name);
            this->value = std::move(value);
        }

        std::string type() const override {
            return "LetStatement";
        }
};

