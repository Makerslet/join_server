#ifndef CORE_MOCK_H
#define CORE_MOCK_H

#include "interfaces/execution_unit.h"
#include "interfaces/icore.h"

class core_mock : public icore
{
public:
    core_mock(std::shared_ptr<itables_manager> tm = nullptr) :
        _tm(tm) {}

    std::shared_ptr<itables_manager> tables_manager() override {
        return _tm;
    }

    void add_command(std::unique_ptr<execution_unit>&& exec_unit) override {
        _exec_units.push_back(std::move(exec_unit));
    }

    void start() override {}
    void stop() override {};

    std::vector<std::unique_ptr<execution_unit>> _exec_units;
    std::shared_ptr<itables_manager> _tm;
};

#endif // CORE_MOCK_H
