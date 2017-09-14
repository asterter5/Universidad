
a<-c(5, 7, 9)
p<-c(1/3, 1/2, 1/6)
x<-runif(10)
x1<- (x<=p[1])
x2<- (x>p[1]&x<=p[1]+p[2])
x3<- (x>p[1]+p[2]&x<=p[1]+p[2]+p[3])
y<- a[1]*x1+a[2]*x2+a[3]*x3
y

# - - - #

x<-sample(c(5, 7, 9), 1000, prob=c(1/3, 1/2, 1/6), replace=TRUE)
table(x)/1000

# - - - #

m<- a%*%p			#Esperança
var<- a^2%*%p-m^2		#Variancia

# - - - #

#EX. 2
val<- c(3, 5, 7, 9)
prob<-c(0.1, 0.3, 0.2, 0.4)
x<-sample(val, 10000, prob, replace=TRUE)
freq<- table(x)/10000
espT<- 3*0.1+5*0.3+7*0.2+9*0.4
esp<- val%*%prob
varT<- val^2%*%prob-espT^2
var<- val^2%*%prob-esp^2
res<- c(freq, espT, esp, varT, var)
res