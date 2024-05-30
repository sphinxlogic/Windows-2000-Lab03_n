The Platform software development kit (SDK) provides
documentation on how to use notification events to provide asynchronous
handling of messages, which is one kind of trigger functionality. However,
you can also use Performance Monitor counters to monitor for triggering
conditions. This article points you to a sample application that shows you
how to write a trigger using a Performance Monitor counter.

The sample, "MQTrigger," is written in Visual Basic and C++. It uses a
timer event to periodically poll a Performance Monitor counter for a
message count. The sample application displays a dialog box when the
message count in a queue reaches the threshold.
