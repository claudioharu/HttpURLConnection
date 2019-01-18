//---------------------------------------------------------------------------

#ifndef RequestPropertyH
#define RequestPropertyH
//---------------------------------------------------------------------------
#endif

#include <string>

using namespace std;

/**
@internal
@brief
    DTO contendo os campos do header
    da requisição

@author claudio.junior
@date 18/01/2019 14:56:28
*/
class RequestProperty
{
public:
    RequestProperty(string, string);
    string key;
    string value;
};