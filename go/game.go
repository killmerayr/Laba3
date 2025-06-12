package main

import (
	"fmt"
)

func max(a, b int) int {
	if a > b {
		return a
	}
	return b
}

func main() {
	var countNumbers, maxTake int
	fmt.Print("Введите количество чисел и маскисмальное количество чисел за ход: ")
	fmt.Scan(&countNumbers, &maxTake)

	sequence := make([]int, countNumbers)
	fmt.Printf("Введите %d целых чисел: ", countNumbers)
	for i := 0; i < countNumbers; i++ {
		fmt.Scan(&sequence[i])
	}

	prefixSum := make([]int, countNumbers+1)
	for idx := 0; idx < countNumbers; idx++ {
		prefixSum[idx+1] = prefixSum[idx] + sequence[idx]
	}

	dpt := make([]int, countNumbers+1)
	for pos := countNumbers - 1; pos >= 0; pos-- {
		maxDiff := -1000000000
		for take := 1; take <= maxTake && pos+take <= countNumbers; take++ {
			sumTaken := prefixSum[pos+take] - prefixSum[pos]
			maxDiff = max(maxDiff, sumTaken-dpt[pos+take])
		}
		dpt[pos] = maxDiff
	}

	if dpt[0] > 0 {
		fmt.Println("1 - Победил Павел")
	} else {
		fmt.Println("0 - Победила Вика")
	}
}
