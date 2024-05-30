
README.TXT - CrmFiles

This project is a sample Compensating Resource Manager (CRM) that creates and deletes files.

The CRM Worker provides an interface for creating or deleting files.

The CRM Compensator implements ICrmCompensator to receive transaction outcome notifications.

The CRM Compensator also implements ICrmFormatLogRecords to support monitoring.

This CRM can be installed in a server application or in a library application. 

The CRM Worker requires a transaction. The CRM Compensator should not have a transaction.


