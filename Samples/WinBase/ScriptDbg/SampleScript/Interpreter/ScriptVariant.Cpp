/******************************************************************************
* 
*  File: ScriptVariant.cpp
*
*  Author:  Joel Alley
*
*  Date: September 4, 1998
*
*  Description:   This file contains the definition of a wrapper class for 
*                 VARIANT's.  It's primary purpose is to overload the basic
*                 operators, initializers and destructors to make VARIANT's
*                 a little easier to deal with in the script engine.
*
*  Modifications:
******************************************************************************/
#define SCRIPTVARIANT
#include "depends.h"
#include "wchar.h"

//Constructors
ScriptVariant::ScriptVariant( BOOL deleteVariant)
{
   SCRIPTVARIANTTRACE( "ScriptVariant\n");

   m_pValue = new VARIANT;
   VariantInit( m_pValue );
   m_isExternal = false;
   m_deleteVariant = deleteVariant;
}

ScriptVariant::ScriptVariant( const ScriptVariant& source )
{
   SCRIPTVARIANTTRACE( "ScriptVariant\n");

   m_pValue = new VARIANT;
   VariantInit(m_pValue );
   VariantCopy( m_pValue, source.m_pValue );
   m_isExternal = source.m_isExternal;
   m_deleteVariant = source.m_deleteVariant;

}

ScriptVariant::ScriptVariant( VARIANT* pVariant, BOOL deleteVariant )
{
   SCRIPTVARIANTTRACE( "ScriptVariant\n");

   m_pValue = pVariant;
   m_isExternal = false;
   m_deleteVariant = deleteVariant;
}

ScriptVariant::ScriptVariant( LPCOLESTR pStr, BOOL deleteVariant )
{
   SCRIPTVARIANTTRACE( "ScriptVariant\n");

   m_pValue = new VARIANT;
   VariantInit( m_pValue );
   m_pValue->vt = VT_BSTR;
   m_pValue->bstrVal = SysAllocString( pStr );
   m_isExternal = false;
   m_deleteVariant = deleteVariant;
}

ScriptVariant::ScriptVariant( long lVal, BOOL deleteVariant )
{
   SCRIPTVARIANTTRACE( "ScriptVariant\n");

   m_pValue = new VARIANT;
   VariantInit( m_pValue );
   m_pValue->vt = VT_R8;
   m_pValue->dblVal = (double)lVal;
   m_isExternal = false;
   m_deleteVariant = deleteVariant;
}

ScriptVariant::ScriptVariant( double dbVal, BOOL deleteVariant )
{
   SCRIPTVARIANTTRACE( "ScriptVariant\n");

   m_pValue = new VARIANT;
   VariantInit( m_pValue );
   m_pValue->vt = VT_R8;
   m_pValue->dblVal = dbVal;
   m_isExternal = false;
   m_deleteVariant = deleteVariant;
}

ScriptVariant::ScriptVariant( IDispatch* pDispatch, BOOL deleteVariant )
{
   SCRIPTVARIANTTRACE( "ScriptVariant\n");

   m_pValue = new VARIANT;
   VariantInit( m_pValue );
   m_pValue->vt = VT_DISPATCH;
   m_pValue->pdispVal = pDispatch;
   m_isExternal = false;
   m_deleteVariant = deleteVariant;
}

//Destructor
ScriptVariant::~ScriptVariant()
{
   SCRIPTVARIANTTRACE("~ScriptVariant\n");

   if (m_deleteVariant){
      VariantClear( m_pValue );
      delete m_pValue;
   }
}

BOOL ScriptVariant::isTrue()
{
   //Create some temporaries.
   VARIANT temp1;
   VariantInit( &temp1 );

   //Attempt to convert the comparison values to doubles
   HRESULT hr1 = VariantChangeType( &temp1, m_pValue, 0, VT_R8 );

   if (SUCCEEDED(hr1))
   {
      return temp1.dblVal != 0.0;
   }
   else
      return false;
}

BOOL ScriptVariant::isExternal()
{
   return m_isExternal;
}

