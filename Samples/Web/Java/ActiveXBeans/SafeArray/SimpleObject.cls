VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
END
Attribute VB_Name = "SimpleObject"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = True
Public Function ComputeSum(A() As Long)
    Dim l As Long
    Dim i As Integer

    l = 0
    For i = LBound(A) To UBound(A)
        l = l + A(i)
    Next i
    ComputeSum = l
End Function


Public Function CreateSquares()
    Dim A(-4 To 6) As Long
    Dim i As Long
    For i = 0 To 10
        A(i + LBound(A)) = i * i
    Next i
    CreateSquares = A
End Function
