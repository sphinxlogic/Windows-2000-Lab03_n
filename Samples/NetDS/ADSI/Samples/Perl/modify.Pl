# This sample demonstrates how to retrieve/modify properties
# for objects in DS

use OLE;             # Include OLE and Win32 extensions
use Win32;

# Create the Global Providers object
$adsiNameSpaces = CreateObject OLE 'ADsNameSpaces'
                  or warn "Couldn't create new instance of the ADSI Name Spaces Check your registry for ADsNameSpaces key under classes!!";

$errNum = Win32::OLELastError;
if ($errNum != 0)
{
   print "OLE Error0: ", Win32::FormatMessage($errNum);
   exit(1);
}
else
{
    print "Successfully created the NameSpaces object\n";
}

# Now get the LDAP Provider object 
$ldapNameSpace = $adsiNameSpaces->getobject("", "LDAP:");

$errNum = Win32::OLELastError;
if ($errNum != 0)
{
   print "OLE Error1: ", Win32::FormatMessage($errNum);
   exit(1);
}
else
{
    print "Successfully got the LDAP Provider object\n";
}

# Let us bind to a DS
$myDSObject = $ldapNameSpace->OpenDSObject("LDAP:/\/\NW01T1/\DC=NW01T1DOM,DC=NTDEV,DC=Microsoft,DC=Com", "cn=administrator,cn=users,dc=nw01t1dom,dc=ntdev,dc=microsoft,dc=com", "", 1);

$errNum = Win32::OLELastError;
if ($errNum != 0)
{
   print "OLE Error2: ", Win32::FormatMessage($errNum);
   exit(1);
}
else
{
    print "Successfully bound to an object\n";
}

#Create an User object in the DS
$newObj = $myDSObject->create("User", "cn=Anandha");

$errNum = Win32::OLELastError;
if ($errNum != 0)
{
   print "OLE Error3: ", Win32::FormatMessage($errNum);
   exit(1);
}
else
{
    print "Successfully called IADsContainer::Create to create an object\n";
}

# We have to set the mandatory property samAccountName
$newObj->put("samAccountName", "Anandha");

$errNum = Win32::OLELastError;
if ($errNum != 0)
{
   print "OLE Error4: ", Win32::FormatMessage($errNum);
}
else
{
    print "Successfully set SamAccountName property on the created object\n";
}

# SetInfo on the object
$newObj->setinfo();

$errNum = Win32::OLELastError;
if ($errNum != 0)
{
   print "OLE Error5: ", Win32::FormatMessage($errNum);
}
else
{
    print "Successfully created the object in DS (SetInfo passes)\n";
}

####################################################
# Now let us demonstrate how to get/set properties #
####################################################

# Set a single valued property of syntax String
$newObj->put("singleString", "Ganesan");
$errNum = Win32::OLELastError;
if ($errNum != 0)
{
   print "OLE Error6: ", Win32::FormatMessage($errNum);
}
else
{
    print "Successfully put singleString\n";
}

# Get the singleString
$strVal = $newObj->get("singleString");
$errNum = Win32::OLELastError;
if ($errNum != 0)
{
   print "OLE Error7: ", Win32::FormatMessage($errNum);
}
else
{
    print "String value is $strVal\n";
}

# Set a single valued property of syntax Integer
$newObj->put("singleInteger", 1357);
$errNum = Win32::OLELastError;
if ($errNum != 0)
{
   print "OLE Error8: ", Win32::FormatMessage($errNum);
}
else
{
    print "Successfully put singleInteger\n";
}

# Get the singleInteger
$intVal = $newObj->get("singleInteger");
$errNum = Win32::OLELastError;
if ($errNum != 0)
{
   print "OLE Error9: ", Win32::FormatMessage($errNum);
}
else
{
    print "Integer value is $intVal\n";
}

# Set a single valued property of syntax Boolean
$newObj->put("singleBoolean", 1);
$errNum = Win32::OLELastError;
if ($errNum != 0)
{
   print "OLE Error10: ", Win32::FormatMessage($errNum);
}
else
{
    print "Successfully put singleBoolean\n";
}

# Get the singleBoolean
$boolVal = $newObj->get("singleBoolean");
$errNum = Win32::OLELastError;
if ($errNum != 0)
{
   print "OLE Error11: ", Win32::FormatMessage($errNum);
}
else
{
    print "Boolean value is $boolVal\n";
}

# Set a single valued property of syntax OctetString
$binaryString = 'this is binary string';
$newObj->put("singleOctetString", $binaryString);
$errNum = Win32::OLELastError;
if ($errNum != 0)
{
   print "OLE Error12: ", Win32::FormatMessage($errNum);
}
else
{
    print "Successfully put singleOctetString\n";
}

# Get the singleOctetString
$octStrVal = $newObj->get("singleOctetString");
$errNum = Win32::OLELastError;
if ($errNum != 0)
{
   print "OLE Error13: ", Win32::FormatMessage($errNum);
}
else
{
    print "OctetString value0 is $octStrVal \n";
}

