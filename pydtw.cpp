
#include <Python.h>
#include <stdlib.h>

#include "dtw.hpp"
#include <iostream>

template <typename T> static T *listToArr(int *size, PyObject *list) {
  if (!PyList_CheckExact(list)) {
    printf("support native python list only.\n");
    return NULL;
  }
  int arrlen = (int)PyObject_Length(list);
  if (arrlen < 0) {
    printf("bad list lenth.\n");
    return NULL;
  }
  T *arr = new T[arrlen];
  if (arr == NULL) {
    delete[] arr;
    printf("out of memory.\n");
    return NULL;
  }
  for (int i = 0; i < arrlen; ++i) {
    PyObject *item = PyList_GetItem(list, i);
    if (PyFloat_CheckExact(item)) {
      arr[i] = (T)PyFloat_AsDouble(item);
    } else if (PyLong_CheckExact(item)) {
      arr[i] = (T)PyLong_AsLong(item);
    } else {
      delete[] arr;
      printf("support native python int/float only.\n");
      return NULL;
    }
  } // for
  *size = arrlen;
  return arr;
} // listToArr

static PyObject *calDtw(PyObject *self, PyObject *args) {
  PyObject *float_list1;
  PyObject *float_list2;
  int arrlen1, arrlen2;
  double c;
  double *arr1;
  double *arr2;

  // 1. from py to c++
  if (!PyArg_ParseTuple(args, "OOd", &float_list1, &float_list2, &c)) {
    printf("bad parameters.\n");
    return NULL;
  }
  arr1 = listToArr<double>(&arrlen1, float_list1);
  if (arr1 == NULL) {
    return NULL;
  }
  arr2 = listToArr<double>(&arrlen2, float_list2);
  if (arr2 == NULL) {
    return NULL;
  }

  // 2. do c++ calculation
  double dist = dtw::dtw(arr1, arrlen1, arr2, arrlen2, c);
  delete[] arr1;
  delete[] arr2;

  return Py_BuildValue("d", dist);
} // calDtw

static PyMethodDef Methods[] = {
    {"calDtw", calDtw, METH_VARARGS,
     "Return the dtw distance between two given series."},
    {NULL, NULL, 0, NULL}}; // PyMethodDef GreetMethods

static struct PyModuleDef pydtw = {
    PyModuleDef_HEAD_INIT, "pydtw", /* name of module */
    "",                             /* module documentation, may be NULL */
    -1, /* size of per-interpreter state of the module, or -1 if the module
           keeps state in global variables. */
    Methods}; // struct pydtw

PyMODINIT_FUNC PyInit_pydtw(void) {
  return PyModule_Create(&pydtw);
} // PyInit_greet
