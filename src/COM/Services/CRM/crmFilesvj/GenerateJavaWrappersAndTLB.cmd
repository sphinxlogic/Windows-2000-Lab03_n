REM ----------------------------------------------------------------------------
REM
REM Generates Java wrappers for the components in comsvcs.dll and compiles 
REM the type library for crmfilesvj.dll.
REM
REM CAUTION! Be careful using the COM Classes Tab (Project Properties Dialog 
REM Box). Selecting an existing type library is a destructive operation; one 
REM that replaces existing code with template code for the COM classes and
REM interfaces defined in the existing type library.
REM
REM ----------------------------------------------------------------------------


ECHO ----------------------------------------------------------------------------
ECHO 1. Generating Java wrappers for the comsvcs package
ECHO ----------------------------------------------------------------------------

rem
rem The CrmFilesVJ packages gets its definition of ICrmCompensatorVariants
rem and XACTE from this codebase.
rem

jactivex /nologo /d . /e /l "comsvcs.lst" %SystemRoot%\System32\comsvcs.dll

ECHO ----------------------------------------------------------------------------
ECHO 2. Compiling the type library for crmfilesvj.dll (This type library can be
ECHO used by Visual J++ to generate stub code)
ECHO ----------------------------------------------------------------------------
ECHO CAUTION! Be careful using the COM Classes Tab (Project Properties Dialog 
ECHO Box). Selecting an existing type library is a destructive operation; one 
ECHO that replaces existing code with template code for the COM classes and
ECHO interfaces defined in the existing type library.
ECHO ----------------------------------------------------------------------------

midl /win32 /nologo /dlldata nul /header nul /iid nul /proxy nul /tlb crmfilesvj.tlb crmfilesvj.idl