void ScriptVariant::isExternal( BOOL value )
{
   m_isExternal = value;
}

LPCOLESTR ScriptVariant::toString( )
{
   WCHAR* buffer = new WCHAR[80];

   switch( m_pValue->vt ){
   case VT_EMPTY:
      swprintf( buffer, L"<VT_EMPTY>   Unitialized" );
      break;
   case VT_UI1:
      swprintf( buffer, L"<VT_UI1>   %c", m_pValue->bVal);
      break;
   case VT_I2:
      swprintf( buffer, L"<VT_I2>   %d", m_pValue->iVal );
      break;
   case VT_I4:
      swprintf( buffer, L"<VT_I4>   %d", m_pValue->lVal );
      break;
   case VT_R4:
      swprintf( buffer, L"<VT_R4>   %f", m_pValue->fltVal );
      break;
   case VT_R8:
      swprintf( buffer, L"<VT_R8>   %f", m_pValue->dblVal );
      break;
   case VT_BOOL:
      swprintf( buffer, L"<VT_BOOL>   %S", m_pValue->boolVal ? "true" : "false");
      break;
   case VT_ERROR:
      swprintf( buffer, L"<VT_ERROR>   %X", m_pValue->scode );
      break;
   case VT_BSTR:
      swprintf( buffer, L"<VT_BSTR>   %s", m_pValue->bstrVal );
      break;
   case VT_BYREF | VT_UI1:
      swprintf( buffer, L"<VT_BYREF | VT_UI1>   %c", *(m_pValue->pbVal));
      break;
   case VT_BYREF | VT_I2:
      swprintf( buffer, L"<VT_BYREF | VT_I2>   %d", *(m_pValue->piVal) );
      break;
   case VT_BYREF | VT_I4:
      swprintf( buffer, L"<VT_BYREF | VT_I4>   %d", *(m_pValue->plVal) );
      break;
   case VT_BYREF | VT_R4:
      swprintf( buffer, L"<VT_BYREF | VT_R4>   %f", *(m_pValue->pfltVal) );
      break;
   case VT_BYREF | VT_R8:
      swprintf( buffer, L"<VT_BYREF | VT_R8>   %f", *(m_pValue->pdblVal) );
      break;
   case VT_BYREF | VT_BOOL:
      swprintf( buffer, L"<VT_BYREF | VT_BOOL>   %S", *(m_pValue->pboolVal) ? "true" : "false");
      break;
   case VT_BYREF | VT_ERROR:
      swprintf( buffer, L"<VT_BYREF | VT_ERROR>   %X", *(m_pValue->pscode) );
      break;
   case VT_BYREF | VT_BSTR:
      swprintf( buffer, L"<VT_BYREF | VT_BSTR>   %S", *(m_pValue->pbstrVal) );
      break;
   default:
      swprintf( buffer, L"Unprintable VARIANT type." );
      break;
   }

   return buffer;
}

//Assignment Operations
ScriptVariant ScriptVariant::operator=( ScriptVariant rightChild )
{ 
   VariantCopy( m_pValue, rightChild.m_pValue );
   return rightChild;
}

ScriptVariant ScriptVariant::operator*=( ScriptVariant rightChild )
{
   ScriptVariant temp(*this);
   *this = temp * rightChild;
   return *this;
}

ScriptVariant ScriptVariant::operator/=( ScriptVariant rightChild )
{
   ScriptVariant temp(*this);
   *this = temp / rightChild;
   return *this;
}

ScriptVariant ScriptVariant::operator+=( ScriptVariant rightChild )
{
   ScriptVariant temp(*this);
   *this = temp + rightChild;
   return *this;
}

ScriptVariant ScriptVariant::operator-=( ScriptVariant rightChild )
{
   ScriptVariant temp(*this);
   *this = temp - rightChild;
   return *this;
}

