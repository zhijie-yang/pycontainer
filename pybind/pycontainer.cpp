#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "container.hpp"


namespace py = pybind11;

PYBIND11_MODULE(pycontainer, m) {
    py::class_<Container>(m, "Container")
        .def(py::init<std::string, MappedPaths>())
        .def("start", [] (Container &self, std::vector<std::string> args) {return self.start(args);});
}