while [ $# -gt 0 ]; do
	case "$1" in
		--input*)
			file=$2
			shift 2
			;;
		--category_size*)
			category_size=$2
			shift 2
			;;
		*)
			printf "Invalid argument $1"
			exit 1
	esac
done

jq ".annotations | map({image_id: .image_id, category_id: .category_id}) | group_by(.category_id) | map(select(length >= $category_size)) | flatten | .[].image_id" $file