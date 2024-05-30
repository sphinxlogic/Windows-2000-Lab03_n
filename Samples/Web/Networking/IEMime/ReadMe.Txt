IEMime Sample
=============

IEMime demonstrates MIME type registration and MIME type recognition of downloads.

The control starts an asynchronous download, usually by asking its
bind-host to MonikerBindToStorage on its behalf. During the download process, IEMime
is notified of the MIME type on its bind-status-callback. IEMime displays this MIME type.

Main points of interest:

* For purposes of demonstration, IEMime uses a somewhat atypical scheme for
  downloading during initialization. Typically, a control which downloads asynchronous
  data based on a data-path property (URL) would proceed with the download as soon
  as it possibly can. The ReadyState property would then be used to signal to MSHTML as
  the control container that the control was done downloading whatever data it needed
  asynchronously. MSHTML would continue to show progress and UI such as the spinning
  icon until the control signaled READYSTATE_COMPLETE. In most cases, any events
  signaling the download would happen before the page was ready to receive them. In
  the case of IEMime, this would cause the Complete() event to not fire on page-startup.

  Instead, IEMime waits until the container is totally ready to receive events before
  starting its download. That way, script can catch Complete() even for downloads kicked off
  by <PARAM URL=> persistent properties. However, this gets us into a deadlocked
  situation of sorts -- the container is waiting for our control to signal complete
  while we're waiting for the container to go complete. We avoid this problem by
  signaling "COMPLETE" as soon as our properties are loaded and then transitioning back to
  "INTERACTIVE" once we start our asynchronous download. This solution is acceptable --
  it is okay for a control to change ReadyState back to LOADED or INTERACTIVE while it
  is re-downloading a data file or re-evaluating a query, for example. We always go back
  to INTERACTIVE when doing an asynchronous download.

  The traditional means for a control to know when its container is up and running and
  can receive events is to watch IOleControl::FreezeEvents until the freeze count
  transitions from 1 to 0. This is where IEMime kicks off the download by calling Reload().

* IEMime adds to the basic ATL class CBindStatusCallback by adding some extra overrides.
  IEMime's CBindStatusCallback2 passes the FORMATETC and STGMEDIUM on to the using class
  (CIEMimeCtl) during OnData, because these structures are what we are really interested in.
  The original CBindStatusCallback did not provide these to the using class.

  IEMime also calls up to two funcs in the using class, PreBindMoniker & OnBindingFailure.
  The class design here could be improved, as this requires the using class to implement
  these funcs instead of pass in func-pointers such as with OnData. In our case,
  we want to handle both so it isn't a big deal.

* PreBindMoniker is intended to allow the using class to talk to the IBindCtx and IMoniker
  interfaces before the upcoming bind process. In our case, we use it to demonstrate
  the use of the RegisterMediaType, CreateFormatEnumerator, and RegisterFormatEnumerator APIs.
  If the "Media" property has been set on the control, then IEMime uses this custom
  string to Register a new Media Type. This nets a Clipboard format for that media type. Then,
  IEMime creates a format enumerator that enumerates ONLY this custom clipformat and registers
  that format enumerator on the bindctx. The net effect of this is that IE will use this
  custom type in the HTTP "Accept" header supplied to remote servers to indicate the
  accepted types that we're looking for. Feel free to experiment with different servers
  and different requested types.

* IEMime marks itself as safe-for-persistence on the IPersistPropertyBag interface. This
  is necessary to allow controls to receive Property persistence through <PARAM> tags. 
  The standard ATL IObjectSafetyImpl doesn't support this automatically, so we override
  Set/GetInterfaceSafetyOptions and do the right magic.

* Miscellaneous Note #1: When asking a BindHost to do a binding via MonikerBindToStorage,
  the IBindStatusCallback registered on the IBindCtx will not be used in most cases and
  will get dumped. It's pretty important to supply the IBindStatusCallback interface as the
  third parameter to MonikerBindToStorage. 

* Miscellaneous Note #2: IProvideClassInfo(2) must be implemented by a control if it wants
  IE/MSHTML to connect the control's event sink for scripting.
