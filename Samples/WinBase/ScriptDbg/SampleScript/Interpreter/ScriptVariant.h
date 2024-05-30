/******************************************************************************
* 
*  File: ScriptVariant.h
*
*  Author:  Joel Alley
*
*  Date: September 4, 1998
*
*  Description:   This file contains the delcaration of a wrapper class for 
*                 VARIANT's.  It's primary purpose is to overload the basic
*                 operators, initializers and destructors to make VARIANT's
*                 a little easier to deal with in the script engine.
*
*  Modifications:
******************************************************************************/

class ScriptVariant
{
protected:
   VARIANT* m_pValue;
   BOOL m_isExternal;
   BOOL m_deleteVariant;
   
public:
   //Constructors
   ScriptVariant( BOOL deleteVariant = true );
   ScriptVariant( const ScriptVariant& source );
   ScriptVariant( VARIANT* pVariant, BOOL deleteVariant = true );
   ScriptVariant( LPCOLESTR pStr, BOOL deleteVariant = true );
   ScriptVariant( long lVal, BOOL deleteVariant = true );
   ScriptVariant( double dbVal, BOOL deleteVariant = true );
   ScriptVariant( IDispatch* pDispatch, BOOL deleteVariant = true );
   
   //Destructor
   virtual ~ScriptVariant();
   
   //Accessors
   VARTYPE Type() {return m_pValue->vt;}
   VARIANT* Variant()
   {
      return m_pValue;
   }
   BOOL isTrue();
   BOOL isExternal();
   void isExternal( BOOL value );
   LPCOLESTR toString( );

   //Assignment Operations
   ScriptVariant operator=( ScriptVariant rightChild );
   ScriptVariant operator*=( ScriptVariant rightChild );
   ScriptVariant operator/=( ScriptVariant rightChild );
   ScriptVariant operator+=( ScriptVariant rightChild );
   ScriptVariant operator-=( ScriptVariant rightChild );
   
   //Logical Operations
   ScriptVariant operator||( ScriptVariant rightChild );
   ScriptVariant operator&&( ScriptVariant rightChild );
   ScriptVariant operator==( ScriptVariant rightChild );
   ScriptVariant operator!=( ScriptVariant rightChild );
   ScriptVariant operator>=( ScriptVariant rightChild );
   ScriptVariant operator<=( ScriptVariant rightChild );
   ScriptVariant operator<( ScriptVariant rightChild );
   ScriptVariant operator>( ScriptVariant rightChild );
   
   //Binary Operations
   ScriptVariant operator+( ScriptVariant rightChild );
   ScriptVariant operator-( ScriptVariant rightChild );
   ScriptVariant operator*( ScriptVariant rightChild );
   ScriptVariant operator/( ScriptVariant rightChild );
   
   //Unary Operations
   ScriptVariant operator++( );
   ScriptVariant operator++( int x );
   ScriptVariant operator--( );
   ScriptVariant operator--( int x );
   ScriptVariant operator+( );
   ScriptVariant operator-( );
   ScriptVariant operator!( );
};