//////////////////////////////////////////////////////////////////////////
//
//  AFCBeanListener.java
//
//      This example demonstrates how one can write a 100% pure AFC
//      object and host it inside of an ActiveX container. When used in
//      development tool that has a design mode, when the PropertyViewer
//      for the bean is displayed, it will use a UIComponent for a 
//      customizer.
//
//      This file defines an interface for listening to the AFCBean events.
//
//  (C) Copyright 1997 by Microsoft Corporation. All rights reserved.
//
//////////////////////////////////////////////////////////////////////////

public interface AFCBeanListener extends java.util.EventListener
{
    public void itemSelected();
}