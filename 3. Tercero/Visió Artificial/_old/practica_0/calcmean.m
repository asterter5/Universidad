nsamples = 5;
npoints = 5;

for k = 1: nsamples
    iterationString = ['Iteration #', int2str(k)];
    disp(iterationString)
    currentData = rand(npoints, 1);
    sampleMean(k) = mean(currentData)
end

overallMean = mean(sampleMean)

if overallMean < .49
    disp('Mean is Less than expected.')
elseif overallMean > .51
    disp('Mean is Greater than expected.')
else 
    disp('Mean whithin range!')
end
