x<-rnorm(1000,40,3)
mean(x)
var(x)

# FUNCIO DE DENSITAT #

x<-seq(20,60,by=0.05)	# Coneixent la Norma.
y<-dnorm(x,40,3)
plot(x,y, type="l")

x<-seq(0,1,by=0.005)	# No coneixent la llei.
y<-(3/7)*(x+1)^2
plot(x,y, type="l")

# FUNCIO DE DISTRIBUCIO #

x<-seq(20,60,by=0.05)	# Coneixent la Norma.
y<-pnorm(x,40,3)
plot(x,y, type="l")

x<-seq(0,1,by=0.05)	# No coneixent la llei.
y<-(1/7)*(x+1)^3-1/7
plot(x,y, type="l")

# CALCULAR PROBABILITATS #

pnorm(45,40,3)		# P(X<=45)
1-pnorm(35,40,3)		# P(X>=35) == 1 - P(X<35)
qnorm(0.8,40,3)		# y == P(X<=y)

x<-0.3			# P(X<=0.3)
y<-(1/7)*(x+1)^3-1/7
x<-0.8			# P(X>=0.8) == 1 - P(X<0.8)
y<-1-((1/7)*(x+1)^3-1/7)
