###############################################################################
#
#  Microsoft Confidential
#	Copyright (C) Microsoft Corporation 1996
#	All Rights Reserved.
#
###############################################################################

.idl.tlb:
	midl -I$(_NTDRIVE)$(_NTROOT)\public\sdk\inc -I$(COMMONINC_DIR)\sdk\include\dt $(MIDL_FLAGS) $< 

ripple.tlb : ripple.idl

