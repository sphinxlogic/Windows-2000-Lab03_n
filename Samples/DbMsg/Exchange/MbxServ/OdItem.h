//--oditem.h------------------------------------------------------------------
//
// interface of the COwnerDrawItem class
//
// Copyright (C) Microsoft Corp. 1986-1996.  All Rights Reserved.
//----------------------------------------------------------------------------

#define ODI_DELOBJECT   0x10    // delete data object associated with the ODI when ODI deleted
#define ODI_GOTDATA     0x20    // have data object filled in   
#define ODI_DISABLED    0x40    // disabled item (greyed out) 
#define ODI_BOLDTEXT    0x100   // draw bold text

class COwnerDrawItem : public CObject
{
public:
    COwnerDrawItem ();
    virtual ~COwnerDrawItem ();
    void Create (CObject* pObject, const char *szDescription, DWORD dwFlags = 0);

    COwnerDrawItem& operator= (const COwnerDrawItem &rhs);
    
    // Data members
    CString         m_strDescription;
    CObject        *m_pObject;          // User data
    DWORD           m_dwFlags;          // ODI_???
    COLORREF        m_crText;           // TextColor
    COLORREF        m_crBkText;         // Background Color
        
#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif

protected:
    DECLARE_DYNAMIC(COwnerDrawItem)
};

