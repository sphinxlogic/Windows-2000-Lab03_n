<!--
function OnDSReadyStateChangeEvt (ReadyState)
{
//mpReadyStateUninitialized  0  The FileName property has not been initialized.  
//mpReadyStateLoading        1  The player control is asynchronously loading a file.  
//mpReadyStateInteractive    3  The player control loaded a file, and downloaded enough data to play the file, but has not yet received all data.  
//mpReadyStateComplete       4  All data has been downloaded.  

    if ((ReadyState == 3) || (ReadyState == 4))
        alert("ReadyState: " + ReadyState);

}   /* end OnDSReadyStateChangeEvt() */
//-->
