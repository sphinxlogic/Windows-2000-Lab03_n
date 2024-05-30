This directory contains several sub-directories for MSMQ sample programs:

Sub-directory	Description
-------------	-----------
C_DRAW		C++ distributed Windows drawing application.  
		Port of VB_DRAW implemented with the MSMQ SDK C API.
		Interops with VB_DRAW and IMP_DRAW.

Imp_Draw	C++ distributed Windows drawing application.
		Port of VB_DRAW implemented with the MSMQ COM components.
		Interops with C_DRAW and VB_DRAW.

MQAPITST	C Windows application to interactively invoke MSMQ SDK C APIs.

mqport		C++ console application demonstrating how to use completion ports
		to asynchronously receive MSMQ messages.  Implemented with
		both the MSMQ SDK C API and the MSMQ COM components.

MQTESTOA	C++ console app that demonstrates how to send and receive messages
		between processes.  Implemented with the MSMQ COM components.  Interops
		with msmqtest.

MQTRANS		C++ console app that demonstrates how to send/receive coordinated 
		transactions that include MSMQ messages and SQL database updates.

mqtrigger	VB and C++ application that shows how to use NT MSMQ PerfMon counters
		in order to implement trigger functionality. 

msmqtest	C++ console app that demonstrates how to send and receive messages
		between processes.  Implemented with the MSMQ SDK C API.  Interops 
		with msmqtest.

VB_DRAW		VB distributed Windows drawing application.  Interops with C_DRAW and IMP_DRAW.
