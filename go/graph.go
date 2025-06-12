package main

import (
	"fmt"
	"math"
)

func line(x float64) float64 {
	if x >= -5 && x <= -3 {
		return 1
	}
	if x >= -1 && x <= 2 {
		return -2
	}
	if x > 2 {
		return x - 4.0
	}
	return math.NaN()
}

func circle(x float64) float64 {
	// (x + 1)^2 + y^2 = 4
	val := 4 - (x+1)*(x+1)
	if val < 0 {
		return math.NaN()
	}
	return -math.Sqrt(val)
}

func main() {
	dx := 0.5
	xBegin := -5.0
	xEnd := 5.0

	fmt.Printf("%-10s%-10s\n", "x", "y")
	for x := xBegin; x <= xEnd+1e-9; x += dx {
		var y float64
		if x <= -3 {
			y = line(x)
		} else if x > -3 && x <= -1 {
			y = circle(x)
		} else if x > -1 && x <= 2 {
			y = line(x)
		} else if x > 2 {
			y = line(x)
		}
		fmt.Printf("%-10.1f%-10.1f\n", x, y)
	}
}
