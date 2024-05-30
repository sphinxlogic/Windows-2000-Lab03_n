   Module: SUPERUSR.C

   The following sample code demonstrates how to extract a token from
   a process running in the context of the local system and use it to 
   create a child process running in that same context. The local system
   security context is very powerful because of its far-reaching security 
   access.

   Once you have your superusr-mode console running, here are some interesting
   things to try:

      - Run WHOAMI.EXE

      - Run PVIEW from the reskit and look at the process tokens for
      the system services

      - Run REGEDT32 and have a look around in your SAM database

   Note: You must be a member of the local administrator group for this
   sample to work. Additionally, note that CreateProcessAsUser requires the 
   SeAssignPrimaryToken (Replace a process level token) and 
   SeIncreaseQuotaPrivilege (Increase Quotas) rights.

   Note: This sample relies on the fact that PID (2) is usually the "system"
   process. It is this process from which I extract the token that it used
   for CreateProcessAsUser(). If, for some reason, "system" is not PID (2), 
   change SYSTEM_PID to reflect the PID of "system" on your machine. You 
   can retrieve the PID with TLIST.EXE.