To use these ASP pages, create a Virtual Root in IIS to point to this
directory, then disable Anonymous authentication.  The API calls to
the CrsApi object will not function if the user is not authenticated
as a SiteServer Publishing Operator, a SiteServer Publishing Admin-
istrator, or a local Administrator.

If the new VRoot you have created points to URL http://machine/CDSDK
you will be able to access that URL to load default.asp.  From there
you can click on the ASP page links in the left pane to load the .asp
page samples.