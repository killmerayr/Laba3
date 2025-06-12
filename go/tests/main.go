package main

import (
	"fmt"
	"math/rand"
	"time"
)

func main() {
	primes := eratosthenesSieve(500)

	fmt.Println("Алгоритмы для генерации простых чисел:")
	fmt.Println("- Генерация с помощью теста Миллера - 1.")
	fmt.Println("- Генерация с помощью теста Поклингтона - 2.")
	fmt.Println("- Генерация с помощью ГОСТ - 3.")

	var algorithmNum int
	for {
		fmt.Print("Введите номер алгоритма (1/2/3), или 0 для выхода: ")
		fmt.Scan(&algorithmNum)
		if algorithmNum > 0 && algorithmNum < 4 {
			break
		} else if algorithmNum == 0 {
			return
		}
		fmt.Println("Неверный номер алгоритма. Попробуйте еще раз (1/2/3), или 0 для выхода.")
	}

	rand.Seed(time.Now().UnixNano())
	minBits := 5
	maxBits := 13
	if algorithmNum == 3 {
		minBits = 16
		maxBits = 32
	}

	type PrimeFunc func(int, []int) (uint64, int)
	algorithms := []PrimeFunc{
		millerPrime,
		pocklingtonPrime,
		gostPrime,
	}

	results := []PrimeResult{}
	for len(results) < 10 {
		numSize := rand.Intn(maxBits-minBits+1) + minBits
		resultNum, tries := algorithms[algorithmNum-1](numSize, primes)

		var probTest bool
		if algorithmNum == 3 {
			probTest = pocklingtonTest(resultNum, 10)
		} else {
			probTest = millerTest(resultNum, 10)
		}

		results = append(results, PrimeResult{
			Num:   resultNum,
			Tries: tries,
			Prob:  probTest,
		})
	}

	fmt.Println("\nТаблица:")
	printTable(results)
}
