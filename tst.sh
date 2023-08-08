IFS="-	"
cat prim6.txt | while read i; do
    set $i
    echo "Testing: $1-$2-$3"
    gcc -O2 -DTEST=xoroshiro -DP1=$1 -DP2=$2 -DP3=$3 tst.c -o tst
    ./tst | PractRand/build/Linux/bin/RNG_test stdin32 -tlmin 128G -tlmax 128G | grep -e length= -e FAIL
done

exit 0

xorshift passing 128G:
18-13-2		37	33
7-8-3		39	18

xoroshiro weight 35/37 passing 128G:
2-9-5		35	16
13-3-6		35	22
16-12-5		37	33
18-13-5		35	36
25-9-4		35	38
1-15-24		37	40
24-15-1		37	40
6-27-7		35	40
