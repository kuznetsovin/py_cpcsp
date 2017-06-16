#include <string.h>
#include "cpcsp.h"

int VerifyCertChain(char *cert_file_path)
{
    PCCERT_CONTEXT           cert_context;
    PCCERT_CHAIN_CONTEXT     chain_context;
    CERT_ENHKEY_USAGE        enhkey_usage;
    CERT_USAGE_MATCH         cert_usage;
    CERT_CHAIN_PARA          chain_para;

    /*
      инициализация парметров поиска и сопоставления, которые 
      будут использоваться для построения цепочки сертификатов 
    */
    enhkey_usage.cUsageIdentifier = 0;
    enhkey_usage.rgpszUsageIdentifier = NULL;
    cert_usage.dwType = USAGE_MATCH_TYPE_AND;
    cert_usage.Usage  = enhkey_usage;
    chain_para.cbSize = sizeof(CERT_CHAIN_PARA);
    chain_para.RequestedUsage = cert_usage;
 
    cert_context = ReadCertificateFromFile(cert_file_path);
    if (!cert_context)
	return READ_CERT_ERROR;

    // строим цепочку сертификатов
    if (!CertGetCertificateChain(
	    NULL,
	    cert_context,
	    NULL,
	    NULL,
	    &chain_para,
	    0,
	    NULL,
	    &chain_context))
	return GET_CERT_CHAIN_ERROR;

    int result = chain_context->TrustStatus.dwErrorStatus;

    if (chain_context)
	CertFreeCertificateChain(chain_context);
  
    return result;
}


//функция для проверки подписи
int VerifySignedMessage(char *signature)
{
    DWORD blob_size = 0;
    /* 
       определяем размер выходного der блоба
       для подписанного сообщения
    */
    if (!CryptStringToBinaryA(
	    signature,
	    strlen(signature),
	    CRYPT_STRING_BASE64,
	    NULL,
	    &blob_size,
	    NULL,
	    NULL))
	return STR_TO_BIN_LEN_ERROR;	


    /*
       заполняем блоб подписанного сообщения
     */
    BYTE *msg_blob;
    msg_blob = (BYTE *)malloc(blob_size);
    if (!CryptStringToBinaryA(
	    signature,
	    strlen(signature),
	    CRYPT_STRING_BASE64,
	    msg_blob,
	    &blob_size,
	    NULL,
	    NULL))
	return STR_TO_BIN_CONTENT_ERROR;	

    /*
      выполняем проверку подписи
     */
    CRYPT_VERIFY_MESSAGE_PARA verify_params;

    verify_params.cbSize = sizeof(CRYPT_VERIFY_MESSAGE_PARA);
    verify_params.dwMsgAndCertEncodingType = ENCODING_TYPE;
    verify_params.hCryptProv = 0;
    verify_params.pfnGetSignerCertificate = NULL;
    verify_params.pvGetArg = NULL;
    
    if(!CryptVerifyMessageSignature(
        &verify_params,
        0,
        msg_blob,
        blob_size,
        NULL,
        NULL,
        NULL))
	return VERIFY_MSG_SIGNATURE;
    
    return OPERATION_SUCCESS;
}