//Logical Operations
ScriptVariant ScriptVariant::operator||( ScriptVariant rightChild )
{
   //Create some temporaries.
   VARIANT temp1;
   VariantInit( &temp1 );

   VARIANT temp2;
   VariantInit(&temp2);

   ScriptVariant returnVal;

   //Attempt to convert the comparison values to doubles
   HRESULT hr1 = VariantChangeType( &temp1, m_pValue, 0, VT_R8 );
   HRESULT hr2 = VariantChangeType( &temp2, rightChild.m_pValue, 0, VT_R8 );

   //If we succeeded, perform the operation and place the value in
   //the returnVal ScriptVariant.
   if ((SUCCEEDED(hr1)) && (SUCCEEDED(hr2)))
   {
      returnVal.m_pValue->vt = VT_R8;
      returnVal.m_pValue->dblVal = temp1.dblVal || temp2.dblVal;
   }

   //send back returnVal whether or not we succeeded.  If we failed, then
   //returnVal's VT_EMPTY type will signify it nicely.
   return returnVal;
}

ScriptVariant ScriptVariant::operator&&( ScriptVariant rightChild )
{
   //Create some temporaries.
   VARIANT temp1;
   VariantInit( &temp1 );

   VARIANT temp2;
   VariantInit(&temp2);

   ScriptVariant returnVal;

   //Attempt to convert the comparison values to doubles
   HRESULT hr1 = VariantChangeType( &temp1, m_pValue, 0, VT_R8 );
   HRESULT hr2 = VariantChangeType( &temp2, rightChild.m_pValue, 0, VT_R8 );

   //If we succeeded, perform the operation and place the value in
   //the returnVal ScriptVariant.
   if ((SUCCEEDED(hr1)) && (SUCCEEDED(hr2)))
   {
      returnVal.m_pValue->vt = VT_R8;
      returnVal.m_pValue->dblVal = temp1.dblVal && temp2.dblVal;
   }

   //send back returnVal whether or not we succeeded.  If we failed, then
   //returnVal's VT_EMPTY type will signify it nicely.
   return returnVal;
}

ScriptVariant ScriptVariant::operator==( ScriptVariant rightChild )
{
   //Create some temporaries.
   VARIANT temp1;
   VariantInit( &temp1 );

   VARIANT temp2;
   VariantInit(&temp2);

   ScriptVariant returnVal;

   //Attempt to convert the comparison values to doubles
   HRESULT hr1 = VariantChangeType( &temp1, m_pValue, 0, VT_R8 );
   HRESULT hr2 = VariantChangeType( &temp2, rightChild.m_pValue, 0, VT_R8 );

   //If we succeeded, perform the operation and place the value in
   //the returnVal ScriptVariant.
   if ((SUCCEEDED(hr1)) && (SUCCEEDED(hr2)))
   {
      returnVal.m_pValue->vt = VT_R8;
      returnVal.m_pValue->dblVal = temp1.dblVal == temp2.dblVal;
   }

   //send back returnVal whether or not we succeeded.  If we failed, then
   //returnVal's VT_EMPTY type will signify it nicely.
   return returnVal;
}

ScriptVariant ScriptVariant::operator!=( ScriptVariant rightChild )
{
   //Create some temporaries.
   VARIANT temp1;
   VariantInit( &temp1 );

   VARIANT temp2;
   VariantInit(&temp2);

   ScriptVariant returnVal;

   //Attempt to convert the comparison values to doubles
   HRESULT hr1 = VariantChangeType( &temp1, m_pValue, 0, VT_R8 );
   HRESULT hr2 = VariantChangeType( &temp2, rightChild.m_pValue, 0, VT_R8 );

   //If we succeeded, perform the operation and place the value in
   //the returnVal ScriptVariant.
   if ((SUCCEEDED(hr1)) && (SUCCEEDED(hr2)))
   {
      returnVal.m_pValue->vt = VT_R8;
      returnVal.m_pValue->dblVal = temp1.dblVal != temp2.dblVal;
   }

   //send back returnVal whether or not we succeeded.  If we failed, then
   //returnVal's VT_EMPTY type will signify it nicely.
   return returnVal;
}

