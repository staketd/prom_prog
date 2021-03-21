BEGIN {
	count=0
}

function human_readable(x) {
	if (x < 1024)
	 {
	 	return x
	 } else {
	 	x /= 1024
	 }
	 suffs="KMGT";
	 ind=1;
	 while (x >= 1024 && ind <= 4) {
	 	x /= 1024;
	 	ind+=1
	 }
	 return int(x + 0.5) substr(suffs, ind, ind)
}
{
	if ( NF >= 5) {
		count=count + $5
	}
}

END {
	print count
	print human_readable(count)
}