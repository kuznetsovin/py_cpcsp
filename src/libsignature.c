#include <stdio.h>
#include "libsignature.h"

// Таблица методов реализуемых расширением
// название, функция, параметры, описание
static PyMethodDef LibsignatueMethods[] = {
    {"load_certificate",  PyLoadCertificate, METH_VARARGS, NULL},
    {"load_crl",  PyLoadCRL, METH_VARARGS, NULL},
    {"verify_chain_certificate",  PyVerifyCertChain, METH_VARARGS, NULL},
    {"vefigy_signature",  PyVerifySignedMessage, METH_VARARGS, NULL},
    {NULL, NULL,  0, NULL}
};

PyObject *PyOpenStoreError;
PyObject *PyAddCertToStoreError;
PyObject *PyCloseStoreError;
PyObject *PyAddCrlToStoreError;
PyObject *PyStrToBinLenError;
PyObject *PyStrToBinContentError;
PyObject *PyVerifyMsgSignatureError;
PyObject *PyGetCertChainError;
PyObject *PyReadCertError;
PyObject *PyReadCrlError;

// Инициализация
PyMODINIT_FUNC initlibsignature(void)
{
    PyObject *m;

    // Инизиализруем модуль libsignature
    m = Py_InitModule("libsignature", LibsignatueMethods);
    if (m == NULL)
        return;

    // Создание исключений при работе с расширением
    PyOpenStoreError = PyErr_NewException(
	"libsignature.OpenStoreError",
	NULL,
	NULL
	);
    PyAddCertToStoreError = PyErr_NewException(
	"libsignature.AddCertToStoreError",
	NULL,
	NULL
	);
    PyCloseStoreError = PyErr_NewException(
	"libsignature.CloseStoreError",
	NULL,
	NULL
	);
    PyAddCrlToStoreError = PyErr_NewException(
	"libsignature.AddCRLToStoreError",
	NULL,
	NULL
	);
    PyStrToBinLenError = PyErr_NewException(
	"libsignature.StrToBinLenError",
	NULL,
	NULL
	);
    PyStrToBinContentError = PyErr_NewException(
	"libsignature.StrToBinContentError",
	NULL,
	NULL
	);
    PyVerifyMsgSignatureError = PyErr_NewException(
	"libsignature.VerifySignError",
	NULL,
	NULL
	);
    PyGetCertChainError = PyErr_NewException(
	"libsignature.ChainCertError",
	NULL,
	NULL
	);
    PyReadCertError = PyErr_NewException(
	"libsignature.ReadCertError",
	NULL,
	NULL
	);
    PyReadCrlError = PyErr_NewException(
	"libsignature.ReadCRLError",
	NULL,
	NULL
	);

    Py_INCREF(PyOpenStoreError);
    Py_INCREF(PyAddCertToStoreError);
    Py_INCREF(PyCloseStoreError);
    Py_INCREF(PyAddCrlToStoreError);
    Py_INCREF(PyStrToBinLenError);
    Py_INCREF(PyStrToBinContentError);
    Py_INCREF(PyVerifyMsgSignatureError);
    Py_INCREF(PyGetCertChainError);
    Py_INCREF(PyReadCertError);
    Py_INCREF(PyReadCrlError);

    PyModule_AddObject(m, "error", PyOpenStoreError);
    PyModule_AddObject(m, "error", PyAddCertToStoreError);
    PyModule_AddObject(m, "error", PyCloseStoreError);
    PyModule_AddObject(m, "error", PyAddCrlToStoreError);
    PyModule_AddObject(m, "error", PyStrToBinLenError);
    PyModule_AddObject(m, "error", PyStrToBinContentError);
    PyModule_AddObject(m, "error", PyVerifyMsgSignatureError);
    PyModule_AddObject(m, "error", PyGetCertChainError);
    PyModule_AddObject(m, "error", PyReadCertError);
    PyModule_AddObject(m, "error", PyReadCrlError);
}
