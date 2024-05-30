Attribute VB_Name = "Module1"
Option Explicit

Function lConvertToJohnnyDate(dtDate As Date)

Dim lReturn As Long
lReturn = 0

lReturn = ((Year(dtDate)) * (2 ^ 9))
lReturn = lReturn Or ((Month(dtDate)) * (2 ^ 5))
lReturn = lReturn Or (Day(dtDate))

lConvertToJohnnyDate = lReturn

End Function
Function lConvertToJohnnyTime(dtTime As Date)

Dim lReturn As Long
lReturn = 0

lReturn = ((Hour(dtTime)) * (2 ^ 12))
lReturn = lReturn Or ((Minute(dtTime)) * (2 ^ 6))
lReturn = lReturn Or (Second(dtTime))

lConvertToJohnnyTime = lReturn

End Function


