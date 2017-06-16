#ifdef __linux__
	#include <Python.h>
#elif __APPLE__
	#include <Python/Python.h>
#endif

#ifndef LIBSIGNATURE_H_
#define LIBSIGNATURE_H_

/* 
   Список экспортируемых функций
 */
PyObject * PyLoadCertificate(PyObject *self, PyObject *args);
PyObject * PyLoadCRL(PyObject *self, PyObject *args);
PyObject * PyVerifyCertChain(PyObject *self, PyObject *args);
PyObject * PyVerifySignedMessage(PyObject *self, PyObject *args);

/*
  Типы исключений различных ситуаций
 */
extern PyObject *PyOpenStoreError;
extern PyObject *PyAddCertToStoreError;
extern PyObject *PyCloseStoreError;
extern PyObject *PyAddCrlToStoreError;
extern PyObject *PyStrToBinLenError;
extern PyObject *PyStrToBinContentError;
extern PyObject *PyVerifyMsgSignatureError;
extern PyObject *PyGetCertChainError;
extern PyObject *PyReadCertError;
extern PyObject *PyReadCrlError;

#endif
