package main

import (
	"fmt"
	"math"
)

func coffee(Tk, Tsr, r float64, totalMinutes int) []float64 {
	temperatures := make([]float64, totalMinutes+1)
	for t := 0; t <= totalMinutes; t++ {
		T := Tsr + (Tk-Tsr)*math.Exp(-r*float64(t))
		temperatures[t] = T
	}
	return temperatures
}

func printResults(totalMinutes int, temperatures []float64) {
	fmt.Println("Результаты моделирования остывания кофе:")
	fmt.Println("----------------------------------------")
	fmt.Println("|  Время (мин)  |  Температура (°C)  |")
	fmt.Println("----------------------------------------")
	for t := 0; t <= totalMinutes; t++ {
		fmt.Printf("|%10d   |%14.2f   |\n", t, temperatures[t])
	}
	fmt.Println("----------------------------------------")
}

func main() {
	var Tk, Tsr, r float64
	var totalMinutes int

	fmt.Print("Введите начальную температуру кофе (в градусах цельсия): ")
	fmt.Scan(&Tk)

	fmt.Print("Введите температуру окружающей среды (в градусах цельсия): ")
	fmt.Scan(&Tsr)

	fmt.Print("Введите коэффициент охлаждения (0 < r < 1): ")
	fmt.Scan(&r)

	fmt.Print("Введите время наблюдения (в минутах): ")
	fmt.Scan(&totalMinutes)

	temperatures := coffee(Tk, Tsr, r, totalMinutes)
	printResults(totalMinutes, temperatures)
}
