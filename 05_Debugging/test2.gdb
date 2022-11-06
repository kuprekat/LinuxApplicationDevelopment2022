set pagination off

set $var = 1

break range.c:29
	command 1
	if $var > 27 & $var < 36
		printf "@@@ start = %d, end = %d, step = %d, element = %d\n", start, end, step, i
	end
	set $var = $var + 1
	continue
end

run -100 100 3
quit
