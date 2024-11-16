max=2000
gen=stats/result_gen.csv
path=stats/result_path.csv

for i in $(seq 1000 500 $max); do
    printf "%d;%d;" $i $(($i * $i)) >>$gen
    printf "%d;%d;" $i $(($i * $i)) >>$path
    ./maze $i $i 0 0 1
    echo >>$gen
    echo >>$path
    printf "%d fait\n" $i
done

python3 stats/generate_fig.py
