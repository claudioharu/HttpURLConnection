//---------------------------------------------------------------------------

#pragma hdrstop

#include "HttpURLConnectionException.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

HttpURLConnectionException::HttpURLConnectionException()
{
}
//---------------------------------------------------------------------------

HttpURLConnectionException::HttpURLConnectionException(string message)
{
    this->message = message;
}
//---------------------------------------------------------------------------
 