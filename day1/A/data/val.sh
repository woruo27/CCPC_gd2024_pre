g++ -o val val.cpp -static -O2 -std=c++17
for i in {1..13}; do
    ./val < "$i.in"
	if [ $? -eq 0 ]; then
		echo "Testcase #$i is valid."
	fi
done
rm val