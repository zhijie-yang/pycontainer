# A Simple Container with Python Interfaces

## C++ Backend

Run with `sudo ./pycontainer`. The examplary `main` creates a new process with the rootfs of an `ubuntu-2204`, calls and handles the new process to `/bin/bash`.

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