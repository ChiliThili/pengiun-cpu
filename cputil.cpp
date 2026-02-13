#include"cputil.h"
#include<vector>
#include<fstream>
#include <numeric>

std::vector<size_t> get_cpu_times() {
    std::ifstream proc_stat("/proc/stat");
    proc_stat.ignore(5, ' '); // Skip the 'cpu' prefix.
    std::vector<size_t> times;
    for (size_t time; proc_stat >> time; times.push_back(time));
    return times;
}

bool get_cpu_times(size_t &idle_time, size_t &total_time) {
    const std::vector<size_t> cpu_times = get_cpu_times();
    if (cpu_times.size() < 4)
        return false;
    idle_time = cpu_times[3];  // idle time is 4th field
    total_time = std::accumulate(cpu_times.begin(), cpu_times.end(), 0);
    return true;
}

CPU cpu_util(size_t previous_idle_time, size_t previous_total_time) {
    size_t idle_time, total_time;
    if (!get_cpu_times(idle_time, total_time)) {
        return {0.0f, previous_idle_time, previous_total_time};
    }
    
    const float idle_time_delta = static_cast<float>(idle_time - previous_idle_time);
    const float total_time_delta = static_cast<float>(total_time - previous_total_time);
    const float utilization = total_time_delta > 0 ? 
        100.0f * (1.0f - idle_time_delta / total_time_delta) : 0.0f;
    
    CPU cpu;
    cpu.utilization = utilization;
    cpu.previous_idle_time = idle_time;
    cpu.previous_total_time = total_time;
    return cpu;
}

RAM get_ram_info() {
    RAM ram{0};
    std::ifstream meminfo("/proc/meminfo");
    
    std::string line;
    while (std::getline(meminfo, line)) {
        if (line.starts_with("MemTotal:")) {
            ram.total_kb = std::stoul(line.substr(9));
        }
        else if (line.starts_with("MemFree:")) {
            ram.free_kb = std::stoul(line.substr(8));
        }
        else if (line.starts_with("MemAvailable:")) {
            ram.available_kb = std::stoul(line.substr(13));
        }
    }
    
    ram.used_kb = ram.total_kb - ram.free_kb;
    ram.used_percent = 100.0f * (float)ram.used_kb / ram.total_kb;
    return ram;
}

