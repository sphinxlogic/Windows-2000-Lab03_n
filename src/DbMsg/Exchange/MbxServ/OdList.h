//--odlist.h------------------------------------------------------------------
//
// interface of the COwnerDrawListBox class
//
// Copyright (C) Microsoft Corp. 1986-1996.  All Rights Reserved.
//----------------------------------------------------------------------------

// Forward Reference
class COwnerDrawItem;

class COwnerDrawListBox : public CListBox
{
public:
    COwnerDrawListBox();
    virtual ~COwnerDrawListBox();

#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif

    int m_nCurSel;
    // overrides for standard get and set functions to accomodate COwnerDrawItem
    // as a data wi save pODI, which has a pointer to the "real" data
    // all this is transperent to the user
    void*           GetItemDataPtr     (int index);
    DWORD           GetItemData        (int index);
    CObject*        GetItemDataObject  (int index);  
    COwnerDrawItem* GetODI             (int index);      
    int             SetItemDataPtr     (int index, void    *pData);
    int             SetItemData        (int index, DWORD   dwData);
    int             SetItemDataObject  (int index, CObject *pObject);
    int             SetODI             (int index, COwnerDrawItem *pODI);
                                      
    // override for standard Add and Insert functions
    // lpStr is a data obect that is stored as item data pointer
    // Default owner draw item is created for this version
    // if you need to create specific ODI, use the other overload
    int      AddString          (LPCSTR lpStr);
    int      AddODI             (COwnerDrawItem *pODI);
    int      InsertString       (int index, LPCSTR lpStr);
    int      InsertODI          (int index, COwnerDrawItem *pODI);
    
    // override for standard function to prevent selection of disabled item    
    int      SetCurSel          (int index);
    
    // disable or enables item depending on bEnable
    void     EnableString       (int index, BOOL bEnable);
 
protected:
    DECLARE_DYNCREATE(COwnerDrawListBox)
                                 
protected:
// Overridables (must override draw, measure and compare for owner draw)
    virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
    virtual void MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct);
    virtual void DeleteItem(LPDELETEITEMSTRUCT lpDeleteItemStruct);

// Generated message map functions
protected:
    //{{AFX_MSG(COwnerDrawListBox)
    afx_msg UINT OnGetDlgCode();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

// Add inlines
#ifndef _DEBUG
#define _MSX_INLINE inline
#include "odlist.inl"
#endif
