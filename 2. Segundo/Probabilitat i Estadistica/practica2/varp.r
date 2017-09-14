varp <- function(x) {
	for (i in lenght(x))
		res1 += (x[[i]]-sum(x))^2
	
	res2 = (res1/lenght(x))
	
	return res2