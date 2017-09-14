
Fdd <- function (x, y) {
	len <- length(x)
	res <- array(0:len)
	for (i in len) res[[i]] <- ((x[[i]]-2^x[[i]])*y[[i]])/factorial(i)
	res
	ff <- sum(res)
	ff
	}

Fdd(c(1,2,3,4), c(4,3,2,1))