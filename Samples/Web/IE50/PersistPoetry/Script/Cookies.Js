 //  from Scott Isaac's Inside DHTML
        
 function parseCookie() {
   // Separate each cookie.
   var cookieList = document.cookie.split("; ");
   // Array for each cookie in cookieList
   var cookieArray = new Array();
   for (var i = 0; i < cookieList.length; i++) {
      // Separate name-value pairs.
      var name = cookieList[i].split("=");
      // Decode and add to cookie array.
      cookieArray[unescape(name[0])] = unescape(name[1]);
   }
   return cookieArray;
}  
       
function CookiesaveLocations() {
    
    var expireDate = new Date();
	expireDate.setDate(365 + expireDate.getDate());

	document.cookie = "FileIndex=" + sltChooseData.selectedIndex + ";" + "expires=" + expireDate.toGMTString() + ";";
}

function CookieloadLocations() {

	var intFileIndex;
	var cookieData = parseCookie();

	if ("undefined" == cookieData.FileIndex)
		intFileIndex = 0;
	else
		intFileIndex = cookieData.FileIndex;
	
	strDatasetName = "./xml/words" + intFileIndex + ".xml";
	sltChooseData.selectedIndex = intFileIndex;

}