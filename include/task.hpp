#pragma once
#include <string>
#include <vector>
#include <utility>
#include <iostream>
#include <atomic>
#include <sys/wait.h>
#include "status.hpp"
#include "resp_status.hpp"

typedef std::vector<std::pair<std::string, std::string>> MappedPaths;

class Task {
private:
    std::string m_name;
    MappedPaths m_mapped_paths;
    std::atomic<Status> m_status;
    std::vector<std::string> m_flags;

public:
    Task(std::string name, MappedPaths mapped_paths)
        : m_name{name}
        , m_mapped_paths{mapped_paths}
    {}

    const std::string& getName();
    const MappedPaths& getMappedPaths();
    const Status& getStatus();
    const std::vector<std::string>& getFlags();

    bool start();
    const ResponseStatus& stop();

    static inline void* getFreeStack(unsigned long stack_size);
    template <typename... T>
    static int runCommand(T... params) {
        char *args[] = {(char *)params..., (char*) 0};
        for (int i = 0; i < (sizeof(args) / sizeof(void*)); i++) {
            std::cout << "args[" << i << "]: " << args[i] << std::endl;
        }
        return execvp(args[0], args);
    }

    static int entrySubprocess(void* args);
    static void changeRoot(char* folder);
    static void mountFs(MappedPaths const& mapped_paths);
    template <typename Function>
    static void cloneProcess(Function&& func, void* stack_addr, int flags) {
        pid_t child_pid = clone(func, stack_addr, flags, 0);
        wait(nullptr);
    }
    static int taskRunner(void* args);
    static inline unsigned long getStackSize();
};