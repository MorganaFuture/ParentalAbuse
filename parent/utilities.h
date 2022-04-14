#pragma once

#include <string>
#include <vector>

namespace Utilities
{
    std::string get_option( const std::vector<std::string>& args, const std::string& option_name);
    bool is_period_correct(const int period);
    bool is_number(const std::string& s);
    std::string create_shared_memory(const char *filepath, const int id, const size_t space);
} // namespace Utilities
