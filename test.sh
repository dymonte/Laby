values=(2 1000) #30000)
for width in "${values[@]}"; do
    for height in "${values[@]}"; do
        printf "\n+----------------------------------------------------------------+\n"
        printf "# Test with width $width and height $height\n"
        printf "+----------------------------------------------------------------+\n"

        time ./maze $width $height 1 0
    done
done
