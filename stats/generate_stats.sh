start=10000
gap=200
max=20000
repeat=3
gen=stats/result_gen.csv
path=stats/result_path.csv

for i in $(seq $start $gap $max); do
    for j in $(seq 1 $repeat); do
        printf "%d;%d;" $i $(($i * $i)) >>$gen
        printf "%d;%d;" $i $(($i * $i)) >>$path
        ./maze $i $i 0 0 1
        echo >>$gen
        echo >>$path
    done
    printf "%d done\n" $i
done

python3 stats/generate_fig.py
