make clean
make compile

# Assigns the NUMBER to the $NUMBER variable in the makefile
# Then does make run and takes its output to the .txt file
# where the & symbol runs them in parallel
for NUMBER in {1..10}; do
    NUMBER=$NUMBER make run > "hello_world_${NUMBER}.txt" & 
done

wait

echo "Done"
