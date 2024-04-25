g++ -o std std.cpp -static -O2 -std=c++17
for i in {1..13}; do
    ./std < "../data/$i.in" > "$i.out"
	diff "$i.out" "../data/$i.ans"
	if [ $? -eq 0 ]; then
		echo "Testcase #$i is ok."
	fi
	rm "$i.out"
done
rm std