VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
END
Attribute VB_Name = "AEditorClass"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Attribute VB_Description = "Agent Editor - Properties common to the project."
Attribute VB_Ext_KEY = "SavedWithClassBuilder" ,"Yes"
Attribute VB_Ext_KEY = "Top_Level" ,"Yes"
Option Explicit

'***********************************************************************
'  Copyright (c) by Microsoft 1998
'***********************************************************************
'
'                 AGENT EDITOR CLASS
'
'   Overview: A generic class that acts as a common holder for properties
'   used throughout the program. This class is not needed in your own
'   project if you use the Agentmap.cls and cdohandler.cls
'-------------------------------------------------------

Private msFolderID As String            'Folder Entry ID
Private msScriptPathName As String      'Script Path Name
Private msScriptInitDir As String       'Script initial search directory
Private msMapPathName As String         'Map Path Name
Private msMapInitDir As String          'Map Init Search Directory
Private msAgentName As String           'Name of Agent
Private msAgentClassID As String        'Agent Class ID
Private mbCancelled As Boolean          'Generic UI Cancel indicator
Private miEditMode As Integer           'Edit Mode constant
Private miDirty As Integer              'Dirty Indicator
Private mlCol As Long                   'Current Grid Col
Private mlRow As Long                   'Current Grid Row
Private miAgentMode As Integer          'Agent Type (scripthandler or routing)
Private msCellData As String            'Grid Cell Cut/copy/paste string
Private mbNewAgent As Boolean           'New Agent can read in binding map
Private mbRouteAgentExists As Boolean   'Routing Agent already exists
Private msBindingEID                    'Binding Entry ID

'BindingEID
Public Property Let BindingEID(ByVal sPN As String)
  msBindingEID = sPN
End Property

'BindingEID
Public Property Get BindingEID() As String
  BindingEID = msBindingEID
End Property

'Set to true if a Routing Agent exists in a folder
Public Property Let RouteAgentExists(ByVal vData As Boolean)
    mbRouteAgentExists = vData
End Property

'Returns true if a Routing Agent exists in a folder
Public Property Get RouteAgentExists() As Boolean
    RouteAgentExists = mbRouteAgentExists
End Property

'Data used for cell copy paste.
Public Property Let CellData(ByVal vData As String)
    msCellData = vData
End Property

'Data used for cell copy paste.
Public Property Get CellData() As String
    CellData = msCellData
End Property

'ClassID of the agent
Public Property Let AgentClassID(ByVal sPN As String)
  msAgentClassID = sPN
End Property

'ClassId of the agent
Public Property Get AgentClassID() As String
  AgentClassID = msAgentClassID
End Property

'Agent Name (Binding Name)
Public Property Let AgentName(ByVal sPN As String)
  msAgentName = sPN
End Property

'Agent Name (Binding Name)
Public Property Get AgentName() As String
  AgentName = msAgentName
End Property

'Agent Mode (Scripthanlder or Routing)
Public Property Let AgentMode(ByVal iData As Integer)
    miAgentMode = iData
End Property

'Agent Mode (Scripthanlder or Routing)
Public Property Get AgentMode() As Integer
    AgentMode = miAgentMode
End Property

'The initial directory for the script search file dialog
Public Property Let ScriptInitDir(ByVal sPN As String)
  msScriptInitDir = sPN
End Property

'The initial directory for the script search file dialog
Public Property Get ScriptInitDir() As String
  ScriptInitDir = msScriptInitDir
End Property

'The initial directory for the script search file dialog
Public Property Let MapInitDir(ByVal sPN As String)
  msMapInitDir = sPN
End Property

'The initial directory for the script search file dialog
Public Property Get MapInitDir() As String
  MapInitDir = msMapInitDir
End Property

'The path and name of the script
Public Property Let MapPathName(ByVal sPN As String)
  msMapPathName = sPN
End Property

'The path and name of the script
Public Property Get MapPathName() As String
  ScriptPathName = msMapPathName
End Property

'The path and name of the script
Public Property Let ScriptPathName(ByVal sPN As String)
  msScriptPathName = sPN
End Property

'The path and name of the script
Public Property Get ScriptPathName() As String
  ScriptPathName = msScriptPathName
End Property

'Dirty flag for script
Public Property Let Dirty(ByVal iData As Integer)
    miDirty = iData
End Property

'Dirty flag for script
Public Property Get Dirty() As Integer
    Dirty = miDirty
End Property

'Edit Mode
Public Property Let EditMode(ByVal iData As Integer)
    miEditMode = iData
End Property

'Edit Mode
Public Property Get EditMode() As Integer
    EditMode = miEditMode
End Property

'Cancelled property used with dialog boxes and form cancels
Public Property Let Cancelled(ByVal bData As Boolean)
    mbCancelled = bData
End Property

'Cancelled property used with dialog boxes and form cancels
Public Property Get Cancelled() As Boolean
    Cancelled = mbCancelled
End Property

'Get Row number for Grid
Public Property Get CurrentRow() As Long
   CurrentRow = mlRow
End Property

'Store Row number for grid
Public Property Let CurrentRow(lRow As Long)
   mlRow = lRow
End Property

'Get Column number for grid
Public Property Get CurrentCol() As Long
   CurrentCol = mlCol
End Property

'Store column number for grid
Public Property Let CurrentCol(lCol As Long)
   mlCol = lCol
End Property
