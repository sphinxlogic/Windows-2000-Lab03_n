/******************************************************************************
*
*  File: TStack.h
*
*  Author:  Joel Alley
*
*  Date: August 7, 1998
*
*  Description:   This file contains the definition of a templatized stack.
*                 Taken from Decker&Hirshfield. "Working Classes", 
*                 International Thomson Publishing, 1996.
*
*  Modifications:
******************************************************************************/
template <class T>
class TStack : public TList<T>{

public:
   //Constructor
   TStack() : TList<T>() {;}
   //Destructor
   ~TStack() {;}

   void Push( T e)
   {
      Reset();
      TList<T>::InsertBefore( e );
   }

   void Pop( )
   {
      Reset();
      Remove();
   }

   T Top() const
   {
      return Retrieve();
   }

   int IsEmpty() const
   {
      return (size == 0);
   }

   void InsertBefore(T e, LPCOLESTR theName = NULL)
   {
      Push( e );
   }
   
   void InsertAfter(T e, LPCOLESTR theName = NULL)
   {
      Push( e );
   } 
};
