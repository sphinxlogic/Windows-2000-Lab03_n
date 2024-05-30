var curElement = null;
var iMaxIndex = 1000;

function doMouseMove() {
  var newleft=0, newTop = 0;

  if ((event.button==1) && (curElement!=null)) {
        // position element

        newleft = event.x - document.body.offsetLeft - (curElement.offsetWidth / 2) ;
        if (newleft < 0) 
			newleft = 0;

        curElement.style.left = newleft;
        newtop = event.y - document.body.offsetTop - (curElement.offsetHeight / 2);

        if (newtop < 0) 
			newtop = 0;
        curElement.style.top = newtop;
        event.returnValue = false;
        event.cancelBubble = true;
    }
  }

  function doDragStart() {

    // Don't do default drag operation.
    if ("DIV"==event.srcElement.tagName)
      event.returnValue=false;

  }

  function doMouseDown() {

 
    if ((event.button==1) && (event.srcElement.tagName=="DIV")) {
    
		curElement = event.srcElement;
		
		//bring to top of z-index
		if (iMaxIndex < 32000) 
			iMaxIndex++;
		curElement.style.zIndex = iMaxIndex; 
		//warning - this is a poor way to implement this.
		
	}
    else
		curElement = null;
  }

  function doMouseUp() {
 
    curElement = null;
  }

  document.ondragstart = doDragStart;
  document.onmousedown = doMouseDown;
  document.onmousemove = doMouseMove;
  document.onmouseup = doMouseUp;