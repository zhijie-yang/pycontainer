#pragma once
#include <string>
#include <vector>
#include <utility>
#include <ctime>
#include <iostream>
#include <atomic>
#include <sys/wait.h>
#include "container_status.hpp"
#include "resp_status.hpp"

typedef std::vector<std::pair<std::string, std::string>> MappedPaths;

class Container {
private:
    std::string ID_;
    std::string root_path;
    pid_t initi_process_pid_;
    uint64_t init_process_start_time_;
    std::time_t created_;
    MappedPaths mapped_paths_;
    std::atomic<ContainerStatus> status_;
    std::vector<std::string> flags_;

public:
    Container(std::string ID, std::string root_path, MappedPaths mapped_paths)
        : ID_{ID}
        , root_path {root_path}
        , mapped_paths_{mapped_paths}
    {}

    const std::string& getID();
    const MappedPaths& getMappedPaths();
    const ContainerStatus& getStatus();
    const std::vector<std::string>& getFlags();

    bool start(std::vector<std::string> args);
    const ResponseStatus& stop();

    static inline void* getFreeStack(unsigned long stack_size);
    static int runCommand(char** args);

    static int entrySubprocess(void* args);
    static void changeRoot(char* folder);
    static void mountFs(MappedPaths const& mapped_paths);
    template <typename Function>
    static void cloneProcess(Function&& func, void* stack_addr, int flags, void* args) {
        pid_t child_pid = clone(func, stack_addr, flags, args);
        if (child_pid == -1) {
            perror("Error clone child process");
        }
        wait(nullptr);
    }
    static int taskRunner(void* args);
    static inline unsigned long getStackSize();
};