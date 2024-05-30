<!--
function ToggleControls (setting)
{
    document.NSPlay.ShowControls = setting;

}   /* end controlType() */


function displaySize (setting)
{
    document.NSPlay.DisplaySize = setting;

}   /* end displaySize() */


function PlayClick ()
{
    document.NSPlay.Play();

}   /* end PlayClick() */


function StopClick ()
{
    document.NSPlay.Stop();
    document.NSPlay.CurrentPosition = 0;

}   /* end StopClick() */


function PauseClick ()
{
    document.NSPlay.Pause();

}   /* end PauseClick() */


function PlayPauseClick ()
{
    var state;
    
    state = document.NSPlay.PlayState;

    if (state == 0) {
        document.NSPlay.Play();
        document.myform.PlayPause.value = "Pause";
    } else if (state == 1) {
        document.NSPlay.Play();
        document.myform.PlayPause.value = "Pause";
    } else if (state == 2) {
        document.NSPlay.Pause();
        document.myform.PlayPause.value = " Play";
    }

}   /* end PlayPauseClick() */
//-->
