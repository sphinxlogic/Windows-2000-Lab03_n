Attribute VB_Name = "Globals"
'*******************************************************************************
'* MODULE:  Globals
'*    Contains globals used by the project.
'*
'* VERSIONS:
'*    1.00  9/9/97   Matthew Carroll
'*
'* Copyright © 1997 Microsoft Corp.  All rights reserved.
'*******************************************************************************
Option Explicit
Option Compare Text

'* Expression tokens
Public Const g_sQuote = """"
Public Const g_sOpenBracket = "["
Public Const g_sCloseBracket = "]"
Public Const g_sOpenParen = "("
Public Const g_sCloseParen = ")"
Public Const g_sOpenBrace = "{"
Public Const g_sCloseBrace = "}"
Public Const g_sListDelimiter = ","
Public Const g_sPaddedListDelimiter = g_sListDelimiter & " "
Public Const g_sPathDelimiter = "."
Public Const g_sEquals = "="
Public Const g_sTuplePrefix = g_sOpenParen
Public Const g_sTupleSuffix = g_sCloseParen
Public Const g_sSetPrefix = g_sOpenBrace
Public Const g_sSetSuffix = g_sCloseBrace
Public Const g_sParameterPrefix = g_sOpenParen
Public Const g_sParameterSuffix = g_sCloseParen
Public Const g_sStartDelimiter = g_sOpenBracket
Public Const g_sEndDelimiter = g_sCloseBracket


'* Expression token lengths
Public Const g_iQuoteLen = 1
Public Const g_iOpenBracketLen = 1
Public Const g_iCloseBracketLen = 1
Public Const g_iOpenParenLen = 1
Public Const g_iCloseParenLen = 1
Public Const g_iOpenBraceLen = 1
Public Const g_iCloseBraceLen = 1
Public Const g_iTuplePrefixLen = g_iOpenParenLen
Public Const g_iTupleSuffixLen = g_iCloseParenLen
Public Const g_iSetPrefixLen = g_iOpenBraceLen
Public Const g_iSetSuffixLen = g_iCloseBraceLen
Public Const g_iParameterPrefixLen = 1
Public Const g_iParameterSuffixLen = 1
Public Const g_iStartDelimiterLen = 1
Public Const g_iEndDelimiterLen = 1

'* Connection String constants
Public Const g_sCnStrValuePrefix = "="
Public Const g_sCnStrValueSuffix = ";"
'Public Const g_sCnStrDataSource = "Data Source"
Public Const g_sCnStrDataSource = "Location"
Public Const g_sCnStrUserID = "User ID"
Public Const g_sCnStrPassword = "Password"
Public Const g_sCnStrProvider = "Provider"
Public Const g_sCnStrDataSourceDefault = "LocalHost"
Public Const g_sCnStrProviderDefault = "MSOLAP"

'* MDX Keywords
Public Const g_sMDXQuote = "'"
Public Const g_sMDXSelect = "SELECT"
Public Const g_sMDXNonEmpty = "NON EMPTY"
Public Const g_sMDXOn = "ON"
Public Const g_sMDXAxis = "AXIS"
Public Const g_sMDXFrom = "FROM"
Public Const g_sMDXWhere = "WHERE"
Public Const g_sMDXDefine = "DEFINE"
Public Const g_sMDXMember = "MEMBER"
Public Const g_sMDXSet = "SET"
Public Const g_sMDXAs = "AS"
Public Const g_sMDXExpression = "EXPRESSION"
Public Const g_sMDXFormat = "FORMAT"

'* MDX Keyword lengths
Public Const g_iMDXSelectLen = 6
Public Const g_iMDXNonEmptyLen = 9
Public Const g_iMDXOnLen = 2
Public Const g_iMDXAxisLen = 4
Public Const g_iMDXFromLen = 4
Public Const g_iMDXWhereLen = 5
Public Const g_iMDXWithLen = 4
Public Const g_iMDXNestLen = 4

'* Predefined Axes
Public Const g_sAxisColumns = "COLUMNS"
Public Const g_sAxisRows = "ROWS"
Public Const g_sAxisPages = "PAGES"
Public Const g_sAxisSections = "SECTIONS"
Public Const g_sAxisChapters = "CHAPTERS"
Public Const g_iAxisColumns = 0
Public Const g_iAxisRows = 1
Public Const g_iAxisPages = 2
Public Const g_iAxisSections = 3
Public Const g_iAxisChapters = 4

'* MDX Member Functions
Public Const g_sMbFnParent = "Parent"
Public Const g_sMbFnFirstChild = "FirstChild"
Public Const g_sMbFnLastChild = "LastChild"
Public Const g_sMbFnPrevMember = "PrevMember"
Public Const g_sMbFnNextMember = "NextMember"
Public Const g_sMbFnLead = "Lead"
Public Const g_sMbFnLag = "Lag"
Public Const g_sMbFnCurrentMember = "CurrentMember"
Public Const g_sMbFnFirstSibling = "FirstSibling"
Public Const g_sMbFnLastSibling = "LastSibling"
Public Const g_sMbFnAncestor = "Ancestor"

'* MDX Set Functions
Public Const g_sSetFnMembers = "Members"
Public Const g_sSetFnChildren = "Children"
Public Const g_sSetFnDescendants = "Descendants"
Public Const g_sSetFnOrder = "Order"
Public Const g_sSetFnHierarchize = "Hierarchize"
Public Const g_sSetFnTopCount = "TopCount"
Public Const g_sSetFnBottomCount = "BottomCount"
Public Const g_sSetFnTopPercent = "TopPercent"
Public Const g_sSetFnBottomPercent = "BottomPercent"
Public Const g_sSetFnTopSum = "TopSum"
Public Const g_sSetFnBottomSum = "BottomSum"
Public Const g_sSetFnFilter = "Filter"
Public Const g_sSetFnUnion = "Union"
Public Const g_sSetFnUnique = "Unique"
Public Const g_sSetFnIntersect = "Intersect"
Public Const g_sSetFnExcept = "Except"
Public Const g_sSetFnNest = "Nest"
Public Const g_sSetFnExtract = "Extract"
Public Const g_sSetFnGenerate = "Generate"

'* MDX Tuple Functions
Public Const g_sTpFnCurrent = "Current"

'* MDX Numeric Functions
Public Const g_sNmFnSum = "Sum"
Public Const g_sNmFnCount = "Count"
Public Const g_sNmFnAvg = "Avg"
Public Const g_sNmFnMin = "Min"
Public Const g_sNmFnMax = "Max"
Public Const g_sNmFnVariance = "Var"
Public Const g_sNmFnStdDev = "StdDev"
Public Const g_sNmFnRank = "Rank"

'* Syntax Example Tags
Public Const g_sTagStart = "«"
Public Const g_sTagEnd = "»"
Public Const g_sTagIdentifier = g_sTagStart & "Identifier" & g_sTagEnd
Public Const g_sTagMember = g_sTagStart & "Member" & g_sTagEnd
Public Const g_sTagSet = g_sTagStart & "Set" & g_sTagEnd
Public Const g_sTagTuple = g_sTagStart & "Tuple" & g_sTagEnd
Public Const g_sTagCube = g_sTagStart & "Cube" & g_sTagEnd
Public Const g_sTagDimension = g_sTagStart & "Dimension" & g_sTagEnd
Public Const g_sTagDimHeirLev = g_sTagStart & "Dim/Hier/Level" & g_sTagEnd
Public Const g_sTagLevel = g_sTagStart & "Level" & g_sTagEnd
Public Const g_sTagIndex = g_sTagStart & "Index" & g_sTagEnd
Public Const g_sTagValue = g_sTagStart & "Value" & g_sTagEnd
Public Const g_sTagPath = g_sTagStart & "Path" & g_sTagEnd
Public Const g_sTagPercentage = g_sTagStart & "Percentage" & g_sTagEnd
Public Const g_sTagStringExpression = _
                  g_sTagStart & "String Expression" & g_sTagEnd
Public Const g_sTagNumericExpression = _
                  g_sTagStart & "Numeric Expression" & g_sTagEnd
Public Const g_sTagBooleanExpression = _
                  g_sTagStart & "Boolean Expression" & g_sTagEnd
Public Const g_sTagStringOrNumericExpression = _
                  g_sTagStart & "String/Numeric Expression" & g_sTagEnd

'* Member Functions Examples
Public Const g_sMbFnTplParent = g_sTagMember & g_sPathDelimiter & g_sMbFnParent
Public Const g_sMbFnTplFirstChild = _
                  g_sTagMember & g_sPathDelimiter & g_sMbFnFirstChild
Public Const g_sMbFnTplLastChild = _
                  g_sTagMember & g_sPathDelimiter & g_sMbFnLastChild
Public Const g_sMbFnTplPrevMember = _
                  g_sTagMember & g_sPathDelimiter & g_sMbFnPrevMember
Public Const g_sMbFnTplNextMember = _
                  g_sTagMember & g_sPathDelimiter & g_sMbFnNextMember
Public Const g_sMbFnTplLead = _
                  g_sMbFnLead & g_sParameterPrefix & g_sTagMember & _
                  g_sPaddedListDelimiter & g_sTagSet & _
                  g_sPaddedListDelimiter & g_sTagIndex & g_sParameterSuffix
Public Const g_sMbFnTplLag = _
                  g_sMbFnLag & g_sParameterPrefix & g_sTagMember & _
                  g_sPaddedListDelimiter & g_sTagSet & _
                  g_sPaddedListDelimiter & g_sTagIndex & g_sParameterSuffix
Public Const g_sMbFnTplCurrentMember = _
                  g_sTagDimension & g_sPathDelimiter & g_sMbFnCurrentMember
Public Const g_sMbFnTplFirstSibling = _
                  g_sTagMember & g_sPathDelimiter & g_sMbFnFirstSibling
Public Const g_sMbFnTplLastSibling = _
                  g_sTagMember & g_sPathDelimiter & g_sMbFnLastSibling
Public Const g_sMbFnTplAncestor = _
                  g_sMbFnAncestor & g_sParameterPrefix & g_sTagMember & _
                  g_sPaddedListDelimiter & g_sTagLevel & g_sParameterSuffix

'* Set Function Examples
Public Const g_sSetFnTplMembers = _
                  g_sTagDimHeirLev & g_sPathDelimiter & g_sSetFnMembers
Public Const g_sSetFnTplChildren = _
                  g_sTagMember & g_sPathDelimiter & g_sSetFnChildren
Public Const g_sSetFnTplDescendants = _
                  g_sSetFnDescendants & g_sParameterPrefix & g_sTagMember & _
                  g_sPaddedListDelimiter & g_sTagLevel & g_sParameterSuffix
Public Const g_sSetFnTplOrder = _
                  g_sSetFnOrder & g_sParameterPrefix & g_sTagSet & _
                  g_sPaddedListDelimiter & g_sTagStringOrNumericExpression & _
                  g_sParameterSuffix
Public Const g_sSetFnTplHierarchize = _
                  g_sSetFnHierarchize & g_sParameterPrefix & g_sTagSet & _
                  g_sParameterSuffix
Public Const g_sSetFnTplTopCount = _
                  g_sSetFnTopCount & g_sParameterPrefix & g_sTagSet & _
                  g_sPaddedListDelimiter & g_sTagIndex & _
                  g_sPaddedListDelimiter & g_sTagNumericExpression & _
                  g_sParameterSuffix
Public Const g_sSetFnTplBottomCount = _
                  g_sSetFnBottomCount & g_sParameterPrefix & g_sTagSet & _
                  g_sPaddedListDelimiter & g_sTagIndex & _
                  g_sPaddedListDelimiter & g_sTagNumericExpression & _
                  g_sParameterSuffix
Public Const g_sSetFnTplTopPercent = _
                  g_sSetFnTopPercent & g_sParameterPrefix & g_sTagSet & _
                  g_sPaddedListDelimiter & g_sTagPercentage & _
                  g_sPaddedListDelimiter & g_sTagNumericExpression & _
                  g_sParameterSuffix
Public Const g_sSetFnTplBottomPercent = _
                  g_sSetFnBottomPercent & g_sParameterPrefix & g_sTagSet & _
                  g_sPaddedListDelimiter & g_sTagPercentage & _
                  g_sPaddedListDelimiter & g_sTagNumericExpression & _
                  g_sParameterSuffix
Public Const g_sSetFnTplTopSum = _
                  g_sSetFnTopSum & g_sParameterPrefix & g_sTagSet & _
                  g_sPaddedListDelimiter & g_sTagValue & _
                  g_sPaddedListDelimiter & g_sTagNumericExpression & _
                  g_sParameterSuffix
Public Const g_sSetFnTplBottomSum = _
                  g_sSetFnBottomSum & g_sParameterPrefix & g_sTagSet & _
                  g_sPaddedListDelimiter & g_sTagValue & _
                  g_sPaddedListDelimiter & g_sTagNumericExpression & _
                  g_sParameterSuffix
Public Const g_sSetFnTplFilter = _
                  g_sSetFnFilter & g_sParameterPrefix & g_sTagSet & _
                  g_sPaddedListDelimiter & g_sTagBooleanExpression & _
                  g_sParameterSuffix
Public Const g_sSetFnTplUnion = _
                  g_sSetFnUnion & g_sParameterPrefix & g_sTagSet & _
                  g_sPaddedListDelimiter & g_sTagSet & g_sParameterSuffix
Public Const g_sSetFnTplUnique = _
                  g_sSetFnUnique & g_sParameterPrefix & g_sTagSet & _
                  g_sParameterSuffix
Public Const g_sSetFnTplIntersect = _
                  g_sSetFnIntersect & g_sParameterPrefix & g_sTagSet & _
                  g_sPaddedListDelimiter & g_sTagSet & g_sParameterSuffix
Public Const g_sSetFnTplExcept = _
                  g_sSetFnExcept & g_sParameterPrefix & g_sTagSet & _
                  g_sPaddedListDelimiter & g_sTagSet & g_sParameterSuffix
Public Const g_sSetFnTplNest = _
                  g_sSetFnNest & g_sParameterPrefix & g_sTagSet & _
                  g_sPaddedListDelimiter & g_sTagSet & g_sParameterSuffix
Public Const g_sSetFnTplExtract = _
                  g_sSetFnExtract & g_sParameterPrefix & g_sTagSet & _
                  g_sPaddedListDelimiter & g_sTagDimension & g_sParameterSuffix
Public Const g_sSetFnTplGenerate = _
                  g_sSetFnGenerate & g_sParameterPrefix & g_sTagSet & _
                  g_sPaddedListDelimiter & g_sTagSet & g_sParameterSuffix

'* Tuple Function Examples
Public Const g_sTpFnTplCurrent = _
                  g_sTagSet & g_sPathDelimiter & g_sTpFnCurrent

'* Numeric Function Examples
Public Const g_sNmFnTplSum = _
                  g_sNmFnSum & g_sParameterPrefix & g_sTagSet & _
                  g_sPaddedListDelimiter & g_sTagNumericExpression & _
                  g_sParameterSuffix
Public Const g_sNmFnTplCount = _
                  g_sNmFnCount & g_sParameterPrefix & g_sTagSet & _
                  g_sParameterSuffix
Public Const g_sNmFnTplAvg = _
                  g_sNmFnAvg & g_sParameterPrefix & g_sTagSet & _
                  g_sPaddedListDelimiter & g_sTagNumericExpression & _
                  g_sParameterSuffix
Public Const g_sNmFnTplMin = _
                  g_sNmFnMin & g_sParameterPrefix & g_sTagSet & _
                  g_sPaddedListDelimiter & g_sTagNumericExpression & _
                  g_sParameterSuffix
Public Const g_sNmFnTplMax = _
                  g_sNmFnMax & g_sParameterPrefix & g_sTagSet & _
                  g_sPaddedListDelimiter & g_sTagNumericExpression & _
                  g_sParameterSuffix
Public Const g_sNmFnTplVariance = _
                  g_sNmFnVariance & g_sParameterPrefix & g_sTagSet & _
                  g_sPaddedListDelimiter & g_sTagNumericExpression & _
                  g_sParameterSuffix
Public Const g_sNmFnTplStdDev = _
                  g_sNmFnStdDev & g_sParameterPrefix & g_sTagSet & _
                  g_sPaddedListDelimiter & g_sTagNumericExpression & _
                  g_sParameterSuffix
Public Const g_sNmFnTplRank = _
                  g_sNmFnRank & g_sParameterPrefix & g_sTagTuple & _
                  g_sPaddedListDelimiter & g_sTagSet & _
                  g_sParameterSuffix

'* MDX Query Examples
Private Const sIndent = "   "
Private Const sSpace = " "
Public Const g_sMDXTplQuery = _
                  g_sMDXSelect & vbCrLf & _
                  sIndent & g_sTagSet & sSpace & g_sMDXOn & sSpace & _
                  g_sAxisColumns & g_sListDelimiter & vbCrLf & _
                  sIndent & g_sTagSet & sSpace & g_sMDXOn & sSpace & _
                  g_sAxisRows & vbCrLf & _
                  g_sMDXFrom & sSpace & g_sTagCube & vbCrLf & _
                  g_sMDXWhere & sSpace & g_sTagTuple
Public Const g_sMDXTplQueryWMemberDef = _
                  g_sMDXTplQuery & vbCrLf & _
                  g_sMDXDefine & sSpace & g_sMDXMember & sSpace & _
                  g_sTagPath & g_sPathDelimiter & g_sTagIdentifier & _
                  sSpace & g_sMDXAs & vbCrLf & _
                  sIndent & g_sMDXExpression & sSpace & g_sEquals & sSpace & _
                  g_sMDXQuote & g_sTagNumericExpression & g_sMDXQuote & _
                  vbCrLf & sIndent & g_sMDXFormat & sSpace & g_sEquals & _
                  sSpace & g_sMDXQuote & g_sTagStringExpression & g_sMDXQuote
Public Const g_sMDXTplQueryWSetDef = _
                  g_sMDXTplQuery & vbCrLf & _
                  g_sMDXDefine & sSpace & g_sMDXSet & sSpace & _
                  g_sTagSet & sSpace & g_sMDXAs & sSpace & g_sTagIdentifier

