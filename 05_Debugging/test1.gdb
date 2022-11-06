set pagination off

break range.c:29 if i % 5 == 0
	command 1
	printf "@@@ start = %d, end = %d, step = %d, element = %d\n", start, end, step, i
	continue
end

run 1 12
quit
