#include "cpcsp.h"


//функция для тестирования библиотеки
void ErrorHandler(char *message, int error_code)
{
    printf("Place error code: %d\n", error_code);

    char  *msg = ErrorMsg(message);
    printf("%s\n", msg);
    exit(1);
}

//функция для тестирования библиотеки
void RunTest()
{
    int error_code = 0;

    // загружаем сертификат УЦ
    error_code = LoadCertificateToSystemStore("./tests/files/ca.cer", ROOT_STORE);
    if (error_code != 0)
	ErrorHandler("Error load cert", error_code);
    else
	printf("Success cert load\n");
	    
    // загрузка списка отозванных сертификатов
    error_code = LoadCRLToSystemStore("./tests/files/ca.crl", ROOT_STORE);
    if (error_code != 0)
	ErrorHandler("Error load CRL", error_code);
    else
	printf("Success CRL load\n");

    // проверка подписи сертификата
    error_code = VerifyCertChain("./tests/files/user.cer");
    if (error_code != 0)
	ErrorHandler("Error verify chain cert", error_code);
    else
	printf("Success verify chain cert\n");

    CPCSP_FILE signed_file = ReadCpcspFile("./tests/files/test_sign.sig");
    error_code = VerifySignedMessage((char *)signed_file.content);
    if (error_code != 0)
    	ErrorHandler("Error verify signature", error_code);
    else
    	printf("Success verify signature\n");
}

int main()
{
    RunTest();
    return 0;
}
