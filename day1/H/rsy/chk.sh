g++ -o std match.cpp -static -O2 -std=c++17
for i in {1..43}; do
	./std < "../data/${i}.in" > temp
	diff temp "../data/${i}.ans"
	if [ $? -eq 0 ]; then
		echo "Testcase #${i} is valid."
	fi
	rm temp
done
rm std