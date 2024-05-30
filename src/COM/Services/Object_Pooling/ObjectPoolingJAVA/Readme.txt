Object Pooling JAVA Sample

Pre Build Configuration

  - 	Create new Database(Name: "Bank")
  -     Create new System DSN (Name : "Account", User : sa  Password : , Database: "Bank")
  -     Make any database setting changes in Object_Pooling\ObjectPoolingJAVA\ObjectPoolingComponent\Account\util\databaseSettings.java
  -	Set the User Environment Variable "Classpath" to point to the Object_Pooling\ObjectPoolingJAVA\ObjectPoolingComponent\Account folder

Build
  - 	Open and build  Object_Pooling\ObjectPoolingJAVA\ObjectPoolingComponent\Account\Account.vjp
  -     Open and build  Object_Pooling\ObjectPoolingJAVA\ObjectPoolingClient\InitDatabase\InitDatabase.vjp
  -     Open Object_Pooling\ObjectPoolingJAVA\ObjectPoolingClient\GUI\ObjectPoolingClient.vjp
  -     From the Menu bar select "Project" - "Add COM Wrapper"
  -     Un-check "Account" if checked
  -     Click "OK"
  -     From the Menu bar select "Project" - "Add COM Wrapper"
  -     Check "Account"
  -     Click "OK"
  -     Build ObjectPoolingClient


Configure
  -	Add new COM+ Application (Name: Object Pooling)
  -     Add new componet (Account.dll)
  -     Go to properties of the Account.Account component and select the Activation tab
  -     Check the "Enable object pooling" check box
  -     Enter minimum pool size: 1
  -     Enter maximum pool size: 2
  -     Enter Creation timeout: 60000
  -     Press OK.

To Run 
  -	To Initialize the Database for first time run: Object_Pooling\ObjectPoolingJAVA\ObjectPoolingClient\InitDatabase\InitDatabase.exe		
  -	Run client: Object_Pooling\ObjectPoolingJAVA\ObjectPoolingClient\GUI\ObjectPoolingClient.exe
  -	Enter the data(Valid account numbers are in rane 1-30)
  -  	Perform the desired operation(such as Balance, Debit etc.)

To Check object pooling

  -	In the Com Explorer 
	- Click Components in Object pooling application
	- click status view icon on the toolbar to see the pool status


 	  	
	 