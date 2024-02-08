# A Simple Container with Python Interfaces

## Dependencies

```bash
sudo apt install cmake python3-dev
```

## Build

```bash
pip3 install .
```

## Usage
Download an Ubuntu 22.04 root hierarchy (or any arbitrary image rootfs) and unzip it.
[amd64](https://cdimage.ubuntu.com/ubuntu-base/releases/22.04/release/ubuntu-base-22.04-base-amd64.tar.gz),
[arm64](https://cdimage.ubuntu.com/ubuntu-base/releases/22.04/release/ubuntu-base-22.04-base-arm64.tar.gz)

```bash
# In project source directory, run with sudo privilege
\# python3 main.py --name someName --root /path/to/unzipped/rootfs \<command\> [<args>...]
# For example, this command will spawn a containerised bash and traps the current terminal into it
sudo python3 main.py --name containerised_bash --root ./ubuntu-base-22.04-base-arm64 /bin/bash
```

If installed with `pip`, this program can also be run with
```bash
sudo pycontainer --name someName --root ...
```

## C++ Backend

Provides APIs for the lower level abstraction required to spawn containerised processes. Command line interface
is implemented with `main.py`. Can be used either as a C++ library or a Python module.

## TODO

* Functionalities
  * Map default `/dev` with correct handling of `stdio`, `shm`, `random`, `zero`, etc.
  * Mapping for custom paths
  * Not yet decided...
* Setting up pybind11 interfaces
  * Use Python to manage multiple running interfaces
  * Serialize daemon status upon exiting

## References

* [Contains from Scratch](https://github.com/lizrice/containers-from-scratch)
* [Creating Your Own Containers](https://cesarvr.github.io/post/2018-05-22-create-containers/)
* [tinydocker](https://github.com/HobbyBear/tinydocker/)