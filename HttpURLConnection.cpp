//---------------------------------------------------------------------------

#pragma hdrstop

#include "HttpURLConnection.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

HttpURLConnection::HttpURLConnection()
{
    family  = AF_INET;
    version = "1.1";
    port = 80;

    RequestProperty* requestProperty = new RequestProperty("Connection", "close");
    this->requestProperty.push_back(requestProperty);
}
//---------------------------------------------------------------------------

HttpURLConnection::~HttpURLConnection()
{
    

}
//---------------------------------------------------------------------------

HttpURLConnection& HttpURLConnection::getInstance()
{
    HttpURLConnection* conn = new HttpURLConnection();
    return *conn;
}
//---------------------------------------------------------------------------

void HttpURLConnection::getFree(HttpURLConnection& conn)
{
    delete &conn;
}
//---------------------------------------------------------------------------

void HttpURLConnection::closeConnection(void)
{
    closesocket(sock);
    WSACleanup();

    setPort(0);
    setIp("/0");
    setRequestMethod("/0");
    setPath("/0");

    clearRequestProperty();

}
//---------------------------------------------------------------------------

HttpURLConnection& HttpURLConnection::clearRequestProperty()
{

    vector<RequestProperty*>::iterator itProperties;
    string header = "";
    for(itProperties = requestProperty.begin();
        itProperties != requestProperty.end();
        ++itProperties)
    {
        delete *itProperties;
    }

    requestProperty.clear();

    return *this;
}
//---------------------------------------------------------------------------

HttpURLConnection& HttpURLConnection::setIp(string ip)
{
    this->ip = ip;
  	server.sin_addr.s_addr = inet_addr(ip.c_str());

    return *this;
}
//---------------------------------------------------------------------------

HttpURLConnection& HttpURLConnection::setPort(int port)
{
    this->port = port;
    server.sin_port = htons(port);

    return *this;
}
//---------------------------------------------------------------------------

HttpURLConnection& HttpURLConnection::setRequestMethod(string requestMethod)
{
    this->requestMethod = requestMethod;
    return *this;
}
//---------------------------------------------------------------------------

HttpURLConnection& HttpURLConnection::setFamily(short family)
{
    this->family = family;
    server.sin_family = family;
    return *this;
}
//---------------------------------------------------------------------------

HttpURLConnection& HttpURLConnection::setRequestProperty(string key, string value)
{
    RequestProperty* requestProperty = new RequestProperty(key, value);
    this->requestProperty.push_back(requestProperty);
    return *this;

}
//---------------------------------------------------------------------------

HttpURLConnection& HttpURLConnection::setPath(string path)
{
    this->path = path;
    return *this;
}
//---------------------------------------------------------------------------

HttpURLConnection& HttpURLConnection::setVersion(string version)
{
    this->version = version;
    return *this;
}
//---------------------------------------------------------------------------

void HttpURLConnection::initializeWinsock()
{
    //initialising winsock
	if (WSAStartup(MAKEWORD(2,2),&wsadata) != 0)
	{
		cout << "Failed. Error Code : " << WSAGetLastError() << endl;
        throw( new HttpURLConnectionException("Failed. Error Code : " + WSAGetLastError()));
	}
}
//---------------------------------------------------------------------------

void HttpURLConnection::createSocket()
{
   	//Create a socket
	if((sock = socket(AF_INET , SOCK_STREAM , 0 )) == INVALID_SOCKET)
	{
		cout << "Could not create sock : " << WSAGetLastError();
        throw( new HttpURLConnectionException("Could not create sock : " + WSAGetLastError()));
	}
}
//---------------------------------------------------------------------------

void HttpURLConnection::httpConnect()
{
    initializeWinsock();

    createSocket();

    if (connect(sock , (struct sockaddr *)&server , sizeof(server)) < 0)
	{
		cout << "connect error" << endl;
        throw( new HttpURLConnectionException("connect error: " + WSAGetLastError()));
	}
    cout << "Connected" << endl;
}
//---------------------------------------------------------------------------

string HttpURLConnection::getMessage(void)
{
    vector<RequestProperty*>::iterator itProperties;
    string header = "";
    for(itProperties = requestProperty.begin();
        itProperties != requestProperty.end();
        ++itProperties)
    {
        header += (*itProperties)->key + ": " + (*itProperties)->value + "\r\n";
    }

    return requestMethod + " " + path + " " + "HTTP/" + version + "\r\n" + header + "\r\n";
}
//---------------------------------------------------------------------------

string HttpURLConnection::getResponse(void)
{
    httpConnect();
    
    string message = getMessage();
    if( send(sock , message.c_str() , message.length() , 0) < 0)
	{
		cout << "Send failed" << endl;
		throw new exception();
	}
    cout << "Data send" << endl;

  	//Receive a reply from the server
	if((recv_size = recv(sock , server_reply , 900000 , 0)) == SOCKET_ERROR)
	{
		cout << "recv failed" << endl;
   		throw new exception();
	}
	cout << "Reply received" << endl;

	//Add a NULL terminating character to make it a proper string before printing
	server_reply[recv_size] = '\0';

    return server_reply;
}
//---------------------------------------------------------------------------

string HttpURLConnection::getStatus(void)
{
    string response (server_reply);
    string delimiter = "HTTP/1.1";
    string token = response.substr(response.find(delimiter), response.find(delimiter) + delimiter.length()  + 4);

    vector<string> vector;
    split(vector, " ", token);
    status = vector[1];
    vector.clear();

    return status;
}
//---------------------------------------------------------------------------

void HttpURLConnection::split(vector<string>& vector, string delimiter, string str)
{

    string token;
    size_t pos = 0;
    while ((pos = str.find(delimiter)) != std::string::npos) {
        token = str.substr(0, pos);
        vector.push_back(token);
        cout << token  << endl;
        str.erase(0, pos + delimiter.length());
    }
    vector.push_back(str);
}
