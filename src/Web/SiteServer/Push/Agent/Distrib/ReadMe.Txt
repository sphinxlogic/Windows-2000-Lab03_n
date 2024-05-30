-------------
INTRODUCTION
-------------

Active Channel Agents are employed by the Active Channel Server (ACS) to collect content for channels.  Active Channel Server provides a built-in set of Active Channel Agents, which may be extended by building and distributing custom and installable channel agents.  Custom agents can be used directly in the Active Channel Server without creating installable agent package.  If you choose to redistribute an agent or write an agent that requires special administration options, then you will want to create an installable agent.  An installable agent appears in the property pages for Channels, under the Agent tab. When the ACS administrator creates a channel, selects an installable Active Channel Agent, and chooses Options to configure the agent, the channel agent administration pages that are created to administer the agent will be displayed. The components of a redistributable Active Channel Agent are described below.

-------------
Components of an Installable Channel Agent
-------------

SampleAgent.DLL - COM Property Sheet that is displayed in the Active Channel Server MMC to configure the agent options.  This file's default install location is the SiteServer bin directory.
SampleAgent.VBS - The actual agent that populates the channel with content items, and optionally sub-channels.  This file's default install location is the SiteServer bin directory.
WizSampleAgent.ASP - ASP prop sheet for the Channel Wizard in the Web-based administration
AgSampleAgent.ASP - ASP prop sheet for the Channel Properties in the Web-based administration
WizPushChn0.ASP - ASP prop sheet for the Channel Wizard final page where custom options are persisted.   The Web-based administration wizard model does not persist the information gathered in the wizard until the last page of the wizard.  For some agents this page is not required.

NOTE: The ASP files' default install location is the SiteServer installation location under the SiteServer\Admin\Knowledge\ActiveChannel directory.

The channel agent files are contained in the 'Distrib' directory.

-------------
Building an Installable Channel Agent
-------------

The channel agent may created in VBScript or any scripting language that is supported by the ActiveX Scripting Host. The ASP files can be created and edited in any text or ASP editor.  The sample MMC channel agent options DLL can be built using a C++ development system that includes support for MFC and Unicode.  You may choose to build an agent options DLL using another language, such as Visual Basic, the agent must support the ISpecifyPropertyPages and IPropertyPage interfaces for the Active Channel Server to uses the agent options DLL.

Note: When building the agent option DLL sample using the debug libraries, you may see the sample agent display the message: 'Agent Page Name' has non-standard dimensions. This is expected in debug builds of the agent because the MMC property pages to not conform to the MFC standard property page sizes.  In the retail build, this message is not displayed.

-------------
Building an installable executable
-------------

Installing the Active Channel Agent can be accomplished using any installation toolkit.  The SampleAgent.DLL creates the required registry keys to use the installable agent in the Active Channel Server.

