This WSH script uses VBScript to show uses of a few of the newer features
in the Content Deployment SDK (aka "CRS SDK").

Type "cscript crstool.vbs /?" to get command line help.

Three of the features were not implemented in this release.  They are:
a) listitems (ReplicationItem interface)
b) sendfiles (ReplicationClient/ReplicationClientError interface)
c) setpa     (ReplicationPostingAcceptor interface)

However, these features are implemented in a pre-compiled binary located
in the \bin directory.  A version is available for x86 and alpha platforms.
The binary is called "crstool.exe".  These features may be implemented in
a future release of the SDK.

If you execute crstool.exe and crstool.vbs, you should get very similar
output.