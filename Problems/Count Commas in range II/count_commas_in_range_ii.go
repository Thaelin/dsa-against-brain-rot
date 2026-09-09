func countCommas(n int64) int64 {
	var commas int64 = 0
	var treshold int64 = 1000

	for n >= treshold {
		commas += n - treshold + 1
		treshold *= 1000
	}

	return commas
}