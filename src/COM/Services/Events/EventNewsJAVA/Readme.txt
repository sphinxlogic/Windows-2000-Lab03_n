Events News JAVA Sample


Configure & Build.

1) Adding to CLASSPATH in User Enviroment Variables
       
       a)   Name: CLASSPATH
       b)   1st path to add: <path to Services\Events\EventNewsJAVA folder>
       c)   2nd path to add: <path to Services\Events\EventNewsJAVA\NewsEvent folder>
         	
2) Open the \Events\EventNewsJAVA\NewsEvent\helper\sampleConstants.java file and change the following

      a)  Change paths of PersistSubs.dll to reflect it's intended location 	
      b)  Change paths of CascadeEvent.dll to reflect it's intended location
      c)  Change paths of NewsEvent.dll to reflect it's intended location	
    
3) Build all the projects in the following sequence
    
      a) NewsEvent
      b) CascadeEvent
      c) PersistSubs
      d) NewsFlash
      e) NewsSubscriber

Running the Sample

Run NewsSubscriber.exe and do either step #1 or step #2

    1) Direct Events
    	a) Select the "Direct" radio button to receive the event directly from the publisher.
    	b) Click either "Subscribe" button.	 
    
    2) Cascade Event( To show event class can act both as subscriber and publisher)
	a) In the ' App name' give the name for cascade event application(for e.g 'Cascade')           
	b) Check the path in the 'Dll Path' , it should be pointing to the location of CascadeEvent.dll
	c) Click the "Install" button to install the cascade event class.
	d) Click the "Cascade" radio button to receive the event from cascade event class.
        e) Click the corresponding "Subscribe" button.

Run the NewsFlash.exe and do the following

   1) Install the event class
          a) Check the path in the 'EC DLL Path', it should be pointing to the location of NewsEvent.dll
          b) Click the install button.

    2) Publish the Event
           a) In Symbol type the symbol(for e.g "MSFT")
           b) In the Headline type the headline (for e.g. "Overshoot analyst expectations")
           c) Click the Publish button.
  
      


             	
              
