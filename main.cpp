#include <fstream>
#include <iostream>
#include <unistd.h>
#include <vector>
#include <chrono>
#include <thread>
#include <print>
#include "cputil.h" 

int main() {
    CPU cpu{0, 0, 0};
    int time{(int)(0.5 * 1000)};
    
    while(true){

        std::cout << "\033[?25l";  // Hide cursor
        std::cout <<"\033[2J\033[1;1H";  // Clear screen

        cpu = cpu_util(cpu.previous_idle_time, cpu.previous_total_time);
        RAM ram = get_ram_info();
        std::println("CPU: {:.1f}%  RAM: {:.1f}% ({:.1f}GB / {:.1f}GB)",
            cpu.utilization, 
            ram.used_percent,
            ram.used_kb / 1024.0f / 1024.0f,
            ram.total_kb / 1024.0f / 1024.0f
        );

        std::this_thread::sleep_for(std::chrono::milliseconds(time));
    }

    std::cout << "\033[?25h";  // Show cursor
    return 0;
}
