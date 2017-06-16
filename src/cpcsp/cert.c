#include "cpcsp.h"

// функция чтения сертификата из файла
PCCERT_CONTEXT ReadCertificateFromFile(char *filename)
{
    PCCERT_CONTEXT cert_context = NULL;
    CPCSP_FILE     file_cert; 

    file_cert = ReadCpcspFile(filename);

    cert_context = CertCreateCertificateContext(
	ENCODING_TYPE,
	file_cert.content,
	file_cert.size);
    
    if (!cert_context)
	return NULL;

  return cert_context;
}

// функция загрузки сертификата в заданное хранилище
int LoadCertificateToSystemStore(char *cert_file_path, char *store_name)
{
    HCERTSTORE     cpcsp_cert_store = NULL;
    PCCERT_CONTEXT cert_context;

    cert_context = ReadCertificateFromFile(cert_file_path);
    if (!cert_context)
	return READ_CERT_ERROR;
  
    cpcsp_cert_store = CertOpenSystemStore(0, store_name);

    if (!cpcsp_cert_store)
	return OPEN_STORE_ERROR;

    if (!CertAddCertificateContextToStore(
	    cpcsp_cert_store,
	    cert_context,
	    CERT_STORE_ADD_REPLACE_EXISTING,
	    NULL))
	return ADD_CERT_TO_STORE_ERROR;

    if (!CertCloseStore(cpcsp_cert_store, 0))
	return CLOSE_STORE_ERROR;

    if (cert_context)
	CertFreeCertificateContext(cert_context);

    return OPERATION_SUCCESS;
}
