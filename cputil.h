#include <cstddef>
#ifndef CPU_H 
#define CPU_H
struct CPU {
    float utilization;
    size_t previous_idle_time;
    size_t previous_total_time;
};

struct RAM {
    size_t total_kb;
    size_t free_kb;
    size_t available_kb;
    size_t used_kb;
    float used_percent;
};

CPU cpu_util(size_t previous_idle_time, size_t previous_total_time);

RAM get_ram_info();

#endif
