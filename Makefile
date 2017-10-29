lispy: lispy.c
		$(CC) -std=c99 -Wall lispy.c mpc.c -ledit -lm -o lispy
