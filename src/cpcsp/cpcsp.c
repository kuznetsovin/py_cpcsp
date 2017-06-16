#define _GNU_SOURCE
#include "cpcsp.h"

// функция чтения файла и преобразование его в определенную структуру
CPCSP_FILE ReadCpcspFile(char *filename)
{
    CPCSP_FILE cert = {NULL, 0};
    FILE       *cert_file;

    // выполняем чтение файла
    cert_file = fopen(filename, "r");
    if (cert_file)
    {
	fseek(cert_file, 0, SEEK_END);   
	cert.size = ftell(cert_file);
	rewind(cert_file);

	cert.content = (unsigned char *)malloc(cert.size * sizeof(unsigned char));
	fread(cert.content, cert.size, 1, cert_file);
    }
    fclose(cert_file);

  return cert;
}

// функция для получения текста ошибки с кодом
char * ErrorMsg(char *message)
{
    char *error_message=NULL;
    
    asprintf(
	&error_message,
	"%s. Code error: 0x%08x\n",
	message,
	GetLastError()
	);
    
    return error_message;
}
