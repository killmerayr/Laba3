package main

import (
	"fmt"
	"math"
)

// Вычисление суммы ряда
func computeSum(power, base, iterations int) float64 {
	sum := 0.0
	for n := 1; n <= iterations; n++ {
		sum += math.Pow(float64(n), float64(power)) / math.Pow(float64(base), float64(n))
	}
	return sum
}

// Проверка на рациональность (поиск приближённой дроби)
func isRational(value, epsilon float64) (numer, denom float64, ok bool) {
	denom = 1
	numer = 1
	diff := math.Abs(value - (numer / denom))
	tries := 0

	for tries != 100 {
		if numer/denom < value {
			numer++
		} else {
			denom++
		}
		diff = math.Abs(value - (numer / denom))
		tries++
		if diff < epsilon {
			return numer, denom, true
		}
	}
	return numer, denom, false
}

func main() {
	var power, base int
	fmt.Print("Введите свои a и b: ")
	fmt.Scan(&power, &base)

	if base == 1 {
		fmt.Println("Infinity")
	} else {
		sum := computeSum(power, base, 1000)
		epsilon := 1e-10
		numer, denom, ok := isRational(sum, epsilon)
		if !ok {
			fmt.Println("Irrational")
		} else {
			fmt.Printf("%.0f / %.0f\n", numer, denom)
		}
	}
}