ScriptVariant ScriptVariant::operator<( ScriptVariant rightChild )
{
   //Create some temporaries.
   VARIANT temp1;
   VariantInit( &temp1 );

   VARIANT temp2;
   VariantInit(&temp2);

   ScriptVariant returnVal;

   //Attempt to convert the comparison values to doubles
   HRESULT hr1 = VariantChangeType( &temp1, m_pValue, 0, VT_R8 );
   HRESULT hr2 = VariantChangeType( &temp2, rightChild.m_pValue, 0, VT_R8 );

   //If we succeeded, perform the operation and place the value in
   //the returnVal ScriptVariant.
   if ((SUCCEEDED(hr1)) && (SUCCEEDED(hr2)))
   {
      returnVal.m_pValue->vt = VT_R8;
      returnVal.m_pValue->dblVal = temp1.dblVal < temp2.dblVal;
   }

   //send back returnVal whether or not we succeeded.  If we failed, then
   //returnVal's VT_EMPTY type will signify it nicely.
   return returnVal;
}

ScriptVariant ScriptVariant::operator>( ScriptVariant rightChild )
{
   //Create some temporaries.
   VARIANT temp1;
   VariantInit( &temp1 );

   VARIANT temp2;
   VariantInit(&temp2);

   ScriptVariant returnVal;

   //Attempt to convert the comparison values to doubles
   HRESULT hr1 = VariantChangeType( &temp1, m_pValue, 0, VT_R8 );
   HRESULT hr2 = VariantChangeType( &temp2, rightChild.m_pValue, 0, VT_R8 );

   //If we succeeded, perform the operation and place the value in
   //the returnVal ScriptVariant.
   if ((SUCCEEDED(hr1)) && (SUCCEEDED(hr2)))
   {
      returnVal.m_pValue->vt = VT_R8;
      returnVal.m_pValue->dblVal = temp1.dblVal > temp2.dblVal;
   }

   //send back returnVal whether or not we succeeded.  If we failed, then
   //returnVal's VT_EMPTY type will signify it nicely.
   return returnVal;
}

ScriptVariant ScriptVariant::operator>=( ScriptVariant rightChild )
{
   //Create some temporaries.
   VARIANT temp1;
   VariantInit( &temp1 );

   VARIANT temp2;
   VariantInit(&temp2);

   ScriptVariant returnVal;

   //Attempt to convert the comparison values to doubles
   HRESULT hr1 = VariantChangeType( &temp1, m_pValue, 0, VT_R8 );
   HRESULT hr2 = VariantChangeType( &temp2, rightChild.m_pValue, 0, VT_R8 );

   //If we succeeded, perform the operation and place the value in
   //the returnVal ScriptVariant.
   if ((SUCCEEDED(hr1)) && (SUCCEEDED(hr2)))
   {
      returnVal.m_pValue->vt = VT_R8;
      returnVal.m_pValue->dblVal = temp1.dblVal >= temp2.dblVal;
   }

   //send back returnVal whether or not we succeeded.  If we failed, then
   //returnVal's VT_EMPTY type will signify it nicely.
   return returnVal;
}

ScriptVariant ScriptVariant::operator<=( ScriptVariant rightChild )
{
   //Create some temporaries.
   VARIANT temp1;
   VariantInit( &temp1 );

   VARIANT temp2;
   VariantInit(&temp2);

   ScriptVariant returnVal;

   //Attempt to convert the comparison values to doubles
   HRESULT hr1 = VariantChangeType( &temp1, m_pValue, 0, VT_R8 );
   HRESULT hr2 = VariantChangeType( &temp2, rightChild.m_pValue, 0, VT_R8 );

   //If we succeeded, perform the operation and place the value in
   //the returnVal ScriptVariant.
   if ((SUCCEEDED(hr1)) && (SUCCEEDED(hr2)))
   {
      returnVal.m_pValue->vt = VT_R8;
      returnVal.m_pValue->dblVal = temp1.dblVal <= temp2.dblVal;
   }

   //send back returnVal whether or not we succeeded.  If we failed, then
   //returnVal's VT_EMPTY type will signify it nicely.
   return returnVal;
}

