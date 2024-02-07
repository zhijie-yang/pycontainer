#pragma once

// Status definition following
// https://github.com/opencontainers/runc/blob/main/libcontainer/container.go
enum ContainerStatus {
    CREATED,
    RUNNING,
    PAUSED,
    STOPPED
};
