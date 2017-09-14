sdp <- function(x) {
	for (i in lenght(x))
		res1 += (x[[i]]-sum(x))^2
	
	res2 = sqrt(res1/lenght(x))
	
	return res2


#sdp <- function(x) {
#	return sqrt(varp(x))