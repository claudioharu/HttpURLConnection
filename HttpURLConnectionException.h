//---------------------------------------------------------------------------

#ifndef HttpURLConnectionExceptionH
#define HttpURLConnectionExceptionH
//---------------------------------------------------------------------------
#endif

#include <string>
#include <exception>
using namespace std;

/**
@internal
@brief

    Exceções relacionadas ao encapsulador
    HttpURLConnection.
    
@author claudio.junior
@date 18/01/2019 14:57:13
*/
class HttpURLConnectionException :  public exception
{
private:
    string message;
public:
    HttpURLConnectionException(string);
    HttpURLConnectionException();
};
