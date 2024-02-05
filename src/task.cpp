#include <sys/resource.h>
#include <sys/wait.h>
#include <sys/mount.h>
#include <iostream>
#include <sched.h>
#include <signal.h>
#include "task.hpp"

int Task::entrySubprocess(void* args) {
    runCommand("/bin/bash");
}

int Task::taskRunner(void* args) {
    clearenv();
    std::string hostname = "ubuntu-2204-container";
    sethostname(hostname.c_str(), hostname.size());
    setenv("TERM", "xterm-256color", 0);
    setenv("PATH", "/bin/:/sbin/:usr/bin:/usr/sbin", 0);
    changeRoot("./ubuntu-base-22.04-base-arm64");
    mount("proc", "/proc", "proc", 0, 0);
    cloneProcess(entrySubprocess, SIGCHLD);
    umount("/proc");
    return EXIT_SUCCESS;
}

const std::string& Task::getName(void) {
    return this->m_name;
}

const MappedPaths& Task::getMappedPaths(void) {
    return this->m_mapped_paths;
}


const Status& Task::getStatus(void) {
    return this->m_status;
}

const std::vector<std::string>& Task::getFlags(void) {
    return this->m_flags;
}

const ResponseStatus& Task::start(void) {
    cloneProcess(taskRunner, CLONE_NEWUTS | CLONE_NEWPID | SIGCHLD);
    wait(nullptr);
}

void* Task::getFreeStack() {
    struct rlimit stack_lim;
    getrlimit(RLIMIT_STACK, &stack_lim);
    unsigned long stack_size = stack_lim.rlim_cur;

    char* stack = (char*) new (std::nothrow) char[stack_size];;
    if (!stack) {
        std::cout << "Cannot allocation a stack of " << stack_size << " bytes." << std::endl;
        exit(EXIT_FAILURE);
    }

    return (void*) stack + stack_size;
}

void Task::changeRoot(char* folder) {
    chroot(folder);
    chdir("/");
}