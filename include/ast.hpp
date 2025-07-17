#include <memory>

class Statement;
using StatementPtr = std::unique_ptr<Statement>;

class Statement {
    public:
        virtual ~Statement() = default;

        virtual std::string string();
};