//Binary Operations
ScriptVariant ScriptVariant::operator+( ScriptVariant rightChild )
{
   //Create some temporaries.
   VARIANT temp1;
   VariantInit( &temp1 );

   VARIANT temp2;
   VariantInit(&temp2);

   ScriptVariant returnVal;

   //Attempt to convert the comparison values to doubles
   HRESULT hr1 = VariantChangeType( &temp1, m_pValue, 0, VT_R8 );
   HRESULT hr2 = VariantChangeType( &temp2, rightChild.m_pValue, 0, VT_R8 );

   //If we succeeded, perform the operation and place the value in
   //the returnVal ScriptVariant.
   if ((SUCCEEDED(hr1)) && (SUCCEEDED(hr2)))
   {
      returnVal.m_pValue->vt = VT_R8;
      returnVal.m_pValue->dblVal = temp1.dblVal + temp2.dblVal;
   }

   //send back returnVal whether or not we succeeded.  If we failed, then
   //returnVal's VT_EMPTY type will signify it nicely.
   return returnVal;
}

ScriptVariant ScriptVariant::operator-( ScriptVariant rightChild )
{
   //Create some temporaries.
   VARIANT temp1;
   VariantInit( &temp1 );

   VARIANT temp2;
   VariantInit(&temp2);

   ScriptVariant returnVal;

   //Attempt to convert the comparison values to doubles
   HRESULT hr1 = VariantChangeType( &temp1, m_pValue, 0, VT_R8 );
   HRESULT hr2 = VariantChangeType( &temp2, rightChild.m_pValue, 0, VT_R8 );

   //If we succeeded, perform the operation and place the value in
   //the returnVal ScriptVariant.
   if ((SUCCEEDED(hr1)) && (SUCCEEDED(hr2)))
   {
      returnVal.m_pValue->vt = VT_R8;
      returnVal.m_pValue->dblVal = temp1.dblVal - temp2.dblVal;
   }

   //send back returnVal whether or not we succeeded.  If we failed, then
   //returnVal's VT_EMPTY type will signify it nicely.
   return returnVal;
}

ScriptVariant ScriptVariant::operator*( ScriptVariant rightChild )
{
   //Create some temporaries.
   VARIANT temp1;
   VariantInit( &temp1 );

   VARIANT temp2;
   VariantInit(&temp2);

   ScriptVariant returnVal;

   //Attempt to convert the comparison values to doubles
   HRESULT hr1 = VariantChangeType( &temp1, m_pValue, 0, VT_R8 );
   HRESULT hr2 = VariantChangeType( &temp2, rightChild.m_pValue, 0, VT_R8 );

   //If we succeeded, perform the operation and place the value in
   //the returnVal ScriptVariant.
   if ((SUCCEEDED(hr1)) && (SUCCEEDED(hr2)))
   {
      returnVal.m_pValue->vt = VT_R8;
      returnVal.m_pValue->dblVal = temp1.dblVal * temp2.dblVal;
   }

   //send back returnVal whether or not we succeeded.  If we failed, then
   //returnVal's VT_EMPTY type will signify it nicely.
   return returnVal;
}

ScriptVariant ScriptVariant::operator/( ScriptVariant rightChild )
{
   //Create some temporaries.
   VARIANT temp1;
   VariantInit( &temp1 );

   VARIANT temp2;
   VariantInit(&temp2);

   ScriptVariant returnVal;

   //Attempt to convert the comparison values to doubles
   HRESULT hr1 = VariantChangeType( &temp1, m_pValue, 0, VT_R8 );
   HRESULT hr2 = VariantChangeType( &temp2, rightChild.m_pValue, 0, VT_R8 );

   //If we succeeded, perform the operation and place the value in
   //the returnVal ScriptVariant.
   if ((SUCCEEDED(hr1)) && (SUCCEEDED(hr2)))
   {
      returnVal.m_pValue->vt = VT_R8;
      returnVal.m_pValue->dblVal = temp1.dblVal / temp2.dblVal;
   }

   //send back returnVal whether or not we succeeded.  If we failed, then
   //returnVal's VT_EMPTY type will signify it nicely.
   return returnVal;
}

