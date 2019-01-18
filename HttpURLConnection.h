//---------------------------------------------------------------------------

#ifndef HttpURLConnectionH
#define HttpURLConnectionH
//---------------------------------------------------------------------------
#endif

#include<winsock2.h>
#include <iostream>
#include <vector.h>
#include "RequestProperty.h"
#include "HttpURLConnectionException.h"

#pragma comment(lib,"ws2_32.lib") //Winsock Library
using namespace std;


/**
@internal
@brief
    Classe responsável por realizar requisições
    https.

    Por default:
        - family = AF_INET
        - HTTP/VERSION = 1.1
        Para alterações basta utilizar os respectivos setters

    TODOS:
        - Implementar o parse do response:
            - Separar o codigo de resposta
            - Separar a msg.
            - etc

@author claudio.junior
@date 18/01/2019 14:53:03
*/
class  HttpURLConnection
{
private:

    HttpURLConnection(void);
    ~HttpURLConnection(void);

    WSADATA wsadata;
	SOCKET sock;
    short family;

    struct sockaddr_in server;
	char *message , server_reply[900000];
	int recv_size;
    int port;

    string path;
    string requestMethod;
    string ip;
    string version;
    vector<RequestProperty*> requestProperty;

    void createSocket(void);
    void httpConnect(void);
    void initializeWinsock(void);

    string getMessage(void);


public:


    static HttpURLConnection& getInstance(void);
    static void getFree(HttpURLConnection& conn);

    HttpURLConnection& setFamily(short family);
    HttpURLConnection& setPort(int port);
    HttpURLConnection& setIp(string ip);
    HttpURLConnection& setRequestMethod(string requestMethod);
    HttpURLConnection& setPath(string service);
    HttpURLConnection& setRequestProperty(string key, string value);
    HttpURLConnection& setVersion(string version);
    HttpURLConnection& HttpURLConnection::clearRequestProperty(void);

    string getResponse(void);

    void closeConnection(void);
};
