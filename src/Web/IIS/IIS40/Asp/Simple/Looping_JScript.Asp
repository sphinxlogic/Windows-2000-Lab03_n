<%@ LANGUAGE = JScript %>

<HTML>
    <HEAD>
        <TITLE>Looping</TITLE>
    </HEAD>

    <BODY bgcolor="white" topmargin="10" leftmargin="10">

        
        <!-- Display Header -->

        <font size="4" face="Arial, Helvetica">
        <b>Looping with ASP</b></font><br>
      
        <hr size="1" color="#000000">



        <!-- Looping with a for loop -->

        <% for(i = 1; i < 6; i++) { %> 

            <FONT SIZE=<% = i %>> 
            Hello World with a For Loop!<BR>
			</FONT> 

        <% } %> 


        <hr>


        <!-- Looping with a while loop -->

        <% 
           i = 1;
        %>

        <% while (i < 6) { %>
    
            <FONT SIZE=<% = i %>> 
            Hello World with a While Loop!<BR>
			</FONT> 

            <% i = i+1; %>

        <% } %> 


        <hr>


        <!-- Looping with a do..while loop -->

        <% 
           i = 1;
        %>

        <% do { %>
    
            <FONT SIZE=<% = i %>> 
            Hello World with a Do..While Loop!<BR>
			</FONT> 

            <% i = i+1; %>

        <% } while (i < 6); %> 

    </BODY>
</HTML>
