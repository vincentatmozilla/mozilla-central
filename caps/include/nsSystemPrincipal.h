/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * The contents of this file are subject to the Netscape Public
 * License Version 1.1 (the "License"); you may not use this file
 * except in compliance with the License. You may obtain a copy of
 * the License at http://www.mozilla.org/NPL/
 *
 * Software distributed under the License is distributed on an "AS
 * IS" basis, WITHOUT WARRANTY OF ANY KIND, either express or
 * implied. See the License for the specific language governing
 * rights and limitations under the License.
 *
 * The Original Code is mozilla.org code.
 *
 * The Initial Developer of the Original Code is Netscape
 * Communications Corporation.  Portions created by Netscape are
 * Copyright (C) 1999 Netscape Communications Corporation. All
 * Rights Reserved.
 *
 * Contributor(s): 
 */

/* The privileged system principal. */

#ifndef _NS_SYSTEM_PRINCIPAL_H_
#define _NS_SYSTEM_PRINCIPAL_H_

#include "nsBasePrincipal.h"

// TODO: get new cid
#define NS_SYSTEMPRINCIPAL_CID \
{ 0x7ee2a400, 0x0c99, 0xaad3, \
{ 0xba, 0x18, 0xd7, 0x60, 0xb0, 0xf1, 0x99, 0xa2 }}

class nsSystemPrincipal : public nsBasePrincipal {
public:
    
    NS_DECL_ISUPPORTS
    
    NS_IMETHOD ToString(char **result);

    NS_IMETHOD Equals(nsIPrincipal *other, PRBool *result);

    NS_IMETHOD HashValue(PRUint32 *result);

    NS_IMETHOD CanEnableCapability(const char *capability, PRInt16 *result);

    NS_IMETHOD SetCanEnableCapability(const char *capability, 
                                      PRInt16 canEnable);

    NS_IMETHOD IsCapabilityEnabled(const char *capability, void * annotation, 
                                   PRBool *result);

    NS_IMETHOD EnableCapability(const char *capability, void * *annotation);

    NS_IMETHOD RevertCapability(const char *capability, void * *annotation);

    NS_IMETHOD DisableCapability(const char *capability, void * *annotation);

    nsSystemPrincipal();
    
    NS_IMETHOD Init();

    virtual ~nsSystemPrincipal(void);
};

#endif // _NS_SYSTEM_PRINCIPAL_H_
