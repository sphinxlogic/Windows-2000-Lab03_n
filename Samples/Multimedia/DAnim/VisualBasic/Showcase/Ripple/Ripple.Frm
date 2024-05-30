VERSION 5.00
Object = "{34F681D0-3640-11CF-9294-00AA00B8A733}#1.0#0"; "DANIM.DLL"
Begin VB.Form Ripple 
   Caption         =   "Ripple"
   ClientHeight    =   5880
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   5790
   LinkTopic       =   "Form1"
   ScaleHeight     =   5880
   ScaleWidth      =   5790
   StartUpPosition =   3  'Windows Default
   Begin DirectAnimationCtl.DAViewerControlWindowed DAViewerControlWindowed 
      Height          =   5655
      Left            =   120
      OleObjectBlob   =   "Ripple.frx":0000
      TabIndex        =   0
      Top             =   120
      Width           =   5535
   End
End
Attribute VB_Name = "Ripple"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False

  Dim rawimage

Private Sub Form_Load()
  dimn = 0.03  ' in meters
  
  'Set relative paths for the bin\visualbasic directory.
  Dim mediaBase, imgBase As String
  
  'Find out if your are in the bin directory of the SDK,
  'and append the path accordingly.
  strBin = "bin"
  binPos = InStr(1, CurDir, strBin)
  If (binPos > 0) Then
    mediaBase = CurDir + "\..\..\..\Media\"
  Else
    mediaBase = CurDir + "\..\..\..\..\Media\"
  End If
  
  imgBase = mediaBase + "image\"

  'Import the image
  Set rawimage1 = ImportImage(imgBase + "metablob.jpg")
  Set rawimage2 = ImportImage(imgBase + "mndscp2.jpg")
  
  Dim rippler As Object
  Set rippler = CreateObject("DX3DTransform.Microsoft.Ripple")

  ' Construct a number that holds at 0 for three seconds, moves to 1
  ' over three seconds, then comes back to 0 over three seconds, then
  ' repeats.
  Dim extent As Double
  extent = 1#
  
  Set holdTime = DANumber(0).Duration(1)
  Set forward = Interpolate(0, extent, 5)
  Set back = Interpolate(extent, 0, 5)
  Set evaluator = Sequence(holdTime, Sequence(forward, back)).RepeatForever()
  
  Set rippleResult = ApplyDXTransform(rippler, Array(rawimage1, rawimage2), evaluator)

  ' This will run it's course over the canonical 0 to 1 period.
  Set xformedGeo = rippleResult.OutputBvr

  Set xPos = Interpolate(-1, 1, 8).RepeatForever()
  Set yPos = Interpolate(-1, 1, 7).RepeatForever()
  
  Set xformedGeo = xformedGeo.Transform(Scale3Uniform(dimn * 3))

  extent = (3.1415 / 2) * 0.8
  
  Set ang1 = Interpolate(-extent, extent, 15)
  Set ang2 = Interpolate(extent, -extent, 15)
  Set ang = Sequence(ang1, ang2).RepeatForever()
  
  Set xformedGeo = xformedGeo.Transform(Rotate3Anim(YVector3, ang))
  Set xformedGeo = xformedGeo.Transform(Translate3(0, 0, -5 * dimn))

  ' a point light
  Set light = PointLight.Transform(Translate3(dimn / 2, dimn / 4, 1.5 * dimn))

  ' a perspective camera
  Set camera = PerspectiveCamera(2 * dimn, 1.8 * dimn)

  ' render the cube with the light and camera
  Set finalImg = UnionGeometry(xformedGeo, light).Render(camera)

  Set finalImg = finalImg

  DAViewerControlWindowed.Image = Overlay(finalImg, SolidColorImage(White))

  ' start the animation
  DAViewerControlWindowed.Start

End Sub
