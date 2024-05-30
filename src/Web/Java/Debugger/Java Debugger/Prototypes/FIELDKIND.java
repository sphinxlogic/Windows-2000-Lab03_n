package com.ms.debug;

public final class FIELDKIND
{
  public static final int FIELD_KIND_DATA_OBJECT    = 0x0001;
  public static final int FIELD_KIND_DATA_PRIMITIVE = 0x0002;
  public static final int FIELD_KIND_ARRAY          = 0x0004;
  public static final int FIELD_KIND_CLASS          = 0x0008;
  public static final int FIELD_KIND_METHOD         = 0x0010;
  public static final int FIELD_KIND_LOCAL          = 0x1000;
  public static final int FIELD_KIND_PARAM          = 0x2000;
  public static final int FIELD_KIND_THIS           = 0x4000;
}
