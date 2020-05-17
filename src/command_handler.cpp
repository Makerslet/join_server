#include "command_handler.h"
#include "command_handling_exception.h"

command_handler::command_handler(std::size_t num_workers) :
    _num_workers(num_workers)
{}

void command_handler::push_command(std::unique_ptr<execution_unit>&& exec_unit)
{
    _cmds_queue.push(std::move(exec_unit));
}

void command_handler::start_handling()
{
    for(std::size_t worker = 0; worker < _num_workers; ++worker)
        _workers.push_back(std::thread(create_worker_handler()));
}

void command_handler::stop_handling()
{
    _cmds_queue.shutdown();

    for(auto& thread_worker : _workers)
        thread_worker.join();
}

command_handler::worker_handler command_handler::create_worker_handler()
{
    return [this]() {

        while(_cmds_queue.is_running())
        {
            std::unique_ptr<execution_unit> exec_unit = _cmds_queue.pop();
            if(!exec_unit)
                continue;
            try {

                auto cmd_type = exec_unit->command->get_command_type();
                if(cmd_type == command_type::command_without_result)
                    exec_unit->command->execute(exec_unit->context);
                else
                {
                    std::string result = exec_unit->command->execute(exec_unit->context);
                    result += "OK\n";
                    exec_unit->context.sess->send(result);
                }
            }
            catch(const command_handling_exception& ex) {
                std::string description(ex.what());
                std::string err_description("ERR " + description + "\n");
                exec_unit->context.sess->send(err_description);
            }
        }
    };
}
