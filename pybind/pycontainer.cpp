#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "task.hpp"


namespace py = pybind11;

PYBIND11_MODULE(pycontainer, m) {
    py::class_<Task>(m, "Task")
        .def(py::init<std::string, MappedPaths>())
        .def("start", [] (Task &self) {return self.start();});
}