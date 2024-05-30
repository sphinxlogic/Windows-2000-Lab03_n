# THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
# ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED
# TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
# PARTICULAR PURPOSE.
#
# Copyright 1998 Microsoft Corporation.  All Rights Reserved.
#
# Processor independent makefile

all:
	@$(MAKE) /$(MAKEFLAGS) -nologo -f dibview.mak all ICM=ICM_NONE
	@$(MAKE) /$(MAKEFLAGS) -nologo -f dibview.mak all ICM=ICM_INSIDE_DC
	@$(MAKE) /$(MAKEFLAGS) -nologo -f dibview.mak all ICM=ICM_OUTSIDE_DC

clean:
	@$(MAKE) /$(MAKEFLAGS) -nologo -f dibview.mak clean ICM=ICM_NONE
	@$(MAKE) /$(MAKEFLAGS) -nologo -f dibview.mak clean ICM=ICM_INSIDE_DC
	@$(MAKE) /$(MAKEFLAGS) -nologo -f dibview.mak clean ICM=ICM_OUTSIDE_DC
