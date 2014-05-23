To compile, produce histogram data from warandpeace.txt, and show a graph of it, just run "make".

If you want to do it step by step...


To produce histogram data, run:

./exercise1 ./warandpeace.txt > histdata.txt


To plot the data, run:

echo 'set log xy; plot "histdata.txt" using 2 title "Word popularity"' | gnuplot -persist
