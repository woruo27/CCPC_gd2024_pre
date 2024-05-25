g++ -o val.exe val.cpp -static -O2
for i in {1..88}; do
    ./val.exe < "../data/$i.in"
	if [ $? -eq 0 ]; then
		echo "Testcase #$i is valid."
	fi
done
rm val.exe