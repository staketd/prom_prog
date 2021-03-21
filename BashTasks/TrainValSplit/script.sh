stratisfied=0
while [ $# -gt 0 ]; do
	case "$1" in
		--input*)
			file=$2
			shift 2
			;;
		--train_ratio*)
			train_ratio=$2
			shift 2
			;;
		--stratisfied*)
			stratisfied=1
			shift
			;;
		--y_column*)
			y_column=$2
			shift 2
			;;
		*)
			printf "Invalid argument $1"
			exit 1
	esac
done

number_of_data_lines=$(( $(wc -l $file | awk '{print $1}') - 1 ))
number_of_lines_in_train=$(echo "($number_of_data_lines * $train_ratio + 0.5)/1" | bc)
number_of_lines_in_test=$(( number_of_data_lines - number_of_lines_in_train ))
column_no=$(head -n 1 $file | awk 'BEGIN {RS=","} {print NR " " $1 "\n"}' | awk -v stat=$y_column 'BEGIN{IGNORECASE = 1;} $2 ~ stat {print $1}')

train="train_"$file
test="test_"$file

head -n 1 $file > $test
head -n 1 $file > $train

if [ $stratisfied -eq 0 ]; then
	head -n "-$number_of_lines_in_test" $file > $train
	tail -n "+$((number_of_lines_in_train + 2))" $file >> $test
else
	tail --lines=+2 $file > tmpfile
	awk -v col=$column_no -vtrain_ratio=$train_ratio -vtrain_file=$train -vtest_file=$test -vFPAT="([^,]*)|(\".*\")" '
		NR==FNR{
			count[$col]++;
		}
		NR!=FNR {
			printed[$col]++;
			if (int(count[$col] * train_ratio + 0.5) <= printed[$col]) {
				print $0 >> train_file;
			} else {
				print $0 >> test_file;
			}
		}
	' tmpfile tmpfile
	rm tmpfile
fi

