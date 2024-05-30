function saveLocations() {

	for (i = 0; i < magnet.length; i++) {
		//store the magnet positions in the DIV element
		sltChooseData.setAttribute("intTopMagnet" + i,magnet[i].style.top);
		sltChooseData.setAttribute("intLeftMagnet" + i,magnet[i].style.left);
	}
	
	sltChooseData.save("oXMLStore");	
}

function loadLocations() {
	var intNumMagnets;
	
	sltChooseData.load("oXMLStore");
	intNumMagnets = magnet.length;

	if (null != sltChooseData.getAttribute("intTopMagnet" + 0)) {
	//make sure stored data exists.
			for (i = 0; i < intNumMagnets; i++) {
				magnet[i].style.top = sltChooseData.getAttribute("intTopMagnet" + i);
				magnet[i].style.left = sltChooseData.getAttribute("intLeftMagnet" + i);
		} 
	}
	
	else {
		resetMagnets();
	}	
	for (i = 0; i < intNumMagnets; i++) {
		magnet[i].style.visibility = "visible";
	}
}

