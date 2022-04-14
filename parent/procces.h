#pragma once

#include <thread>

class Procces 
{
public:
    Procces(const Procces&) = delete;
    Procces& operator=(const Procces&) = delete;
    Procces(Procces&&) = delete;
    Procces& operator=(Procces&&)= delete;
    Procces(const char **argv)
       : childThread(&Procces::restart_prog,this, argv) {};

    ~Procces()
    {
        childThread.detach();
    }

private:
    int exec_prog(const char **argv);
    void restart_prog(const char **argv);

private:
    std::thread childThread;
};