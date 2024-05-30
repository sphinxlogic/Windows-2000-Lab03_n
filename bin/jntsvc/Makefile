all: testservice.exe

testservice.exe: testservice.class
    jntsvc /svcmain:TestService /eventsource:TestService testservice.class

testservice.class: testservice.java
    ..\jvc -cp:p service.zip testservice.java

clean:
    del testservice.class
    del testservice.exe