# Set a single valued property of syntax UTCTime
$dateString = new OLE::Variant(OLE::VT_DATE, 'Feb 26, 1998');
$newObj->put("singleUTCTime", $dateString);
$errNum = Win32::OLELastError;
if ($errNum != 0)
{
   print "OLE Error14: ", Win32::FormatMessage($errNum);
}
else
{
    print "Successfully put singleUTCTime\n";
}

# Get the singleUTCTime
$dateStr = $newObj->get("singleUTCTime");
$errNum = Win32::OLELastError;
if ($errNum != 0)
{
   print "OLE Error15: ", Win32::FormatMessage($errNum);
}
else
{
    print "UTCTime value is $dateStr \n";
}

# Set a single valued property of syntax LargeInteger
$largeInt = 32352489;
$newObj->put("singleLargeInteger", $largeInt);
$errNum = Win32::OLELastError;
if ($errNum != 0)
{
   print "OLE Error16: ", Win32::FormatMessage($errNum);
}
else
{
    print "Successfully put singleLargeInteger\n";
}

# Get the singleLargeInteger
$largeInt1 = $newObj->get("singleLargeInteger");
$errNum = Win32::OLELastError;
if ($errNum != 0)
{
   print "OLE Error17: ", Win32::FormatMessage($errNum);
}
else
{
    print "LargeInteger value is $largeInt1 \n";
}

# Set a multi valued property of syntax String
@strArr1 = ("Anandha", "Ganesan", "Kumar");  #Create an array of strings
$refStrArr1 = \@strArr1;                     # Get reference to array

$newObj->put("multiString", $refStrArr1);
$errNum = Win32::OLELastError;
if ($errNum != 0)
{
   print "OLE Error18: ", Win32::FormatMessage($errNum);
}
else
{
    print "Successfully put multiString\n";
}

# Get the multiString
$strArr2 = $newObj->get("multiString");
$errNum = Win32::OLELastError;
if ($errNum != 0)
{
   print "OLE Error19: ", Win32::FormatMessage($errNum);
}
else
{
    print "String value is : @{ $strArr2 }\n";
}

# Set a multi valued property of syntax Integer
@intArr1 = (2343, 834, 234, 32048);  #Create an array of integers
$refIntArr1 = \@intArr1;             # Get reference to array

$newObj->put("multiInteger", $refIntArr1);
$errNum = Win32::OLELastError;
if ($errNum != 0)
{
   print "OLE Error20: ", Win32::FormatMessage($errNum);
}
else
{
    print "Successfully put multiInteger\n";
}

# Get the multiInteger
$intArr2 = $newObj->get("multiInteger");
$errNum = Win32::OLELastError;
if ($errNum != 0)
{
   print "OLE Error21: ", Win32::FormatMessage($errNum);
}
else
{
    print "Integer value is : @{ $intArr2 }\n";
}

# Set a multi valued property of syntax Boolean
@boolArr1 = (1, 0, 0);                #Create an array of integers
$refBoolArr1 = \@boolArr1;             # Get reference to array

$newObj->put("multiBoolean", $refBoolArr1);
$errNum = Win32::OLELastError;
if ($errNum != 0)
{
   print "OLE Error22: ", Win32::FormatMessage($errNum);
}
else
{
    print "Successfully put multiBoolean\n";
}

# Get the multiBoolean
$boolArr2 = $newObj->get("multiBoolean");
$errNum = Win32::OLELastError;
if ($errNum != 0)
{
   print "OLE Error23: ", Win32::FormatMessage($errNum);
}
else
{
    print "Boolean value is : @{ $boolArr2 }\n";
}

# Now delete the User object
$myDSObject->delete("User", "cn=Anandha");

$errNum = Win32::OLELastError;
if ($errNum != 0)
{
   print "OLE Error24: ", Win32::FormatMessage($errNum);
}
else
{
    print "Successfully deleted the object\n";
}

# Close handles to the OLE objects
DestroyObject OLE $myDSObject;
$errNum = Win32::OLELastError;
if ($errNum != 0)
{
   print "OLE Error25: ", Win32::FormatMessage($errNum);
   exit(1);
}
else
{
    print "Successfully destroyed the object myDSObject\n";
}

DestroyObject OLE $ldapNameSpace;
$errNum = Win32::OLELastError;
if ($errNum != 0)
{
   print "OLE Error26: ", Win32::FormatMessage($errNum);
   exit(1);
}
else
{
    print "Successfully destroyed the object ldapNameSpace \n";
}

DestroyObject OLE $adsiNameSpaces;
$errNum = Win32::OLELastError;
if ($errNum != 0)
{
   print "OLE Error27: ", Win32::FormatMessage($errNum);
   exit(1);
}
else
{
    print "Successfully destroyed the object adsiNameSpaces \n";
}
