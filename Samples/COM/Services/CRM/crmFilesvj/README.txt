
README.TXT - crmfilesvj

This project is a sample Compensating Resource Manager (CRM) that creates and deletes files.

The crmfilesvj.Worker provides an interface for creating or deleting files.

The crmfilesvj.Compensator implements ICrmCompensatorVariants to receive transaction outcome notifications.

This CRM can be installed in a server application or in a library application. 

The crmfilesvj.Worker requires a transaction. The crmfilesvj.Compensator should not have a transaction.

To build crmfilesvj.dll

1.	Run GenerateJavaWrappers.cmd. This batch file creates Java wrappers for %SystemRoot%\system32\comsvcs.dll and compiles crmfilesvj.idl to produce crmfilesvj.tlb.

2.	Put the crmfilesvj sub-directory on your system Classpath environment variable. The comsvcs and crmfilesvj class files in this sub-directory are required by crmfilesvj.dll.

3.	Build the comsvcs project.

4.	Build the crmfilesvj project.

