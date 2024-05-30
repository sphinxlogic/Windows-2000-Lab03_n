<%@ LANGUAGE = JScript %>
<%
  // Parse error formatting function
  function reportParseError(error)
  {
    var s = "";
    for (var i=1; i<error.linepos; i++) {
      s += " ";
    }
    r = "<font face=Verdana size=2><font size=4>XML Error loading '" + 
        error.url + "'</font>" +
        "<P><B>" + error.reason + 
        "</B></P></font>";
    if (error.line > 0)
      r += "<font size=3><XMP>" +
      "at line " + error.line + ", character " + error.linepos +
      "\n" + error.srcText +
      "\n" + s + "^" +
      "</XMP></font>";
    return r;
  }

  // Runtime error formatting function
  function reportRuntimeError(exception)
  {
    return "<font face=Verdana size=2><font size=4>XSL Runtime Error</font>" +
        "<P><B>" + exception.description + "</B></P></font>";
  }

  // Set the source and stylesheet locations here
  var sourceFile = Server.MapPath("simple.xml");
  var styleFile = Server.MapPath("simple.xsl");
  
  // Load the XML 
  var source = Server.CreateObject("Microsoft.XMLDOM");
  source.async = false;
  source.load(sourceFile);

  // Load the XSL
  var style = Server.CreateObject("Microsoft.XMLDOM");
  style.async = false;
  style.load(styleFile);

  if (source.parseError.errorCode != 0)
    result = reportParseError(source.parseError);
  else
  {
    if (style.parseError.errorCode != 0)
      result = reportParseError(style.parseError);
    else
    {
      try {
        result = source.transformNode(style);
      }
      catch (exception) {
        result = reportRuntimeError(exception);
      }
    }
  }

  Response.Write(result);
%>
