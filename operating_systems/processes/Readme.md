The wheel

The main process (A) will create a subprocess (B) that will create another subprocess (C).
Then the main process (A) will send a generated random number (between 1000 and 2000) to process B.
The process (B) will subtract 10 units and will send the number to process (C). C will subtract 20 units and will send the number to (A). The (A) process will subtract 30 units and will send the number to (B), again. And so on, until the value is less than zero. In this moment, the game will stop.
The winner is the process that estabilished the negative number.
The communication between all the processes is done using pipe channels.