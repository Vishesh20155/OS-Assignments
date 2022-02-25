all: p1Fifo p2Fifo p1MsgQueue p2MsgQueue p1Socket p2Socket

p1Fifo: P1fifo.c
	gcc P1fifo.c -o p1Fifo

p2Fifo: P2fifo.c
	gcc P2fifo.c -o p2Fifo

p1Socket: P1socket.c
	gcc P1socket.c -o p1Socket

p2Socket: P2socket.c
	gcc P2socket.c -o p2Socket

p1MsgQueue: P1msgQ.c
	gcc P1msgQ.c -o p1MsgQueue

p2MsgQueue: P2msgQ.c
	gcc P2msgQ.c -o p2MsgQueue