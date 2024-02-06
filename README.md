# A Simple Container with Python Interfaces

## Dependencies

```bash
sudo apt install cmake python3-dev
```

## Build

```bash
mkdir build && cd build
cmake ..
make
```

## Usage
Download an Ubuntu 22.04 root hierarchy and unzip it in the `build` directory.
[amd64](https://cdimage.ubuntu.com/ubuntu-base/releases/22.04/release/ubuntu-base-22.04-base-amd64.tar.gz),
[arm64](https://cdimage.ubuntu.com/ubuntu-base/releases/22.04/release/ubuntu-base-22.04-base-arm64.tar.gz)

```bash
# In project source directory
python3 main.py --name SomeName /bin/bash -c 'echo Hallo!'
```

## C++ Backend

Run with `sudo ./simple_container`. The examplary `main` creates a new process with the rootfs of an `ubuntu-2204`, calls and handles the new process to `/bin/bash`.

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