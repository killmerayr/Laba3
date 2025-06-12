package main

import (
	"fmt"
	"math"
	"sort"
)

// Решето Эратосфена
func eratosthenesSieve(limit int) []int {
	isPrime := make([]bool, limit+1)
	for i := range isPrime {
		isPrime[i] = true
	}
	isPrime[0], isPrime[1] = false, false
	for p := 2; p*p <= limit; p++ {
		if isPrime[p] {
			for i := p * p; i <= limit; i += p {
				isPrime[i] = false
			}
		}
	}
	primes := []int{}
	for i := 2; i <= limit; i++ {
		if isPrime[i] {
			primes = append(primes, i)
		}
	}
	return primes
}

// Факторизация числа на простые множители
func factorize(num uint64) [][2]int {
	result := make([][2]int, 0)
	primes := eratosthenesSieve(500)
	for _, prime := range primes {
		exponent := 0
		for num%uint64(prime) == 0 && num > 0 {
			exponent++
			num /= uint64(prime)
		}
		if exponent > 0 {
			result = append(result, [2]int{prime, exponent})
		}
	}
	return result
}

// Быстрое возведение в степень по модулю
func modPow(a, exp, m uint64) int {
	res := 1
	base := int(a % m)
	for exp > 0 {
		if exp&1 == 1 {
			res = (res * base) % int(m)
		}
		base = (base * base) % int(m)
		exp >>= 1
	}
	return res
}

// Размер числа в битах (log2)
func sizeNum(n uint64) int {
	if n == 0 {
		return 0
	}
	return int(math.Log2(float64(n)))
}

// Структура для хранения результата
type PrimeResult struct {
	Num   uint64
	Tries int
	Prob  bool
}

// Печать таблицы результатов
func printTable(results []PrimeResult) {
	sort.Slice(results, func(i, j int) bool {
		return results[i].Num < results[j].Num
	})
	colWidth := 15
	for _, r := range results {
		fmt.Printf("%-*d", colWidth, r.Num)
	}
	fmt.Println()
	for _, r := range results {
		if r.Prob {
			fmt.Printf("%-*s", colWidth, "+")
		} else {
			fmt.Printf("%-*s", colWidth, "-")
		}
	}
	fmt.Println()
	for _, r := range results {
		fmt.Printf("%-*d", colWidth, r.Tries)
	}
	fmt.Println()
}
