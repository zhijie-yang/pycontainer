# A Simple Container with Python Interfaces

## Dependencies

```bash
sudo apt install cmake python3-dev
```

## Build

(Optional 1) Install in `home` directory or virtual environments

```bash
pip3 install .
```

(Option 2) Install under `/usr`

```bash
sudo pip3 install .
```

## Usage
Download an Ubuntu 22.04 root hierarchy (or any arbitrary image rootfs) and unzip it.
[amd64](https://cdimage.ubuntu.com/ubuntu-base/releases/22.04/release/ubuntu-base-22.04-base-amd64.tar.gz),
[arm64](https://cdimage.ubuntu.com/ubuntu-base/releases/22.04/release/ubuntu-base-22.04-base-arm64.tar.gz)

For installation with option 1:

```bash
# `env "PATH=$PATH` is necessary to find the executable if not installed with sudo...
sudo env "PATH=$PATH" pycontainer --name <name> --root <path/to/unzipped/rootfs> <command> [<args>...]
```

For installation with option 2:

```bash
sudo pycontainer --name <name> --root <path/to/unzipped/rootfs> <command> [<args>...]
```


## C++ Backend

Provides APIs for the lower level abstraction required to spawn containerised processes. Command line interface
is implemented with `main.py`. Can be used either as a C++ library or a Python module.

## Features

### Implemented

 * `chroot` jail (deprecated)
 * `pivot_root` jail
 * `proc` mapping
 * Isolation on cgroup, IPC, mount, network, PID and UTS

### Not implemented yet

 * Network binding
 * Arbitrary path mapping
 * `dev` and `sys` path mapping
 * Resource management with `cgroup`
 * User management under unshared user namespace
 * UnionFS
 * Daemon

## References

* [Contains from Scratch](https://github.com/lizrice/containers-from-scratch)
* [Creating Your Own Containers](https://cesarvr.github.io/post/2018-05-22-create-containers/)
* [tinydocker](https://github.com/HobbyBear/tinydocker/)
* [Ccont](https://github.com/7aske/ccont)