//Unary Operations
ScriptVariant ScriptVariant::operator++( )
{
   //Attempt to convert the comparison values to doubles
   HRESULT hr1 = VariantChangeType( m_pValue, m_pValue, 0, VT_R8 );

   //If we succeeded, perform the operation and place the value in
   //the returnVal ScriptVariant.
   if (SUCCEEDED(hr1))
   {
      m_pValue->dblVal++;
   }

   //Send back this ScriptVariant
   return *this;
}

ScriptVariant ScriptVariant::operator++( int x )
{
   //Attempt to convert the comparison values to doubles
   HRESULT hr1 = VariantChangeType( m_pValue, m_pValue, 0, VT_R8 );

   //If we succeeded, perform the operation and place the value in
   //the returnVal ScriptVariant.
   if (SUCCEEDED(hr1))
   {
      m_pValue->dblVal++;
   }

   //Send back this ScriptVariant
   return *this;
}

ScriptVariant ScriptVariant::operator--( )
{
   //Attempt to convert the comparison values to doubles
   HRESULT hr1 = VariantChangeType( m_pValue, m_pValue, 0, VT_R8 );

   //If we succeeded, perform the operation and place the value in
   //the returnVal ScriptVariant.
   if (SUCCEEDED(hr1))
   {
      m_pValue->dblVal--;
   }

   //Send back this ScriptVariant
   return *this;
}

ScriptVariant ScriptVariant::operator--( int x )
{
   //Attempt to convert the comparison values to doubles
   HRESULT hr1 = VariantChangeType( m_pValue, m_pValue, 0, VT_R8 );

   //If we succeeded, perform the operation and place the value in
   //the returnVal ScriptVariant.
   if (SUCCEEDED(hr1))
   {
      m_pValue->dblVal--;
   }

   //Send back this ScriptVariant
   return *this;
}

ScriptVariant ScriptVariant::operator+( )
{
   //Create some temporaries.
   VARIANT temp1;
   VariantInit( &temp1 );

   ScriptVariant returnVal;

   //Attempt to convert the comparison values to doubles
   HRESULT hr1 = VariantChangeType( &temp1, m_pValue, 0, VT_R8 );

   //If we succeeded, perform the operation and place the value in
   //the returnVal ScriptVariant.
   if (SUCCEEDED(hr1))
   {
      returnVal.m_pValue->vt = VT_R8;
      returnVal.m_pValue->dblVal = +(temp1.dblVal);
   }

   //send back returnVal whether or not we succeeded.  If we failed, then
   //returnVal's VT_EMPTY type will signify it nicely.
   return returnVal;
}

ScriptVariant ScriptVariant::operator-( )
{
   //Create some temporaries.
   VARIANT temp1;
   VariantInit( &temp1 );

   ScriptVariant returnVal;

   //Attempt to convert the comparison values to doubles
   HRESULT hr1 = VariantChangeType( &temp1, m_pValue, 0, VT_R8 );

   //If we succeeded, perform the operation and place the value in
   //the returnVal ScriptVariant.
   if (SUCCEEDED(hr1))
   {
      returnVal.m_pValue->vt = VT_R8;
      returnVal.m_pValue->dblVal = -(temp1.dblVal);
   }

   //send back returnVal whether or not we succeeded.  If we failed, then
   //returnVal's VT_EMPTY type will signify it nicely.
   return returnVal;
}

ScriptVariant ScriptVariant::operator!( )
{
   //Create some temporaries.
   VARIANT temp1;
   VariantInit( &temp1 );

   ScriptVariant returnVal;

   //Attempt to convert the comparison values to doubles
   HRESULT hr1 = VariantChangeType( &temp1, m_pValue, 0, VT_R8 );

   //If we succeeded, perform the operation and place the value in
   //the returnVal ScriptVariant.
   if (SUCCEEDED(hr1))
   {
      returnVal.m_pValue->vt = VT_R8;
      returnVal.m_pValue->dblVal = !(temp1.dblVal);
   }

   //send back returnVal whether or not we succeeded.  If we failed, then
   //returnVal's VT_EMPTY type will signify it nicely.
   return returnVal;
}

