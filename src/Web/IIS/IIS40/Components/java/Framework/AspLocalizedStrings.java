/*  ********************************************************************************
    AspLocalizedStrings.java *******************************************************
    ********************************************************************************  */

package aspcomp;

/**
 * Localizable error message strings.
 */

public interface AspLocalizedStrings
{

/*  ********************************************************************************
    Exception Messages *************************************************************
    ********************************************************************************  */

    public static final String ASP_E_NON_STRING_DICT_KEY =
        new String("AspComponent: Get/Put attempted with a non-String key");
    
    public static final String ASP_E_DICT_REMOVE =
        new String("AspComponent: Remove attempted on an ASP dictionary");

    public static final String ASP_E_FAIL_GET_CONTEXT =
        new String("AspComponent: Retreiving MTx object context failed");

    public static final String ASP_E_FAIL_GET_INTRINSIC =
        new String("AspComponent: Failure in getting ASP intrinsic object");

    public static final String ASP_E_INTERNAL_FAILURE =
        new String("AspComponent: Internal error detected");

    public static final String ASP_E_READ_ONLY_DICT =
        new String("AspComponent: Put attempted on read-only ASP dicitonary");

    public static final String ASP_E_UNMARKED_STREAM =
        new String("AspComponent: Reset attempted on unmarked InputStream");

    public static final String ASP_E_COOKIE_PUT =
        new String("AspComponent: Put attempted on Cookie dictionary");
}
