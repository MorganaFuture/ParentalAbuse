#include <signal.h>

#include <string>
#include <vector>

#include <iostream>
#include "procces.h"
#include "utilities.h"

struct sigaction old_action;
const char CILD_PATH[] = "../child/child";
const char SHARED_MEMORY_PATH[] = ".";

void sigint_handler(int sig_no)
{
    printf("Shared memory cleaned \n");
    sigaction(SIGINT, &old_action, NULL);
    kill(0, SIGINT);
}

int main(int argc, char *argv[])
{
    std::cout << "Start parent" << std::endl;
    signal(SIGINT, sigint_handler);

    if(argc < 3)
        return -1;

    const std::vector<std::string> args(argv, argv + argc);
    const std::string str_period = Utilities::get_option(args, "-p");

    if(!Utilities::is_number(str_period))
        return -1;

    const int period = std::stoi(str_period);

    if (!Utilities::is_period_correct(period))
        return -1;

    const std::string memory_key = Utilities::create_shared_memory(SHARED_MEMORY_PATH, 65, sizeof(int));
    std::vector<const char*> agrv = {CILD_PATH, &memory_key[0], &std::to_string(period)[0], NULL};
    Procces child(agrv.data());

    for(;;)
        ;

    return 0;
}
