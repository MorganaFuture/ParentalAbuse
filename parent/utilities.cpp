#include "utilities.h"

#include <sys/ipc.h>
#include <sys/shm.h>

#include <algorithm>
#include <string>

namespace Utilities
{
    std::string get_option(const std::vector<std::string>& args, const std::string& option_name) {
        for (auto it = args.begin(), end = args.end(); it != end; ++it) {
          if (*it == option_name)
              if (it + 1 != end)
                    return *(it + 1);
        }
    
        return "";
    }

    bool is_period_correct(const int period)
    {
        if ( (1 <= period)  && (period <= 1000) )
            return true;
        else
            return false;
    }

    bool is_number(const std::string& s)
    {
        return !s.empty() && std::find_if(s.begin(), 
            s.end(), [](unsigned char c) { return !std::isdigit(c); }) == s.end();
    }

    std::string create_shared_memory(const char *filepath, const int id, const size_t space)
    {
        const key_t key = ftok(filepath,id);
        if(key == -1)
            return "";

        const int shmid = shmget(key, space, 0666|IPC_CREAT);
        if(shmid == -1)
            return "";

        const void *buf = shmat(shmid,(void*)0,0);
        if (buf == (void *) -1)
		    return "";

        const int status = shmctl(shmid, IPC_RMID, 0);
        if(status == -1)
            return "";

        return std::to_string(key);
    }
} // Utilities
