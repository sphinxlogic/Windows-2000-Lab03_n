
_MSX_INLINE void* COwnerDrawListBox::GetItemDataPtr (int index)
{
    ASSERT (index != CB_ERR);
    
    COwnerDrawItem *pODI = GetODI (index);
    
    return pODI->m_pObject;
}

_MSX_INLINE DWORD COwnerDrawListBox::GetItemData (int index)
{
    ASSERT (index != CB_ERR);
    
    COwnerDrawItem *pODI = GetODI (index);
        
    return (DWORD)pODI->m_pObject;
} 

_MSX_INLINE CObject* COwnerDrawListBox::GetItemDataObject (int index)
{
    ASSERT (index != CB_ERR);
    
    COwnerDrawItem *pODI = GetODI (index);
        
    return (CObject*)pODI->m_pObject;
}

_MSX_INLINE COwnerDrawItem* COwnerDrawListBox::GetODI (int index)
{  
    ASSERT ((index != CB_ERR) && (index < GetCount()));
    
    return (COwnerDrawItem*)CListBox::GetItemDataPtr (index);
}

_MSX_INLINE int COwnerDrawListBox::SetItemDataPtr (int index, void *pData)
{
    ASSERT (index != CB_ERR);
    
    COwnerDrawItem *pODI = GetODI (index);
    
    pODI->m_pObject = (CObject*)pData;
    
    return 0;
}

_MSX_INLINE int COwnerDrawListBox::SetItemData (int index, DWORD dwData)
{
    ASSERT (index != CB_ERR);
    
    COwnerDrawItem *pODI = GetODI (index);
    
    pODI->m_pObject = (CObject*) dwData;
    
    return 0;
} 

_MSX_INLINE int COwnerDrawListBox::SetItemDataObject (int index, CObject *pObject)
{
    ASSERT (index != CB_ERR);
    
    COwnerDrawItem *pODI = GetODI (index);
    ASSERT (pODI);                                   
    pODI->m_pObject = pObject;
    
    return 0;
}   

_MSX_INLINE int COwnerDrawListBox::SetODI (int index, COwnerDrawItem *pODI)
{
    ASSERT ((index != CB_ERR) && (index < GetCount()));
    
    return (CListBox::SetItemDataPtr(index, pODI));
}
                                      
_MSX_INLINE int COwnerDrawListBox::AddString (LPCSTR lpStr)
{
    COwnerDrawItem *pODI = new COwnerDrawItem ();
    pODI->Create (NULL, lpStr);
        
    return CListBox::AddString ((LPCSTR)pODI);
} 

_MSX_INLINE int COwnerDrawListBox::AddODI (COwnerDrawItem *pODI)
{                  
    ASSERT (pODI);
    
    return CListBox::AddString ((LPCSTR)pODI);
}

_MSX_INLINE int COwnerDrawListBox::InsertString (int index, LPCSTR lpStr)
{                                          
    ASSERT (index != LB_ERR);
    ASSERT (lpStr);
    COwnerDrawItem *pODI = new COwnerDrawItem ();
    pODI->Create (NULL, lpStr);
        
    return CListBox::InsertString (index, (LPCSTR)pODI);
}

_MSX_INLINE int COwnerDrawListBox::InsertODI (int index, COwnerDrawItem *pODI)
{                                             
    ASSERT (index != LB_ERR);
    ASSERT (pODI);
    
    return CListBox::InsertString (index, (LPCSTR)pODI);
}
