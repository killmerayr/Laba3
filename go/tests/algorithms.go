package main

import (
	"math"
	"math/rand"
)

// Тест Миллера
func millerTest(number uint64, rounds int) bool {
	if number == 2 || number == 3 || number == 5 || number == 7 {
		return true
	}
	if number < 10 {
		return false
	}

	bases := make(map[uint64]struct{})
	for len(bases) < rounds {
		base := uint64(rand.Intn(int(number-2)) + 2)
		bases[base] = struct{}{}
	}

	for base := range bases {
		if modPow(base, number-1, number) != 1 {
			return false
		}
	}

	primeFactors := factorize(number - 1)
	for _, factor := range primeFactors {
		primeQ := factor[0]
		onlyOne := true
		for base := range bases {
			if modPow(uint64(base), (number-1)/uint64(primeQ), number) != 1 {
				onlyOne = false
				break
			}
		}
		if onlyOne {
			return false
		}
	}
	return true
}

// Тест Поклингтона
func pocklingtonTest(number uint64, rounds int) bool {
	if number == 2 || number == 3 || number == 5 || number == 7 {
		return true
	}
	if number < 10 {
		return false
	}

	r := uint64(rand.Intn(3) + 1)
	primeFactors := factorize((number - 1) / r)

	bases := make(map[uint64]struct{})
	for len(bases) < rounds {
		base := uint64(rand.Intn(int(number-2)) + 2)
		bases[base] = struct{}{}
	}

	for base := range bases {
		if modPow(base, number-1, number) != 1 {
			return false
		}
	}

	for base := range bases {
		noOne := true
		for _, factor := range primeFactors {
			primeQ := factor[0]
			if modPow(base, (number-1)/uint64(primeQ), number) == 1 {
				noOne = false
				break
			}
		}
		if noOne {
			return true
		}
	}
	return false
}

// Генерация простого с помощью теста Миллера
func millerPrime(bitSize int, primes []int) (uint64, int) {
	var candidate uint64 = 1
	failedMillerCount := -1
	for !millerTest(candidate, 9) {
		attemptCount := 0
		var m uint64 = 1
		uniqQ := make(map[int]struct{})
		for sizeNum(m) != bitSize-1 {
			primeQ := primes[rand.Intn(len(primes))]
			expA := rand.Intn(20) + 1
			powQ := uint64(math.Pow(float64(primeQ), float64(expA)))
			if sizeNum(m*powQ) <= bitSize-1 && uniqQ[primeQ] == struct{}{} {
				m *= powQ
				uniqQ[primeQ] = struct{}{}
			}
			attemptCount++
			if attemptCount == 100 && sizeNum(m) != bitSize-1 {
				m = 1
				attemptCount = 0
				uniqQ = make(map[int]struct{})
			}
		}
		candidate = 2*m + 1
		failedMillerCount++
	}
	return candidate, failedMillerCount
}

// Генерация простого с помощью теста Поклингтона
func pocklingtonPrime(bitSize int, primes []int) (uint64, int) {
	var candidate uint64 = 1
	failedPocklingtonCount := -1
	for !pocklingtonTest(candidate, 9) {
		attemptCount := 0
		var f uint64 = 1
		uniqQ := make(map[int]struct{})
		for sizeNum(f)-1 != bitSize/2 {
			primeQ := primes[rand.Intn(len(primes))]
			expA := rand.Intn(20) + 1
			powQ := uint64(math.Pow(float64(primeQ), float64(expA)))
			if sizeNum(f*powQ)-1 <= bitSize/2 {
				f *= powQ
				uniqQ[primeQ] = struct{}{}
			}
			attemptCount++
			if attemptCount == 100 && sizeNum(f)-1 != bitSize/2 {
				f = 1
				attemptCount = 0
				uniqQ = make(map[int]struct{})
			}
		}
		r := f >> 1
		if r%2 == 1 {
			r++
		}
		candidate = r*f + 1
		failedPocklingtonCount++
	}
	return candidate, failedPocklingtonCount
}

// Генерация простого с помощью ГОСТ
func gostPrime(bitSize int, primes []int) (uint64, int) {
	if bitSize <= 1 {
		return 0, 0
	}
	if bitSize == 2 {
		return 3, 0
	}
	var p, n, u uint64
	q, _ := millerPrime(int(math.Ceil(float64(bitSize)/2)), primes)
	for {
		e := rand.Float64()
		n = uint64(math.Ceil(math.Pow(2, float64(bitSize-1))/float64(q))) +
			uint64(math.Ceil(math.Pow(2, float64(bitSize-1))*e/float64(q)))
		if n%2 == 1 {
			n++
		}
		u = 0
		p = (n+u)*q + 1
		if p <= uint64(math.Pow(2, float64(bitSize))) {
			break
		}
	}
	failedGostCount := -1
	for !(modPow(2, p-1, p) == 1 && modPow(2, n+u, p) != 1) {
		u += 2
		p = (n+u)*q + 1
		failedGostCount++
	}
	if failedGostCount == -1 {
		failedGostCount = 0
	}
	return p, failedGostCount
}
