{
	for (i=2; i<=NF; ++i) {
		count[$1]+=int($i)
		
		}
} 

END {
	for (word in count) {
		print word, count[word];
	}
}