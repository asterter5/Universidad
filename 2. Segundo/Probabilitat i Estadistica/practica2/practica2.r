#.....................................................#

varp <- function(x) {
	for (i in lenght(x))
		res1 += (x[[i]]-sum(x))^2
	
	res2 = (res1/lenght(x))
	
	return res2

#.....................................................#

sdp <- function(x) {
	return sqrt(varp(x))

#.....................................................#



stem(LakeHuron)

boxplot(LakeHuron)

hist(LakeHuron)
hist(LakeHuron, nclass=4)
hist(LakeHuron, nclass=5)
hist(LakeHuron, breaks=c(576,577,578,579,580,582))

quantile(LakeHuron)
quantile(LakeHuron, prob=c(0.20, 0.45, 0.89))

#...#

boxplot(count~spray, data=InsectSprays)

hist(InsectSprays$count, labels=TRUE)

#...#

table = c(0, 40, 1, 52, 2, 83, 3, 24, 4, 12, 5, 4)
dim(table) = c(2, 6)

mean(table)

var(table)
#varp(table)

sd(table)
#sdp(table)

#...#

boxplot(weight~Diet, data=ChickWeight)


