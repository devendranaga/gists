#include <csignal>
#include <iostream>

static std::sig_atomic_t signal_status;

void signal_handler(int signal)
{
    signal_status = signal;
}

int main()
{
    std::signal(SIGINT, signal_handler);

    while (1) {
        if (signal_status == SIGINT) {
            std::cout << "caught ctrl + c .. exit\n" << std::endl;
            break;
        }
    }
}

