#include "cpcsp.h"

// функция для чтения списка отозванны сертификатов из файла
PCCRL_CONTEXT ReadCRLFromFile(char *filename)
{
    PCCRL_CONTEXT crl_context = NULL;
    CPCSP_FILE    crl_file; 

    crl_file = ReadCpcspFile(filename);
    crl_context = CertCreateCRLContext(
	ENCODING_TYPE,
	crl_file.content,
	crl_file.size);

    if (!crl_context)
	return NULL;

    return crl_context;
}


// функция загрузки списка отозванных сертификатов в заданное хранилище
int LoadCRLToSystemStore(char *cert_file_path, char *store_name)
{
    HCERTSTORE    cpcsp_cert_store = NULL;
    PCCRL_CONTEXT crl_context;

    crl_context = ReadCRLFromFile(cert_file_path);
    if (!crl_context)
	return READ_CRL_ERROR;
  
    cpcsp_cert_store = CertOpenSystemStore(0, store_name);

    if (!cpcsp_cert_store)
	return OPEN_STORE_ERROR;

    if (!CertAddCRLContextToStore(
	    cpcsp_cert_store,
	    crl_context,
	    CERT_STORE_ADD_REPLACE_EXISTING,
	    NULL))
	return ADD_CRL_TO_STORE_ERROR;

    if (!CertCloseStore(cpcsp_cert_store, 0))
	return CLOSE_STORE_ERROR;

    if (crl_context)
	CertFreeCRLContext(crl_context);

  return OPERATION_SUCCESS;
}
