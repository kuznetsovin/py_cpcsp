#include "libsignature.h"
#include "cpcsp/cpcsp.h"

/* 
   Питоновская обертка для добавления сертификата в хранилище 
*/
PyObject * PyLoadCertificate(PyObject *self, PyObject *args)
{
    char *cert_path=NULL;
    char *store_name=NULL;
    
    if (!PyArg_ParseTuple(args, "ss", &cert_path, &store_name))
	return NULL;
    
    int load_state = LoadCertificateToSystemStore(
    	cert_path,
    	store_name);

    switch (load_state) {
    case READ_CERT_ERROR:
    	PyErr_SetString(
    	    PyReadCertError,
    	    ErrorMsg("Can't read certificate file"));
    	return NULL;
    case OPEN_STORE_ERROR:
    	PyErr_SetString(
    	    PyOpenStoreError,
    	    ErrorMsg("Can't open certificate store"));
    	return NULL;
    case ADD_CERT_TO_STORE_ERROR:
    	PyErr_SetString(
    	    PyAddCertToStoreError,
    	    ErrorMsg("Can't append certificate to store"));
    	return NULL;
    case CLOSE_STORE_ERROR:
    	PyErr_SetString(
    	    PyCloseStoreError,
    	    ErrorMsg("Can't close certificate store"));
    	return NULL;
    default:
    	break;
    }
    
    Py_RETURN_NONE;
}

/* 
   Питоновская обертка для добавления 
   списка отозванных сертификатов в хранилище
*/
PyObject * PyLoadCRL(PyObject *self, PyObject *args)
{
    char *cert_path=NULL;
    char *store_name=NULL;
    
    if (!PyArg_ParseTuple(args, "ss", &cert_path, &store_name))
	return NULL;
    
    int load_state = LoadCRLToSystemStore(
    	cert_path,
    	store_name);

    switch (load_state) {
    case READ_CRL_ERROR:
    	PyErr_SetString(
    	    PyReadCrlError,
    	    ErrorMsg("Can't read crl file"));
    	return NULL;
    case OPEN_STORE_ERROR:
    	PyErr_SetString(
    	    PyOpenStoreError,
    	    ErrorMsg("Can't open crl store"));
    	return NULL;
    case ADD_CRL_TO_STORE_ERROR:
    	PyErr_SetString(
    	    PyAddCrlToStoreError,
    	    ErrorMsg("Can't append crl to store"));
    	return NULL;
    case CLOSE_STORE_ERROR:
    	PyErr_SetString(
    	    PyCloseStoreError,
    	    ErrorMsg("Can't close crl store"));
    	return NULL;
    default:
    	break;
    }
    
    Py_RETURN_NONE;
}

/* 
   Питоновская обертка для проверки цепочки сертификатов 
 */
PyObject * PyVerifyCertChain(PyObject *self, PyObject *args)
{
    char *cert_path=NULL;
    
    if (!PyArg_ParseTuple(args, "s", &cert_path))
	return NULL;
    
    int load_state = VerifyCertChain(cert_path);

    switch (load_state) {
    case READ_CERT_ERROR:
    	PyErr_SetString(
    	    PyReadCertError,
    	    ErrorMsg("Can't read certificate file"));
    	return NULL;
    case GET_CERT_CHAIN_ERROR:
    	PyErr_SetString(
    	    PyGetCertChainError,
    	    ErrorMsg("Can't get certificate chain"));
    	return NULL;
    default:
    	break;
    }
    
    Py_RETURN_NONE;
}

/*
  Питоновская обертка для проверки ЭЦП сообщения
 */
PyObject * PyVerifySignedMessage(PyObject *self, PyObject *args)
{
    char *signature=NULL;
    
    if (!PyArg_ParseTuple(args, "s", &signature))
	return NULL;
    
    int load_state = VerifySignedMessage(signature);

    switch (load_state) {
    case STR_TO_BIN_LEN_ERROR:
    	PyErr_SetString(
    	    PyStrToBinLenError,
    	    ErrorMsg("Can't get size decode signature"));
    	return NULL;
    case STR_TO_BIN_CONTENT_ERROR:
    	PyErr_SetString(
    	    PyStrToBinContentError,
    	    ErrorMsg("Can't decode signature"));
    	return NULL;
    case VERIFY_MSG_SIGNATURE:
    	PyErr_SetString(
    	    PyVerifyMsgSignatureError,
    	    ErrorMsg("Can't verify signature"));
    	return NULL;
    default:
    	break;
    }
    
    Py_RETURN_NONE;
}
