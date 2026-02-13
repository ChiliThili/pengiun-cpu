#include <fstream>
#include <iostream>
#include <unistd.h>
#include <vector>
#include <chrono>
#include <thread>
#include <print>
#include "cputil.h" 
#include <cstdlib>

int main() {
    const char* penguins[6][3] = {
        {  // Standard Penguin
            "(o_",
            "//\\",
            "V_/_\n"
        },
        {  // Pissed Penguin (Drunk)
            "(*_",
            "//\\", 
            "V_/_\n"
        },
        {  // Shocked Penguin
            "(O_",
            "//\\",
            "V_/_\n"
        },
        {  // Noisy Penguin
            "(o<",
            "//\\",
            "V_/_\n"
        },
        {  // Penguin Eating Fish
            "(o<)<",
            "//\\",
            "V_/_\n"
        },
        {  // Paranoid Penguin
            "_o)",
            "//\\",
            "V_/_\n"
        }
    };


    CPU cpu{0, 0, 0};
    int time{(int)(0.5 * 1000)};

    std::cout << "\033[?25l";  // Hide cursor
    std::cout <<"\033[2J\033[1;1H";  // Clear screen
    int pswitch{0};
    int rnd = rand() % 3;
    while(true){
        std::cout << "\033[?25l";  // Hide cursor
        std::cout <<"\033[2J\033[1;1H";  // Clear screen

        cpu = cpu_util(cpu.previous_idle_time, cpu.previous_total_time);
        RAM ram = get_ram_info();

        if(pswitch > 3 ){ rnd = rand() % 6; pswitch = 0;}
        for(int i = 0; i < 3; i++){
            std::println("{}", penguins[rnd][i]);
        }

        std::println("CPU: {:.1f}%  RAM: {:.1f}% ({:.1f}GB / {:.1f}GB)",
                cpu.utilization, 
                ram.used_percent,
                ram.used_kb / 1024.0f / 1024.0f,
                ram.total_kb / 1024.0f / 1024.0f
                );

        std::this_thread::sleep_for(std::chrono::milliseconds(time));
        pswitch++;
    }

    std::cout << "\033[?25h";  // Show cursor
    return 0;
}
