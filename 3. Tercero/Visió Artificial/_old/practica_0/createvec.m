niter = 7;

for i = 1: niter
   A(i) = rand(1, 1); 
end

a3 = A(3);
B = A(1:5);
C = A(1:2:7);
C1 = C + .7;
C2 = C + C1;

D = [];
for j = 1:5
    if B(j) >= .4
        D(j) = B(j);
    end
end
D = D(D~=0);

disp(sprintf('Matrix(A)', A))
disp(sprintf('Value(A(3))', a3))
disp(sprintf('Matrix(B)', B))
disp(sprintf('Matrix(C)', C))
disp(sprintf('Matrix(C + 0.7)', C1))
disp(sprintf('Matrix(C + (C + 0.7))', C2))
disp(sprintf('Matrix(D)', D))