#include "args_parser.h"

#include <iostream>

/**
 * @brief Entry point
 *
 * Execution of the program
 * starts here.
 *
 * @return Program exit status
 */

int main (int argc, char** argv)
{
    args_parser parser;
    auto result = parser.parse(argc, argv);
    if(!result.has_value())
        return 0;

    return 0;
}


