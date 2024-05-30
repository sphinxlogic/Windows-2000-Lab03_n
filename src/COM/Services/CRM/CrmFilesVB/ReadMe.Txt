
README.TXT - CrmFilesVB

This project is a sample Compensating Resource Manager (CRM) implemented in Visual Basic that creates and deletes files.

See CrmFiles for the VC version.

The CRM Worker provides an interface for creating or deleting files.

The CRM Compensator implements ICrmCompensator to receive transaction outcome notifications.

This CRM can be installed in a server application or in a library application. 

The CRM Worker requires a transaction. The CRM Compensator should not have a transaction.


