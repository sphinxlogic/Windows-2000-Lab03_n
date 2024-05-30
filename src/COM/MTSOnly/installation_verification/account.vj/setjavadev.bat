rem Compile AccountLib.idl yielding AccountLib.tlb
midl AccountLib.idl

rem Convert AccountLib.tlb to classes in the AccountLib package
javatlb /d . AccountLib.tlb

rem Add GUIDs to AccountLib classes
javaguid AccountLib\CAccount.class       AccountLib\IAccount.class
javaguid AccountLib\CGetReceipt.class    AccountLib\IGetReceipt.class
javaguid AccountLib\CMoveMoney.class     AccountLib\IMoveMoney.class
javaguid AccountLib\CUpdateReceipt.class AccountLib\IUpdateReceipt.class

rem Convert ADO typelib to classes in the msado15 package
rem This command produces 7 warnings
javatlb /d . "%SystemDrive%\Program Files\Common Files\System\ADO\msado15.dll"
