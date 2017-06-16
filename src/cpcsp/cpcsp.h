#include <stdio.h>
#include <stdlib.h>
#include <CSP_WinDef.h>
#include <CSP_WinCrypt.h>

# define ROOT_STORE "ROOT"

# define ENCODING_TYPE PKCS_7_ASN_ENCODING | X509_ASN_ENCODING

/* 
   Коды ошибок
 */
# define OPERATION_SUCCESS        0
# define OPEN_STORE_ERROR         1
# define ADD_CERT_TO_STORE_ERROR  2
# define CLOSE_STORE_ERROR        3
# define ADD_CRL_TO_STORE_ERROR   4
# define STR_TO_BIN_LEN_ERROR     5
# define STR_TO_BIN_CONTENT_ERROR 6
# define VERIFY_MSG_SIGNATURE     7
# define GET_CERT_CHAIN_ERROR     8
# define READ_CERT_ERROR          9
# define READ_CRL_ERROR           10

/*
  Структура для корректной работы с файлами
 */
typedef struct CPCSP_FILE {
    BYTE *content;
    DWORD size;
} CPCSP_FILE;

/*  
    Список функций для работы с криптопро csp
*/
CPCSP_FILE ReadCpcspFile(char *filename);
PCCERT_CONTEXT ReadCertificateFromFile(char *filename);
PCCRL_CONTEXT ReadCRLFromFile(char *filename);
int LoadCertificateToSystemStore(char *certFilePath, char *storeName);
int LoadCRLToSystemStore(char *certFilePath, char *storeName);
int VerifyCertChain(char *certFilePath);
int VerifySignedMessage(char *signature);
char * ErrorMsg(char *message);
