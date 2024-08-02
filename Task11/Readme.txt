In this task  i have done my SPI communication through Master(MEGA) and slave(UNO) Without using API's AT Register level
important things must taken carefully
1--> data is only transferred when SS pin = low (0) (Always from master to slave 
2---> clock turns its state whenever (1) Mets
3---> trans_reception(I Defined like this ): transmission and receptions are done simultaneously from master to slave and slave to master 
4--->one must wait in order  to do (3) (i.e     while(!(SPSR& (1<<SPIF)));

5---> see From master side one MISO IS INput whereas MOSI,CS/SS,CLK ARE Outputs  

ignore file names as Serial_uni_slave AND Serial_uni_master but they just represents as slave and master code