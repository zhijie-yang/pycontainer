#include <sys/resource.h>
#include <sys/wait.h>
#include <sys/mount.h>
#include <iostream>
#include <filesystem>
#include <sched.h>
#include <signal.h>
#include <string>
#include <cstring>
#include "container.hpp"


int Container::runCommand(char** args) {
    return execvp(args[0], args);
}

int Container::entrySubprocess(void* args) {
    runCommand((char**) args);
}

int Container::taskRunner(void* args) {
    // if (mount("", "/", "", MS_PRIVATE | MS_REC, NULL) == -1) {
    //     perror("Error remounting / as private mount: ");
    // }
    clearenv();
    std::string hostname = "ubuntu-2204-container";
    sethostname(hostname.c_str(), hostname.size());
    setenv("TERM", "xterm-256color", 0);
    setenv("PATH", "/bin/:/sbin/:usr/bin:/usr/sbin", 0);
    changeRoot(((char**) args)[0]);
    if (mount("proc", "/proc", "proc", MS_NOEXEC | MS_NODEV | MS_NOSUID, NULL) == -1) {
        perror("Error mounting /proc");
    }
    unsigned long stack_size = getStackSize();
    void* stack_addr = getFreeStack(stack_size);
    cloneProcess(entrySubprocess, stack_addr, SIGCHLD, &(((char**) args)[1]));
    free(stack_addr - stack_size);
    std::cout << "unmounting proc" << std::endl;
    umount("/proc");
    return EXIT_SUCCESS;
}

const std::string& Container::getID(void) {
    return this->ID_;
}

const MappedPaths& Container::getMappedPaths(void) {
    return this->mapped_paths_;
}

const ContainerStatus& Container::getStatus(void) {
    return this->status_;
}

const std::vector<std::string>& Container::getFlags(void) {
    return this->flags_;
}

bool Container::start(std::vector<std::string> args) {
    const char* args_[args.size()+2];
    args_[0] = this->root_path.c_str();
    for (size_t i = 0; i < args.size(); i++) {
        args_[i+1] = args[i].c_str();
        // std::cout << "args[" << i << "]: " << args[i] << std::endl;
    }
    args_[args.size()+1] = (char*) 0;
    unsigned long stack_size = getStackSize();
    void* stack_addr = getFreeStack(stack_size);
    cloneProcess(taskRunner, stack_addr, CLONE_NEWUTS | CLONE_NEWCGROUP | CLONE_NEWPID | CLONE_NEWIPC | CLONE_NEWNS | CLONE_NEWNET | SIGCHLD, args_);
    free(stack_addr - stack_size);
    return true;
}

void* Container::getFreeStack(unsigned long stack_size) {
    void* stack = malloc(stack_size);
    if (!stack) {
        std::cout << "Cannot allocation a stack of " << stack_size << " bytes." << std::endl;
        exit(EXIT_FAILURE);
    }

    return stack + stack_size;
}

void Container::changeRoot(char* folder) {
    if (chroot(folder) == -1) {
        perror("Error chroot");
        exit(EXIT_FAILURE);
    }
    if (chdir("/") == -1) {
        perror("Error chdir");
        exit(EXIT_FAILURE);
    }
}

unsigned long Container::getStackSize() {
    struct rlimit stack_lim;
    getrlimit(RLIMIT_STACK, &stack_lim);
    return stack_lim.rlim_cur;
}
