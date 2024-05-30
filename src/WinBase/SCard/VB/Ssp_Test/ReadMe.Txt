SSP_TEST illustrates how to use the Smart Card SDK low-level SSP COM interfaces
to perform basic smart card functions.  The project expects a data file to be
available on the card (ID: 3F05) of type transparent EF and at least 120 bytes.

Files included in this sample
=============================

1) ReadMe.txt   - This file
2) scardvb.frm  - Main program
3) scardvb.vbp  - Visual Basic Project file

Low-level SSP functions used in this sample
===========================================

ISCard
- AttachByReader
- LockSCard
- Transaction
- UnlockSCard
- Detach

ISCardCmd
- ReplyStatusSW1
- ReplyStatusSW2
- ApduReplyLength
- ApduReply

ISCardISO7816
- SetDefaultClassId
- SelectFile
- UpdateBinary
- ReadBinary

IByteBuffer
- Read
- Initialize
- Seek
- Write

How to compile
==============

The following steps must be successfully completed in sequence:

    1) Open the .vbp project
    2) From the Project/References menu, reference the following
       type libraries built from the corresponding .IDL files
       (refer to section 8)

                scarddat.tlb
                scardmgr.tlb
                scardsrv.tlb

    3) Build the project
    4) Save the project

If compile/run of project complains about the following:

    Line 64: Property TextRTF in Test_Step had an invalid value
    Line 77: Property TextRTF in Test_Output had an invalid value
    Line 64: Property TextRTF in Test_Step had an invalid value
    Line 77: Property TextRTF in Test_Output had an invalid value

Save the .frm file and the project and close Visual Basic. Then
re-start Visual Basic and re-open the project.

