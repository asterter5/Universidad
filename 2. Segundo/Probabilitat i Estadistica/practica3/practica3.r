# EX 1.


x<-c(2,3,6,7,8,10)
prob<-c(0.2,0.1,0.2,0.1,0.2,0.2)

plot(x,prob,type="h", xlim=c(0,6), ylim=c(0,1))

acum<-cumsum(prob)
s<-stepfun(x, c(0,acum))
plot(s,verticals=FALSE)


# EX 2.


x<-c(0,1)
prob<-c(0.1,0.9)
plot(x,prob,type="h", xlim=c(0,1), ylim=c(0,1))

acum<-cumsum(prob)
s<-stepfun(x, c(0,acum))
plot(s,verticals=FALSE)


# EX 3.


# (A)
x<-c(0:3)
prob<-dbinom(x, 3, 0.4)
plot(x,prob,type="h", xlim=c(0,3), ylim=c(0,1))

acum<-cumsum(prob)
s<-stepfun(x, c(0,acum))
plot(s,verticals=FALSE)

# (B)
x<-c(0:10)
prob<-dbinom(x, 10, 0.001)
plot(x,prob,type="h", xlim=c(0,10), ylim=c(0,1))

acum<-cumsum(prob)
s<-stepfun(x, c(0,acum))
plot(s,verticals=FALSE)

# (C)
x<-c(0:20)
prob<-dbinom(x, 20, 0.8)
plot(x,prob,type="h", xlim=c(0,20), ylim=c(0,1))

acum<-cumsum(prob)
s<-stepfun(x, c(0,acum))
plot(s,verticals=FALSE)


# EX 4.


x<-c(0:5)
prob<-0.6

# (A)
dbinom(5, 5, 0.6)

# (B)
pbinom(3, 5, 0.6)

# (C)
1-pbinom(2, 5, 0.6)

# (D)
dbinom(2, 5, 0.6)

# (E)
1-pbinom(0, 5, 0.6)


# EX 5.



