// SampleRequest.java
//
// Created 09/10/97
//
// (C)Copyright 1997 Microsoft Corporation, All rights reserved.
//

package com.ms.samples.security.custom;

import com.ms.security.*;
import com.ms.security.auditing.*;


/**
 * Request object are optional for simplistic permissions
 * (such as SamplePermission).  Any object may be used for a parameterized
 * security check, but request objects make it easier for clients of
 * parameterized permission to make checks.
 * <p>
 * ISecurityRequest
 * is a convenience interface - it provides the permission id of the
 * permission the request object should be used with, so that clients
 * of the permission do not need to worry about getting it right.
 * <p>
 * ISecurityAuditInfo provides additional information to an auditor
 * to enable it to better present the request in an auditing log.
 * Request objects that do not implement this interface are simply
 * toString'd.
 */
public class SampleRequest implements ISecurityRequest,
                                      ISecurityAuditInfo
{
    String item;


    public SampleRequest (String item)
    {
        if (item == null)
            throw new NullPointerException();
        this.item = item;
    }


    // ISecurityRequest methods

    public PermissionID getPermissionID ()
    {
        return SamplePermission.id;
    }


    // ISecurityAuditInfo methods

    public String getAuditIdentifier ()
    {
        return "com.ms.samples.security.custom";
    }

    public String[] getAuditDetails ()
    {
        String[] details = new String[1];
        details[0] = item;
        return details;
    }
}

